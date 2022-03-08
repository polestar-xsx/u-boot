#include <common.h>
#include <asm/io.h>
#include "cpu.h"

/* Poll the specified 32-bit register until the value matches the mask and value specified or timeout occurred */
static bool CPU__boWaitForRegister32bit(volatile u32 *pu32Register, u32 u32Mask, u32 u32Value)
{
    u32 u32ReadValue;
    u32 u32TimeStart, u32TimeCurrent;
    bool boMatch = False, boTimeout = False;

    /* Make sure the mask is not zero and the expected value does not fall outside the mask */
    if ((u32Mask != 0UL) && ((u32Value & (~u32Mask)) == 0UL))
    {
        u32TimeStart = SYN__u32GetTimeUs();

        /* Poll register until match or timeout */
        do
        {
            /* Read and compare the register with mask and expected value */
            u32ReadValue = *pu32Register;
            if ((u32ReadValue & u32Mask) == u32Value)
            {
                boMatch = True;
            }
            /* Get the current time and compare the time difference (unsigned) with timeout value */
            u32TimeCurrent = SYN__u32GetTimeUs();
            if ((u32)(u32TimeCurrent - u32TimeStart) >= (u32)CPU__nVerificationTimeoutUs)
            {
                boTimeout = True;
            }
        } while ((False == boMatch) && (False == boTimeout));
    }

    return (bool)((True == boMatch) && (False == boTimeout));
}

/***************************************************************************
* Interface Description: Initialisation of Interrupt Controller
*
* Description          : To initialise the generic interrupt controller,
*                        enable the Distributor and CPU interfaces
*
* Return Value         : N/A
*
* Author               : Vishnu Patekar
*
****************************************************************************/
void CPU_vIntControllerInit(void)
{

    /*
    * Deal with the banked PPI and SGI interrupts - disable all
    * PPI interrupts, ensure all SGI interrupts are enabled.
    * Make sure everything is deactivated.
    */

    u32 u32Addr = CPU__nGICD_BaseAddr + GICD__nICACTIVER;
    writel(CPU__nGICD_ICACTIVER_Cfg, u32Addr);

    u32Addr = CPU__nGICD_BaseAddr + GICD__nICENABLER;
    writel(CPU__nGICD_ICENABLER_Cfg, u32Addr);

    u32Addr = CPU__nGICD_BaseAddr + GICD__nISENABLER;
    writel(CPU__nGICD_ISENABLER_Cfg, u32Addr);

    /* Higher interrupt priority corresponds to a lower value of the Priority field. */
    writel((u32)(31UL << 3), (CPU__nGICC_BaseAddr + GICC__nPMR));

    /* The highest priority pending interrupt forwarded from the Distributor
    to the CPU interface is signaled to the connected processor                             */
    writel(CPU__nGICC_CTLR_Cfg, (CPU__nGICC_BaseAddr + GICC__nCTRL));

    /* Enables the forwarding of pending interrupts from the Distributor to the CPU interfaces. */
    writel(CPU__nGIDC_CTLR_Cfg, (CPU__nGICD_BaseAddr + GICD__nCTRL));
}

/* Reset the CA7BAR2 register to the initial value and set it to invalid */
static bool CPU__boResetCA7BAR2(void)
{
    bool boReturn = False;
    volatile u32 *pu32CA7BAR2 = (volatile u32 *)(CPU__nCA7BAR2_Reg);

    /* Restore the register */
    *pu32CA7BAR2 = CPU__nCA7BAR2_INITIALVALUE;

    /* Verify write value */
    if (False != CPU__boWaitForRegister32bit(pu32CA7BAR2, UINT32_MAX, CPU__nCA7BAR2_INITIALVALUE))
    {
        boReturn = True;
    }

    return boReturn;
}

/* Reset the CA7BAR register to the initial value and set it to valid */
static bool CPU__boResetCA7BAR(void)
{
    u32 u32Value;
    bool boReturn = False;
    volatile u32 *pu32CA7BAR = (volatile u32 *)(CPU__nCA7BAR_Reg);

    /* Restore the register without BAREN bit */
    u32Value = (CPU__nCA7BAR_INITIALVALUE & (~CPU__nCA7BAR_BAREN_Msk));
    *pu32CA7BAR = u32Value;
    /* Set BAREN bit (must be done last) */
    u32Value |= CPU__nCA7BAR_BAREN_Msk;
    *pu32CA7BAR = u32Value;

    /* Verify write value */
    if (False != CPU__boWaitForRegister32bit(pu32CA7BAR, UINT32_MAX, u32Value))
    {
        /* Switch to CA7BAR */
        if (False != CPU__boResetCA7BAR2())
        {
            boReturn = True;
        }
    }

    return boReturn;
}

void CPU_vInit(void)
{
    /* Initialize QoS for S3CTRL */
#if (CPU_nboIRQS_ENABLED == Yes)
    CPU_vIntControllerInit();
    CPU_vEnableInt();
#endif
    /* Set the Cortex-A7 Boot Address Registers to initial value */
    CPU__boResetCA7BAR();
}