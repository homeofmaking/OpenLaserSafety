#ifndef __CONFIG_H__
#define __CONFIG_H__
#include "stdbool.h"

#define ENABLE_TEMP2 true
#define TEMP_SMOOTHING 10
#define TEMP_RECOVER_OFFSET 3

/* 50kOhm @25°C + 150kOhm R1
 * 25°C -> 1023 ADC value
 */
#define TEMP1_LOWER 1638  // 10°C
#define TEMP1_UPPER 856  // 30°C

#define TEMP2_LOWER 1638  // 10°C
#define TEMP2_UPPER 856  // 30°C

#define MIN_PULSES 5 // minimum number of pulses from flow sensor required per loop

#define DOOR1_GPIO_TYPE GPIOF
#define DOOR1_GPIO_PIN GPIO_PIN_4
#define DOOR1_GPIO_DESIRED GPIO_PIN_SET

#endif
