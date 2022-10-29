#include "main.h"
#include "check.h"

#define TLC59116_ADDRESS 0xC0
#define TLC59116_PWM0_AUTOINCR 0x82

void tlc59116_init(I2C_HandleTypeDef*);
void tlc59116_setLEDs(I2C_HandleTypeDef, CheckResults);
void tlc59116_setAllLEDsOn();

extern UART_HandleTypeDef huart1;
extern I2C_HandleTypeDef hi2c2;

