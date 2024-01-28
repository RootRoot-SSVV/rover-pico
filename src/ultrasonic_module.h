#ifndef ULTRASONIC_MODULE_H_
#define ULTRASONIC_MODULE_H_

#define TRIG 0
#define ECHO 1

#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "bluetooth.h"

void init_ultrasonic_module();
double get_distance();
void write_double_to_output(double value);
void ultrasonic_module_reaction();

#endif // ULTRASONIC_MODULE_H_