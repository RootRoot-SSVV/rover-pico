#include "bluetooth.h"
#include "system_manager.h"

static uint8_t* input_buffer;
static uint8_t* output_buffer;

static uint8_t mode;

void bluetooth_init() {
    input_buffer = (uint8_t *)malloc(sizeof(int) * 64);
    output_buffer = (uint8_t *)malloc(sizeof(int) * 64);

    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    uart_set_fifo_enabled(UART_ID, true);
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;
    
    irq_set_exclusive_handler(UART_IRQ, bluetooth_recieve);
    irq_set_enabled(UART_IRQ, true);
    uart_set_irq_enables(UART_ID, true, false);
}

void response() {
    switch (input_buffer[0]) {
    case 16:
        // No return
        break;
    case 17:
        // Rescan
        test_rescan_return();
        break;
    case 18:
        // Disconnect
        break;
    case 19:
        // Change module to
        break;
    default:
        error_signal();
        break;
    }
    test_set_leds();
}

void bluetooth_recieve() {
    uart_set_irq_enables(UART_ID, false, false);


    uart_read_blocking(UART_ID, input_buffer, 64);

    response();

    for (int i = 0; i < 64; i++){
        
    }
    
    // hw_clear_bits(&uart_get_hw(UART_ID)->rsr, UART_UARTRSR_BITS);
    uart_set_irq_enables(UART_ID, true, false);
}

void bluetooth_send() {
    //uart_putc_raw()
    //uart_putc()
    uart_write_blocking(UART_ID, output_buffer, 64);
}

uint8_t* get_input_buffer() {
    return input_buffer;
}

//////////////////////////////////////////////
// Tests
void test_rescan_return() {
    test__choose_test();
}

void test_select_module(int mode) {
    gpio_put(0, mode & 1);
    mode >>= 1;
    gpio_put(1, mode & 1);
    mode >>= 1;
    gpio_put(2, mode & 1);
    mode >>= 1;
}

void error_signal() {
    gpio_put(25, true);
}

///////////////////////////////////////////////