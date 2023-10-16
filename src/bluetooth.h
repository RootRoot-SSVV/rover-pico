#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#define UART_ID uart0
#define BAUD_RATE 9600
#define UART_TX_PIN 16
#define UART_RX_PIN 17

void bluetooth_init();
void on_bluetooth_rx(uint8_t *data_buffer);
void bluetooth_interrupt_init();

#endif // BLUETOOTH_H_
