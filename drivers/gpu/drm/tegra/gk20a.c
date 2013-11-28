/*
 * Copyright (C) 2013 NVIDIA Corporation
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/reset.h>
#include <linux/regulator/consumer.h>
#include <linux/tegra-powergate.h>

struct gk20a {
	struct device *dev;
	void __iomem *regs;
	void __iomem *bar1;

	struct reset_control *rst;
	struct clk *clk;
	struct clk *clk_pll;

	struct regulator *vdd;

	int irq;
	int irq_nostall;
};

static inline unsigned long gk20a_readl(struct gk20a *gpu, unsigned long offset)
{
	unsigned long value = readl(gpu->regs + offset);
	dev_dbg(gpu->dev, "%08lx > %08lx\n", offset, value);
	return value;
}

static inline void gk20a_writel(struct gk20a *gpu, unsigned long value,
				unsigned long offset)
{
	dev_dbg(gpu->dev, "%08lx < %08lx\n", offset, value);
	writel(value, gpu->regs + offset);
}

static irqreturn_t gk20a_irq(int irq, void *data)
{
	struct gk20a *gpu = data;

	dev_dbg(gpu->dev, "> %s(irq=%d, data=%p)\n", __func__, irq, data);

	dev_dbg(gpu->dev, "< %s()\n", __func__);
	return IRQ_HANDLED;
}

static int gk20a_power_up(struct gk20a *gpu)
{
	int err;

	reset_control_assert(gpu->rst);

	err = clk_enable(gpu->clk);
	if (err < 0)
		return err;

	err = tegra_powergate_remove_clamping(TEGRA_POWERGATE_3D);
	if (err < 0)
		return err;

	reset_control_deassert(gpu->rst);

	return 0;
}

static int gk20a_init(struct gk20a *gpu)
{
	unsigned long value;
	int err;

	err = gk20a_power_up(gpu);
	if (err < 0)
		return err;

	value = gk20a_readl(gpu, 0x000000);
	dev_dbg(gpu->dev, "NV_PMC_BOOT_0: %08lx\n", value);
	dev_dbg(gpu->dev, "  Revision: %lu.%lu\n", (value >> 4) & 0xf,
		value & 0xf);
	dev_dbg(gpu->dev, "  Device ID: %lx\n", (value >> 12) & 0x3f);
	dev_dbg(gpu->dev, "  Implementation: %lx\n", (value >> 20) & 0xf);
	dev_dbg(gpu->dev, "  Architecture: %lx\n", (value >> 24) & 0x1f);
	dev_dbg(gpu->dev, "  Foundry: %lx\n", (value >> 29) & 0x7);

	value = gk20a_readl(gpu, 0x000004);
	dev_dbg(gpu->dev, "NV_PMC_BOOT_1: %08lx\n", value);

	value = gk20a_readl(gpu, 0x000008);
	dev_dbg(gpu->dev, "NV_PMC_BOOT_2: %08lx\n", value);

	value = gk20a_readl(gpu, 0x137250);
	dev_dbg(gpu->dev, "0x00137250: %08lx\n", value);

	return 0;
}

static int tegra_gk20a_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct gk20a *gpu;
	int err;

	dev_dbg(&pdev->dev, "> %s(pdev=%p)\n", __func__, pdev);

	if (dev_get_drvdata(pdev->dev.parent) == NULL) {
		err = -EPROBE_DEFER;
		goto out;
	}

	gpu = devm_kzalloc(&pdev->dev, sizeof(*gpu), GFP_KERNEL);
	if (!gpu) {
		err = -ENOMEM;
		goto out;
	}

	gpu->dev = &pdev->dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	gpu->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(gpu->regs)) {
		err = PTR_ERR(gpu->regs);
		goto out;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	gpu->bar1 = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(gpu->bar1)) {
		err = PTR_ERR(gpu->bar1);
		goto out;
	}

	gpu->vdd = devm_regulator_get(&pdev->dev, "vdd");
	if (IS_ERR(gpu->vdd)) {
		err = PTR_ERR(gpu->vdd);
		goto out;
	}

	gpu->rst = devm_reset_control_get(&pdev->dev, "gpu");
	if (IS_ERR(gpu->rst)) {
		err = PTR_ERR(gpu->rst);
		goto out;
	}

	gpu->clk = devm_clk_get(&pdev->dev, "gpu");
	if (IS_ERR(gpu->clk)) {
		err = PTR_ERR(gpu->clk);
		goto out;
	}

	err = clk_prepare(gpu->clk);
	if (err < 0)
		goto out;

	gpu->clk_pll = devm_clk_get(&pdev->dev, "pll");
	if (IS_ERR(gpu->clk_pll)) {
		err = PTR_ERR(gpu->clk_pll);
		goto out;
	}

	err = platform_get_irq(pdev, 0);
	if (err < 0)
		goto out;

	gpu->irq = err;

	err = platform_get_irq(pdev, 1);
	if (err < 0)
		goto out;

	gpu->irq_nostall = err;

	err = devm_request_irq(&pdev->dev, gpu->irq, gk20a_irq, 0, "stall",
			       gpu);
	if (err < 0)
		goto out;

	err = devm_request_irq(&pdev->dev, gpu->irq_nostall, gk20a_irq, 0,
			       "non-stall", gpu);
	if (err < 0)
		goto out;

	err = clk_prepare(gpu->clk_pll);
	if (err < 0)
		goto out;

	err = gk20a_init(gpu);
	if (err < 0)
		goto out;

	platform_set_drvdata(pdev, gpu);

out:
	dev_dbg(&pdev->dev, "< %s() = %d\n", __func__, err);
	return err;
}

static int tegra_gk20a_remove(struct platform_device *pdev)
{
	struct gk20a *gpu = platform_get_drvdata(pdev);
	int err = 0;

	dev_dbg(&pdev->dev, "> %s(pdev=%p)\n", __func__, pdev);

	clk_disable_unprepare(gpu->clk_pll);
	clk_disable_unprepare(gpu->clk);

	dev_dbg(&pdev->dev, "< %s() = %d\n", __func__, err);
	return err;
}

static const struct of_device_id tegra_gk20a_match[] = {
	{ .compatible = "nvidia,tegra124-gk20a" },
	{ }
};

static struct platform_driver tegra_gk20a_driver = {
	.driver = {
		.name = "tegra-gk20a",
		.of_match_table = tegra_gk20a_match,
	},
	.probe = tegra_gk20a_probe,
	.remove = tegra_gk20a_remove,
};
module_platform_driver(tegra_gk20a_driver);
