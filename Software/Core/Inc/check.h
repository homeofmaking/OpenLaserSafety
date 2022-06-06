#ifndef __CHECK_H__
#define __CHECK_H__


#include "stdbool.h"
#include "main.h"

typedef struct CheckResults {
	bool temp1;
	bool temp2;
	bool flow;
	bool pressure;
	bool exhaust_digital;
	bool door1;
	bool door2;
	bool all;
} CheckResults;

typedef struct CheckValues {
	uint16_t temp1;
	uint16_t temp2;
	uint16_t flow;
	uint16_t pressure;
	bool exhaust_digital;
	bool door1;
	bool door2;
} CheckValues;

typedef struct Check {
	CheckResults results;
	CheckValues values;
} Check;


void serialPrintResult(CheckValues*, UART_HandleTypeDef);

void checkFlowCount(TIM_HandleTypeDef*, uint32_t*, Check*);

bool checkIOPin(GPIO_TypeDef*, uint16_t, GPIO_PinState);

void overallStatus(CheckResults*);

#endif
