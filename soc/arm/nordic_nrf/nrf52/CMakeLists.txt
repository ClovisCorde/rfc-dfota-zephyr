# SPDX-License-Identifier: Apache-2.0

zephyr_library()

zephyr_library_sources(
  soc.c
  )

zephyr_library_include_directories(
  ${ZEPHYR_BASE}/kernel/include
  ${ZEPHYR_BASE}/arch/arm/include
  )

if(CONFIG_SOC_NRF52832_ALLOW_SPIM_DESPITE_PAN_58 AND CONFIG_SPI_NRFX_SPIM)
  message(WARNING "Both SOC_NRF52832_ALLOW_SPIM_DESPITE_PAN_58 and an NRF SPIM driver are enabled, therefore PAN 58 will apply if RXD.MAXCNT == 1 and TXD.MAXCNT <= 1")
endif()

if(CONFIG_SOC_NRF52832)
  if(NOT CONFIG_NRF52_ANOMALY_109_WORKAROUND)
    if (CONFIG_NRFX_SPIS OR CONFIG_NRFX_SPIM OR CONFIG_NRFX_TWIM OR CONFIG_NRFX_PWM)
      message(WARNING "NRF52_ANOMALY_109_WORKAROUND disabled with SPIS, SPIM, TWIM or PWM enabled. This will occasionally cause the first byte transmitted to be incorrect")
    endif()
  endif()
endif()

set(SOC_LINKER_SCRIPT ${ZEPHYR_BASE}/include/zephyr/arch/arm/cortex_m/scripts/linker.ld CACHE INTERNAL "")
