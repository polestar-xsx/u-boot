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

struct uart_port {
	unsigned long	iobase;		/* in/out[bwl] */
	unsigned char	*membase;	/* read/write[bwl] */
	unsigned long	mapbase;	/* for ioremap */
};

static void output_ansi_reset(void)
{

}

static void d1h_serial_init_generic(struct uart_port *port)
{
	writew(0x38,port->membase + (SCSCR_OFFSET));/* TIE=0,RIE=0,TE=1,RE=1,REIE=1 */
	writew(0x38,port->membase + (SCSCR_OFFSET));
	writew(0x00,port->membase + (SCSMR_OFFSET));
	writew(0x00,port->membase + (SCSMR_OFFSET));
	writew(0x06,port->membase + (SCFCR_OFFSET));
	readw(port->membase + (SCFCR_OFFSET));
	writew(0x00,port->membase + (SCFCR_OFFSET));
	writew(0x03,port->membase + (SCSPTR_OFFSET));
}

static int d1h_serial_probe(struct udevice *dev)
{
	struct d1h_serial_plat *plat = dev_get_plat(dev);
	struct uart_port *priv = dev_get_priv(dev);

	priv->membase	= (unsigned char *)plat->base;
	priv->mapbase	= plat->base;

	d1h_serial_init_generic(priv);

	return 0;
}

static int d1h_serial_remove(struct udevice *dev)
{
	struct d1h_serial_plat *plat = dev_get_plat(dev);


	return 0;
}

static int d1h_serial_putc(struct udevice *dev, const char ch)
{
	struct d1h_serial_priv *priv = dev_get_priv(dev);
	struct d1h_serial_plat *plat = dev_get_plat(dev);


	return 0;
}

static int d1h_serial_pending(struct udevice *dev, bool input)
{
	struct d1h_serial_priv *priv = dev_get_priv(dev);

	return 0;
}

static int d1h_serial_getc(struct udevice *dev)
{
	struct d1h_serial_priv *priv = dev_get_priv(dev);


	return 0;
}

#ifdef CONFIG_DEBUG_UART_D1H

#include <debug_uart.h>

static inline void _debug_uart_init(void)
{
}

static inline void _debug_uart_putc(int ch)
{
	os_putc(ch);
}

DEBUG_UART_FUNCS

#endif /* CONFIG_DEBUG_UART_D1H */

static int d1h_serial_getconfig(struct udevice *dev, uint *serial_config)
{
	uint config = SERIAL_DEFAULT_CONFIG;


	return 0;
}

static int d1h_serial_setconfig(struct udevice *dev, uint serial_config)
{

	return 0;
}

static int d1h_serial_getinfo(struct udevice *dev,
				  struct serial_device_info *serial_info)
{
	struct serial_device_info info = {
		.type = SERIAL_CHIP_UNKNOWN,
		.addr_space = SERIAL_ADDRESS_SPACE_IO,
		.addr = SERIAL_DEFAULT_ADDRESS,
		.reg_width = 1,
		.reg_offset = 0,
		.reg_shift = 0,
		.clock = SERIAL_DEFAULT_CLOCK,
	};

	if (!serial_info)
		return -EINVAL;

	*serial_info = info;

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
	.getconfig = d1h_serial_getconfig,
	.setconfig = d1h_serial_setconfig,
	.getinfo = d1h_serial_getinfo,
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
	.remove = d1h_serial_remove,
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