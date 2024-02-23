#include "matrix_module.h"

bool firstTurnOn = true;

// Function to send data to a single register
void max7219_send(uint8_t reg, uint8_t data) {
    gpio_put(CS, 0); // Start transmission
    spi_write_blocking(SPI_PORT, &reg, 1);
    spi_write_blocking(SPI_PORT, &data, 1);
    gpio_put(CS, 1); // End transmission
}

// Initialize MAX7219
void init_matrix_module() {
    // Initialize SPI
    spi_init(SPI_PORT, 1000000); // 1 MHz SPI clock
    gpio_set_function(DIN, GPIO_FUNC_SPI);
    gpio_set_function(CLK, GPIO_FUNC_SPI);
    gpio_init(CS);
    gpio_set_dir(CS, GPIO_OUT);

    // Initialize MAX7219
    max7219_send(0x0F, 0x00); // Display test register - turn off test mode
    max7219_send(0x09, 0x00); // Decode mode - use no decode
    max7219_send(0x0B, 0x07); // Scan limit - display all digits
    max7219_send(0x0C, 0x01); // Shutdown register - normal operation
    max7219_send(0x0A, 0x0F); // Intensity register - max intensity

    if(firstTurnOn) {
        firstTurnOn = false;
        display_pattern((uint8_t[]){0, 0, 0, 0, 0, 0, 0, 0});
    }
}

// Set a single LED in the matrix
void set_led(int x, int y, bool state) {
    uint8_t led_matrix[8] = {0};

    if (state) {
        led_matrix[y] |= (1 << x);
    } else {
        led_matrix[y] &= ~(1 << x);
    }

    max7219_send(y + 1, led_matrix[y]);
}

// Function to display a pattern or data on the matrix
void display_pattern(uint8_t *pattern) {
    for (int i = 0; i < 8; i++) {
        max7219_send(i + 1, pattern[i]);
    }
}

void matrix_module_reaction() {
    // [mode][id][display][pattern 1 - 8]
    //   0     1     2         3 - 11

    uint8_t *message = get_input_buffer();    
    display_pattern(&message[3]);
}

