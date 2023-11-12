#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "bluetooth.h"
#include "module_management.h"

int main() {
    stdio_init_all();
    
    bluetooth_init();
    bus_init();

    printf("Hello\n");

    while (1) {
        tight_loop_contents();
    }
}
