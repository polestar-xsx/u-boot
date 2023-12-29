#include <common.h>
#include <spl.h>
#include <asm/io.h>
#include <asm/arch/base.h>
#include <asm/arch/timer.h>
#include <asm/arch/sfma.h>
#include <asm/arch/sdram.h>
#include <asm/arch/cpu.h>
#include <asm/arch/clock.h>

void board_init_f(ulong dummy)
{
    if (CONFIG_IS_ENABLED(OF_CONTROL)) {
		int ret;

		ret = spl_early_init();
		if (ret) {
			debug("spl_early_init() failed: %d\n", ret);
			hang();
		}
	}
    time_init();
    cpu_init();
    clock_init();
    sdram_init();
#if defined(CONFIG_SPL_SERIAL_SUPPORT)
	/* init console */
	/*Hardware serial init code*/
    
	preloader_console_init();
#endif
}

u32 spl_boot_device(void)
{
	return BOOT_DEVICE_NOR;
}