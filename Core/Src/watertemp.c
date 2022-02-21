#include "watertemp.h"
#include "main.h"
#include "string.h"
#include "stdbool.h"


UART_HandleTypeDef huart3;

const uint16_t TEMP_SMOOTHING = 20000;
const uint16_t TEMP_RECOVER_OFFSET = 3;


bool checkWaterInletTemperature(WaterInletData *data) {

	// lower limit
    if ( (*data->adcBuffer)[0] < data->lowerBound ) {
    	if ( data->numBelowLimit < TEMP_SMOOTHING ) {
        	++(data->numBelowLimit);
        }
    } else {
        if (data->numBelowLimit > 0) {
        	if ((*data->adcBuffer)[0] > (data->lowerBound + TEMP_RECOVER_OFFSET)) {
            --(data->numBelowLimit);
        	}
        } else {
        	data->tooLow = false;
        }
    }
    if (data->numBelowLimit >= TEMP_SMOOTHING) {
    	data->tooLow = true;
    }

	// upper limit
    if ( (*data->adcBuffer)[0] > data->upperBound ) {
    	if ( data->numAboveLimit < TEMP_SMOOTHING ) {
        	++(data->numAboveLimit);
        }
    } else {
        if (data->numAboveLimit > 0) {
        	if ((*data->adcBuffer)[0] < (data->upperBound - TEMP_RECOVER_OFFSET)) {
            --(data->numAboveLimit);
        	}
        } else {
        	data->tooHigh = false;
        }
    }
    if (data->numAboveLimit >= TEMP_SMOOTHING) {
    	data->tooHigh = true;
    }



    if (data->tooLow || data->tooHigh) {
    	return false;
    }
    return true;


}
