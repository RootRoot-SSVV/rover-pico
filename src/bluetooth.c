#include "bluetooth.h"


static uint8_t input_buffer[64];
static uint8_t output_buffer[64];

static uint8_t mode;

void bluetooth_init() {
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    uart_set_fifo_enabled(UART_ID, true);
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;
    
    irq_set_exclusive_handler(UART_IRQ, bluetooth_recieve);
    irq_set_enabled(UART_IRQ, true);
    uart_set_irq_enables(UART_ID, true, false);

    for(int i = 0; i < 32; i++) {
        while (!uart_is_writable(UART_ID));
        uart_putc(UART_ID, 0);
    }
    
}

void response() {
    motor_driver(input_buffer[1]);
    switch (input_buffer[0]) {
    case 0:
        // neutral
        break;
    case 1:
        // ultrasonic_module
        ultrasonic_module_reaction();
        bluetooth_send();
        break;
    case 2:
        // ultrasonic_module
        ultrasonic_module_reaction();
        bluetooth_send();
        break;
    case 3:
        // ultrasonic_module
        ultrasonic_module_reaction();
        bluetooth_send();
        break;
    case 4:
        // ultrasonic_module
        ultrasonic_module_reaction();
        bluetooth_send();
        break;
    case 5:
        // ultrasonic_module
        ultrasonic_module_reaction();
        bluetooth_send();
        break;
    case 6:
        // ultrasonic_module
        ultrasonic_module_reaction();
        bluetooth_send();
        break;
    case 7:
        // demo_module
        demo_module_reaction();
        break;
    case 18:
        // rescan
        send_return_message();
        break;
    case 19:
        // Change module to
        set_module_id(input_buffer[2]);
        module_setup(input_buffer[2]);
        break;
    default:
        break;
    }
}

void bluetooth_recieve() {
    uart_set_irq_enables(UART_ID, false, false);

    // uart_read_blocking(UART_ID, input_buffer, 64);

    while(!uart_is_readable(UART_ID));
    while(uart_getc(UART_ID) != 254);

    for (int i = 0; i < 64; i++) {
        while (!uart_is_readable(UART_ID)) {}
        input_buffer[i] = uart_getc(UART_ID);
    }

    response();

    uart_set_irq_enables(UART_ID, true, false);
}

void bluetooth_send() {
    while (!uart_is_writable(UART_ID));
    uart_putc(UART_ID, 254);
    for(int i = 0; i < 61; i++) {
        while (!uart_is_writable(UART_ID));
        uart_putc(UART_ID, output_buffer[i]);
    }

    // uart_write_blocking(UART_ID, output_buffer, 64);
}

uint8_t* get_input_buffer() {
    return input_buffer;
}

uint8_t* get_output_buffer() {
    return output_buffer;
}

void send_return_message() {
    output_buffer[0] = 17;
    uint8_t *connected_modules = get_connected_modules();
    output_buffer[1] = get_number_of_modules();

    for(int i = 0; i<output_buffer[1]; i++) {
        output_buffer[2 + i] = connected_modules[i];
    }
    bluetooth_send();
}


//////////////////////////////////////////////
// Tests

void error_signal() {
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);
    gpio_put(25, true);
}

///////////////////////////////////////////////