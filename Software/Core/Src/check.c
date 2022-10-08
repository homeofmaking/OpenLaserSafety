#include "main.h"
#include "config.h"
#include "check.h"
#include "string.h"
#include "stdio.h"

void checkFlowCount(TIM_HandleTypeDef *htim, uint32_t *pulseCounter, Check *check)
{
  uint32_t previous = *pulseCounter;
  *pulseCounter = __HAL_TIM_GET_COUNTER(htim);

  uint32_t measurement = *pulseCounter - previous;
  check->values.flow = measurement;

  if (measurement > MIN_PULSES)
  {
    check->results.flow = true;
  }
  check->results.flow = false;
}

bool checkIOPin(GPIO_TypeDef *type, uint16_t pin, GPIO_PinState desired)
{
  if (HAL_GPIO_ReadPin(type, pin) == desired)
  {
    return true;
  }
  return false;
}

void serialPrintResult(CheckValues *values, UART_HandleTypeDef huart)
{
  char buffer[60] = {'\0'};
  sprintf(buffer, "Temp1: %d|", values->temp1);
  if (ENABLE_TEMP2)
  {
    sprintf(buffer + strlen(buffer), "Temp2: %d|", values->temp2);
  }
  sprintf(buffer + strlen(buffer), "Pressure: %d|", values->pressure);
  HAL_UART_Transmit(&huart, (uint8_t *)buffer, strlen(buffer), 100);

  sprintf(buffer, "Flow1: %d|", values->flow);
  sprintf(buffer + strlen(buffer), "Door1: %d|", values->door1);
  sprintf(buffer + strlen(buffer), "Door2: %d|", values->door2);
  HAL_UART_Transmit(&huart, (uint8_t *)buffer, strlen(buffer), 100);

  sprintf(buffer, "Exhaust: %d|", values->exhaust_digital);
  HAL_UART_Transmit(&huart, (uint8_t *)buffer, strlen(buffer), 100);
  sprintf(buffer, "\r\n");
  HAL_UART_Transmit(&huart, (uint8_t *)buffer, strlen(buffer), 100);
}

void overallStatus(CheckResults *data)
{
  bool all;
  all = data->door1 &&
        data->door2 &&
        data->flow &&
        data->pressure &&
        data->exhaust_digital &&
        data->temp1;
  if (ENABLE_TEMP2)
  {
    all = all && data->temp2;
  }
  if (all)
  {
    HAL_GPIO_WritePin(MASTER_OUT_GPIO_Port, MASTER_OUT_Pin, GPIO_PIN_SET);
  }
  else
  {
    HAL_GPIO_WritePin(MASTER_OUT_GPIO_Port, MASTER_OUT_Pin, GPIO_PIN_RESET);
  }
}
