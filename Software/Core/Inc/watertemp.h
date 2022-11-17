#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"
#include "main.h"


typedef struct AnalogData
{
  uint16_t lowerBound;
  uint16_t upperBound;
  uint16_t numAboveLimit;
  uint16_t numBelowLimit;
  bool tooLow;
  bool tooHigh;
} AnalogData;


bool checkAnalogData(AnalogData*, uint32_t, uint16_t);
float inputToCelcius(uint32_t);
extern UART_HandleTypeDef huart1;
extern uint32_t pulseCounter;

