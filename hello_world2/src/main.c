/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>

int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);

	int count = 1000;
	const k_timeout_t delay_ms = K_MSEC(1000);		// 1 second

	while (count > 0) {
		printf("DEBUG: count=%d\n", count);
		k_sleep(delay_ms);
		count--;
	}

	return 0;
}
