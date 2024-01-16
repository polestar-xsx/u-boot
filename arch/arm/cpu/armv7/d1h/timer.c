#include <common.h>
#include <asm/io.h>
#include <asm/arch/base.h>
#include <asm/arch/timer.h>

#define GAP32(start,finish)          u32 u32__##start##_##finish[(((finish)-(start))/4)]

/* Structure of registers in GPIO Blocks */
typedef struct
{
    u32 u32IoIntSel;       /* 0x00, General IO/interrupt switching register */
    u32 u32InOutSel;       /* 0x04, General input/output switching register */
    u32 u32Outdt;          /* 0x08, General output register */
    u32 u32InDt;           /* 0x0C, General input register */
    u32 u32IntDt;          /* 0x10, Interrupt display register */
    u32 u32IntClr;         /* 0x14, Interrupt clear register */
    u32 u32IntMsk;         /* 0x18, Interrupt mask register */
    u32 u32MskClr;         /* 0x1C, Interrupt mask clear register */
    u32 u32PosNeg;         /* 0x20, Positive/negative logic select register */
    u32 u32EdgLevel;       /* 0x24, Edge/level select register */
    u32 u32FilOnOff;       /* 0x28, Chattering prevention on/off register */
    GAP32(0x002C, 0x0038);
    u32 u32IntMsks;        /* 0x38, Interrupt sub mask register */
    u32 u32MskClrs;        /* 0x3C, Interrupt sub mask clear register */
    u32 u32OutDtSel;       /* 0x40, Output data select register */
    u32 u32OutDth;         /* 0x44, Output data high register */
    u32 u32OutDtl;         /* 0x48, Output data low register */
    u32 u32BothEdge;       /* 0x4C, One edge/both edge select register */
} tstGpioReg, *tpstGpioReg;

void time_init(void)
{
    /* Stop generic timer */
   ((volatile cntcr_regs *)(CNTCR_BASE))->cntcr_en = 0;

   /* Reset generic timer counter to 0 */
   ((volatile cntcr_regs *)(CNTCR_BASE))->cntcv = 0;

   /* Start generic timer */
   ((volatile cntcr_regs *)(CNTCR_BASE))->cntcr_en = 1;
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

void timer_settstpin(u8 group,u8 gpio, u8 level)
{
    volatile tpstGpioReg pstGpioReg;
    pstGpioReg = (tpstGpioReg)(0xE6050000UL + ((group) * 0x1000UL));
    pstGpioReg->u32PosNeg   &= ~(1 << gpio);     /* Positive logic */
    pstGpioReg->u32IoIntSel &= ~(1 << gpio);     /* General input/output mode */
    pstGpioReg->u32InOutSel |= (1 << gpio);      /* General output mode */
    if(!level)
    {
        pstGpioReg->u32OutDtSel &= ~(1 << gpio);      /* Use Output DT H/L registers */
    }
    else
    {
        pstGpioReg->u32OutDtSel |= (1 << gpio);      /* Use Output DT H/L registers */
    }
}
