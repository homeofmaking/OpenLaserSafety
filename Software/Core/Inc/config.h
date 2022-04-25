#ifndef __CONFIG_H__
#define __CONFIG_H__
#include "stdbool.h"

#define ENABLE_TEMP2 true
#define TEMP_SMOOTHING 10
#define TEMP_RECOVER_OFFSET 3

/* 50kOhm @25°C + 10kOhm R1
 * 25°C -> 3412 ADC value
 * 0°C -> 38655 ADC value
 * 30°C -> 3279 ADC value
 */
#define TEMP1_LOWER 1638  // 10°C
#define TEMP1_UPPER 856  // 30°C

#define TEMP2_LOWER 1638  // 10°C
#define TEMP2_UPPER 856  // 30°C

#define MIN_PULSES 5 // minimum number of pulses from flow sensor required per loop

#define DOOR1_GPIO_TYPE GPIOF
#define DOOR1_GPIO_PIN GPIO_PIN_4
#define DOOR1_GPIO_DESIRED GPIO_PIN_SET


/* Differential pressure sensor
 * Test values:
 * 1250 no differential
 * 1230-1234  exhaust without filter
 * 1233-1238  exhaust with filter
 */
#endif
