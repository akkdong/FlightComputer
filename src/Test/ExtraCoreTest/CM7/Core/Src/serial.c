/*
 * serial.c
 *
 *  Created on: 2021. 12. 25.
 *      Author: akkdong
 */


#include "main.h"
#include "serial.h"
#include "lwrb/lwrb.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


static UART_HandleTypeDef* uartHandle = 0;

static uint8_t 	serial_rxbuf[256];
static uint8_t 	serial_txbuf[256];

static char 	printf_buf[128];

static lwrb_t 	rb_rx;
static lwrb_t 	rb_tx;

static volatile uint8_t tx_status = 0; // 1: busy
static uint8_t rx_char;

//
//
//

static void serial_receive()
{
#if 0
	void* rx_buf = lwrb_get_linear_block_write_address(&rb_rx);
	HAL_UART_Receive_IT(uartHandle, (uint8_t *)&rx_buf, 1);
#else
	HAL_UART_Receive_IT(uartHandle, &rx_char, 1);
#endif
}


//
//
//

void serial_init(UART_HandleTypeDef* uart)
{
	uartHandle = uart;

	lwrb_init(&rb_rx, serial_rxbuf, sizeof(serial_rxbuf));
	lwrb_init(&rb_tx, serial_txbuf, sizeof(serial_txbuf));

	serial_receive();
}

int serial_available()
{
	return lwrb_get_full(&rb_rx);
}

int serial_read()
{
	uint8_t c;
	if (lwrb_read(&rb_rx, &c, 1) == 0)
		return -1;

	return c;
}

int serial_write(uint8_t ch)
{
	int sent = lwrb_write(&rb_tx, &ch, 1);
	if (sent > 0)
		serial_flush();

	return sent;
}


int serial_print(const char* str)
{
	int sent = lwrb_write(&rb_tx, str, strlen(str));
	if (sent > 0)
		serial_flush();

	return sent;
}

int serial_println(const char* str)
{
	return serial_print(str) + serial_print("\r\n");
}

int serial_printf(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vsprintf(printf_buf, fmt, args);
	va_end(args);

	return serial_print(printf_buf);
}

void serial_flush()
{
	if (lwrb_get_full(&rb_tx) > 0 && tx_status == 0)
	{
		uint8_t c;
		lwrb_read(&rb_tx, &c, 1);

		HAL_UART_Transmit_IT(uartHandle, &c, 1);
		tx_status = 1;
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
#if 0
	lwrb_advance(&rb_rx, 1);
#else
	lwrb_write(&rb_rx, &rx_char, 1);
#endif
	serial_receive();

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	// tx complete
	tx_status = 0;

	// flush
	serial_flush();
}
