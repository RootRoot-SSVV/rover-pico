#include "system_manager.h"
#include "bluetooth.h"
#include "demo_module.h"

static uint8_t connected_modules[16];
static uint8_t number_of_modules;
static uint8_t selected_module;

// initiales system states
void system_manager_init() {
    selected_module = 16;
    number_of_modules = 0;
}

void module_setup(int id) {
    switch (id) {
    case 1:
        init_demo_module();
        break;
    case 2:
        // module with id 2
        break;
    default:
        break;
    }
}

void bus_init() {
    // 0 - 11       -> data for module
    // 12, 13, 14   -> module selector
    // 15           -> module is active

    for(int i = 0; i <= 11; i++) {
        gpio_init(i);
        gpio_set_dir(i, GPIO_OUT);
    }

    for (int i = 12; i < 15; i++){
        gpio_init(i);
        gpio_set_dir(i, GPIO_OUT);
    }
    
    gpio_init(15);
    gpio_set_dir(15, GPIO_IN);

}

void set_module_id(uint8_t id) {
    selected_module = id;
    gpio_put(12, id & 1);
    gpio_put(13, id & 2);
    gpio_put(14, id & 4);

}

void scan_for_modules() {
    number_of_modules = 0;

    for (int i = 0; i < 8; i++) {
        gpio_put(12, i & 1);
        gpio_put(13, i & 2);
        gpio_put(14, i & 4);

        if(gpio_get(15)) {
            number_of_modules++;
            connected_modules[number_of_modules-1] = i;
        }
    }
    
}

uint8_t* get_connected_modules() {
    // Test
    connected_modules[0] = 1;
    number_of_modules = 1;
    // ...

    return connected_modules;
}

uint8_t get_number_of_modules() {
    return number_of_modules;
}

void select_module(uint8_t mode) {
    selected_module = mode;

    gpio_put(12, mode & 1);
    gpio_put(13, mode & 2);
    gpio_put(14, mode & 4);

    // Change GPIOs 0, 1, 2 on bus to match 'mode' in binary...
}

void motor_init() {
    gpio_init(28);
    gpio_set_dir(28, GPIO_OUT);
    gpio_init(27);
    gpio_set_dir(27, GPIO_OUT);
    gpio_init(26);
    gpio_set_dir(26, GPIO_OUT);     // LPWM
    gpio_init(22);
    gpio_set_dir(22, GPIO_OUT);     // RPWM

    gpio_init(21);
    gpio_set_dir(21, GPIO_OUT);
    gpio_init(20);
    gpio_set_dir(20, GPIO_OUT);
    gpio_init(19);
    gpio_set_dir(19, GPIO_OUT);     // LPWM
    gpio_init(18);
    gpio_set_dir(18, GPIO_OUT);     // RPWM

    gpio_put(28, 1);
    gpio_put(27, 1);
    gpio_put(21, 1);
    gpio_put(20, 1);
}

void motor_driver(uint8_t motorInt) {
    uint8_t forward = motorInt & 1;
    uint8_t backward = motorInt & 2;
    uint8_t left = motorInt & 4;
    uint8_t right = motorInt & 8;

    if(forward && right) {
        gpio_put(22, 0);
        gpio_put(26, 1);

        gpio_put(19, 0);
        gpio_put(18, 0);
    } else if (forward && left) {
        gpio_put(26, 0);
        gpio_put(22, 0);

        gpio_put(18, 0);
        gpio_put(19, 1);
    } else if (backward && right) {
        gpio_put(26, 0);
        gpio_put(22, 1);

        gpio_put(19, 0);
        gpio_put(18, 0);
    } else if (backward && left) {
        gpio_put(26, 0);
        gpio_put(22, 0);

        gpio_put(19, 0);
        gpio_put(18, 1);
    } else if (forward) {
        gpio_put(22, 0);
        gpio_put(26, 1);

        gpio_put(18, 0);
        gpio_put(19, 1);
    } else if (backward) {
        gpio_put(26, 0);
        gpio_put(22, 1);

        gpio_put(19, 0);
        gpio_put(18, 1);
    } else if (right) {
        gpio_put(22, 0);
        gpio_put(26, 1);

        gpio_put(19, 0);
        gpio_put(18, 1);
    } else if (left) {
        gpio_put(26, 0);
        gpio_put(22, 1);

        gpio_put(18, 0);
        gpio_put(19, 1);
    } else {
        gpio_put(26, 0);
        gpio_put(22, 0);

        gpio_put(19, 0);
        gpio_put(18, 0);
    }
}

//////////////////////////////////////////////
// Tests

//////////////////////////////////////////////