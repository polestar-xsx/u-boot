#include <common.h>
#include <clk-uclass.h>
#include <dm.h>
#include <linux/bitops.h>
#include <common.h>
#include <errno.h>
#include <log.h>
#include <asm/global_data.h>
#include <asm/io.h>
#include <linux/bitops.h>
#include <wait_bit.h>
#include <asm/arch/base.h>
#define CPG_RST_MODEMR		0x0060

#define CPG_PLL0CR		0x00d8
#define CPG_SDCKCR		0x0074
#define TSTR0		0x04
#define TSTR0_STR0	BIT(0)


#define DEF_TYPE(_name, _id, _type...)	\
	{ .name = _name, .id = _id, .type = _type }
#define DEF_BASE(_name, _id, _type, _parent...)	\
	DEF_TYPE(_name, _id, _type, .parent = _parent)

#define DEF_INPUT(_name, _id) \
	DEF_TYPE(_name, _id, CLK_TYPE_IN)
#define DEF_FIXED(_name, _id, _parent, _div, _mult)	\
	DEF_BASE(_name, _id, CLK_TYPE_FF, _parent, .div = _div, .mult = _mult)
#define DEF_DIV6P1(_name, _id, _parent, _offset)	\
	DEF_BASE(_name, _id, CLK_TYPE_DIV6P1, _parent, .offset = _offset)
#define DEF_DIV6_RO(_name, _id, _parent, _offset, _div)	\
	DEF_BASE(_name, _id, CLK_TYPE_DIV6_RO, _parent, .offset = _offset, .div = _div, .mult = 1)
#define DEF_RATE(_name, _id, _rate)	\
	DEF_TYPE(_name, _id, CLK_TYPE_FR, .mult = _rate)

/* Convert from sparse base-100 to packed index space */
#define MOD_CLK_PACK(x)	((x) - ((x) / 100) * (100 - 32))

#define MOD_CLK_ID(x)	(MOD_CLK_BASE + MOD_CLK_PACK(x))

#define DEF_MOD(_name, _mod, _parent...)	\
	{ .name = _name, .id = MOD_CLK_ID(_mod), .parent = _parent }

struct cpg_mssr_info {
	const struct cpg_core_clk	*core_clk;
	unsigned int			core_clk_size;
	const struct mssr_mod_clk	*mod_clk;
	unsigned int			mod_clk_size;
	const struct mstp_stop_table	*mstp_table;
	unsigned int			mstp_table_size;
	const char			*reset_node;
	const char			*extalr_node;
	const char			*extal_usb_node;
	unsigned int			mod_clk_base;
	unsigned int			clk_extal_id;
	unsigned int			clk_extalr_id;
	unsigned int			clk_extal_usb_id;
	unsigned int			pll0_div;
	const void			*(*get_pll_config)(const u32 cpg_mode);
};

/*
 * Definitions of CPG Core Clocks
 *
 * These include:
 *   - Clock outputs exported to DT
 *   - External input clocks
 *   - Internal CPG clocks
 */
struct cpg_core_clk {
	/* Common */
	const char *name;
	unsigned int id;
	unsigned int type;
	/* Depending on type */
	unsigned int parent;	/* Core Clocks only */
	unsigned int div;
	unsigned int mult;
	unsigned int offset;
};

enum clk_types {
	/* Generic */
	CLK_TYPE_IN,		/* External Clock Input */
	CLK_TYPE_FF,		/* Fixed Factor Clock */
	CLK_TYPE_DIV6P1,	/* DIV6 Clock with 1 parent clock */
	CLK_TYPE_DIV6_RO,	/* DIV6 Clock read only with extra divisor */
	CLK_TYPE_FR,		/* Fixed Rate Clock */

	/* Custom definitions start here */
	CLK_TYPE_CUSTOM,
};



/*
 * Definitions of Module Clocks
 */
struct mssr_mod_clk {
	const char *name;
	unsigned int id;
	unsigned int parent;	/* Add MOD_CLK_BASE for Module Clocks */
};



struct mstp_stop_table {
	u32	sdis;
	u32	sen;
	u32	rdis;
	u32	ren;
};



/*
 * Module Standby and Software Reset register offets.
 *
 * If the registers exist, these are valid for SH-Mobile, R-Mobile,
 * R-Car Gen2, R-Car Gen3, and RZ/G1.
 * These are NOT valid for R-Car Gen1 and RZ/A1!
 */

/*
 * Module Stop Status Register offsets
 */

static const u16 mstpsr[] = {
	0x030, 0x038, 0x040, 0x048, 0x04C, 0x03C, 0x1C0, 0x1C4,
	0x9A0, 0x9A4, 0x9A8, 0x9AC,
};

#define	MSTPSR(i)	mstpsr[i]


/*
 * System Module Stop Control Register offsets
 */

static const u16 smstpcr[] = {
	0x130, 0x134, 0x138, 0x13C, 0x140, 0x144, 0x148, 0x14C,
	0x990, 0x994, 0x998, 0x99C,
};

#define	SMSTPCR(i)	smstpcr[i]


/* Realtime Module Stop Control Register offsets */
#define RMSTPCR(i)	(smstpcr[i] - 0x20)

/* Modem Module Stop Control Register offsets (r8a73a4) */
#define MMSTPCR(i)	(smstpcr[i] + 0x20)

/* Software Reset Clearing Register offsets */
#define	SRSTCLR(i)	(0x940 + (i) * 4)

struct clk_div_table {
	u8	val;
	u8	div;
};

/* SDHI divisors */
static const struct clk_div_table cpg_sdh_div_table[] = {
	{  0,  2 }, {  1,  3 }, {  2,  4 }, {  3,  6 },
	{  4,  8 }, {  5, 12 }, {  6, 16 }, {  7, 18 },
	{  8, 24 }, { 10, 36 }, { 11, 48 }, {  0,  0 },
};

static const struct clk_div_table cpg_sd01_div_table[] = {
	{  4,  8 }, {  5, 12 }, {  6, 16 }, {  7, 18 },
	{  8, 24 }, { 10, 36 }, { 11, 48 }, { 12, 10 },
	{  0,  0 },
};

bool renesas_clk_is_mod(struct clk *clk)
{
	return (clk->id >> 16) == CPG_MOD;
}

int renesas_clk_get_mod(struct clk *clk, struct cpg_mssr_info *info,
			const struct mssr_mod_clk **mssr)
{
	const unsigned long clkid = clk->id & 0xffff;
	int i;

	for (i = 0; i < info->mod_clk_size; i++) {
		if (info->mod_clk[i].id !=
		    (info->mod_clk_base + MOD_CLK_PACK(clkid)))
			continue;

		*mssr = &info->mod_clk[i];
		return 0;
	}

	return -ENODEV;
}

int renesas_clk_get_core(struct clk *clk, struct cpg_mssr_info *info,
			 const struct cpg_core_clk **core)
{
	const unsigned long clkid = clk->id & 0xffff;
	int i;

	for (i = 0; i < info->core_clk_size; i++) {
		if (info->core_clk[i].id != clkid)
			continue;

		*core = &info->core_clk[i];
		return 0;
	}

	return -ENODEV;
}

int renesas_clk_get_parent(struct clk *clk, struct cpg_mssr_info *info,
			   struct clk *parent)
{
	const struct cpg_core_clk *core;
	const struct mssr_mod_clk *mssr;
	int ret;

	if (renesas_clk_is_mod(clk)) {
		ret = renesas_clk_get_mod(clk, info, &mssr);
		if (ret)
			return ret;

		parent->id = mssr->parent;
	} else {
		ret = renesas_clk_get_core(clk, info, &core);
		if (ret)
			return ret;

		if (core->type == CLK_TYPE_IN)
			parent->id = ~0;	/* Top-level clock */
		else
			parent->id = core->parent;
	}

	parent->dev = clk->dev;

	return 0;
}

int renesas_clk_endisable(struct clk *clk, void __iomem *base, bool enable)
{
	const unsigned long clkid = clk->id & 0xffff;
	const unsigned int reg = clkid / 100;
	const unsigned int bit = clkid % 100;
	const u32 bitmask = BIT(bit);

	if (!renesas_clk_is_mod(clk))
		return -EINVAL;

	debug("%s[%i] MSTP %lu=%02u/%02u %s\n", __func__, __LINE__,
	      clkid, reg, bit, enable ? "ON" : "OFF");

	if (enable) {
		clrbits_le32(base + SMSTPCR(reg), bitmask);
		return wait_for_bit_le32(base + MSTPSR(reg),
				    bitmask, 0, 100, 0);
	} else {
		setbits_le32(base + SMSTPCR(reg), bitmask);
		return 0;
	}
}

int renesas_clk_remove(void __iomem *base, struct cpg_mssr_info *info)
{
	unsigned int i;

	/* Stop TMU0 */
	clrbits_le32(TMU_BASE + TSTR0, TSTR0_STR0);

	/* Stop module clock */
	for (i = 0; i < info->mstp_table_size; i++) {
		clrsetbits_le32(base + SMSTPCR(i),
				info->mstp_table[i].sdis,
				info->mstp_table[i].sen);
		clrsetbits_le32(base + RMSTPCR(i),
				info->mstp_table[i].rdis,
				info->mstp_table[i].ren);
	}

	return 0;
}

static u8 d1h_clk_get_sdh_div(const struct clk_div_table *table, u8 val)
{
	for (;;) {
		if (!(*table).div)
			return 0xff;

		if ((*table).val == val)
			return (*table).div;

		table++;
	}
}

static int d1h_clk_enable(struct clk *clk)
{
	struct d1h_clk_priv *priv = dev_get_priv(clk->dev);

	return renesas_clk_endisable(clk, priv->base, true);
}

static int d1h_clk_disable(struct clk *clk)
{
	struct d1h_clk_priv *priv = dev_get_priv(clk->dev);

	return renesas_clk_endisable(clk, priv->base, false);
}

static ulong d1h_clk_get_rate(struct clk *clk)
{
	struct d1h_clk_priv *priv = dev_get_priv(clk->dev);
	struct cpg_mssr_info *info = priv->info;
	struct clk parent;
	const struct cpg_core_clk *core;
	const struct rcar_d1h_cpg_pll_config *pll_config =
					priv->cpg_pll_config;
	u32 value, mult, div, rate = 0;
	int ret;

	debug("%s[%i] Clock: id=%lu\n", __func__, __LINE__, clk->id);

	ret = renesas_clk_get_parent(clk, info, &parent);
	if (ret) {
		printf("%s[%i] parent fail, ret=%i\n", __func__, __LINE__, ret);
		return ret;
	}

	if (renesas_clk_is_mod(clk)) {
		rate = d1h_clk_get_rate(&parent);
		debug("%s[%i] MOD clk: parent=%lu => rate=%u\n",
		      __func__, __LINE__, parent.id, rate);
		return rate;
	}

	ret = renesas_clk_get_core(clk, info, &core);
	if (ret)
		return ret;

	switch (core->type) {
	case CLK_TYPE_IN:
		if (core->id == info->clk_extal_id) {
			rate = clk_get_rate(&priv->clk_extal);
			debug("%s[%i] EXTAL clk: rate=%u\n",
			      __func__, __LINE__, rate);
			return rate;
		}

		if (core->id == info->clk_extal_usb_id) {
			rate = clk_get_rate(&priv->clk_extal_usb);
			debug("%s[%i] EXTALR clk: rate=%u\n",
			      __func__, __LINE__, rate);
			return rate;
		}

		return -EINVAL;

	case CLK_TYPE_FF:
		rate = (d1h_clk_get_rate(&parent) * core->mult) / core->div;
		debug("%s[%i] FIXED clk: parent=%i mul=%i div=%i => rate=%u\n",
		      __func__, __LINE__,
		      core->parent, core->mult, core->div, rate);
		return rate;

	case CLK_TYPE_DIV6P1:	/* DIV6 Clock with 1 parent clock */
		value = (readl(priv->base + core->offset) & 0x3f) + 1;
		rate = d1h_clk_get_rate(&parent) / value;
		debug("%s[%i] DIV6P1 clk: parent=%i div=%i => rate=%u\n",
		      __func__, __LINE__,
		      core->parent, value, rate);
		return rate;

	case CLK_TYPE_d1h_MAIN:
		rate = d1h_clk_get_rate(&parent) / pll_config->extal_div;
		debug("%s[%i] MAIN clk: parent=%i extal_div=%i => rate=%u\n",
		      __func__, __LINE__,
		      core->parent, pll_config->extal_div, rate);
		return rate;

	case CLK_TYPE_d1h_PLL0:
		/*
		 * PLL0 is a  configurable multiplier clock except on R-Car
		 * V2H/E2. Register the PLL0 clock as a fixed factor clock for
		 * now as there's no generic multiplier clock implementation and
		 * we  currently  have no need to change  the multiplier value.
		 */
		mult = pll_config->pll0_mult;
		if (!mult) {
			value = readl(priv->base + CPG_PLL0CR);
			mult = (((value >> 24) & 0x7f) + 1) * 2;
		}

		rate = (d1h_clk_get_rate(&parent) * mult) / info->pll0_div;
		debug("%s[%i] PLL0 clk: parent=%i mult=%u => rate=%u\n",
		      __func__, __LINE__, core->parent, mult, rate);
		return rate;

	case CLK_TYPE_d1h_PLL1:
		rate = (d1h_clk_get_rate(&parent) * pll_config->pll1_mult) / 2;
		debug("%s[%i] PLL1 clk: parent=%i mul=%i => rate=%u\n",
		      __func__, __LINE__,
		      core->parent, pll_config->pll1_mult, rate);
		return rate;

	case CLK_TYPE_d1h_PLL3:
		rate = d1h_clk_get_rate(&parent) * pll_config->pll3_mult;
		debug("%s[%i] PLL3 clk: parent=%i mul=%i => rate=%u\n",
		      __func__, __LINE__,
		      core->parent, pll_config->pll3_mult, rate);
		return rate;

	case CLK_TYPE_d1h_SDH:
		value = (readl(priv->base + CPG_SDCKCR) >> 8) & 0xf;
		div = d1h_clk_get_sdh_div(cpg_sdh_div_table, value);
		rate = d1h_clk_get_rate(&parent) / div;
		debug("%s[%i] SDH clk: parent=%i div=%i => rate=%u\n",
		      __func__, __LINE__,
		      core->parent, div, rate);
		return rate;

	case CLK_TYPE_d1h_SD0:
		value = (readl(priv->base + CPG_SDCKCR) >> 4) & 0xf;
		div = d1h_clk_get_sdh_div(cpg_sd01_div_table, value);
		rate = d1h_clk_get_rate(&parent) / div;
		debug("%s[%i] SD0 clk: parent=%i div=%i => rate=%u\n",
		      __func__, __LINE__,
		      core->parent, div, rate);
		return rate;

	case CLK_TYPE_d1h_SD1:
		value = (readl(priv->base + CPG_SDCKCR) >> 0) & 0xf;
		div = d1h_clk_get_sdh_div(cpg_sd01_div_table, value);
		rate = d1h_clk_get_rate(&parent) / div;
		debug("%s[%i] SD1 clk: parent=%i div=%i => rate=%u\n",
		      __func__, __LINE__,
		      core->parent, div, rate);
		return rate;
	}

	printf("%s[%i] unknown fail\n", __func__, __LINE__);

	return -ENOENT;
}

static int d1h_clk_setup_mmcif_div(struct clk *clk, ulong rate)
{
	struct d1h_clk_priv *priv = dev_get_priv(clk->dev);
	struct cpg_mssr_info *info = priv->info;
	const struct cpg_core_clk *core;
	struct clk parent, pparent;
	u32 val;
	int ret;

	ret = renesas_clk_get_parent(clk, info, &parent);
	if (ret) {
		debug("%s[%i] parent fail, ret=%i\n", __func__, __LINE__, ret);
		return ret;
	}

	if (renesas_clk_is_mod(&parent))
		return 0;

	ret = renesas_clk_get_core(&parent, info, &core);
	if (ret)
		return ret;

	if (strcmp(core->name, "mmc0") && strcmp(core->name, "mmc1"))
		return 0;

	ret = renesas_clk_get_parent(&parent, info, &pparent);
	if (ret) {
		debug("%s[%i] parent fail, ret=%i\n", __func__, __LINE__, ret);
		return ret;
	}

	val = (d1h_clk_get_rate(&pparent) / rate) - 1;

	debug("%s[%i] MMCIF offset=%x\n", __func__, __LINE__, core->offset);

	writel(val, priv->base + core->offset);

	return 0;
}

static ulong d1h_clk_set_rate(struct clk *clk, ulong rate)
{
	/* Force correct MMC-IF divider configuration if applicable */
	d1h_clk_setup_mmcif_div(clk, rate);
	return d1h_clk_get_rate(clk);
}

static int d1h_clk_of_xlate(struct clk *clk, struct ofnode_phandle_args *args)
{
	if (args->args_count != 2) {
		debug("Invaild args_count: %d\n", args->args_count);
		return -EINVAL;
	}

	clk->id = (args->args[0] << 16) | args->args[1];

	return 0;
}

const struct clk_ops d1h_clk_ops = {
	.enable		= d1h_clk_enable,
	.disable	= d1h_clk_disable,
	.get_rate	= d1h_clk_get_rate,
	.set_rate	= d1h_clk_set_rate,
	.of_xlate	= d1h_clk_of_xlate,
};

int d1h_clk_probe(struct udevice *dev)
{
	struct d1h_clk_priv *priv = dev_get_priv(dev);
	struct cpg_mssr_info *info =
		(struct cpg_mssr_info *)dev_get_driver_data(dev);
	fdt_addr_t rst_base;
	u32 cpg_mode;
	int ret;

	priv->base = dev_read_addr_ptr(dev);
	if (!priv->base)
		return -EINVAL;

	priv->info = info;
	ret = fdt_node_offset_by_compatible(gd->fdt_blob, -1, info->reset_node);
	if (ret < 0)
		return ret;

	rst_base = fdtdec_get_addr_size_auto_noparent(gd->fdt_blob, ret, "reg",
						      0, NULL, false);
	if (rst_base == FDT_ADDR_T_NONE)
		return -EINVAL;

	cpg_mode = readl(rst_base + CPG_RST_MODEMR);

	priv->cpg_pll_config =
		(struct rcar_d1h_cpg_pll_config *)info->get_pll_config(cpg_mode);
	if (!priv->cpg_pll_config->extal_div)
		return -EINVAL;

	ret = clk_get_by_name(dev, "extal", &priv->clk_extal);
	if (ret < 0)
		return ret;

	if (info->extal_usb_node) {
		ret = clk_get_by_name(dev, info->extal_usb_node,
				      &priv->clk_extal_usb);
		if (ret < 0)
			return ret;
	}

	return 0;
}

int d1h_clk_remove(struct udevice *dev)
{
	struct d1h_clk_priv *priv = dev_get_priv(dev);

	return renesas_clk_remove(priv->base, priv->info);
}

enum clk_ids {
	/* Core Clock Outputs exported to DT */
	LAST_DT_CORE_CLK = d1h_CLK_OSC,

	/* External Input Clocks */
	CLK_EXTAL,
	CLK_USB_EXTAL,

	/* Internal Core Clocks */
	CLK_MAIN,
	CLK_PLL0,
	CLK_PLL1,
	CLK_PLL3,
	CLK_PLL1_DIV2,

	/* Module Clocks */
	MOD_CLK_BASE
};

static const struct cpg_core_clk d1h_core_clks[] = {
	/* External Clock Inputs */
	DEF_INPUT("extal",     CLK_EXTAL),
	DEF_INPUT("usb_extal", CLK_USB_EXTAL),

	/* Internal Core Clocks */
	DEF_BASE(".main",       CLK_MAIN, CLK_TYPE_d1h_MAIN, CLK_EXTAL),
	DEF_BASE(".pll0",       CLK_PLL0, CLK_TYPE_d1h_PLL0, CLK_MAIN),
	DEF_BASE(".pll1",       CLK_PLL1, CLK_TYPE_d1h_PLL1, CLK_MAIN),
	DEF_BASE(".pll3",       CLK_PLL3, CLK_TYPE_d1h_PLL3, CLK_MAIN),

	DEF_FIXED(".pll1_div2", CLK_PLL1_DIV2, CLK_PLL1, 2, 1),

	/* Core Clock Outputs */
	DEF_BASE("adsp", d1h_CLK_ADSP, CLK_TYPE_d1h_ADSP, CLK_PLL1),
	DEF_BASE("sdh",  d1h_CLK_SDH,  CLK_TYPE_d1h_SDH,  CLK_PLL1),
	DEF_BASE("sd0",  d1h_CLK_SD0,  CLK_TYPE_d1h_SD0,  CLK_PLL1),
	DEF_BASE("qspi", d1h_CLK_QSPI, CLK_TYPE_d1h_QSPI, CLK_PLL1_DIV2),
	DEF_BASE("rcan", d1h_CLK_RCAN, CLK_TYPE_d1h_RCAN, CLK_USB_EXTAL),

	DEF_FIXED("z2",     d1h_CLK_Z2,    CLK_PLL0,          1, 1),
	DEF_FIXED("zg",     d1h_CLK_ZG,    CLK_PLL1,          6, 1),
	DEF_FIXED("zx",     d1h_CLK_ZX,    CLK_PLL1,          3, 1),
	DEF_FIXED("zs",     d1h_CLK_ZS,    CLK_PLL1,          6, 1),
	DEF_FIXED("hp",     d1h_CLK_HP,    CLK_PLL1,         12, 1),
	DEF_FIXED("i",      d1h_CLK_I,     CLK_PLL1,          2, 1),
	DEF_FIXED("b",      d1h_CLK_B,     CLK_PLL1,         12, 1),
	DEF_FIXED("lb",     d1h_CLK_LB,    CLK_PLL1,         24, 1),
	DEF_FIXED("p",      d1h_CLK_P,     CLK_PLL1,         24, 1),
	DEF_FIXED("cl",     d1h_CLK_CL,    CLK_PLL1,         48, 1),
	DEF_FIXED("cp",     d1h_CLK_CP,    CLK_PLL1,         48, 1),
	DEF_FIXED("m2",     d1h_CLK_M2,    CLK_PLL1,          8, 1),
	DEF_FIXED("zb3",    d1h_CLK_ZB3,   CLK_PLL3,          4, 1),
	DEF_FIXED("zb3d2",  d1h_CLK_ZB3D2, CLK_PLL3,          8, 1),
	DEF_FIXED("ddr",    d1h_CLK_DDR,   CLK_PLL3,          8, 1),
	DEF_FIXED("mp",     d1h_CLK_MP,    CLK_PLL1_DIV2,    15, 1),
	DEF_FIXED("cpex",   d1h_CLK_CPEX,  CLK_EXTAL,         2, 1),
	DEF_FIXED("r",      d1h_CLK_R,     CLK_PLL1,      49152, 1),
	DEF_FIXED("osc",    d1h_CLK_OSC,   CLK_PLL1,      12288, 1),

	DEF_DIV6P1("sd2",   d1h_CLK_SD2,   CLK_PLL1_DIV2, 0x078),
	DEF_DIV6P1("sd3",   d1h_CLK_SD3,   CLK_PLL1_DIV2, 0x26c),
	DEF_DIV6P1("mmc0",  d1h_CLK_MMC0,  CLK_PLL1_DIV2, 0x240),
};

static const struct mssr_mod_clk d1h_mod_clks[] = {
	DEF_MOD("msiof0",		   0,	d1h_CLK_MP),
	DEF_MOD("vcp0",			 101,	d1h_CLK_ZS),
	DEF_MOD("vpc0",			 103,	d1h_CLK_ZS),
	DEF_MOD("jpu",			 106,	d1h_CLK_M2),
	DEF_MOD("tmu1",			 111,	d1h_CLK_P),
	DEF_MOD("3dg",			 112,	d1h_CLK_ZG),
	DEF_MOD("2d-dmac",		 115,	d1h_CLK_ZS),
	DEF_MOD("fdp1-0",		 119,	d1h_CLK_ZS),
	DEF_MOD("tmu3",			 121,	d1h_CLK_P),
	DEF_MOD("tmu2",			 122,	d1h_CLK_P),
	DEF_MOD("cmt0",			 124,	d1h_CLK_R),
	DEF_MOD("tmu0",			 125,	d1h_CLK_CP),
	DEF_MOD("vsp1du0",		 128,	d1h_CLK_ZS),
	DEF_MOD("vsp1-sy",		 131,	d1h_CLK_ZS),
	DEF_MOD("scifa2",		 202,	d1h_CLK_MP),
	DEF_MOD("scifa1",		 203,	d1h_CLK_MP),
	DEF_MOD("scifa0",		 204,	d1h_CLK_MP),
	DEF_MOD("msiof2",		 205,	d1h_CLK_MP),
	DEF_MOD("scifb0",		 206,	d1h_CLK_MP),
	DEF_MOD("scifb1",		 207,	d1h_CLK_MP),
	DEF_MOD("msiof1",		 208,	d1h_CLK_MP),
	DEF_MOD("scifb2",		 216,	d1h_CLK_MP),
	DEF_MOD("sys-dmac1",		 218,	d1h_CLK_ZS),
	DEF_MOD("sys-dmac0",		 219,	d1h_CLK_ZS),
	DEF_MOD("tpu0",			 304,	d1h_CLK_CP),
	DEF_MOD("sdhi3",		 311,	d1h_CLK_SD3),
	DEF_MOD("sdhi2",		 312,	d1h_CLK_SD2),
	DEF_MOD("sdhi0",		 314,	d1h_CLK_SD0),
	DEF_MOD("mmcif0",		 315,	d1h_CLK_MMC0),
	DEF_MOD("iic0",			 318,	d1h_CLK_HP),
	DEF_MOD("iic1",			 323,	d1h_CLK_HP),
	DEF_MOD("cmt1",			 329,	d1h_CLK_R),
	DEF_MOD("usbhs-dmac0",		 330,	d1h_CLK_HP),
	DEF_MOD("usbhs-dmac1",		 331,	d1h_CLK_HP),
	DEF_MOD("rwdt",			 402,	d1h_CLK_R),
	DEF_MOD("irqc",			 407,	d1h_CLK_CP),
	DEF_MOD("intc-sys",		 408,	d1h_CLK_ZS),
	DEF_MOD("audio-dmac0",		 502,	d1h_CLK_HP),
	DEF_MOD("adsp_mod",		 506,	d1h_CLK_ADSP),
	DEF_MOD("pwm",			 523,	d1h_CLK_P),
	DEF_MOD("usb-ehci",		 703,	d1h_CLK_MP),
	DEF_MOD("usbhs",		 704,	d1h_CLK_HP),
	DEF_MOD("hscif2",		 713,	d1h_CLK_ZS),
	DEF_MOD("scif5",		 714,	d1h_CLK_P),
	DEF_MOD("scif4",		 715,	d1h_CLK_P),
	DEF_MOD("hscif1",		 716,	d1h_CLK_ZS),
	DEF_MOD("hscif0",		 717,	d1h_CLK_ZS),
	DEF_MOD("scif3",		 718,	d1h_CLK_P),
	DEF_MOD("scif2",		 719,	d1h_CLK_P),
	DEF_MOD("scif1",		 720,	d1h_CLK_P),
	DEF_MOD("scif0",		 721,	d1h_CLK_P),
	DEF_MOD("du1",			 723,	d1h_CLK_ZX),
	DEF_MOD("du0",			 724,	d1h_CLK_ZX),
	DEF_MOD("ipmmu-sgx",		 800,	d1h_CLK_ZX),
	DEF_MOD("mlb",			 802,	d1h_CLK_HP),
	DEF_MOD("vin1",			 810,	d1h_CLK_ZG),
	DEF_MOD("vin0",			 811,	d1h_CLK_ZG),
	DEF_MOD("etheravb",		 812,	d1h_CLK_HP),
	DEF_MOD("ether",		 813,	d1h_CLK_P),
	DEF_MOD("gyro-adc",		 901,	d1h_CLK_P),
	DEF_MOD("gpio6",		 905,	d1h_CLK_CP),
	DEF_MOD("gpio5",		 907,	d1h_CLK_CP),
	DEF_MOD("gpio4",		 908,	d1h_CLK_CP),
	DEF_MOD("gpio3",		 909,	d1h_CLK_CP),
	DEF_MOD("gpio2",		 910,	d1h_CLK_CP),
	DEF_MOD("gpio1",		 911,	d1h_CLK_CP),
	DEF_MOD("gpio0",		 912,	d1h_CLK_CP),
	DEF_MOD("can1",			 915,	d1h_CLK_P),
	DEF_MOD("can0",			 916,	d1h_CLK_P),
	DEF_MOD("qspi_mod",		 917,	d1h_CLK_QSPI),
	DEF_MOD("i2c5",			 925,	d1h_CLK_HP),
	DEF_MOD("i2c4",			 927,	d1h_CLK_HP),
	DEF_MOD("i2c3",			 928,	d1h_CLK_HP),
	DEF_MOD("i2c2",			 929,	d1h_CLK_HP),
	DEF_MOD("i2c1",			 930,	d1h_CLK_HP),
	DEF_MOD("i2c0",			 931,	d1h_CLK_HP),
	DEF_MOD("ssi-all",		1005,	d1h_CLK_P),
	DEF_MOD("ssi9",			1006,	MOD_CLK_ID(1005)),
	DEF_MOD("ssi8",			1007,	MOD_CLK_ID(1005)),
	DEF_MOD("ssi7",			1008,	MOD_CLK_ID(1005)),
	DEF_MOD("ssi6",			1009,	MOD_CLK_ID(1005)),
	DEF_MOD("ssi5",			1010,	MOD_CLK_ID(1005)),
	DEF_MOD("ssi4",			1011,	MOD_CLK_ID(1005)),
	DEF_MOD("ssi3",			1012,	MOD_CLK_ID(1005)),
	DEF_MOD("ssi2",			1013,	MOD_CLK_ID(1005)),
	DEF_MOD("ssi1",			1014,	MOD_CLK_ID(1005)),
	DEF_MOD("ssi0",			1015,	MOD_CLK_ID(1005)),
	DEF_MOD("scu-all",		1017,	d1h_CLK_P),
	DEF_MOD("scu-dvc1",		1018,	MOD_CLK_ID(1017)),
	DEF_MOD("scu-dvc0",		1019,	MOD_CLK_ID(1017)),
	DEF_MOD("scu-ctu1-mix1",	1020,	MOD_CLK_ID(1017)),
	DEF_MOD("scu-ctu0-mix0",	1021,	MOD_CLK_ID(1017)),
	DEF_MOD("scu-src6",		1025,	MOD_CLK_ID(1017)),
	DEF_MOD("scu-src5",		1026,	MOD_CLK_ID(1017)),
	DEF_MOD("scu-src4",		1027,	MOD_CLK_ID(1017)),
	DEF_MOD("scu-src3",		1028,	MOD_CLK_ID(1017)),
	DEF_MOD("scu-src2",		1029,	MOD_CLK_ID(1017)),
	DEF_MOD("scu-src1",		1030,	MOD_CLK_ID(1017)),
	DEF_MOD("scifa3",		1106,	d1h_CLK_MP),
	DEF_MOD("scifa4",		1107,	d1h_CLK_MP),
	DEF_MOD("scifa5",		1108,	d1h_CLK_MP),
};

/*
 * CPG Clock Data
 */

/*
 *   MD		EXTAL		PLL0	PLL1	PLL3
 * 14 13 19	(MHz)		*1	*2
 *---------------------------------------------------
 * 0  0  1	15		x200/3	x208/2	x88
 * 0  1  1	20		x150/3	x156/2	x66
 * 1  0  1	26 / 2		x230/3	x240/2	x102
 * 1  1  1	30 / 2		x200/3	x208/2	x88
 *
 * *1 :	Table 7.5c indicates VCO output (PLL0 = VCO/3)
 * *2 :	Table 7.5c indicates VCO output (PLL1 = VCO/2)
 */
#define CPG_PLL_CONFIG_INDEX(md)	((((md) & BIT(14)) >> 13) | \
					 (((md) & BIT(13)) >> 13))
static const struct rcar_d1h_cpg_pll_config cpg_pll_configs[4] = {
	{ 1, 208,  88, 200 },
	{ 1, 156,  66, 150 },
	{ 2, 240, 102, 230 },
	{ 2, 208,  88, 200 },
};

static const struct mstp_stop_table d1h_mstp_table[] = {
	{ 0x00440801, 0x400000, 0x00440801, 0x0 },
	{ 0x936899DA, 0x0, 0x936899DA, 0x0 },
	{ 0x100D21FC, 0x2000, 0x100D21FC, 0x0 },
	{ 0xE084D810, 0x0, 0xE084D810, 0x0 },
	{ 0x800001C4, 0x180, 0x800001C4, 0x0 },
	{ 0x40C00044, 0x0, 0x40C00044, 0x0 },
	{ 0x0, 0x0, 0x0, 0x0 },	/* SMSTP6 is not present on d1h */
	{ 0x013FE618, 0x80000, 0x013FE618, 0x0 },
	{ 0x40803C05, 0x0, 0x40803C05, 0x0 },
	{ 0xFB879FEE, 0x0, 0xFB879FEE, 0x0 },
	{ 0xFFFEFFE0, 0x0, 0xFFFEFFE0, 0x0 },
	{ 0x000001C0, 0x0, 0x000001C0, 0x0 },
};

static const void *d1h_get_pll_config(const u32 cpg_mode)
{
	return &cpg_pll_configs[CPG_PLL_CONFIG_INDEX(cpg_mode)];
}

static const struct cpg_mssr_info d1h_cpg_mssr_info = {
	.core_clk		= d1h_core_clks,
	.core_clk_size		= ARRAY_SIZE(d1h_core_clks),
	.mod_clk		= d1h_mod_clks,
	.mod_clk_size		= ARRAY_SIZE(d1h_mod_clks),
	.mstp_table		= d1h_mstp_table,
	.mstp_table_size	= ARRAY_SIZE(d1h_mstp_table),
	.reset_node		= "renesas,d1h-rst",
	.extal_usb_node		= "usb_extal",
	.mod_clk_base		= MOD_CLK_BASE,
	.clk_extal_id		= CLK_EXTAL,
	.clk_extal_usb_id	= CLK_USB_EXTAL,
	.pll0_div		= 2,
	.get_pll_config		= d1h_get_pll_config,
};

static const struct udevice_id d1h_clk_ids[] = {
	{
		.compatible	= "renesas,d1h_cpg_mssr",
		.data		= (ulong)&d1h_cpg_mssr_info
	},
	{ }
};

U_BOOT_DRIVER(clk_d1h) = {
	.name		= "clk_d1h",
	.id		= UCLASS_CLK,
	.of_match	= d1h_clk_ids,
	.priv_auto	= sizeof(struct d1h_clk_priv),
	.ops		= &d1h_clk_ops,
	.probe		= d1h_clk_probe,
	.remove		= d1h_clk_remove,
};