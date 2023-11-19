#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "bluetooth.h"
#include "system_manager.h"

int main() {
    stdio_init_all();

    bluetooth_init();
    bus_init();

    int a = 7;
    int b = 15;

    for(int i = 0; i < 3; i++, a >>= 1) {
        gpio_put(i, 1);
        sleep_ms(200);
    }

    for(int i = 3; i < 7; i++, b >>= 1) {
        gpio_put(i, 1);
        sleep_ms(200);
    }

    while (1) {
        tight_loop_contents();
    }
}
