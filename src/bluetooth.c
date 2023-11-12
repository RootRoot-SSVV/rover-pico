#include <stdio.h>
#include <stdlib.h>
#include "bluetooth.h"
#include "module_management.h"

/*
Communication rules:

data_buffer = [mode][movement][additional data][additional data]...

modes:
    0-15    =   module selection
    16      =   no special action
    17      =   rescan for modules
    18      =   disconnect
*/

uint8_t *data_buffer;

void bluetooth_init() {
    data_buffer = malloc(sizeof(uint8_t) * 64);

    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // Bluetooth interrupt init
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;
    irq_set_exclusive_handler(UART_IRQ, on_bluetooth_rx);
    irq_set_enabled(UART_IRQ, true);
    uart_set_irq_enables(UART_ID, true, false);

    uart_set_fifo_enabled(UART_ID, false);
}

void on_bluetooth_rx() {
    uint8_t data = 0;
    uint8_t received = 0;
    uint8_t mode = 0;

    while (uart_is_readable(UART_ID) && received < 64) {
        data = uart_getc(UART_ID);
        
        data_buffer[received] = data;
        
        received++;
    }

    set_motor_pins(data_buffer[1]);

    if(data_buffer[0] == 17) {
        select(data_buffer[0]);

        uint8_t n = rescan(data_buffer);
        for(int i = 0; i<n+2; i++) {
            if(uart_is_writable(UART_ID)) {
                uart_putc(UART_ID, data_buffer[i]);
            }
        }
    }

}

void bluetooth_interrupt_init() {
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;
    irq_set_exclusive_handler(UART_IRQ, on_bluetooth_rx);
    irq_set_enabled(UART_IRQ, true);
    uart_set_irq_enables(UART_ID, true, false);
}