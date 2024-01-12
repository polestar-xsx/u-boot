#include <common.h>
#include <asm/io.h>
#include <asm/arch/base.h>
#include <asm/arch/clock.h>
#include <asm/arch/timer.h>

volatile CLK_tstD1H_ClkCtrl * CLK__xCPG = (volatile CLK_tstD1H_ClkCtrl *)(CLK__D1H_CLOCK_CTRL);


void plls_init(void)
{
    CLK__tunPllCR unPllCR;   /* Temporary variable for read-modify-write */
/*init pll0*/
    /* Preserve CKSEL by read-modify-write operation */
      unPllCR.u32word        = CLK__xCPG->u32Pll0cr;
      unPllCR.bits.bi32STC   = CLK__nCPG_PLL0_STC_Cfg;
      unPllCR.bits.bi32P     = CLK__nCPG_PLL0_P_Cfg;
      CLK__xCPG->u32Pll0cr  = unPllCR.u32word;
    /* Changing PLL SSCG mode */
      /* a. Assert clock stop */
    CLK__xCPG->u32Pllecr &= ~(CLK__nPLLEnable);  //Disable pll0
    /* b. Change the SSCG setting in the PLL0CR1 while keeping frequency dithering disabled */
    CLK__xCPG->u32Pll0cr1 = CLK__nCPG_PLL0CR1_Cfg | CLK__nRstn_Msk;
    /* c. Enable SSCG setting as configured */
    CLK__xCPG->u32Pll0cr1 = CLK__nCPG_PLL0CR1_Cfg;
    /* d. de-assert clock stop */
    CLK__xCPG->u32Pllecr |= (CLK__nPLLEnable);
    while((CLK__xCPG->u32Pllecr & CLK__nPLL0Locked_Msk) == 0)
    {}
    __udelay(300UL);/* wait 300us after changing PLL SSCG mode*/
/*Init pll1*/
    CLK__xCPG->u32Pllecr |= (CLK__nPLLEnable << 1);

    /* Wait for the PLL to achieve lock by polling the PLL LOCK bit. */
    while((CLK__xCPG->u32Pllecr & CLK__nPLL1Locked_Msk) == 0)
    {}

/*Init plls */
    /* Changing PLL SSCG mode */
    /* a. Assert clock stop */
    CLK__xCPG->u32Pllecr &= ~ (CLK__nPLLEnable << 4);
    /* b. Change the SSCG setting in the PLLSCR1 while keeping frequency dithering disabled */
    CLK__xCPG->u32Pllscr1  = CLK__nCPG_PLLSCR1_Cfg | CLK__nRstn_Msk;
    /* c. Enable SSCG setting as configured */
    CLK__xCPG->u32Pllscr1  = CLK__nCPG_PLLSCR1_Cfg;
    /* d. de-assert clock stop */
    CLK__xCPG->u32Pllecr |= (CLK__nPLLEnable << 4);

    /* Wait for the PLL to achieve lock by polling the PLL LOCK bit. */
    while((CLK__xCPG->u32Pllecr & CLK__nPLLSLocked_Msk) == 0)
    {}

    __udelay(300UL);   /* 10.1.5.3(5): wait 300us after changing PLL SSCG mode*/
/*Init pll3*/
    (*(volatile u32 *)(CLK__nDBRSTLCK_Addr)) = CLK__nDisableDbscResetLock;   /* Disable the DDR3-SDRAM Memory Controller (DBSC) reset lock */
    (*(volatile u32 *)(CLK__nDBRST_Addr))    = 0x0UL;   /* De-assert DBSC reset */
    (*(volatile u32 *)(CLK__nDBRSTLCK_Addr)) = 0x0UL;   /* DBSC reset lock enabled */
    /* 1. DBSC3 mstp ON, SMSTPCR4[30] = 1 */
    CLK__xCPG->u32Smstpcr4 |= CLK__nDBSC3_Msk;
    /* 2. DBSC3 soft reset ON, SRCR4[30] = 1 */
    (*(volatile u32 *)(CLK__nSRCR4_Addr))   |= CLK__nDBSC3_Msk;   /* Assert DBSC3-soft-reset */

    /* 3. PLL3 setting */
    /* Preserve CKSEL by read-modify-write operation */
    unPllCR.u32word        = CLK__xCPG->u32Pll3cr;
    unPllCR.bits.bi32CfgEn = CLK__nCPG_PLL3_CfgEN_Cfg;
    unPllCR.bits.bi32STC   = CLK__nCPG_PLL3_STC_Cfg;
    unPllCR.bits.bi32P     = CLK__nCPG_PLL3_P_Cfg;
    CLK__xCPG->u32Pll3cr  = unPllCR.u32word;

    CLK__xCPG->u32Pllecr |= (CLK__nPLLEnable << 3);

    /* Wait for the PLL to achieve lock by polling the PLL LOCK bit. */
    while((CLK__xCPG->u32Pllecr & CLK__nPLL3Locked_Msk) == 0)
    {}

    /* 4. DBSC3 mstp OFF, SMSTPCR4[30] = 0 */
    CLK__xCPG->u32Smstpcr4 &= (~CLK__nDBSC3_Msk);
    /* 5. DBSC3 soft reset OFF, SRSTCLR4[30] = 1 */
    (*(volatile u32 *)(CLK__nSRSTCLR4_Addr)) |= CLK__nDBSC3_Msk;
}


void clocktree_init(void)
{
   CLK__tunCkscCR2 unTemp;   /* Temporary variables for read-modify-write */
   
   /* Configure Clock Pulse Generator registers */
   while(CLK__xCPG->u32Frqcrb & CLK__nFrqcrbKick_Msk)
   {
      /* When the KICK bit is read as 1, do not modify FRQCRB */
   };
   CLK__xCPG->u32Frqcrb      = CLK__nCPG_FRQCRB_Cfg;     
   CLK__xCPG->u32Frqcrb     |= CLK__nFrqcrbKick_Msk;   /* Activate the FRQCRB settings */
   CLK__xCPG->u32Mmc0ckcr    = CLK__nCPG_MMC0CKCR_Cfg;   
   CLK__xCPG->u32Rcanckcr    = CLK__nCPG_RCANCKCR_Cfg;   

   /* Select PLL1 as clock source and then modify the Z2CKSEL1 */
   unTemp.u32word             = CLK__xCPG->u32Cksccr2;   /* Read the CKSCCR2 register */
   CLK__xCPG->u32Cksccr     &= ~ (CLK__nZ2Sel_Msk);
   __udelay(10UL);   /* 10.1.5.4: Wait 10us after changing between non-SSCG PLL1 and SSCG PLLS clock  via the CKSCCR register */
   unTemp.bits.bi32Z2CkSel1   = CLK__nCPG_Z2CKSEL1_Cfg;   /* Modify the Z2CKSEL1 */
   CLK__xCPG->u32Cksccr2     = unTemp.u32word;   /* Write into the CKSCCR2 register */

   /* Select PLLS as clock source and then modify the Z2CKSEL0 */
   CLK__xCPG->u32Cksccr     |= CLK__nZ2Sel_Msk;
   __udelay(10UL);   /* 10.1.5.4: Wait 10us after changing between non-SSCG PLL1 and SSCG PLLS clock via the CKSCCR register */
   unTemp.bits.bi32Z2CkSel0   = CLK__nCPG_Z2CKSEL0_Cfg;   /* Modify the Z2CKSEL1 */
   CLK__xCPG->u32Cksccr2     = unTemp.u32word;

   CLK__xCPG->u32Cksccr      = CLK__nCPG_CKSCCR_Cfg;     
   __udelay(10UL);   /* 10.1.5.4 &10.1.5.5: Wait 10us after changing CPU, SYS2, SYS3 & SYS5 clocks */

   /* 10.1.5.6: Stop the clock before change the setting of the related divider */
   CLK__xCPG->u32Z2dclkcr    |= CLK__nCKSTP_Mask;
   CLK__xCPG->u32Z3dclkcr    |= CLK__nCKSTP_Mask;
   CLK__xCPG->u32Pix1clkcr   |= CLK__nCKSTP_Mask;
   CLK__xCPG->u32Pix2clkcr   |= CLK__nPIX2CKSTP_Mask;
   CLK__xCPG->u32Pix3clkcr   |= CLK__nCKSTP_Mask;
   CLK__xCPG->u32Pix4clkcr   |= CLK__nCKSTP_Mask;

   /* Configure the clock sources and dividers */
   CLK__xCPG->u32Usbclkcr    = CLK__nCPG_USBCLKCR_Cfg;   
   CLK__xCPG->u32Z2dclkcr    = CLK__nCPG_Z2DCLKCR_Cfg;   
   CLK__xCPG->u32Z3dclkcr    = CLK__nCPG_Z3DCLKCR_Cfg;   
   CLK__xCPG->u32Pix1clkcr   = CLK__nCPG_PIX1CLKCR_Cfg;  
   CLK__xCPG->u32Pix2aclkcr  = CLK__nCPG_PIX2ACLKCR_Cfg; 
   CLK__xCPG->u32Pix2bclkcr  = CLK__nCPG_PIX2BCLKCR_Cfg; 
   CLK__xCPG->u32Pix2dclkcr  = CLK__nCPG_PIX2DCLKCR_Cfg; 
   CLK__xCPG->u32Pix2clkcr   = CLK__nCPG_PIX2CLKCR_Cfg;
   CLK__xCPG->u32Pix3aclkcr  = CLK__nCPG_PIX3ACLKCR_Cfg; 
   CLK__xCPG->u32Pix3clkcr   = CLK__nCPG_PIX3CLKCR_Cfg;  
   CLK__xCPG->u32Pix4aclkcr  = CLK__nCPG_PIX4ACLKCR_Cfg; 
   CLK__xCPG->u32Pix4clkcr   = CLK__nCPG_PIX4CLKCR_Cfg;  
   CLK__xCPG->u32Tpuclkcr    = CLK__nCPG_TPUCLKCR_Cfg;   
   CLK__xCPG->u32Tmuclkcr    = CLK__nCPG_TMUCLKCR_Cfg;   
   CLK__xCPG->u32Cmtclkcr    = CLK__nCPG_CMTCLKCR_Cfg;   
   CLK__xCPG->u32Sfmaclkcr   = CLK__nCPG_SFMACLKCR_Cfg;  
   __udelay(10UL);   /* 10.1.5.6: Wait 10us after changing dividers */

   /* Configure Module Stand-by Control Registers */
   CLK__xCPG->u32Smstpcr0    = CLK__nMSBC_SMSTPCR0_Cfg;
   CLK__xCPG->u32Smstpcr1    = CLK__nMSBC_SMSTPCR1_Cfg;
   CLK__xCPG->u32Smstpcr2    = CLK__nMSBC_SMSTPCR2_Cfg;
   CLK__xCPG->u32Smstpcr3    = CLK__nMSBC_SMSTPCR3_Cfg;
   CLK__xCPG->u32Smstpcr4    = CLK__nMSBC_SMSTPCR4_Cfg;
   CLK__xCPG->u32Smstpcr5    = CLK__nMSBC_SMSTPCR5_Cfg;
   CLK__xCPG->u32Smstpcr6    = CLK__nMSBC_SMSTPCR6_Cfg;
   CLK__xCPG->u32Smstpcr7    = CLK__nMSBC_SMSTPCR7_Cfg;
   CLK__xCPG->u32Smstpcr8    = CLK__nMSBC_SMSTPCR8_Cfg;
   CLK__xCPG->u32Smstpcr9    = CLK__nMSBC_SMSTPCR9_Cfg;
   CLK__xCPG->u32Smstpcr10   = CLK__nMSBC_SMSTPCR10_Cfg;
   CLK__xCPG->u32Smstpcr11   = CLK__nMSBC_SMSTPCR11_Cfg;

   CLK__xCPG->u32IntOscProc  = CLK__nProtCmdVal2;   /* protection unlock command */
   CLK__xCPG->u32IntOscProc2 = CLK__nReleaseWriteProtect;  /* set bit0=1 */
   CLK__xCPG->u32IntOscEncr  = CLK__nCPG_INTOSCENCR_Cfg;   /* set bit18=1 and bit0=1 */
   __udelay(20UL);   /* 10.1.4.31: wait 20us after enable/disable the IntOsc */

}

void clock_init(void)
{
    plls_init();
    clocktree_init();
}

/***************************************************************************
* Description         : This function returns the fEX frequency
* Implementation      : Determines the fEX frequency based on MD14 setting
* Return Value        : u32, frequency in Hz
****************************************************************************/
u32 clock_u32GetFrequencyFEX(void)
{
   volatile u32 * pu32ModeMR = (volatile u32 *)(MODEMR);

   u32 u32RetVal = MainOScillatorFreq;
   CLK__tunModeMR unModeMR;

   unModeMR.u32word = * pu32ModeMR;
   /* MD14 = L: fEX = 24 MHz
    * MD14 = H: fEX = 48 MHz */
   if (unModeMR.bits.bi32MD14 == 0)
   {
      u32RetVal = u32RetVal / 2U;
   }
   return u32RetVal;
}


/***************************************************************************
* Description         : This function returns the PLL1 frequency
* Implementation      : Calculates the PLL1 frequency based on settings in control register
* Return Value        : u32, frequency in Hz
****************************************************************************/
u32 clock_u32GetFrequencyPLL1(void)
{
   u64 u64RetVal;
   u32 u32Nr;
   u32 u32Mr;
   CLK__tunPllCR unPllCR;

   unPllCR.u32word = (CLK__xCPG->u32Pll1cr);
   u32Nr = unPllCR.bits.bi32STC + 1U;   /* get the PLL1 multiply factor, Nr = STC[6:0] + 1 */
   u32Mr = unPllCR.bits.bi32P + 1U;     /* get the PLL1 input clock divider Mr = P[1:0] + 1 */
   u64RetVal = (u64)clock_u32GetFrequencyFEX() * u32Nr / u32Mr;
   /* CKSEL PLL1 input clock selection
    * 0: MainOsc clock fEX / 1
    * 1: MainOsc clock fEX / 2 */
   if (unPllCR.bits.bi32CKSEL != 0)
   {
      u64RetVal = u64RetVal / 2U;
   }
   return (u32)u64RetVal;
}

/***************************************************************************
* Description         : This function returns the PLLS frequency
* Implementation      : Calculates the PLLS frequency based on settings in control register
* Return Value        : u32, frequency in Hz
****************************************************************************/
u32 clock_u32GetFrequencyPLLS(void)
{
   u64 u64RetVal;
   u32 u32Nr;
   u32 u32Mr;
   CLK__tunPllCR unPllCR;

   unPllCR.u32word = (CLK__xCPG->u32Pllscr);
   u32Nr = unPllCR.bits.bi32STC + 1U;   /* get the PLLS multiply factor, Nr = STC[6:0] + 1 */
   u32Mr = unPllCR.bits.bi32P + 1U;     /* get the PLLS input clock divider Mr = P[1:0] + 1 */
   u64RetVal = (u64)clock_u32GetFrequencyFEX() * u32Nr / u32Mr;
   /* CKSEL PLLS input clock selection
    * 0: MainOsc clock fEX / 2
    * 1: MainOsc clock fEX / 1 */
   if (unPllCR.bits.bi32CKSEL == 0U)
   {
      u64RetVal = u64RetVal / 2U;
   }
   return (u32)u64RetVal;
}

/***************************************************************************
* Description         : This function returns the SYS3 frequency
* Implementation      : Calculates the SYS3 frequency based on settings in control register
* Return Value        : u32, frequency in Hz
****************************************************************************/
u32 clock_u32GetFrequencySYS3(void)
{
   u32 u32RetVal;
   u32 u32Zxsel;

   u32Zxsel = (CLK__xCPG->u32Cksccr & CLK__nZXSel_Msk);  /* mask out ZXSEL from PLL1 Control Register */
   if(u32Zxsel == 0U)
   {
      u32RetVal = clock_u32GetFrequencyPLL1() / 3U;
   }
   else
   {
      u32RetVal = clock_u32GetFrequencyPLLS() / 3U;
   }
    return u32RetVal;
}

/***************************************************************************
* Description         : This function returns the S frequency,
*                       clock domain for HSCIF, SCIF, ADG
* Implementation      : Returns the divided fPLL1CLK
* Return Value        : u32, frequency in Hz
****************************************************************************/
u32 clock_u32GetFrequencyS(void)
{
   return clock_u32GetFrequencyPLL1() / 6U;
}

/***************************************************************************
* Description         : This function returns the S frequency
* Implementation      : Returns the divided fSYS3
* Return Value        : u32, frequency in Hz
****************************************************************************/
u32 clock_u32GetFrequencyZS(void)
{
   return clock_u32GetFrequencySYS3() / 2U;
}

/***************************************************************************
* Description         : This function returns the SFMA frequency
* Implementation      : Returns the divided fSYS3
* Return Value        : u32, frequency in Hz
****************************************************************************/
u32 clock_u32GetFrequencySFMA(void)
{
   u32 u32Div = 1;
   union /* structure of CKSC_SFMA_CTL register */
   {
      u32 u32word;
      struct
      {
         u32 bi32Reserved0 :  6;
         u32 bi32Exsrc     :  2;
         u32 bi32Ckstp     :  1;
         u32 bi32Reserved1 : 23;
      }bits;
   }unReg;

   unReg.u32word = CLK__xCPG->u32Sfmaclkcr;
   switch (unReg.bits.bi32Exsrc)
   {
      case 0U:
         u32Div = 2U;
         break;
      case 1U:
         u32Div = 3U;
         break;
      case 2U:
         u32Div = 4U;
         break;
      case 3U:
         u32Div = 6U;
         break;
      default:
         break;
   }
   return clock_u32GetFrequencySYS3() / u32Div;
}

/***************************************************************************
* Description         : This function returns the CPU core clock frequency
* Implementation      : Determine the CPU core clock frequency from CKSCCR
*                       and CKSCCR2 registers
* Return Value        : u32, frequency in Hz
****************************************************************************/
u32 clock_u32GetFrequencyZ2(void)   /* CPU core clock */
{
   u32 u32RetVal;
   u32 u32SrcSel;
   u32 u32Div = 1;
   union /* structure of CKSC_CTL Control Register 2 */
   {
      u32 u32word;
      struct
      {
         u32 bi32Z2CKSEL0  :  2;
         u32 bi32Reserved0 :  2;
         u32 bi32Z2CKSEL1  :  2;
         u32 bi32Reserved1 : 26;
      }bits;
   }unReg;

   u32SrcSel = (CLK__xCPG->u32Cksccr & (1 << 0x0U));  /* mask out Z2SEL from PLL1 Control Register */
   unReg.u32word = CLK__xCPG->u32Cksccr2;
   if(u32SrcSel == 0U)
   {
      u32Div = unReg.bits.bi32Z2CKSEL0;
      u32RetVal = clock_u32GetFrequencyPLL1();
   }
   else
   {
      u32Div = unReg.bits.bi32Z2CKSEL1;
      u32RetVal = clock_u32GetFrequencyPLLS();
   }

   switch (u32Div)
   {
      case 0U:
         u32RetVal /= 2U;
         break;
      case 1U:
         u32RetVal /= 3U;
         break;
      case 2U:
         u32RetVal = (u32RetVal / 26U) * 11U;
         break;
      case 3U:
         u32RetVal /= 6U;
         break;
      default:
         break;
   }
   return u32RetVal;
}
