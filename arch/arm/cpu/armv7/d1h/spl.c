#include <common.h>
#include <asm/io.h>
#include <asm/arch/base.h>
#include <asm/arch/timer.h>
#include <asm/arch/sfma.h>
#include <asm/arch/sdram.h>
#include <asm/arch/cpu.h>
#include <asm/arch/clock.h>

void board_init_f(ulong dummy)
{
    time_init();
    cpu_init();
    clock_init();
    sdram_init();
}
