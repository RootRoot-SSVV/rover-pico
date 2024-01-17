#include "ultrasonic_module.h"

//component    gpio
//TRIG         0
//ECHO         1

#define TRIG 0
#define ECHO 1

uint8_t* output = get_output_buffer();

void init_ultrasonic_module(){
    gpio_set_dir(TRIG, GPIO_OUT);
    gpio_set_dir(ECHO, GPIO_IN);
}

double get_distance(){
    gpio_put(TRIG, 1);
    sleep_us(10);
    gpio_put(TRIG, 0);

    while(gpio_get(ECHO) == 0);
    uint64_t start = time_us_64();
    while(gpio_get(ECHO) == 1);
    uint64_t end = time_us_64();

    uint64_t duration = end - start;
    float distance = duration * 0.034 / 2;

    return (double)distance;
}

void write_double_to_output(double value) {
    memcpy(output, &value, sizeof(double));
}

void ultrasonic_module_reaction() {
    // [mode][id][motor][pulse]
    //    0    1    2      3

    uint8_t *message = get_input_buffer();

    if (message[3] == true) {
        double distance = get_distance();
        write_double_to_output(distance);
    }

}

