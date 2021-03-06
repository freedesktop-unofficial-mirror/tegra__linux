/*
 * Copyright (C) 2013 Freescale Semiconductor, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#ifndef __DTS_IMX53_PINGRP_H
#define __DTS_IMX53_PINGRP_H

#include "imx53-pinfunc.h"

#define MX53_AUDMUX_PINGRP1 \
	MX53_PAD_KEY_COL0__AUDMUX_AUD5_TXC		0x80000000 \
	MX53_PAD_KEY_ROW0__AUDMUX_AUD5_TXD		0x80000000 \
	MX53_PAD_KEY_COL1__AUDMUX_AUD5_TXFS		0x80000000 \
	MX53_PAD_KEY_ROW1__AUDMUX_AUD5_RXD		0x80000000

#define MX53_AUDMUX_PINGRP2 \
	MX53_PAD_SD2_DATA3__AUDMUX_AUD4_TXC		0x80000000 \
	MX53_PAD_SD2_DATA2__AUDMUX_AUD4_TXD		0x80000000 \
	MX53_PAD_SD2_DATA1__AUDMUX_AUD4_TXFS		0x80000000 \
	MX53_PAD_SD2_DATA0__AUDMUX_AUD4_RXD		0x80000000

#define MX53_AUDMUX_PINGRP3 \
	MX53_PAD_CSI0_DAT4__AUDMUX_AUD3_TXC		0x80000000 \
	MX53_PAD_CSI0_DAT5__AUDMUX_AUD3_TXD		0x80000000 \
	MX53_PAD_CSI0_DAT6__AUDMUX_AUD3_TXFS		0x80000000 \
	MX53_PAD_CSI0_DAT7__AUDMUX_AUD3_RXD		0x80000000

#define MX53_CAN1_PINGRP1 \
	MX53_PAD_PATA_INTRQ__CAN1_TXCAN			0x80000000 \
	MX53_PAD_PATA_DIOR__CAN1_RXCAN			0x80000000

#define MX53_CAN1_PINGRP2 \
	MX53_PAD_KEY_COL2__CAN1_TXCAN			0x80000000 \
	MX53_PAD_KEY_ROW2__CAN1_RXCAN			0x80000000

#define MX53_CAN1_PINGRP3 \
	MX53_PAD_GPIO_7__CAN1_TXCAN			0x80000000 \
	MX53_PAD_GPIO_8__CAN1_RXCAN			0x80000000

#define MX53_CAN2_PINGRP1 \
	MX53_PAD_KEY_COL4__CAN2_TXCAN			0x80000000 \
	MX53_PAD_KEY_ROW4__CAN2_RXCAN			0x80000000


#define MX53_CSI_PINGRP1 \
	MX53_PAD_CSI0_DATA_EN__IPU_CSI0_DATA_EN		0x1d5 \
	MX53_PAD_CSI0_VSYNC__IPU_CSI0_VSYNC		0x1d5 \
	MX53_PAD_CSI0_MCLK__IPU_CSI0_HSYNC		0x1d5 \
	MX53_PAD_CSI0_PIXCLK__IPU_CSI0_PIXCLK		0x1d5 \
	MX53_PAD_CSI0_DAT19__IPU_CSI0_D_19		0x1d5 \
	MX53_PAD_CSI0_DAT18__IPU_CSI0_D_18		0x1d5 \
	MX53_PAD_CSI0_DAT17__IPU_CSI0_D_17		0x1d5 \
	MX53_PAD_CSI0_DAT16__IPU_CSI0_D_16		0x1d5 \
	MX53_PAD_CSI0_DAT15__IPU_CSI0_D_15		0x1d5 \
	MX53_PAD_CSI0_DAT14__IPU_CSI0_D_14		0x1d5 \
	MX53_PAD_CSI0_DAT13__IPU_CSI0_D_13		0x1d5 \
	MX53_PAD_CSI0_DAT12__IPU_CSI0_D_12		0x1d5 \
	MX53_PAD_CSI0_DAT11__IPU_CSI0_D_11		0x1d5 \
	MX53_PAD_CSI0_DAT10__IPU_CSI0_D_10		0x1d5 \
	MX53_PAD_CSI0_DAT9__IPU_CSI0_D_9		0x1d5 \
	MX53_PAD_CSI0_DAT8__IPU_CSI0_D_8		0x1d5 \
	MX53_PAD_CSI0_DAT7__IPU_CSI0_D_7		0x1d5 \
	MX53_PAD_CSI0_DAT6__IPU_CSI0_D_6		0x1d5 \
	MX53_PAD_CSI0_DAT5__IPU_CSI0_D_5		0x1d5 \
	MX53_PAD_CSI0_DAT4__IPU_CSI0_D_4		0x1d5 \
	MX53_PAD_CSI0_PIXCLK__IPU_CSI0_PIXCLK		0x1d5

#define MX53_CSI_PINGRP2 \
	MX53_PAD_CSI0_VSYNC__IPU_CSI0_VSYNC		0x1d5 \
	MX53_PAD_CSI0_MCLK__IPU_CSI0_HSYNC		0x1d5 \
	MX53_PAD_CSI0_PIXCLK__IPU_CSI0_PIXCLK		0x1d5 \
	MX53_PAD_CSI0_DAT19__IPU_CSI0_D_19		0x1d5 \
	MX53_PAD_CSI0_DAT18__IPU_CSI0_D_18		0x1d5 \
	MX53_PAD_CSI0_DAT17__IPU_CSI0_D_17		0x1d5 \
	MX53_PAD_CSI0_DAT16__IPU_CSI0_D_16		0x1d5 \
	MX53_PAD_CSI0_DAT15__IPU_CSI0_D_15		0x1d5 \
	MX53_PAD_CSI0_DAT14__IPU_CSI0_D_14		0x1d5 \
	MX53_PAD_CSI0_DAT13__IPU_CSI0_D_13		0x1d5 \
	MX53_PAD_CSI0_DAT12__IPU_CSI0_D_12		0x1d5

#define MX53_CSPI_PINGRP1 \
	MX53_PAD_SD1_DATA0__CSPI_MISO			0x1d5 \
	MX53_PAD_SD1_CMD__CSPI_MOSI			0x1d5 \
	MX53_PAD_SD1_CLK__CSPI_SCLK			0x1d5

#define MX53_CSPI_PINGRP2 \
	MX53_PAD_EIM_D22__CSPI_MISO			0x1d5 \
	MX53_PAD_EIM_D28__CSPI_MOSI			0x1d5 \
	MX53_PAD_EIM_D21__CSPI_SCLK			0x1d5

#define MX53_ECSPI1_PINGRP1 \
	MX53_PAD_EIM_D16__ECSPI1_SCLK			0x80000000 \
	MX53_PAD_EIM_D17__ECSPI1_MISO			0x80000000 \
	MX53_PAD_EIM_D18__ECSPI1_MOSI			0x80000000

#define MX53_ECSPI1_PINGRP2 \
	MX53_PAD_GPIO_19__ECSPI1_RDY			0x80000000 \
	MX53_PAD_EIM_EB2__ECSPI1_SS0			0x80000000 \
	MX53_PAD_EIM_D16__ECSPI1_SCLK			0x80000000 \
	MX53_PAD_EIM_D17__ECSPI1_MISO			0x80000000 \
	MX53_PAD_EIM_D18__ECSPI1_MOSI			0x80000000 \
	MX53_PAD_EIM_D19__ECSPI1_SS1			0x80000000

#define MX53_ECSPI2_PINGRP1 \
	MX53_PAD_EIM_OE__ECSPI2_MISO			0x80000000 \
	MX53_PAD_EIM_CS1__ECSPI2_MOSI			0x80000000 \
	MX53_PAD_EIM_CS0__ECSPI2_SCLK			0x80000000

#define MX53_ESDHC1_PINGRP1 \
	MX53_PAD_SD1_DATA0__ESDHC1_DAT0			0x1d5 \
	MX53_PAD_SD1_DATA1__ESDHC1_DAT1			0x1d5 \
	MX53_PAD_SD1_DATA2__ESDHC1_DAT2			0x1d5 \
	MX53_PAD_SD1_DATA3__ESDHC1_DAT3			0x1d5 \
	MX53_PAD_SD1_CMD__ESDHC1_CMD			0x1d5 \
	MX53_PAD_SD1_CLK__ESDHC1_CLK			0x1d5

#define MX53_ESDHC1_PINGRP2 \
	MX53_PAD_SD1_DATA0__ESDHC1_DAT0			0x1d5 \
	MX53_PAD_SD1_DATA1__ESDHC1_DAT1			0x1d5 \
	MX53_PAD_SD1_DATA2__ESDHC1_DAT2			0x1d5 \
	MX53_PAD_SD1_DATA3__ESDHC1_DAT3			0x1d5 \
	MX53_PAD_PATA_DATA8__ESDHC1_DAT4		0x1d5 \
	MX53_PAD_PATA_DATA9__ESDHC1_DAT5		0x1d5 \
	MX53_PAD_PATA_DATA10__ESDHC1_DAT6		0x1d5 \
	MX53_PAD_PATA_DATA11__ESDHC1_DAT7		0x1d5 \
	MX53_PAD_SD1_CMD__ESDHC1_CMD			0x1d5 \
	MX53_PAD_SD1_CLK__ESDHC1_CLK			0x1d5

#define MX53_ESDHC2_PINGRP1 \
	MX53_PAD_SD2_CMD__ESDHC2_CMD			0x1d5 \
	MX53_PAD_SD2_CLK__ESDHC2_CLK			0x1d5 \
	MX53_PAD_SD2_DATA0__ESDHC2_DAT0			0x1d5 \
	MX53_PAD_SD2_DATA1__ESDHC2_DAT1			0x1d5 \
	MX53_PAD_SD2_DATA2__ESDHC2_DAT2			0x1d5 \
	MX53_PAD_SD2_DATA3__ESDHC2_DAT3			0x1d5

#define MX53_ESDHC3_PINGRP1 \
	MX53_PAD_PATA_DATA8__ESDHC3_DAT0		0x1d5 \
	MX53_PAD_PATA_DATA9__ESDHC3_DAT1		0x1d5 \
	MX53_PAD_PATA_DATA10__ESDHC3_DAT2		0x1d5 \
	MX53_PAD_PATA_DATA11__ESDHC3_DAT3		0x1d5 \
	MX53_PAD_PATA_DATA0__ESDHC3_DAT4		0x1d5 \
	MX53_PAD_PATA_DATA1__ESDHC3_DAT5		0x1d5 \
	MX53_PAD_PATA_DATA2__ESDHC3_DAT6		0x1d5 \
	MX53_PAD_PATA_DATA3__ESDHC3_DAT7		0x1d5 \
	MX53_PAD_PATA_RESET_B__ESDHC3_CMD		0x1d5 \
	MX53_PAD_PATA_IORDY__ESDHC3_CLK			0x1d5

#define MX53_FEC_PINGRP1 \
	MX53_PAD_FEC_MDC__FEC_MDC			0x80000000 \
	MX53_PAD_FEC_MDIO__FEC_MDIO			0x80000000 \
	MX53_PAD_FEC_REF_CLK__FEC_TX_CLK		0x80000000 \
	MX53_PAD_FEC_RX_ER__FEC_RX_ER			0x80000000 \
	MX53_PAD_FEC_CRS_DV__FEC_RX_DV			0x80000000 \
	MX53_PAD_FEC_RXD1__FEC_RDATA_1			0x80000000 \
	MX53_PAD_FEC_RXD0__FEC_RDATA_0			0x80000000 \
	MX53_PAD_FEC_TX_EN__FEC_TX_EN			0x80000000 \
	MX53_PAD_FEC_TXD1__FEC_TDATA_1			0x80000000 \
	MX53_PAD_FEC_TXD0__FEC_TDATA_0			0x80000000

#define MX53_FEC_PINGRP2 \
	MX53_PAD_FEC_MDC__FEC_MDC			0x80000000 \
	MX53_PAD_FEC_MDIO__FEC_MDIO			0x80000000 \
	MX53_PAD_FEC_REF_CLK__FEC_TX_CLK		0x80000000 \
	MX53_PAD_FEC_RX_ER__FEC_RX_ER			0x80000000 \
	MX53_PAD_FEC_CRS_DV__FEC_RX_DV			0x80000000 \
	MX53_PAD_FEC_RXD1__FEC_RDATA_1			0x80000000 \
	MX53_PAD_FEC_RXD0__FEC_RDATA_0			0x80000000 \
	MX53_PAD_FEC_TX_EN__FEC_TX_EN			0x80000000 \
	MX53_PAD_FEC_TXD1__FEC_TDATA_1			0x80000000 \
	MX53_PAD_FEC_TXD0__FEC_TDATA_0			0x80000000 \
	MX53_PAD_KEY_ROW1__FEC_COL			0x80000000 \
	MX53_PAD_KEY_COL3__FEC_CRS			0x80000000 \
	MX53_PAD_KEY_COL2__FEC_RDATA_2			0x80000000 \
	MX53_PAD_KEY_COL0__FEC_RDATA_3			0x80000000 \
	MX53_PAD_KEY_COL1__FEC_RX_CLK			0x80000000 \
	MX53_PAD_KEY_ROW2__FEC_TDATA_2			0x80000000 \
	MX53_PAD_GPIO_19__FEC_TDATA_3			0x80000000 \
	MX53_PAD_KEY_ROW0__FEC_TX_ER			0x80000000

#define MX53_I2C1_PINGRP1 \
	MX53_PAD_CSI0_DAT8__I2C1_SDA			0xc0000000 \
	MX53_PAD_CSI0_DAT9__I2C1_SCL			0xc0000000

#define MX53_I2C1_PINGRP2 \
	MX53_PAD_EIM_D21__I2C1_SCL			0xc0000000 \
	MX53_PAD_EIM_D28__I2C1_SDA			0xc0000000

#define MX53_I2C2_PINGRP1 \
	MX53_PAD_KEY_ROW3__I2C2_SDA			0xc0000000 \
	MX53_PAD_KEY_COL3__I2C2_SCL			0xc0000000

#define MX53_I2C2_PINGRP2 \
	MX53_PAD_EIM_D16__I2C2_SDA			0xc0000000 \
	MX53_PAD_EIM_EB2__I2C2_SCL			0xc0000000

#define MX53_I2C3_PINGRP1 \
	MX53_PAD_GPIO_6__I2C3_SDA			0xc0000000 \
	MX53_PAD_GPIO_5__I2C3_SCL			0xc0000000

#define MX53_I2C3_PINGRP2 \
	MX53_PAD_GPIO_3__I2C3_SCL			0xc0000000 \
	MX53_PAD_GPIO_6__I2C3_SDA			0xc0000000

#define MX53_IPU_DISP0_PINGRP1 \
	MX53_PAD_DI0_DISP_CLK__IPU_DI0_DISP_CLK		0x5 \
	MX53_PAD_DI0_PIN15__IPU_DI0_PIN15		0x5 \
	MX53_PAD_DI0_PIN2__IPU_DI0_PIN2			0x5 \
	MX53_PAD_DI0_PIN3__IPU_DI0_PIN3			0x5 \
	MX53_PAD_DISP0_DAT0__IPU_DISP0_DAT_0		0x5 \
	MX53_PAD_DISP0_DAT1__IPU_DISP0_DAT_1		0x5 \
	MX53_PAD_DISP0_DAT2__IPU_DISP0_DAT_2		0x5 \
	MX53_PAD_DISP0_DAT3__IPU_DISP0_DAT_3		0x5 \
	MX53_PAD_DISP0_DAT4__IPU_DISP0_DAT_4		0x5 \
	MX53_PAD_DISP0_DAT5__IPU_DISP0_DAT_5		0x5 \
	MX53_PAD_DISP0_DAT6__IPU_DISP0_DAT_6		0x5 \
	MX53_PAD_DISP0_DAT7__IPU_DISP0_DAT_7		0x5 \
	MX53_PAD_DISP0_DAT8__IPU_DISP0_DAT_8		0x5 \
	MX53_PAD_DISP0_DAT9__IPU_DISP0_DAT_9		0x5 \
	MX53_PAD_DISP0_DAT10__IPU_DISP0_DAT_10		0x5 \
	MX53_PAD_DISP0_DAT11__IPU_DISP0_DAT_11		0x5 \
	MX53_PAD_DISP0_DAT12__IPU_DISP0_DAT_12		0x5 \
	MX53_PAD_DISP0_DAT13__IPU_DISP0_DAT_13		0x5 \
	MX53_PAD_DISP0_DAT14__IPU_DISP0_DAT_14		0x5 \
	MX53_PAD_DISP0_DAT15__IPU_DISP0_DAT_15		0x5 \
	MX53_PAD_DISP0_DAT16__IPU_DISP0_DAT_16		0x5 \
	MX53_PAD_DISP0_DAT17__IPU_DISP0_DAT_17		0x5 \
	MX53_PAD_DISP0_DAT18__IPU_DISP0_DAT_18		0x5 \
	MX53_PAD_DISP0_DAT19__IPU_DISP0_DAT_19		0x5 \
	MX53_PAD_DISP0_DAT20__IPU_DISP0_DAT_20		0x5 \
	MX53_PAD_DISP0_DAT21__IPU_DISP0_DAT_21		0x5 \
	MX53_PAD_DISP0_DAT22__IPU_DISP0_DAT_22		0x5 \
	MX53_PAD_DISP0_DAT23__IPU_DISP0_DAT_23		0x5

#define MX53_IPU_DISP1_PINGRP1 \
	MX53_PAD_EIM_DA9__IPU_DISP1_DAT_0		0x5 \
	MX53_PAD_EIM_DA8__IPU_DISP1_DAT_1		0x5 \
	MX53_PAD_EIM_DA7__IPU_DISP1_DAT_2		0x5 \
	MX53_PAD_EIM_DA6__IPU_DISP1_DAT_3		0x5 \
	MX53_PAD_EIM_DA5__IPU_DISP1_DAT_4		0x5 \
	MX53_PAD_EIM_DA4__IPU_DISP1_DAT_5		0x5 \
	MX53_PAD_EIM_DA3__IPU_DISP1_DAT_6		0x5 \
	MX53_PAD_EIM_DA2__IPU_DISP1_DAT_7		0x5 \
	MX53_PAD_EIM_DA1__IPU_DISP1_DAT_8		0x5 \
	MX53_PAD_EIM_DA0__IPU_DISP1_DAT_9		0x5 \
	MX53_PAD_EIM_EB1__IPU_DISP1_DAT_10		0x5 \
	MX53_PAD_EIM_EB0__IPU_DISP1_DAT_11		0x5 \
	MX53_PAD_EIM_A17__IPU_DISP1_DAT_12		0x5 \
	MX53_PAD_EIM_A18__IPU_DISP1_DAT_13		0x5 \
	MX53_PAD_EIM_A19__IPU_DISP1_DAT_14		0x5 \
	MX53_PAD_EIM_A20__IPU_DISP1_DAT_15		0x5 \
	MX53_PAD_EIM_A21__IPU_DISP1_DAT_16		0x5 \
	MX53_PAD_EIM_A22__IPU_DISP1_DAT_17		0x5 \
	MX53_PAD_EIM_A23__IPU_DISP1_DAT_18		0x5 \
	MX53_PAD_EIM_A24__IPU_DISP1_DAT_19		0x5 \
	MX53_PAD_EIM_D31__IPU_DISP1_DAT_20		0x5 \
	MX53_PAD_EIM_D30__IPU_DISP1_DAT_21		0x5 \
	MX53_PAD_EIM_D26__IPU_DISP1_DAT_22		0x5 \
	MX53_PAD_EIM_D27__IPU_DISP1_DAT_23		0x5 \
	MX53_PAD_EIM_A16__IPU_DI1_DISP_CLK		0x5 \
	MX53_PAD_EIM_DA13__IPU_DI1_D0_CS		0x5 \
	MX53_PAD_EIM_DA14__IPU_DI1_D1_CS		0x5 \
	MX53_PAD_EIM_DA15__IPU_DI1_PIN1			0x5 \
	MX53_PAD_EIM_DA11__IPU_DI1_PIN2			0x5 \
	MX53_PAD_EIM_DA12__IPU_DI1_PIN3			0x5 \
	MX53_PAD_EIM_A25__IPU_DI1_PIN12			0x5 \
	MX53_PAD_EIM_DA10__IPU_DI1_PIN15		0x5

#define MX53_IPU_DISP2_PINGRP1 \
	MX53_PAD_LVDS0_TX0_P__LDB_LVDS0_TX0		0x80000000 \
	MX53_PAD_LVDS0_TX1_P__LDB_LVDS0_TX1		0x80000000 \
	MX53_PAD_LVDS0_TX2_P__LDB_LVDS0_TX2		0x80000000 \
	MX53_PAD_LVDS0_TX3_P__LDB_LVDS0_TX3		0x80000000 \
	MX53_PAD_LVDS0_CLK_P__LDB_LVDS0_CLK		0x80000000 \
	MX53_PAD_LVDS1_TX0_P__LDB_LVDS1_TX0		0x80000000 \
	MX53_PAD_LVDS1_TX1_P__LDB_LVDS1_TX1		0x80000000 \
	MX53_PAD_LVDS1_TX2_P__LDB_LVDS1_TX2		0x80000000 \
	MX53_PAD_LVDS1_TX3_P__LDB_LVDS1_TX3		0x80000000 \
	MX53_PAD_LVDS1_CLK_P__LDB_LVDS1_CLK		0x80000000

#define MX53_NAND_PINGRP1 \
	MX53_PAD_NANDF_WE_B__EMI_NANDF_WE_B		0x4 \
	MX53_PAD_NANDF_RE_B__EMI_NANDF_RE_B		0x4 \
	MX53_PAD_NANDF_CLE__EMI_NANDF_CLE		0x4 \
	MX53_PAD_NANDF_ALE__EMI_NANDF_ALE		0x4 \
	MX53_PAD_NANDF_WP_B__EMI_NANDF_WP_B		0xe0 \
	MX53_PAD_NANDF_RB0__EMI_NANDF_RB_0		0xe0 \
	MX53_PAD_NANDF_CS0__EMI_NANDF_CS_0		0x4 \
	MX53_PAD_PATA_DATA0__EMI_NANDF_D_0		0xa4 \
	MX53_PAD_PATA_DATA1__EMI_NANDF_D_1		0xa4 \
	MX53_PAD_PATA_DATA2__EMI_NANDF_D_2		0xa4 \
	MX53_PAD_PATA_DATA3__EMI_NANDF_D_3		0xa4 \
	MX53_PAD_PATA_DATA4__EMI_NANDF_D_4		0xa4 \
	MX53_PAD_PATA_DATA5__EMI_NANDF_D_5		0xa4 \
	MX53_PAD_PATA_DATA6__EMI_NANDF_D_6		0xa4 \
	MX53_PAD_PATA_DATA7__EMI_NANDF_D_7		0xa4

#define MX53_OWIRE_PINGRP1 \
	MX53_PAD_GPIO_18__OWIRE_LINE			0x80000000

#define MX53_PWM1_PINGRP1 \
	MX53_PAD_DISP0_DAT8__PWM1_PWMO			0x5

#define MX53_PWM2_PINGRP1 \
	MX53_PAD_GPIO_1__PWM2_PWMO			0x80000000

#define MX53_UART1_PINGRP1 \
	MX53_PAD_CSI0_DAT10__UART1_TXD_MUX		0x1e4 \
	MX53_PAD_CSI0_DAT11__UART1_RXD_MUX		0x1e4

#define MX53_UART1_PINGRP2 \
	MX53_PAD_PATA_DIOW__UART1_TXD_MUX		0x1e4 \
	MX53_PAD_PATA_DMACK__UART1_RXD_MUX		0x1e4

#define MX53_UART1_PINGRP3 \
	MX53_PAD_PATA_RESET_B__UART1_CTS		0x1c5 \
	MX53_PAD_PATA_IORDY__UART1_RTS			0x1c5

#define MX53_UART2_PINGRP1 \
	MX53_PAD_PATA_BUFFER_EN__UART2_RXD_MUX		0x1e4 \
	MX53_PAD_PATA_DMARQ__UART2_TXD_MUX		0x1e4

#define MX53_UART2_PINGRP2 \
	MX53_PAD_PATA_BUFFER_EN__UART2_RXD_MUX		0x1c5 \
	MX53_PAD_PATA_DMARQ__UART2_TXD_MUX		0x1c5 \
	MX53_PAD_PATA_DIOR__UART2_RTS			0x1c5 \
	MX53_PAD_PATA_INTRQ__UART2_CTS			0x1c5

#define MX53_UART3_PINGRP1 \
	MX53_PAD_PATA_CS_0__UART3_TXD_MUX		0x1e4 \
	MX53_PAD_PATA_CS_1__UART3_RXD_MUX		0x1e4 \
	MX53_PAD_PATA_DA_1__UART3_CTS			0x1e4 \
	MX53_PAD_PATA_DA_2__UART3_RTS			0x1e4

#define MX53_UART3_PINGRP2 \
	MX53_PAD_PATA_CS_0__UART3_TXD_MUX		0x1e4 \
	MX53_PAD_PATA_CS_1__UART3_RXD_MUX		0x1e4

#define MX53_UART4_PINGRP1 \
	MX53_PAD_KEY_COL0__UART4_TXD_MUX		0x1e4 \
	MX53_PAD_KEY_ROW0__UART4_RXD_MUX		0x1e4

#define MX53_UART5_PINGRP1 \
	MX53_PAD_KEY_COL1__UART5_TXD_MUX		0x1e4 \
	MX53_PAD_KEY_ROW1__UART5_RXD_MUX		0x1e4

#endif /* __DTS_IMX53_PINGRP_H */
