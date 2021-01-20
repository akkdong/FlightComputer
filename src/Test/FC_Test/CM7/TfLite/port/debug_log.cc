// debug_log.cc
//

#include <stdio.h>
#include "usart.h"

#if _UNDEF_

#ifdef __GNUC__
extern "C" int __io_putchar(int ch)
{
  HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY);

  return ch;
}
#else
extern "C" int fputc(int ch, FILE* f)
{
  HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY);

  return ch;
}
#endif /* __GNUC__ */

#endif


extern "C" void DebugLog(const char* s)
{
	fprintf(stderr, "%s", s);
}

