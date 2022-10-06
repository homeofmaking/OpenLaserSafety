#ifndef __CONFIG_H__
#define __CONFIG_H__
#include "stdbool.h"

#define ENABLE_TEMP2 false
#define TEMP_SMOOTHING 5
#define TEMP_RECOVER_OFFSET 3

/* 50kOhm @25°C + 10kOhm R1
 * TEMPERATURE VS RESISTANCE TABLE
 * Resistance         50k Ohms at 25deg. C
 * B Value            3950K at 25/50 deg. C
 * Temp. Range:－40-＋150℃
 * 0°C -> 3865 ADC value
 * 25°C -> 3412 ADC value
 * 30°C -> 3279
 */
#define TEMP1_LOWER 10  // °C
#define TEMP1_UPPER 30  // °C

#define TEMP2_LOWER 10  // °C
#define TEMP2_UPPER 30  // °C
/*
 * Pressure sensor open value: 2.50 V raw -> 1.7V after divider -> reading 2064
 * Upper limit 4.7 V:  raw -> 3.2 V after divider -> reading 4001
 * Lower limit 4.7 V:  raw -> 2.04 V after divider -> reading 4001
 */
#define PRESSURE_UPPER 4001 // 4.99 V
#define PRESSURE_LOWER 2550  // 3.00 V
//#define PRESSURE_LOWER 2000

#define MIN_PULSES 5 // minimum number of pulses from flow sensor required per loop

#define DOOR1_GPIO_TYPE GPIOA
#define DOOR1_GPIO_PIN GPIO_PIN_12
#define DOOR1_GPIO_DESIRED GPIO_PIN_RESET

#define DOOR2_GPIO_TYPE GPIOA
#define DOOR2_GPIO_PIN GPIO_PIN_4
#define DOOR2_GPIO_DESIRED GPIO_PIN_RESET

#define EXHAUST_DIGITAL_GPIO_TYPE GPIOA
#define EXHAUST_DIGITAL_GPIO_PIN GPIO_PIN_11
#define EXHAUST_DIGITAL_GPIO_DESIRED GPIO_PIN_RESET

#define NUMBER_ADC_CHANNEL 3
#define NUMBER_ADC_CHANNEL_AVERAGE_PER_CHANNEL 8

#define I2C1_SCL_GPIO_Port GPIOB
#define I2C1_SCL_Pin GPIO_PIN_10
#define I2C1_SDA_GPIO_Port GPIOB
#define I2C1_SDA_Pin GPIO_PIN_11

#define MASTER_OUT_GPIO_Port GPIOB
#define MASTER_OUT_Pin GPIO_PIN_12

#define ADC_CHANNEL_TEMP1 2
#define ADC_CHANNEL_TEMP2 0
#define ADC_CHANNEL_PRESSURE 1
#endif
