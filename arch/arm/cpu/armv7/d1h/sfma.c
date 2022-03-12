#include <common.h>
#include <asm/io.h>
#include <asm/arch/base.h>
#include <asm/arch/clock.h>
#include <asm/arch/timer.h>
#include <asm/arch/sfma.h>

/* Mapped to PFC Register */
volatile SFMA__tstPfcReg * SFMA__pstPFC = (volatile SFMA__tstPfcReg *)(PFC_BASE);
volatile SFMA__tstReg * SFMA__pstReg = (volatile SFMA__tstReg *)(SFMA_BASE)
/* Intialize all SFMA Ports */
void sfma__ioinit(void)
{
    u32 u32TmpReg;

    /* SFMA IO Lines
       Pin Name    GPn[x]=1 Function IPS=0
       SFMA0CLK    GP2_14/MD0
       SFMA0SSL    GP2_15/MD14
       SFMA0O00    GP2_16 
       SFMA0O10    GP2_17 
       SFMA0O20    GP2_18 
       SFMA0O30    GP2_19 
       SFMA0O01    GP2_20 
       SFMA0O11    GP2_21 
       SFMA0O21    GP2_22 
       SFMA0O31    GP2_23 */

    /* Peripheral function selection */
    /* SFMA Pins on IP4[24:15]
       0x01ff8000ul : 0000 0001 1111 1111 1000 0000 0000 0000 */
    u32TmpReg = SFMA__pstPFC->u32Ipsr[4];
    u32TmpReg &= SFMA__nPFC_IPSR_DefaultInv;   /* All SFMA pins to 0 leaving others to its current values */
    SFMA__pstPFC->u32Pmmr = (~u32TmpReg);      /* write inverse value into PPMR */
    SFMA__pstPFC->u32Ipsr[4] = u32TmpReg;      /* write */

    /* GPIO function selection */
    u32TmpReg = SFMA__pstPFC->u32Gpsr[2];
    u32TmpReg |= SFMA__nPFC_GPSR_Default;
    SFMA__pstPFC->u32Pmmr = (~u32TmpReg);      /* write inverse value into PPMR */
    SFMA__pstPFC->u32Gpsr[2] = u32TmpReg;      /* write */

    /* setting IOCTRL0 port drive strength */
    u32TmpReg = SFMA__pstPFC->u32IOCTRL[0] & SFMA__nIOCTLR_ODSCMask;
    u32TmpReg |= SFMA__nPortDriveStrength;
    SFMA__pstPFC->u32Pmmr = (~u32TmpReg);      /* write inverse value into PPMR */
    SFMA__pstPFC->u32IOCTRL[0] = u32TmpReg;    /* write */
    
    /* SFMA macro reset SRCR7/SRSTCLR7 Bit 12 
       software reset register 7       SRCR7    @ 0xe61501cc
       software reset clear register 7 SRSTCLR7 @ 0xe615095c */
    u32TmpReg = *((volatile unsigned long*)SFMA__nSwResetSetAddr);
    u32TmpReg |= SFMA__nSwResetBit;
    /* Power RESET_SET */
    *((volatile unsigned long*)SFMA__nSwResetSetAddr) = u32TmpReg;
    __udelay(1000);
    u32TmpReg = *((volatile unsigned long*)SFMA__nSwResetClearAddr);
    u32TmpReg |= SFMA__nSwResetBit;
    /* Power RESET_CLEAR */
    *((volatile unsigned long*)SFMA__nSwResetClearAddr) = u32TmpReg;
}

void sfma_deactivatebus(void)
{
    u16 u8CheckCtr = 0xff;
    /* SSLN negation in case of active SSL */
    SFMA__pstReg->unDRCR.bits.bi32SSLN = 1;

    /* a counter is added in case the register does  not change immediately */
    while ((SFMA__pstReg->unCMNSR.bits.bi32SSLF != 0) && (--u8CheckCtr));
}

/* Initialize serial flash */
void sfma__initflashcfg(void)
{
    u8 u8Idx;
    u16 u16Dly = 0x1fff;
    /* Data Read Configuration */
    SFMA__pstReg->unDRCR.u32word = SFMA__nDataReadConfig;
    /* Common configuration */
    SFMA__pstReg->unCMNCR.u32word = (SFMA__nCommonCtrlCfg | SFMA__nSPIMode | SFMA__nSDRCtrlCfg | (uint32)SFMA__nsfmaChannelMode);
    /* SSL delay configuration */
    SFMA__pstReg->u32SSLDR = SFMA__nSSLDelay;
#if (CLK__nCPG_SFMA_EXSRC_Cfg == 0x1UL)
    /* Set SPI Mode frequency @ 43.5 MHz default */
    SFMA__pstReg->u32SPBCR = ((uint32)((SFMA_nPLLDiv3_44MHz & 0x0F) << 8));
    /* Set delay/clock settings */
    SFMA__pstReg->u32SPODLY = (SFMA__nSPODLY_NoDelay);
    SFMA__pstReg->u32CKDLY = (SFMA__nCKDLYOC_PllDiv3);

#elif (PMAN__nCPG_SFMA_EXSRC_Cfg == 0x2UL)
    /* Set SPI Mode frequency @ 33 MHz default */
    SFMA__pstReg->u32SPBCR = ((uint32)((SFMA_nenFreq033MHz & 0x0F) << SFMA__n1byteShift));
    /* Set delay/clock settings */
    SFMA__pstReg->u32SPODLY = (SFMA__nSPODLY_NoDelay);
    SFMA__pstReg->u32CKDLY = (SFMA__nCKDLYOC_PllDiv4);

#endif
    /* ensure there is no ongoing transfer */
    while ((SFMA__pstReg->unCMNSR.bits.bi32TEND != 0x1u) && (--u16Dly));

    /* Reset Flash from Continuous Read Mode (RAW MODE)
    ------------------------------------------------
    This routine sends 64 high data bits to the SPI flash to mark the end of a previous
    continuous read configuration(so that the device accepts valid SPI commands again.
    It is necessary to do it this way(because D1Mx adapter boards do not connect the
    RESET pin to board reset(so the flash device must always be considered in an un-
    defined state during power-up. */
    for (u8Idx = 0; u8Idx < 16; u8Idx++)
    {
        /* Set Command to "Exit Continous Read Mode" (0xffff) */
        SFMA__pstReg->u32SMCMR = (SFMA__nSMCR_ExitCM);
        /* - Command data width is 1-bit
        - Optional Command data width is 1-bit
        - Enable Command
        - Enable Optional Command */
        SFMA__pstReg->unSMENR.u32word = (SFMA__nSMENR_COP);
        /* Send Command */
        SFMA__pstReg->unSMCR.u32word = (SFMA__nSMCR_StartXfer);
        while ((SFMA__pstReg->unCMNSR.bits.bi32TEND != 0x1u) && (--u16Dly));
    }

    __udelay(1000);
}

void sfma_init(void)
{
    /* boot up delay after 3V3 power is applied to serial flash and
       before the fist access. see SFMA__nDevicePowerUpDelay in ci header 
       -- 10 milliseconds boot-up time */
    __udelay(20000);

    /* Intialize all SFMA Ports */
    sfma__ioinit();

    /* reset CS activation */
    sfma_deactivatebus();

    /* perform flash configuration */
    sfma__initflashcfg();
}