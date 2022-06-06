#include "main.h"
#include "check.h"

#define TLC59116_ADDRESS 0xC0
#define TLC59116_PWM0_AUTOINCR 0x82

void tlc59116_init(I2C_HandleTypeDef*,UART_HandleTypeDef*);
void tlc59116_setLEDs(I2C_HandleTypeDef, CheckResults);
bool wait_for_gpio_state_timeout(GPIO_TypeDef*, uint16_t, GPIO_PinState, uint32_t);
void I2C_ClearBusyFlagErratum(I2C_HandleTypeDef*, uint32_t);
