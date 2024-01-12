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
#include <asm/arch/clock.h>
#include <asm/arch/base.h>
#include <asm/io.h>
#include "serial_d1h.h"
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


static void d1h_scif_initpfc(UART__tstPfcReg *scif_pfc)
{
	UART__tunPfcReg tempPfcReg;
	/* Configure GP4_2 and GP4_3 for SCIF2 (Function 1) */
      tempPfcReg.u32word = scif_pfc->u32Ipsr[8];    /* read */
      tempPfcReg.u32word &= UART__nIPSR_SCIF2_FUNC1_Msk;   /* modify - IP8[14:12]=0, IP8[11:9]=0 */
      scif_pfc->u32Pmmr = (~tempPfcReg.u32word);    /* write inverse value into PPMR */
      scif_pfc->u32Ipsr[8] = tempPfcReg.u32word;    /* write */

      tempPfcReg.u32word = scif_pfc->u32Gpsr[4];
      tempPfcReg.u32word |= ((1UL << 3) | (1UL << 2));   /* select Peripheral Function, GP4[3]=1, GP4[2]=1 */
      scif_pfc->u32Pmmr = (~tempPfcReg.u32word);    /* write inverse value into PPMR */
      scif_pfc->u32Gpsr[4] = tempPfcReg.u32word;    /* write */

      tempPfcReg.u32word = scif_pfc->u32ModSel;
      tempPfcReg.u32ModSel_view.biSelScif2 = 0x0U;   /* select Function 1 */
      scif_pfc->u32Pmmr = (~tempPfcReg.u32word);   /* write inverse value into PPMR */
      scif_pfc->u32ModSel = tempPfcReg.u32word;    /* write */
}

static int scif_rxfill(UART__tstCommonReg *port)
{
	return port->scfdr.bits.bi16R;
}

static void d1h_serial_init_generic(UART__tstCommonReg *port)
{
	//u32 u32OneBitInterval;   /*the duration of one bit interval in microsecond*/
	/* Initialize UART Control Registers */

	port->scscr.u16word = UART__nDefaultValue;   /* Clear the TE & RE to 0 */

	/* Reset the Tx & Rx FIFOs */
	port->scfcr.u16word |= UART__nFifoReset_Msk;

	port->scfsr.u16word = UART__nDefaultValue;   /* Clear ER,DR,BRK,and RDF */
	port->sclsr.u16word = UART__nDefaultValue;   /* Clear TO and ORER */

	/* Set data transfer format in SCSMR */
	/* Set up RS-232 Mode */
	port->scsmr.bits.bi16CA   = UART__nDefaultValue;   /* Asynchronous mode */

	/* 1 Stop bit, 8 Bits word size */
	port->scsmr.bits.bi16CHR  = UART_nCharLength8Bits;
	port->scsmr.bits.bi16STOP = UART_nOneStopBit;

	port->scsmr.bits.bi16PE = UART__nOn;
	port->scsmr.bits.bi16OE = UART_nParityNone;

	/* Setup UART clock*/
	port->scsmr.bits.bi16CKS = UART__SCSMR_CKS_cfg;   /* select clock source */
	port->cks.bits.bi16XIN = UART__CKS_XIN_cfg;
	port->cks.bits.bi16CKS = UART__CKS_CKS_cfg;
	/* The SCBRR setting , N = (P# /(64 x 2^(2n+1) x B)) - 1
	* B: Bit rate (bit/s)
	* P#: Peripheral module operating frequency
	* n: SCSMR.CKS[1:0] Setting
	*/
	//port->scbrr = (u8)(CLK_u32GetFrequencyS() / ((64UL << (2U * UART__SCSMR_CKS_cfg + 1U)) * UART_nBaud115200) - 1U);

	//u32OneBitInterval = UART__nOneSecond / UART_nBaud115200 + 1U;
	//udelay(u32OneBitInterval);

	/* Set bits RTRG[1:0], TTRG[1:0], and clear bits TFRST and RFRST to 0 */
	port->scfcr.bits.bi16RTRG = UART__nRTRG_1_BYTES;
	port->scfcr.bits.bi16TTRG = UART__nTTRG_0_BYTES;
	port->scfcr.bits.bi16TFRST = UART__nOff;
	port->scfcr.bits.bi16RFRST = UART__nOff;

	/* Wait at least one bit interval, then set bit TE or RE in SCSCR to 1 */
	//udelay(u32OneBitInterval);

	/* Enable UART transmiter */
	port->scscr.bits.bi16TE = UART__nOn;
	/* Enable UART receiver */
	port->scscr.bits.bi16RE = UART__nOn;
}

static void d1h_serial_setbrg_generic(UART__tstCommonReg *port, int baudrate)
{
	port->scbrr = (u8)(clock_u32GetFrequencyS() / ((64UL << (2U * UART__SCSMR_CKS_cfg + 1U)) * baudrate) - 1U);
	udelay(1000000/baudrate + 1);
}

static void handle_error(UART__tstCommonReg *port)
{
	port->scfsr.u16word &= ~UART_nRxErrorMask1;
	port->sclsr.u16word = 0x00;
}

static int serial_raw_putc(UART__tstCommonReg *port, const char c)
{
	/* Tx fifo is empty */
	if (port->scfdr.bits.bi16T == UART__nFifoFull)
		return -EAGAIN;
	port->scftdr = c;
	return 0;
}

static int serial_rx_fifo_level(UART__tstCommonReg *port)
{
	return scif_rxfill(port);
}

static int d1h_serial_tstc_generic(UART__tstCommonReg *port)
{
	if (port->scfsr.u16word & UART_nRxErrorMask1) {
		handle_error(port);
		return 0;
	}

	return serial_rx_fifo_level(port) ? 1 : 0;
}

static int serial_getc_check(UART__tstCommonReg *port)
{
	u16 status;
	status = port->scfsr.u16word;
	if (status & UART_nRxErrorMask1)
		handle_error(port);
	if (port->sclsr.bits.bi16ORER)
		handle_error(port);
	status &= 0x03;//RDF & DR
	if (status)
		return status;
	return scif_rxfill(port);
}

static int d1h_serial_getc_generic(UART__tstCommonReg *port)
{

	char ch;
	if (!serial_getc_check(port))
		return -EAGAIN;
	return ch;
}


#if CONFIG_IS_ENABLED(DM_SERIAL)

struct d1h_serial_priv {
	UART__tstCommonReg *uart;
};

static int d1h_serial_pending(struct udevice *dev, bool input)
{
	struct d1h_serial_priv *priv = dev_get_priv(dev);

	return d1h_serial_tstc_generic(priv->uart);
}

static int d1h_serial_putc(struct udevice *dev, const char ch)
{
	struct d1h_serial_priv *priv = dev_get_priv(dev);

	return serial_raw_putc(priv->uart, ch);
}

static int d1h_serial_getc(struct udevice *dev)
{
	struct d1h_serial_priv *priv = dev_get_priv(dev);

	return d1h_serial_getc_generic(priv->uart);
}

static int d1h_serial_setbrg(struct udevice *dev, int baudrate)
{
	struct d1h_serial_plat *plat = dev_get_plat(dev);
	struct d1h_serial_priv *priv = dev_get_priv(dev);

	d1h_serial_setbrg_generic(priv->uart, baudrate);

	return 0;
}


static int d1h_serial_probe(struct udevice *dev)
{
	struct d1h_serial_plat *plat = dev_get_plat(dev);
	struct d1h_serial_priv *priv = dev_get_priv(dev);

#if CONFIG_IS_ENABLED(OF_CONTROL)
	fdt_addr_t addr_base;

	addr_base = dev_read_addr(dev);
	if (addr_base == FDT_ADDR_T_NONE)
		return -ENODEV;

	plat->addr_base = (uint32_t)addr_base;
#endif

	priv->uart	= (UART__tstCommonReg *)plat->addr_base;

	d1h_serial_init_generic(priv->uart);

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
	.plat_auto	= sizeof(struct d1h_serial_plat),
	.priv_auto	= sizeof(struct d1h_serial_priv),
	.probe = d1h_serial_probe,
	.ops	= &d1h_serial_ops,
	.flags = DM_FLAG_PRE_RELOC,
};

#else /* CONFIG_DM_SERIAL */


static void d1h_serial_setbrg(void)
{
	DECLARE_GLOBAL_DATA_PTR;
	UART__tstCommonReg *port = (UART__tstCommonReg *)CONFIG_SYS_DEBUG_UART_BASE;

	d1h_serial_setbrg_generic(port, gd->baudrate);
}

static int d1h_serial_init(void)
{
	UART__tstCommonReg *port = (UART__tstCommonReg *)CONFIG_SYS_DEBUG_UART_BASE;
	UART__tstPfcReg *pfc = (UART__tstPfcReg *)PFC_BASE;
	d1h_serial_init_generic(port);
	d1h_scif_initpfc(pfc);
	serial_setbrg();

	return 0;
}

static void d1h_serial_putc(const char c)
{
	UART__tstCommonReg *port = (UART__tstCommonReg *)CONFIG_SYS_DEBUG_UART_BASE;

	if (c == '\n') {
		while (1) {
			if  (serial_raw_putc(port, '\r') != -EAGAIN)
				break;
		}
	}
	while (1) {
		if  (serial_raw_putc(port, c) != -EAGAIN)
			break;
	}
}

static int d1h_serial_tstc(void)
{
	UART__tstCommonReg *port = (UART__tstCommonReg *)CONFIG_SYS_DEBUG_UART_BASE;

	return d1h_serial_tstc_generic(port);
}

static int d1h_serial_getc(void)
{
	UART__tstCommonReg *port = (UART__tstCommonReg *)CONFIG_SYS_DEBUG_UART_BASE;
	int ch;

	while (1) {
		ch = d1h_serial_getc_generic(port);
		if (ch != -EAGAIN)
			break;
	}

	return ch;
}

static struct serial_device d1h_serial_drv = {
	.name	= "d1h_serial",
	.start	= d1h_serial_init,
	.stop	= NULL,
	.setbrg	= d1h_serial_setbrg,
	.putc	= d1h_serial_putc,
	.puts	= default_serial_puts,
	.getc	= d1h_serial_getc,
	.tstc	= d1h_serial_tstc,
};

void d1h_serial_initialize(void)
{
	serial_register(&d1h_serial_drv);
}

__weak struct serial_device *default_serial_console(void)
{
	return &d1h_serial_drv;
}
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
