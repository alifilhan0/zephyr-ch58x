# Copyright 2023-2024 NXP
#
# SPDX-License-Identifier: Apache-2.0

zephyr_sources(soc.c mcxw71_platform_init.S)

zephyr_include_directories(.)

set(SOC_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld CACHE INTERNAL "")

zephyr_linker_sources_ifdef(CONFIG_BT RAM_SECTIONS sections.ld)
