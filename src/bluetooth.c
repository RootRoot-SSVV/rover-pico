#include "bluetooth.h"

static uint8_t* inputBuffer;
static uint8_t* outputBuffer;

static uint8_t mode;

void bluetooth_init() {
    inputBuffer = (uint8_t *)malloc(sizeof(int) * 64);
    outputBuffer = (uint8_t *)malloc(sizeof(int) * 64);

    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    uart_set_fifo_enabled(UART_ID, false);
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;
    
    irq_set_exclusive_handler(UART_IRQ, bluetooth_recieve);
    irq_set_enabled(UART_IRQ, true);
    uart_set_irq_enables(UART_ID, true, false);
}

void bluetooth_recieve() {
    int index = 0;

    // PONTENTIAL PROBLEM !!!!!
    uart_read_blocking(UART_ID, inputBuffer, 64);
    
}

void bluetooth_send() {
    //uart_putc_raw()
    //uart_write_blocking()
    //uart_putc()
}


//////////////////////////////////////////////
// Tests

void ledTest(){
    for(int i = 1; i<=4; i++) {
        if(inputBuffer[1] >> i) {
            gpio_put(i + 5, 1);
        } else {
            gpio_put(i + 5, 0);
        }
    }
}

///////////////////////////////////////////////