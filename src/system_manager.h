#ifndef SYSTEM_MANAGER_H_
#define SYSTEM_MANAGER_H_

#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

void system_manager_init();

void bus_init();

uint8_t* get_connected_modules();
uint8_t get_number_of_modules();

// TESTS
void test__choose_test();
void test_set_leds();

#endif // SYSTEM_MANAGER_H_