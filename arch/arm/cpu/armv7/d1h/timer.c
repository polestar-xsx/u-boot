#include <common.h>
#include <asm/io.h>
#include <asm/arch/base.h>
#include <asm/arch/timer.h>

int timer_init(void)
{
    /* Stop generic timer */
   ((volatile cntcr_regs *)(CNTCR_BASE))->cntcr_en = 0;

   /* Reset generic timer counter to 0 */
   ((volatile cntcr_regs *)(CNTCR_BASE))->cntcv = 0;

   /* Start generic timer */
   ((volatile cntcr_regs *)(CNTCR_BASE))->cntcr_en = 1;
   return 0;
}


void __udelay(unsigned long usec)
{
    u32 time_current, time_start;
    volatile cntcr_regs *ptimer_reg = (cntcr_regs *)(CNTCR_BASE);

    /* Read generic timer counter */
    time_start = (u32)(ptimer_reg->cntcv);

    /* Validate time delay value */
    if ((usec > 0UL) && (usec < TIMER_DELAY_MAX_US))
    {
        /* Maximum value without overflow is 132152839.84, which is approx. 132.15 seconds */
        usec = (usec * TIMER_INV_SCL_INT_MULT_FACTOR) + (usec / TIMER_INV_SCL_FRAC_DIV_FACTOR);

        do {
            /* Read generic timer counter */
            time_current = (u32)(ptimer_reg->cntcv);
        } while ((time_current - time_start) < usec);
    }
}

unsigned long get_timer(unsigned long base)
{
    u64 timer;
    timer = ((volatile cntcr_regs *)(CNTCR_BASE))->cntcv;
    timer = (timer * TIMER_SCL_NUMERATOR) / TIMER_SCL_DENOMINATOR;
    return (timer - base);
}