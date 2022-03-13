#ifndef __ASM_ARCH_D1H_SDRAM_H__
#define __ASM_ARCH_D1H_SDRAM_H__
#include <asm/types.h>

bool sdram_init(void);

#define SDRAM_GAP32(start,finish)    u32 u32__##start##_##finish[((finish)-(start))/4]

#define SDRAM_nDDR3_1066   1066
#define SDRAM_nDDR3_1333   1333

#define SDRAM_nDDR3_2x4Gb   1
#define SDRAM_nDDR3_2x2Gb   2
#define SDRAM_nDDR3_2x1Gb   3
#define SDRAM_nDDR3_1x4Gb   4
#define SDRAM_nDDR3_1x2Gb   5
#define SDRAM_nDDR3_1x1Gb   6
/*
 * Description: Configuration for DDR3 fallback values
 * Values     : SDRAM_nDDR3_1066 - use DDR3-1066
 *              SDRAM_nDDR3_1333 - use DDR3-1333
 */
#define SDRAM_nDDR3RateConfig   SDRAM_nDDR3_1333

#define SDRAM_nDDR3SizeConfig   SDRAM_nDDR3_2x4Gb

/*
* Memory Test Configuration
* This is used to verify DDR3 Initialization
*/
#define SDRAM__nMemTestDataPattern             0xE11AE11AUL
#define SDRAM__nMemTestStartAddress            0x40000000UL
#define SDRAM__nMemTestAddressIncrement        0x10000000UL
#define SDRAM__nMemTestEndAddress              0xBFFFFFFFUL

/***************************************************************************
* SDRAM TIMING CONFIGURATION
****************************************************************************/
#define SDRAM__nSDRAM_ZQCalibration           On
/*
* Description : Switch to enable periodic ZQ calibration
*  Values      : On | Off
*/

#define SDRAM__nSDRAM_AutoPowerDown           On
/*
* Description : Switch to enable auto-power-down mode
*  Values      : On | Off
*/

/*
* DBSC3 Auto-Refresh Enable Register
* [0:0]   ARFEN: Auto-Refresh Enable Bit
*/
#define SDRAM__nDBSC3_DBFREN_Enable           0x00000001UL
#define SDRAM__nDBSC3_DBFREN_Disable          0x00000000UL

/*
* DBSC3 SDRAM Access Enable Register
* [0:0]   ACCEN: SDRAM Access Enable
*/
#define SDRAM__nDBSC3_DBACEN_Enable           0x00000001UL
#define SDRAM__nDBSC3_DBACEN_Disable          0x00000000UL

/*
* DBSC3 SDRAM Type Setting Register
* [2:0]   DDCG: SDRAM Type Bits
*         111 - DDR3-SDRAM (other settings prohibited)
*/
#define SDRAM__nDBSC3_DBKIND                  0x00000007UL
/*
* DBSC3 SDRAM Configuration Setting Register 0
* [28:24] AWRW0 : Row Address Bit Width
* [20:20] AWRK0 : Number of Ranks --> Must always be 0 (One rank)
* [17:16] AWBK0 : Number of Banks --> Must always be 0b11 (Eight banks)
* [11:8]  AWCL0 : Column Address Bit Width
* [1:0]   DW0 : External Data Bus Width Settings
*         01 - 16 bits
*         10 - 32 bits
*         (other settings prohibited)
*/
#if   (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_2x4Gb)
#define SDRAM__nDBSC3_DBCONF0                 0x0F030A02UL
#elif (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_2x2Gb)
#define SDRAM__nDBSC3_DBCONF0                 0x0E030A02UL
#elif (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_2x1Gb)
#define SDRAM__nDBSC3_DBCONF0                 0x0D030A02UL
#elif (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_1x4Gb)
#define SDRAM__nDBSC3_DBCONF0                 0x0F030A01UL
#elif (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_1x2Gb)
#define SDRAM__nDBSC3_DBCONF0                 0x0E030A01UL
#elif (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_1x1Gb)
#define SDRAM__nDBSC3_DBCONF0                 0x0D030A01UL
#endif

/*
* DBSC3 PHY Type Setting Register
* [1:0]   PHYTYPE: PHY Type Setting Bits
*         01 - DFI (other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBPHYTYPE               0x00000001UL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBPHYTYPE               0x00000001UL
#endif

/*
* DBSC3 SDRAM Timing Register 0
* [3:0]   CL: CAS Latency Setting Bits
*         3..14 (other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBTR0                   0x00000007UL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBTR0                   0x00000009UL
#endif

/*
* DBSC3 SDRAM Timing Register 1
* [3:0]   CWL: CAS Write Latency Setting Bits
*         2..10 (other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBTR1                   0x00000006UL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBTR1                   0x00000007UL
#endif

/*
* DBSC3 SDRAM Timing Register 3
* [4:0]   TRCD: ACT to READ/ACT to WRITE Interval Setting Bits
*         3..31 (other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBTR3                   0x00000008UL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBTR3                   0x0000000AUL
#endif

/*
* DBSC3 SDRAM Timing Register 4
* [20:16] TRPA: PREA Time Setting Bits
*         3..31 (other settings prohibited)
* [4:0]   TRP: PRE Time Setting Bits
*         3..31 (other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBTR4                   0x00080008UL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBTR4                   0x000A000AUL
#endif

/*
* DBSC3 SDRAM Timing Register 5
* [5:0]   TRC: ACT to ACT/ACT to REF Interval Setting Bits
*         6..63 (other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBTR5                   0x0000001BUL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBTR5                   0x00000021UL
#endif

/*
* DBSC3 SDRAM Timing Register 6
* [5:0]   TRAS: ACT to PRE Interval Setting Bits
*         3..34 (other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBTR6                   0x00000014UL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBTR6                   0x00000018UL
#endif

/*
* DBSC3 SDRAM Timing Register 7
* [3:0]   TRRD: ACT(A) to ACT(B) Interval Setting Bits
*         2..15 (other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBTR7                   0x00000006UL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBTR7                   0x00000005UL
#endif

/*
* DBSC3 SDRAM Timing Register 8
* [7:0]   TFAW: Four Active Window Length Setting Bits
*         8..63(other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBTR8                   0x0000001BUL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBTR8                   0x0000001EUL
#endif

/*
* DBSC3 SDRAM Timing Register 9
* [3:0]   TRDPR: READ-PRE Interval Setting Bits
*         4..15(other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBTR9                   0x00000006UL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBTR9                   0x00000007UL
#endif

/*
* DBSC3 SDRAM Timing Register 10
* [3:0]   TWR: Write-Recovery Period Setting Bits
*         3..14(other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBTR10                  0x00000008UL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBTR10                  0x0000000CUL
#endif

/*
* DBSC3 SDRAM Timing Register 11
* [5:0]   TRDWR: READ to WRITE Interval Setting Bits
*         6..15(other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBTR11                  0x00000008UL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBTR11                  0x00000009UL
#endif

/*
* DBSC3 SDRAM Timing Register 12
* [5:0]   TWRRD: WRITE to READ Interval Setting Bits
*         6..31(other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBTR12                  0x0000000EUL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBTR12                  0x00000010UL
#endif

/*
* DBSC3 SDRAM Timing Register 13
* [11:0]  TRFC/TRFCAB: REF to ACT/REF or All Bank REF to ACT/REF
*         Interval Setting Bits
*         8..511(other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#if   (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_2x4Gb) || (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_1x4Gb)
#define SDRAM__nDBSC3_DBTR13                  0x0000008BUL
#elif (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_2x2Gb) || (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_1x2Gb)
#define SDRAM__nDBSC3_DBTR13                  0x00000056UL
#elif (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_2x1Gb) || (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_1x1Gb)
#define SDRAM__nDBSC3_DBTR13                  0x0000003BUL
#endif

#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#if   (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_2x4Gb) || (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_1x4Gb)
#define SDRAM__nDBSC3_DBTR13                  0x000000AEUL
#elif (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_2x2Gb) || (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_1x2Gb)
#define SDRAM__nDBSC3_DBTR13                  0x0000006BUL
#elif (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_2x1Gb) || (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_1x1Gb)
#define SDRAM__nDBSC3_DBTR13                  0x0000004AUL
#endif
#endif   /*SDRAM_nDDR3RateConfig*/

/*
* DBSC3 SDRAM Timing Register 14
* [23:16] TCKEHDLL: CKEH (DLL-LOCK) Period Setting Bits
*         2..23(other settings prohibited)
* [7:0]   TCKEH: CKEH Period Setting Bits
*         2..15(other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBTR14                  0x000D0004UL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBTR14                  0x00100004UL
#endif

/*
* DBSC3 SDRAM Timing Register 15
* [19:18] TCKESR: CKESR Period Setting Bits
*         2..15(other settings prohibited)
* [3:0]   TCKEL: CKEL Period Setting Bits
*         2..15(other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBTR15                  0x00040003UL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBTR15                  0x00050004UL
#endif

/*
* DBSC3 SDRAM Timing Register 16
* [31:28] DQIENLTNCY
*         2..11(other settings prohibited)
* [21:16] DQL (dqltncy)
*         7..63(other settings prohibited)
* [15:12] DQENLTNCY
*         0..5(other settings prohibited)
* [3:0]   WDQL
*         0..8(other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBTR16                  0x30191003UL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBTR16                  0x501B3005UL
#endif

/*
* DBSC3 SDRAM Timing Register 17
* [21:16] TMOD: MRS Time Setting Bits
*         2..15(other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBTR17                  0x000C0000UL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBTR17                  0x000C0000UL
#endif

/*
* DBSC3 SDRAM Timing Register 18
* [26:24] RODTL: Bits for ODT Assert Period Setting at Read
*         000..111(other settings prohibited)
* [18:16] RODTA: Bits for ODT Assert Start Timing Settings Bits Read
*         000..011(other settings prohibited)
* [10:8]  WODTL: Bits for ODT Assert Period Setting at Write
*         000..111(other settings prohibited)
* [2:0]   WODTA
*         0..3(other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBTR18                  0x00000200UL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBTR18                  0x00000200UL
#endif

/*
* DBSC3 SDRAM Timing Register 19
* [7:0]   TZQCS
*         6..255(other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBTR19                  0x00000040UL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBTR19                  0x00000040UL
#endif

/*
* DBSC3 ODT Operation Setting Register
* [16:16] RODTOUT0: Bit for ODT Output Level Setting at Read
*         0 | 1
* [0:0]   WODTOUT0: Bit for ODT Output Level Setting at Write
*         0 | 1
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBRNK0                  0x00000001UL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBRNK0                  0x00000001UL
#endif

/*
* DBSC3 Operation Adjustment Register 0
* [17:16] FREQRATIO: PHY Frequency Ratio Settings Bits
*         10: Ratio is 1:4 (other settings prohibited)
* [0:0]   CAMODE: Command/Address Output Mode Setting Bit
*         1: One command output in 2 clock cycles
*         (other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBADJ0                  0x00020001UL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBADJ0                  0x00020001UL
#endif

/*
* DBSC3 Operation Adjustment Register 2
* [31:24] ACAPC1
*         0x20 Fixed value (other settings prohibited)
* [19:16] ACAPX1: Transaction Count Acceptable by Device Control Unit
*         (High priority port)
*         4 | 8 (other settings prohibited)
* [15:8]  ACAPC0
*         0x20 Fixed value (other settings prohibited)
* [3:0]   ACAPX0: Transaction Count Acceptable by Device Control Unit
*         (High priority port)
*         4 | 8 (other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBADJ2                  0x20042004UL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBADJ2                  0x20042004UL
#endif

/*
* DDR3-SDRAM Calibration Timing Register
* [27:16] TCALRZ: DDR3-SDRAM Calibration Timing Setting
* [11:0]  TCALZR: DDR3-SDRAM Calibration Timing Setting
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#if   (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_2x4Gb) || (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_1x4Gb)
#define SDRAM__nDBSC3_DBCALTR                 0x00F600ABUL
#elif (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_2x2Gb) || (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_1x2Gb)
#define SDRAM__nDBSC3_DBCALTR                 0x00C100ABUL
#elif (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_2x1Gb) || (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_1x1Gb)
#define SDRAM__nDBSC3_DBCALTR                 0x00A600ABUL
#endif

#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#if   (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_2x4Gb) || (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_1x4Gb)
#define SDRAM__nDBSC3_DBCALTR                 0x012100B3UL
#elif (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_2x2Gb) || (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_1x2Gb)
#define SDRAM__nDBSC3_DBCALTR                 0x00DE00B3UL
#elif (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_2x1Gb) || (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_1x1Gb)
#define SDRAM__nDBSC3_DBCALTR                 0x00BD00B3UL
#endif
#endif   /*SDRAM_nDDR3RateConfig*/

/*
* DBSC3 Refresh Configuration Register 0
* [11:0]  REFTHF: Forcibel Auto-Refresh Threshold Setting Bits
*         0x80..0x1FF (other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBRFCNF0                0x0000003BUL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBRFCNF0                0x00000042UL
#endif

/*
* DBSC3 Refresh Configuration Register 1
* [31:16] REFPMAX: Maximum Post Number of Refresh Command Setting Bits
*         2..8 (other setting prohibited)
* [11:0]  REFINT: Average Refresh Interval Setting Bits
*         0x80..0x3FFF (other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBRFCNF1                0x0008080BUL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBRFCNF1                0x00080A0EUL
#endif

/*
* DBSC3 Refresh Configuration Register 2
* [19:16] REFPMIN: Minimum Post Number of Refresh Command Setting Bits
*         1 (other settings prohibited)
* [0:0]   REFINTS: Average Refresh Interval Adjutsment Bit
*         0 | 1
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBRFCNF2                0x00010000UL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBRFCNF2                0x00010000UL
#endif

/*
* DBSC3 Auto-Refresh Enable Register
* [0:0]   ARFEN: Auto-Refresh Enable Bit
*         0 -
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define  SDRAM__nDBSC3_DBRFEN                 0x00000001UL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define  SDRAM__nDBSC3_DBRFEN                 0x00000001UL
#endif

/*
* DDR3-SDRAM Calibration Configuration Register
* [24:24] CALEN: DDR3-SDRAM Calibration Enable Bit
* [15:0]  CALINT: DDR3-SDRAM Calibration Frequency Settings Bit
*         0x0001..0xFFFF
*/
#define SDRAM__nDBSC3_DBCALCNF_Enable         0x0100983EUL
#define SDRAM__nDBSC3_DBCALCNF_Disable        0x0000983EUL

/*
* DBSC3 PHY Control Register 0
* [0:0] CNTREG0: Enable PHY update request
*/
#define SDRAM__nDBSC3_DBPDCNT0_Enable         (0x00000001UL)
#define SDRAM__nDBSC3_DBPDCNT0_Disable        (0x00000000UL)

/*
* DBSC3 DFI Status IF Output Register
* [5:4] FREQRATIO
* [0:0] INITSTART
*/
#define SDRAM__nDBSC3_DBDFICNT_Init          (0x00000011UL)


/*
* DBSC3 PHY Unit Lock Register
* [15:0] PLOCK: PHY Unit Access Lock Setting
*/
#define SDRAM__nDBSC3_DBPDLCK_EnableAccess    (0x0000A55AUL)
#define SDRAM__nDBSC3_DBPDLCK_DisableAccess   (0x00000000UL) /*Any value other than A55A should work */

/*
* DBSC3 Bus Control Unit 0 Control Register 1
* [1:0]   BKADM: Bank Assignment Setting Bits
*  Values      : 00 - Whole logical address space is regarded as one block
*                01 - One block for banks 0-3 and one block for banks 4-7
*                10 - Three blocks: 0-1, 2-3, 4-7
*                11 - Four blocks: 0, 1, 2-3, 4-7
*/
#define SDRAM__nDBSC3_DBBS0CNT1               0x000000000UL

/*
* DBSC3 AXI Port Setting Register 0
* [18:16] WASYN: "010" (other settings prohibited)
* [2:0]   WCN: AXI Clock to Memory Clock Ratio Setting Bits
*         000..101 (other settings prohibited)
*/
#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)
#define SDRAM__nDBSC3_DBWT0CNF0               0x00020005UL
#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)
#define SDRAM__nDBSC3_DBWT0CNF0               0x00020003UL
#endif

/*
* DBSC3 AXI Port Setting Register 4
* [4:0]   RDFIFONUM: Read FIFO Count Bit
*         11111 (other settings prohibited)
*/
#define SDRAM__nDBSC3_DBWT0CNF4               0x0000001FUL

/*
* DBSC3 Reset Lock Register
* [31:0] DBRSTLCK
*/
#define SDRAM__nDBSC3_DBRSTLCK_EnableAccess   (0x0000A55AUL)
#define SDRAM__nDBSC3_DBRSTLCK_DisableAccess  (0x00000000UL)

/*
* DBSC3 Reset Register
* [0:0]   DBRST:  DBSC Reset control
*/
#define SDRAM__nDBSC3_DBRST_Assert            (0x00000001UL)
#define SDRAM__nDBSC3_DBRST_Deassert          (0x00000000UL)

/*
* DBSC3 Manual command-issuing register
* [29:24] OPC:  Operation Code Bits
*/
#define SDRAM__nDBSC3_DBCMD_SetResetPinToHigh (0x21000000UL)
#define SDRAM__nDBSC3_DBCMD_PowerDownExit     (0x11000000UL)
#define SDRAM__nDBSC3_DBCMD_PowerDownEntry    (0x10000000UL)


#if (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1066)

/*
* DDR3 PHY Settings
*/
#define SDRAM__nDDR3PHY0003B                  (0x0380C700UL)
#define SDRAM__nDDR3PHY0003A                  (0x0780C700UL)
#define SDRAM__nDDR3PHY0004                   (0x00F03EC9UL)
#define SDRAM__nDDR3PHY0008                   (0x001B8000UL)
#define SDRAM__nDDR3PHY0020                   (0x00181884UL)
#define SDRAM__nDDR3PHY0021                   (0x0024641FUL)
#define SDRAM__nDDR3PHY0022                   (0x1000040BUL)
#define SDRAM__nDDR3PHY0023                   (0x21940844UL)

/*
* SDRAM__nDDR3PHY0024
*/
#if   (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_2x4Gb) || (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_1x4Gb)
#define SDRAM__nDDR3PHY0024                   (0x16845CC0UL)
#elif (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_2x2Gb) || (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_1x2Gb)
#define SDRAM__nDDR3PHY0024                   (0x1A82B4C0UL)
#elif (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_2x1Gb) || (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_1x1Gb)
#define SDRAM__nDDR3PHY0024                   (0x1A81DCC0UL)
#else
#error "Invalid SDRAM_nDDR3SizeConfig!"
#endif

#define SDRAM__nDDR3PHY0025                   (0x30003600UL)
#define SDRAM__nDDR3PHY0026                   (0x001486C9UL)
#define SDRAM__nDDR3PHY0027                   (0x00001930UL)
#define SDRAM__nDDR3PHY0028                   (0x00000004UL)
#define SDRAM__nDDR3PHY0029                   (0x00000088UL)
#define SDRAM__nDDR3PHY002C                   (0x81003047UL)
#if (SDRAM_nDDR3LayerConfig == SDRAM_nDDR3_8LayerPCB)
#define SDRAM__nDDR3PHY0091                   (0x0007BB5DUL)
#define SDRAM__nDDR3PHY0099                   (0x0007BB5DUL)
#elif (SDRAM_nDDR3LayerConfig == SDRAM_nDDR3_6LayerPCB)
#define SDRAM__nDDR3PHY0091                   (0x0007BB5BUL)
#define SDRAM__nDDR3PHY0099                   (0x0007BB5BUL)
#else
#error "Invalid SDRAM_nDDR3LayerConfig!"
#endif   /*SDRAM_nDDR3LayerConfig*/
#define SDRAM__nDDR3PHY0095                   (0x0007BB5BUL)

#elif (SDRAM_nDDR3RateConfig == SDRAM_nDDR3_1333)

/*
* DDR3 PHY Settings
*/
#define SDRAM__nDDR3PHY0003B                  (0x0380C720UL)
#define SDRAM__nDDR3PHY0003A                  (0x0780C720UL)
#define SDRAM__nDDR3PHY0004                   (0x00F04EE2UL)
#define SDRAM__nDDR3PHY0008                   (0x000B8000UL)
#define SDRAM__nDDR3PHY0020                   (0x00181884UL)
#define SDRAM__nDDR3PHY0021                   (0x0024641FUL)
#define SDRAM__nDDR3PHY0022                   (0x1000040BUL)
#define SDRAM__nDDR3PHY0023                   (0x29580A55UL)

/*
* SDRAM__nDDR3PHY0024
*/
#if   (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_2x4Gb) || (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_1x4Gb)
#define SDRAM__nDDR3PHY0024                   (0x1A8574C0UL)
#elif (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_2x2Gb) || (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_1x2Gb)
#define SDRAM__nDDR3PHY0024                   (0x1A835CC0UL)
#elif (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_2x1Gb) || (SDRAM_nDDR3SizeConfig == SDRAM_nDDR3_1x1Gb)
#define SDRAM__nDDR3PHY0024                   (0x1A8254C0UL)
#else
#error "Invalid SDRAM_nDDR3SizeConfig!"
#endif

#define SDRAM__nDDR3PHY0025                   (0x30004200UL)
#define SDRAM__nDDR3PHY0026                   (0x0014A849UL)
#define SDRAM__nDDR3PHY0027                   (0x00001D50UL)
#define SDRAM__nDDR3PHY0028                   (0x00000004UL)
#define SDRAM__nDDR3PHY0029                   (0x00000090UL)
#define SDRAM__nDDR3PHY002C                   (0x81003047UL)
#if (SDRAM_nDDR3LayerConfig == SDRAM_nDDR3_8LayerPCB)
#define SDRAM__nDDR3PHY0091                   (0x0007BB5DUL)
#define SDRAM__nDDR3PHY0099                   (0x0007BB5DUL)
#elif (SDRAM_nDDR3LayerConfig == SDRAM_nDDR3_6LayerPCB)
#define SDRAM__nDDR3PHY0091                   (0x0007BB5BUL)
#define SDRAM__nDDR3PHY0099                   (0x0007BB5BUL)
#else
#error "Invalid SDRAM_nDDR3LayerConfig!"
#endif   /*SDRAM_nDDR3LayerConfig*/
#define SDRAM__nDDR3PHY0095                   (0x0007BB5BUL)

#endif   /*SDRAM_nDDR3RateConfig*/

/*
* Mask for External Data Bus Width Setting Bits in SDRAM Configuration Setting Register 0
*/
#define SDRAM__nDBCONF0_DW0_Msk               (0x00000003UL)

/*
* Mask for error flags. Error if bits[27:20]<>0
*/
#define SDRAM__nErrorFlags1_Msk               (0x0FF00000UL)

/*
* Mask for error flags. Error if bits[31]==0
*/
#define SDRAM__nErrorFlags2_Msk               (0x7FFFFFFFUL)

/*
* DDR3 PHY Address Settings (do not change)
*/
#define SDRAM__nDDR3PHY000_Addr               (0x00000000UL)
#define SDRAM__nDDR3PHY001_Addr               (0x00000001UL)
#define SDRAM__nDDR3PHY002_Addr               (0x00000002UL)
#define SDRAM__nDDR3PHY003_Addr               (0x00000003UL)
#define SDRAM__nDDR3PHY004_Addr               (0x00000004UL)
#define SDRAM__nDDR3PHY005_Addr               (0x00000005UL)
#define SDRAM__nDDR3PHY006_Addr               (0x00000006UL)
#define SDRAM__nDDR3PHY007_Addr               (0x00000007UL)
#define SDRAM__nDDR3PHY008_Addr               (0x00000008UL)
#define SDRAM__nDDR3PHY020_Addr               (0x00000020UL)
#define SDRAM__nDDR3PHY021_Addr               (0x00000021UL)
#define SDRAM__nDDR3PHY022_Addr               (0x00000022UL)
#define SDRAM__nDDR3PHY023_Addr               (0x00000023UL)
#define SDRAM__nDDR3PHY024_Addr               (0x00000024UL)
#define SDRAM__nDDR3PHY025_Addr               (0x00000025UL)
#define SDRAM__nDDR3PHY026_Addr               (0x00000026UL)
#define SDRAM__nDDR3PHY027_Addr               (0x00000027UL)
#define SDRAM__nDDR3PHY028_Addr               (0x00000028UL)
#define SDRAM__nDDR3PHY029_Addr               (0x00000029UL)
#define SDRAM__nDDR3PHY02C_Addr               (0x0000002CUL)
#define SDRAM__nDDR3PHY090_Addr               (0x00000090UL)
#define SDRAM__nDDR3PHY091_Addr               (0x00000091UL)
#define SDRAM__nDDR3PHY095_Addr               (0x00000095UL)
#define SDRAM__nDDR3PHY099_Addr               (0x00000099UL)
#define SDRAM__nDDR3PHY0A0_Addr               (0x000000A0UL)
#define SDRAM__nDDR3PHY0A3_Addr               (0x000000A3UL)
#define SDRAM__nDDR3PHY0A7_Addr               (0x000000A7UL)
#define SDRAM__nDDR3PHY0A8_Addr               (0x000000A8UL)
#define SDRAM__nDDR3PHY0A9_Addr               (0x000000A9UL)
#define SDRAM__nDDR3PHY0C0_Addr               (0x000000C0UL)
#define SDRAM__nDDR3PHY0C3_Addr               (0x000000C3UL)
#define SDRAM__nDDR3PHY0C7_Addr               (0x000000C7UL)
#define SDRAM__nDDR3PHY0C8_Addr               (0x000000C8UL)
#define SDRAM__nDDR3PHY0C9_Addr               (0x000000C9UL)
#define SDRAM__nDDR3PHY0E0_Addr               (0x000000E0UL)
#define SDRAM__nDDR3PHY0E1_Addr               (0x000000E1UL)
#define SDRAM__nDDR3PHY0E3_Addr               (0x000000E3UL)
#define SDRAM__nDDR3PHY0E7_Addr               (0x000000E7UL)
#define SDRAM__nDDR3PHY0E8_Addr               (0x000000E8UL)
#define SDRAM__nDDR3PHY0E9_Addr               (0x000000E9UL)
#define SDRAM__nDDR3PHY100_Addr               (0x00000100UL)
#define SDRAM__nDDR3PHY101_Addr               (0x00000101UL)
#define SDRAM__nDDR3PHY103_Addr               (0x00000103UL)
#define SDRAM__nDDR3PHY107_Addr               (0x00000107UL)
#define SDRAM__nDDR3PHY108_Addr               (0x00000108UL)
#define SDRAM__nDDR3PHY109_Addr               (0x00000109UL)
/**
* Description: Struct to store calibration information`
*/
typedef struct {
   u32 u32DBTR3;
   u32 u32DBTR4;
   u32 u32DBTR5;
   u32 u32DBTR6;
   u32 u32DBTR7;
   u32 u32DBTR8;
   u32 u32DBTR9;
   u32 u32DBTR10;
   u32 u32DBTR11;
   u32 u32DBTR12;
   u32 u32DBTR13;
   u32 u32DBTR14;
   u32 u32DBTR15;
   u32 u32DBTR16;
   u32 u32DBTR17;
   u32 u32DBTR18;
   u32 u32DBTR19;
} SDRAM_tstTimingCfg;

typedef struct {
   u32 u32DBRFCNF0;
   u32 u32DBRFCNF1;
   u32 u32DBRFCNF2;
} SDRAM_tstRefreshCfg;

/** 
* Description: Struct used to access DBSC3 registers
*/
typedef struct {
   u32 u32DBACEN;       // 0x0010 - SDRAM access enable register
   u32 u32DBRFEN;       // 0x0014 - Auto-refresh enable register
   u32 u32DBCMD;        // 0x0018 - Manual command-issuing register
   u32 u32DBWAIT;       // 0x001C - Operation completion waiting register
   u32 u32DBKIND;       // 0x0020 - SDRAM type setting register
   u32 u32DBCONF0;      // 0x0024 - SDRAM configuration setting register 0
   SDRAM_GAP32(0x0028, 0x0030);
   u32 u32DBPHYTYPE;    // 0x0030 - PHY type setting register
   SDRAM_GAP32(0x0034, 0x0040);
   u32 u32DBTR0;        // 0x0040 - SDRAM timing register 0
   u32 u32DBTR1;        // 0x0044 - SDRAM timing register 1
   SDRAM_GAP32(0x0048, 0x0050);
   SDRAM_tstTimingCfg stTimingReg;
/* u32 u32DBTR3;        // 0x0050 - SDRAM timing register 3
   u32 u32DBTR4;        // 0x0054 - SDRAM timing register 4
   u32 u32DBTR5;        // 0x0058 - SDRAM timing register 5
   u32 u32DBTR6;        // 0x005C - SDRAM timing register 6
   u32 u32DBTR7;        // 0x0060 - SDRAM timing register 7
   u32 u32DBTR8;        // 0x0064 - SDRAM timing register 8
   u32 u32DBTR9;        // 0x0068 - SDRAM timing register 9
   u32 u32DBTR10;       // 0x006C - SDRAM timing register 10
   u32 u32DBTR11;       // 0x0070 - SDRAM timing register 11
   u32 u32DBTR12;       // 0x0074 - SDRAM timing register 12
   u32 u32DBTR13;       // 0x0078 - SDRAM timing register 13
   u32 u32DBTR14;       // 0x007C - SDRAM timing register 14
   u32 u32DBTR15;       // 0x0080 - SDRAM timing register 15
   u32 u32DBTR16;       // 0x0084 - SDRAM timing register 16
   u32 u32DBTR17;       // 0x0088 - SDRAM timing register 17
   u32 u32DBTR18;       // 0x008C - SDRAM timing register 18
   u32 u32DBTR19;       // 0x0090 - SDRAM timing register 19 */
   SDRAM_GAP32(0x0094, 0x00C0);
   u32 u32DBADJ0;       // 0x00C0 - DBSC3 operation adjustment register 0
   SDRAM_GAP32(0x00C4, 0x00C8);
   u32 u32DBADJ2;       // 0x00C8 - DBSC3 operation adjustment register 2
   SDRAM_GAP32(0x00CC, 0x00E0);
   SDRAM_tstRefreshCfg stRefreshReg;
/* u32 u32DBRFCNF0;     // 0x00E0 - Refresh configuration register 0
   u32 u32DBRFCNF1;     // 0x00E4 - Refresh configuration register 1
   u32 u32DBRFCNF2;     // 0x00E8 - Refresh configuration register 2 */
   SDRAM_GAP32(0x00EC, 0x00F4);
   u32 u32DBCALCNF;     // 0x00F4 - DDR3-SDRAM calibration configuration register
   u32 u32DBCALTR;      // 0x00F8 - DDR3-SDRAM calibration timing register
   SDRAM_GAP32(0x00FC, 0x0100);
   u32 u32DBRNK0;       // 0x0100 - ODT operation setting register
   SDRAM_GAP32(0x0104, 0x0180);
   u32 u32DBPDNCNF;     // 0x0180 - Power-down configuration register
   SDRAM_GAP32(0x0184, 0x0200);
   u32 u32DBPDCNT0;     // 0x0200 - PHY Control Register 0
   SDRAM_GAP32(0x0204, 0x0240);
   u32 u32DBDFISTAT;    // 0x0240 - DFI status IF input register
   u32 u32DBDFICNT;     // 0x0244 - DFI status IF output register
   SDRAM_GAP32(0x0248, 0x0280);
   u32 u32DBPDLCK;      // 0x0280 - PHY unit lock register
   SDRAM_GAP32(0x0284, 0x0290);
   u32 u32DBPDRGA;      // 0x0290 - PHY unit address register
   SDRAM_GAP32(0x0294, 0x02A0);
   u32 u32DBPDRGD;      // 0x02A0 - PHY unit access register
   SDRAM_GAP32(0x02A4, 0x0304);
   u32 u32DBBS0CNT1;    // 0x0304 - Bus control unit 0 control register 1
   SDRAM_GAP32(0x0308, 0x0380);
   u32 u32DBWT0CNF0;    // 0x0380 - AXI port setting register 0
   SDRAM_GAP32(0x0384, 0x0390);
   u32 u32DBWT0CNF4;    // 0x0390 - AXI port setting register 4
   SDRAM_GAP32(0x0394, 0x0500);
   u32 u32DBSCHECNT0;   // 0x0500 - Scheduler setting register 0
   SDRAM_GAP32(0x0504, 0x4000);
   u32 u32DBRSTLCK;     // 0x4000 - DBSC Reset Lock register
   SDRAM_GAP32(0x4004, 0x4008);
   u32 u32DBRST;        // 0x4008 - DBSC Reset register

} * SDRAM__tpstDBSC3Reg;

typedef struct {
   uint32 u32DBTR0;  // SDRAM Timing Register 0
   uint32 u32DBTR1;
   /* u32DBTR2 does not exist */
   SDRAM_tstTimingCfg stTimingCfg;
   uint32 u32DBCONF0;
   uint32 u32DBRNK0;
   uint32 u32DBADJ0;
   uint32 u32DBADJ2;
   uint32 u32DBWT0CNF0;
   uint32 u32DBCALTR;
   SDRAM_tstRefreshCfg stRefreshCfg;
   uint32 u32DBRFEN;
} SDRAM_tstTimingConfig;

/* Struct of DDR3 PHY settings */
typedef struct {
   uint32 u32Phy0003A;
   uint32 u32Phy0003B;
   uint32 u32Phy0004;
   uint32 u32Phy0008;
   uint32 u32Phy0020;
   uint32 u32Phy0022;
   uint32 u32Phy0023;
   uint32 u32Phy0024;
   uint32 u32Phy0025;
   uint32 u32Phy0026;
   uint32 u32Phy0027;
   uint32 u32Phy0028;
   uint32 u32Phy0029;
   uint32 u32Phy0091;
   uint32 u32Phy0099;
} SDRAM_tstPhyConfig;

#endif /* __ASM_ARCH_D1H_SDRAM_H__ */
