#ifndef __ASM_ARCH_D1H_CLOCK_H_
#define __ASM_ARCH_D1H_CLOCK_H_
#include <asm/types.h>


void clock_init(void);
/*
* Description: Macro to fill the gaps within structures
*/
#define CLK__GAP8(start,finish)     u8   u8__##start##_##finish[(finish)-(start)]
#define CLK__GAP16(start,finish)    u16 u16__##start##_##finish[((finish)-(start))/2]
#define CLK__GAP32(start,finish)    u32 u32__##start##_##finish[((finish)-(start))/4]

/* D1H */
#define CLK__nProtCmdVal           0xA5U          /* register protection unlock command */
#define CLK__nProtCmdVal2          0xA5A55A5AU    /* register protection unlock command 2 */
#define CLK__nCLMAMASK             (u8)0x01U   /* mask for clock monitor enable bits */
#define CLK__nPLL0Locked_Msk       0x00000100UL   /* Status bit of PLL 0 lock */
#define CLK__nPLL1Locked_Msk       0x00000200UL   /* Status bit of PLL 1 lock */
#define CLK__nPLL3Locked_Msk       0x00000800UL   /* Status bit of PLL 3 lock */
#define CLK__nPLLSLocked_Msk       0x00001000UL   /* Status bit of PLL S lock */
#define CLK__nPLLEnable            0x1UL          /* PLL output enable */

#define CLK__nCLMADisable          0x0U           /* disable CLMA */
#define CLK__nCLMAEnable           0x1U           /* enable CLMA */

#define CLK__nClmaPcmdOffset       0x10U          /* OFfset to CLMAn control register 0 */
#define CLK__nClmaPsOffset         0x14U          /* OFfset to CLMAn control register 0 */

#define CLK__nClma_Msk             0x0FFFU        /* Mask for CLMA compare registers */
#define CLK__nZXSel_Msk            0x00000010UL   /* Mask for ZXSEL bit in CKSC_CTL Register */
#define CLK__nDIV_Msk              0x0000003FUL   /* Mask for clock divider */
#define CLK__nDIV_Msk2             0x0000007FUL   /* Mask for clock divider */

#define CLK__nFrqcrbKick_Msk       0x80000000UL   /* Frequency control registers B activation */
#define CLK__nRstn_Msk             0x00100000UL   /* PLL SSCG mode control */
#define CLK__nZ2Sel_Msk            0x00000001UL   /* Mask for Z2 clock selector */
#define CLK__nZ2CkSel0_Msk         0x00000003UL   /* Mask for Z2 clock divider */
#define CLK__nZ2CkSel1_Msk         0x00000030UL   /* Mask for Z2 clock divider */

#define CLK__nReleaseWriteProtect  0x00000001UL   /* Release write protect for LOCOENCR */

/* Needed for changing the multiplication ratio of PLL3 */
#define CLK__nDBSC3_Msk            0x40000000UL   /* Mask for DDR3-SDRAM Memory Controller */
#define CLK__nDisableDbscResetLock 0x0000A55AUL   /* Write this value into DBRSTLCK register to disable the reset lock */


/* Setting for PLL Enable Control Register 
 *   0:PLL disable
 *   1:PLL enable */
#define CLK__nCPG_PLL0_EN_Cfg      0x1UL
#define CLK__nCPG_PLL1_EN_Cfg      0x1UL
#define CLK__nCPG_PLLS_EN_Cfg      0x1UL
#define CLK__nCPG_PLL3_EN_Cfg      0x1UL

/* PLL input clock divider Mr
 * P[1:0] determines the PLL1 input clock divider Mr = P[1:0] + 1.
 *   00b: Mr = 1
 *   01b: Mr = 2
 *   10b: Mr = 3
 *   11b: Mr = 4
*/
#define CLK__nCPG_PLL0_P_Cfg       0x1UL
#define CLK__nCPG_PLL3_P_Cfg       0x1UL

/* PLL0 input clock divider Nr
 * STC[6:0] determines the PLL0 multiply factor Nr = STC[6:0] + 1.
 *   011 1011b: Nr = 60
 *   to
 *   111 0111b: Nr = 120
 *   All others: Setting prohibited
*/
#define CLK__nCPG_PLL0_STC_Cfg     0x69UL   /*PLL0 = 1272MHz*/

/* PLL3 input clock divider Nr
 * STC[6:0] determines the PLL3 multiply factor Nr = STC[6:0] + 1.
 *   101 0111b: Nr = 88,  (with Mr = 2: fPLL3OUT = 1056 MHz)
 *   110 1101b: Nr = 110, (with Mr = 2: fPLL3OUT = 1320 MHz)
 *   All others: Setting prohibited
*/
#if (MEMC_nDDR3RateConfig == MEMC_nDDR3_1333)
#define CLK__nCPG_PLL3_STC_Cfg     0x6DUL
#else
#define CLK__nCPG_PLL3_STC_Cfg     0x57UL
#endif

/* PLL3 Config enable
 *   0: P = 01b
 *   1: P = PLL3CR.P[1:0]
 */
#define CLK__nCPG_PLL3_CfgEN_Cfg   0x1UL

/* PLL SSCG mode control
 *   0: frequency dithering enabled
 *   1: frequency dithering disabled
*/
#define CLK__nCPG_PLL0_RSTN_Cfg    0x1UL
#define CLK__nCPG_PLLS_RSTN_Cfg    0x1UL

/* PLL1 SSCG frequency dithering mode selection
 *   0: center-spread mode
 *   1: down-spread mode
*/
#define CLK__nCPG_PLL0_MODE_Cfg    0x1UL

/* PLLS SSCG frequency dithering mode selection
 *   0: Setting prohibited
 *   1: down-spread mode
*/
#define CLK__nCPG_PLLS_MODE_Cfg    0x1UL   /*do not change*/

/* PLL SSCG modulation frequency control parameter Sr
 * Sr = 2SDIV[1:0]
 *   0x0: Sr = 1
 *   0x1: Sr = 2
 *   0x2: Sr = 4
 *   0x3: Sr = 8
*/
#define CLK__nCPG_PLL0_SDIV_Cfg    0x0UL
#define CLK__nCPG_PLLS_SDIV_Cfg    0x0UL

/* PLL SSCG modulation frequency control parameter Cv
 * Cv = 256 + 16 x TWGCNT[3:0]
 *   0x0: Cv = 256
 *   0x1: Cv = 272
 *   ...
 *   0xE: Cv = 480
 *   0xF: Cv = 496
*/
#define CLK__nCPG_PLL0_TWGCNT_Cfg  0xAUL
#define CLK__nCPG_PLLS_TWGCNT_Cfg  0xAUL

/* PLL SSCG modulation frequency band control
 *   0x0: fMOD > 10 kHz
 *   0x1: fMOD <= 10 kHz
*/
#define CLK__nCPG_PLL0_BANDSET_Cfg 0x0UL
#define CLK__nCPG_PLLS_BANDSET_Cfg 0x0UL

/* PLL SSCG modulation depth control parameter Dp
 *                 | center spread |  down spread  |
 *                 +---------------+---------------+
 *   0x0: Dp = 1   | -0.50% +0.50% |  not defined  |
 *   0x1: Dp = 2   | -1.00% +1.00% | -2.00% +0.00% |
 *   0x2: Dp = 3   | -1.50% +1.50% | -3.00% +0.00% |
 *   0x3: Setting prohibited
*/
#define CLK__nCPG_PLL0_DEPTH_Cfg   0x2UL
#define CLK__nCPG_PLLS_DEPTH_Cfg   0x2UL

/* Debug clock ZTRD2# frequency divider ZTRD2FC
 * Source clock is SYS2# = fPLL1CLK or fPLLSCLK = 1560 MHz
 *   0x5: x 1/12 (130 MHz)
 *   0x6: x 1/16
 *   0x7: x 1/18
 *   0x8: x 1/24 (65 MHz)
 *   Other values: Setting prohibited
*/
/* #define CLK__nCPG_ZTRD2FC_Cfg      0x5UL
 * As per User Manual v0.81, ZTRD2phi clock and its selection bits ZTRD2FC[3:0] were removed from FRQCRB register
*/

/* Debug trace bus clock ZT# frequency divider ZTFC
 * Source clock is SYS5# = fPLL1CLK or fPLLSCLK = 1560 MHz
 *   0xC: x 1/5 (312 MHz)
 *   0x3: x 1/6
 *   0x4: x 1/8
 *   0x5: x 1/12
 *   0x6: x 1/16
 *   0x7: x 1/18
 *   0x8: x 1/24 (65 MHz)
 *   Other values: Setting prohibited
*/
#define CLK__nCPG_ZTFC_Cfg         0xcUL

/* Debug trace port clock ZTR# frequency divider ZTRFC
 * Source clock is SYS2# = fPLL1CLK or fPLLSCLK = 1560 MHz
 *   0x3: x 1/6 (260 MHz)
 *   0x4: x 1/8
 *   0x5: x 1/12
 *   0x6: x 1/16
 *   0x7: x 1/18
 *   0x8: x 1/24 (65 MHz)
 *   Other values: Setting prohibited
*/
#define CLK__nCPG_ZTRFC_Cfg        0x3UL

/* Output control
 *   0: active
 *   1: stopped
*/
#define CLK__nCPG_MMC0_CKSTP_Cfg   0x0UL
#define CLK__nCPG_RCAN_CKSTP_Cfg   0x0UL
#define CLK__nCPG_USBCK_CKSTP_Cfg  0x0UL
#define CLK__nCPG_Z2D_CKSTP_Cfg    0x0UL
#define CLK__nCPG_Z3D_CKSTP_Cfg    0x0UL
#define CLK__nCPG_PIX1_CKSTP_Cfg   0x0UL
#define CLK__nCPG_PIX2_CKSTP_Cfg   0x0UL
#define CLK__nCPG_PIX3B_CKSTP_Cfg  0x0UL
#define CLK__nCPG_PIX4B_CKSTP_Cfg  0x0UL
#define CLK__nCPG_TPU_CKSTP_Cfg    0x0UL
#define CLK__nCPG_TMU_CKSTP_Cfg    0x0UL
#define CLK__nCPG_CMT_CKSTP_Cfg    0x0UL
#define CLK__nCPG_SFMA_CKSTP_Cfg   0x0UL


/* SYS2# clock divider for the MMC0# clock
 * MMC0# = SYS2#/2 x 1/(DIV[5:0] + 1) = 780 MHz x 1/(DIV[5:0] + 1)
 *   0x07: x 1/8 (97.5 MHz)
 *   0x08: x 1/9 (86.67 MHz)
 *   ...
 *   0x3F: x 1/64 (12.1875 MHz)
 *   All others: Setting prohibited
*/
#define CLK__nCPG_MMC0_DIV_Cfg     0x3FUL

/* RCAN# clock selector RCAN_CKSEL
 *   0: RCAN# = fX = 24 MHz
 *   1: RCAN# = fX/6 = 4 MHz
*/
#define CLK__nCPG_RCAN_CKSEL_Cfg   0x0UL

/*Z2# clock selector CKSC_Z2CK_CTL
 *  0: Z2# = fPLL1CLK/n0 (non-SSCG)
 *  1: Z2# = fPLLSCLK/n1 (SSCG)
 *  n0 is determined by CKSCCR2.Z2SEL0.
 *  n1 is determined by CKSCCR2.Z2SEL1.
*/
#define CLK__nCPG_Z2SEL_Cfg        0x1UL

/* SYS3# clock selector CKSC_ZXCK_CTL
 *   0: SYS3# = fPLL1CLK/3 (520 MHz, non-SSCG)
 *   1: SYS3# = fPLLSCLK/3 (520 MHz, SSCG)
*/
#define CLK__nCPG_ZXSEL_Cfg        0x0UL

/* SYS5# clock selector CKSC_ZTCK_CTL
 *   0: SYS5# = fPLL1CLK/5 (312 MHz, non-SSCG)
 *   1: SYS5# = fPLLSCLK/5 (312 MHz, SSCG)
*/
#define CLK__nCPG_ZTSEL_Cfg        0x1UL

/* SYS2# clock selector CKSC_SYSCK_CTL
 *   0: SYS2# = fPLL1CLK/2 (780 MHz, non-SSCG)
 *   1: SYS2# = fPLLSCLK/2 (780 MHz, SSCG)
*/
#define CLK__nCPG_SYSSEL_Cfg       0x1UL

/* fPLL1CLK clock divider CKSC_Z2CK0_CTL for the Z2# clock
 * if non-SSCG clock is selected for Z2#(CKSCCR.Z2SEL = 0)
 *   0x0: Z2# = fPLL1CLK x 1/2 (780 MHz)
 *   0x1: Z2# = fPLL1CLK x 1/3 (520 MHz)
 *   0x2: Z2# = fPLL1CLK x 11/26 (660 MHz)
 *   0x3: Z2# = fPLL1CLK x 1/6 (260 MHz)
*/
#define CLK__nCPG_Z2CKSEL0_Cfg     0x0UL

/* fPLLSCLK clock divider CKSC_Z2CK1_CTL for the Z2# clock,
 * if SSCG clock is selected for Z2#(CKSCCR.Z2SEL = 1)
 *   0x0: Z2# = fPLLSCLK x 1/2 (780 MHz)   - only D1H2
 *   0x1: Z2# = fPLLSCLK x 1/3 (520 MHz)   - initial value
 *   0x2: Z2# = fPLLSCLK x 11/26 (660 MHz) - D1H1 up to 660MHz
 *   0x3: Z2# = fPLLSCLK x 1/6 (260 MHz)
*/
#define CLK__nCPG_Z2CKSEL1_Cfg     0x0UL

/* Z2D#/Z3D# clock selector CKSC_Z2DCLK_CTL
 *   1xxxb: ZnD# = fPLL3CLK / 4
 *   00x0b: ZnD# = fPLL1CLK / 5 (312 MHz non-SSCG) - only D1H2? 330MHz?
 *   00x1b: ZnD# = fPLL1CLK / 6 (260 MHz non-SSCG)
 *   010xb: ZnD# = fPLLSCLK / 5 (312 MHz SSCG)     - only D1H2? 330MHz?
 *   011xb: ZnD# = fPLLSCLK / 6 (260 MHz SSCG)
*/
#define CLK__nCPG_Z2D_CKSEL_Cfg    0x8UL
#define CLK__nCPG_Z3D_CKSEL_Cfg    0x8UL

/* PIX1# clock selector CKSC_PIX1_CTL
 *   0: PIX1# = fPLL0CLK, only allowed if PLL0 <= 875MHz
 *   1: PIX1# = fPLL0CLK / n = PIX1ACLK
 *   n is determined by PIX1CLKCR.DIV[5:0].
*/
#define CLK__nCPG_PIX1_CKSEL_Cfg   0x1UL

/* PIX2# clock selection
 *   0x0: PIX2# = fPLL1CLK x 1/n1 = PIX2ACLK
 *   0x1: PIX2# = fPLLSCLK x 1/nS = PIX2BCLK
 *   0x2: PIX2# = fPLL0CLK x 1/n0 = PIX2CCLK
 *   0x3: PIX2# = fPLL3CLK x 1/n3 = PIX2DCLK
 *   CAUTION
 *   The frequency of PIX2# must not exceed 75 MHz
 *   n0 is determined by PIX2CLKCR.DIV[5:0].
 *   n1 is determined by PIX2ACLKCR.DIV[5:0].
 *   nS is determined by PIX2BCLKCR.DIV[5:0].
 *   n3 is determined by PIX2DCLKCR.DIV[5:0].
*/
#define CLK__nCPG_PIX2_EXSCR_Cfg   0x1UL   /*use jittered clock for RSDS*/

/* fPLL0CLK clock divider CKSC_PIX1_CTL for the PIX1ACLK clock
 * PIX1ACLK = fPLL0CLK = 1/(DIV[5:0] + 1)
 *   0x00: setting prohibited
 *   0x01: PIX1ACLK = fPLL0CLK x 1/2
 *   0x02: PIX1ACLK = fPLL0CLK x 1/3
 *   ...
 *   0x3E: PIX1ACLK = fPLL0CLK x 1/63
 *   0x3F: PIX1ACLK = fPLL0CLK x 1/64
*/
#define CLK__nCPG_PIX1_DIV_Cfg     0x02UL
#define CLK__nCPG_PIX2_DIV_Cfg     0x1FUL

/* fPLL1CLK clock divider CKSC_PIX2A_CTL for the PIX2ACLK clock
 *   PIX2ACLK = fPLL1CLK = 1/(DIV[6:0] + 1) = 1560 MHz x 1/(DIV[6:0] + 1)
 *   0x03: PIX2ACLK = fPLL1CLK x 1/4 (390 MHz)
 *   0x04: PIX2ACLK = fPLL1CLK x 1/5 (312 MHz)
 *   ...
 *   0x7F: PIX2ACLK = fPLL1CLK x 1/128 (12.1875 MHz)
 *   All others: setting prohibited
*/
#define CLK__nCPG_PIX2A_DIV_Cfg    0x7FUL

/* fPLLSCLK clock divider CKSC_PIX2B_CTL for the PIX2BCLK clock
 *   PIX2BCLK = fPLLSCLK x 1/(DIV[6:0] + 1) = 1560 MHz x 1/(DIV[6:0] + 1)
 *   0x03: PIX2BCLK = fPLLSCLK x 1/4 (390 MHz)
 *   0x04: PIX2BCLK = fPLLSCLK x 1/5 (312 MHz)
 *   ...
 *   0x7F: PIX2BCLK = fPLLSCLK x 1/128 (12.1875 MHz)
 *   All others: setting prohibited
*/
#define CLK__nCPG_PIX2B_DIV_Cfg    0x7FUL

/* fPLL3CLK clock divider CKSC_PIX2B_CTL for the PIX2DCLK clock
 *   PIX2DCLK = fPLL3CLK x 1/(DIV[6:0] + 1)
 *   0x03: PIX2DCLK = fPLL3CLK x 1/4
 *   0x04: PIX2DCLK = fPLL3CLK x 1/5
 *   ...
 *   0x7F: PIX2DCLK = fPLL3CLK x 1/128
 *   All others: setting prohibited
*/
#define CLK__nCPG_PIX2D_DIV_Cfg    0x7FUL

/* fPLLSCLK clock divider CKSC_PIX3A_CTL for the PIX3ACLK clock
 *   PIX3ACLK = fPLLSCLK x 1/(DIV[5:0] + 1) = 1560 MHz x 1/(DIV[5:0] + 1)
 *   0x03: PIX3ACLK = fPLLSCLK x 1/4 (390 MHz)
 *   0x04: PIX3ACLK = fPLLSCLK x 1/5 (312 MHz)
 *   ...
 *   0x3F: PIX3ACLK = fPLLSCLK x 1/64 (24.375 MHz)
 *   All others: setting prohibited
*/
#define CLK__nCPG_PIX3A_DIV_Cfg    0x3FUL

/* PIX3ACLK clock divider CKSC_PIX3B_CTL for the PIX3? clock
 *   PIX3# = PIX3ACLK x 1/(DIV[5:0] + 1)
 *   0x01: PIX3# = PIX3ACLK x 1/2
 *   0x02: PIX3# = PIX3ACLK x 1/3
 *   0x03: PIX3# = PIX3ACLK x 1/4
 *   0x04: PIX3# = PIX3ACLK x 1/5
 *   ...
 *   0x3F: PIX3# = PIX3ACLK x 1/64
 *   All others: setting prohibited
 *   CAUTION
 *   The frequency of PIX3# must not exceed 66 MHz.
*/
#define CLK__nCPG_PIX3B_DIV_Cfg    0x3FUL

/* fPLLSCLK clock divider CKSC_PIX4A_CTL for the PIX4ACLK clock
 *   PIX4ACLK = fPLLSCLK x 1/(DIV[5:0] + 1) = 1560 MHz x 1/(DIV[5:0] + 1)
 *   0x03: PIX4ACLK = fPLLSCLK x 1/4 (390 MHz)
 *   0x04: PIX4ACLK = fPLLSCLK x 1/5 (312 MHz)
 *   ...
 *   0x3F: PIX4ACLK = fPLLSCLK x 1/64 (24.375 MHz)
 *   All others: setting prohibited
*/
#define CLK__nCPG_PIX4A_DIV_Cfg    0x3FUL

/* PIX4ACLK clock divider CKSC_PIX4B_CTL for the PIX4? clock
 *   PIX4# = PIX4ACLK x 1/(DIV[5:0] + 1)
 *   0x03: PIX4# = PIX4ACLK x 1/4
 *   0x04: PIX4# = PIX4ACLK x 1/5
 *   ...
 *   0x3F: PIX4# = PIX4ACLK x 1/64
 *   All others: setting prohibited
 *   CAUTION
 *   The frequency of PIX4# must not exceed 66 MHz.
*/
#define CLK__nCPG_PIX4B_DIV_Cfg    0x3FUL

/* TPU#/TMU# clock source selection
 *   0: fPLL1CLK x 1/48 clock selection (32.5 MHz, non-SSCG)
 *   1: fPLLSCLK x 1/48 clock selection (32.5 MHz, SSCG)
*/
#define CLK__nCPG_TPU_EXSRC_Cfg    0x1UL
#define CLK__nCPG_TMU_EXSRC_Cfg    0x1UL
#define CLK__nCPG_CMT_EXSRC_Cfg    0x1UL

/* SFMA# clock source selector CKSC_SFMA_CTL
 *   0x0: SYS3# x 1/2 selection (260 MHz)
 *   0x1: SYS3# x 1/3 selection (173 MHz)
 *   0x2: SYS3# x 1/4 selection (130 MHz)
 *   0x3: SYS3# x 1/6 selection (87 MHz)
*/
#define CLK__nCPG_SFMA_EXSRC_Cfg   0x1UL

/* Enable IntOsc_ENABLE_Control Register
 *   0: this register disable
 *   1: this register enable
*/
#define CLK__nCPG_INTOSC_RENB_Cfg  0x1UL

/* LOCO output enable
 *   0: output disable
 *   1: output enable
*/
#define CLK__nCPG_INTOSC_LOEN_Cfg  0x1UL


/* Module stop control registers settings
 *   1: Halt the clock to the module.
 *   0: Supply the clock to the module.
*/
#define CLK__nMSTP_MSIOF0_Cfg      0x0UL  /* Synchronous Serial I/F.        Clock stopped: ZMP# */
#define CLK__nMSTP_MSIOF1_Cfg      0x0UL  /* Synchronous Serial I/F.        Clock stopped: ZMP# */
#define CLK__nMSTP_MSIOF2_Cfg      0x0UL  /* Synchronous Serial I/F.        Clock stopped: ZMP# */
#define CLK__nMSTP_MSIOF3_Cfg      0x0UL  /* Synchronous Serial I/F.        Clock stopped: ZMP# */
#define CLK__nMSTP_MSIOF4_Cfg      0x0UL  /* Synchronous Serial I/F.        Clock stopped: ZMP# */
#define CLK__nMSTP_MSIOF5_Cfg      0x1UL  /* Synchronous Serial I/F.        Clock stopped: ZMP# */
#define CLK__nMSTP_MSIOF6_Cfg      0x1UL  /* Synchronous Serial I/F.        Clock stopped: ZMP# */
#define CLK__nMSTP_VPC_Cfg         0x1UL  /* Video Processing Unit Cache.   Clock stopped: HP# */
#define CLK__nMSTP_STBE_Cfg        0x1UL  /* Ethernet AVB Stream Buffer.    Clock stopped: HP# */
#define CLK__nMSTP_ADG_Cfg         0x1UL  /* Serial Sound I/F (SSIF) Audio Clock Generator. Clock stopped: M2# */
#define CLK__nMSTP_GPU3D_Cfg       0x1UL  /* 3D Graphics Processing Unit.   Clock stopped: Z3D# */
#define CLK__nMSTP_VDP1C_Cfg       0x1UL  /* Video Decoding Processor.      Clock stopped: ZS# */
#define CLK__nMSTP_TMU0_0_Cfg      0x1UL  /* 32-bit Timer Unit (timer 0).   Clock stopped: TMU# */
#define CLK__nMSTP_TMU0_1_Cfg      0x1UL  /* 32-bit Timer Unit (timer 1).   Clock stopped: TMU# */
#define CLK__nMSTP_TMU0_2_Cfg      0x1UL  /* 32-bit Timer Unit (timer 2).   Clock stopped: TMU# */
#define CLK__nMSTP_TMU0_3_Cfg      0x1UL  /* 32-bit Timer Unit (timer 3).   Clock stopped: TMU# */
#define CLK__nMSTP_VSPD0_Cfg       0x1UL  /* Video Signal Processor.        Clock stopped: ZS# */
#define CLK__nMSTP_VSPD1_Cfg       0x1UL  /* Video Signal Processor.        Clock stopped: ZS# */

#define CLK__nMSTP_SYS_DMAC0_Cfg   0x0UL  /* DMA Controller.                Clock stopped: ZS#, HP# */
#define CLK__nMSTP_SYS_DMAC1_Cfg   0x0UL  /* DMA Controller.                Clock stopped: ZS#, HP# */
#define CLK__nMSTP_TPU0_Cfg        0x1UL  /* 16-Bit Timer Pulse Unit.       Clock stopped: TPU# */
#define CLK__nMSTP_TPU1_Cfg        0x1UL  /* 16-Bit Timer Pulse Unit.       Clock stopped: TPU# */
#define CLK__nMSTP_TPU2_Cfg        0x1UL  /* 16-Bit Timer Pulse Unit.       Clock stopped: TPU# */
#define CLK__nMSTP_TPU3_Cfg        0x1UL  /* 16-Bit Timer Pulse Unit.       Clock stopped: TPU# */
#define CLK__nMSTP_MMC0_Cfg        0x1UL  /* Multi Media Card Interface.    Clock stopped: MMC0# */
#define CLK__nMSTP_CMT10_Cfg       0x1UL  /* Compare Match Timer 1.         Clock stopped: CMT# */
#define CLK__nMSTP_USB_DMAC0_Cfg   0x1UL  /* USB Function DMA Controller.   Clock stopped: ZS# */
#define CLK__nMSTP_USB_DMAC1_Cfg   0x1UL  /* USB Function DMA Controller.   Clock stopped: ZS# */
#define CLK__nMSTP_RWDT0_Cfg       0x0UL  /* Watchdog Time.                 Clock stopped: R#, CP# */
#define CLK__nMSTP_DMAC_Cfg        0x0UL  /* USB Descriptor.                Clock stopped: ZS#, HP# */
#define CLK__nMSTP_IRQC_Cfg        0x0UL  /* External Interrupt controller. Clock stopped: R#, CP# */
#define CLK__nMSTP_INTC_SYS_Cfg    0x0UL  /* Interrupt Controller.          Clock stopped: ZS# */
#define CLK__nMSTP_S3CTRL_Cfg      0x0UL  /* S3 Cache Controller.           Clock stopped: ZS#, HP# */
#define CLK__nMSTP_CLMA_Cfg        0x1UL  /* Clock Monitors.                Clock stopped: HP#, OSCD2#, osc125k */

#define CLK__nMSTP_CMREG_Cfg       0x1UL  /* Common Registers.              Clock stopped: LB#, OSCD2#, HP#, P# */
#define CLK__nMSTP_ECM_Cfg         0x0UL  /* Error Control Module */
#define CLK__nMSTP_PCMP0_Cfg       0x1UL  /* PCM-PWM Converter.             Clock stopped: P# */
#define CLK__nMSTP_NFMA0_Cfg       0x1UL  /* NAND Flash Memory Interface A. Clock stopped: HP#, CS# */
#define CLK__nMSTP_USBHC_Cfg       0x1UL  /* USB 2.0 Host Controller.       Clock stopped: USB# */
#define CLK__nMSTP_USBFC_Cfg       0x1UL  /* USB 2.0 Function Controller.   Clock stopped: USB# */
#define CLK__nMSTP_VOCA0_Cfg       0x1UL  /* Video Output Checker.          Clock stopped: HP#, R200k# */
#define CLK__nMSTP_RSDS_IF_Cfg     0x1UL  /* Video Output.                  Clock stopped: PIX2# */
#define CLK__nMSTP_SFMA0_Cfg       0x0UL  /* Serial Flash Memory Interface. Clock stopped: SFMA# */
#define CLK__nMSTP_HSCIF0_Cfg      0x1UL  /* Asynchronous High Speed Serial Communication I/F. Clock stopped: S# */
#define CLK__nMSTP_HSCIF1_Cfg      0x1UL  /* Asynchronous High Speed Serial Communication I/F. Clock stopped: S# */
#define CLK__nMSTP_SCIF0_Cfg       0x0UL  /* Asynchronous/synchronous Serial Communication I/F. Clock stopped: P#, S# */
#define CLK__nMSTP_SCIF1_Cfg       0x0UL  /* Asynchronous/synchronous Serial Communication I/F. Clock stopped: P#, S# */
#define CLK__nMSTP_SCIF2_Cfg       0x0UL  /* Asynchronous/synchronous Serial Communication I/F. Clock stopped: P#, S# */
#define CLK__nMSTP_SCIF3_Cfg       0x0UL  /* Asynchronous/synchronous Serial Communication I/F. Clock stopped: P#, S# */
#define CLK__nMSTP_DU0_Cfg         0x1UL  /* Display Unit.                  Clock stopped: PIX4# */
#define CLK__nMSTP_DU1_Cfg         0x1UL  /* Display Unit.                  Clock stopped: PIX4# */
#define CLK__nMSTP_DU2_Cfg         0x1UL  /* Display Unit.                  Clock stopped: PIX4# */
#define CLK__nMSTP_LVDS_IF_Cfg     0x1UL  /* Video Output.                  Clock stopped: HP# */
#define CLK__nMSTP_DISCOM0_Cfg     0x1UL  /* Display Output Comparator.     Clock stopped: ZS#, HP# */
#define CLK__nMSTP_DISCOM1_Cfg     0x1UL  /* Display Output Comparator.     Clock stopped: ZS#, HP# */
#define CLK__nMSTP_DISCOM2_Cfg     0x1UL  /* Display Output Comparator.     Clock stopped: ZS#, HP# */
#define CLK__nMSTP_DISCOM3_Cfg     0x1UL  /* Display Output Comparator.     Clock stopped: ZS#, HP# */
#define CLK__nMSTP_TCON0_Cfg       0x1UL  /* Timing Controller.             Clock stopped: ZS#, HP# */

#define CLK__nMSTP_IPMMUGP_Cfg     0x0UL  /* IP Memory Management Unit.     Clock stopped: S#, B# */
#define CLK__nMSTP_MLBB0_Cfg       0x1UL  /* Media Local Bus I/F.           Clock stopped: HP# */
#define CLK__nMSTP_MIPI_IF_Cfg     0x0UL  /* Video Input MIPI I/F module.   Clock stopped: ZU#, ZUD2#, HP#, MP# */
#define CLK__nMSTP_GPU2D_Cfg       0x1UL  /* 2D Graphics Processing Unit.   Clock stopped: Z2D# */
#define CLK__nMSTP_VIN0_Cfg        0x1UL  /* Video Input Module.            Clock stopped: ZS#, LB# */
#define CLK__nMSTP_VIN1_Cfg        0x1UL  /* Video Input Module.            Clock stopped: ZS#, LB# */
#define CLK__nMSTP_ETNB0_Cfg       0x1UL  /* Ethernet AVB MAC.              Clock stopped: HP#, AVB_TX_CLK */
#define CLK__nMSTP_GPIO0_Cfg       0x0UL  /* GPIO block.                    Clock stopped: CP# */
#define CLK__nMSTP_GPIO1_Cfg       0x0UL  /* GPIO block.                    Clock stopped: CP# */
#define CLK__nMSTP_GPIO2_Cfg       0x0UL  /* GPIO block.                    Clock stopped: CP# */
#define CLK__nMSTP_GPIO3_Cfg       0x0UL  /* GPIO block.                    Clock stopped: CP# */
#define CLK__nMSTP_GPIO4_Cfg       0x0UL  /* GPIO block.                    Clock stopped: CP# */
#define CLK__nMSTP_RS_CANFD_Cfg    0x1UL  /* CANFD I/F.                     Clock stopped: LB#, CAN30#, RCAN# */
#define CLK__nMSTP_I2C0_Cfg        0x0UL  /* I2C Bus I/F .                  Clock stopped: HP# */
#define CLK__nMSTP_I2C1_Cfg        0x0UL  /* I2C Bus I/F .                  Clock stopped: HP# */
#define CLK__nMSTP_DNFA0_Cfg       0x0UL  /* Digital Noise Filter.          Clock stopped: LB# */
#define CLK__nMSTP_SSIF0_Cfg       0x1UL  /* Serial Sound I/F module.       Clock stopped: HP# */
#define CLK__nMSTP_SSIF1_Cfg       0x1UL  /* Serial Sound I/F module.       Clock stopped: HP# */
#define CLK__nMSTP_DCRA0_Cfg       0x0UL  /* Data CRC.                      Clock stopped: HP# */


/* D1H */
/* PLL Enable Control Register */
#define CLK__nCPG_PLLECR_Cfg         ((CLK__nCPG_PLLS_EN_Cfg      << 4U)  \
                                     | (CLK__nCPG_PLL3_EN_Cfg      << 3U)  \
                                     | (CLK__nCPG_PLL1_EN_Cfg      << 1U)  \
                                     | (CLK__nCPG_PLL0_EN_Cfg      << 0U))

/* PLL0 control register */
#define CLK__nCPG_PLL0CR_Cfg         ((CLK__nCPG_PLL0_STC_Cfg     << 24U)  \
                                     | (CLK__nCPG_PLL0_P_Cfg       << 20U))

/* PLL3 control register */
#define CLK__nCPG_PLL3CR_Cfg         ((CLK__nCPG_PLL3_CfgEN_Cfg   << 31U)  \
                                     | (CLK__nCPG_PLL3_STC_Cfg     << 24U)  \
                                     | (CLK__nCPG_PLL3_P_Cfg       << 20U))

/* PLL0 control register 1 */
#define CLK__nCPG_PLL0CR1_Cfg        ((CLK__nCPG_PLL0_DEPTH_Cfg   << 29U)  \
                                     | (CLK__nCPG_PLL0_BANDSET_Cfg << 28U)  \
                                     | (CLK__nCPG_PLL0_TWGCNT_Cfg  << 24U)  \
                                     | (CLK__nCPG_PLL0_SDIV_Cfg    << 22U)  \
                                     | (CLK__nCPG_PLL0_MODE_Cfg    << 21U)  \
                                     | (CLK__nCPG_PLL0_RSTN_Cfg    << 20U))

/* PLLS control register 1 */
#define CLK__nCPG_PLLSCR1_Cfg        ((CLK__nCPG_PLLS_DEPTH_Cfg   << 29U)  \
                                     | (CLK__nCPG_PLLS_BANDSET_Cfg << 28U)  \
                                     | (CLK__nCPG_PLLS_TWGCNT_Cfg  << 24U)  \
                                     | (CLK__nCPG_PLLS_SDIV_Cfg    << 22U)  \
                                     | (CLK__nCPG_PLLS_MODE_Cfg    << 21U)  \
                                     | (CLK__nCPG_PLLS_RSTN_Cfg    << 20U))

/* Frequency control register B */
#define CLK__nCPG_FRQCRB_Cfg         ((CLK__nCPG_ZTRFC_Cfg        << 20U)  \
                                     | (CLK__nCPG_ZTFC_Cfg         << 16U) | 0x00001355UL)

/* MMC0 clock frequency control register */
#define CLK__nCPG_MMC0CKCR_Cfg       ((CLK__nCPG_MMC0_CKSTP_Cfg   <<  8U)  \
                                     | (CLK__nCPG_MMC0_DIV_Cfg     <<  0U))

/* RCAN clock frequency control register */
#define CLK__nCPG_RCANCKCR_Cfg       ((CLK__nCPG_RCAN_CKSTP_Cfg   <<  8U)  \
                                     | (CLK__nCPG_RCAN_CKSEL_Cfg   <<  0U))

/* CKSC_CTL Register */
#define CLK__nCPG_CKSCCR_Cfg         ((CLK__nCPG_SYSSEL_Cfg       << 12U)  \
                                     | (CLK__nCPG_ZTSEL_Cfg        <<  8U)  \
                                     | (CLK__nCPG_ZXSEL_Cfg        <<  4U)  \
                                     | (CLK__nCPG_Z2SEL_Cfg        <<  0U))

/* CKSC_Z2CK_CTL Register */
#define CLK__nCPG_CKSCCR2_Cfg        ((CLK__nCPG_Z2CKSEL1_Cfg     <<  4U)  \
                                     | (CLK__nCPG_Z2CKSEL0_Cfg     <<  0U))

/* CKSC_USBCLK_CTL Register */
#define CLK__nCPG_USBCLKCR_Cfg       ((CLK__nCPG_USBCK_CKSTP_Cfg  <<  8U) | 0x1FUL)

/* CKSC_Z2DCLK_CTL Register */
#define CLK__nCPG_Z2DCLKCR_Cfg       ((CLK__nCPG_Z2D_CKSEL_Cfg    << 10U)  \
                                     | (CLK__nCPG_Z2D_CKSTP_Cfg    <<  8U))

/* CKSC_Z3DCLK_CTL Register */
#define CLK__nCPG_Z3DCLKCR_Cfg       ((CLK__nCPG_Z3D_CKSEL_Cfg    << 10U)  \
                                     | (CLK__nCPG_Z3D_CKSTP_Cfg    <<  8U))

/* CKSC_PIX1_CTL Register */
#define CLK__nCPG_PIX1CLKCR_Cfg      ((CLK__nCPG_PIX1_CKSTP_Cfg   <<  8U)  \
                                     | (CLK__nCPG_PIX1_CKSEL_Cfg   <<  6U)  \
                                     | (CLK__nCPG_PIX1_DIV_Cfg     <<  0U))

/* CKSC_PIX2_CTL Register */
#define CLK__nCPG_PIX2CLKCR_Cfg      ((CLK__nCPG_PIX2_CKSTP_Cfg   <<  9U)  \
                                     | (CLK__nCPG_PIX2_EXSCR_Cfg   <<  6U)  \
                                     | (CLK__nCPG_PIX2_DIV_Cfg     <<  0U))

/* CKSC_PIX2A_CTL Register */
#define CLK__nCPG_PIX2ACLKCR_Cfg      (CLK__nCPG_PIX2A_DIV_Cfg)

/* CKSC_PIX2B_CTL Register */
#define CLK__nCPG_PIX2BCLKCR_Cfg      (CLK__nCPG_PIX2B_DIV_Cfg)

/* CKSC_PIX2D_CTL Register */
#define CLK__nCPG_PIX2DCLKCR_Cfg      (CLK__nCPG_PIX2D_DIV_Cfg)

/* CKSC_PIX3A_CTL Register */
#define CLK__nCPG_PIX3ACLKCR_Cfg      (CLK__nCPG_PIX3A_DIV_Cfg)

/* CKSC_PIX3_CTL Register */
#define CLK__nCPG_PIX3CLKCR_Cfg      ((CLK__nCPG_PIX3B_CKSTP_Cfg  <<  8U)  \
                                     | (CLK__nCPG_PIX3B_DIV_Cfg    <<  0U))

/* CKSC_PIX4A_CTL Register */
#define CLK__nCPG_PIX4ACLKCR_Cfg      (CLK__nCPG_PIX4A_DIV_Cfg)

/* CKSC_PIX4_CTL Register */
#define CLK__nCPG_PIX4CLKCR_Cfg      ((CLK__nCPG_PIX4B_CKSTP_Cfg  <<  8U)  \
                                     | (CLK__nCPG_PIX4B_DIV_Cfg    <<  0U))

/* CKSC_TPUCLK_Control Register */
#define CLK__nCPG_TPUCLKCR_Cfg       ((CLK__nCPG_TPU_CKSTP_Cfg    <<  8U)  \
                                     | (CLK__nCPG_TPU_EXSRC_Cfg    <<  6U))

/* CKSC_TMUCLK_Control Register */
#define CLK__nCPG_TMUCLKCR_Cfg       ((CLK__nCPG_TMU_CKSTP_Cfg    <<  8U)  \
                                     | (CLK__nCPG_TMU_EXSRC_Cfg    <<  6U))

/* CKSC_CMTCLK_Control Register */
#define CLK__nCPG_CMTCLKCR_Cfg       ((CLK__nCPG_CMT_CKSTP_Cfg    <<  8U)  \
                                     | (CLK__nCPG_CMT_EXSRC_Cfg    <<  6U))

/* CKSC_SFMACLK_Control Register */
#define CLK__nCPG_SFMACLKCR_Cfg      ((CLK__nCPG_SFMA_CKSTP_Cfg   <<  8U)  \
                                     | (CLK__nCPG_SFMA_EXSRC_Cfg   <<  6U))

/* IntOsc Enable Control Register */
#define CLK__nCPG_INTOSCENCR_Cfg     ((CLK__nCPG_INTOSC_LOEN_Cfg  << 18U)  \
                                     | (CLK__nCPG_INTOSC_RENB_Cfg  <<  0U))


/* System module stop control register 0 */
#define CLK__nMSBC_SMSTPCR0_Cfg       (CLK__nMSTP_MSIOF0_Cfg)

/* System module stop control register 1 */
#define CLK__nMSBC_SMSTPCR1_Cfg      ((CLK__nMSTP_VSPD0_Cfg       << 28U)  \
                                     | (CLK__nMSTP_VSPD1_Cfg       << 27U)  \
                                     | (CLK__nMSTP_TMU0_0_Cfg      << 25U)  \
                                     | (CLK__nMSTP_TMU0_2_Cfg      << 22U)  \
                                     | (CLK__nMSTP_TMU0_3_Cfg      << 21U)  \
                                     | (CLK__nMSTP_VDP1C_Cfg       << 19U)  \
                                     | (CLK__nMSTP_GPU3D_Cfg       << 12U)  \
                                     | (CLK__nMSTP_TMU0_1_Cfg      << 11U)  \
                                     | (CLK__nMSTP_ADG_Cfg         <<  6U)  \
                                     | (CLK__nMSTP_STBE_Cfg        <<  4U)  \
                                     | (CLK__nMSTP_VPC_Cfg         <<  3U) | 0xE597E7A7UL)

/* System module stop control register 2 */
#define CLK__nMSBC_SMSTPCR2_Cfg      ((CLK__nMSTP_SYS_DMAC0_Cfg   << 19U)  \
                                     | (CLK__nMSTP_SYS_DMAC1_Cfg   << 18U)  \
                                     | (CLK__nMSTP_MSIOF3_Cfg      << 15U)  \
                                     | (CLK__nMSTP_MSIOF4_Cfg      << 14U)  \
                                     | (CLK__nMSTP_MSIOF1_Cfg      <<  8U)  \
                                     | (CLK__nMSTP_MSIOF2_Cfg      <<  5U))

/* System module stop control register 3 */
#define CLK__nMSBC_SMSTPCR3_Cfg      ((CLK__nMSTP_USB_DMAC1_Cfg   << 31U)  \
                                     | (CLK__nMSTP_USB_DMAC0_Cfg   << 30U)  \
                                     | (CLK__nMSTP_CMT10_Cfg       << 29U)  \
                                     | (CLK__nMSTP_MMC0_Cfg        << 15U)  \
                                     | (CLK__nMSTP_TPU0_Cfg        <<  4U) | 0x1FFF7FEFUL)

/* System module stop control register 4 */
#define CLK__nMSBC_SMSTPCR4_Cfg      ((CLK__nMSTP_S3CTRL_Cfg      << 23U)  \
                                     | (CLK__nMSTP_INTC_SYS_Cfg    <<  8U)  \
                                     | (CLK__nMSTP_IRQC_Cfg        <<  7U)  \
                                     | (CLK__nMSTP_DMAC_Cfg        <<  6U)  \
                                     | (CLK__nMSTP_RWDT0_Cfg       <<  2U))

/* System module stop control register 5 */
#define CLK__nMSBC_SMSTPCR5_Cfg      ((CLK__nMSTP_NFMA0_Cfg       << 24U)  \
                                     | (CLK__nMSTP_PCMP0_Cfg       << 23U)  \
                                     | (CLK__nMSTP_ECM_Cfg         << 13U)  \
                                     | (CLK__nMSTP_CMREG_Cfg       << 12U)  \
                                     | (CLK__nMSTP_CLMA_Cfg        <<  0U) | 0x82608FFEUL)

/* System module stop control register 6 */
#define CLK__nMSBC_SMSTPCR6_Cfg      ((CLK__nMSTP_MSIOF6_Cfg      << 23U)  \
                                     | (CLK__nMSTP_MSIOF5_Cfg      << 22U)  \
                                     | (CLK__nMSTP_TPU3_Cfg        <<  3U)  \
                                     | (CLK__nMSTP_TPU2_Cfg        <<  2U)  \
                                     | (CLK__nMSTP_TPU1_Cfg        <<  1U) | 0xCF3FFFF1UL)

/* System module stop control register 7 */
#define CLK__nMSBC_SMSTPCR7_Cfg      ((CLK__nMSTP_DISCOM0_Cfg     << 31U)  \
                                     | (CLK__nMSTP_DISCOM1_Cfg     << 30U)  \
                                     | (CLK__nMSTP_TCON0_Cfg       << 29U)  \
                                     | (CLK__nMSTP_DISCOM2_Cfg     << 28U)  \
                                     | (CLK__nMSTP_DISCOM3_Cfg     << 27U)  \
                                     | (CLK__nMSTP_LVDS_IF_Cfg     << 26U)  \
                                     | (CLK__nMSTP_DU0_Cfg         << 24U)  \
                                     | (CLK__nMSTP_DU1_Cfg         << 23U)  \
                                     | (CLK__nMSTP_DU2_Cfg         << 22U)  \
                                     | (CLK__nMSTP_SCIF0_Cfg       << 21U)  \
                                     | (CLK__nMSTP_SCIF1_Cfg       << 20U)  \
                                     | (CLK__nMSTP_SCIF2_Cfg       << 19U)  \
                                     | (CLK__nMSTP_SCIF3_Cfg       << 18U)  \
                                     | (CLK__nMSTP_HSCIF0_Cfg      << 17U)  \
                                     | (CLK__nMSTP_HSCIF1_Cfg      << 16U)  \
                                     | (CLK__nMSTP_SFMA0_Cfg       << 12U)  \
                                     | (CLK__nMSTP_RSDS_IF_Cfg     << 11U)  \
                                     | (CLK__nMSTP_VOCA0_Cfg       <<  7U)  \
                                     | (CLK__nMSTP_USBFC_Cfg       <<  4U)  \
                                     | (CLK__nMSTP_USBHC_Cfg       <<  3U) | 0x0200E765UL)

/* System module stop control register 8 */
#define CLK__nMSBC_SMSTPCR8_Cfg      ((CLK__nMSTP_ETNB0_Cfg       << 12U)  \
                                     | (CLK__nMSTP_VIN0_Cfg        << 11U)  \
                                     | (CLK__nMSTP_VIN1_Cfg        << 10U)  \
                                     | (CLK__nMSTP_GPU2D_Cfg       <<  7U)  \
                                     | (CLK__nMSTP_MIPI_IF_Cfg     <<  3U)  \
                                     | (CLK__nMSTP_MLBB0_Cfg       <<  2U)  \
                                     | (CLK__nMSTP_IPMMUGP_Cfg     <<  0U) | 0x01F0E300UL)

/* System module stop control register 9 */
#define CLK__nMSBC_SMSTPCR9_Cfg      ((CLK__nMSTP_I2C0_Cfg        << 31U)  \
                                     | (CLK__nMSTP_I2C1_Cfg        << 30U)  \
                                     | (CLK__nMSTP_RS_CANFD_Cfg    << 16U)  \
                                     | (CLK__nMSTP_GPIO0_Cfg       << 12U)  \
                                     | (CLK__nMSTP_GPIO1_Cfg       << 11U)  \
                                     | (CLK__nMSTP_GPIO2_Cfg       << 10U)  \
                                     | (CLK__nMSTP_GPIO3_Cfg       <<  9U)  \
                                     | (CLK__nMSTP_GPIO4_Cfg       <<  8U) | 0x01D4E047UL)

/* System module stop control register 10 */
#define CLK__nMSBC_SMSTPCR10_Cfg     ((CLK__nMSTP_SSIF0_Cfg       << 15U)  \
                                     | (CLK__nMSTP_SSIF1_Cfg       << 14U)  \
                                     | (CLK__nMSTP_DNFA0_Cfg       <<  3U) | 0xFFFE3FE0UL)

/* System module stop control register 11 */
#define CLK__nMSBC_SMSTPCR11_Cfg     ((CLK__nMSTP_DCRA0_Cfg       <<  3U) | 0x1F7UL)

/*Mask for clock output control bit */
#define CLK__nCKSTP_Mask                    (1UL << 8U)
#define CLK__nPIX2CKSTP_Mask                (1UL << 9U)

/* H1H - Structure of Clock Controller Registers */
typedef struct {
   CLK__GAP32(0x0000, 0x0004);
   u32 u32Frqcrb;      /* 0xE615 0004 - Frequency control register B */
   CLK__GAP32(0x0008, 0x0028);
   u32 u32Pll1cr;      /* 0xE615 0028 - PLL1 control register */
   CLK__GAP32(0x002C, 0x0030);
   u32 u32Mstpsr0;     /* 0xE615 0030 - Module stop status register 0 */
   CLK__GAP32(0x0034, 0x0038);
   u32 u32Mstpsr1;     /* 0xE615 0038 - Module stop status register 1 */
   u32 u32Mstpsr5;     /* 0xE615 003C - Module stop status register 5 */
   u32 u32Mstpsr2;     /* 0xE615 0040 - Module stop status register 2 */
   CLK__GAP32(0x0044, 0x0048);
   u32 u32Mstpsr3;     /* 0xE615 0048 - Module stop status register 3 */
   u32 u32Mstpsr4;     /* 0xE615 004C - Module stop status register 4 */
   CLK__GAP32(0x0050, 0x00D0);
   u32 u32Pllecr;      /* 0xE615 00D0 - PLL Enable Control Register */
   CLK__GAP32(0x00D4, 0x00D8);
   u32 u32Pll0cr;      /* 0xE615 00D8 - PLL0 control register */
   u32 u32Pll3cr;      /* 0xE615 00DC - PLL3 control register */  
   CLK__GAP32(0x00E0, 0x0130);
   u32 u32Smstpcr0;    /* 0xE615 0130 - System module stop control register 0 */
   u32 u32Smstpcr1;    /* 0xE615 0134 - System module stop control register 1 */
   u32 u32Smstpcr2;    /* 0xE615 0138 - System module stop control register 2 */
   u32 u32Smstpcr3;    /* 0xE615 013C - System module stop control register 3 */
   u32 u32Smstpcr4;    /* 0xE615 0140 - System module stop control register 4 */
   u32 u32Smstpcr5;    /* 0xE615 0144 - System module stop control register 5 */
   u32 u32Smstpcr6;    /* 0xE615 0148 - System module stop control register 6 */
   u32 u32Smstpcr7;    /* 0xE615 014C - System module stop control register 7 */
   CLK__GAP32(0x0150, 0x01C0);
   u32 u32Mstpsr6;     /* 0xE615 01C0 - Module stop status register 6 */
   u32 u32Mstpsr7;     /* 0xE615 01C4 - Module stop status register 7 */
   CLK__GAP32(0x01C8, 0x01F4);
   u32 u32Pllscr;      /* 0xE615 01F4 - PLLS control register */
   CLK__GAP32(0x01F8, 0x0240);
   u32 u32Mmc0ckcr;    /* 0xE615 0240 - MMC0 clock frequency control register */
   CLK__GAP32(0x0244, 0x0270);
   u32 u32Rcanckcr;    /* 0xE615 0270 - RCAN clock frequency control register */
   CLK__GAP32(0x0274, 0x036C); /* GAP of 62 words */
   u32 u32IntOscEncr;  /* 0xE615 036C - Internal OSC enable control register */
   u32 u32IntOscProc;  /* 0xE615 0370 - Internal OSC protection command register */
   u32 u32IntOscProc2; /* 0xE615 0374 - Internal OSC write protect register 2 */
   CLK__GAP32(0x0378, 0x0990); /* GAP of 390 words */
   u32 u32Smstpcr8;    /* 0xE615 0990 - System module stop control register 8 */
   u32 u32Smstpcr9;    /* 0xE615 0994 - System module stop control register 9 */
   u32 u32Smstpcr10;   /* 0xE615 0998 - System module stop control register 10 */
   u32 u32Smstpcr11;   /* 0xE615 099C - System module stop control register 11 */
   u32 u32Mstpsr8;     /* 0xE615 09A0 - Module stop status register 8 */
   u32 u32Mstpsr9;     /* 0xE615 09A4 - Module stop status register 9 */
   u32 u32Mstpsr10;    /* 0xE615 09A8 - Module stop status register 10 */
   u32 u32Mstpsr11;    /* 0xE615 09AC - Module stop status register 11 */
   CLK__GAP32(0x09B0, 0x0A08);
   u32 u32Tpuclkcr;    /* 0xE615 0A08 - CKSC_TPUCLK_Control Register */
   u32 u32Cmtclkcr;    /* 0xE615 0A0C - CKSC_CMTCLK_Control Register */
   u32 u32Tmuclkcr;    /* 0xE615 0A10 - CKSC_TMUCLK_Control Register */
   u32 u32Sfmaclkcr;   /* 0xE615 0A14 - CKSC_SFMACLK_Control Register */
   CLK__GAP32(0x0A18, 0x0A24);
   u32 u32Z2dclkcr;    /* 0xE615 0A24 - CKSC_Z2DCLK_CTL Register */
   u32 u32Z3dclkcr;    /* 0xE615 0A28 - CKSC_Z3DCLK_CTL Register */
   u32 u32Usbclkcr;    /* 0xE615 0A2C - CKSC_USBCLK_CTL Register */
   CLK__GAP32(0x0A30, 0x0A34);
   u32 u32Pix2aclkcr;  /* 0xE615 0A34 - CKSC_PIX2A_CTL Register */
   u32 u32Pix2bclkcr;  /* 0xE615 0A38 - CKSC_PIX2B_CTL Register */
   u32 u32Pix3aclkcr;  /* 0xE615 0A3C - CKSC_PIX3A_CTL Register */
   u32 u32Pix4aclkcr;  /* 0xE615 0A40 - CKSC_PIX4A_CTL Register */
   u32 u32Cksccr;      /* 0xE615 0A44 - CKSC_CTL Register */
   CLK__GAP32(0x0A48, 0x0A64);
   u32 u32Pix1clkcr;   /* 0xE615 0A64 - CKSC_PIX1_CTL Register */
   u32 u32Pix2clkcr;   /* 0xE615 0A68 - CKSC_PIX2_CTL Register */
   u32 u32Pix3clkcr;   /* 0xE615 0A6C - CKSC_PIX3_CTL Register */
   u32 u32Pix4clkcr;   /* 0xE615 0A70 - CKSC_PIX4_CTL Register */
   CLK__GAP32(0x0A74, 0x0A78);
   u32 u32Pix2dclkcr;  /* 0xE615 0A78 - CKSC_PIX2D_CTL Register */
   CLK__GAP32(0x0A7C, 0x0A80);
   u32 u32Pll0cr1;     /* 0xE615 0A80 - PLL0 control register 1 */
   CLK__GAP32(0x0A84, 0x0A88);
   u32 u32Pllscr1;     /* 0xE615 0A88 - PLLS control register 1 */
   CLK__GAP32(0x0A8C, 0x0A90);
   u32 u32Cksccr2;     /* 0xE615 0A90 - CKSC_Z2CK_CTL Register */
} CLK_tstD1H_ClkCtrl;

/* D1H - Structure of Clock Monitor registers */
typedef struct {
   u8  u8Clmanctl0;    /* 0x00 - CLMAn control register 0 */
   CLK__GAP8(0x0001, 0x0008);
   u16 u16Clmancmpl;    /* 0x08 - CLMAn compare register L */
   CLK__GAP16(0x000A, 0x000C);
   u16 u16Clmancmph;    /* 0x0C - CLMAn compare register H */
   CLK__GAP16(0x000E, 0x0010);
   u8  u8Clmanpcmd;    /* 0x10 - CLMAnCTL0 protection command register */
   CLK__GAP8(0x0011, 0x0014);
   u8  u8Clmanps;      /* 0x14 - CLMAnCTL0 protection status register */
   CLK__GAP8(0x0015, 0x0018);
   u8  u8Clmanemu0;    /* 0x18 - CLMAn emulation register 0 */
} CLK_tstD1H_Clma;


/* Structure of PLLx control register */
typedef union{
   u32 u32word;
   struct
   {
      u32 bi32Reserved0  :  7;
      u32 bi32CKSEL      :  1;
      u32 bi32Reserved1  :  4;
      u32 bi32CKSELPLL0  :  1;
      u32 bi32Reserved2  :  7;
      u32 bi32P          :  2;
      u32 bi32Reserved3  :  2;
      u32 bi32STC        :  7;
      u32 bi32CfgEn      :  1;
   }bits;
} CLK__tunPllCR;


/* D1H - Structure of Phase Lock Loop configuration */
typedef struct {
   u32 u32Pllecr;      /* PLL Enable Control Register */
   CLK__tunPllCR unPll0cr;      /* PLL0 control register */
   CLK__tunPllCR unPll3cr;      /* PLL3 control register */
   u32 u32Pll0cr1;     /* PLL0 control register 1 */
   u32 u32Pllscr1;     /* PLLS control register 1 */
}CLK_tstD1H_PLL_Config;

/* D1H - Structure of Clock Pulse Generator configuration */
typedef struct {
   u32 u32Frqcrb;      /* Frequency control register B */
   u32 u32Mmc0ckcr;    /* MMC0 clock frequency control register */
   u32 u32Rcanckcr;    /* RCAN clock frequency control register */
   u32 u32Cksccr;      /* CKSC_CTL Register */
   u32 u32Cksccr2;     /* CKSC_Z2CK_CTL Register */
   u32 u32Usbclkcr;    /* CKSC_USBCLK_CTL Register */
   u32 u32Z2dclkcr;    /* CKSC_Z2DCLK_CTL Register */
   u32 u32Z3dclkcr;    /* CKSC_Z3DCLK_CTL Register */
   u32 u32Pix1clkcr;   /* CKSC_PIX1_CTL Register */
   u32 u32Pix2clkcr;   /* CKSC_PIX2_CTL Register */
   u32 u32Pix2aclkcr;  /* CKSC_PIX2A_CTL Register */
   u32 u32Pix2bclkcr;  /* CKSC_PIX2B_CTL Register */
   u32 u32Pix2dclkcr;  /* CKSC_PIX2D_CTL Register */
   u32 u32Pix3aclkcr;  /* CKSC_PIX3A_CTL Register */
   u32 u32Pix3clkcr;   /* CKSC_PIX3_CTL Register */
   u32 u32Pix4aclkcr;  /* CKSC_PIX4A_CTL Register */
   u32 u32Pix4clkcr;   /* CKSC_PIX4_CTL Register */
   u32 u32Tpuclkcr;    /* CKSC_TPUCLK_Control Register */
   u32 u32Tmuclkcr;    /* CKSC_TMUCLK_Control Register */
   u32 u32Cmtclkcr;    /* CKSC_CMTCLK_Control Register */
   u32 u32Sfmaclkcr;   /* CKSC_SFMACLK_Control Register */
} CLK_tstD1H_CPG_Config;


/* D1H - Structure of Module Stand-by Control configuration */
typedef struct {
   u32 u32Smstpcr0;    /* System module stop control register 0 */
   u32 u32Smstpcr1;    /* System module stop control register 1 */
   u32 u32Smstpcr2;    /* System module stop control register 2 */
   u32 u32Smstpcr3;    /* System module stop control register 3 */
   u32 u32Smstpcr4;    /* System module stop control register 4 */
   u32 u32Smstpcr5;    /* System module stop control register 5 */
   u32 u32Smstpcr6;    /* System module stop control register 6 */
   u32 u32Smstpcr7;    /* System module stop control register 7 */
   u32 u32Smstpcr8;    /* System module stop control register 8 */
   u32 u32Smstpcr9;    /* System module stop control register 9 */
   u32 u32Smstpcr10;   /* System module stop control register 10 */
   u32 u32Smstpcr11;   /* System module stop control register 11 */
} CLK_tstD1H_MSBC_Config;

/* D1H - Structure of Clock Monitoring configuration */
typedef struct {
   u16 u16Clma0cmpl;   /* PLL0 compare register L */
   u16 u16Clma0cmph;   /* PLL0 compare register H */
   u16 u16Clma1cmpl;   /* PLL1 compare register L */
   u16 u16Clma1cmph;   /* PLL1 compare register H */
   u16 u16Clma2cmpl;   /* PLL2 compare register L */
   u16 u16Clma2cmph;   /* PLL2 compare register H */
   u16 u16Clma3cmpl;   /* PLL3 compare register L */
   u16 u16Clma3cmph;   /* PLL3 compare register H */
   u16 u16Clma4cmpl;   /* PLL4 compare register L */
   u16 u16Clma4cmph;   /* PLL4 compare register H */
   u16 u16Clma5cmpl;   /* PLL5 compare register L */
   u16 u16Clma5cmph;   /* PLL5 compare register H */
   u8  u8Clma0ctl0;    /* PLL0 control register */
   u8  u8Clma1ctl0;    /* PLL1 control register */
   u8  u8Clma2ctl0;    /* PLL2 control register */
   u8  u8Clma3ctl0;    /* PLL3 control register */
   u8  u8Clma4ctl0;    /* PLL4 control register */
   u8  u8Clma5ctl0;    /* PLL5 control register */
   u16 u16dummy;       /* Padding for word-align */
} CLK_tstD1H_CLMA_Config;


/* Structure of Mode Monitor Register (MODEMR) */
typedef union{
   u32 u32word;
   struct
   {
      u32 bi32MD00       :  1;
      u32 bi32MD01       :  1;
      u32 bi32MD02       :  1;
      u32 bi32Reserved0  :  2;
      u32 bi32MD05       :  1;
      u32 bi32Reserved1  :  3;
      u32 bi32MD09       :  1;
      u32 bi32Reserved2  :  4;
      u32 bi32MD14       :  1;
      u32 bi32Reserved3  : 17;
   }bits;
} CLK__tunModeMR;


/* Structure of Frequency Control Register B (FRQCRB) */
typedef union{
   u32 u32word;
   struct
   {
/*    u32 bi32ZTRD2FC    :  4; */ /*As per User Manual v0.81, ZTRD2phi clock and its selection bits ZTRD2FC[3:0] were removed from FRQCRB register */
      u32 bi32Reserved0  : 16;
      u32 bi32ZTFC       :  4;
      u32 bi32ZTRFC      :  4;
      u32 bi32Reserved1  :  7;
      u32 bi32KICK       :  1;
   }bits;
} CLK__tunFrqCRB;


/* Structure of CKSC_Z2/3DCLK_CTL Control Register */
typedef union{
   u32 u32word;
   struct
   {
         u32 bi32Reserved0 :  8;
         u32 bi32CKSTP     :  1;
         u32 bi32Reserved1 :  1;
         u32 bi32Div1      :  1;   /* 0: fPLL1CLK / 5, 1: fPLL1CLK / 6 */
         u32 bi32Div2      :  1;   /* 0: fPLLSCLK / 5, 1: fPLLSCLK / 6 */
         u32 bi32ClkSel1   :  1;   /* 0: Z3D = fPLL1CLK/DIV, 1: Z3D = fPLLSCLK/DIV */
         u32 bi32ClkSel2   :  1;   /* 1: Z3D = PLL3CLK / 4 */
         u32 bi32Reserved2 : 18;
   }bits;
} CLK__tunZ2dclkCR;


/* Structure of CKSC_CTL Control Register 2 */
typedef union{
      u32 u32word;
      struct
      {
         u32 bi32Z2CkSel0   :  2;
         u32 bi32Reserved0  :  2;
         u32 bi32Z2CkSel1   :  2;
         u32 bi32Reserved1  : 26;
      }bits;
} CLK__tunCkscCR2;


/* Structure of CLK Configuration */
typedef struct {
   CLK_tstD1H_CPG_Config  stCPGConfig;
   CLK_tstD1H_MSBC_Config stMSBCConfig;
   CLK_tstD1H_PLL_Config  stPLLConfig;
#if (CLK_nHandleCLMA == Yes)
   CLK_tstD1H_CLMA_Config stCLMAConfig;
#endif
} CLK_tstConfig;
#endif

