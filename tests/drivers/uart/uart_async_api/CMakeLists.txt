# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(uart_high_level_api)

target_sources(app PRIVATE
    src/test_uart_async.c
    )
target_sources_ifdef(CONFIG_UART_WIDE_DATA app PRIVATE src/test_uart_wide.c)
