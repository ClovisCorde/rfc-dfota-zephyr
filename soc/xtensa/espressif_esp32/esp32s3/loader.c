/*
 * Copyright (c) 2022 Espressif Systems (Shanghai) Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <soc.h>
#include <zephyr/storage/flash_map.h>
#include <esp_log.h>
#include <stdlib.h>

#include <esp32s3/rom/cache.h>
#include "esp32s3/dport_access.h"
#include "soc/cache_memory.h"
#include <soc/dport_reg.h>
#include "soc/extmem_reg.h"
#include <bootloader_flash_priv.h>

#ifdef CONFIG_BOOTLOADER_MCUBOOT

#define BOOT_LOG_INF(_fmt, ...) \
	ets_printf("[" CONFIG_SOC_SERIES "] [INF] " _fmt "\n\r", ##__VA_ARGS__)

#define HDR_ATTR __attribute__((section(".entry_addr"))) __attribute__((used))

extern uint32_t _image_irom_start, _image_irom_size, _image_irom_vaddr;
extern uint32_t _image_drom_start, _image_drom_size, _image_drom_vaddr;

void __start(void);

static HDR_ATTR void (*_entry_point)(void) = &__start;

static int map_rom_segments(void)
{
	int rc = 0;
	size_t _partition_offset = FIXED_PARTITION_OFFSET(slot0_partition);
	uint32_t _app_irom_start = _partition_offset + (uint32_t)&_image_irom_start;
	uint32_t _app_irom_size = (uint32_t)&_image_irom_size;
	uint32_t _app_irom_vaddr = (uint32_t)&_image_irom_vaddr;

	uint32_t _app_drom_start = _partition_offset + (uint32_t)&_image_drom_start;
	uint32_t _app_drom_size = (uint32_t)&_image_drom_size;
	uint32_t _app_drom_vaddr = (uint32_t)&_image_drom_vaddr;

	uint32_t autoload = Cache_Suspend_DCache();

	Cache_Invalidate_DCache_All();

	/* Clear the MMU entries that are already set up,
	 * so the new app only has the mappings it creates.
	 */
	for (size_t i = 0; i < FLASH_MMU_TABLE_SIZE; i++) {
		FLASH_MMU_TABLE[i] = MMU_TABLE_INVALID_VAL;
	}

	uint32_t drom_page_count = bootloader_cache_pages_to_map(_app_drom_size, _app_drom_vaddr);

	rc |= esp_rom_Cache_Dbus_MMU_Set(MMU_ACCESS_FLASH,
				_app_drom_vaddr & MMU_FLASH_MASK,
				_app_drom_start & MMU_FLASH_MASK,
				64, drom_page_count, 0);

	uint32_t irom_page_count = bootloader_cache_pages_to_map(_app_irom_size, _app_irom_vaddr);

	rc |= esp_rom_Cache_Ibus_MMU_Set(MMU_ACCESS_FLASH,
				_app_irom_vaddr & MMU_FLASH_MASK,
				_app_irom_start & MMU_FLASH_MASK,
				64, irom_page_count, 0);

	REG_CLR_BIT(EXTMEM_DCACHE_CTRL1_REG, EXTMEM_DCACHE_SHUT_CORE0_BUS);
	REG_CLR_BIT(EXTMEM_DCACHE_CTRL1_REG, EXTMEM_DCACHE_SHUT_CORE1_BUS);

	Cache_Resume_DCache(autoload);

	/* Show map segments continue using same log format as during MCUboot phase */
	BOOT_LOG_INF("DROM segment: paddr=%08Xh, vaddr=%08Xh, size=%05Xh (%6d) map",
		_app_drom_start, _app_drom_vaddr, _app_drom_size, _app_drom_size);
	BOOT_LOG_INF("IROM segment: paddr=%08Xh, vaddr=%08Xh, size=%05Xh (%6d) map\r\n",
		_app_irom_start, _app_irom_vaddr, _app_irom_size, _app_irom_size);
	esp_rom_uart_tx_wait_idle(0);

	return rc;
}
#endif /* CONFIG_BOOTLOADER_MCUBOOT */

void __start(void)
{
#ifdef CONFIG_BOOTLOADER_MCUBOOT
	int err = map_rom_segments();

	if (err != 0) {
		ets_printf("Failed to setup XIP, aborting\n");
		abort();
	}
#endif
	__esp_platform_start();
}
