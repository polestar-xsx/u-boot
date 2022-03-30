#include <common.h>
#include <asm/io.h>
#include <asm/arch/base.h>

void s_init(void)
{
	writel(0xA5A5A500, RWTCSRA);
}