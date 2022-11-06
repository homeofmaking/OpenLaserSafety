#include "main.h"
#include "config.h"
#include "tlc59116.h"
#include "adc.h"
#include "stdio.h"
#include "string.h"

void adc_panic() {
	while (1) {
		// Ensure master output is off
		HAL_GPIO_WritePin(MASTER_OUT_GPIO_Port, MASTER_OUT_Pin, GPIO_PIN_RESET);
		// Log error
		char buffer[100];
		sprintf(buffer, "L|Panic could not initialize ADC\n");

		// Set LEDs to a destinctive pattern
		HAL_UART_Transmit(&huart1, (uint8_t*)buffer, strlen(buffer), 100);
			uint8_t aTXBuffer[] = {
			TLC59116_PWM0_AUTOINCR,
			0,
			0,
			255,
			255,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
		};
		tlc59116_send(aTXBuffer, sizeof(aTXBuffer));
		HAL_Delay(1000);
	}
}