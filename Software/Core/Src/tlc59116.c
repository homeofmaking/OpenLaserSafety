#include "main.h"
#include "config.h"
#include "check.h"
#include "tlc59116.h"
#include "stdio.h"
#include "string.h"

void tlc59116_init() {

	uint8_t aTXBuffer[] = {
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
			0xAA, // Register 14 /  LED output state 0  // Default set all LEDs to PWM
			0xAA, // Register 15 /  LED output state 1  // Default set all LEDs to PWM
			0xAA, // Register 16 /  LED output state 2  // Default set all LEDs to PWM
			0xAA, // Register 17 /  LED output state 3  // Default set all LEDs to PWM
			0x00, // Register 18 /  I2C bus subaddress 1
			0x00, // Register 19 /  I2C bus subaddress 2
			0x00, // Register 1A /  I2C bus subaddress 3
			0x00, // Register 1B /  All Call I2C bus address
			0xFF, // Register 1C /  IREF configuration
		};
	HAL_I2C_Master_Transmit(&hi2c2, TLC59116_ADDRESS, aTXBuffer, sizeof(aTXBuffer), 100);
}


void tlc59116_setLEDs(CheckResults data) {

	bool doors = data.door1 && data.door2;
	uint8_t aTXBuffer[] = {
			TLC59116_PWM0_AUTOINCR,
			doors * 255,
			!doors * 255,
			data.temp1 * 255,
			!data.temp1 * 255,
			data.flow * 255,
			!data.flow * 255,
			data.extunlock * 255,
			!data.extunlock * 255,
			data.pressure * 255,
			!data.pressure * 255,
			0,
			0,
			0,
			0,
			data.all * 255,
			!data.all* 255
	};
	tlc59116_send(aTXBuffer, sizeof(aTXBuffer));
}

void tlc59116_setAllLEDs(uint8_t value) {
	uint8_t aTXBuffer[] = {
			TLC59116_PWM0_AUTOINCR,
			value,
			value,
			value,
			value,
			value,
			value,
			value,
			value,
			value,
			value,
			value,
			value,
			value,
			value,
			value,
			value,
	};
	tlc59116_send(aTXBuffer, sizeof(aTXBuffer));
}
void tlc59116_send(uint8_t aTXBuffer[], uint8_t  size) {
	tlc59116_init();
	if (HAL_I2C_Master_Transmit(&hi2c2, TLC59116_ADDRESS, aTXBuffer, size, 100) != HAL_OK){
		char buffer[100];
		HAL_I2C_Init(&hi2c2);
		tlc59116_init();
		sprintf(buffer, "L|Setting LEDs failed\n");
		HAL_UART_Transmit(&huart1, (uint8_t*)buffer, strlen(buffer), 100);
	};
}



