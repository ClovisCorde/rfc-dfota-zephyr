/*
 * Copyright (c) 2023 Kickmaker
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef ZEPHYR_INCLUDE_DELTA_DELTA_ALGORITHM_H_
#define ZEPHYR_INCLUDE_DELTA_DELTA_ALGORITHM_H_

struct delta_api_t;

/**
 * @brief backend API to define a delta algorithm.
 */
struct delta_backend_api_t{
	int (*patch)(struct delta_api_t *self_p);
};

#endif /* ZEPHYR_INCLUDE_DELTA_DELTA_ALGORITHM_H_ */
