#ifndef __DRIVERS_D1H_UART_H
#define __DRIVERS_D1H_UART_H

#define UART_GAP32(start,finish)    u32 u32__##start##_##finish[((finish)-(start))/4]
#define UART_GAP16(start,finish)    u16 u16__##start##_##finish[((finish)-(start))/2]
#define UART_GAP8(start,finish)     u8  u8__##start##_##finish[((finish)-(start))]

/*
 * Information about serial port
 *
 * @base:	Register base address
 * @clk:	Input clock rate, used for calculating the baud rate divisor
 * @clk_mode:	Clock mode, set internal (INT) or external (EXT)
 * @type:	Type of SCIF
 */
struct d1h_serial_plat {
	u32 addr_base;
};



/**
 * Baudrate 
 * Use this baudrate definition for configuration of the transmission
 * parameters of a channel.
 */
enum UART_enBaudrate
{

   UART_nBaud1200   = 1200,
   UART_nBaud2400   = 2400,
   UART_nBaud4800   = 4800,
   UART_nBaud9600   = 9600,
   UART_nBaud10400  = 10400,
   UART_nBaud19200  = 19200,
   UART_nBaud38400  = 38400,
   UART_nBaud57600  = 57600,
   UART_nBaud115200 = 115200,
   UART_nDummyBaud = 0 /* don't use this baudrate! */
};
typedef enum UART_enBaudrate UART_tenBaudrate;


/** UART parity types */
enum UART_enParity
{
   UART_nParityEven = 0,
   UART_nParityOdd,
   UART_nParityNone
};
typedef enum UART_enParity UART_tenParity;


/** UART character data length definitions */
enum UART_enCharLength
{
   UART_nCharLength8Bits = 0,
   UART_nCharLength7Bits
};
typedef enum UART_enCharLength UART_tenCharLength;


/** UART number of stop bits */
enum UART_enStopBits
{
   UART_nOneStopBit = 0,
   UART_nTwoStopBits
};
typedef enum UART_enStopBits UART_tenStopBits;


/**
 * UART Channel States
 * For every configured channel, a channel state variable is provided.
 */
enum UART_enState
{
   /** UART is deinitialized */
   UART_nOff = 0,
   /** UART is initialized; communication is still not activated. */
   UART_nInitialized,
   /** UART channel is opened by an application; communication can take place. */
   UART_nOpened,
   /** UART channel is opened and Tx data is transferred. */
   UART_nBusy
};
typedef enum UART_enState UART_tenState;

/* HL3D SCIF */
/* Select the clock source for the on-chip baud rate generator 
 * Values: 0x0 -> PØ
 *         0x1 -> PØ/4
 *         0x2 -> PØ/16
 *         0x3 -> PØ/64
 */
#define UART__SCSMR_CKS_cfg     0x0

/* Selects the baud rate generator clock source for the external clock
 * Values: 0: External clock (SCIF_CLK),
 *         1: Internal clock (S#)
*/
#define UART__CKS_XIN_cfg       0x1

/* This bit switches the output between the frequency divided clock (SC_CLK) and external clock (SCK).
 * Values: 0: SC_CLK (selectable between SCIF_CLK and S#) 
 *         1: SCK
*/
#define UART__CKS_CKS_cfg       0x0

/* Configuration of UART receiver error mask  */
#define UART_nRxErrorMask1          ((u16) 0x009CU)
#define UART_nRxErrorMask2          ((u16) 0x0005U)
/* Configuration of default value set for UART registers.*/
#define UART__nDefaultValue         (0x0U)   
/* Initial value of Bit Rate Register*/
#define UART__nDefaultBitRate       (0xFF)
/*UART macro that is used for enabling UART function/feature */
#define UART__nOn                    1       
/*UART macro that is used for disabling UART function/feature */
#define UART__nOff                   0      

/*FIFO Data Count Register (SCFDR), 0x10 indicates that SCFTDR is full of transmit data*/
#define UART__nFifoFull              0x10

/* UART FIFO (TX & RX) reset mask */
#define UART__nFifoReset_Msk         ((u16) 0x0006U)

#define UART__nOneSecond             (1000000UL)


/* Base address of GPIO registers */
#define D1H_GPIO_BASE_ADDR			    (0xE6050000UL)
/* Base address of Port Function Controller registers */
#define UART__nPFC_BaseAddr          (0xE6060000UL)

/* The masks for D1H Peripheral Function Select Registers */
#define UART__nIPSR_SCIF0_FUNC3_Msk  (0xC1FFFFFFUL)
#define UART__nIPSR_SCIF0_FUNC4_Msk  (0xFFFFE73FUL)
#define UART__nIPSR_SCIF0_FUNC2_Msk  (0xFFFFC0FFUL)
#define UART__nIPSR_SCIF0_FUNC1_Msk  (0xFFFC3FFFUL)

#define UART__nIPSR_SCIF1_FUNC3_Msk  (0xFFF03FFFUL)
#define UART__nIPSR_SCIF1_FUNC2_Msk  (0xFF83FFFFUL)
#define UART__nIPSR_SCIF1_FUNC1_Msk  (0xF03FFFFFUL)

#define UART__nIPSR_SCIF2_FUNC2_Msk  (0xFF03FFFFUL)
#define UART__nIPSR_SCIF2_FUNC3_Msk  (0xFFFFFF0FUL)
#define UART__nIPSR_SCIF2_FUNC1_Msk  (0xFFFF81FFUL)

#define UART__nIPSR_SCIF3_FUNC3_Msk  (0xFFFFC0FFUL)
#define UART__nIPSR_SCIF3_FUNC2_Msk  (0xFFFFFFC0UL)
#define UART__nIPSR_SCIF3_FUNC1_Msk  (0xFFFFFE07UL)

/*RTRG[1:0] - Specify the number of receive data bytes that makes the RDF
(receive data full) flag to be set in SCFSR (Asynchronous Mode)*/
#define UART__nRTRG_1_BYTES           0x0
#define UART__nRTRG_4_BYTES           0x1
#define UART__nRTRG_8_BYTES           0x2
#define UART__nRTRG_14_BYTES          0x3

/*TTRG[1:0] - Specify the number of remaining transmit data bytes that makes the
* transmit FIFO data register empty (TDFE) flag to be set in SCFSR.*/
#define UART__nTTRG_8_BYTES           0x0
#define UART__nTTRG_4_BYTES           0x1
#define UART__nTTRG_2_BYTES           0x2
#define UART__nTTRG_0_BYTES           0x3

/* Structure of UART SCSMR register */
typedef union
   {
      u16 u16word;
      struct
      {
         u16 bi16CKS        :  2;  // Clock Select, 00: P#, 01: P#/4, 10: P#/16, 11: P#/64
         u16 bi16Reserved0  :  1;  // Reserved
         u16 bi16STOP       :  1;  // Stop bit length, 0: one stop bit, 1: two stop bits
         u16 bi16OE         :  1;  // Parity Mode, 0: Even, 1: Odd
         u16 bi16PE         :  1;  // Parity Enable
         u16 bi16CHR        :  1;  // Character Length, 0: 8 bits, 1: 7 bits
         u16 bi16CA         :  1;  // Communication Mode, 0: Asynchronous mode, 1: Synchronous mode
         u16 bi16Reserved1  :  8;  // Reserved
      }bits;
   }UART__tunSCSMR;

/* Structure of UART SCSCR register */
typedef union
   {
      u16 u16word;
      struct
      {
         u16 bi16CKE        :  2;  // Clock Enable, 0: Disable, 1: Enable
         u16 bi16TOIE       :  1;  // Timeout Interrupt Enable
         u16 bi16REIE       :  1;  // Receive Error Interrupt Enable
         u16 bi16RE         :  1;  // Receive Enable
         u16 bi16TE         :  1;  // Transmit Enable
         u16 bi16RIE        :  1;  // Receive Interrupt Enable
         u16 bi16TIE        :  1;  // Transmit Interrupt Enable
         u16 bi16Reserved0  :  3;  // Reserved
         u16 bi16TEIE       :  1;  // Transmit End Interrupt Enable
         u16 bi16Reserved1  :  4;  // Reserved
      }bits;
   }UART__tunSCSCR;


/* Structure of UART SCFSR register */
typedef union
   {
      u16 u16word;
      struct
      {
         u16 bi16DR         :  1;  // Receive Data Ready
         u16 bi16RDF        :  1;  // Receive FIFO Data Full
         u16 bi16PER        :  1;  // Parity Error (read only)
         u16 bi16FER        :  1;  // Framing Error (read only)
         u16 bi16BRK        :  1;  // Break Detect
         u16 bi16TDFE       :  1;  // Transmit FIFO Data Empty
         u16 bi16TEND       :  1;  // Transmission ended
         u16 bi16ER         :  1;  // Receive Error
         u16 bi16FERC       :  4;  // Framing Error Count (read only)
         u16 bi16PERC       :  4;  // Parity Error Count (read only)
      }bits;
   }UART__tunSCFSR;


/* Structure of UART SCFCR register */
typedef union
   {
      u16 u16word;
      struct
      {
         u16 bi16Reserved0  :  1;  // Reserved
         u16 bi16RFRST      :  1;  // Receive FIFO Data Register Reset, 0: Disable the reset, 1: Enable the reset
         u16 bi16TFRST      :  1;  // Transmit FIFO Data Register Reset, 0: Disable the reset, 1: Enable the reset
         u16 bi16Reserved1  :  1;  // Reserved
         u16 bi16TTRG       :  2;  // Specify the number of remaining transmit data bytes that makes the transmit FIFO data register empty (TDFE) flag to be set in SCFSR.
                                      // 00: 8, 01: 4, 10: 2, 11: 0
         u16 bi16RTRG       :  2;  // These bits specify the number of receive data bytes that makes the RDF (receive data full) flag to be set in SCFSR.
                                      // Asynchronous Mode - 00: 1, 01: 4, 10: 8, 11: 14
                                      // Synchronous  Mode - 00: 1, 01: 2, 10: 8, 11: 14
         u16 bi16Reserved2  :  8;  // Reserved
      }bits;
   }UART__tunSCFCR;


/* Structure of UART SCFDR register */
typedef union
   {
      u16 u16word;
      struct
      {
         u16 bi16R          :  5;  // Number of receive data stored in SCFRDR in bytes (read only)
         u16 bi16Reserved0  :  3;  // Reserved
         u16 bi16T          :  5;  // Number of data bytes untransmitted (read only)
         u16 bi16Reserved1  :  3;  // Reserved
      }bits;
   }UART__tunSCFDR;


/* Structure of UART SCSPTR register */
typedef union
   {
      u16 u16word;
      struct
      {
         u16 bi16SPB2DT     :  1;  // Serial Port Break Data
         u16 bi16SPB2IO     :  1;  // Serial Port Break Input/Output
         u16 bi16SCKDT      :  1;  // Serial Port Clock Pin Data
         u16 bi16SCKIO      :  1;  // Serial Port Clock Pin Input/Output
         u16 bi16Reserved0  :  12; // Reserved
      }bits;
   }UART__tunSCSPTR;


/* Structure of UART SCLSR register */
typedef union
   {
      u16 u16word;
      struct
      {
         u16 bi16ORER       :  1;  // Overrun Error
         u16 bi16Reserved0  :  1;  // Reserved
         u16 bi16TO         :  1;  // Timeout
         u16 bi16Reserved1  :  13; // Reserved
      }bits;
   }UART__tunSCLSR;


/* Structure of UART CKS register
 * This register switches the output between the frequency divided clock and specifies a source clock for
 * the external baud rate */
typedef union
   {
      u16 u16word;
      struct
      {
         u16 bi16Reserved0  :  14; // Reserved
         u16 bi16XIN        :  1;  // Selects the baud rate generator clock source for the external clock, 0: External clock (SCIF_CLK), 1: Internal clock (S#)
         u16 bi16CKS        :  1;  // 0: SC_CLK (selectable between SCIF_CLK and S#) , 1: SCK
      }bits;
   }UART__tunCKS;


/* Structure of PFC Register */
typedef struct {
    u32	u32Pmmr;                         // 0x00
    u32  u32Gpsr[7];                      // 0x04 - 0x1F
    u32  u32Ipsr[9];                      // 0x20 - 0x43
    UART_GAP32(0x0044, 0x0090);                   // 0x44 - 0x89
    u32	u32ModSel;                       // 0x90
    u32	u32ModSel2;                      // 0x94
} UART__tstPfcReg;


/* Structure of Module select registers in Pin Function Controller */
typedef union
{
   u32 u32word;
   struct{
      u32  biSelIrqc8             :  2;
      u32  biSelIrqc9             :  2;
      u32  biSelScif0             :  2;
      u32  biSelScif2             :  2;
      u32  biSelMsiof1            :  1;
      u32  biSelMsiof3            :  1;
      u32  biSelMsiof5            :  1;
      u32  biSelVi1               :  1;
      u32  biSelHscif1            :  1;
      u32  biSelHscif0            :  1;
      u32  biSelCan0              :  1;
      u32  biSelCan1              :  1;
      u32  biSelIrqc2             :  2;
      u32  biSelIrqc3             :  2;
      u32  biSelNand              :  1;
      u32  biSelMsiof2            :  1;
      u32  biSelScif1             :  2;
      u32  biSelMsiof0            :  1;
      u32  biSelAvb               :  1;
      u32  biSelTmu1              :  1;
      u32  biSelTmu2              :  2;
      u32  biSelTmu3              :  1;
      u32  biSelScifclk           :  1;
      u32  biSelCan2              :  1;
   }u32ModSel_view;
   struct{
      u32  biDummy                :  10;
      u32  biSel_vi1cke           :  1;
      u32  biSel_avbavtp          :  1;
      u32  biSel_scif0s           :  1;
      u32  biSel_scif3r           :  2;
      u32  biSel_scif3s           :  2;
      u32  biSel_ecm              :  1;
      u32  biSel_i2c0             :  2;
      u32  biSel_i2c1             :  2;
      u32  biSel_irqc1            :  2;
      u32  biSel_irqc4            :  2;
      u32  biSel_irqc5            :  2;
      u32  biSel_irqc6            :  2;
      u32  biSel_irqc7            :  2;
   }u32ModSel2_view;
}UART__tunPfcReg;


/* Structure of UART registers of each channel */
typedef struct {
    UART__tunSCSMR scsmr;     // 0x00 - Serial mode register
    UART_GAP16(0x02,0x04);
    u8          scbrr;     // 0x04 - Bit rate register
    UART_GAP8 (0x05,0x08);
    UART__tunSCSCR scscr;     // 0x08 - Serial control register
    UART_GAP16(0x0A,0x0C);
    u8          scftdr;    // 0x0C - Transmit FIFO data register
    UART_GAP8 (0x0D,0x10);
    UART__tunSCFSR scfsr;     // 0x10 - Serial status register
    UART_GAP16(0x12,0x14);
    u8          scfrdr;    // 0x14 - Receive FIFO data register
    UART_GAP8 (0x15,0x18);
    UART__tunSCFCR scfcr;     // 0x18 - FIFO control register
    UART_GAP16(0x1A,0x1C);
    UART__tunSCFDR scfdr;     // 0x1C - FIFO data count register
    UART_GAP16(0x1E,0x20);
    UART__tunSCSPTR scsptr;    // 0x20 - Serial port register
    UART_GAP16(0x22,0x24);
    UART__tunSCLSR sclsr;     // 0x24 - Line status register
    UART_GAP16(0x26,0x30);
    u16         dl;        // 0x30 - Frequency division register
    UART_GAP16(0x32,0x34);
    UART__tunCKS    cks;       // 0x34 - Clock Select register
} UART__tstCommonReg;

#endif