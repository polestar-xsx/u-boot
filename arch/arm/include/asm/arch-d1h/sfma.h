#ifndef __ASM_ARCH_D1H_SFMA_H__
#define __ASM_ARCH_D1H_SFMA_H__
#include <asm/types.h>

void sfma_init(void);

/***************************************************************************
SFMA macro definitions
****************************************************************************/
/* SFMA Data Read Configuration 

   [31:29] Enable SFMA cache
   [19:16] Read Data Burst Length */
#define SFMA__nDataReadConfig                      0xe00f0301UL

/*
* SFMA channel mode selection:
* SFMA_nenDualChannel, SFMA_nenSingleChannel
*/
#define SFMA__nsfmaChannelMode  SFMA_nenDualChannel

/* SFMA Common Control Settings 

   MOIIO3[1:0] [23:22] always set to "01: Output value 1"
   IO3FV[1:0]  [15:14] always set to "01: Output value 1"
   CPOL        [3]     SPBSSL Negation Period SPBCLK Output Direction
   */
#define SFMA__nCommonCtrlCfg                       0x007f7300UL

/* CPHAT & CPHAR for SDR
    CPHAT       [6]     Output Shift: set to 0
    CPHAR       [5]     Output Shift: set to 1
*/
#define SFMA__nSDRCtrlCfg                          0x00000020UL

/* SFMA SSL delay configuration
    default - 0x00070007ul
              SPNDL: 2 clock cycles
              SLNDL: 1.5 clock cycles
              SCKDL: 1 clock cycle */
#define SFMA__nSSLDelay                            0x00070007UL

/* adaptation for of retries when polling 
   device ready condition. 1...255 */
#define SFMA__nDeviceReadyRetries                  10

/* SFMA Frequency Definition. Select the frequency based on the PLL divider used by your System.
   Base Clock = 520 Mhz, PLLdiv = 1/2, 1/3, 1/4, 1/6
   Valid Values :
   For PLL Divider 3, Clock = 173 Mhz  ==>  SFMA_nPLLDiv3_87MHz, SFMA_nPLLDiv3_44MHz, SFMA_nPLLDiv3_29MHz, SFMA_nPLLDiv3_22MHz, SFMA_nPLLDiv3_18MHz
   For PLL Divider 4, Clock = 130 Mhz  ==>  SFMA_nPLLDiv4_65MHz, SFMA_nPLLDiv4_33MHz, SFMA_nPLLDiv4_22MHz, SFMA_nPLLDiv4_16MHz
   For PLL Divider 6, Clock = 87 Mhz   ==>  SFMA_nPLLDiv6_44MHz, SFMA_nPLLDiv6_22MHz, SFMA_nPLLDiv6_14MHz
    */
/* PLL/3 = 173 Mhz */
#define SFMA_nPLLDiv3_87MHz     0x01    /* Baudrate = 173/ (2 * 1) = 86.50 */
#define SFMA_nPLLDiv3_44MHz     0x02    /* Baudrate = 173/ (2 * 2) = 43.25 */
#define SFMA_nPLLDiv3_29MHz     0x03    /* Baudrate = 173/ (2 * 3) = 28.80 */
#define SFMA_nPLLDiv3_22MHz     0x04    /* Baudrate = 173/ (2 * 4) = 21.62 */
#define SFMA_nPLLDiv3_18MHz     0x05    /* Baudrate = 173/ (2 * 5) = 17.30 */

/* PLL/4 = 130 Mhz */
#define SFMA_nPLLDiv4_65MHz     0x21    /* Baudrate = 130/ (2 * 1) = 65 */
#define SFMA_nPLLDiv4_33MHz     0x22    /* Baudrate = 130/ (2 * 2) = 32.5 */
#define SFMA_nPLLDiv4_22MHz     0x23    /* Baudrate = 130/ (2 * 3) = 21.66 */
#define SFMA_nPLLDiv4_16MHz     0x24    /* Baudrate = 130/ (2 * 4) = 16.25 */

/* PLL/6 = 87 Mhz */
#define SFMA_nPLLDiv6_44MHz     0x31    /* Baudrate = 87/ (2 * 1) = 43.25 */
#define SFMA_nPLLDiv6_22MHz     0x32    /* Baudrate = 87/ (2 * 2) = 21.75 */
#define SFMA_nPLLDiv6_14MHz     0x33    /* Baudrate = 87/ (2 * 3) =  14.50 */

/* Channel mode selection */
#define SFMA_nenSingleChannel   0
#define SFMA_nenDualChannel     1

/* Write protection code */
#define SFMA__nWPCode                          0xa5000000UL

/* Protected register unlock */
#define SFMA__nUnlockSequence                  0x000000a5UL

/* Port drive strength options */
#define SFMA__nPDSCFast                         0
#define SFMA__nPDSCSlow                         1

/* NULL definitions */
#define SFMA__nU8NULL                          0x00U
#define SFMA__nU8REVNULL					    0xffU
#define SFMA__nU16NULL                         0x0000U
#define SFMA__nU32NULL					        0x00000000UL
#define SFMA__nU32REVNULL				        0xffffffffUL

/* SPI Mode Enable Settings */
/* Only command and transfer data is enabled 1-bit 
   Read data = 64-bits, 32 bits per channel */
#define SFMA__nBusCfg_Cmd_Data                 0x0000400fUL
/* 64 - bits read data, 32 bits per channel */
#define SFMA__nBusCfg_Data                     0x0000000fUL

/* SPI Mode Control */
/* Start read-only transfer with CS disabled after operation*/
#define SFMA__nSMStartRdCSDs                   0x00000105UL
/* Start read-only transfer with CS enabled after operation*/
#define SFMA__nSMStartRdCSEn                   0x00000005UL

/* sampling point value for error */
#define SFMA__nErrorSamplePoint                0xffffffffUL

/* SFMA macro reset at bit 12 */
#define SFMA__nSwResetBit                      0x00001000UL

/* Extended Address settings */
#define SFMA__nBit2400Enable                   0x00000000UL
#define SFMA__nBit2500Enable                   0x00000001UL
#define SFMA__nBit2600Enable                   0x00000002UL
#define SFMA__nBit2700Enable                   0x00000003UL
#define SFMA__nBit2800Enable                   0x00000004UL

/* port drive strngth */
#define SFMA__nIOCTLR_ODSCMask                 0x55555fffUL

/* common flash commands */
#define SFMA__nCmdWREN                         0x06
#define SFMA__nCmdNormalRead                   0x03
#define SFMA__nCmdNormalRead4B                 0x13
#define SFMA__nCmdReadID                       0x9f

/* register bit locations */
#define SFMA__nRegBitWREN                      0x02
#define SFMA__nRegBitWIP                       0x01
#define SFMA__nRegSRVolatileMask               0xfc

/* option data enable */
#define SFMA__n1byteOpData                     0x8
#define SFMA__n2byteOpData                     0xc

/* byte shifting */
#define SFMA__n3byteShift                      24
#define SFMA__n2byteShift                      16
#define SFMA__n1byteShift                      8

/* DRCR RCF Clear Cache */
#define SFMA__nCacheClearAll                   1

/* CMNCR Data Bus Size Mask*/
#define SFMA__nBusSizeMask                     0xFFFFFFFEUL

/* Addressing mode */
#define SFMA__n24bitsEnable                    0x7
#define SFMA__n32bitsEnable                    0xf

/* Frame bytes per channel */
#define SFMA__n4bytePerChannel                 0x0000000fUL
#define SFMA__n2bytePerChannel                 0x0000000cUL
#define SFMA__n1bytePerChannel                 0x00000008UL

/* SFMA register configuration defaults */
#define SFMA__nSPODLY_NoDelay                  0xa5000000UL     
#define SFMA__nSPODLY_WithDelay                0xa5001111UL
#define SFMA__nCKDLYOC_NoShift                 0xa5000000UL 
#define SFMA__nCKDLYOC_PllDiv3                 0xa5030000UL 
#define SFMA__nCKDLYOC_PllDiv4                 0xa5050000UL 
#define SFMA__nSMCR_EnableTx                   0x00000002UL
#define SFMA__nSMCR_EnableRx                   0x00000004UL                        
#define SFMA__nSMCR_EnableNeg                  0x00000100UL
#define SFMA__nSMCR_DisableNeg                 0xfffffeffUL
#define SFMA__nSMCR_StartXfer                  0x00000001UL
#define SFMA__nSMCR_ExitCM                     0x00ff00ffUL
#define SFMA__nSMENR_COP                       0x00005000UL
#define SFMA__nDRDRENR_SDR                     0x00000000UL
#define SFMA__nDRDRENR_DDR                     0x00000101UL
#define SFMA__nDRCMR_NRead                     0x00030000UL
#define SFMA__nCMNCR_Dual                      0x00000001UL
#define SFMA__nDRENR_4init                     0x0222c000UL
#define SFMA__nDRENR_1init                     0x0020c000UL
#define SFMA__nDRENR_1bit                      0x00004700UL
#define SFMA__nDRENR_1byteOpdData              0x00000080UL
#define SFMA__nDRENR_1bitOpdData               0xffcfffffUL
#define SFMA__nDRENR_24BitAddress              0x00000700UL
#define SFMA__nDRENR_32BitAddress              0x00000f00UL
#define SFMA__nDROPR_Default                   0x00000000UL
#define SFMA__nDRDMode                         0x00000000UL
#define SFMA__nSPIMode                         0x80000000UL

/* Ports configuration */
#define SFMA__nPFC_IPSR_Default                0x01ff8000UL
#define SFMA__nPFC_IPSR_DefaultInv             0xfe007fffUL
#define SFMA__nPFC_GPSR_Default                0x00ffc000UL
#define SFMA__nPFC_IOCTR_Fast                  0xaaaaa000UL
#define SFMA__nPFC_IOCTR_Slow                  0x55555fffUL

/* SFMA power reset/set address */
#define SFMA__nSwResetSetAddr                  0xe61501ccUL
#define SFMA__nSwResetClearAddr                0xe615095cUL

/* IO signal levels */
#define SFMA__nSignalLevelMask                 0xFF0000FFUL
#define SFMA__nSignalLevel_0_HiZ               0x003F3300UL
#define SFMA__nSignalLevel_1_HiZ               0x007F7300UL
#define SFMA__nSignalLevel_AllHiZ              0x00FFF300UL

/* cycles */
#define SFMA__nCycles3OpBytes                  6
#define SFMA__nCycles2OpBytes                  4
#define SFMA__nCycles1OpByte                   2

/* Macro to fill the gaps within structures */
#define SFMA__nReserved(start,finish)          u32 u32__##start##_##finish[((finish)-(start))/4]


/* Data Read Enable Setting Register Configuration */
/* optional command, none */
#define SFMA__nOpCommandByte           0

/* 32-bit extended upper address fixed value */
#define	SFMA__nEUAFixedValue           0x00

/* dummy cycle reconfiguration */
#define SFMA__nMinDCReconfig           9
#define SFMA__nMaxDCReconfig           16

/* dummy cycle adjustment */
#define SFMA__n8Cycles                 8

/* 32-bit external address valid range configuration
based on the maximum adddressable memory */
#define SFMA__nValidRange24_0          0x00000000u
#define SFMA__nValidRange25_0          0x00000001u
#define SFMA__nValidRange26_0          0x00000002u
#define SFMA__nValidRange27_0          0x00000003u
#define SFMA__nValidRange28_0          0x00000004u

/* dummy cycle configuration */
#define SFMA__nDummyCycleDisable       0xffff7fffu
#define SFMA__nDummyCycleEnable        0x00008000u
/* command enable, 0/1 */
#define SFMA__nCommandEnable           0x00004000u			
/* optional command enable, 0/1 */
#define SFMA__nOpCommandDisable        0xffffefffu

/* option data enable, 0/1 */
#define SFMA__nOpDataDisable           0xffffff7fu
/* enable 8-bit OPD3 */
#define SFMA__nOpData1byteEnable       0x00000080u
#define SFMA__nOpData2byteEnable       0x000000c0u
#define SFMA__nOpData3byteEnable       0x000000e0u
#define SFMA__nOpData4byteEnable       0x000000f0u

/* Addess enable configuration */
#define SFMA__n32bitAddressing         0x00000f00u
#define SFMA__n24bitAddressing         0x00000700u

/* option data DDR enable */
#define SFMA__nOpDataDDREnable			0x00000000u

/* Data Read DDR Enable Register */
/* address DDR enable */
#define SFMA__nAddressDDREnable		0x00000100u
/* data read DDR enable */
#define SFMA__nDataReadDDREnable       0x00000001u

/* 4-bit data read size */
#define SFMA__nDataReadSize            0x00000000u
/* 4-bit address size */
#define SFMA__nAddressSize				0x00000000u
/* 4-bit dummy cycle size */
#define SFMA__nDummyCycleSize			0x00020000u
/* option data bit size */
#define SFMA__nOpDataSizebit           0x00000000u

/***************************************************************************
SFMA internal type definitions
****************************************************************************/

/* Possible sample points for 65 MHz */
typedef enum
{
    SFMA_PT_50004 = 0x50004,
    SFMA_PT_50003 = 0x50003,
    SFMA_PT_50002 = 0x50002,
    SFMA_PT_50001 = 0x50001,
    SFMA_PT_50000 = 0x50000
}SFMA__enSamplePoints65MHz;

/* Possible sample points for 87 MHz */
typedef enum
{
    SFMA_PT_30002 = 0x30002,
    SFMA_PT_30001 = 0x30001,
    SFMA_PT_30000 = 0x30000
}SFMA__enSamplePoints87MHz;

/* Structure of SFMA DRCR register */
typedef union
{
    u32 u32word;
    struct
    {
        u32 bi32SSLE : 1;            /* SPBSSL Negation        */
        u32 bi32Reserved0 : 7;       /* Reserved               */
        u32 bi32RBE : 1;             /* Read Burst             */
        u32 bi32RCF : 1;             /* Read cache Flush       */
        u32 bi32Reserved1 : 6;       /* Reserved               */
        u32 bi32RBURST : 4;          /* Read Data Burst Length */
        u32 bi32Reserved2 : 4;       /* Reserved               */
        u32 bi32SSLN : 1;            /* SPBSSL Negation        */
        u32 bi32Reserved3 : 4;       /* Reserved               */
        u32 bi32BFM : 3;             /* Enable SFMA cache      */
    }bits;
}SFMA__tunDRCR;

/* Structure of SFMA DRCMR register */
typedef union
{
    u32 u32word;
    struct
    {
        u32 bi32OCMD : 8;            /* Optional Command */ 
        u32 bi32Reserved0 : 8;       /* Reserved         */
        u32 bi32CMD : 8;             /* Command          */
        u32 bi32Reserved1 : 8;       /* Reserved         */
    }bits;
}SFMA__tunDRCMR;

/* Structure of SFMA SMDMCR register */
typedef union
{
    u32 u32word;
    struct
    {
        u32 bi32DMCYC : 3;           /* Number of Dummy Cycles */
        u32 bi32Reserved0 : 13;      /* Reserved               */
        u32 bi32DMDB : 2;            /* Dummy Cycle Bit Size   */
        u32 bi32Reserved1 : 14;      /* Reserved               */
    }bits;
}SFMA__tunSMDMCR;

/* Structure of SFMA SMENR register */
typedef union
{
    u32 u32word;
    struct
    {
        u32 bi32SPIDE : 4;           /* Transfer Data Enable      */
        u32 bi32OPDE : 4;            /* Option Data Enable        */
        u32 bi32ADE : 4;             /* Address Enable            */
        u32 bi32OCDE : 1;            /* Optional Command Enable   */
        u32 bi32Reserved0 : 1;       /* Reserved                  */
        u32 bi32CDE : 1;             /* Command Enable            */
        u32 bi32DME : 1;             /* Dummy Cycle Enable        */
        u32 bi32SPIDB : 2;           /* Transfer Data Bit Size    */
        u32 bi32Reserved1 : 2;       /* Reserved                  */
        u32 bi32OPDB : 2;            /* Option Data Bit Size      */
        u32 bi32Reserved2 : 2;       /* Reserved                  */
        u32 bi32ADB : 2;             /* Address Bit Size          */
        u32 bi32Reserved3 : 2;       /* Reserved                  */
        u32 bi32OCDB : 2;            /* Optional Command Bit Size */
        u32 bi32CDB : 2;             /* Command Bit Size          */
    }bits;
}SFMA__tunSMENR;

/* Structure of SFMA CMNCR register */
typedef union
{
    u32 u32word;
    struct
    {
        u32 bi32BSZ : 2;             /* Data Bus Size                                     */
        u32 bi32Reserved0 : 1;       /* Reserved                                          */
        u32 bi32CPOL : 1;            /* SPBSSL Negation Period SPBCLK Output Direction    */
        u32 bi32SSLP : 1;            /* SPBSSL Signal Polarity                            */
        u32 bi32CPHAR : 1;           /* Input Latch                                       */
        u32 bi32CPHAT : 1;           /* Output Shift                                      */
        u32 bi32Reserved1 : 1;       /* Reserved                                          */
        u32 bi32IO0FV : 2;           /* SPBIO00, SPBIO01 Fixed Value for 1-bit Size Input */
        u32 bi32Reserved2 : 2;       /* Reserved                                          */
        u32 bi32IO2FV : 2;           /* SPBIO20, SPBIO21 Fixed Value for 1-bit/2-bit Size */
        u32 bi32IO3FV : 2;           /* SPBIO30, SPBIO31 Fixed Value for 1-bit/2-bit Size */
        u32 bi32MOIIO0 : 2;          /* SPBSSL Output Idle Value Fix SPBIO00, SPBIO01     */
        u32 bi32MOIIO1 : 2;          /* SPBSSL Output Idle Value Fix SPBIO10, SPBIO11     */
        u32 bi32MOIIO2 : 2;          /* SPBSSL Output Idle Value Fix SPBIO20, SPBIO21     */
        u32 bi32MOIIO3 : 2;          /* SPBSSL Output Idle Value Fix SPBIO30, SPBIO31     */
        u32 bi32SFDE : 1;            /* Data Swap Setting for Serial Flash Memory         */
        u32 bi32Reserved3 : 6;       /* Reserved                                          */
        u32 bi32MD : 1;              /* Operating Mode Switch                             */
    }bits;
}SFMA__tunCMNCR;

/* Structure of SFMA CMNSR register */
typedef union
{
    u32 u32word;
    struct
    {
        u32 bi32TEND : 1;            /* Transfer End Flag  */
        u32 bi32SSLF : 1;            /* SPBSSL Pin Monitor */
        u32 bi32Reserved1 : 30;      /* Reserved           */
    }bits;
}SFMA__tunCMNSR;

/* Structure of SFMA RDR register */
typedef union
{
    u32 u32word;
    struct
    {
        u32 bi32LL : 8;      /* lower byte of the lower nibble  */
        u32 bi32LH : 8;      /* higherbyte of the lower nibble  */
        u32 bi32HL : 8;      /* lower byte of the higher nibble */
        u32 bi32HH : 8;      /* higherbyte of the higher nibble */  
    }bits;

}SFMA__tunRDR;

/* Structure of SFMA SMCR register */
typedef union
{
    u32 u32word;
    struct
    {
        u32 bi32SPIE : 1;            /* SPI Data Transfer Enable */
        u32 bi32SPIWE : 1;           /* Data Write Enable        */
        u32 bi32SPIRE : 1;           /* Data Read Enable         */
        u32 bi32Reserved0 : 5;       /* Reserved                 */
        u32 bi32SSLKP : 1;           /* SPBSSL Signal Level      */
        u32 bi32Reserved1 : 23;      /* Reserved                 */
    }bits;
}SFMA__tunSMCR;


/* Structure of SFMAO registers */
typedef struct {
    SFMA__tunCMNCR unCMNCR;        /* 0x00 - Common control register                     */
    u32 u32SSLDR;                /* 0x04 - SSL delay register                          */
    u32 u32SPBCR;                /* 0x08 - Bit rate register                           */
    SFMA__tunDRCR unDRCR;          /* 0x0C - Data read control register                  */
    SFMA__tunDRCMR unDRCMR;        /* 0x10 - Data read command setting register          */
    u32 u32DREAR;                /* 0x14 - Data read extended address setting register */
    u32 u32DROPR;                /* 0x18 - Data read option setting register           */
    u32 u32DRENR;                /* 0x1C - Data read enable setting register           */
    SFMA__tunSMCR unSMCR;          /* 0x20 - SPI mode control register                   */
    u32 u32SMCMR;                /* 0x24 - SPI mode command setting register           */
    u32 u32SMADR;                /* 0x28 - SPI mode address setting register           */
    u32 u32SMOPR;                /* 0x2C - SPI mode option setting register            */
    SFMA__tunSMENR   unSMENR;      /* 0x30 - SPI mode enable setting register            */
    SFMA__nReserved(0x0034, 0x0038);
    SFMA__tunRDR unSMRDR0;         /* 0x38 - SPI mode read data register 0               */
    SFMA__tunRDR unSMRDR1;         /* 0x3C - SPI mode read data register 1               */
    u32 u32SMWDR0;               /* 0x40 - SPI mode write data register 0              */
    u32 u32SMWDR1;               /* 0x44 - SPI mode write data register 1              */
    SFMA__tunCMNSR   unCMNSR;      /* 0x48 - Common status register                      */
    SFMA__nReserved(0x004C, 0x0050);
    u32 u32CKDLY;                /* 0x50 - Clock phase adjust register                 */
    SFMA__nReserved(0x0054, 0x0058);
    u32 u32DRDMCR;               /* 0x58 - Data read dummy cycle setting register      */
    u32 u32DRDENR;               /* 0x5C - Data read DDR enable register               */
    SFMA__tunSMDMCR unSMDMCR;      /* 0x60 - SPI mode dummy cycle setting register       */
    u32 u32SMDRENR;              /* 0x64 - SPI mode DDR enable register                */
    u32 u32SPODLY;               /* 0x68 - Output data delay register                  */
} SFMA_tstReg;

typedef struct {
    u32	u32Pmmr;                    /* 0x00         */
    u32  u32Gpsr[7];                 /* 0x04 - 0x1F  */
    u32  u32Ipsr[9];                 /* 0x20 - 0x43  */
    SFMA__nReserved(0x0044, 0x0060);
    u32	u32IOCTRL[4];               /* 0x60 - 0x6F  */  
    SFMA__nReserved(0x0070, 0x0090);   /* 0x70 - 0x60  */
    u32	u32ModSel;                  /* 0x90         */
    u32	u32ModSel2;                 /* 0x94         */
    SFMA__nReserved(0x0098, 0x0100);   /* 0x98 - 0x100 */    
} SFMA__tstPfcReg;

#endif /* __ASM_ARCH_D1H_SFMA_H__ */
