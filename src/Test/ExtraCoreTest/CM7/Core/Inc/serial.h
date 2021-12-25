/*
 * serial.h
 *
 *  Created on: 2021. 12. 25.
 *      Author: akkdong
 */

#ifndef INC_SERIAL_H_
#define INC_SERIAL_H_


void serial_init(UART_HandleTypeDef* uart);

int serial_available();
int serial_read();

int serial_write(uint8_t ch);

int serial_print(const char *);
int serial_println(const char *);
int serial_printf(const char* fmt, ...);

void serial_flush();

#endif /* INC_SERIAL_H_ */
