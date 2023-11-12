#include "module_management.h"
#include "pico/stdlib.h"

#include <stdio.h>

int numOfModules;

int get_required_num_of_data(int i) {
    int required_num_of_data[18] = {4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    return required_num_of_data[i];
}

void bus_init() {
    int i;
    
    for(i = 2; i <= 8; i++) {
        gpio_init(i);
        gpio_set_dir(i, GPIO_OUT);
        gpio_put(i, false);
    }
}

void select(int module) {
    int i;
    
    for(i = 6; i <= 8; i++) {
        gpio_put(i, (module & 1));
        module >>= 1;
    }
}

int rescan(uint8_t *modulesConnected) {
    numOfModules = 2;

    modulesConnected[0] = 0;
    modulesConnected[1] = numOfModules;

    for(int i = 2; i<numOfModules+2; i++) {
        modulesConnected[i] = i-2;
    }

    return numOfModules;
}

void set_motor_pins(int code) {
    printf("%d\n", code);
    for(int i = 2; i<6; i++) {
        gpio_put(i, (code & 1));
        code >>= 1;
    }
}