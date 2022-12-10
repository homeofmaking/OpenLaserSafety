#ifndef __CHECK_H__
#define __CHECK_H__

typedef struct ErrorCounters
{
  uint16_t i2c;
  uint16_t upperBound;
  uint16_t numAboveLimit;
  uint16_t numBelowLimit;
  bool tooLow;
  bool tooHigh;
} AnalogData;

#endif