#include "main.h"
#include "check.h"

#define TLC59116_ADDRESS 0xC0
#define TLC59116_PWM0_AUTOINCR 0x82

void tlc59116_init();
void tlc59116_setLEDs(CheckResults);
void tlc59116_setAllLEDs(uint8_t);
void tlc59116_send(uint8_t[], uint8_t);

extern UART_HandleTypeDef huart1;
extern I2C_HandleTypeDef hi2c2;

