#include "main.h"
#include "config.h"
#include "check.h"
#include "string.h"
#include "stdio.h"
#include "tlc59116.h"

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
  else
  {
    check->results.flow = false;
  }
}

void tim_panic() {
	while (1) {
		// Ensure master output is off
		HAL_GPIO_WritePin(MASTER_OUT_GPIO_Port, MASTER_OUT_Pin, GPIO_PIN_RESET);
		// Log error
		char buffer[100];
		sprintf(buffer, "L|Panic could not initialize Timer\n");

		// Set LEDs to a destinctive pattern
		HAL_UART_Transmit(&huart1, (uint8_t*)buffer, strlen(buffer), 100);
			uint8_t aTXBuffer[] = {
			TLC59116_PWM0_AUTOINCR,
			0,
			0,
			0,
			0,
			255,
			255,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
		};
		tlc59116_send(aTXBuffer, sizeof(aTXBuffer));
		HAL_Delay(1000);
	}
}

bool checkIOPin(GPIO_TypeDef *type, uint16_t pin, GPIO_PinState desired)
{
  if (HAL_GPIO_ReadPin(type, pin) == desired)
  {
    return true;
  }
  return false;
}

void serialPrintResult(CheckValues *values)
{
  char buffer[60] = {'\0'};
  sprintf(buffer, "S|");
  HAL_UART_Transmit(&huart1, (uint8_t *)buffer, strlen(buffer), 50);

  sprintf(buffer, "T1: %d|", values->temp1);
  HAL_UART_Transmit(&huart1, (uint8_t *)buffer, strlen(buffer), 50);
  sprintf(buffer, "T2: %d|", values->temp2);
  HAL_UART_Transmit(&huart1, (uint8_t *)buffer, strlen(buffer), 50);
  sprintf(buffer, "PRE: %d|", values->pressure);
  HAL_UART_Transmit(&huart1, (uint8_t *)buffer, strlen(buffer), 50);

  sprintf(buffer, "FLOW: %d|", values->flow);
  HAL_UART_Transmit(&huart1, (uint8_t *)buffer, strlen(buffer), 50);
  sprintf(buffer, "D1: %d|", values->door1);
  HAL_UART_Transmit(&huart1, (uint8_t *)buffer, strlen(buffer), 50);
  sprintf(buffer, "D2: %d|", values->door2);
  HAL_UART_Transmit(&huart1, (uint8_t *)buffer, strlen(buffer), 50);
  sprintf(buffer, "VENT: %d|", values->exhaust_digital);
  HAL_UART_Transmit(&huart1, (uint8_t *)buffer, strlen(buffer), 50);
  sprintf(buffer, "UNL: %d|", values->extunlock);
  HAL_UART_Transmit(&huart1, (uint8_t *)buffer, strlen(buffer), 50);
  sprintf(buffer, "FIRE: %d|", values->fire);
  HAL_UART_Transmit(&huart1, (uint8_t *)buffer, strlen(buffer), 50);
  sprintf(buffer, "\r\n");
  HAL_UART_Transmit(&huart1, (uint8_t *)buffer, strlen(buffer), 50);
}\

bool overallStatus(CheckResults *data)
{
  bool all;
  all = data->door1 &&
        data->door2 &&
        data->flow &&
        data->pressure &&
        data->temp1;
  if (ENABLE_TEMPOUT)
  {
    all = all && data->temp2;
  }
  if (ENABLE_EXTUNLOCK)
  {
    all = all && data->extunlock;
  }
  if (ENABLE_FIREALARM)
  {
    all = all && data->fire;
  }

  if (all)
  {
    HAL_GPIO_WritePin(MASTER_OUT_GPIO_Port, MASTER_OUT_Pin, GPIO_PIN_SET);
  }
  else
  {
    HAL_GPIO_WritePin(MASTER_OUT_GPIO_Port, MASTER_OUT_Pin, GPIO_PIN_RESET);
  }
  return all;
}
