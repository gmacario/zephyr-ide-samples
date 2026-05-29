/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/logging/log_ctrl.h>

// /* In all files comprising the module but one */
// LOG_MODULE_DECLARE(foo, CONFIG_FOO_LOG_LEVEL);

// LOG_MODULE_REGISTER(foo, CONFIG_FOO_LOG_LEVEL);
LOG_MODULE_REGISTER(main);

static inline void foo(void)
{
    //  LOG_MODULE_DECLARE(foo, CONFIG_FOO_LOG_LEVEL);

     LOG_INF("foo");
}

int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);

#ifdef CONFIG_CONSOLE
	printf("DEBUG: CONFIG_CONSOLE=%d\n", CONFIG_CONSOLE);
#endif
#ifdef CONFIG_UART_CONSOLE
	printf("DEBUG: CONFIG_UART_CONSOLE=%d\n", CONFIG_UART_CONSOLE);
#endif
#ifdef CONFIG_LOG
	printf("DEBUG: CONFIG_LOG=%d\n", CONFIG_LOG);
#endif
#ifdef CONFIG_LOG_PRINTK
	printf("DEBUG: CONFIG_LOG_PRINTK=%d\n", CONFIG_LOG_PRINTK);
#endif

	printk("This is a message from printk\n");

	LOG_INIT();
	/* If multithreading is enabled provide thread id to the logging. */
	log_thread_set(k_current_get());

	foo();

	int count = 1000;
	const k_timeout_t delay_ms = K_MSEC(1000);		// 1 second

	while (count > 0) {
		// printf("DEBUG: count=%d\n", count);
		LOG_INF("count=%d", count);
		k_sleep(delay_ms);
		count--;
	}

	return 0;
}
