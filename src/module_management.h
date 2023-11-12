#ifndef MODULE_MANAGEMENT_H
#define MODULE_MANAGEMENT_H

#include "hardware/uart.h"
#include "hardware/gpio.h"

int get_required_num_of_data(int i);

void bus_init();

void select(int module);

int rescan(uint8_t *modulesConnected);

void set_motor_pins(int code);

#endif // MODULE_MANAGEMENT_H
