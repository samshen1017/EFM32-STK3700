#include "leuart.h"

void leuart_init(void)
{
	/* Enable peripheral clocks */
  CMU_ClockEnable(cmuClock_HFPER, true);
  /* Configure GPIO pins */
  CMU_ClockEnable(cmuClock_GPIO, true);
  /* To avoid false start, configure output as high */
  GPIO_PinModeSet(LEUART_TXPORT, LEUART_TXPIN, gpioModePushPull, 1);
  GPIO_PinModeSet(LEUART_RXPORT, LEUART_RXPIN, gpioModeInput, 0);

  LEUART_Init_TypeDef init = LEUART_INIT_DEFAULT;

  /* Enable CORE LE clock in order to access LE modules */
  CMU_ClockEnable(cmuClock_CORELE, true);

  /* Select LFXO for LEUARTs (and wait for it to stabilize) */
  CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFXO);
  CMU_ClockEnable(cmuClock_LEUART0, true);

  /* Do not prescale clock */
  CMU_ClockDivSet(cmuClock_LEUART0, cmuClkDiv_1);

  /* Configure LEUART */
  init.enable = leuartDisable;

  LEUART_Init(LEUART0, &init);

  /* Enable pins at default location */
  LEUART0->ROUTE = LEUART_ROUTE_RXPEN | LEUART_ROUTE_TXPEN | LEUART_LOCATION;

  /* Finally enable it */
  LEUART_Enable(LEUART0, leuartEnable);
}

void leuart_write(uint8_t *data, uint32_t size)
{
	for(int i = 0; i < size; i++)
	{
		LEUART_Tx(LEUART0, data[i]);
	}
}

void leuart_read(uint8_t *buf)
{
	static uint32_t rxIndex = 0;
	while(LEUART0->STATUS & LEUART_STATUS_RXDATAV){
		char data = LEUART_Rx(LEUART0);
		buf[rxIndex++] = data;
	}
}

