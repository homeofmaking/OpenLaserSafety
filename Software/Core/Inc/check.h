#include "stdbool.h"
#include "main.h"

typedef struct CheckResults {
	bool temp1;
	bool temp2;
	bool flow;
	bool door1;
} CheckResults;

typedef struct CheckValues {
	uint16_t temp1;
	uint16_t temp2;
	uint16_t flow;
	bool door1;
} CheckValues;

typedef struct Check {
	CheckResults results;
	CheckValues values;
} Check;


void serialPrintResult(CheckValues*, UART_HandleTypeDef);

bool checkFlowCount(TIM_HandleTypeDef*, uint32_t*, Check*);

bool checkIOPin(GPIO_TypeDef*, uint16_t, GPIO_PinState);
