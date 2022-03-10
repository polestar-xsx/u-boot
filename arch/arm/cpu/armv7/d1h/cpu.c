#include <common.h>
#include <asm/io.h>
#include <asm/arch/cpu.h>
#include <asm/arch/timer.h>

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

void cpu_init(void)
{

    /* Set the Cortex-A7 Boot Address Registers to initial value */
    cpu_reset_ca7bar();
}