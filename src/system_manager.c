#include "system_manager.h"
#include "bluetooth.h"

static uint8_t* connected_modules;
static uint8_t number_of_modules;
static uint8_t selected_module;

// initiales system states
void system_manager_init() {
    selected_module = 16;
    number_of_modules = 0;
    connected_modules = (uint8_t *)malloc(sizeof(uint8_t) * 16);        // Saves IDs of modules
}

void bus_init() {
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    for(int i = 0; i<7; i++) {
        gpio_init(i);
        gpio_set_dir(i, GPIO_OUT);
    }
}

uint8_t* get_connected_modules() {
    return connected_modules;
}

uint8_t get_number_of_modules() {
    return number_of_modules;
}

void select_module(uint8_t mode) {
    selected_module = mode;

    // Change GPIOs 0, 1, 2 on bus to match 'mode' in binary...
}

//////////////////////////////////////////////
// Tests

void test_set_leds() {
    uint8_t *input_buffer = get_input_buffer();
    uint8_t mode = input_buffer[0];
    uint8_t motors = input_buffer[1];
    
    selected_module = mode;

    for(int i = 0; i < 4; i++, motors >>= 1) {
        gpio_put(i, motors & 1);
    }

    for(int i = 4; i < 7; i++, mode >>= 1) {
        gpio_put(i, mode & 1);
    }
}

void test1() {
    number_of_modules = 1;
    connected_modules[0] = 1;
}

void test2() {
    number_of_modules = 2;
    connected_modules[0] = 0;
    connected_modules[0] = 1;
}

void test3() {
    number_of_modules = 0;
}

void test__choose_test() {
    switch (number_of_modules) {
    case 0:
        test1();
        break;
    case 1:
        test1();
        break;
    case 2:
        test1();
        break;
    default:
        break;
    }
}

//////////////////////////////////////////////