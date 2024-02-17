#include "ultrasonic_module.h"

//component    gpio
//TRIG         0
//ECHO         1


void init_ultrasonic_module() {
    gpio_set_dir(TRIG, GPIO_OUT);
    gpio_set_dir(ECHO, GPIO_IN);
}

int get_distance() {
    gpio_set_dir(TRIG, GPIO_OUT);
    gpio_set_dir(ECHO, GPIO_IN);

    gpio_put(TRIG, 0);
    sleep_us(2);
    gpio_put(TRIG, 1);
    sleep_us(10);
    gpio_put(TRIG, 0);

    while(gpio_get(ECHO) == 0);
    absolute_time_t start_time = get_absolute_time();

    while(gpio_get(ECHO) == 1);
    absolute_time_t end_time = get_absolute_time();

    int64_t duration = absolute_time_diff_us(start_time, end_time);
    int distance = (duration * 0.0343) / 2;


    if(distance > 20) error_signal();

    return distance;
}


void ultrasonic_module_reaction() {
    uint8_t *message = get_input_buffer();
    get_output_buffer()[0] = 1;

    if (message[3] == 1) {
        int distance = get_distance();
        if(distance < 20) get_output_buffer()[1] = 1;
        else get_output_buffer()[1] = 2;
    }
}

