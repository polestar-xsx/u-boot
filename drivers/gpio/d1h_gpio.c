// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2024 Xu Songxue <xusongxue88@163.com>
 */

#include <common.h>
#include <clk.h>
#include <dm.h>
#include <malloc.h>
#include <asm/global_data.h>
#include <dm/device_compat.h>
#include <dm/pinctrl.h>
#include <errno.h>
#include <asm/gpio.h>
#include <asm/io.h>
#include <linux/bitops.h>
#include "../pinctrl/renesas/sh_pfc.h"

#define GPIO_IOINTSEL	0x00	/* General IO/Interrupt Switching Register */
#define GPIO_INOUTSEL	0x04	/* General Input/Output Switching Register */
#define GPIO_OUTDT	0x08	/* General Output Register */
#define GPIO_INDT	0x0c	/* General Input Register */
#define GPIO_INTDT	0x10	/* Interrupt Display Register */
#define GPIO_INTCLR	0x14	/* Interrupt Clear Register */
#define GPIO_INTMSK	0x18	/* Interrupt Mask Register */
#define GPIO_MSKCLR	0x1c	/* Interrupt Mask Clear Register */
#define GPIO_POSNEG	0x20	/* Positive/Negative Logic Select Register */
#define GPIO_EDGLEVEL	0x24	/* Edge/level Select Register */
#define GPIO_FILONOFF	0x28	/* Chattering Prevention On/Off Register */
#define GPIO_BOTHEDGE	0x4c	/* One Edge/Both Edge Select Register */

#define RCAR_MAX_GPIO_PER_BANK		32

DECLARE_GLOBAL_DATA_PTR;

struct d1h_gpio_priv {
	void __iomem		*regs;
	int			pfc_offset;
};

static int d1h_gpio_get_value(struct udevice *dev, unsigned offset)
{
	struct d1h_gpio_priv *priv = dev_get_priv(dev);
	const u32 bit = BIT(offset);

	/*
	 * Testing on r8a7790 shows that INDT does not show correct pin state
	 * when configured as output, so use OUTDT in case of output pins.
	 */
	if (readl(priv->regs + GPIO_INOUTSEL) & bit)
		return !!(readl(priv->regs + GPIO_OUTDT) & bit);
	else
		return !!(readl(priv->regs + GPIO_INDT) & bit);
}

static int d1h_gpio_set_value(struct udevice *dev, unsigned offset,
			       int value)
{
	struct d1h_gpio_priv *priv = dev_get_priv(dev);

	if (value)
		setbits_le32(priv->regs + GPIO_OUTDT, BIT(offset));
	else
		clrbits_le32(priv->regs + GPIO_OUTDT, BIT(offset));

	return 0;
}

static void d1h_gpio_set_direction(void __iomem *regs, unsigned offset,
				    bool output)
{
	/*
	 * follow steps in the GPIO documentation for
	 * "Setting General Output Mode" and
	 * "Setting General Input Mode"
	 */

	/* Configure postive logic in POSNEG */
	clrbits_le32(regs + GPIO_POSNEG, BIT(offset));

	/* Select "General Input/Output Mode" in IOINTSEL */
	clrbits_le32(regs + GPIO_IOINTSEL, BIT(offset));

	/* Select Input Mode or Output Mode in INOUTSEL */
	if (output)
		setbits_le32(regs + GPIO_INOUTSEL, BIT(offset));
	else
		clrbits_le32(regs + GPIO_INOUTSEL, BIT(offset));
}

static int d1h_gpio_direction_input(struct udevice *dev, unsigned offset)
{
	struct d1h_gpio_priv *priv = dev_get_priv(dev);

	d1h_gpio_set_direction(priv->regs, offset, false);

	return 0;
}

static int d1h_gpio_direction_output(struct udevice *dev, unsigned offset,
				      int value)
{
	struct d1h_gpio_priv *priv = dev_get_priv(dev);

	/* write GPIO value to output before selecting output mode of pin */
	d1h_gpio_set_value(dev, offset, value);
	d1h_gpio_set_direction(priv->regs, offset, true);

	return 0;
}

static int d1h_gpio_get_function(struct udevice *dev, unsigned offset)
{
	struct d1h_gpio_priv *priv = dev_get_priv(dev);
	uint32_t inoutsel = readl(priv->regs + GPIO_INOUTSEL);
	debug("%s:inoutsel reg:0x%x val:0x%x offset:%d  \n", __func__,(priv->regs + GPIO_INOUTSEL),inoutsel,offset);
	if (readl(priv->regs + GPIO_INOUTSEL) & BIT(offset))
		return GPIOF_OUTPUT;
	else
		return GPIOF_INPUT;
}

static int d1h_gpio_probe(struct udevice *dev)
{
	struct gpio_dev_priv *uc_priv = dev_get_uclass_priv(dev);
	struct d1h_gpio_priv *priv = dev_get_priv(dev);
	struct fdtdec_phandle_args args;
    const void *blob = gd->fdt_blob;
	int node = fdt_path_offset(blob, dev->node_.np->full_name);
	int ret;

	priv->regs = dev_read_addr_ptr(dev);
	uc_priv->bank_name = dev->name;

	ret = fdtdec_parse_phandle_with_args(gd->fdt_blob, node, "gpio-ranges",
					     NULL, 3, 0, &args);
	priv->pfc_offset = ret == 0 ? args.args[1] : -1;
	uc_priv->gpio_count = ret == 0 ? args.args[2] : RCAR_MAX_GPIO_PER_BANK;
    debug("%s: d1h gpio probe called\n", __func__);
	return ret;
}

static const struct dm_gpio_ops d1h_gpio_ops = {
	.direction_input	= d1h_gpio_direction_input,
	.direction_output	= d1h_gpio_direction_output,
	.get_value		= d1h_gpio_get_value,
	.set_value		= d1h_gpio_set_value,
	.get_function		= d1h_gpio_get_function,
};

static const struct udevice_id d1h_gpio_ids[] = {
	{ .compatible = "renesas,d1h-gpio" },
	{ /* sentinel */ }
};

U_BOOT_DRIVER(d1h_gpio) = {
	.name	= "d1h-gpio",
	.id	= UCLASS_GPIO,
	.of_match = d1h_gpio_ids,
	.ops	= &d1h_gpio_ops,
	.priv_auto	= sizeof(struct d1h_gpio_priv),
	.probe	= d1h_gpio_probe,
};