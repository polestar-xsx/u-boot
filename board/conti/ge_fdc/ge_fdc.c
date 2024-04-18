#include <common.h>
#include <asm/io.h>
#include <asm/arch/base.h>
#include <asm/global_data.h>

DECLARE_GLOBAL_DATA_PTR;

void s_init(void)
{
	writel(0xA5A5A500, RWTCSRA);
}

int dram_init(void)
{
	gd->ram_size = 0x40000000;
	return 0;
}

int board_init(void)
{
	/* adress of boot parameters */
	gd->bd->bi_boot_params = CONFIG_SYS_SDRAM_BASE + 0x100;

	return 0;
}
