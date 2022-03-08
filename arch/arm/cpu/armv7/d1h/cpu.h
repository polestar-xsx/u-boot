#ifndef __CPU_H
#define __CPU_H

/***************************************************************************
* S3CTRL Registers
****************************************************************************/
#define CPU__nS3CTRL_BaseAddr           0xE6784000UL

#define CPU__nS3C_QoS_Reg_BaseAddr       (CPU__nS3CTRL_BaseAddr + 0x0014UL)

//#define CPU__nS3C_QoSDCACHE_BaseAddr   (CPU__nS3CTRL_BaseAddr + 0x0BDCUL)
#define CPU__nS3C_QoSCCI0_BaseAddr       (CPU__nS3CTRL_BaseAddr + 0x0C00UL)
#define CPU__nS3C_QoSCCI1_BaseAddr       (CPU__nS3CTRL_BaseAddr + 0x0C24UL)
#define CPU__nS3C_QoSMXI_BaseAddr        (CPU__nS3CTRL_BaseAddr + 0x0C48UL)
#define CPU__nS3C_QoSAXI_BaseAddr        (CPU__nS3CTRL_BaseAddr + 0x0C6CUL)

/***************************************************************************
* DBSC3 Registers
****************************************************************************/
#define CPU__nDBSC3_DEVICE_MAX             16
#define CPU__nDBCS3_0_BaseAddr            0xE6790000UL
/* DBSC3 QoS Read register */
#define CPU__nDBCS3_0_QOS_R0_BaseAddr     (CPU__nDBCS3_0_BaseAddr + 0x1000UL)
#define CPU__nDBCS3_0_QOS_R1_BaseAddr     (CPU__nDBCS3_0_BaseAddr + 0x1100UL)
#define CPU__nDBCS3_0_QOS_R2_BaseAddr     (CPU__nDBCS3_0_BaseAddr + 0x1200UL)
#define CPU__nDBCS3_0_QOS_R3_BaseAddr     (CPU__nDBCS3_0_BaseAddr + 0x1300UL)
#define CPU__nDBCS3_0_QOS_R4_BaseAddr     (CPU__nDBCS3_0_BaseAddr + 0x1400UL)
#define CPU__nDBCS3_0_QOS_R5_BaseAddr     (CPU__nDBCS3_0_BaseAddr + 0x1500UL)
#define CPU__nDBCS3_0_QOS_R6_BaseAddr     (CPU__nDBCS3_0_BaseAddr + 0x1600UL)
#define CPU__nDBCS3_0_QOS_R7_BaseAddr     (CPU__nDBCS3_0_BaseAddr + 0x1700UL)
#define CPU__nDBCS3_0_QOS_R8_BaseAddr     (CPU__nDBCS3_0_BaseAddr + 0x1800UL)
#define CPU__nDBCS3_0_QOS_R9_BaseAddr     (CPU__nDBCS3_0_BaseAddr + 0x1900UL)
#define CPU__nDBCS3_0_QOS_R10_BaseAddr    (CPU__nDBCS3_0_BaseAddr + 0x1A00UL)
#define CPU__nDBCS3_0_QOS_R11_BaseAddr    (CPU__nDBCS3_0_BaseAddr + 0x1B00UL)
#define CPU__nDBCS3_0_QOS_R12_BaseAddr    (CPU__nDBCS3_0_BaseAddr + 0x1C00UL)
#define CPU__nDBCS3_0_QOS_R13_BaseAddr    (CPU__nDBCS3_0_BaseAddr + 0x1D00UL)
#define CPU__nDBCS3_0_QOS_R14_BaseAddr    (CPU__nDBCS3_0_BaseAddr + 0x1E00UL)
#define CPU__nDBCS3_0_QOS_R15_BaseAddr    (CPU__nDBCS3_0_BaseAddr + 0x1F00UL)

/* DBSC3 QoS Write register */
#define CPU__nDBCS3_0_QOS_W0_BaseAddr     (CPU__nDBCS3_0_BaseAddr + 0x2000UL)
#define CPU__nDBCS3_0_QOS_W1_BaseAddr     (CPU__nDBCS3_0_BaseAddr + 0x2100UL)
#define CPU__nDBCS3_0_QOS_W2_BaseAddr     (CPU__nDBCS3_0_BaseAddr + 0x2200UL)
#define CPU__nDBCS3_0_QOS_W3_BaseAddr     (CPU__nDBCS3_0_BaseAddr + 0x2300UL)
#define CPU__nDBCS3_0_QOS_W4_BaseAddr     (CPU__nDBCS3_0_BaseAddr + 0x2400UL)
#define CPU__nDBCS3_0_QOS_W5_BaseAddr     (CPU__nDBCS3_0_BaseAddr + 0x2500UL)
#define CPU__nDBCS3_0_QOS_W6_BaseAddr     (CPU__nDBCS3_0_BaseAddr + 0x2600UL)
#define CPU__nDBCS3_0_QOS_W7_BaseAddr     (CPU__nDBCS3_0_BaseAddr + 0x2700UL)
#define CPU__nDBCS3_0_QOS_W8_BaseAddr     (CPU__nDBCS3_0_BaseAddr + 0x2800UL)
#define CPU__nDBCS3_0_QOS_W9_BaseAddr     (CPU__nDBCS3_0_BaseAddr + 0x2900UL)
#define CPU__nDBCS3_0_QOS_W10_BaseAddr    (CPU__nDBCS3_0_BaseAddr + 0x2A00UL)
#define CPU__nDBCS3_0_QOS_W11_BaseAddr    (CPU__nDBCS3_0_BaseAddr + 0x2B00UL)
#define CPU__nDBCS3_0_QOS_W12_BaseAddr    (CPU__nDBCS3_0_BaseAddr + 0x2C00UL)
#define CPU__nDBCS3_0_QOS_W13_BaseAddr    (CPU__nDBCS3_0_BaseAddr + 0x2D00UL)
#define CPU__nDBCS3_0_QOS_W14_BaseAddr    (CPU__nDBCS3_0_BaseAddr + 0x2E00UL)
#define CPU__nDBCS3_0_QOS_W15_BaseAddr    (CPU__nDBCS3_0_BaseAddr + 0x2F00UL)

#define CPU__nDBSC3_0_DBADJ2_Addr     	  (CPU__nDBCS3_0_BaseAddr + 0x00C8UL)

#define CPU__nCCI_400_BaseAddr             0xF0090000UL
#define CPU__nCCI_400_OverReg_BaseAddr    (CPU__nCCI_400_BaseAddr + 0x00001100UL)
#define CPU__nCCI_400_QosCntrl1_BaseAddr  (CPU__nCCI_400_BaseAddr + 0x0000110CUL)
#define CPU__nCCI_400_QosCntrl2_BaseAddr  (CPU__nCCI_400_BaseAddr + 0x0000210CUL)
#define CPU__nCCI_400_QosCntrl3_BaseAddr  (CPU__nCCI_400_BaseAddr + 0x0000310CUL)

/* MXI */
#define	CPU__nMXI_BaseAddr 		           0xFE960000UL
#define	CPU__nMXI_CR_BaseAddr             (CPU__nMXI_BaseAddr + 0x0040UL)
#define	CPU__nMXI_QOS_BaseAddr 		       0xFE960300UL
#define	CPU__nMXIR_QOS_BaseAddr		       (0xFE960200UL + 3*sizeof(uint32))

/* SYS AXI */
#define CPU__nSYS_AXI_SYX64TO128_BaseAddr  0xFF800300UL
#define CPU__nSYS_AXI_AVB_BaseAddr   	   0xFF800340UL
#define CPU__nSYS_AXI_IMUX0_BaseAddr	   0xFF800600UL
#define CPU__nSYS_AXI_IMUX1_BaseAddr	   0xFF800640UL
#define CPU__nSYS_AXI_IMUX2_BaseAddr	   0xFF800680UL
#define CPU__nSYS_AXI_MMUDS_BaseAddr	   0xFF800700UL
#define CPU__nSYS_AXI_MMUM_BaseAddr	       0xFF800740UL
#define CPU__nSYS_AXI_MMUS0_BaseAddr	   0xFF8007C0UL
#define CPU__nSYS_AXI_MMUS1_BaseAddr	   0xFF800800UL
#define CPU__nSYS_AXI_SDS0_BaseAddr	       0xFF800A80UL
#define CPU__nSYS_AXI_SDS1_BaseAddr	       0xFF800AC0UL
#define CPU__nSYS_AXI_USB20_BaseAddr       0xFF800C00UL
#define CPU__nSYS_AXI_MLB_BaseAddr	       0xFF800C80UL
#define CPU__nSYS_AXI_AX2M_BaseAddr	       0xFF800380UL
#define CPU__nSYS_AXI_CCI_BaseAddr	       0xFF800440UL
#define CPU__nSYS_AXI_CS_BaseAddr		   0xFF800480UL
#define CPU__nSYS_AXI_DDM_BaseAddr	       0xFF8004C0UL
#define CPU__nSYS_AXI_NANDC_BaseAddr	   0xFF800500UL
#define CPU__nSYS_AXI_DHDX_BaseAddr	       0xFF800840UL
#define CPU__nSYS_AXI_SDM0_BaseAddr	       0xFF800A00UL
#define CPU__nSYS_AXI_SDM1_BaseAddr	       0xFF800A40UL
#define CPU__nSYS_AXI_TRKF_BaseAddr	       0xFF800B00UL
#define CPU__nSYS_AXI_UDM0_BaseAddr	       0xFF800B80UL
#define CPU__nSYS_AXI_UDM1_BaseAddr	       0xFF800BC0UL
#define CPU__nSYS_AXI256_SYX_BaseAddr	   0xFF860140UL
#define CPU__nSYS_AXI256_MXI_BaseAddr	   0xFF8601C0UL

#define CPU__nCCI_AXI_MMUS0_BaseAddr	   0xFF880100UL
#define CPU__nCCI_AXI_SYX2_BaseAddr	       0xFF880140UL
#define CPU__nCCI_AXI_MMUR_BaseAddr	       0xFF880180UL
#define CPU__nCCI_AXI_MMUDS_BaseAddr	   0xFF8801C0UL
#define CPU__nCCI_AXI_MMUM_BaseAddr	       0xFF880200UL
#define CPU__nCCI_AXI_MXI_BaseAddr	       0xFF880240UL
#define CPU__nCCI_AXI_MMUS1_BaseAddr	   0xFF880280UL
#define CPU__nCCI_AXI_MMUMP_BaseAddr	   0xFF8802C0UL

#define CPU__nMEDIA_AXI_MXR_BaseAddr	   0xFE960080UL
#define CPU__nMEDIA_AXI_MXW_BaseAddr	   0xFE9600C0UL
#define CPU__nMEDIA_AXI_VSPDU0CR_BaseAddr  0xFE9645C0UL
#define CPU__nMEDIA_AXI_VSPDU0CW_BaseAddr  0xFE9665C0UL
#define CPU__nMEDIA_AXI_VSPDU1CR_BaseAddr  0xFE964600UL
#define CPU__nMEDIA_AXI_VSPDU1CW_BaseAddr  0xFE966600UL
#define CPU__nMEDIA_AXI_VIN0W_BaseAddr	   0xFE966900UL
#define CPU__nMEDIA_AXI_VSPD0R_BaseAddr	   0xFE965500UL
#define CPU__nMEDIA_AXI_VSPD0W_BaseAddr	   0xFE967500UL
#define CPU__nMEDIA_AXI_VSPD1R_BaseAddr	   0xFE965540UL
#define CPU__nMEDIA_AXI_VSPD1W_BaseAddr	   0xFE967540UL
#define CPU__nMEDIA_AXI_DU0R_BaseAddr	   0xFE965580UL
#define CPU__nMEDIA_AXI_DU0W_BaseAddr	   0xFE967580UL
#define CPU__nMEDIA_AXI_DU1R_BaseAddr	   0xFE9655C0UL
#define CPU__nMEDIA_AXI_DU1W_BaseAddr	   0xFE9675C0UL
#define CPU__nMEDIA_AXI_VCP0CR_BaseAddr	   0xFE965900UL
#define CPU__nMEDIA_AXI_VCP0CW_BaseAddr	   0xFE967900UL
#define CPU__nMEDIA_AXI_VCP0VR_BaseAddr	   0xFE965940UL
#define CPU__nMEDIA_AXI_VCP0VW_BaseAddr	   0xFE967940UL
#define CPU__nMEDIA_AXI_VPC0R_BaseAddr	   0xFE965980UL

/***************************************************************************
* D1H - CPU GIC (Generic Inetrrupt Controller or INTC-SYS )
****************************************************************************/
#define CPU__nGICD_BaseAddr         0xF1001000UL  /* Distributor Interface */
#define CPU__nGICC_BaseAddr         0xF1002000UL  /* CPU - Interface */

/* 
* Refer IHI0048B_b_gic_architecture_specification for details about below registers. 
*/
#define GICD__nCTRL                   (0x000)
#define GICD__nTYPER                  (0x004)
#define GICD__nGROUP                  (0x080)

#define GICD__nISENABLER              (0x100)
#define GICD__nICENABLER              (0x180)
#define GICD__nISPENDR                (0x200)
#define GICD__nICPENDR                (0x280)
#define GICD__nISACTIVER              (0x300)
#define GICD__nICACTIVER              (0x380)
#define GICD__nIPRIORITYR             (0x400)
#define GICD__nITARGETSR              (0x800)
#define GICD__nICFGR                  (0xC00)
#define GICC__nCTRL                   (0x0000)    /* CPU Interface Control Register   */
#define GICC__nIAR                    (0x000C)    /* Interrupt Acknowledge Register   */
#define GICC__nEOIR                   (0x0010)    /* End of Interrupt Register        */
#define GICC__nPMR                    (0x0004)    /* CPU Interface Priority Mask Register */




/* The threshold queue length which the read transactions of QOS-Level0 can fill
*   0x0 0000b: [ 0x00 ]
*   to
*   0x1 1111b: [ 0x1F ]
*/
 #define CPU__nS3CRORR_QOSTH0_Cfg     0x08UL

/* The threshold queue length which the read transactions of QOS-Level1 can fill
*   0x0 0000b: [ 0x00 ]
*   to
*   0x1 1111b: [ 0x1F ]
*  When QOSTHn = 0x1F, its transaction number is not limited
*/
 #define CPU__nS3CRORR_QOSTH1_Cfg     0x09UL

/* The threshold queue length which the read transactions of QOS-Level2 can fill
*   0x0 0000b: [ 0x00 ]
*   to
*   0x1 1111b: [ 0x1F ]
*  When QOSTHn = 0x1F, its transaction number is not limited
*/
#define CPU__nS3CRORR_QOSTH2_Cfg     0x0BUL

/* The threshold queue length which the read transactions of QOS-Level3 can fill
*   0x0 0000b: [ 0x00 ]
*   to
*   0x1 1111b: [ 0x1F ]
*  When QOSTHn = 0x1F, its transaction number is not limited
*/
#define CPU__nS3CRORR_QOSTH3_Cfg     0x1FUL

/* Reset the read transaction counter
*   0:Do not Reset counter
*   1:Reset Counter */
#define CPU__nS3CRORR_RST_Cfg        0x0UL

/* The threshold queue length which the write transactions of QOS-Level0 can fill
*   0x0 0000b: [ 0x00 ]
*   to
*   0x1 1111b: [ 0x1FF]
*/
 #define CPU__nS3CWORR_QOSTH0_Cfg     0x08UL

/* The threshold queue length which the write transactions of QOS-Level1 can fill
*   0x0 0000b: [ 0x00 ]
*   to
*   0x1 1111b: [ 0x1F ]
*  When QOSTHn = 0x1F, its transaction number is not limited
*/
 #define CPU__nS3CWORR_QOSTH1_Cfg     0x0AUL

/* The threshold queue length which the write transactions of QOS-Level2 can fill
*   0x0 0000b: [ 0x00 ]
*   to
*   0x1 1111b: [ 0x1F ]
*  When QOSTHn = 0x1F, its transaction number is not limited
*/
#define CPU__nS3CWORR_QOSTH2_Cfg     0x0EUL

/* The threshold queue length which the write transactions of QOS-Level3 can fill
*   0x0 0000b: [ 0x00 ]
*   to
*   0x1 1111b: [ 0x1F ]
*  When QOSTHn = 0x1F, its transaction number is not limited
*/
#define CPU__nS3CWORR_QOSTH3_Cfg     0x1FUL

/* Reset the write transaction counter
*   0:Do not Reset counter
*   1:Reset Counter */
#define CPU__nS3CWORR_RST_Cfg        0x0UL

/*S3C Read Outstanding Regulation Register */
#define CPU__nS3CRORR_Cfg       0x1F0B0604UL

/*S3C Write Outstanding Regulation Register */
#define CPU__nS3CWORR_Cfg       0x1F0E0705UL

/* DBSC adjustment Register Configuration */
#define CPU__nDBSC3_0_DBADJ2_Cfg     (0x20042004UL)

/* Cortex A7, SGX540 CCI0 QoS Control Registers configurations */
#define CPU__nSC3_CCI0_QOS0_Cfg          0x00890089UL
#define CPU__nSC3_CCI0_QOS1_Cfg          0x20960010UL
#define CPU__nSC3_CCI0_QOS2_Cfg          0x20302030UL
#define CPU__nSC3_CCI0_QOS3_Cfg          0x20AA2200UL
#define CPU__nSC3_CCI0_QOS4_Cfg          0x00002032UL
#define CPU__nSC3_CCI0_QOS5_Cfg          0x20960010UL
#define CPU__nSC3_CCI0_QOS6_Cfg          0x20302030UL

#define CPU__nSC3_CCI0_QOS7_Cfg          0x20AA2200UL
#define CPU__nSC3_CCI0_QOS8_Cfg          0x00002032UL

/*  Cortex A7, SGX540 CCI1 QoS Control Registers configurations */
#define CPU__nSC3_CCI1_QOS0_Cfg          0x00A300A3UL
#define CPU__nSC3_CCI1_QOS1_Cfg          0x20960010UL
#define CPU__nSC3_CCI1_QOS2_Cfg          0x20302030UL
#define CPU__nSC3_CCI1_QOS3_Cfg          0x20AA2200UL
#define CPU__nSC3_CCI1_QOS4_Cfg          0x00002032UL
#define CPU__nSC3_CCI1_QOS5_Cfg          0x20960010UL
#define CPU__nSC3_CCI1_QOS6_Cfg          0x20302030UL
#define CPU__nSC3_CCI1_QOS7_Cfg          0x20AA2200UL
#define CPU__nSC3_CCI1_QOS8_Cfg          0x00002032UL

/*  Cortex A7, SGX540 MXI QoS Control Registers configurations  */
#define CPU__nSC3_MXI_QOS0_Cfg           0x80928092UL
#define CPU__nSC3_MXI_QOS1_Cfg           0x20960020UL
#define CPU__nSC3_MXI_QOS2_Cfg           0x20302030UL
#define CPU__nSC3_MXI_QOS3_Cfg           0x20AA20DCUL
#define CPU__nSC3_MXI_QOS4_Cfg           0x00002032UL
#define CPU__nSC3_MXI_QOS5_Cfg           0x20960020UL
#define CPU__nSC3_MXI_QOS6_Cfg           0x20302030UL
#define CPU__nSC3_MXI_QOS7_Cfg           0x20AA20DCUL
#define CPU__nSC3_MXI_QOS8_Cfg           0x00002032UL

/*  Cortex A7, SGX540 AXI QoS Control Registers configurations */
#define CPU__nSC3_AXI_QOS0_Cfg           0x00820082UL
#define CPU__nSC3_AXI_QOS1_Cfg           0x20960020UL
#define CPU__nSC3_AXI_QOS2_Cfg           0x20302030UL
#define CPU__nSC3_AXI_QOS3_Cfg           0x20AA20FAUL
#define CPU__nSC3_AXI_QOS4_Cfg           0x00002032UL
#define CPU__nSC3_AXI_QOS5_Cfg           0x20960020UL
#define CPU__nSC3_AXI_QOS6_Cfg           0x20302030UL
#define CPU__nSC3_AXI_QOS7_Cfg           0x20AA20FAUL
#define CPU__nSC3_AXI_QOS8_Cfg           0x00002032UL

/* DBSC3 READ QOS Control Register configurations */
#define CPU__nDBSC3_RDQoS_LGCNT_Cfg      0x00000002UL
#define CPU__nDBSC3_RDQoS_TMVAL0_Cfg     0x00002096UL
#define CPU__nDBSC3_RDQoS_TMVAL1_Cfg     0x00002064UL
#define CPU__nDBSC3_RDQoS_TMVAL2_Cfg     0x00002032UL
#define CPU__nDBSC3_RDQoS_TMVAL3_Cfg     0x00002032UL
#define CPU__nDBSC3_RDQoS_RQCTR_Cfg      0x00000001UL
#define CPU__nDBSC3_RDQoS_THRES0_Cfg     0x00002078UL
#define CPU__nDBSC3_RDQoS_THRES1_Cfg     0x0000204BUL
#define CPU__nDBSC3_RDQoS_THRES2_Cfg     0x00001337UL
#define CPU__nDBSC3_RDQoS_THRES3_Cfg     0x00000000UL
#define CPU__nDBSC3_RDQoS_LGQON_Cfg      0x00000001UL

/* DBSC3 Write QOS Control Register configurations */
#define CPU__nDBSC3_WRQoS_LGCNT_Cfg      0x00000002UL
#define CPU__nDBSC3_WRQoS_TMVAL0_Cfg     0x00002096UL
#define CPU__nDBSC3_WRQoS_TMVAL1_Cfg     0x00002064UL
#define CPU__nDBSC3_WRQoS_TMVAL2_Cfg     0x00002050UL
#define CPU__nDBSC3_WRQoS_TMVAL3_Cfg     0x0000203AUL
#define CPU__nDBSC3_WRQoS_RQCTR_Cfg      0x00000001UL
#define CPU__nDBSC3_WRQoS_THRES0_Cfg     0x00002078UL
#define CPU__nDBSC3_WRQoS_THRES1_Cfg     0x0000204BUL
#define CPU__nDBSC3_WRQoS_THRES2_Cfg     0x0000203CUL
#define CPU__nDBSC3_WRQoS_THRES3_Cfg     0x00000000UL
#define CPU__nDBSC3_WRQoS_LGQON_Cfg      0x00000001UL

/* CCI-400 QOS Control Register configurations */
#define CPU__nCCI400_QoS_ARQOS_Cfg       0x00000000UL
#define CPU__nCCI400_QoS_AWQOS_Cfg       0x00000000UL
#define CPU__nCCI400_QoS_MAXOT1_Cfg      0x20002000UL
#define CPU__nCCI400_QoS_MAXOT2_Cfg      0x20002000UL
#define CPU__nCCI400_QoS_MAXOT3_Cfg      0x20002000UL
#define CPU__nCCI400_QoS_CTRL1_Cfg       0x0000000CUL
#define CPU__nCCI400_QoS_CTRL2_Cfg       0x0000000CUL
#define CPU__nCCI400_QoS_CTRL3_Cfg       0x0000000CUL

/* MXI Bus configurations */
/* MXI Bus Transaction Control Register */
#define CPU__nMXI_Tran_MXRTCR_Cfg        0x00000013UL
#define CPU__nMXI_Tran_MXWTCR_Cfg        0x00000011UL
#define CPU__nMXI_Tran_MXSAAR0_Cfg       0x00780080UL
#define CPU__nMXI_Tran_MXSAAR1_Cfg       0x02000800UL

/* MXI Bus QoS Control Register */
#define CPU__nMXI_QoS_VSPDU0_Cfg         0x0000000CUL
#define CPU__nMXI_QoS_VSPDU1_Cfg         0x0000000CUL
#define CPU__nMXI_QoS_DU0_Cfg            0x0000000EUL
#define CPU__nMXI_QoS_DU1_Cfg            0x0000000EUL

/* MXIR Bus QoS Control Register */
#define CPU__nMXIR_QoS_VIN_Cfg            0x0000000EUL

/***************************************************************************
* CA7BAR Registers
****************************************************************************/

/* Cortex-A7 Boot Address Register (CA7BAR) */
#define CPU__nCA7BAR_Reg                0xE6160030UL
#define CPU__nCA7BAR_SBAR_Msk           0xFFFFFC00UL
#define CPU__nCA7BAR_BAREN_Msk          0x00000010UL
#define CPU__nCA7BAR_BTMD_SBAR          0x00000000UL
#define CPU__nCA7BAR_BTMD_BUILTIN       0x00000002UL
#define CPU__nCA7BAR_SBARSHIFT          8U              /* Shift to translate SBAR[39:18] to CA7BAR[31:10] */

/* Cortex-A7 Boot Address Register 2 (CA7BAR2) */
#define CPU__nCA7BAR2_Reg               0xE6160034UL
#define CPU__nCA7BAR2_SBAR_Msk          0xFFFFFC00UL
#define CPU__nCA7BAR2_BAREN_Msk         0x00000010UL
#define CPU__nCA7BAR2_VLD_Msk           0x00000001UL
#define CPU__nCA7BAR2_SBARSHIFT         8U              /* Shift to translate SBAR2[39:18] to CA7BAR2[31:10] */

/* Initial value of Boot Address Registers
 * Ref: R01UH0573EJ0110_R-CarD1.pdf (2017-04-28) page 283 & 284
 * These registers will not be reset by the internal reset. And the CPU core will use this register
 * to select the program location for booting.
 * If you are changing this register, e.g. for the booting of the second CPU, Renesas recommends
 * to set this register back to the initial value, if the second CPU is started. Otherwise with an
 * internal Reset the R-Car D1 will start from the wrong location.
*/
#define CPU__nCA7BAR_INITIALVALUE       0x00000012UL
#define CPU__nCA7BAR2_INITIALVALUE      0x00000000UL


/* Cortex-A7 CPU Wake Up Control Register (CA7WUPCR) */
#define CPU__nCA7WUPCR_Reg              0xE6151010UL
#define CPU__nCA7WUPCR_CPU1WUP_Msk      0x00000002UL

/* Cortex-A7 Reset Control Register (CA7RESCNT) */
#define CPU__nCA7RESCNT_Reg             0xE6160044UL
#define CPU__nCA7RESCNT_CA7CPU1R_Msk    0x00000004UL
#define CPU__nCA7RESCNT_WRITEPATTERN    0x5A5A0003UL

/* CPU1 Power Status Control Register (CA7CPU1CR) */
#define CPU__nCA7CPU1CR_Reg             0xE6151110UL
#define CPU__nCA7CPU1CR_CPUPWR_SLEEP    0x00000000UL    /* Sleep mode */
#define CPU__nCA7CPU1CR_CPUPWR_STANDBY  0x00000003UL    /* Core Standby mode */

/* Mask of the CPUID in Multiprocessor Affinity Register */
#define CPU__nMPIDR_CPUID_Msk           0x00000003UL

/* SYS AXI Configurations */
#define CPU__nSYSAXI_S64_CONF_Cfg        0x00000002UL
#define CPU__nSYSAXI_S64_CTSET0_Cfg      0x00002245UL
#define CPU__nSYSAXI_S64_CTSET1_Cfg      0x00002096UL
#define CPU__nSYSAXI_S64_CTSET2_Cfg      0x00002030UL
#define CPU__nSYSAXI_S64_CTSET3_Cfg      0x00002030UL
#define CPU__nSYSAXI_S64_REQCTR_Cfg      0x00000001UL
#define CPU__nSYSAXI_S64_THRES0_Cfg      0x00002064UL
#define CPU__nSYSAXI_S64_THRES1_Cfg      0x00002004UL
#define CPU__nSYSAXI_S64_THRES2_Cfg      0x00000000UL
#define CPU__nSYSAXI_S64_QON_Cfg         0x00000001UL

#define CPU__nSYSAXI_AVB_CONF_Cfg        0x00000000UL
#define CPU__nSYSAXI_AVB_CTSET0_Cfg      0x000020A6UL
#define CPU__nSYSAXI_AVB_CTSET1_Cfg      0x00000000UL
#define CPU__nSYSAXI_AVB_CTSET2_Cfg      0x00000000UL
#define CPU__nSYSAXI_AVB_CTSET3_Cfg      0x00000000UL
#define CPU__nSYSAXI_AVB_REQCTR_Cfg      0x00000001UL
#define CPU__nSYSAXI_AVB_THRES0_Cfg      0x00002064UL
#define CPU__nSYSAXI_AVB_THRES1_Cfg      0x00002004UL
#define CPU__nSYSAXI_AVB_THRES2_Cfg      0x00000000UL
#define CPU__nSYSAXI_AVB_QON_Cfg         0x00000001UL

#define CPU__nSYSAXI_IMUX0_CONF_Cfg      0x00000002UL
#define CPU__nSYSAXI_IMUX0_CTSET0_Cfg    0x00002245UL
#define CPU__nSYSAXI_IMUX0_CTSET1_Cfg    0x00002096UL
#define CPU__nSYSAXI_IMUX0_CTSET2_Cfg    0x00002030UL
#define CPU__nSYSAXI_IMUX0_CTSET3_Cfg    0x00002030UL
#define CPU__nSYSAXI_IMUX0_REQCTR_Cfg    0x00000001UL
#define CPU__nSYSAXI_IMUX0_THRES0_Cfg    0x00002064UL
#define CPU__nSYSAXI_IMUX0_THRES1_Cfg    0x00002004UL
#define CPU__nSYSAXI_IMUX0_THRES2_Cfg    0x00000000UL
#define CPU__nSYSAXI_IMUX0_QON_Cfg       0x00000001UL

#define CPU__nSYSAXI_IMUX1_CONF_Cfg      0x00000002UL
#define CPU__nSYSAXI_IMUX1_CTSET0_Cfg    0x00002245UL
#define CPU__nSYSAXI_IMUX1_CTSET1_Cfg    0x00002096UL
#define CPU__nSYSAXI_IMUX1_CTSET2_Cfg    0x00002030UL
#define CPU__nSYSAXI_IMUX1_CTSET3_Cfg    0x00002030UL
#define CPU__nSYSAXI_IMUX1_REQCTR_Cfg    0x00000001UL
#define CPU__nSYSAXI_IMUX1_THRES0_Cfg    0x00002064UL
#define CPU__nSYSAXI_IMUX1_THRES1_Cfg    0x00002004UL
#define CPU__nSYSAXI_IMUX1_THRES2_Cfg    0x00000000UL
#define CPU__nSYSAXI_IMUX1_QON_Cfg       0x00000001UL

#define CPU__nSYSAXI_IMUX2_CONF_Cfg      0x00000002UL
#define CPU__nSYSAXI_IMUX2_CTSET0_Cfg    0x00002245UL
#define CPU__nSYSAXI_IMUX2_CTSET1_Cfg    0x00002096UL
#define CPU__nSYSAXI_IMUX2_CTSET2_Cfg    0x00002030UL
#define CPU__nSYSAXI_IMUX2_CTSET3_Cfg    0x00002030UL
#define CPU__nSYSAXI_IMUX2_REQCTR_Cfg    0x00000001UL
#define CPU__nSYSAXI_IMUX2_THRES0_Cfg    0x00002064UL
#define CPU__nSYSAXI_IMUX2_THRES1_Cfg    0x00002004UL
#define CPU__nSYSAXI_IMUX2_THRES2_Cfg    0x00000000UL
#define CPU__nSYSAXI_IMUX2_QON_Cfg       0x00000001UL

#define CPU__nSYSAXI_MMUDS_CONF_Cfg      0x00000001UL
#define CPU__nSYSAXI_MMUDS_CTSET0_Cfg    0x00002004UL
#define CPU__nSYSAXI_MMUDS_CTSET1_Cfg    0x00002096UL
#define CPU__nSYSAXI_MMUDS_CTSET2_Cfg    0x00002030UL
#define CPU__nSYSAXI_MMUDS_CTSET3_Cfg    0x00002030UL
#define CPU__nSYSAXI_MMUDS_REQCTR_Cfg    0x00000001UL
#define CPU__nSYSAXI_MMUDS_THRES0_Cfg    0x00002064UL
#define CPU__nSYSAXI_MMUDS_THRES1_Cfg    0x00002004UL
#define CPU__nSYSAXI_MMUDS_THRES2_Cfg    0x00000000UL
#define CPU__nSYSAXI_MMUDS_QON_Cfg       0x00000001UL

#define CPU__nSYSAXI_MMUM_CONF_Cfg       0x00000001UL
#define CPU__nSYSAXI_MMUM_CTSET0_Cfg     0x00002004UL
#define CPU__nSYSAXI_MMUM_CTSET1_Cfg     0x00002096UL
#define CPU__nSYSAXI_MMUM_CTSET2_Cfg     0x00002030UL
#define CPU__nSYSAXI_MMUM_CTSET3_Cfg     0x00002030UL
#define CPU__nSYSAXI_MMUM_REQCTR_Cfg     0x00000001UL
#define CPU__nSYSAXI_MMUM_THRES0_Cfg     0x00002064UL
#define CPU__nSYSAXI_MMUM_THRES1_Cfg     0x00002004UL
#define CPU__nSYSAXI_MMUM_THRES2_Cfg     0x00000000UL
#define CPU__nSYSAXI_MMUM_QON_Cfg        0x00000001UL

#define CPU__nSYSAXI_MMUS0_CONF_Cfg      0x00000001UL
#define CPU__nSYSAXI_MMUS0_CTSET0_Cfg    0x00002004UL
#define CPU__nSYSAXI_MMUS0_CTSET1_Cfg    0x00002096UL
#define CPU__nSYSAXI_MMUS0_CTSET2_Cfg    0x00002030UL
#define CPU__nSYSAXI_MMUS0_CTSET3_Cfg    0x00002030UL
#define CPU__nSYSAXI_MMUS0_REQCTR_Cfg    0x00000001UL
#define CPU__nSYSAXI_MMUS0_THRES0_Cfg    0x00002064UL
#define CPU__nSYSAXI_MMUS0_THRES1_Cfg    0x00002004UL
#define CPU__nSYSAXI_MMUS0_THRES2_Cfg    0x00000000UL
#define CPU__nSYSAXI_MMUS0_QON_Cfg       0x00000001UL

#define CPU__nSYSAXI_MMUS1_CONF_Cfg      0x00000001UL
#define CPU__nSYSAXI_MMUS1_CTSET0_Cfg    0x00002004UL
#define CPU__nSYSAXI_MMUS1_CTSET1_Cfg    0x00002096UL
#define CPU__nSYSAXI_MMUS1_CTSET2_Cfg    0x00002030UL
#define CPU__nSYSAXI_MMUS1_CTSET3_Cfg    0x00002030UL
#define CPU__nSYSAXI_MMUS1_REQCTR_Cfg    0x00000001UL
#define CPU__nSYSAXI_MMUS1_THRES0_Cfg    0x00002064UL
#define CPU__nSYSAXI_MMUS1_THRES1_Cfg    0x00002004UL
#define CPU__nSYSAXI_MMUS1_THRES2_Cfg    0x00000000UL
#define CPU__nSYSAXI_MMUS1_QON_Cfg       0x00000001UL

#define CPU__nSYSAXI_SDS0_CONF_Cfg       0x00000000UL
#define CPU__nSYSAXI_SDS0_CTSET0_Cfg     0x000020A6UL
#define CPU__nSYSAXI_SDS0_CTSET1_Cfg     0x00000000UL
#define CPU__nSYSAXI_SDS0_CTSET2_Cfg     0x00000000UL
#define CPU__nSYSAXI_SDS0_CTSET3_Cfg     0x00000000UL
#define CPU__nSYSAXI_SDS0_REQCTR_Cfg     0x00000001UL
#define CPU__nSYSAXI_SDS0_THRES0_Cfg     0x00002064UL
#define CPU__nSYSAXI_SDS0_THRES1_Cfg     0x00002004UL
#define CPU__nSYSAXI_SDS0_THRES2_Cfg     0x00000000UL
#define CPU__nSYSAXI_SDS0_QON_Cfg        0x00000001UL

#define CPU__nSYSAXI_SDS1_CONF_Cfg       0x00000001UL
#define CPU__nSYSAXI_SDS1_CTSET0_Cfg     0x00002245UL
#define CPU__nSYSAXI_SDS1_CTSET1_Cfg     0x00000000UL
#define CPU__nSYSAXI_SDS1_CTSET2_Cfg     0x00000000UL
#define CPU__nSYSAXI_SDS1_CTSET3_Cfg     0x00000000UL
#define CPU__nSYSAXI_SDS1_REQCTR_Cfg     0x00000009UL
#define CPU__nSYSAXI_SDS1_THRES0_Cfg     0x00002064UL
#define CPU__nSYSAXI_SDS1_THRES1_Cfg     0x00002004UL
#define CPU__nSYSAXI_SDS1_THRES2_Cfg     0x00000000UL
#define CPU__nSYSAXI_SDS1_QON_Cfg        0x00000001UL

#define CPU__nSYSAXI_USB20_CONF_Cfg      0x00000000UL
#define CPU__nSYSAXI_USB20_CTSET0_Cfg    0x00002053UL
#define CPU__nSYSAXI_USB20_CTSET1_Cfg    0x00000000UL
#define CPU__nSYSAXI_USB20_CTSET2_Cfg    0x00000000UL
#define CPU__nSYSAXI_USB20_CTSET3_Cfg    0x00000000UL
#define CPU__nSYSAXI_USB20_REQCTR_Cfg    0x00000001UL
#define CPU__nSYSAXI_USB20_THRES0_Cfg    0x00002064UL
#define CPU__nSYSAXI_USB20_THRES1_Cfg    0x00002004UL
#define CPU__nSYSAXI_USB20_THRES2_Cfg    0x00000000UL
#define CPU__nSYSAXI_USB20_QON_Cfg       0x00000001UL

#define CPU__nSYSAXI_MLB_CONF_Cfg        0x00000000UL
#define CPU__nSYSAXI_MLB_CTSET0_Cfg      0x00002053UL
#define CPU__nSYSAXI_MLB_CTSET1_Cfg      0x00000000UL
#define CPU__nSYSAXI_MLB_CTSET2_Cfg      0x00000000UL
#define CPU__nSYSAXI_MLB_CTSET3_Cfg      0x00000000UL
#define CPU__nSYSAXI_MLB_REQCTR_Cfg      0x00000001UL
#define CPU__nSYSAXI_MLB_THRES0_Cfg      0x00002064UL
#define CPU__nSYSAXI_MLB_THRES1_Cfg      0x00002004UL
#define CPU__nSYSAXI_MLB_THRES2_Cfg      0x00000000UL
#define CPU__nSYSAXI_MLB_QON_Cfg         0x00000001UL

#define CPU__nSYSAXI_AX2M_CONF_Cfg       0x00000002UL
#define CPU__nSYSAXI_AX2M_CTSET0_Cfg     0x00002245UL
#define CPU__nSYSAXI_AX2M_CTSET1_Cfg     0x00000000UL
#define CPU__nSYSAXI_AX2M_CTSET2_Cfg     0x00000000UL
#define CPU__nSYSAXI_AX2M_CTSET3_Cfg     0x00000000UL
#define CPU__nSYSAXI_AX2M_REQCTR_Cfg     0x00000001UL
#define CPU__nSYSAXI_AX2M_THRES0_Cfg     0x00002064UL
#define CPU__nSYSAXI_AX2M_THRES1_Cfg     0x00002004UL
#define CPU__nSYSAXI_AX2M_THRES2_Cfg     0x00000000UL
#define CPU__nSYSAXI_AX2M_QON_Cfg        0x00000001UL

#define CPU__nSYSAXI_CCI_CONF_Cfg        0x00000002UL
#define CPU__nSYSAXI_CCI_CTSET0_Cfg      0x00002245UL
#define CPU__nSYSAXI_CCI_CTSET1_Cfg      0x00000000UL
#define CPU__nSYSAXI_CCI_CTSET2_Cfg      0x00000000UL
#define CPU__nSYSAXI_CCI_CTSET3_Cfg      0x00000000UL
#define CPU__nSYSAXI_CCI_REQCTR_Cfg      0x00000001UL
#define CPU__nSYSAXI_CCI_THRES0_Cfg      0x00002064UL
#define CPU__nSYSAXI_CCI_THRES1_Cfg      0x00002004UL
#define CPU__nSYSAXI_CCI_THRES2_Cfg      0x00000000UL
#define CPU__nSYSAXI_CCI_QON_Cfg         0x00000001UL

#define CPU__nSYSAXI_CS_CONF_Cfg         0x00000000UL
#define CPU__nSYSAXI_CS_CTSET0_Cfg       0x00002053UL
#define CPU__nSYSAXI_CS_CTSET1_Cfg       0x00000000UL
#define CPU__nSYSAXI_CS_CTSET2_Cfg       0x00000000UL
#define CPU__nSYSAXI_CS_CTSET3_Cfg       0x00000000UL
#define CPU__nSYSAXI_CS_REQCTR_Cfg       0x00000001UL
#define CPU__nSYSAXI_CS_THRES0_Cfg       0x00002064UL
#define CPU__nSYSAXI_CS_THRES1_Cfg       0x00002004UL
#define CPU__nSYSAXI_CS_THRES2_Cfg       0x00000000UL
#define CPU__nSYSAXI_CS_QON_Cfg          0x00000001UL

#define CPU__nSYSAXI_DDM_CONF_Cfg        0x00000000UL
#define CPU__nSYSAXI_DDM_CTSET0_Cfg      0x000020A6UL
#define CPU__nSYSAXI_DDM_CTSET1_Cfg      0x00000000UL
#define CPU__nSYSAXI_DDM_CTSET2_Cfg      0x00000000UL
#define CPU__nSYSAXI_DDM_CTSET3_Cfg      0x00000000UL
#define CPU__nSYSAXI_DDM_REQCTR_Cfg      0x00000001UL
#define CPU__nSYSAXI_DDM_THRES0_Cfg      0x00002064UL
#define CPU__nSYSAXI_DDM_THRES1_Cfg      0x00002004UL
#define CPU__nSYSAXI_DDM_THRES2_Cfg      0x00000000UL
#define CPU__nSYSAXI_DDM_QON_Cfg         0x00000001UL

#define CPU__nSYSAXI_NANDC_CONF_Cfg      0x00000000UL
#define CPU__nSYSAXI_NANDC_CTSET0_Cfg    0x00002053UL
#define CPU__nSYSAXI_NANDC_CTSET1_Cfg    0x00000000UL
#define CPU__nSYSAXI_NANDC_CTSET2_Cfg    0x00000000UL
#define CPU__nSYSAXI_NANDC_CTSET3_Cfg    0x00000000UL
#define CPU__nSYSAXI_NANDC_REQCTR_Cfg    0x00000001UL
#define CPU__nSYSAXI_NANDC_THRES0_Cfg    0x00002064UL
#define CPU__nSYSAXI_NANDC_THRES1_Cfg    0x00002004UL
#define CPU__nSYSAXI_NANDC_THRES2_Cfg    0x00000000UL
#define CPU__nSYSAXI_NANDC_QON_Cfg       0x00000001UL

#define CPU__nSYSAXI_DHDX_CONF_Cfg       0x00000002UL
#define CPU__nSYSAXI_DHDX_CTSET0_Cfg     0x00002245UL
#define CPU__nSYSAXI_DHDX_CTSET1_Cfg     0x00000000UL
#define CPU__nSYSAXI_DHDX_CTSET2_Cfg     0x00000000UL
#define CPU__nSYSAXI_DHDX_CTSET3_Cfg     0x00000000UL
#define CPU__nSYSAXI_DHDX_REQCTR_Cfg     0x00000001UL
#define CPU__nSYSAXI_DHDX_THRES0_Cfg     0x00002064UL
#define CPU__nSYSAXI_DHDX_THRES1_Cfg     0x00002004UL
#define CPU__nSYSAXI_DHDX_THRES2_Cfg     0x00000000UL
#define CPU__nSYSAXI_DHDX_QON_Cfg        0x00000001UL

#define CPU__nSYSAXI_SDM0_CONF_Cfg       0x00000000UL
#define CPU__nSYSAXI_SDM0_CTSET0_Cfg     0x0000214CUL
#define CPU__nSYSAXI_SDM0_CTSET1_Cfg     0x00000000UL
#define CPU__nSYSAXI_SDM0_CTSET2_Cfg     0x00000000UL
#define CPU__nSYSAXI_SDM0_CTSET3_Cfg     0x00000000UL
#define CPU__nSYSAXI_SDM0_REQCTR_Cfg     0x00000001UL
#define CPU__nSYSAXI_SDM0_THRES0_Cfg     0x00002064UL
#define CPU__nSYSAXI_SDM0_THRES1_Cfg     0x00002004UL
#define CPU__nSYSAXI_SDM0_THRES2_Cfg     0x00000000UL
#define CPU__nSYSAXI_SDM0_QON_Cfg        0x00000001UL

#define CPU__nSYSAXI_SDM1_CONF_Cfg       0x00000001UL
#define CPU__nSYSAXI_SDM1_CTSET0_Cfg     0x00002245UL
#define CPU__nSYSAXI_SDM1_CTSET1_Cfg     0x00000000UL
#define CPU__nSYSAXI_SDM1_CTSET2_Cfg     0x00000000UL
#define CPU__nSYSAXI_SDM1_CTSET3_Cfg     0x00000000UL
#define CPU__nSYSAXI_SDM1_REQCTR_Cfg     0x00000009UL
#define CPU__nSYSAXI_SDM1_THRES0_Cfg     0x00002064UL
#define CPU__nSYSAXI_SDM1_THRES1_Cfg     0x00002004UL
#define CPU__nSYSAXI_SDM1_THRES2_Cfg     0x00000000UL
#define CPU__nSYSAXI_SDM1_QON_Cfg        0x00000001UL

#define CPU__nSYSAXI_TRKF_CONF_Cfg       0x00000000UL
#define CPU__nSYSAXI_TRKF_CTSET0_Cfg     0x000020A6UL
#define CPU__nSYSAXI_TRKF_CTSET1_Cfg     0x00000000UL
#define CPU__nSYSAXI_TRKF_CTSET2_Cfg     0x00000000UL
#define CPU__nSYSAXI_TRKF_CTSET3_Cfg     0x00000000UL
#define CPU__nSYSAXI_TRKF_REQCTR_Cfg     0x00000001UL
#define CPU__nSYSAXI_TRKF_THRES0_Cfg     0x00002064UL
#define CPU__nSYSAXI_TRKF_THRES1_Cfg     0x00002004UL
#define CPU__nSYSAXI_TRKF_THRES2_Cfg     0x00000000UL
#define CPU__nSYSAXI_TRKF_QON_Cfg        0x00000001UL

#define CPU__nSYSAXI_UDM0_CONF_Cfg       0x00000000UL
#define CPU__nSYSAXI_UDM0_CTSET0_Cfg     0x00002053UL
#define CPU__nSYSAXI_UDM0_CTSET1_Cfg     0x00000000UL
#define CPU__nSYSAXI_UDM0_CTSET2_Cfg     0x00000000UL
#define CPU__nSYSAXI_UDM0_CTSET3_Cfg     0x00000000UL
#define CPU__nSYSAXI_UDM0_REQCTR_Cfg     0x00000001UL
#define CPU__nSYSAXI_UDM0_THRES0_Cfg     0x00002064UL
#define CPU__nSYSAXI_UDM0_THRES1_Cfg     0x00002004UL
#define CPU__nSYSAXI_UDM0_THRES2_Cfg     0x00000000UL
#define CPU__nSYSAXI_UDM0_QON_Cfg        0x00000001UL

#define CPU__nSYSAXI_UDM1_CONF_Cfg       0x00000000UL
#define CPU__nSYSAXI_UDM1_CTSET0_Cfg     0x00002053UL
#define CPU__nSYSAXI_UDM1_CTSET1_Cfg     0x00000000UL
#define CPU__nSYSAXI_UDM1_CTSET2_Cfg     0x00000000UL
#define CPU__nSYSAXI_UDM1_CTSET3_Cfg     0x00000000UL
#define CPU__nSYSAXI_UDM1_REQCTR_Cfg     0x00000001UL
#define CPU__nSYSAXI_UDM1_THRES0_Cfg     0x00002064UL
#define CPU__nSYSAXI_UDM1_THRES1_Cfg     0x00002004UL
#define CPU__nSYSAXI_UDM1_THRES2_Cfg     0x00000000UL
#define CPU__nSYSAXI_UDM1_QON_Cfg        0x00000001UL

#define CPU__nSYSAXI_S256SYX_CONF_Cfg    0x00000002UL
#define CPU__nSYSAXI_S256SYX_CTSET0_Cfg  0x000020EBUL
#define CPU__nSYSAXI_S256SYX_CTSET1_Cfg  0x00002096UL
#define CPU__nSYSAXI_S256SYX_CTSET2_Cfg  0x00002030UL
#define CPU__nSYSAXI_S256SYX_CTSET3_Cfg  0x00002030UL
#define CPU__nSYSAXI_S256SYX_REQCTR_Cfg  0x00000001UL
#define CPU__nSYSAXI_S256SYX_THRES0_Cfg  0x00002064UL
#define CPU__nSYSAXI_S256SYX_THRES1_Cfg  0x00002004UL
#define CPU__nSYSAXI_S256SYX_THRES2_Cfg  0x00000000UL
#define CPU__nSYSAXI_S256SYX_QON_Cfg     0x00000001UL

#define CPU__nSYSAXI_S256MXI_CONF_Cfg    0x00000002UL
#define CPU__nSYSAXI_S256MXI_CTSET0_Cfg  0x000020EBUL
#define CPU__nSYSAXI_S256MXI_CTSET1_Cfg  0x00002096UL
#define CPU__nSYSAXI_S256MXI_CTSET2_Cfg  0x00002030UL
#define CPU__nSYSAXI_S256MXI_CTSET3_Cfg  0x00002030UL
#define CPU__nSYSAXI_S256MXI_REQCTR_Cfg  0x00000001UL
#define CPU__nSYSAXI_S256MXI_THRES0_Cfg  0x00002064UL
#define CPU__nSYSAXI_S256MXI_THRES1_Cfg  0x00002004UL
#define CPU__nSYSAXI_S256MXI_THRES2_Cfg  0x00000000UL
#define CPU__nSYSAXI_S256MXI_QON_Cfg     0x00000001UL

/* CCI AXI Configurations */
#define CPU__nCCIAXI_MMUS0_CONF_Cfg      0x00000001UL
#define CPU__nCCIAXI_MMUS0_CTSET0_Cfg    0x00002004UL
#define CPU__nCCIAXI_MMUS0_CTSET1_Cfg    0x00002096UL
#define CPU__nCCIAXI_MMUS0_CTSET2_Cfg    0x00002030UL
#define CPU__nCCIAXI_MMUS0_CTSET3_Cfg    0x00002030UL
#define CPU__nCCIAXI_MMUS0_REQCTR_Cfg    0x00000001UL
#define CPU__nCCIAXI_MMUS0_THRES0_Cfg    0x00002064UL
#define CPU__nCCIAXI_MMUS0_THRES1_Cfg    0x00002004UL
#define CPU__nCCIAXI_MMUS0_THRES2_Cfg    0x00000000UL
#define CPU__nCCIAXI_MMUS0_QON_Cfg       0x00000001UL

#define CPU__nCCIAXI_MMUS1_CONF_Cfg      0x00000001UL
#define CPU__nCCIAXI_MMUS1_CTSET0_Cfg    0x00002004UL
#define CPU__nCCIAXI_MMUS1_CTSET1_Cfg    0x00002096UL
#define CPU__nCCIAXI_MMUS1_CTSET2_Cfg    0x00002030UL
#define CPU__nCCIAXI_MMUS1_CTSET3_Cfg    0x00002030UL
#define CPU__nCCIAXI_MMUS1_REQCTR_Cfg    0x00000001UL
#define CPU__nCCIAXI_MMUS1_THRES0_Cfg    0x00002064UL
#define CPU__nCCIAXI_MMUS1_THRES1_Cfg    0x00002004UL
#define CPU__nCCIAXI_MMUS1_THRES2_Cfg    0x00000000UL
#define CPU__nCCIAXI_MMUS1_QON_Cfg       0x00000001UL

#define CPU__nCCIAXI_SYX2_CONF_Cfg       0x00000002UL
#define CPU__nCCIAXI_SYX2_CTSET0_Cfg     0x00002245UL
#define CPU__nCCIAXI_SYX2_CTSET1_Cfg     0x00002096UL
#define CPU__nCCIAXI_SYX2_CTSET2_Cfg     0x00002030UL
#define CPU__nCCIAXI_SYX2_CTSET3_Cfg     0x00002030UL
#define CPU__nCCIAXI_SYX2_REQCTR_Cfg     0x00000001UL
#define CPU__nCCIAXI_SYX2_THRES0_Cfg     0x00002064UL
#define CPU__nCCIAXI_SYX2_THRES1_Cfg     0x00002004UL
#define CPU__nCCIAXI_SYX2_THRES2_Cfg     0x00000000UL
#define CPU__nCCIAXI_SYX2_QON_Cfg        0x00000001UL

#define CPU__nCCIAXI_MMUDS_CONF_Cfg      0x00000001UL
#define CPU__nCCIAXI_MMUDS_CTSET0_Cfg    0x00002004UL
#define CPU__nCCIAXI_MMUDS_CTSET1_Cfg    0x00002096UL
#define CPU__nCCIAXI_MMUDS_CTSET2_Cfg    0x00002030UL
#define CPU__nCCIAXI_MMUDS_CTSET3_Cfg    0x00002030UL
#define CPU__nCCIAXI_MMUDS_REQCTR_Cfg    0x00000001UL
#define CPU__nCCIAXI_MMUDS_THRES0_Cfg    0x00002064UL
#define CPU__nCCIAXI_MMUDS_THRES1_Cfg    0x00002004UL
#define CPU__nCCIAXI_MMUDS_THRES2_Cfg    0x00000000UL
#define CPU__nCCIAXI_MMUDS_QON_Cfg       0x00000001UL

#define CPU__nCCIAXI_MMUM_CONF_Cfg       0x00000001UL
#define CPU__nCCIAXI_MMUM_CTSET0_Cfg     0x00002004UL
#define CPU__nCCIAXI_MMUM_CTSET1_Cfg     0x00002096UL
#define CPU__nCCIAXI_MMUM_CTSET2_Cfg     0x00002030UL
#define CPU__nCCIAXI_MMUM_CTSET3_Cfg     0x00002030UL
#define CPU__nCCIAXI_MMUM_REQCTR_Cfg     0x00000001UL
#define CPU__nCCIAXI_MMUM_THRES0_Cfg     0x00002064UL
#define CPU__nCCIAXI_MMUM_THRES1_Cfg     0x00002004UL
#define CPU__nCCIAXI_MMUM_THRES2_Cfg     0x00000000UL
#define CPU__nCCIAXI_MMUM_QON_Cfg        0x00000001UL

#define CPU__nCCIAXI_MXI_CONF_Cfg        0x00000002UL
#define CPU__nCCIAXI_MXI_CTSET0_Cfg      0x00002245UL
#define CPU__nCCIAXI_MXI_CTSET1_Cfg      0x00002096UL
#define CPU__nCCIAXI_MXI_CTSET2_Cfg      0x00002030UL
#define CPU__nCCIAXI_MXI_CTSET3_Cfg      0x00002030UL
#define CPU__nCCIAXI_MXI_REQCTR_Cfg      0x00000001UL
#define CPU__nCCIAXI_MXI_THRES0_Cfg      0x00002064UL
#define CPU__nCCIAXI_MXI_THRES1_Cfg      0x00002004UL
#define CPU__nCCIAXI_MXI_THRES2_Cfg      0x00000000UL
#define CPU__nCCIAXI_MXI_QON_Cfg         0x00000001UL

#define CPU__nMEDAXI_MXR_CONF_Cfg        0x00000002UL
#define CPU__nMEDAXI_MXR_CTSET0_Cfg      0x000020DCUL
#define CPU__nMEDAXI_MXR_CTSET1_Cfg      0x00002096UL
#define CPU__nMEDAXI_MXR_CTSET2_Cfg      0x00002030UL
#define CPU__nMEDAXI_MXR_CTSET3_Cfg      0x00002030UL
#define CPU__nMEDAXI_MXR_REQCTR_Cfg      0x00000020UL
#define CPU__nMEDAXI_MXR_THRES0_Cfg      0x000020AAUL
#define CPU__nMEDAXI_MXR_THRES1_Cfg      0x00002032UL
#define CPU__nMEDAXI_MXR_THRES2_Cfg      0x00000001UL
#define CPU__nMEDAXI_MXR_QON_Cfg         0x00000000UL

#define CPU__nMEDAXI_MXW_CONF_Cfg        0x00000002UL
#define CPU__nMEDAXI_MXW_CTSET0_Cfg      0x000020DCUL
#define CPU__nMEDAXI_MXW_CTSET1_Cfg      0x00002096UL
#define CPU__nMEDAXI_MXW_CTSET2_Cfg      0x00002030UL
#define CPU__nMEDAXI_MXW_CTSET3_Cfg      0x00002030UL
#define CPU__nMEDAXI_MXW_REQCTR_Cfg      0x00000020UL
#define CPU__nMEDAXI_MXW_THRES0_Cfg      0x000020AAUL
#define CPU__nMEDAXI_MXW_THRES1_Cfg      0x00002032UL
#define CPU__nMEDAXI_MXW_THRES2_Cfg      0x00000001UL
#define CPU__nMEDAXI_MXW_QON_Cfg         0x00000000UL

#define CPU__nMEDAXI_VIN0W_CONF_Cfg      0x00000001UL
#define CPU__nMEDAXI_VIN0W_CTSET0_Cfg    0x00001FF0UL
#define CPU__nMEDAXI_VIN0W_CTSET1_Cfg    0x00000000UL
#define CPU__nMEDAXI_VIN0W_CTSET2_Cfg    0x00000000UL
#define CPU__nMEDAXI_VIN0W_CTSET3_Cfg    0x00000000UL
#define CPU__nMEDAXI_VIN0W_REQCTR_Cfg    0x00000020UL
#define CPU__nMEDAXI_VIN0W_THRES0_Cfg    0x00002064UL
#define CPU__nMEDAXI_VIN0W_THRES1_Cfg    0x00002004UL
#define CPU__nMEDAXI_VIN0W_THRES2_Cfg    0x00002001UL
#define CPU__nMEDAXI_VIN0W_QON_Cfg       0x00000001UL

#define CPU__nMEDAXI_VSPDU0CR_CONF_Cfg   0x00000001UL
#define CPU__nMEDAXI_VSPDU0CR_CTSET0_Cfg 0x00002190UL
#define CPU__nMEDAXI_VSPDU0CR_CTSET1_Cfg 0x00000000UL
#define CPU__nMEDAXI_VSPDU0CR_CTSET2_Cfg 0x00000000UL
#define CPU__nMEDAXI_VSPDU0CR_CTSET3_Cfg 0x00000000UL
#define CPU__nMEDAXI_VSPDU0CR_REQCTR_Cfg 0x00000020UL
#define CPU__nMEDAXI_VSPDU0CR_THRES0_Cfg 0x00002064UL
#define CPU__nMEDAXI_VSPDU0CR_THRES1_Cfg 0x00002004UL
#define CPU__nMEDAXI_VSPDU0CR_THRES2_Cfg 0x00000001UL
#define CPU__nMEDAXI_VSPDU0CR_QON_Cfg    0x00000001UL

#define CPU__nMEDAXI_VSPDU0CW_CONF_Cfg   0x00000001UL
#define CPU__nMEDAXI_VSPDU0CW_CTSET0_Cfg 0x00002190UL
#define CPU__nMEDAXI_VSPDU0CW_CTSET1_Cfg 0x00000000UL
#define CPU__nMEDAXI_VSPDU0CW_CTSET2_Cfg 0x00000000UL
#define CPU__nMEDAXI_VSPDU0CW_CTSET3_Cfg 0x00000000UL
#define CPU__nMEDAXI_VSPDU0CW_REQCTR_Cfg 0x00000020UL
#define CPU__nMEDAXI_VSPDU0CW_THRES0_Cfg 0x00000001UL
#define CPU__nMEDAXI_VSPDU0CW_THRES1_Cfg 0x00000001UL
#define CPU__nMEDAXI_VSPDU0CW_THRES2_Cfg 0x00000001UL
#define CPU__nMEDAXI_VSPDU0CW_QON_Cfg    0x00000001UL

#define CPU__nMEDAXI_VSPD0R_CONF_Cfg     0x00000003UL
#define CPU__nMEDAXI_VSPD0R_CTSET0_Cfg   0x000020C8UL
#define CPU__nMEDAXI_VSPD0R_CTSET1_Cfg   0x00000000UL
#define CPU__nMEDAXI_VSPD0R_CTSET2_Cfg   0x00000000UL
#define CPU__nMEDAXI_VSPD0R_CTSET3_Cfg   0x00000000UL
#define CPU__nMEDAXI_VSPD0R_REQCTR_Cfg   0x00000001UL
#define CPU__nMEDAXI_VSPD0R_THRES0_Cfg   0x00002064UL
#define CPU__nMEDAXI_VSPD0R_THRES1_Cfg   0x00002004UL
#define CPU__nMEDAXI_VSPD0R_THRES2_Cfg   0x00000001UL
#define CPU__nMEDAXI_VSPD0R_QON_Cfg      0x00000001UL

#define CPU__nMEDAXI_VSPD0W_CONF_Cfg     0x00000003UL
#define CPU__nMEDAXI_VSPD0W_CTSET0_Cfg   0x000020C8UL
#define CPU__nMEDAXI_VSPD0W_CTSET1_Cfg   0x00000000UL
#define CPU__nMEDAXI_VSPD0W_CTSET2_Cfg   0x00000000UL
#define CPU__nMEDAXI_VSPD0W_CTSET3_Cfg   0x00000000UL
#define CPU__nMEDAXI_VSPD0W_REQCTR_Cfg   0x00000001UL
#define CPU__nMEDAXI_VSPD0W_THRES0_Cfg   0x00002064UL
#define CPU__nMEDAXI_VSPD0W_THRES1_Cfg   0x00002004UL
#define CPU__nMEDAXI_VSPD0W_THRES2_Cfg   0x00000001UL
#define CPU__nMEDAXI_VSPD0W_QON_Cfg      0x00000001UL

#define CPU__nMEDAXI_VSPDU1CR_CONF_Cfg   0x00000001UL
#define CPU__nMEDAXI_VSPDU1CR_CTSET0_Cfg 0x00002190UL
#define CPU__nMEDAXI_VSPDU1CR_CTSET1_Cfg 0x00000000UL
#define CPU__nMEDAXI_VSPDU1CR_CTSET2_Cfg 0x00000000UL
#define CPU__nMEDAXI_VSPDU1CR_CTSET3_Cfg 0x00000000UL
#define CPU__nMEDAXI_VSPDU1CR_REQCTR_Cfg 0x00000020UL
#define CPU__nMEDAXI_VSPDU1CR_THRES0_Cfg 0x00002064UL
#define CPU__nMEDAXI_VSPDU1CR_THRES1_Cfg 0x00002004UL
#define CPU__nMEDAXI_VSPDU1CR_THRES2_Cfg 0x00000001UL
#define CPU__nMEDAXI_VSPDU1CR_QON_Cfg    0x00000001UL

#define CPU__nMEDAXI_VSPDU1CW_CONF_Cfg   0x00000001UL
#define CPU__nMEDAXI_VSPDU1CW_CTSET0_Cfg 0x00002190UL
#define CPU__nMEDAXI_VSPDU1CW_CTSET1_Cfg 0x00000000UL
#define CPU__nMEDAXI_VSPDU1CW_CTSET2_Cfg 0x00000000UL
#define CPU__nMEDAXI_VSPDU1CW_CTSET3_Cfg 0x00000000UL
#define CPU__nMEDAXI_VSPDU1CW_REQCTR_Cfg 0x00000020UL
#define CPU__nMEDAXI_VSPDU1CW_THRES0_Cfg 0x00000001UL
#define CPU__nMEDAXI_VSPDU1CW_THRES1_Cfg 0x00000001UL
#define CPU__nMEDAXI_VSPDU1CW_THRES2_Cfg 0x00000001UL
#define CPU__nMEDAXI_VSPDU1CW_QON_Cfg    0x00000001UL

#define CPU__nMEDAXI_VSPD1R_CONF_Cfg     0x00000003UL
#define CPU__nMEDAXI_VSPD1R_CTSET0_Cfg   0x000020C8UL
#define CPU__nMEDAXI_VSPD1R_CTSET1_Cfg   0x00000000UL
#define CPU__nMEDAXI_VSPD1R_CTSET2_Cfg   0x00000000UL
#define CPU__nMEDAXI_VSPD1R_CTSET3_Cfg   0x00000000UL
#define CPU__nMEDAXI_VSPD1R_REQCTR_Cfg   0x00000001UL
#define CPU__nMEDAXI_VSPD1R_THRES0_Cfg   0x00002064UL
#define CPU__nMEDAXI_VSPD1R_THRES1_Cfg   0x00002004UL
#define CPU__nMEDAXI_VSPD1R_THRES2_Cfg   0x00000001UL
#define CPU__nMEDAXI_VSPD1R_QON_Cfg      0x00000001UL

#define CPU__nMEDAXI_VSPD1W_CONF_Cfg     0x00000003UL
#define CPU__nMEDAXI_VSPD1W_CTSET0_Cfg   0x000020C8UL
#define CPU__nMEDAXI_VSPD1W_CTSET1_Cfg   0x00000000UL
#define CPU__nMEDAXI_VSPD1W_CTSET2_Cfg   0x00000000UL
#define CPU__nMEDAXI_VSPD1W_CTSET3_Cfg   0x00000000UL
#define CPU__nMEDAXI_VSPD1W_REQCTR_Cfg   0x00000001UL
#define CPU__nMEDAXI_VSPD1W_THRES0_Cfg   0x00002064UL
#define CPU__nMEDAXI_VSPD1W_THRES1_Cfg   0x00002004UL
#define CPU__nMEDAXI_VSPD1W_THRES2_Cfg   0x00000001UL
#define CPU__nMEDAXI_VSPD1W_QON_Cfg      0x00000001UL
/* ======== DU ======== */
#define CPU__nMEDAXI_DU0R_CONF_Cfg       0x00000003UL
#define CPU__nMEDAXI_DU0R_CTSET0_Cfg     0x00002063UL
#define CPU__nMEDAXI_DU0R_CTSET1_Cfg     0x00000000UL
#define CPU__nMEDAXI_DU0R_CTSET2_Cfg     0x00000000UL
#define CPU__nMEDAXI_DU0R_CTSET3_Cfg     0x00000000UL
#define CPU__nMEDAXI_DU0R_REQCTR_Cfg     0x00000001UL
#define CPU__nMEDAXI_DU0R_THRES0_Cfg     0x00002064UL
#define CPU__nMEDAXI_DU0R_THRES1_Cfg     0x00002004UL
#define CPU__nMEDAXI_DU0R_THRES2_Cfg     0x00000001UL
#define CPU__nMEDAXI_DU0R_QON_Cfg        0x00000001UL

#define CPU__nMEDAXI_DU0W_CONF_Cfg       0x00000003UL
#define CPU__nMEDAXI_DU0W_CTSET0_Cfg     0x00002063UL
#define CPU__nMEDAXI_DU0W_CTSET1_Cfg     0x00000000UL
#define CPU__nMEDAXI_DU0W_CTSET2_Cfg     0x00000000UL
#define CPU__nMEDAXI_DU0W_CTSET3_Cfg     0x00000000UL
#define CPU__nMEDAXI_DU0W_REQCTR_Cfg     0x00000001UL
#define CPU__nMEDAXI_DU0W_THRES0_Cfg     0x00002064UL
#define CPU__nMEDAXI_DU0W_THRES1_Cfg     0x00002004UL
#define CPU__nMEDAXI_DU0W_THRES2_Cfg     0x00000001UL
#define CPU__nMEDAXI_DU0W_QON_Cfg        0x00000001UL

#define CPU__nMEDAXI_DU1R_CONF_Cfg       0x00000003UL
#define CPU__nMEDAXI_DU1R_CTSET0_Cfg     0x00002063UL
#define CPU__nMEDAXI_DU1R_CTSET1_Cfg     0x00000000UL
#define CPU__nMEDAXI_DU1R_CTSET2_Cfg     0x00000000UL
#define CPU__nMEDAXI_DU1R_CTSET3_Cfg     0x00000000UL
#define CPU__nMEDAXI_DU1R_REQCTR_Cfg     0x00000001UL
#define CPU__nMEDAXI_DU1R_THRES0_Cfg     0x00002064UL
#define CPU__nMEDAXI_DU1R_THRES1_Cfg     0x00002004UL
#define CPU__nMEDAXI_DU1R_THRES2_Cfg     0x00000001UL
#define CPU__nMEDAXI_DU1R_QON_Cfg        0x00000001UL

#define CPU__nMEDAXI_DU1W_CONF_Cfg       0x00000003UL
#define CPU__nMEDAXI_DU1W_CTSET0_Cfg     0x00002063UL
#define CPU__nMEDAXI_DU1W_CTSET1_Cfg     0x00000000UL
#define CPU__nMEDAXI_DU1W_CTSET2_Cfg     0x00000000UL
#define CPU__nMEDAXI_DU1W_CTSET3_Cfg     0x00000000UL
#define CPU__nMEDAXI_DU1W_REQCTR_Cfg     0x00000001UL
#define CPU__nMEDAXI_DU1W_THRES0_Cfg     0x00000001UL
#define CPU__nMEDAXI_DU1W_THRES1_Cfg     0x00000001UL
#define CPU__nMEDAXI_DU1W_THRES2_Cfg     0x00000001UL
#define CPU__nMEDAXI_DU1W_QON_Cfg        0x00000001UL
/* ======== iVDP1c ======== */
#define CPU__nMEDAXI_VCP0CR_CONF_Cfg     0x00000001UL
#define CPU__nMEDAXI_VCP0CR_CTSET0_Cfg   0x00002073UL
#define CPU__nMEDAXI_VCP0CR_CTSET1_Cfg   0x00000000UL
#define CPU__nMEDAXI_VCP0CR_CTSET2_Cfg   0x00000000UL
#define CPU__nMEDAXI_VCP0CR_CTSET3_Cfg   0x00000000UL
#define CPU__nMEDAXI_VCP0CR_REQCTR_Cfg   0x00000020UL
#define CPU__nMEDAXI_VCP0CR_THRES0_Cfg   0x00002064UL
#define CPU__nMEDAXI_VCP0CR_THRES1_Cfg   0x00002004UL
#define CPU__nMEDAXI_VCP0CR_THRES2_Cfg   0x00000001UL
#define CPU__nMEDAXI_VCP0CR_QON_Cfg      0x00000001UL

#define CPU__nMEDAXI_VCP0CW_CONF_Cfg     0x00000001UL
#define CPU__nMEDAXI_VCP0CW_CTSET0_Cfg   0x00002073UL
#define CPU__nMEDAXI_VCP0CW_CTSET1_Cfg   0x00000000UL
#define CPU__nMEDAXI_VCP0CW_CTSET2_Cfg   0x00000000UL
#define CPU__nMEDAXI_VCP0CW_CTSET3_Cfg   0x00000000UL
#define CPU__nMEDAXI_VCP0CW_REQCTR_Cfg   0x00000020UL
#define CPU__nMEDAXI_VCP0CW_THRES0_Cfg   0x00000001UL
#define CPU__nMEDAXI_VCP0CW_THRES1_Cfg   0x00000001UL
#define CPU__nMEDAXI_VCP0CW_THRES2_Cfg   0x00000001UL
#define CPU__nMEDAXI_VCP0CW_QON_Cfg      0x00000001UL

#define CPU__nMEDAXI_VCP0VR_CONF_Cfg     0x00000001UL
#define CPU__nMEDAXI_VCP0VR_CTSET0_Cfg   0x00002073UL
#define CPU__nMEDAXI_VCP0VR_CTSET1_Cfg   0x00000000UL
#define CPU__nMEDAXI_VCP0VR_CTSET2_Cfg   0x00000000UL
#define CPU__nMEDAXI_VCP0VR_CTSET3_Cfg   0x00000000UL
#define CPU__nMEDAXI_VCP0VR_REQCTR_Cfg   0x00000020UL
#define CPU__nMEDAXI_VCP0VR_THRES0_Cfg   0x00002064UL
#define CPU__nMEDAXI_VCP0VR_THRES1_Cfg   0x00002004UL
#define CPU__nMEDAXI_VCP0VR_THRES2_Cfg   0x00000001UL
#define CPU__nMEDAXI_VCP0VR_QON_Cfg      0x00000001UL

#define CPU__nMEDAXI_VCP0VW_CONF_Cfg     0x00000001UL
#define CPU__nMEDAXI_VCP0VW_CTSET0_Cfg   0x00002073UL
#define CPU__nMEDAXI_VCP0VW_CTSET1_Cfg   0x00000000UL
#define CPU__nMEDAXI_VCP0VW_CTSET2_Cfg   0x00000000UL
#define CPU__nMEDAXI_VCP0VW_CTSET3_Cfg   0x00000000UL
#define CPU__nMEDAXI_VCP0VW_REQCTR_Cfg   0x00000020UL
#define CPU__nMEDAXI_VCP0VW_THRES0_Cfg   0x00000001UL
#define CPU__nMEDAXI_VCP0VW_THRES1_Cfg   0x00000001UL
#define CPU__nMEDAXI_VCP0VW_THRES2_Cfg   0x00000001UL
#define CPU__nMEDAXI_VCP0VW_QON_Cfg      0x00000001UL

#define CPU__nMEDAXI_VCP0R_CONF_Cfg      0x00000001UL
#define CPU__nMEDAXI_VCP0R_CTSET0_Cfg    0x00002073UL
#define CPU__nMEDAXI_VCP0R_CTSET1_Cfg    0x00000000UL
#define CPU__nMEDAXI_VCP0R_CTSET2_Cfg    0x00000000UL
#define CPU__nMEDAXI_VCP0R_CTSET3_Cfg    0x00000000UL
#define CPU__nMEDAXI_VCP0R_REQCTR_Cfg    0x00000020UL
#define CPU__nMEDAXI_VCP0R_THRES0_Cfg    0x00002064UL
#define CPU__nMEDAXI_VCP0R_THRES1_Cfg    0x00002004UL
#define CPU__nMEDAXI_VCP0R_THRES2_Cfg    0x00000001UL
#define CPU__nMEDAXI_VCP0R_QON_Cfg       0x00000001UL


/* Reset value of the interrupt controller registers */
#define CPU__nIntRegResetValue           0x00000000UL

/* Configuration for Distributor Control Register, enable the Grp0 and Grp1 */
#define CPU__nGIDC_CTLR_Cfg              0x00000003UL

/* Configuration for CPU Interface Control Register */
#define CPU__nGICC_CTLR_Cfg              0x0000016fUL

#define CPU__nGICD_ICACTIVER_Cfg         0xffffffffUL
#define CPU__nGICD_ICENABLER_Cfg         0xffff0000UL
#define CPU__nGICD_ISENABLER_Cfg         0x0000ffffUL

#endif __CPU_H