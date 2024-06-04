// SPDX-License-Identifier: GPL-2.0+
/*
 * D1H soc R7S721063 processor support
 *
 * Copyright (C) 2024 Xu Songxue <xusongxue88@163.com>
 */

#include <common.h>
#include <dm.h>
#include <asm/global_data.h>
#include <dm/lists.h>
#include <dm/pinctrl.h>
#include <linux/bitops.h>
#include <linux/io.h>
#include <linux/err.h>

DECLARE_GLOBAL_DATA_PTR;

struct d1h_pfc_plat {
	void __iomem	*base;
};

#define D1H_OFFSET_PMMR          (0x0000)
#define D1H_OFFSET_GPSR          (0x0004)
#define D1H_OFFSET_IPSR          (0x0020)
#define D1H_OFFSET_IOCTRL        (0x0060)
#define D1H_OFFSET_MOD           (0x0090)
#define D1H_OFFSET_PUPR          (0x0100)


#define D1H_FPC_GPSR_NUM         (5)
#define D1H_FPC_IPSR_NUM         (9)
#define D1H_FPC_MOD_NUM          (2)
#define D1H_FPC_IOCTRL_NUM       (3)
#define D1H_FPC_PUPR_NUM         (5)

static const char d1h_gpsr_name[D1H_FPC_GPSR_NUM][10] = {
    "pfc-gpsr0",
    "pfc-gpsr1",
    "pfc-gpsr2",
    "pfc-gpsr3",
    "pfc-gpsr4",
};

static const char d1h_ipsr_name[D1H_FPC_IPSR_NUM][10] = {
    "pfc-ipsr0",
    "pfc-ipsr1",
    "pfc-ipsr2",
    "pfc-ipsr3",
    "pfc-ipsr4",
    "pfc-ipsr5",
    "pfc-ipsr6",
    "pfc-ipsr7",
    "pfc-ipsr8",    
};

static const char d1h_mod_name[D1H_FPC_MOD_NUM][13] = {
    "pfc-mod-sel",
    "pfc-mod-sel2",  
};

static const char d1h_ioctrl_name[D1H_FPC_IOCTRL_NUM][12] = {
    "pfc-ioctrl0",
    "pfc-ioctrl1",  
    "pfc-ioctrl2",  
};

static const char d1h_pupr_name[D1H_FPC_PUPR_NUM][10] = {
    "pfc-pupr0",
    "pfc-pupr1",
    "pfc-pupr2",
    "pfc-pupr3",
    "pfc-pupr4",
};

static int d1h_pfc_set_state(struct udevice *dev, struct udevice *config)
{
	debug("%s: set state\n", __func__);
	const void *blob = gd->fdt_blob;
	int node = fdt_path_offset(blob, config->node_.np->full_name);
	struct d1h_pfc_plat *plat = dev_get_plat(dev);
	u32 cells[128];
	u32 reg_tmp;
	int i, k, count;
	/***Set the ipsr register***/
	for(k = 0; k < D1H_FPC_IPSR_NUM; k++){
		count = fdtdec_get_int_array_count(blob, node, (char *)(&d1h_ipsr_name[k][0]),
					   cells, ARRAY_SIZE(cells));
		if (count > 0) {
			if( count > ARRAY_SIZE(cells))
			{
				printf("%s: unsupported ipsr array count %d max num is %d\n",
				__func__, count,ARRAY_SIZE(cells)/2);
			}
			else
			{
				for (i = 0; i < count/2 ; i++){
					writel(cells[i*2],(plat->base + D1H_OFFSET_PMMR));
					writel(cells[i*2 + 1],(plat->base + D1H_OFFSET_IPSR + 4*k));
					debug("Set IPSR%d(%x) mask/val: 0x%x/0x%x \n",k,(plat->base + D1H_OFFSET_IPSR + 4*k),cells[i*2],cells[i*2 + 1]);
				}
			}
		}
	}
	
	/***Set the mode-sel register***/
    for(k = 0; k < D1H_FPC_MOD_NUM; k++){
		count = fdtdec_get_int_array_count(blob, node, (char *)(&d1h_mod_name[k][0]),
					   cells, ARRAY_SIZE(cells));
		if (count > 0) {
			if( count > ARRAY_SIZE(cells))
			{
				printf("%s: unsupported mod-sel array count %d max num is %d\n",
				__func__, count,ARRAY_SIZE(cells)/2);
			}
			else
			{
				for (i = 0; i < count/2 ; i++){
					writel(cells[i*2],(plat->base + D1H_OFFSET_PMMR));
					writel(cells[i*2 + 1],(plat->base + D1H_OFFSET_MOD + 4*k));
					debug("Set MOD_SEL%d(%x) mask/val: 0x%x/0x%x \n",k,(plat->base + D1H_OFFSET_MOD + 4*k),cells[i*2],cells[i*2 + 1]);
				}
			}
		}
	}

	/***Set the ioctrl register***/
    for(k = 0; k < D1H_FPC_IOCTRL_NUM; k++){
		count = fdtdec_get_int_array_count(blob, node, (char *)(&d1h_ioctrl_name[k][0]),
					   cells, ARRAY_SIZE(cells));
		if (count > 0) {
			if( count > ARRAY_SIZE(cells))
			{
				printf("%s: unsupported ioctrl array count %d max num is %d\n",
				__func__, count,ARRAY_SIZE(cells)/2);
			}
			else
			{
				for (i = 0; i < count/2 ; i++){
					writel(cells[i*2],(plat->base + D1H_OFFSET_PMMR));
					writel(cells[i*2 + 1],(plat->base + D1H_OFFSET_IOCTRL + 4*k));
					debug("Set IOCTRL%d(%x) mask/val: 0x%x/0x%x \n",k,(plat->base + D1H_OFFSET_IOCTRL + 4*k),cells[i*2],cells[i*2 + 1]);
				}
			}
		}
	}

	/***Set the pupr register***/
    for(k = 0; k < D1H_FPC_PUPR_NUM; k++){
		count = fdtdec_get_int_array_count(blob, node, (char *)(&d1h_pupr_name[k][0]),
					   cells, ARRAY_SIZE(cells));
		if (count > 0) {
			if( count > ARRAY_SIZE(cells))
			{
				printf("%s: unsupported pupr array count %d max num is %d\n",
				__func__, count,ARRAY_SIZE(cells)/2);
			}
			else
			{
				for (i = 0; i < count/2 ; i++){
					reg_tmp = readl(plat->base + D1H_OFFSET_PUPR + 4*k) & cells[i*2];//set mask
					writel((reg_tmp | cells[i*2 + 1]),(plat->base + D1H_OFFSET_PUPR + 4*k));
					debug("Set PUPR%d(%x) mask/val: 0x%x/0x%x \n",k,(plat->base + D1H_OFFSET_PUPR + 4*k),cells[i*2],cells[i*2 + 1]);
				}
			}
		}
	}

	/***Set the gpsr register***/
    for(k = 0; k < D1H_FPC_GPSR_NUM; k++){
		count = fdtdec_get_int_array_count(blob, node, (char *)(&d1h_gpsr_name[k][0]),
					   cells, ARRAY_SIZE(cells));
		if (count > 0) {
			if( count > ARRAY_SIZE(cells))
			{
				printf("%s: unsupported gpsr array count %d max num is %d\n",
				__func__, count,ARRAY_SIZE(cells)/2);
			}
			else
			{
				for (i = 0; i < count/2 ; i++){
					writel(cells[i*2],(plat->base + D1H_OFFSET_PMMR));
					writel(cells[i*2 + 1],(plat->base + D1H_OFFSET_GPSR + 4*k));
					debug("Set GPSR%d(%x) mask/val: 0x%x/0x%x \n",k,(plat->base + D1H_OFFSET_GPSR + 4*k),cells[i*2],cells[i*2 + 1]);
				}
			}
		}
	}
	return 0;
}

const struct pinctrl_ops d1h_pfc_ops  = {
	.set_state = d1h_pfc_set_state,
};

static int d1h_pfc_probe(struct udevice *dev)
{
	struct d1h_pfc_plat *plat = dev_get_plat(dev);
	fdt_addr_t addr_base;
	ofnode node;
	addr_base = dev_read_addr(dev);
	if (addr_base == FDT_ADDR_T_NONE)
		return -EINVAL;
	plat->base = (void __iomem *)addr_base;
	dev_for_each_subnode(node, dev) {
		struct udevice *cdev;

		if (!ofnode_read_bool(node, "gpio-controller"))
			continue;

		device_bind_driver_to_node(dev, "d1h-gpio",
					   ofnode_get_name(node),
					   node, &cdev);
	}
	debug("%s: d1h pfc probe called\n", __func__);
	return 0;
}

static const struct udevice_id d1h_pfc_match[] = {
	{ .compatible = "d1h,pfc" },
	{}
};

U_BOOT_DRIVER(d1h_pfc) = {
	.name		= "d1h_pfc",
	.id		= UCLASS_PINCTRL,
	.of_match	= d1h_pfc_match,
	.probe		= d1h_pfc_probe,
	.plat_auto	= sizeof(struct d1h_pfc_plat),
	.ops		= &d1h_pfc_ops,
	.flags          = DM_FLAG_PRE_RELOC,
};
