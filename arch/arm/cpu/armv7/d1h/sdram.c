#include <common.h>
#include <asm/io.h>
#include <asm/arch/base.h>
#include <asm/arch/clock.h>
#include <asm/arch/timer.h>
#include <asm/arch/sdram.h>
#include <asm/arch/cpu.h>

static volatile SDRAM__tpstDBSC3Reg SDRAM__xDBSC3 = (SDRAM__tpstDBSC3Reg )(SDRAM__nDBSC3_BaseAddr);

/**********************************************************************************
* Description  : This function programs the PHY Unit Register
* Parameters   : u32Addr - PHY register address
*                u32Data - Write data
* Return Value : none
***********************************************************************************/
static void sdram__setphy(u32 u32Addr, u32 u32Data)
{
   SDRAM__xDBSC3->u32DBPDRGA = u32Addr;
   SDRAM__xDBSC3->u32DBPDRGD = u32Data;
}

static void sdram__waitforphystatus(u32 u32Addr, u32 u32Flag)
{
   SDRAM__xDBSC3->u32DBPDRGA = u32Addr;
   while ((SDRAM__xDBSC3->u32DBPDRGD & u32Flag) != u32Flag);

   /*Wait additional 32 PHY cycles (122ns) after bit is set*/
   __udelay(1UL);
}

static void sdram__waitforphystatusclr(u32 u32Addr, u32 u32Flag)
{
   SDRAM__xDBSC3->u32DBPDRGA = u32Addr;
   while ((SDRAM__xDBSC3->u32DBPDRGD & u32Flag) == u32Flag);

   /*Wait additional 32 PHY cycles (122ns) after bit is clear*/
   __udelay(1UL);
}
/**********************************************************************************
* Description  : This function checks the error flags
* Parameters   : u32Addr - PHY register address
*                u32Mask1 - mask for error flags (error if <> 0)
*                u32Mask2 - mask for error flags (error if == 0)
* Return Value : false - error, at least one flag was set
*                true  - no error, all flags are 0, no error
***********************************************************************************/
static bool sdram__checkerror(u32 u32Addr, u32 u32Mask1, u32 u32Mask2)
{
   bool boStatus;   /* False: error, True: no error */
   u32 u32DBPDRGD;
   SDRAM__xDBSC3->u32DBPDRGA = u32Addr;
   u32DBPDRGD = SDRAM__xDBSC3->u32DBPDRGD;
   /*error if <> 0*/
   boStatus = (u32DBPDRGD & u32Mask1) ? false : true;
   /*error if == 0*/
   boStatus &= (~(u32DBPDRGD | u32Mask2)) ? false : true;
   return boStatus;
}

/* To substitute the repeated sequences */
static void sdram__setphy_3x(u32 u32Addr)
{
   sdram__setphy(u32Addr, 0x0D0D0D0DUL);
   sdram__setphy(u32Addr + 1, 0x0D0D0D0DUL);
   sdram__setphy(u32Addr + 2, 0x000D0D0DUL);
}

/* To substitute the repeated sequences */
static void sdram__setphy0A0tophy100(bool boIs16BitsMode, u32 u32SetVal)
{
   sdram__setphy(SDRAM__nDDR3PHY0A0_Addr, u32SetVal);
   sdram__setphy(SDRAM__nDDR3PHY0C0_Addr, u32SetVal);
   if (boIs16BitsMode == false)
   {  /*Excluded for 16-bits mode*/
      sdram__setphy(SDRAM__nDDR3PHY0E0_Addr, u32SetVal);
      sdram__setphy(SDRAM__nDDR3PHY100_Addr, u32SetVal);
   }
}

/* To substitute the repeated sequences */
static void sdram__setphy0A3tophy103(u32 u32SetVal)
{
    sdram__setphy(SDRAM__nDDR3PHY0A3_Addr, u32SetVal);
    sdram__setphy(SDRAM__nDDR3PHY0C3_Addr, u32SetVal);
    sdram__setphy(SDRAM__nDDR3PHY0E3_Addr, u32SetVal);
    sdram__setphy(SDRAM__nDDR3PHY103_Addr, u32SetVal);
}

bool sdram__initddr3(void)
{
   u32 u32RegVal, i, j;
   u32 u32bdlcount_0, u32leftcode_0, u32leftlatency_0;
   u32 u32bdlcount_0b, u32leftcode_0b, u32leftlatency_0b, u32bdlcount_0b_div2, u32bdlcount_0b_div4;
   u32 u32Dqsgd_0c, u32Gatesl_0c, u32Rdqsd_0c, u32Rdqsnd_0c, u32Rbd_0c;
   u32 u32Bdlcount_0c, u32Bdlcount_0c_div4, u32Bdlcount_0c_div8;
   bool boIs16BitsMode = false;   /* The width of the external bus is 16 bits */
   u8 u8MaxLoopCnt;   /*Maximum loop count for Gate Training*/

   SDRAM_tstTimingCfg stTimingCfg = {SDRAM__nDBSC3_DBTR3,\
                                     SDRAM__nDBSC3_DBTR4,\
                                     SDRAM__nDBSC3_DBTR5,\
                                     SDRAM__nDBSC3_DBTR6,\
                                     SDRAM__nDBSC3_DBTR7,\
                                     SDRAM__nDBSC3_DBTR8,\
                                     SDRAM__nDBSC3_DBTR9,\
                                     SDRAM__nDBSC3_DBTR10,\
                                     SDRAM__nDBSC3_DBTR11,\
                                     SDRAM__nDBSC3_DBTR12,\
                                     SDRAM__nDBSC3_DBTR13,\
                                     SDRAM__nDBSC3_DBTR14,\
                                     SDRAM__nDBSC3_DBTR15,\
                                     SDRAM__nDBSC3_DBTR16,\
                                     SDRAM__nDBSC3_DBTR17,\
                                     SDRAM__nDBSC3_DBTR18,\
                                     SDRAM__nDBSC3_DBTR19};
    SDRAM_tstRefreshCfg stRefreshCfg = {SDRAM__nDBSC3_DBRFCNF0,SDRAM__nDBSC3_DBRFCNF1,SDRAM__nDBSC3_DBRFCNF2};

   /* 0: Wait for 200us */
   __udelay(200UL);

   SDRAM__xDBSC3->u32DBACEN    = SDRAM__nDBSC3_DBACEN_Disable;	//0.1
   SDRAM__xDBSC3->u32DBRFEN    = SDRAM__nDBSC3_DBFREN_Disable;	//0.2
   
   /* Init Sequence from Section 13.5.3 of User Manual */
   /* (a) Apply power-on reset and wait until DBSC3 is released from reset state */
   /* 1. */
   SDRAM__xDBSC3->u32DBPDLCK   = SDRAM__nDBSC3_DBPDLCK_EnableAccess;
   SDRAM__xDBSC3->u32DBRSTLCK  = SDRAM__nDBSC3_DBRSTLCK_EnableAccess;
   SDRAM__xDBSC3->u32DBRST     = SDRAM__nDBSC3_DBRST_Assert;
   
   /* 2. */
   SDRAM__xDBSC3->u32DBCMD     = SDRAM__nDBSC3_DBCMD_SetResetPinToHigh;
   SDRAM__xDBSC3->u32DBCMD     = SDRAM__nDBSC3_DBCMD_PowerDownExit;
   SDRAM__xDBSC3->u32DBCMD     = SDRAM__nDBSC3_DBCMD_PowerDownEntry;
   
   /* 3 - 6. */
   sdram__setphy(SDRAM__nDDR3PHY001_Addr, 0x80010000UL);
   sdram__waitforphystatus(SDRAM__nDDR3PHY006_Addr, 0x00000001UL);

   if(sdram__checkerror(SDRAM__nDDR3PHY006_Addr, SDRAM__nErrorFlags1_Msk, SDRAM__nErrorFlags2_Msk) == false)
   {
      return false;   /* Error, abort initialisation */
   }

   /* 7 - 22. */
   sdram__setphy(SDRAM__nDDR3PHY008_Addr, SDRAM__nDDR3PHY0008);
   sdram__setphy(SDRAM__nDDR3PHY090_Addr, 0x04058904UL);
   sdram__setphy(SDRAM__nDDR3PHY091_Addr, SDRAM__nDDR3PHY0091);
   sdram__setphy(SDRAM__nDDR3PHY095_Addr, SDRAM__nDDR3PHY0095);
   sdram__setphy(SDRAM__nDDR3PHY099_Addr, SDRAM__nDDR3PHY0099);
   sdram__setphy(SDRAM__nDDR3PHY090_Addr, 0x04058900UL);
   sdram__setphy(SDRAM__nDDR3PHY021_Addr, 0x0024641EUL);
   sdram__setphy(SDRAM__nDDR3PHY001_Addr, 0x00010073UL);
   
   /* 23 - 24. */
   sdram__waitforphystatus(SDRAM__nDDR3PHY006_Addr, 0x00000001UL);
   if(sdram__checkerror(SDRAM__nDDR3PHY006_Addr, SDRAM__nErrorFlags1_Msk, SDRAM__nErrorFlags2_Msk) == false)
   {
      return false;   /* Error, abort initialisation */
   }
   
   /* 25 - 28. */
   sdram__setphy(SDRAM__nDDR3PHY090_Addr, 0x0C058900UL);
   sdram__setphy(SDRAM__nDDR3PHY090_Addr, 0x04058900UL);
   
   /* (b) DBSC3 Settings */
   /* 29 - 30 */
   SDRAM__xDBSC3->u32DBKIND       = SDRAM__nDBSC3_DBKIND;
   SDRAM__xDBSC3->u32DBCONF0      = SDRAM__nDBSC3_DBCONF0;

   /* Determine the width of external bus */
   if((SDRAM__nDBSC3_DBCONF0 & SDRAM__nDBCONF0_DW0_Msk) == 1UL)
   {  /* DBCONF0[1:0] == 01b : 16-bit I/F */
      boIs16BitsMode = true;
      u8MaxLoopCnt = 2;   /*Skip DX2 & DX3 for 16-bits mode*/
   }
   else
   {
      boIs16BitsMode = false;
      u8MaxLoopCnt = 4;
   }

   /* 31- 33 */
   SDRAM__xDBSC3->u32DBPHYTYPE    = SDRAM__nDBSC3_DBPHYTYPE;
   
   SDRAM__xDBSC3->u32DBTR0        = SDRAM__nDBSC3_DBTR0;
   SDRAM__xDBSC3->u32DBTR1        = SDRAM__nDBSC3_DBTR1;

   /* 35 - 51 */
   SDRAM__xDBSC3->stTimingReg     = stTimingCfg;
   
   /* 52 - 56 */
   SDRAM__xDBSC3->u32DBRNK0       = SDRAM__nDBSC3_DBRNK0; // 0x00000001UL;
   SDRAM__xDBSC3->u32DBADJ0       = SDRAM__nDBSC3_DBADJ0;
   SDRAM__xDBSC3->u32DBADJ2       = SDRAM__nDBSC3_DBADJ2; // 0x20042004UL;
   SDRAM__xDBSC3->u32DBWT0CNF0    = SDRAM__nDBSC3_DBWT0CNF0; // 0x00020005UL;
   SDRAM__xDBSC3->u32DBWT0CNF4    = SDRAM__nDBSC3_DBWT0CNF4;
   
   /* JunSal: InitQOS
   H. Kuesters suggests that he InitQOS() for the DBSC3 should be
   placed after DBSC3 Setting 1 and before Phy Init
   */
   cpu_qos_dbsc3init();

   /* (c) PHY Setting_1 - Part 2 */
   /* 57 - 59 */
   sdram__waitforphystatus(SDRAM__nDDR3PHY006_Addr, 0x00000001UL);
   if(sdram__checkerror(SDRAM__nDDR3PHY006_Addr, SDRAM__nErrorFlags1_Msk, SDRAM__nErrorFlags2_Msk) == false)
   {
      return false;   /* Error, abort initialisation */
   }
   
   SDRAM__xDBSC3->u32DBDFICNT     = SDRAM__nDBSC3_DBDFICNT_Init;
   
   if (boIs16BitsMode != false)
   {
      /*59.01 - 59.12: 16-bit interface mode*/
      sdram__setphy(SDRAM__nDDR3PHY0E0_Addr, 0x7C0202F4UL);
      sdram__setphy(SDRAM__nDDR3PHY100_Addr, 0x7C0202F4UL);
      sdram__setphy(SDRAM__nDDR3PHY0E1_Addr, 0x55555555UL);
      sdram__setphy(SDRAM__nDDR3PHY101_Addr, 0x55555555UL);
      sdram__setphy(SDRAM__nDDR3PHY0E3_Addr, 0x00000505UL);
      sdram__setphy(SDRAM__nDDR3PHY103_Addr, 0x00000505UL);
   }

   /* 60 - 61.2 */

   sdram__setphy(SDRAM__nDDR3PHY003_Addr, SDRAM__nDDR3PHY0003A);


   sdram__waitforphystatus(SDRAM__nDDR3PHY007_Addr, 0x40000000UL);

   /* 62 - 83 */
   sdram__setphy(SDRAM__nDDR3PHY004_Addr, SDRAM__nDDR3PHY0004);
   sdram__setphy(SDRAM__nDDR3PHY022_Addr, SDRAM__nDDR3PHY0022);
   sdram__setphy(SDRAM__nDDR3PHY023_Addr, SDRAM__nDDR3PHY0023);
   sdram__setphy(SDRAM__nDDR3PHY024_Addr, SDRAM__nDDR3PHY0024);
   sdram__setphy(SDRAM__nDDR3PHY025_Addr, SDRAM__nDDR3PHY0025);
   sdram__setphy(SDRAM__nDDR3PHY026_Addr, SDRAM__nDDR3PHY0026);
   sdram__setphy(SDRAM__nDDR3PHY027_Addr, SDRAM__nDDR3PHY0027);
   sdram__setphy(SDRAM__nDDR3PHY028_Addr, SDRAM__nDDR3PHY0028);
   sdram__setphy(SDRAM__nDDR3PHY029_Addr, SDRAM__nDDR3PHY0029);
   sdram__setphy(SDRAM__nDDR3PHY02C_Addr, 0x81003047UL);
   sdram__setphy(SDRAM__nDDR3PHY020_Addr, SDRAM__nDDR3PHY0020);
   
   /* 85 - 85.2 */
   sdram__waitforphystatus(SDRAM__nDDR3PHY006_Addr, 0x00000001UL);

   if(sdram__checkerror(SDRAM__nDDR3PHY006_Addr, SDRAM__nErrorFlags1_Msk, SDRAM__nErrorFlags2_Msk) == false)
   {
      return false;   /* Error, abort initialisation */
   }
   
   /* 85.1 - 85.12 */
   sdram__setphy_3x(SDRAM__nDDR3PHY0A7_Addr);
   sdram__setphy_3x(SDRAM__nDDR3PHY0C7_Addr);

   if (boIs16BitsMode == false)
   {  /*Excluded for 16-bits mode*/
      /* 85.13 - 85.24 */
      sdram__setphy_3x(SDRAM__nDDR3PHY0E7_Addr);
      sdram__setphy_3x(SDRAM__nDDR3PHY107_Addr);
   }

   /* 86 - 90-2 */
   sdram__setphy(SDRAM__nDDR3PHY001_Addr, 0x00010181UL);
   SDRAM__xDBSC3->u32DBCMD        = SDRAM__nDBSC3_DBCMD_PowerDownExit;
   
   sdram__waitforphystatus(SDRAM__nDDR3PHY006_Addr, 0x00000001UL);
   if(sdram__checkerror(SDRAM__nDDR3PHY006_Addr, SDRAM__nErrorFlags1_Msk, SDRAM__nErrorFlags2_Msk) == false)
   {
      return false;   /* Error, abort initialisation */
   }
   
   /* 91 - 94.2 */
   sdram__setphy(SDRAM__nDDR3PHY001_Addr, 0x00010601UL);
   sdram__waitforphystatus(SDRAM__nDDR3PHY006_Addr, 0x00000001UL);

   if(sdram__checkerror(SDRAM__nDDR3PHY006_Addr, SDRAM__nErrorFlags1_Msk, SDRAM__nErrorFlags2_Msk) == false)
   {
      return false;   /* Error, abort initialisation */
   }
   
   /* PHY Gate Training Procedure */
   for (i=0; i<u8MaxLoopCnt; i++)
   {
      /* (DX0): 95 - 100, (DX1):116 - 122 */
      /* (DX2):138 - 143, (DX3):159 - 164, skip DX2 & DX3 for 16-bits mode */
      SDRAM__xDBSC3->u32DBPDRGA = 0x000000B1+(i*0x20);
      u32bdlcount_0 = ((SDRAM__xDBSC3->u32DBPDRGD & 0xFF00) >> 8);
      
      SDRAM__xDBSC3->u32DBPDRGA = 0x000000B4+(i*0x20);
      u32leftcode_0 = (SDRAM__xDBSC3->u32DBPDRGD & 0xFF);
      
      SDRAM__xDBSC3->u32DBPDRGA = 0x000000B3+(i*0x20);
      u32leftlatency_0 = (SDRAM__xDBSC3->u32DBPDRGD & 0x7);

      /* Setting 1 */
      /* (DX0):101 - 110, (DX1):122 - 131 */
      /* (DX2):144 - 153, (DX3):166 - 174, skip DX2 & DX3 for 16-bits mode */
      /* Setting 2 */
      /* (DX0):111 - 115, (DX1):132 - 136 */
      /* (DX2):154 - 158, (DX3):175 - 179, skip DX2 & DX3 for 16-bits mode */
      SDRAM__xDBSC3->u32DBPDRGA = 0x000000B2+(i*0x20);
      u32RegVal = (SDRAM__xDBSC3->u32DBPDRGD & 0xFFFFFFF8);

      SDRAM__xDBSC3->u32DBPDRGA = 0x000000B2+(i*0x20);
      if (u32leftcode_0 > 0)
      {
         SDRAM__xDBSC3->u32DBPDRGD = ((u32leftlatency_0 + 1) & 0x7) | u32RegVal;
      }
      else
      {
         SDRAM__xDBSC3->u32DBPDRGD = ((u32leftlatency_0) & 0x7) | u32RegVal;
      }
      SDRAM__xDBSC3->u32DBPDRGA = 0x000000B0+(i*0x20);
      u32RegVal =  (SDRAM__xDBSC3->u32DBPDRGD & 0xFFFFFF00);

      SDRAM__xDBSC3->u32DBPDRGA = 0x000000B0+(i*0x20);
      if (u32leftcode_0 > 0)
      {
         SDRAM__xDBSC3->u32DBPDRGD = u32leftcode_0 | u32RegVal;
      }
      else
      {
         SDRAM__xDBSC3->u32DBPDRGD = ((u32leftcode_0 + (u32bdlcount_0  << 1)) & 0xFF) | u32RegVal;
      }
   }

   /* DDR3 PHY Settings - Part 3 */
   /* 180 - 185 */
   sdram__setphy(SDRAM__nDDR3PHY005_Addr, 0xC1AA00A0UL);

   if (SDRAM_nDDR3_1066 != SDRAM_nDDR3RateConfig)  /* only applicable for DDR3-1333 */
   {
       sdram__setphy0A3tophy103(0x00000008); /* F1 - F8 */
   }
   else  /* only applicable for DDR3-1066 */
   {
      sdram__setphy0A0tophy100(boIs16BitsMode, 0x7C0002C5UL);
   }

   /* 190 - 193.2 */
   sdram__setphy(SDRAM__nDDR3PHY001_Addr, 0x00010801UL);
   sdram__waitforphystatus(SDRAM__nDDR3PHY006_Addr, 0x00000001UL);   //192

   if(sdram__checkerror(SDRAM__nDDR3PHY006_Addr, SDRAM__nErrorFlags1_Msk, SDRAM__nErrorFlags2_Msk) == false)
   {
      return false;   /* Error, abort initialisation */
   }

   /* 194 - 199.02 */
   sdram__setphy(SDRAM__nDDR3PHY005_Addr, 0xC1AA00B8UL);

   if(SDRAM_nDDR3_1066 == SDRAM_nDDR3RateConfig)   /* only applicable for DDR3-1066 */
   {
      sdram__setphy(SDRAM__nDDR3PHY001_Addr, 0x0001F001UL);
      sdram__waitforphystatus(SDRAM__nDDR3PHY006_Addr, 0x00000001UL);   //199
   }

   /* C1 - C64 */
   if(SDRAM_nDDR3_1066 != SDRAM_nDDR3RateConfig)   /* only applicable for DDR3-1333 */
   {
      sdram__setphy(SDRAM__nDDR3PHY001_Addr, 0x00011001UL);   /* C1 */
      sdram__waitforphystatus(SDRAM__nDDR3PHY006_Addr, 0x00000001UL);   /* C3 */
      sdram__setphy0A0tophy100(boIs16BitsMode, 0x7C0002C5UL);   /* C5 - C12 */

      sdram__setphy0A3tophy103(0x00000000);   /* C13 - C20 */

      sdram__setphy(SDRAM__nDDR3PHY001_Addr, 0x00012001UL);   /* C21 - C22 */
      sdram__waitforphystatus(SDRAM__nDDR3PHY006_Addr, 0x00000001UL);   /* C23 - C24 */
      sdram__setphy0A0tophy100(boIs16BitsMode, 0x7C000285UL);   /* C25 - C32 */

      sdram__setphy0A3tophy103(0x00000008);   /* C33 - C40 */

      sdram__setphy(SDRAM__nDDR3PHY001_Addr, 0x00014001UL);   /* C41 - C42 */
      sdram__waitforphystatus(SDRAM__nDDR3PHY006_Addr, 0x00000001UL);   /* C43 - C44 */
      sdram__setphy0A0tophy100(boIs16BitsMode, 0x7C0002C5UL);   /* C45 - C52 */

      sdram__setphy0A3tophy103(0x00000000);   /* C53 - C60 */

      sdram__setphy(SDRAM__nDDR3PHY001_Addr, 0x00018001UL);   /* C61 - C62 */
      sdram__waitforphystatus(SDRAM__nDDR3PHY006_Addr, 0x00000001UL);   /* C63 - C64 */
   }

   /* DBSC PHY Settings - Part 4 */
   /* 199.01 - 199.02 */
   if(sdram__checkerror(SDRAM__nDDR3PHY006_Addr, SDRAM__nErrorFlags1_Msk, SDRAM__nErrorFlags2_Msk) == false)
   {
      return false;   /* Error, abort initialisation */
   }
   
   /* 199.1 - 199.4 */
   sdram__setphy0A0tophy100(boIs16BitsMode, 0x7C000285UL);   /* 199.1, 199.5 - 199.8 */

   /* 199.9 - 199.16 */
   sdram__setphy(SDRAM__nDDR3PHY02C_Addr, 0x81003087UL);
   sdram__setphy(SDRAM__nDDR3PHY001_Addr, 0x00010401UL);
   sdram__waitforphystatus(SDRAM__nDDR3PHY006_Addr, 0x00000001UL);   //199.13

   if(sdram__checkerror(SDRAM__nDDR3PHY006_Addr, SDRAM__nErrorFlags1_Msk, SDRAM__nErrorFlags2_Msk) == false)
   {
      return false;   /* Error, abort initialisation */
   }
   
   /* PHY Gate Training Procedure B */
   for (i=0; i<u8MaxLoopCnt; i++)
   {
     /* Gate training setting_b */
     /* (DX0): GTSb_1 -  GTSb_6, (DX1):GTSb_26 - GTSb_31 */
     /* (DX2):GTSb_51 - GTSb_56, (DX3):GTSb_76 - GTSb_81, skip DX2 & DX3 for 16-bits mode */
      SDRAM__xDBSC3->u32DBPDRGA = 0x000000B1+(i*0x20);
      u32bdlcount_0b = ((SDRAM__xDBSC3->u32DBPDRGD & 0xFF00) >> 8);
      
      SDRAM__xDBSC3->u32DBPDRGA = 0x000000B4+(i*0x20);
      u32leftcode_0b = (SDRAM__xDBSC3->u32DBPDRGD & 0xFF);
      
      SDRAM__xDBSC3->u32DBPDRGA = 0x000000B3+(i*0x20);
      u32leftlatency_0b = (SDRAM__xDBSC3->u32DBPDRGD & 0x7);
      
      u32bdlcount_0b_div2 = (u32bdlcount_0b >> 1);
      u32bdlcount_0b_div4 = (u32bdlcount_0b >> 2);
      
      /* (DX0): GTSb_8 - GTSb_16, (DX1):GTSb_33 - GTSb_41 */
      /* (DX2):GTSb_58 - GTSb_66, (DX3):GTSb_83 - GTSb_91, skip DX2 & DX3 for 16-bits mode */
      /* (DX0):GTSb_17 - GTSb_25, (DX1):GTSb_42 - GTSb_50 */
      /* (DX2):GTSb_67 - GTSb_75, (DX3):GTSb_92 - GTSb_100, skip DX2 & DX3 for 16-bits mode */
      SDRAM__xDBSC3->u32DBPDRGA = 0x000000B2+(i*0x20);
      u32RegVal = (SDRAM__xDBSC3->u32DBPDRGD & 0xFFFFFFF8);

      SDRAM__xDBSC3->u32DBPDRGA = 0x000000B2+(i*0x20);
      if (u32leftcode_0b > u32bdlcount_0b_div4)
      {
         SDRAM__xDBSC3->u32DBPDRGD = ((u32leftlatency_0b + 1) & 0x7) | u32RegVal;
      }
      else
      {
         SDRAM__xDBSC3->u32DBPDRGD = ((u32leftlatency_0b) & 0x7) | u32RegVal;
      }

      SDRAM__xDBSC3->u32DBPDRGA = 0x000000B0+(i*0x20);
      u32RegVal =  (SDRAM__xDBSC3->u32DBPDRGD & 0xFFFFFF00);

      SDRAM__xDBSC3->u32DBPDRGA = 0x000000B0+(i*0x20);
      if (u32leftcode_0b > u32bdlcount_0b_div4)
      {
         SDRAM__xDBSC3->u32DBPDRGD = ((u32leftcode_0b - u32bdlcount_0b_div4) & 0xFF) | u32RegVal;
      }
      else
      {
         SDRAM__xDBSC3->u32DBPDRGD = ((u32leftcode_0b + u32bdlcount_0b + u32bdlcount_0b_div2 + u32bdlcount_0b_div4) & 0xFF) | u32RegVal;
      }
   }

   if(SDRAM_nDDR3_1066 == SDRAM_nDDR3RateConfig)   /* only applicable for DDR3-1066 */
   {
      sdram__setphy0A0tophy100(boIs16BitsMode, 0x7C0002C5UL);   /* 200, 200.04 - 200.07 */
   }

   /* G1 - G8 */
   if (SDRAM_nDDR3_1066 != SDRAM_nDDR3RateConfig)   /* only applicable for DDR3-1333 */
   {
       sdram__setphy0A3tophy103(0x00000008);   /* G1 - G8 */
   }

   sdram__setphy(SDRAM__nDDR3PHY001_Addr, 0x00015001UL);   //200.08
   sdram__waitforphystatus(SDRAM__nDDR3PHY006_Addr, 0x00000001UL);   //200.10

   if(sdram__checkerror(SDRAM__nDDR3PHY006_Addr, SDRAM__nErrorFlags1_Msk, SDRAM__nErrorFlags2_Msk) == false)
   {
      return false;   /* Error, abort initialisation */
   }

   if(SDRAM_nDDR3_1066 != SDRAM_nDDR3RateConfig)   /* only applicable for DDR3-1333 */
   {
      /* PHY Gate Training Procedure C */
      for (i=0; i<u8MaxLoopCnt; i++)
      {
         /* Gate training setting_c */
         /* (DX0): D1.1 -  D4.18,  (DX1):D6.1 - D9.18 */
         /* (DX2): D11.1 - D14.18, (DX3):D16.1 - D19.18, skip DX2 & DX3 for 16-bits mode */
         SDRAM__xDBSC3->u32DBPDRGA = 0x000000B0UL+(i*0x20);   /* D1.1, D6.1, D11.1, D16.1 */
         u32Dqsgd_0c = (SDRAM__xDBSC3->u32DBPDRGD & 0x000000FFUL);

         SDRAM__xDBSC3->u32DBPDRGA = 0x000000B1UL+(i*0x20);   /* D1.3 */
         u32Bdlcount_0c = ((SDRAM__xDBSC3->u32DBPDRGD & 0x0000FF00UL) >> 8);

         u32Bdlcount_0c_div4 = (u32Bdlcount_0c >> 2);
         u32Bdlcount_0c_div8 = (u32Bdlcount_0c >> 3);

         if(u32Dqsgd_0c > u32Bdlcount_0c)
         {
            if(u32Dqsgd_0c <= u32Bdlcount_0c + u32Bdlcount_0c_div4 + u32Bdlcount_0c_div8)
            {
               /* D3, D8, D13, D18 */
               SDRAM__xDBSC3->u32DBPDRGA = 0x000000B0UL+(i*0x20);
               u32RegVal = (SDRAM__xDBSC3->u32DBPDRGD & 0xFFFFFF00UL);
               SDRAM__xDBSC3->u32DBPDRGD = (u32Dqsgd_0c - u32Bdlcount_0c_div8) | u32RegVal;
            }
            else
            {
               /* D4, D9, D14, D19 */
               SDRAM__xDBSC3->u32DBPDRGA = 0x000000B0UL+(i*0x20);   /* D4.1 */
               u32RegVal = (SDRAM__xDBSC3->u32DBPDRGD & 0xFFFFFF00UL);
               SDRAM__xDBSC3->u32DBPDRGD = u32RegVal;

               SDRAM__xDBSC3->u32DBPDRGA = 0x000000B2UL+(i*0x20);   /* D4.3 */
               u32Gatesl_0c = (SDRAM__xDBSC3->u32DBPDRGD & 0x00000007UL);
               SDRAM__xDBSC3->u32DBPDRGA = 0x000000B2UL+(i*0x20);   /* D4.5 */
               u32RegVal = (SDRAM__xDBSC3->u32DBPDRGD & 0xFFFFFFF8UL);
               SDRAM__xDBSC3->u32DBPDRGD = (u32RegVal | ((u32Gatesl_0c + 1) & 0x00000007UL));

               SDRAM__xDBSC3->u32DBPDRGA = 0x000000AFUL+(i*0x20);   /* D4.7 */
               u32RegVal = SDRAM__xDBSC3->u32DBPDRGD;
               u32Rdqsd_0c = (u32RegVal & 0x0000FF00UL) >> 8;
               u32Rdqsnd_0c = (u32RegVal & 0x00FF0000UL) >> 16;
               SDRAM__xDBSC3->u32DBPDRGA = 0x000000AFUL+(i*0x20);   /* D4.9 */
               SDRAM__xDBSC3->u32DBPDRGD = ((u32RegVal & 0xFF0000FFUL) | (((u32Rdqsd_0c + u32Bdlcount_0c_div8) << 8) & 0x0000FF00UL) | (((u32Rdqsnd_0c + u32Bdlcount_0c_div8) << 16) & 0x00FF0000UL));

               SDRAM__xDBSC3->u32DBPDRGA = 0x000000AAUL +(i*0x20);   /* D4.11 */
               u32RegVal = SDRAM__xDBSC3->u32DBPDRGD;
               for (j=0; j< 4; j++)   /* D4.12 */
               {
                  u32Rbd_0c = (u32RegVal >>  (8*j)) & 0x0000001FUL;   /* u32Rbd_0c[j] */
                  u32Rbd_0c = (u32Rbd_0c + u32Bdlcount_0c_div8);
                  if (u32Rbd_0c > 0x1f)
                  {
                     u32Rbd_0c = 0x1f;
                  }
                  u32RegVal = (u32RegVal & ~(0x0000001FUL << (8*j))) | (u32Rbd_0c << (8*j));
               }
               SDRAM__xDBSC3->u32DBPDRGA = 0x000000AAUL +(i*0x20);   /* D4.13 */
               SDRAM__xDBSC3->u32DBPDRGD = u32RegVal;   /* D4.14 */

               SDRAM__xDBSC3->u32DBPDRGA = 0x000000ABUL+(i*0x20);   /* D4.15 */
               u32RegVal = SDRAM__xDBSC3->u32DBPDRGD;
               for (j=0; j< 4; j++)   /* D4.16 */
               {
                  u32Rbd_0c = (u32RegVal >>  (8*j)) & 0x0000001FUL;   /* u32Rbd_0c[j] */
                  u32Rbd_0c = (u32Rbd_0c + u32Bdlcount_0c_div8);
                  if (u32Rbd_0c > 0x1f)
                  {
                     u32Rbd_0c = 0x1f;
                  }
                  u32RegVal = (u32RegVal & ~(0x0000001FUL << (8*j))) | (u32Rbd_0c << (8*j));
               }
               SDRAM__xDBSC3->u32DBPDRGA = 0x000000ABUL +(i*0x20);   /* D4.17 */
               SDRAM__xDBSC3->u32DBPDRGD = u32RegVal;   /* D4.18 */
            }
         }
         /* Finished. D5, D10, D15, D20 */
      }
      sdram__setphy(SDRAM__nDDR3PHY002_Addr, 0x07D81E37UL);   /* D21 */
   }

   sdram__setphy(SDRAM__nDDR3PHY003_Addr, SDRAM__nDDR3PHY0003B);  /* 200.14 - 200.15 */
   
   sdram__waitforphystatusclr(SDRAM__nDDR3PHY007_Addr, 0x40000000UL);   /* 200.16 - 200.17 */
   sdram__setphy(SDRAM__nDDR3PHY005_Addr, 0xC1AA00BCUL);   /* Disable read FIFO reset */
   sdram__setphy(SDRAM__nDDR3PHY021_Addr, 0x0024641FUL);   /* 200.18 - 200.19 */
   
   /* DBSC Settings 2 -Part 2 */ 
   /* 201 - 206 */
   SDRAM__xDBSC3->u32DBPDCNT0     = SDRAM__nDBSC3_DBPDCNT0_Disable;
   SDRAM__xDBSC3->u32DBBS0CNT1    = SDRAM__nDBSC3_DBBS0CNT1; // 0x00000000UL;
   SDRAM__xDBSC3->u32DBCALCNF     = SDRAM__nDBSC3_DBCALCNF_Enable; // 0x0100983EUL;
   SDRAM__xDBSC3->u32DBCALTR      = SDRAM__nDBSC3_DBCALTR;

   SDRAM__xDBSC3->stRefreshReg   = stRefreshCfg;   //204

   SDRAM__xDBSC3->u32DBRFEN       = SDRAM__nDBSC3_DBRFEN;
   
   /* 207.1 - 209 */
   SDRAM__xDBSC3->u32DBRST        = SDRAM__nDBSC3_DBRST_Deassert;
   SDRAM__xDBSC3->u32DBRSTLCK     = SDRAM__nDBSC3_DBRSTLCK_DisableAccess;
   SDRAM__xDBSC3->u32DBACEN       = SDRAM__nDBSC3_DBACEN_Enable;

   if(SDRAM_nDDR3_1066 != SDRAM_nDDR3RateConfig)   /* only applicable for DDR3-1333 */
   {
      sdram__setphy(SDRAM__nDDR3PHY000_Addr, *(u32*)0x40000000UL);   /* E1 - E3 */
      sdram__setphy0A0tophy100(boIs16BitsMode, 0x7C0002C5UL);   /* E4 - E11 */
      sdram__setphy0A3tophy103(0x00000000);   /* E12 - E19 */
   }

   SDRAM__xDBSC3->u32DBPDLCK      = SDRAM__nDBSC3_DBPDLCK_DisableAccess;  
   return true;  
}

/**********************************************************************************
* Description  : This function verifies read and write access to DDR3
* Parameters   : none
* Return Value : bool - check status
***********************************************************************************/
bool sdram__checkddr3(void)
{
   bool boResult = true;
   /* 
   * Variable used to store the check result
   */
   
   volatile u32 * pu32Addr;
   volatile u32 u32Data;
   /* 
   * Variables used to store the address and data during read and
   * write accesses to DDR3
   */
   
   u32 u32Addr = SDRAM__nMemTestStartAddress;
   /* 
   * Variable used to store the DDR3 address to be tested
   */

   while (u32Addr < SDRAM__nMemTestEndAddress)
   {
      pu32Addr    = (volatile u32 *)(u32Addr);
      *pu32Addr   = SDRAM__nMemTestDataPattern;
      u32Data     = *pu32Addr;
      if (u32Data != SDRAM__nMemTestDataPattern)
      {
         boResult = false;
      }
      u32Addr += SDRAM__nMemTestAddressIncrement;
   }
   
   return boResult;
}


/**********************************************************************************
* Description  : Main module initialization function
*                This initializes the EIM, DDR3, and the necessary IOMUXC registers
* Parameters   : none
* Return Value : bool
*                False: initialisation failed
*                True : initialisation successful
***********************************************************************************/
bool sdram_init(void)
 {
   bool boInitStatus = true;   /* False: initialisation failed, True: initialisation successful */ 
     
   /* 1. DDR3 Init */
   boInitStatus = sdram__initddr3();
   if(false != boInitStatus)
   {
        boInitStatus = sdram__checkddr3();
   }

   return boInitStatus;
}