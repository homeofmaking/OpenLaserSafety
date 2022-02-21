#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"



typedef struct WaterInletData
{
  uint16_t (*adcBuffer)[512];
  uint16_t lowerBound;
  uint16_t upperBound;
  uint16_t numAboveLimit;
  uint16_t numBelowLimit;
  bool tooLow;
  bool tooHigh;
} WaterInletData;


bool checkWaterInletTemperature(WaterInletData*);

