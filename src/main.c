#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "bluetooth.h"
#include "system_manager.h"

int main() {
    stdio_init_all();

    bluetooth_init();
    system_manager_init();
    bus_init();
    motor_init();

    while (1) {
        tight_loop_contents();
    }
}
