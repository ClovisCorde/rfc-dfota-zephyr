/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DT_BINDINGS_PINCTRL_IMX8QXP_PINCTRL_H_
#define ZEPHYR_INCLUDE_DT_BINDINGS_PINCTRL_IMX8QXP_PINCTRL_H_

/* values for pad field */
#define SC_P_UART2_TX 113
#define SC_P_UART2_RX 114

/* mux values */
#define IMX8QXP_DMA_LPUART2_RX_UART2_RX 0 /* UART2_RX ---> DMA_LPUART2_RX */
#define IMX8QXP_DMA_LPUART2_TX_UART2_TX 0 /* DMA_LPUART2_TX ---> UART2_TX */

#endif /* ZEPHYR_INCLUDE_DT_BINDINGS_PINCTRL_IMX8QXP_PINCTRL_H_ */
