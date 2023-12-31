# Copyright (c) 2021 Cypress Semiconductor Corporation (an Infineon company) or
# an affiliate of Cypress Semiconductor Corporation
# SPDX-License-Identifier: Apache-2.0

zephyr_sources(soc.c)
zephyr_include_directories(.)

# Add sections
zephyr_linker_sources_ifdef(CONFIG_SOC_FAMILY_INFINEON_CAT1 NOINIT noinit.ld)

# Add section for cm0p image ROM
zephyr_linker_sources_ifdef(CONFIG_SOC_FAMILY_INFINEON_CAT1A ROM_START SORT_KEY 0x0cm0p rom_cm0image.ld)

# Add section for cm0p image RAM
zephyr_linker_sources_ifdef(CONFIG_SOC_FAMILY_INFINEON_CAT1A RAM_SECTIONS SORT_KEY 0 ram_cm0image.ld)

zephyr_linker_sources_ifdef(CONFIG_SOC_FAMILY_INFINEON_CAT1A RAMFUNC_SECTION SORT_KEY 0 ram_func.ld)

zephyr_linker_sources_ifdef(CONFIG_SOC_FAMILY_INFINEON_CAT1 RODATA SORT_KEY 0 rom.ld)

set(SOC_LINKER_SCRIPT ${ZEPHYR_BASE}/include/zephyr/arch/arm/cortex_m/scripts/linker.ld CACHE INTERNAL "")
