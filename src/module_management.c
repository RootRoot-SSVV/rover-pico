#include "module_management.h"
#include "pico/stdlib.h"

int get_required_num_of_data(int i) {
    int required_num_of_data[16] = {4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    return required_num_of_data[i];
}

void bus_init() {
    int i;
    
    for(i = 2; i <= 8; i++) {
        gpio_init(i);
        gpio_set_dir(i, GPIO_OUT);
    }
}

void select(int module) {
    int i;
    
    for(i = 6; i <= 8; i++) {
        gpio_put(i, (module & 1));
        module >>= 1;
    }
}