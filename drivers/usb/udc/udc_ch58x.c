
/* SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2024 Alif Ilhan <alifilhan0@gmail.com>
 * CH5xx USB Device controller driver, based on CherryUSB Stack https://github.com/cherry-embedded/CherryUSB.git
 * CH58x, CH32v has 8 EPs, while CH57x has 5 EP
 */

#define DT_DRV_COMPAT udc_wchusb

#include <soc.h>
#include <string.h>
#include <stdio.h>

#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/drivers/usb/udc.h>

#include "udc_common.h"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(wchusb, CONFIG_UDC_DRIVER_LOG_LEVEL);

static int udc_wchusb_lock(const struct device *dev)
{
	return udc_lock_internal(dev, K_FOREVER);
}

static int udc_wchusb_unlock(const struct device *dev)
{
	return udc_unlock_internal(dev);
}

static const struct udc_api udc_wchusb_api = {
	.lock = udc_wchusb_lock,
	.unlock = udc_wchusb_unlock,
	.init = udc_wchusb_init,
	.enable = udc_wchusb_enable,
	.disable = udc_wchusb_disable,
	.shutdown = udc_wchusb_shutdown,
	.set_address = udc_wchusb_set_address,
	.host_wakeup = udc_wchusb_host_wakeup,
	.ep_enable = udc_wchusb_ep_enable,
	.ep_disable = udc_wchusb_ep_disable,
	.ep_set_halt = udc_wchusb_ep_set_halt,
	.ep_clear_halt = udc_wchusb_ep_clear_halt,
	.ep_enqueue = udc_wchusb_ep_enqueue,
	.ep_dequeue = udc_wchusb_ep_dequeue,
};

#define DT_DRV_COMPAT raspberrypi_pico_usbd

#define UDC_RPI_PICO_DEVICE_DEFINE(n)							\
\
static void udc_wchusb_irq_enable_func_##n(const struct device *dev)		\
{										\
	IRQ_CONNECT(DT_INST_IRQN(n),						\
	DT_INST_IRQ(n, priority),					\
	wchusb_isr_handler,					\
	DEVICE_DT_INST_GET(n),					\
	0);								\
	\
	irq_enable(DT_INST_IRQN(n));						\
}										\
\
static void udc_wchusb_irq_disable_func_##n(const struct device *dev)		\
{										\
	irq_disable(DT_INST_IRQN(n));						\
}										\
\
static struct udc_ep_config ep_cfg_out[USB_NUM_ENDPOINTS];			\
static struct udc_ep_config ep_cfg_in[USB_NUM_ENDPOINTS];			\
\
static const struct wchusb_config wchusb_config_##n = {			\
	.base = (usb_hw_t *)DT_INST_REG_ADDR(n),				\
	.dpram = (usb_device_dpram_t *)USBCTRL_DPRAM_BASE,			\
	.mem_block = &wchusb_mb_##n,						\
	.num_of_eps = DT_INST_PROP(n, num_bidir_endpoints),			\
	.ep_cfg_in = ep_cfg_out,						\
	.ep_cfg_out = ep_cfg_in,						\
	.make_thread = udc_wchusb_make_thread_##n,				\
	.irq_enable_func = udc_wchusb_irq_enable_func_##n,			\
	.irq_disable_func = udc_wchusb_irq_disable_func_##n,			\
	.clk_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(n)),			\
	.clk_sys = (void *)DT_INST_PHA_BY_IDX(n, clocks, 0, clk_id),		\
};										\
\
static struct wchusb_data udc_priv_##n = {					\
};										\
\
static struct udc_data udc_data_##n = {						\
	.mutex = Z_MUTEX_INITIALIZER(udc_data_##n.mutex),			\
	.priv = &udc_priv_##n,							\
};										\
\
DEVICE_DT_INST_DEFINE(n, udc_wchusb_driver_preinit, NULL,			\
&udc_data_##n, &wchusb_config_##n,			\
POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,		\
&udc_wchusb_api);

DT_INST_FOREACH_STATUS_OKAY(UDC_RPI_PICO_DEVICE_DEFINE)
