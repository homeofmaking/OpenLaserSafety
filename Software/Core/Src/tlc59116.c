#include "main.h"
#include "config.h"
#include "check.h"
#include "tlc59116.h"
#include "stdio.h"

void tlc59116_init(I2C_HandleTypeDef hi2c,UART_HandleTypeDef *huart) {

	uint8_t aTxBuffer[] = {
			0x80, // inc
			0x00,  //mod1
			0x00,
			0x00, //led1
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00, // led16
			0xFF, // Register 12 /  Group duty cycle control
			0x00, // Register 13 /  Group frequency
			0xAA, // Register 14 /  LED output state 0  // Default alle LEDs auf PWM
			0xAA, // Register 15 /  LED output state 1  // Default alle LEDs auf PWM
			0xAA, // Register 16 /  LED output state 2  // Default alle LEDs auf PWM
			0xAA, // Register 17 /  LED output state 3  // Default alle LEDs auf PWM
			0x00, // Register 18 /  I2C bus subaddress 1
			0x00, // Register 19 /  I2C bus subaddress 2
			0x00, // Register 1A /  I2C bus subaddress 3
			0x00, // Register 1B /  All Call I2C bus address
			0xFF, // Register 1C /  IREF configuration
		};

	while (HAL_I2C_Master_Transmit(&hi2c, TLC59116_ADDRESS<<1, aTxBuffer, sizeof(aTxBuffer), 100) != HAL_OK) {
		  char msgbuf[512]= {'\0'};
		  sprintf(msgbuf, "Waiting for I2C transmit\r\n");
		  HAL_UART_Transmit(huart, (uint8_t*)msgbuf, strlen(msgbuf), 100);
		  HAL_Delay(200);

	}

}


void tlc59116_setLEDs(I2C_HandleTypeDef hi2c, CheckResults data) {

	uint8_t aTXBuffer[] = {
			TLC59116_PWM0_AUTOINCR,
			data.door1 * 255,
			!data.door1 * 255,
			data.flow * 255,
			!data.flow * 255,
			data.temp1 * 255,
			!data.temp1 * 255,
			data.temp2 * 255,
			!data.temp2 * 255,
			0,
			0,
			0,
			0,
			0,
			0,
			data.all * 255,
			!data.all* 255
	};
    HAL_I2C_Master_Transmit(&hi2c, TLC59116_ADDRESS, aTXBuffer, sizeof(aTXBuffer), 100);

}
