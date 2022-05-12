#include <common.h>
#include <asm/io.h>
#include <asm/arch/cpu.h>
#include <asm/arch/timer.h>

/*
* Description : Variables used to access the S3C Control registers.
*/
static u32 DBSC3_READ_QoS_ADDR[CPU__nDBSC3_DEVICE_MAX] = {
    CPU__nDBCS3_0_QOS_R0_BaseAddr,
    CPU__nDBCS3_0_QOS_R1_BaseAddr,
    CPU__nDBCS3_0_QOS_R2_BaseAddr,
    CPU__nDBCS3_0_QOS_R3_BaseAddr,
    CPU__nDBCS3_0_QOS_R4_BaseAddr,
    CPU__nDBCS3_0_QOS_R5_BaseAddr,
    CPU__nDBCS3_0_QOS_R6_BaseAddr,
    CPU__nDBCS3_0_QOS_R7_BaseAddr,
    CPU__nDBCS3_0_QOS_R8_BaseAddr,
    CPU__nDBCS3_0_QOS_R9_BaseAddr,
    CPU__nDBCS3_0_QOS_R10_BaseAddr,
    CPU__nDBCS3_0_QOS_R11_BaseAddr,
    CPU__nDBCS3_0_QOS_R12_BaseAddr,
    CPU__nDBCS3_0_QOS_R13_BaseAddr,
    CPU__nDBCS3_0_QOS_R14_BaseAddr,
    CPU__nDBCS3_0_QOS_R15_BaseAddr
};

static u32 DBSC3_WRITE_QoS_ADDR[CPU__nDBSC3_DEVICE_MAX] = {
    CPU__nDBCS3_0_QOS_W0_BaseAddr,
    CPU__nDBCS3_0_QOS_W1_BaseAddr,
    CPU__nDBCS3_0_QOS_W2_BaseAddr,
    CPU__nDBCS3_0_QOS_W3_BaseAddr,
    CPU__nDBCS3_0_QOS_W4_BaseAddr,
    CPU__nDBCS3_0_QOS_W5_BaseAddr,
    CPU__nDBCS3_0_QOS_W6_BaseAddr,
    CPU__nDBCS3_0_QOS_W7_BaseAddr,
    CPU__nDBCS3_0_QOS_W8_BaseAddr,
    CPU__nDBCS3_0_QOS_W9_BaseAddr,
    CPU__nDBCS3_0_QOS_W10_BaseAddr,
    CPU__nDBCS3_0_QOS_W11_BaseAddr,
    CPU__nDBCS3_0_QOS_W12_BaseAddr,
    CPU__nDBCS3_0_QOS_W13_BaseAddr,
    CPU__nDBCS3_0_QOS_W14_BaseAddr,
    CPU__nDBCS3_0_QOS_W15_BaseAddr
};

/* Cortex A7, SGX540 S3C Control Registers */
static const CPU__tstS3CTRL_Config CPU__stS3CTRLConfig = {
    CPU__nS3CRORR_Cfg,
    CPU__nS3CWORR_Cfg,
};
/* Cortex A7, SGX540 CCI0 QoS Control Registers */
static const CPU__tstS3C_QOS_Config CPU__stS3CCCI0QoSConfig = {
    CPU__nSC3_CCI0_QOS0_Cfg,
    CPU__nSC3_CCI0_QOS1_Cfg,
    CPU__nSC3_CCI0_QOS2_Cfg,
    CPU__nSC3_CCI0_QOS3_Cfg,
    CPU__nSC3_CCI0_QOS4_Cfg,
    CPU__nSC3_CCI0_QOS5_Cfg,
    CPU__nSC3_CCI0_QOS6_Cfg,
    CPU__nSC3_CCI0_QOS7_Cfg,
    CPU__nSC3_CCI0_QOS8_Cfg
};
/* D/AVE HD QoS CC1 Control Registers */
static const CPU__tstS3C_QOS_Config CPU__stS3CCCI1QoSConfig = {
    CPU__nSC3_CCI1_QOS0_Cfg,
    CPU__nSC3_CCI1_QOS1_Cfg,
    CPU__nSC3_CCI1_QOS2_Cfg,
    CPU__nSC3_CCI1_QOS3_Cfg,
    CPU__nSC3_CCI1_QOS4_Cfg,
    CPU__nSC3_CCI1_QOS5_Cfg,
    CPU__nSC3_CCI1_QOS6_Cfg,
    CPU__nSC3_CCI1_QOS7_Cfg,
    CPU__nSC3_CCI1_QOS8_Cfg
};
/* MEDIA AXI QoS Control Registers */
static const CPU__tstS3C_QOS_Config CPU__stS3CMXIQoSConfig = {
    CPU__nSC3_MXI_QOS0_Cfg,
    CPU__nSC3_MXI_QOS1_Cfg,
    CPU__nSC3_MXI_QOS2_Cfg,
    CPU__nSC3_MXI_QOS3_Cfg,
    CPU__nSC3_MXI_QOS4_Cfg,
    CPU__nSC3_MXI_QOS5_Cfg,
    CPU__nSC3_MXI_QOS6_Cfg,
    CPU__nSC3_MXI_QOS7_Cfg,
    CPU__nSC3_MXI_QOS8_Cfg
};
/* S3C SYS AXI QoS Control Registers */
static const CPU__tstS3C_QOS_Config CPU__stS3CAXIQoSConfig = {
    CPU__nSC3_AXI_QOS0_Cfg,
    CPU__nSC3_AXI_QOS1_Cfg,
    CPU__nSC3_AXI_QOS2_Cfg,
    CPU__nSC3_AXI_QOS3_Cfg,
    CPU__nSC3_AXI_QOS4_Cfg,
    CPU__nSC3_AXI_QOS5_Cfg,
    CPU__nSC3_AXI_QOS6_Cfg,
    CPU__nSC3_AXI_QOS7_Cfg,
    CPU__nSC3_AXI_QOS8_Cfg
};

static const CPU__tstCCI400_QoSCntrlConfig CPU__stCCI400QoSS1Config = {
    CPU__nCCI400_QoS_CTRL1_Cfg,
    CPU__nCCI400_QoS_MAXOT1_Cfg       
};

static const CPU__tstCCI400_QoSCntrlConfig CPU__stCCI400QoSS2Config = {
    CPU__nCCI400_QoS_CTRL2_Cfg,
    CPU__nCCI400_QoS_MAXOT2_Cfg    
};

static const CPU__tstCCI400_QoSCntrlConfig CPU__stCCI400QoSS3Config = {
    CPU__nCCI400_QoS_CTRL3_Cfg,
    CPU__nCCI400_QoS_MAXOT3_Cfg    
};

static const CPU__tstMXI_Config CPU__stMXIConfig = {
    CPU__nMXI_Tran_MXSAAR0_Cfg,
    CPU__nMXI_Tran_MXSAAR1_Cfg
};

static const CPU__tstMXI_CR_Config CPU__stMXI_CRConfig = {
    CPU__nMXI_Tran_MXRTCR_Cfg,
    CPU__nMXI_Tran_MXWTCR_Cfg
};

static const CPU__tstMXI_QOS_Config CPU__stMXI_QOSConfig = {
    CPU__nMXI_QoS_VSPDU0_Cfg,
    CPU__nMXI_QoS_VSPDU1_Cfg,
    CPU__nMXI_QoS_DU0_Cfg,
    CPU__nMXI_QoS_DU1_Cfg
};

static const CPU__tstMXIR_QOS_Config CPU__stMXIR_QOSConfig = {
    CPU__nMXIR_QoS_VIN_Cfg
};

/*  setting for Phase Lock Loop configuration, in case of IPL can't find a valid parameter set,
*  the following values will be used */
static const CPU__tstDBSC3_QOS_Config CPU__stDBSC3ReadQoSConfig = {
    CPU__nDBSC3_RDQoS_LGCNT_Cfg,
    CPU__nDBSC3_RDQoS_TMVAL0_Cfg,
    CPU__nDBSC3_RDQoS_TMVAL1_Cfg,
    CPU__nDBSC3_RDQoS_TMVAL2_Cfg,
    CPU__nDBSC3_RDQoS_TMVAL3_Cfg,
    CPU__nDBSC3_RDQoS_RQCTR_Cfg,
    CPU__nDBSC3_RDQoS_THRES0_Cfg,
    CPU__nDBSC3_RDQoS_THRES1_Cfg,
    CPU__nDBSC3_RDQoS_THRES2_Cfg,
    CPU__nDBSC3_RDQoS_THRES3_Cfg,
    CPU__nDBSC3_RDQoS_LGQON_Cfg
};

static const CPU__tstDBSC3_QOS_Config CPU__stDBSC3WriteQoSConfig = {
    CPU__nDBSC3_WRQoS_LGCNT_Cfg,
    CPU__nDBSC3_WRQoS_TMVAL0_Cfg,
    CPU__nDBSC3_WRQoS_TMVAL1_Cfg,
    CPU__nDBSC3_WRQoS_TMVAL2_Cfg,
    CPU__nDBSC3_WRQoS_TMVAL3_Cfg,
    CPU__nDBSC3_WRQoS_RQCTR_Cfg,
    CPU__nDBSC3_WRQoS_THRES0_Cfg,
    CPU__nDBSC3_WRQoS_THRES1_Cfg,
    CPU__nDBSC3_WRQoS_THRES2_Cfg,
    CPU__nDBSC3_WRQoS_THRES3_Cfg,
    CPU__nDBSC3_RDQoS_LGQON_Cfg
};

static const CPU__tstSYSAXI_QoSCntrlConfig CPU__stSYSAXI_QoSConfig = {
    CPU__nSYSAXI_S64_CONF_Cfg,
    CPU__nSYSAXI_S64_CTSET0_Cfg,
    CPU__nSYSAXI_S64_CTSET1_Cfg,
    CPU__nSYSAXI_S64_CTSET2_Cfg,
    CPU__nSYSAXI_S64_CTSET3_Cfg,
    CPU__nSYSAXI_S64_REQCTR_Cfg,
    CPU__nSYSAXI_S64_THRES0_Cfg,
    CPU__nSYSAXI_S64_THRES1_Cfg,
    CPU__nSYSAXI_S64_THRES2_Cfg,
    CPU__nSYSAXI_S64_QON_Cfg,
    CPU__nSYSAXI_AVB_CONF_Cfg,
    CPU__nSYSAXI_AVB_CTSET0_Cfg,
    CPU__nSYSAXI_AVB_CTSET1_Cfg,
    CPU__nSYSAXI_AVB_CTSET2_Cfg,
    CPU__nSYSAXI_AVB_CTSET3_Cfg,
    CPU__nSYSAXI_AVB_REQCTR_Cfg,
    CPU__nSYSAXI_AVB_THRES0_Cfg,
    CPU__nSYSAXI_AVB_THRES1_Cfg,
    CPU__nSYSAXI_AVB_THRES2_Cfg,
    CPU__nSYSAXI_AVB_QON_Cfg,
    CPU__nSYSAXI_IMUX0_CONF_Cfg,
    CPU__nSYSAXI_IMUX0_CTSET0_Cfg,
    CPU__nSYSAXI_IMUX0_CTSET1_Cfg,
    CPU__nSYSAXI_IMUX0_CTSET2_Cfg,
    CPU__nSYSAXI_IMUX0_CTSET3_Cfg,
    CPU__nSYSAXI_IMUX0_REQCTR_Cfg,
    CPU__nSYSAXI_IMUX0_THRES0_Cfg,
    CPU__nSYSAXI_IMUX0_THRES1_Cfg,
    CPU__nSYSAXI_IMUX0_THRES2_Cfg,
    CPU__nSYSAXI_IMUX0_QON_Cfg,
    CPU__nSYSAXI_IMUX1_CONF_Cfg,
    CPU__nSYSAXI_IMUX1_CTSET0_Cfg,
    CPU__nSYSAXI_IMUX1_CTSET1_Cfg,
    CPU__nSYSAXI_IMUX1_CTSET2_Cfg,
    CPU__nSYSAXI_IMUX1_CTSET3_Cfg,
    CPU__nSYSAXI_IMUX1_REQCTR_Cfg,
    CPU__nSYSAXI_IMUX1_THRES0_Cfg,
    CPU__nSYSAXI_IMUX1_THRES1_Cfg,
    CPU__nSYSAXI_IMUX1_THRES2_Cfg,
    CPU__nSYSAXI_IMUX1_QON_Cfg,
    CPU__nSYSAXI_IMUX2_CONF_Cfg,
    CPU__nSYSAXI_IMUX2_CTSET0_Cfg,
    CPU__nSYSAXI_IMUX2_CTSET1_Cfg,
    CPU__nSYSAXI_IMUX2_CTSET2_Cfg,
    CPU__nSYSAXI_IMUX2_CTSET3_Cfg,
    CPU__nSYSAXI_IMUX2_REQCTR_Cfg,
    CPU__nSYSAXI_IMUX2_THRES0_Cfg,
    CPU__nSYSAXI_IMUX2_THRES1_Cfg,
    CPU__nSYSAXI_IMUX2_THRES2_Cfg,
    CPU__nSYSAXI_IMUX2_QON_Cfg,
    CPU__nSYSAXI_MMUDS_CONF_Cfg,
    CPU__nSYSAXI_MMUDS_CTSET0_Cfg,
    CPU__nSYSAXI_MMUDS_CTSET1_Cfg,
    CPU__nSYSAXI_MMUDS_CTSET2_Cfg,
    CPU__nSYSAXI_MMUDS_CTSET3_Cfg,
    CPU__nSYSAXI_MMUDS_REQCTR_Cfg,
    CPU__nSYSAXI_MMUDS_THRES0_Cfg,
    CPU__nSYSAXI_MMUDS_THRES1_Cfg,
    CPU__nSYSAXI_MMUDS_THRES2_Cfg,
    CPU__nSYSAXI_MMUDS_QON_Cfg,
    CPU__nSYSAXI_MMUM_CONF_Cfg,
    CPU__nSYSAXI_MMUM_CTSET0_Cfg,
    CPU__nSYSAXI_MMUM_CTSET1_Cfg,
    CPU__nSYSAXI_MMUM_CTSET2_Cfg,
    CPU__nSYSAXI_MMUM_CTSET3_Cfg,
    CPU__nSYSAXI_MMUM_REQCTR_Cfg,
    CPU__nSYSAXI_MMUM_THRES0_Cfg,
    CPU__nSYSAXI_MMUM_THRES1_Cfg,
    CPU__nSYSAXI_MMUM_THRES2_Cfg,
    CPU__nSYSAXI_MMUM_QON_Cfg,
    CPU__nSYSAXI_MMUS0_CONF_Cfg,
    CPU__nSYSAXI_MMUS0_CTSET0_Cfg,
    CPU__nSYSAXI_MMUS0_CTSET1_Cfg,
    CPU__nSYSAXI_MMUS0_CTSET2_Cfg,
    CPU__nSYSAXI_MMUS0_CTSET3_Cfg,
    CPU__nSYSAXI_MMUS0_REQCTR_Cfg,
    CPU__nSYSAXI_MMUS0_THRES0_Cfg,
    CPU__nSYSAXI_MMUS0_THRES1_Cfg,
    CPU__nSYSAXI_MMUS0_THRES2_Cfg,
    CPU__nSYSAXI_MMUS0_QON_Cfg,
    CPU__nSYSAXI_MMUS1_CONF_Cfg,
    CPU__nSYSAXI_MMUS1_CTSET0_Cfg,
    CPU__nSYSAXI_MMUS1_CTSET1_Cfg,
    CPU__nSYSAXI_MMUS1_CTSET2_Cfg,
    CPU__nSYSAXI_MMUS1_CTSET3_Cfg,
    CPU__nSYSAXI_MMUS1_REQCTR_Cfg,
    CPU__nSYSAXI_MMUS1_THRES0_Cfg,
    CPU__nSYSAXI_MMUS1_THRES1_Cfg,
    CPU__nSYSAXI_MMUS1_THRES2_Cfg,
    CPU__nSYSAXI_MMUS1_QON_Cfg,
    CPU__nSYSAXI_SDS0_CONF_Cfg,
    CPU__nSYSAXI_SDS0_CTSET0_Cfg,
    CPU__nSYSAXI_SDS0_CTSET1_Cfg,
    CPU__nSYSAXI_SDS0_CTSET2_Cfg,
    CPU__nSYSAXI_SDS0_CTSET3_Cfg,
    CPU__nSYSAXI_SDS0_REQCTR_Cfg,
    CPU__nSYSAXI_SDS0_THRES0_Cfg,
    CPU__nSYSAXI_SDS0_THRES1_Cfg,
    CPU__nSYSAXI_SDS0_THRES2_Cfg,
    CPU__nSYSAXI_SDS0_QON_Cfg,
    CPU__nSYSAXI_SDS1_CONF_Cfg,
    CPU__nSYSAXI_SDS1_CTSET0_Cfg,
    CPU__nSYSAXI_SDS1_CTSET1_Cfg,
    CPU__nSYSAXI_SDS1_CTSET2_Cfg,
    CPU__nSYSAXI_SDS1_CTSET3_Cfg,
    CPU__nSYSAXI_SDS1_REQCTR_Cfg,
    CPU__nSYSAXI_SDS1_THRES0_Cfg,
    CPU__nSYSAXI_SDS1_THRES1_Cfg,
    CPU__nSYSAXI_SDS1_THRES2_Cfg,
    CPU__nSYSAXI_SDS1_QON_Cfg,
    CPU__nSYSAXI_USB20_CONF_Cfg,
    CPU__nSYSAXI_USB20_CTSET0_Cfg,
    CPU__nSYSAXI_USB20_CTSET1_Cfg,
    CPU__nSYSAXI_USB20_CTSET2_Cfg,
    CPU__nSYSAXI_USB20_CTSET3_Cfg,
    CPU__nSYSAXI_USB20_REQCTR_Cfg,
    CPU__nSYSAXI_USB20_THRES0_Cfg,
    CPU__nSYSAXI_USB20_THRES1_Cfg,
    CPU__nSYSAXI_USB20_THRES2_Cfg,
    CPU__nSYSAXI_USB20_QON_Cfg,
    CPU__nSYSAXI_MLB_CONF_Cfg,
    CPU__nSYSAXI_MLB_CTSET0_Cfg,
    CPU__nSYSAXI_MLB_CTSET1_Cfg,
    CPU__nSYSAXI_MLB_CTSET2_Cfg,
    CPU__nSYSAXI_MLB_CTSET3_Cfg,
    CPU__nSYSAXI_MLB_REQCTR_Cfg,
    CPU__nSYSAXI_MLB_THRES0_Cfg,
    CPU__nSYSAXI_MLB_THRES1_Cfg,
    CPU__nSYSAXI_MLB_THRES2_Cfg,
    CPU__nSYSAXI_MLB_QON_Cfg,
    CPU__nSYSAXI_AX2M_CONF_Cfg,
    CPU__nSYSAXI_AX2M_CTSET0_Cfg,
    CPU__nSYSAXI_AX2M_CTSET1_Cfg,
    CPU__nSYSAXI_AX2M_CTSET2_Cfg,
    CPU__nSYSAXI_AX2M_CTSET3_Cfg,
    CPU__nSYSAXI_AX2M_REQCTR_Cfg,
    CPU__nSYSAXI_AX2M_THRES0_Cfg,
    CPU__nSYSAXI_AX2M_THRES1_Cfg,
    CPU__nSYSAXI_AX2M_THRES2_Cfg,
    CPU__nSYSAXI_AX2M_QON_Cfg,
    CPU__nSYSAXI_CCI_CONF_Cfg,
    CPU__nSYSAXI_CCI_CTSET0_Cfg,
    CPU__nSYSAXI_CCI_CTSET1_Cfg,
    CPU__nSYSAXI_CCI_CTSET2_Cfg,
    CPU__nSYSAXI_CCI_CTSET3_Cfg,
    CPU__nSYSAXI_CCI_REQCTR_Cfg,
    CPU__nSYSAXI_CCI_THRES0_Cfg,
    CPU__nSYSAXI_CCI_THRES1_Cfg,
    CPU__nSYSAXI_CCI_THRES2_Cfg,
    CPU__nSYSAXI_CCI_QON_Cfg,
    CPU__nSYSAXI_CS_CONF_Cfg,
    CPU__nSYSAXI_CS_CTSET0_Cfg,
    CPU__nSYSAXI_CS_CTSET1_Cfg,
    CPU__nSYSAXI_CS_CTSET2_Cfg,
    CPU__nSYSAXI_CS_CTSET3_Cfg,
    CPU__nSYSAXI_CS_REQCTR_Cfg,
    CPU__nSYSAXI_CS_THRES0_Cfg,
    CPU__nSYSAXI_CS_THRES1_Cfg,
    CPU__nSYSAXI_CS_THRES2_Cfg,
    CPU__nSYSAXI_CS_QON_Cfg,
    CPU__nSYSAXI_DDM_CONF_Cfg,
    CPU__nSYSAXI_DDM_CTSET0_Cfg,
    CPU__nSYSAXI_DDM_CTSET1_Cfg,
    CPU__nSYSAXI_DDM_CTSET2_Cfg,
    CPU__nSYSAXI_DDM_CTSET3_Cfg,
    CPU__nSYSAXI_DDM_REQCTR_Cfg,
    CPU__nSYSAXI_DDM_THRES0_Cfg,
    CPU__nSYSAXI_DDM_THRES1_Cfg,
    CPU__nSYSAXI_DDM_THRES2_Cfg,
    CPU__nSYSAXI_DDM_QON_Cfg,
    CPU__nSYSAXI_NANDC_CONF_Cfg,
    CPU__nSYSAXI_NANDC_CTSET0_Cfg,
    CPU__nSYSAXI_NANDC_CTSET1_Cfg,
    CPU__nSYSAXI_NANDC_CTSET2_Cfg,
    CPU__nSYSAXI_NANDC_CTSET3_Cfg,
    CPU__nSYSAXI_NANDC_REQCTR_Cfg,
    CPU__nSYSAXI_NANDC_THRES0_Cfg,
    CPU__nSYSAXI_NANDC_THRES1_Cfg,
    CPU__nSYSAXI_NANDC_THRES2_Cfg,
    CPU__nSYSAXI_NANDC_QON_Cfg,
    CPU__nSYSAXI_DHDX_CONF_Cfg,
    CPU__nSYSAXI_DHDX_CTSET0_Cfg,
    CPU__nSYSAXI_DHDX_CTSET1_Cfg,
    CPU__nSYSAXI_DHDX_CTSET2_Cfg,
    CPU__nSYSAXI_DHDX_CTSET3_Cfg,
    CPU__nSYSAXI_DHDX_REQCTR_Cfg,
    CPU__nSYSAXI_DHDX_THRES0_Cfg,
    CPU__nSYSAXI_DHDX_THRES1_Cfg,
    CPU__nSYSAXI_DHDX_THRES2_Cfg,
    CPU__nSYSAXI_DHDX_QON_Cfg,
    CPU__nSYSAXI_SDM0_CONF_Cfg,
    CPU__nSYSAXI_SDM0_CTSET0_Cfg,
    CPU__nSYSAXI_SDM0_CTSET1_Cfg,
    CPU__nSYSAXI_SDM0_CTSET2_Cfg,
    CPU__nSYSAXI_SDM0_CTSET3_Cfg,
    CPU__nSYSAXI_SDM0_REQCTR_Cfg,
    CPU__nSYSAXI_SDM0_THRES0_Cfg,
    CPU__nSYSAXI_SDM0_THRES1_Cfg,
    CPU__nSYSAXI_SDM0_THRES2_Cfg,
    CPU__nSYSAXI_SDM0_QON_Cfg,
    CPU__nSYSAXI_SDM1_CONF_Cfg,
    CPU__nSYSAXI_SDM1_CTSET0_Cfg,
    CPU__nSYSAXI_SDM1_CTSET1_Cfg,
    CPU__nSYSAXI_SDM1_CTSET2_Cfg,
    CPU__nSYSAXI_SDM1_CTSET3_Cfg,
    CPU__nSYSAXI_SDM1_REQCTR_Cfg,
    CPU__nSYSAXI_SDM1_THRES0_Cfg,
    CPU__nSYSAXI_SDM1_THRES1_Cfg,
    CPU__nSYSAXI_SDM1_THRES2_Cfg,
    CPU__nSYSAXI_SDM1_QON_Cfg,
    CPU__nSYSAXI_TRKF_CONF_Cfg,
    CPU__nSYSAXI_TRKF_CTSET0_Cfg,
    CPU__nSYSAXI_TRKF_CTSET1_Cfg,
    CPU__nSYSAXI_TRKF_CTSET2_Cfg,
    CPU__nSYSAXI_TRKF_CTSET3_Cfg,
    CPU__nSYSAXI_TRKF_REQCTR_Cfg,
    CPU__nSYSAXI_TRKF_THRES0_Cfg,
    CPU__nSYSAXI_TRKF_THRES1_Cfg,
    CPU__nSYSAXI_TRKF_THRES2_Cfg,
    CPU__nSYSAXI_TRKF_QON_Cfg,
    CPU__nSYSAXI_UDM0_CONF_Cfg,
    CPU__nSYSAXI_UDM0_CTSET0_Cfg,
    CPU__nSYSAXI_UDM0_CTSET1_Cfg,
    CPU__nSYSAXI_UDM0_CTSET2_Cfg,
    CPU__nSYSAXI_UDM0_CTSET3_Cfg,
    CPU__nSYSAXI_UDM0_REQCTR_Cfg,
    CPU__nSYSAXI_UDM0_THRES0_Cfg,
    CPU__nSYSAXI_UDM0_THRES1_Cfg,
    CPU__nSYSAXI_UDM0_THRES2_Cfg,
    CPU__nSYSAXI_UDM0_QON_Cfg,
    CPU__nSYSAXI_UDM1_CONF_Cfg,
    CPU__nSYSAXI_UDM1_CTSET0_Cfg,
    CPU__nSYSAXI_UDM1_CTSET1_Cfg,
    CPU__nSYSAXI_UDM1_CTSET2_Cfg,
    CPU__nSYSAXI_UDM1_CTSET3_Cfg,
    CPU__nSYSAXI_UDM1_REQCTR_Cfg,
    CPU__nSYSAXI_UDM1_THRES0_Cfg,
    CPU__nSYSAXI_UDM1_THRES1_Cfg,
    CPU__nSYSAXI_UDM1_THRES2_Cfg,
    CPU__nSYSAXI_UDM1_QON_Cfg,
    CPU__nSYSAXI_S256SYX_CONF_Cfg,
    CPU__nSYSAXI_S256SYX_CTSET0_Cfg,
    CPU__nSYSAXI_S256SYX_CTSET1_Cfg,
    CPU__nSYSAXI_S256SYX_CTSET2_Cfg,
    CPU__nSYSAXI_S256SYX_CTSET3_Cfg,
    CPU__nSYSAXI_S256SYX_REQCTR_Cfg,
    CPU__nSYSAXI_S256SYX_THRES0_Cfg,
    CPU__nSYSAXI_S256SYX_THRES1_Cfg,
    CPU__nSYSAXI_S256SYX_THRES2_Cfg,
    CPU__nSYSAXI_S256SYX_QON_Cfg,
    CPU__nSYSAXI_S256MXI_CONF_Cfg,
    CPU__nSYSAXI_S256MXI_CTSET0_Cfg,
    CPU__nSYSAXI_S256MXI_CTSET1_Cfg,
    CPU__nSYSAXI_S256MXI_CTSET2_Cfg,
    CPU__nSYSAXI_S256MXI_CTSET3_Cfg,
    CPU__nSYSAXI_S256MXI_REQCTR_Cfg,
    CPU__nSYSAXI_S256MXI_THRES0_Cfg,
    CPU__nSYSAXI_S256MXI_THRES1_Cfg,
    CPU__nSYSAXI_S256MXI_THRES2_Cfg,
    CPU__nSYSAXI_S256MXI_QON_Cfg
};

static const CPU__tstCCIAXI_QoSCntrlConfig CPU__stCCIAXI_QoSConfig = {
    CPU__nCCIAXI_MMUS0_CONF_Cfg,
    CPU__nCCIAXI_MMUS0_CTSET0_Cfg,
    CPU__nCCIAXI_MMUS0_CTSET1_Cfg,
    CPU__nCCIAXI_MMUS0_CTSET2_Cfg,
    CPU__nCCIAXI_MMUS0_CTSET3_Cfg,
    CPU__nCCIAXI_MMUS0_REQCTR_Cfg,
    CPU__nCCIAXI_MMUS0_THRES0_Cfg,
    CPU__nCCIAXI_MMUS0_THRES1_Cfg,
    CPU__nCCIAXI_MMUS0_THRES2_Cfg,
    CPU__nCCIAXI_MMUS0_QON_Cfg,
    CPU__nCCIAXI_MMUS1_CONF_Cfg,
    CPU__nCCIAXI_MMUS1_CTSET0_Cfg,
    CPU__nCCIAXI_MMUS1_CTSET1_Cfg,
    CPU__nCCIAXI_MMUS1_CTSET2_Cfg,
    CPU__nCCIAXI_MMUS1_CTSET3_Cfg,
    CPU__nCCIAXI_MMUS1_REQCTR_Cfg,
    CPU__nCCIAXI_MMUS1_THRES0_Cfg,
    CPU__nCCIAXI_MMUS1_THRES1_Cfg,
    CPU__nCCIAXI_MMUS1_THRES2_Cfg,
    CPU__nCCIAXI_MMUS1_QON_Cfg,
    CPU__nCCIAXI_SYX2_CONF_Cfg,
    CPU__nCCIAXI_SYX2_CTSET0_Cfg,
    CPU__nCCIAXI_SYX2_CTSET1_Cfg,
    CPU__nCCIAXI_SYX2_CTSET2_Cfg,
    CPU__nCCIAXI_SYX2_CTSET3_Cfg,
    CPU__nCCIAXI_SYX2_REQCTR_Cfg,
    CPU__nCCIAXI_SYX2_THRES0_Cfg,
    CPU__nCCIAXI_SYX2_THRES1_Cfg,
    CPU__nCCIAXI_SYX2_THRES2_Cfg,
    CPU__nCCIAXI_SYX2_QON_Cfg,
    CPU__nCCIAXI_MMUDS_CONF_Cfg,
    CPU__nCCIAXI_MMUDS_CTSET0_Cfg,
    CPU__nCCIAXI_MMUDS_CTSET1_Cfg,
    CPU__nCCIAXI_MMUDS_CTSET2_Cfg,
    CPU__nCCIAXI_MMUDS_CTSET3_Cfg,
    CPU__nCCIAXI_MMUDS_REQCTR_Cfg,
    CPU__nCCIAXI_MMUDS_THRES0_Cfg,
    CPU__nCCIAXI_MMUDS_THRES1_Cfg,
    CPU__nCCIAXI_MMUDS_THRES2_Cfg,
    CPU__nCCIAXI_MMUDS_QON_Cfg,
    CPU__nCCIAXI_MMUM_CONF_Cfg,
    CPU__nCCIAXI_MMUM_CTSET0_Cfg,
    CPU__nCCIAXI_MMUM_CTSET1_Cfg,
    CPU__nCCIAXI_MMUM_CTSET2_Cfg,
    CPU__nCCIAXI_MMUM_CTSET3_Cfg,
    CPU__nCCIAXI_MMUM_REQCTR_Cfg,
    CPU__nCCIAXI_MMUM_THRES0_Cfg,
    CPU__nCCIAXI_MMUM_THRES1_Cfg,
    CPU__nCCIAXI_MMUM_THRES2_Cfg,
    CPU__nCCIAXI_MMUM_QON_Cfg,
    CPU__nCCIAXI_MXI_CONF_Cfg,
    CPU__nCCIAXI_MXI_CTSET0_Cfg,
    CPU__nCCIAXI_MXI_CTSET1_Cfg,
    CPU__nCCIAXI_MXI_CTSET2_Cfg,
    CPU__nCCIAXI_MXI_CTSET3_Cfg,
    CPU__nCCIAXI_MXI_REQCTR_Cfg,
    CPU__nCCIAXI_MXI_THRES0_Cfg,
    CPU__nCCIAXI_MXI_THRES1_Cfg,
    CPU__nCCIAXI_MXI_THRES2_Cfg,
    CPU__nCCIAXI_MXI_QON_Cfg
};


static const CPU__tstMEDAXI_QoSCntrlConfig CPU__stMediaAXI_QoSConfig = {
    CPU__nMEDAXI_MXR_CONF_Cfg,
    CPU__nMEDAXI_MXR_CTSET0_Cfg,
    CPU__nMEDAXI_MXR_CTSET1_Cfg,
    CPU__nMEDAXI_MXR_CTSET2_Cfg,
    CPU__nMEDAXI_MXR_CTSET3_Cfg,
    CPU__nMEDAXI_MXR_REQCTR_Cfg,
    CPU__nMEDAXI_MXR_THRES0_Cfg,
    CPU__nMEDAXI_MXR_THRES1_Cfg,
    CPU__nMEDAXI_MXR_THRES2_Cfg,
    CPU__nMEDAXI_MXR_QON_Cfg,
    CPU__nMEDAXI_MXW_CONF_Cfg,
    CPU__nMEDAXI_MXW_CTSET0_Cfg,
    CPU__nMEDAXI_MXW_CTSET1_Cfg,
    CPU__nMEDAXI_MXW_CTSET2_Cfg,
    CPU__nMEDAXI_MXW_CTSET3_Cfg,
    CPU__nMEDAXI_MXW_REQCTR_Cfg,
    CPU__nMEDAXI_MXW_THRES0_Cfg,
    CPU__nMEDAXI_MXW_THRES1_Cfg,
    CPU__nMEDAXI_MXW_THRES2_Cfg,
    CPU__nMEDAXI_MXW_QON_Cfg,
    CPU__nMEDAXI_VIN0W_CONF_Cfg,
    CPU__nMEDAXI_VIN0W_CTSET0_Cfg,
    CPU__nMEDAXI_VIN0W_CTSET1_Cfg,
    CPU__nMEDAXI_VIN0W_CTSET2_Cfg,
    CPU__nMEDAXI_VIN0W_CTSET3_Cfg,
    CPU__nMEDAXI_VIN0W_REQCTR_Cfg,
    CPU__nMEDAXI_VIN0W_THRES0_Cfg,
    CPU__nMEDAXI_VIN0W_THRES1_Cfg,
    CPU__nMEDAXI_VIN0W_THRES2_Cfg,
    CPU__nMEDAXI_VIN0W_QON_Cfg,
    CPU__nMEDAXI_VSPDU0CR_CONF_Cfg,
    CPU__nMEDAXI_VSPDU0CR_CTSET0_Cfg,
    CPU__nMEDAXI_VSPDU0CR_CTSET1_Cfg,
    CPU__nMEDAXI_VSPDU0CR_CTSET2_Cfg,
    CPU__nMEDAXI_VSPDU0CR_CTSET3_Cfg,
    CPU__nMEDAXI_VSPDU0CR_REQCTR_Cfg,
    CPU__nMEDAXI_VSPDU0CR_THRES0_Cfg,
    CPU__nMEDAXI_VSPDU0CR_THRES1_Cfg,
    CPU__nMEDAXI_VSPDU0CR_THRES2_Cfg,
    CPU__nMEDAXI_VSPDU0CR_QON_Cfg,
    CPU__nMEDAXI_VSPDU0CW_CONF_Cfg,
    CPU__nMEDAXI_VSPDU0CW_CTSET0_Cfg,
    CPU__nMEDAXI_VSPDU0CW_CTSET1_Cfg,
    CPU__nMEDAXI_VSPDU0CW_CTSET2_Cfg,
    CPU__nMEDAXI_VSPDU0CW_CTSET3_Cfg,
    CPU__nMEDAXI_VSPDU0CW_REQCTR_Cfg,
    CPU__nMEDAXI_VSPDU0CW_THRES0_Cfg,
    CPU__nMEDAXI_VSPDU0CW_THRES1_Cfg,
    CPU__nMEDAXI_VSPDU0CW_THRES2_Cfg,
    CPU__nMEDAXI_VSPDU0CW_QON_Cfg,
    CPU__nMEDAXI_VSPD0R_CONF_Cfg,
    CPU__nMEDAXI_VSPD0R_CTSET0_Cfg,
    CPU__nMEDAXI_VSPD0R_CTSET1_Cfg,
    CPU__nMEDAXI_VSPD0R_CTSET2_Cfg,
    CPU__nMEDAXI_VSPD0R_CTSET3_Cfg,
    CPU__nMEDAXI_VSPD0R_REQCTR_Cfg,
    CPU__nMEDAXI_VSPD0R_THRES0_Cfg,
    CPU__nMEDAXI_VSPD0R_THRES1_Cfg,
    CPU__nMEDAXI_VSPD0R_THRES2_Cfg,
    CPU__nMEDAXI_VSPD0R_QON_Cfg,
    CPU__nMEDAXI_VSPD0W_CONF_Cfg,
    CPU__nMEDAXI_VSPD0W_CTSET0_Cfg,
    CPU__nMEDAXI_VSPD0W_CTSET1_Cfg,
    CPU__nMEDAXI_VSPD0W_CTSET2_Cfg,
    CPU__nMEDAXI_VSPD0W_CTSET3_Cfg,
    CPU__nMEDAXI_VSPD0W_REQCTR_Cfg,
    CPU__nMEDAXI_VSPD0W_THRES0_Cfg,
    CPU__nMEDAXI_VSPD0W_THRES1_Cfg,
    CPU__nMEDAXI_VSPD0W_THRES2_Cfg,
    CPU__nMEDAXI_VSPD0W_QON_Cfg,
    CPU__nMEDAXI_VSPDU1CR_CONF_Cfg,
    CPU__nMEDAXI_VSPDU1CR_CTSET0_Cfg,
    CPU__nMEDAXI_VSPDU1CR_CTSET1_Cfg,
    CPU__nMEDAXI_VSPDU1CR_CTSET2_Cfg,
    CPU__nMEDAXI_VSPDU1CR_CTSET3_Cfg,
    CPU__nMEDAXI_VSPDU1CR_REQCTR_Cfg,
    CPU__nMEDAXI_VSPDU1CR_THRES0_Cfg,
    CPU__nMEDAXI_VSPDU1CR_THRES1_Cfg,
    CPU__nMEDAXI_VSPDU1CR_THRES2_Cfg,
    CPU__nMEDAXI_VSPDU1CR_QON_Cfg,
    CPU__nMEDAXI_VSPDU1CW_CONF_Cfg,
    CPU__nMEDAXI_VSPDU1CW_CTSET0_Cfg,
    CPU__nMEDAXI_VSPDU1CW_CTSET1_Cfg,
    CPU__nMEDAXI_VSPDU1CW_CTSET2_Cfg,
    CPU__nMEDAXI_VSPDU1CW_CTSET3_Cfg,
    CPU__nMEDAXI_VSPDU1CW_REQCTR_Cfg,
    CPU__nMEDAXI_VSPDU1CW_THRES0_Cfg,
    CPU__nMEDAXI_VSPDU1CW_THRES1_Cfg,
    CPU__nMEDAXI_VSPDU1CW_THRES2_Cfg,
    CPU__nMEDAXI_VSPDU1CW_QON_Cfg,
    CPU__nMEDAXI_VSPD1R_CONF_Cfg,
    CPU__nMEDAXI_VSPD1R_CTSET0_Cfg,
    CPU__nMEDAXI_VSPD1R_CTSET1_Cfg,
    CPU__nMEDAXI_VSPD1R_CTSET2_Cfg,
    CPU__nMEDAXI_VSPD1R_CTSET3_Cfg,
    CPU__nMEDAXI_VSPD1R_REQCTR_Cfg,
    CPU__nMEDAXI_VSPD1R_THRES0_Cfg,
    CPU__nMEDAXI_VSPD1R_THRES1_Cfg,
    CPU__nMEDAXI_VSPD1R_THRES2_Cfg,
    CPU__nMEDAXI_VSPD1R_QON_Cfg,
    CPU__nMEDAXI_VSPD1W_CONF_Cfg,
    CPU__nMEDAXI_VSPD1W_CTSET0_Cfg,
    CPU__nMEDAXI_VSPD1W_CTSET1_Cfg,
    CPU__nMEDAXI_VSPD1W_CTSET2_Cfg,
    CPU__nMEDAXI_VSPD1W_CTSET3_Cfg,
    CPU__nMEDAXI_VSPD1W_REQCTR_Cfg,
    CPU__nMEDAXI_VSPD1W_THRES0_Cfg,
    CPU__nMEDAXI_VSPD1W_THRES1_Cfg,
    CPU__nMEDAXI_VSPD1W_THRES2_Cfg,
    CPU__nMEDAXI_VSPD1W_QON_Cfg,
    CPU__nMEDAXI_DU0R_CONF_Cfg,
    CPU__nMEDAXI_DU0R_CTSET0_Cfg,
    CPU__nMEDAXI_DU0R_CTSET1_Cfg,
    CPU__nMEDAXI_DU0R_CTSET2_Cfg,
    CPU__nMEDAXI_DU0R_CTSET3_Cfg,
    CPU__nMEDAXI_DU0R_REQCTR_Cfg,
    CPU__nMEDAXI_DU0R_THRES0_Cfg,
    CPU__nMEDAXI_DU0R_THRES1_Cfg,
    CPU__nMEDAXI_DU0R_THRES2_Cfg,
    CPU__nMEDAXI_DU0R_QON_Cfg,
    CPU__nMEDAXI_DU0W_CONF_Cfg,
    CPU__nMEDAXI_DU0W_CTSET0_Cfg,
    CPU__nMEDAXI_DU0W_CTSET1_Cfg,
    CPU__nMEDAXI_DU0W_CTSET2_Cfg,
    CPU__nMEDAXI_DU0W_CTSET3_Cfg,
    CPU__nMEDAXI_DU0W_REQCTR_Cfg,
    CPU__nMEDAXI_DU0W_THRES0_Cfg,
    CPU__nMEDAXI_DU0W_THRES1_Cfg,
    CPU__nMEDAXI_DU0W_THRES2_Cfg,
    CPU__nMEDAXI_DU0W_QON_Cfg,
    CPU__nMEDAXI_DU1R_CONF_Cfg,
    CPU__nMEDAXI_DU1R_CTSET0_Cfg,
    CPU__nMEDAXI_DU1R_CTSET1_Cfg,
    CPU__nMEDAXI_DU1R_CTSET2_Cfg,
    CPU__nMEDAXI_DU1R_CTSET3_Cfg,
    CPU__nMEDAXI_DU1R_REQCTR_Cfg,
    CPU__nMEDAXI_DU1R_THRES0_Cfg,
    CPU__nMEDAXI_DU1R_THRES1_Cfg,
    CPU__nMEDAXI_DU1R_THRES2_Cfg,
    CPU__nMEDAXI_DU1R_QON_Cfg,
    CPU__nMEDAXI_DU1W_CONF_Cfg,
    CPU__nMEDAXI_DU1W_CTSET0_Cfg,
    CPU__nMEDAXI_DU1W_CTSET1_Cfg,
    CPU__nMEDAXI_DU1W_CTSET2_Cfg,
    CPU__nMEDAXI_DU1W_CTSET3_Cfg,
    CPU__nMEDAXI_DU1W_REQCTR_Cfg,
    CPU__nMEDAXI_DU1W_THRES0_Cfg,
    CPU__nMEDAXI_DU1W_THRES1_Cfg,
    CPU__nMEDAXI_DU1W_THRES2_Cfg,
    CPU__nMEDAXI_DU1W_QON_Cfg,
    CPU__nMEDAXI_VCP0CR_CONF_Cfg,
    CPU__nMEDAXI_VCP0CR_CTSET0_Cfg,
    CPU__nMEDAXI_VCP0CR_CTSET1_Cfg,
    CPU__nMEDAXI_VCP0CR_CTSET2_Cfg,
    CPU__nMEDAXI_VCP0CR_CTSET3_Cfg,
    CPU__nMEDAXI_VCP0CR_REQCTR_Cfg,
    CPU__nMEDAXI_VCP0CR_THRES0_Cfg,
    CPU__nMEDAXI_VCP0CR_THRES1_Cfg,
    CPU__nMEDAXI_VCP0CR_THRES2_Cfg,
    CPU__nMEDAXI_VCP0CR_QON_Cfg,
    CPU__nMEDAXI_VCP0CW_CONF_Cfg,
    CPU__nMEDAXI_VCP0CW_CTSET0_Cfg,
    CPU__nMEDAXI_VCP0CW_CTSET1_Cfg,
    CPU__nMEDAXI_VCP0CW_CTSET2_Cfg,
    CPU__nMEDAXI_VCP0CW_CTSET3_Cfg,
    CPU__nMEDAXI_VCP0CW_REQCTR_Cfg,
    CPU__nMEDAXI_VCP0CW_THRES0_Cfg,
    CPU__nMEDAXI_VCP0CW_THRES1_Cfg,
    CPU__nMEDAXI_VCP0CW_THRES2_Cfg,
    CPU__nMEDAXI_VCP0CW_QON_Cfg,
    CPU__nMEDAXI_VCP0VR_CONF_Cfg,
    CPU__nMEDAXI_VCP0VR_CTSET0_Cfg,
    CPU__nMEDAXI_VCP0VR_CTSET1_Cfg,
    CPU__nMEDAXI_VCP0VR_CTSET2_Cfg,
    CPU__nMEDAXI_VCP0VR_CTSET3_Cfg,
    CPU__nMEDAXI_VCP0VR_REQCTR_Cfg,
    CPU__nMEDAXI_VCP0VR_THRES0_Cfg,
    CPU__nMEDAXI_VCP0VR_THRES1_Cfg,
    CPU__nMEDAXI_VCP0VR_THRES2_Cfg,
    CPU__nMEDAXI_VCP0VR_QON_Cfg,
    CPU__nMEDAXI_VCP0VW_CONF_Cfg,
    CPU__nMEDAXI_VCP0VW_CTSET0_Cfg,
    CPU__nMEDAXI_VCP0VW_CTSET1_Cfg,
    CPU__nMEDAXI_VCP0VW_CTSET2_Cfg,
    CPU__nMEDAXI_VCP0VW_CTSET3_Cfg,
    CPU__nMEDAXI_VCP0VW_REQCTR_Cfg,
    CPU__nMEDAXI_VCP0VW_THRES0_Cfg,
    CPU__nMEDAXI_VCP0VW_THRES1_Cfg,
    CPU__nMEDAXI_VCP0VW_THRES2_Cfg,
    CPU__nMEDAXI_VCP0VW_QON_Cfg,
    CPU__nMEDAXI_VCP0R_CONF_Cfg,
    CPU__nMEDAXI_VCP0R_CTSET0_Cfg,
    CPU__nMEDAXI_VCP0R_CTSET1_Cfg,
    CPU__nMEDAXI_VCP0R_CTSET2_Cfg,
    CPU__nMEDAXI_VCP0R_CTSET3_Cfg,
    CPU__nMEDAXI_VCP0R_REQCTR_Cfg,
    CPU__nMEDAXI_VCP0R_THRES0_Cfg,
    CPU__nMEDAXI_VCP0R_THRES1_Cfg,
    CPU__nMEDAXI_VCP0R_THRES2_Cfg,
    CPU__nMEDAXI_VCP0R_QON_Cfg
};

/* Poll the specified 32-bit register until the value matches the mask and value specified or timeout occurred */
static bool cpu_wait_reg(volatile u32 *pu32Register, u32 u32Mask, u32 u32Value)
{
    u32 u32ReadValue;
    unsigned long ultimestart;
    bool boMatch = false, boTimeout = false;

    /* Make sure the mask is not zero and the expected value does not fall outside the mask */
    if ((u32Mask != 0UL) && ((u32Value & (~u32Mask)) == 0UL))
    {
        ultimestart = get_timer(0);
        /* Poll register until match or timeout */
        do
        {
            /* Read and compare the register with mask and expected value */
            u32ReadValue = *pu32Register;
            if ((u32ReadValue & u32Mask) == u32Value)
            {
                boMatch = true;
            }

            if (get_timer(ultimestart) >= (u32)CPU__nVERIFICATION_TIMEOUT)
            {
                boTimeout = true;
            }
        } while ((false == boMatch) && (false == boTimeout));
    }

    return (bool)((true == boMatch) && (false == boTimeout));
}

/* Reset the CA7BAR2 register to the initial value and set it to invalid */
static bool cpu_reset_ca7bar2(void)
{
    bool boReturn = false;
    volatile u32 *pu32CA7BAR2 = (volatile u32 *)(CPU__nCA7BAR2_Reg);

    /* Restore the register */
    *pu32CA7BAR2 = CPU__nCA7BAR2_INITIALVALUE;

    /* Verify write value */
    if (false != cpu_wait_reg(pu32CA7BAR2, UINT32_MAX, CPU__nCA7BAR2_INITIALVALUE))
    {
        boReturn = true;
    }

    return boReturn;
}

/* Reset the CA7BAR register to the initial value and set it to valid */
static bool cpu_reset_ca7bar(void)
{
    u32 u32Value;
    bool boReturn = false;
    volatile u32 *pu32CA7BAR = (volatile u32 *)(CPU__nCA7BAR_Reg);

    /* Restore the register without BAREN bit */
    u32Value = (CPU__nCA7BAR_INITIALVALUE & (~CPU__nCA7BAR_BAREN_Msk));
    *pu32CA7BAR = u32Value;
    /* Set BAREN bit (must be done last) */
    u32Value |= CPU__nCA7BAR_BAREN_Msk;
    *pu32CA7BAR = u32Value;

    /* Verify write value */
    if (false != cpu_wait_reg(pu32CA7BAR, UINT32_MAX, u32Value))
    {
        /* Switch to CA7BAR */
        if (false != cpu_reset_ca7bar2())
        {
            boReturn = true;
        }
    }

    return boReturn;
}

/* S3C Control QoS Registers */
void cpu_set_s3ctrl(void)
{
    /* S3C -QoS */
    *CPU__ptstS3CTRL_reg = CPU__stS3CTRLConfig;
    /* Cortex A7, SGX540 CCI0 QoS Control Registers */
    *CPU__ptstS3C_QOS_CCI0 = CPU__stS3CCCI0QoSConfig;
    /* D/AVE HD QoS CC1 Control Registers */
    *CPU__ptstS3C_QOS_CCI1 = CPU__stS3CCCI1QoSConfig;
    /* MEDIA AXI QoS Control Registers */
    *CPU__ptstS3C_QOS_MXI = CPU__stS3CMXIQoSConfig;
    /* S3C SYS AXI QoS Control Registers */
    *CPU__ptstS3C_QOS_AXI = CPU__stS3CAXIQoSConfig;
}

/*  CCI-400 Control QoS Registers */
void cpu_set_cci400(void)
{
    *CPU__ptstC400_S1QOS_reg = CPU__stCCI400QoSS1Config;
    *CPU__ptstC400_S2QOS_reg = CPU__stCCI400QoSS2Config;
    *CPU__ptstC400_S3QOS_reg = CPU__stCCI400QoSS3Config;
}

/*  MXI Bus Control QoS Registers */
void cpu_set_mxi(void)
{
/* Transaction Control (MXI) */
    *CPU__ptstMXI_CR_reg = CPU__stMXI_CRConfig;
    *CPU__ptstMXI_reg = CPU__stMXIConfig;
    /* QoS Control (MXI) */
    *CPU__ptstMXI_QOS_reg = CPU__stMXI_QOSConfig;
    /* QoS Control (MXIR) */
    *CPU__ptstMXIR_QOS_reg = CPU__stMXIR_QOSConfig;
}
/*  SYS AXI Bus Control QoS Registers */
void cpu_set_sys_axi(void)
{
    u32 u32Count;
    const CPU__tunSYSAXI_QoSCntrlConfig *CPU__punSYSAXI_QoS_Config;

    const u32 u32SYS_AXI_BaseAddr[26] =
    {   /* order must match with the QoSConfig structure */
        CPU__nSYS_AXI_SYX64TO128_BaseAddr,
        CPU__nSYS_AXI_AVB_BaseAddr,
        CPU__nSYS_AXI_IMUX0_BaseAddr,
        CPU__nSYS_AXI_IMUX1_BaseAddr,
        CPU__nSYS_AXI_IMUX2_BaseAddr,
        CPU__nSYS_AXI_MMUDS_BaseAddr,
        CPU__nSYS_AXI_MMUM_BaseAddr,
        CPU__nSYS_AXI_MMUS0_BaseAddr,
        CPU__nSYS_AXI_MMUS1_BaseAddr,
        CPU__nSYS_AXI_SDS0_BaseAddr,
        CPU__nSYS_AXI_SDS1_BaseAddr,
        CPU__nSYS_AXI_USB20_BaseAddr,
        CPU__nSYS_AXI_MLB_BaseAddr,
        CPU__nSYS_AXI_AX2M_BaseAddr,
        CPU__nSYS_AXI_CCI_BaseAddr,
        CPU__nSYS_AXI_CS_BaseAddr,
        CPU__nSYS_AXI_DDM_BaseAddr,
        CPU__nSYS_AXI_NANDC_BaseAddr,
        CPU__nSYS_AXI_DHDX_BaseAddr,
        CPU__nSYS_AXI_SDM0_BaseAddr,
        CPU__nSYS_AXI_SDM1_BaseAddr,
        CPU__nSYS_AXI_TRKF_BaseAddr,
        CPU__nSYS_AXI_UDM0_BaseAddr,
        CPU__nSYS_AXI_UDM1_BaseAddr,
        CPU__nSYS_AXI256_SYX_BaseAddr,
        CPU__nSYS_AXI256_MXI_BaseAddr
    };


    CPU__punSYSAXI_QoS_Config = (const CPU__tunSYSAXI_QoSCntrlConfig *)(&CPU__stSYSAXI_QoSConfig);


    for (u32Count = 0; u32Count < 26; u32Count++)
    {
        *(volatile CPU__tstAXI_Config *)(u32SYS_AXI_BaseAddr[u32Count]) = CPU__punSYSAXI_QoS_Config->arrayView[u32Count];
    }
}

/*  CCI AXI Bus ControlQoS Registers */
void cpu_set_cci_axi(void)
{
    u32 u32Count;
    const CPU__tunCCIAXI_QoSCntrlConfig *CPU__punCCIAXI_QoS_Config;

    const u32 u32CCI_AXI_BaseAddr[6] =
    {   /* order must match with the QoSConfig structure */
        CPU__nCCI_AXI_MMUS0_BaseAddr,
        CPU__nCCI_AXI_MMUS1_BaseAddr,
        CPU__nCCI_AXI_SYX2_BaseAddr,
        CPU__nCCI_AXI_MMUDS_BaseAddr,
        CPU__nCCI_AXI_MMUM_BaseAddr,
        CPU__nCCI_AXI_MXI_BaseAddr
    };

    
    CPU__punCCIAXI_QoS_Config = (const CPU__tunCCIAXI_QoSCntrlConfig *)(&CPU__stCCIAXI_QoSConfig);
    

    for (u32Count = 0; u32Count < 6; u32Count++)
    {
        *(volatile CPU__tstAXI_Config *)(u32CCI_AXI_BaseAddr[u32Count]) = CPU__punCCIAXI_QoS_Config->arrayView[u32Count];
    }
}

/*  MEDIA AXI Bus ControlQoS Registers */
void cpu_set_media_axi(void)
{
    u32 u32Count;
    const CPU__tunMEDAXI_QoSCntrlConfig *CPU__punMEDAXI_QoS_Config;

    const u32 u32MEDIA_AXI_BaseAddr[20] =
    {   /* order must match with the QoSConfig structure */
        CPU__nMEDIA_AXI_MXR_BaseAddr,
        CPU__nMEDIA_AXI_MXW_BaseAddr,
        CPU__nMEDIA_AXI_VIN0W_BaseAddr,
        CPU__nMEDIA_AXI_VSPDU0CR_BaseAddr,
        CPU__nMEDIA_AXI_VSPDU0CW_BaseAddr,
        CPU__nMEDIA_AXI_VSPD0R_BaseAddr,
        CPU__nMEDIA_AXI_VSPD0W_BaseAddr,
        CPU__nMEDIA_AXI_VSPDU1CR_BaseAddr,
        CPU__nMEDIA_AXI_VSPDU1CW_BaseAddr,
        CPU__nMEDIA_AXI_VSPD1R_BaseAddr,
        CPU__nMEDIA_AXI_VSPD1W_BaseAddr,
        CPU__nMEDIA_AXI_DU0R_BaseAddr,
        CPU__nMEDIA_AXI_DU0W_BaseAddr,
        CPU__nMEDIA_AXI_DU1R_BaseAddr,
        CPU__nMEDIA_AXI_DU1W_BaseAddr,
        CPU__nMEDIA_AXI_VCP0CR_BaseAddr,
        CPU__nMEDIA_AXI_VCP0CW_BaseAddr,
        CPU__nMEDIA_AXI_VCP0VR_BaseAddr,
        CPU__nMEDIA_AXI_VCP0VW_BaseAddr,
        CPU__nMEDIA_AXI_VPC0R_BaseAddr
    };

    
    CPU__punMEDAXI_QoS_Config = (const CPU__tunMEDAXI_QoSCntrlConfig *)(&CPU__stMediaAXI_QoSConfig);
    

    for (u32Count = 0; u32Count < 20; u32Count++)
    {
        *(volatile CPU__tstAXI_Config *)(u32MEDIA_AXI_BaseAddr[u32Count]) = CPU__punMEDAXI_QoS_Config->arrayView[u32Count];
    }
}

void cpu_set_qosparams(void)
{
    /* set DBSC adjustment Register     
    */
    *((volatile u32 *)CPU__nDBSC3_0_DBADJ2_Addr) = CPU__nDBSC3_0_DBADJ2_Cfg;

    /* S3C Control QoS Registers */
    cpu_set_s3ctrl();

    /*  CCI-400 Control QoS Registers */
    cpu_set_cci400();

    /*  MXI Bus Control QoS Registers */
    cpu_set_mxi();

    /*  SYS AXI Bus Control QoS Registers */
    cpu_set_sys_axi();

    /*  CCI AXI Bus ControlQoS Registers */
    cpu_set_cci_axi();

    /*  MEDIA AXI Bus ControlQoS Registers */
    cpu_set_media_axi();

}

/**********************************************************************************
* Description  : This function initializes the QoS for DBSC3
* Parameters   : CPU_tstConfig *pvParamsAddr
* Return Value : none
***********************************************************************************/
void cpu_qos_dbsc3init(void)
{
    volatile CPU__tstDBSC3_QOS_Config * xQOS_DBSC3_0;
    u32 u32Index;    

    /* DBSC -QoS */
    for (u32Index = 0; u32Index < CPU__nDBSC3_DEVICE_MAX; u32Index++)
    {
        xQOS_DBSC3_0 = (volatile CPU__tstDBSC3_QOS_Config *)DBSC3_READ_QoS_ADDR[u32Index];
        /* DBSC0 - Read */
        *xQOS_DBSC3_0 = CPU__stDBSC3ReadQoSConfig;
    }

    for (u32Index = 0; u32Index < CPU__nDBSC3_DEVICE_MAX; u32Index++)
    {
        xQOS_DBSC3_0 = (volatile CPU__tstDBSC3_QOS_Config *)DBSC3_WRITE_QoS_ADDR[u32Index];
        /* DBSC0 - Write */
        *xQOS_DBSC3_0 = CPU__stDBSC3WriteQoSConfig;
    }
}

void reset_cpu(void)
{
    u32 u32RegValue;
    u32RegValue = *((volatile u32 *)Reset__nECMIRCFG0_Addr);   /* ECMIRCFG0, ECM reset configuration register 0 */
    u32RegValue |= Reset__nECMWatchdogError_Msk;   /* Set the bit correspond to Watchdog overflow error interrupt */
    *((volatile u32 *)Reset__nECMPCMD1_Addr) = Reset__nECMProtectionCommand;   /* ECMPCMD1, ECM protection command register 1 */
    *((volatile u32 *)Reset__nECMIRCFG0_Addr) = u32RegValue;
    *((volatile u32 *)Reset__nECMIRCFG0_Addr) = ~(u32RegValue);
    *((volatile u32 *)Reset__nECMIRCFG0_Addr) = u32RegValue;

    /* RESET */
    *((volatile u32 *)Reset__nECMRSTCR_Addr) = Reset__nECMResetRequest;

    /* Set WDOG timer value */
    *((volatile u32 *)Reset__nRWTCNT) = (Reset__nRWTCNT_INIT | Reset__nRWTCNT_PATTERN);

    /* Enable WDOG */
    *((volatile u32 *)Reset__nRWTCSRA) = (Reset__nRWTCSRA_TME_Enable | Reset__nRWTCSR_PATTERN);
    while(1);
}

#if defined(CONFIG_DISPLAY_CPUINFO)
int print_cpuinfo(void)
{
    printf("CPU: Renesas Electronics D1H soc\n");
    return 0;
}
#endif

void cpu_init(void)
{

    /* Set the Cortex-A7 Boot Address Registers to initial value */
    cpu_reset_ca7bar();
}