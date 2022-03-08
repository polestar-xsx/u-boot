#include <common.h>
#include <asm/io.h>
#include <asm/arch/cpu.h>

/* Poll the specified 32-bit register until the value matches the mask and value specified or timeout occurred */
static bool CPU__boWaitForRegister32bit(volatile u32 *pu32Register, u32 u32Mask, u32 u32Value)
{
    u32 u32ReadValue;
    u32 u32WaitCnt;
    bool boMatch = false, boTimeout = false;

    /* Make sure the mask is not zero and the expected value does not fall outside the mask */
    if ((u32Mask != 0UL) && ((u32Value & (~u32Mask)) == 0UL))
    {

        /* Poll register until match or timeout */
        do
        {
            /* Read and compare the register with mask and expected value */
            u32ReadValue = *pu32Register;
            if ((u32ReadValue & u32Mask) == u32Value)
            {
                boMatch = true;
            }
            
            if (u32WaitCnt >= (u32)CPU__nVerificationTimeoutCnt)
            {
                boTimeout = true;
            }
            u32WaitCnt++;
        } while ((false == boMatch) && (false == boTimeout));
    }

    return (bool)((true == boMatch) && (false == boTimeout));
}

/* Reset the CA7BAR2 register to the initial value and set it to invalid */
static bool CPU__boResetCA7BAR2(void)
{
    bool boReturn = false;
    volatile u32 *pu32CA7BAR2 = (volatile u32 *)(CPU__nCA7BAR2_Reg);

    /* Restore the register */
    *pu32CA7BAR2 = CPU__nCA7BAR2_INITIALVALUE;

    /* Verify write value */
    if (false != CPU__boWaitForRegister32bit(pu32CA7BAR2, UINT32_MAX, CPU__nCA7BAR2_INITIALVALUE))
    {
        boReturn = true;
    }

    return boReturn;
}

/* Reset the CA7BAR register to the initial value and set it to valid */
static bool CPU__boResetCA7BAR(void)
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
    if (false != CPU__boWaitForRegister32bit(pu32CA7BAR, UINT32_MAX, u32Value))
    {
        /* Switch to CA7BAR */
        if (false != CPU__boResetCA7BAR2())
        {
            boReturn = true;
        }
    }

    return boReturn;
}

void CPU_vInit(void)
{

    /* Set the Cortex-A7 Boot Address Registers to initial value */
    CPU__boResetCA7BAR();
}