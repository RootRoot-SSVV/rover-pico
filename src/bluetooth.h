#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"

#define UART_ID uart0
#define BAUD_RATE 9600
#define UART_TX_PIN 16
#define UART_RX_PIN 17

void bluetooth_init();
void bluetooth_recieve();
void bluetooth_send();
uint8_t* get_input_buffer();
void send_return_message();

// Tests
void error_signal();

#endif // BLUETOOTH_H_