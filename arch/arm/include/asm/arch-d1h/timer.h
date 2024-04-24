#ifndef __ASM_ARCH_D1H_TIMER_H
#define __ASM_ARCH_D1H_TIMER_H

#include <asm/types.h>

void time_init(void);

void __udelay(unsigned long usec);

unsigned long get_timer(unsigned long base);

/**
* Description: Maximum value without overflow is 132152839.84, which is approx.
*              132.15 seconds. This is calucalted by having maximum value of 32-bit
*              (i.e. 0xFFFFFFFF) divided by TIMER_INV_SCL_FACTOR (i.e. 32.5).
*/
#define TIMER_DELAY_MAX_US     (132150000UL)

/**
  * Description: Ratio for the raw generic timer value in order to convert the
  *              raw value into microsecond(us). Generic timer is based on
  *              clock frequency of 260MHz/8 (= 32.5MHz).
  *              The denominator is chosen to be a value of the power of 2 to
  *              improve the division speed because it will use bit shifting.
  *              Then the numerator is chosen to be a value which will result
  *              in division of 32.5. In this case the actual value is
  *              32.49999997, which is close enough to 32.5.
  */
#define TIMER_SCL_NUMERATOR       (132152ULL)//(132152840ULL) us
#define TIMER_SCL_DENOMINATOR     (1ULL << 32)

/**
 * Description: Inverse scaling factor of the raw generic timer value in order to
 *              convert microsecond(us) to raw generic timer value.
 *              The integer and fractional parts are both a value of the power of
 *              2 which makes the calculation efficient as bit shifting can be used.
 */
#define TIMER_INV_SCL_FACTOR           (32.5)
#define TIMER_INV_SCL_INT_MULT_FACTOR    (32UL)  /* Multiplcation factor for integer part, i.e. (N * 32) or (N << 5) */
#define TIMER_INV_SCL_FRAC_DIV_FACTOR    (2UL)   /* Division factor for fractional part, i.e. (N / 2) or (N >> 2) */
/**
* Description: Generic timer counter module and status registers
*/
typedef struct{
    u32 cntcr_en : 1;
    u32 cntcr_hdbg : 1;
    u32 cntcr_reserved : 30;
    u32 cntsr;            /* Counter status register */
    u64 cntcv;            /* Counter count value register */
}cntcr_regs;


#endif

