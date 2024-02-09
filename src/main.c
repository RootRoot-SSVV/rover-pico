#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "bluetooth.h"
#include "system_manager.h"

int main() {
    stdio_init_all();
    gpio_init(25);
    gpio_put(25, 1);

    bluetooth_init();
    bus_init();
    motor_init();
    
    

    while (1) {
        tight_loop_contents();
    }
}
