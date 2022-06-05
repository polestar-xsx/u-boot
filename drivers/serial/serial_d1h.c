#include <common.h>
#include <clk.h>
#include <dm.h>
#include <errno.h>
#include <malloc.h>
#include <watchdog.h>
#include <serial.h>
#include <debug_uart.h>
#include <asm/global_data.h>
#include <linux/compiler.h>
#include <linux/delay.h>

#include <asm/io.h>

DECLARE_GLOBAL_DATA_PTR;

#define SCSMR_OFFSET 0x00
#define SCBRR_OFFSET 0x04
#define SCSCR_OFFSET 0x08
#define SCFTDR_OFFSET 0x0C
#define SCFSR_OFFSET 0x10
#define SCFRDR_OFFSET 0x14
#define SCFCR_OFFSET 0x18
#define SCFDR_OFFSET 0x1C
#define SCSPTR_OFFSET 0x20
#define SCLSR_OFFSET 0x24
#define DL_OFFSET 0x30
#define CKS_OFFSET 0x34

/* SCFSR SCIF */
#define SCIF_ER    0x0080
#define SCIF_TEND  0x0040
#define SCIF_TDFE  0x0020
#define SCIF_BRK   0x0010
#define SCIF_FER   0x0008
#define SCIF_PER   0x0004
#define SCIF_RDF   0x0002
#define SCIF_DR    0x0001
#define SCIF_ERRORS (SCIF_PER | SCIF_FER | SCIF_ER | SCIF_BRK)

#define SCIF_ORER	0x0001

#define SCBRR_VALUE(bps, clk) ((clk+16*bps)/(32*bps)-1)
/*
 * Information about serial port
 *
 * @base:	Register base address
 * @clk:	Input clock rate, used for calculating the baud rate divisor
 * @clk_mode:	Clock mode, set internal (INT) or external (EXT)
 * @type:	Type of SCIF
 */
struct d1h_serial_plat {
	unsigned long base;
	unsigned int clk;
};

struct d1h_serial_priv {
	unsigned long	iobase;		/* in/out[bwl] */
	unsigned char	*membase;	/* read/write[bwl] */
	unsigned long	mapbase;	/* for ioremap */
};

static void output_ansi_reset(void)
{

}

static void handle_error(struct d1h_serial_priv *priv)
{
	readw(priv->membase + (SCFSR_OFFSET));
	writew(0x0073, priv->membase + (SCFSR_OFFSET));
	readw(priv->membase + (SCLSR_OFFSET));
	writew(0x0000, priv->membase + (SCLSR_OFFSET));
}

static int scif_rxfill(struct d1h_serial_priv *priv)
{
	return readw(priv->membase + (SCFDR_OFFSET)) & 0x001f;
}

static void d1h_serial_init_generic(struct d1h_serial_priv *priv)
{
	writew(0x38,priv->membase + (SCSCR_OFFSET));/* TIE=0,RIE=0,TE=1,RE=1,REIE=1 */
	writew(0x38,priv->membase + (SCSCR_OFFSET));
	writew(0x00,priv->membase + (SCSMR_OFFSET));
	writew(0x00,priv->membase + (SCSMR_OFFSET));
	writew(0x06,priv->membase + (SCFCR_OFFSET));
	readw(priv->membase + (SCFCR_OFFSET));
	writew(0x00,priv->membase + (SCFCR_OFFSET));
	writew(0x03,priv->membase + (SCSPTR_OFFSET));
}

static int d1h_serial_tstc_generic(struct d1h_serial_priv *priv)
{
	if (readw(priv->membase + (SCFSR_OFFSET)) & SCIF_ERRORS) 
	{
		handle_error(priv);
		return 0;
	}

	return scif_rxfill(priv) ? 1 : 0;
}

static int d1h_serial_probe(struct udevice *dev)
{
	struct d1h_serial_plat *plat = dev_get_plat(dev);
	struct d1h_serial_priv *priv = dev_get_priv(dev);

	priv->membase	= (unsigned char *)plat->base;
	priv->mapbase	= plat->base;

	d1h_serial_init_generic(priv);

	return 0;
}


static int d1h_serial_putc(struct udevice *dev, const char ch)
{
	struct d1h_serial_priv *priv = dev_get_priv(dev);
	struct d1h_serial_plat *plat = dev_get_plat(dev);
	/* Tx fifo is empty */
	if(!(readw(priv->membase + (SCFSR_OFFSET)) & 0x0040))
		return -EAGAIN;

	writew(ch, priv->membase + (SCFTDR_OFFSET));
	writew(readw(priv->membase + (SCFSR_OFFSET)) & (~(0x0040)), priv->membase + (SCFSR_OFFSET));

	return 0;
}

static int d1h_serial_pending(struct udevice *dev, bool input)
{
	struct d1h_serial_priv *priv = dev_get_priv(dev);

	return d1h_serial_tstc_generic(priv);
}

static int serial_getc_check(struct d1h_serial_priv *priv)
{
	unsigned short status;

	status = readw(priv->membase + (SCFSR_OFFSET));

	if (status & SCIF_ERRORS)
		handle_error(priv);
	if (readw(priv->membase + (SCLSR_OFFSET)) & SCIF_ORER)
		handle_error(priv);
	status &= (SCIF_DR | SCIF_RDF);
	if (status)
		return status;
	return scif_rxfill(priv);
}

static int d1h_serial_getc(struct udevice *dev)
{
	unsigned short status;
	char ch;
	struct d1h_serial_priv *priv = dev_get_priv(dev);
	if (!serial_getc_check(priv))
		return -EAGAIN;

	ch = readw(priv->membase + (SCFRDR_OFFSET));
	status = readw(priv->membase + (SCFSR_OFFSET));

	writew(0x00fc, priv->membase + (SCFSR_OFFSET));
	if (status & SCIF_ERRORS)
		handle_error(priv);

	if (readw(priv->membase + (SCLSR_OFFSET)) & SCIF_ORER)
		handle_error(priv);

	return ch;
}

static int d1h_serial_setbrg(struct udevice *dev, int baudrate)
{
	struct sh_serial_plat *plat = dev_get_plat(dev);
	struct uart_port *priv = dev_get_priv(dev);
	
	writew(SCBRR_VALUE(baudrate, plat->clk), priv->membase + (SCBRR_OFFSET));

	return 0;
}




static int d1h_serial_of_to_plat(struct udevice *dev)
{
	struct d1h_serial_plat *plat = dev_get_plat(dev);

	return 0;
}

static const struct dm_serial_ops d1h_serial_ops = {
	.putc = d1h_serial_putc,
	.pending = d1h_serial_pending,
	.getc = d1h_serial_getc,
	.setbrg = d1h_serial_setbrg,
};

static const struct udevice_id d1h_serial_ids[] = {
	{ .compatible = "d1h,serial" },
	{ }
};

U_BOOT_DRIVER(d1h_serial) = {
	.name	= "d1h_serial",
	.id	= UCLASS_SERIAL,
	.of_match = d1h_serial_ids,
	.of_to_plat = d1h_serial_of_to_plat,
	.plat_auto	= sizeof(struct d1h_serial_plat),
	.priv_auto	= sizeof(struct d1h_serial_priv),
	.probe = d1h_serial_probe,
	.ops	= &d1h_serial_ops,
	.flags = DM_FLAG_PRE_RELOC,
};

#if !CONFIG_IS_ENABLED(OF_PLATDATA)
static const struct d1h_serial_plat platdata_non_fdt = {
	.colour = -1,
};

U_BOOT_DRVINFO(serial_d1h_non_fdt) = {
	.name = "d1h_serial",
	.plat = &platdata_non_fdt,
};
#endif

#ifdef CONFIG_DEBUG_UART_D1H

#include <debug_uart.h>

static inline void _debug_uart_init(void)
{

}

static inline void _debug_uart_putc(int ch)
{

}

DEBUG_UART_FUNCS

#endif