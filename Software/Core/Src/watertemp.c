#include "watertemp.h"
#include "string.h"
#include "stdbool.h"
#include "config.h"



UART_HandleTypeDef huart3;

bool checkWaterTemperature(WaterData *data, uint32_t value ) {

	// lower limit
    if ( value > data->lowerBound ) {
    	if ( data->numBelowLimit < TEMP_SMOOTHING ) {
        	++(data->numBelowLimit);
        }
    } else {
        if (data->numBelowLimit > 0) {
        	if (value < (data->lowerBound + TEMP_RECOVER_OFFSET)) {
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
    if ( value < data->upperBound ) {
    	if ( data->numAboveLimit < TEMP_SMOOTHING ) {
        	++(data->numAboveLimit);
        }
    } else {
        if (data->numAboveLimit > 0) {
        	if (value > (data->upperBound - TEMP_RECOVER_OFFSET)) {
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
