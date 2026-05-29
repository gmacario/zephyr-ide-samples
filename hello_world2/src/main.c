/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <inttypes.h>
#include <stdio.h>
#include <zephyr/drivers/led.h>
#include <zephyr/input/input.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/logging/log_ctrl.h>

// /* In all files comprising the module but one */
// LOG_MODULE_DECLARE(foo, CONFIG_FOO_LOG_LEVEL);

// LOG_MODULE_REGISTER(foo, CONFIG_FOO_LOG_LEVEL);
LOG_MODULE_REGISTER(main);

#define LED0_NODE DT_ALIAS(led0)

// #if DT_NODE_HAS_STATUS_OKAY(DT_PARENT(LED0_NODE))
// static const struct led_dt_spec led0 = LED_DT_SPEC_GET(LED0_NODE);
// #else
// static const struct led_dt_spec led0;
// #endif

static inline void foo(void)
{
    //  LOG_MODULE_DECLARE(foo, CONFIG_FOO_LOG_LEVEL);

     LOG_INF("foo");
}

// See https://github.com/zephyrproject-rtos/zephyr/tree/main/samples/basic/button
static void button_input_cb(struct input_event *evt, void *user_data)
{
	if (evt->sync == 0) {
		return;
	}

	printk("Button %d %s at %" PRIu32 "\n",
	       evt->code,
	       evt->value ? "pressed" : "released",
	       k_cycle_get_32());

	// if (led0.dev != NULL) {
	// 	led_set_brightness_dt(&led0, evt->value ? 100 : 0);
	// }
}

INPUT_CALLBACK_DEFINE(NULL, button_input_cb, NULL);

int main(void)
{
	printf("DEBUG: CONFIG_BOARD_TARGET=%s\n", CONFIG_BOARD_TARGET);

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
#ifdef CONFIG_GPIO
	printf("DEBUG: CONFIG_GPIO=%d\n", CONFIG_GPIO);
#endif
#ifdef CONFIG_INPUT
	printf("DEBUG: CONFIG_INPUT=%d\n", CONFIG_INPUT);
#endif
#ifdef CONFIG_LED
	printf("DEBUG: CONFIG_LED=%d\n", CONFIG_LED);
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

// EOF
