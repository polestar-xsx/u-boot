/*
 * arch/arm/include/asm/arch-d1h/base.h
 *	This file defines registers.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __ASM_ARCH_D1H_BASE_H
#define __ASM_ARCH_D1H_BASE_H

/*
 * R-Car (R8A7750) I/O Addresses
 */
#define RWDT_BASE		0xE6020000
#define SWDT_BASE		0xE6030000
#define LBSC_BASE		0xEE220200
#define TMU_BASE		0xE61E0000
#define GPIO5_BASE		0xE6055000
/*Counter Module Control and Status Registers*/
#define CNTCR_BASE        0xE6080000

/* SCIF */
#define SCIF0_BASE		0xE6E60000
#define SCIF1_BASE		0xE6E68000
#define SCIF2_BASE		0xE6E88000
#define SCIF3_BASE		0xE6C50000
#define SCIF4_BASE		0xE6C40000
#define SCIF5_BASE		0xE6F30000

/* Module stop status register */
#define MSTPSR0			0xE6150030
#define MSTPSR1			0xE6150038
#define MSTPSR2			0xE6150040
#define MSTPSR3			0xE6150048
#define MSTPSR4			0xE615004C
#define MSTPSR5			0xE615003C
#define MSTPSR6			0xE61501C0
#define MSTPSR7			0xE61501C4
#define MSTPSR8			0xE61509A0
#define MSTPSR9			0xE61509A4
#define MSTPSR10		0xE61509A8
#define MSTPSR11		0xE61509AC

/* Realtime module stop control register */
#define RMSTPCR0		0xE6150110
#define RMSTPCR1		0xE6150114
#define RMSTPCR2		0xE6150118
#define RMSTPCR3		0xE615011C
#define RMSTPCR4		0xE6150120
#define RMSTPCR5		0xE6150124
#define RMSTPCR6		0xE6150128
#define RMSTPCR7		0xE615012C
#define RMSTPCR8		0xE6150980
#define RMSTPCR9		0xE6150984
#define RMSTPCR10		0xE6150988
#define RMSTPCR11		0xE615098C

/* System module stop control register */
#define SMSTPCR0		0xE6150130
#define SMSTPCR1		0xE6150134
#define SMSTPCR2		0xE6150138
#define SMSTPCR3		0xE615013C
#define SMSTPCR4		0xE6150140
#define SMSTPCR5		0xE6150144
#define SMSTPCR6		0xE6150148
#define SMSTPCR7		0xE615014C
#define SMSTPCR8		0xE6150990
#define SMSTPCR9		0xE6150994
#define SMSTPCR10		0xE6150998
#define SMSTPCR11		0xE615099C

/* SH-I2C */
#define CONFIG_SYS_I2C_SH_BASE0	0xE60B0000

/* SDHI */
#define CONFIG_SYS_SH_SDHI0_BASE	0xEE100000
#define CONFIG_SYS_SH_SDHI1_BASE	0xEE120000
#define CONFIG_SYS_SH_SDHI2_BASE	0xEE140000
#define CONFIG_SYS_SH_SDHI3_BASE	0xEE160000

/* PFC */
#define PFC_BASE        0xE6060000
#define GPIO_BASE       0xE6050000
#define PFC_PUEN5       0xE6060414
#define PFC_PUEN6       0xE6060418
#define PUEN_USB0_OVC   (1 <<  0)
#define PUEN_USB0_PWEN  (1 << 31)
#define PUEN_USB1_OVC   (1 <<  2)
#define PUEN_USB1_PWEN  (1 <<  1)
#define PUEN_USB2_OVC   (1 <<  6)
#define PUEN_USB2_PWEN  (1 <<  5)
#define PUEN_USB3_OVC   (1 <<  4)
#define PUEN_USB3_PWEN  (1 <<  3)

/* CLOCK*/
#define CLK__D1H_CLOCK_CTRL       0xE6150000UL
#define CLK__nSRCR4_Addr           0xE61500BCUL   /* Address of Software reset register 4 */
#define CLK__nSRSTCLR4_Addr        0xE6150950UL   /* Address of Software reset clear register 4 */
#define CLK__nDBRSTLCK_Addr        0xE6794000UL   /* Address of DBSC Reset Lock Register */
#define CLK__nDBRST_Addr           0xE6794008UL   /* Address of DBSC RESET Register */

/* SFMA register base address */
#define SFMA_BASE                         0xfec08000UL

#ifndef __ASSEMBLY__
#include <asm/types.h>

/* RWDT */
struct rcar_rwdt {
	u32 rwtcnt;	/* 0x00 : 16 with 16 = 32bit write */
	u32 rwtcsra;	/* 0x04 : 8  with 24 = 32bit write */
	u32 rwtcsrb;	/* 0x08 : 8  with 24 = 32bit write */
};

/* SWDT */
struct rcar_swdt {
	u32 swtcnt;	/* 0x00 : 16 with 16 = 32bit write */
	u32 swtcsra;	/* 0x04 : 8  with 24 = 32bit write */
	u32 swtcsrb;	/* 0x08 : 8  with 24 = 32bit write */
};
#endif

#endif /* __ASM_ARCH_D1H_BASE_H */
