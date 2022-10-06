#include "watertemp.h"
#include "string.h"
#include "stdbool.h"
#include "config.h"
#include "math.h"



UART_HandleTypeDef huart3;

bool checkAnalogData(AnalogData *data, uint32_t value, uint16_t recoverOffset) {
	// lower limit
    if ( value < data->lowerBound ) {
    	if ( data->numBelowLimit < TEMP_SMOOTHING ) {
        	++(data->numBelowLimit);
        }
    } else { // current value not to low
        if (data->numBelowLimit > 0) {
        	if (value > (data->lowerBound + recoverOffset)) {
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
    if ( value > data->upperBound ) {
    	if ( data->numAboveLimit < TEMP_SMOOTHING ) {
        	++(data->numAboveLimit);
        }
    } else {
        if (data->numAboveLimit > 0) {
        	if (value < (data->upperBound - recoverOffset)) {
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

float inputToCelcius(uint32_t data) {

	float Vsupply = 3.28; //power supply voltage (3.3 V rail) -STM32 ADC pin is NOT 5 V tolerant
	float Vout; //Voltage divider output
	float R_NTC; //NTC thermistor resistance in Ohms
	float R_10k = 11000; //10k resistor measured resistance in Ohms (other element in the voltage divider)
	float R_25 = 50000;
	float B_param = 3950; //B-coefficient of the thermistor
	float T0 = 298.15; //25°C in Kelvin
	float Temp_K; //Temperature measured by the thermistor (Kelvin)
	float Temp_C; //Temperature measured by the thermistor (Celsius)

	Vout = (float)(data)/4096 * Vsupply;
	R_NTC = (Vout * R_10k) /(Vsupply - Vout);  //calculating the resistance of the thermistor
	Temp_K = (T0*B_param)/(T0*log(R_NTC/R_25)+B_param); //Temperature in Kelvin
	//Temp_K =  1 / ((1 / T0) + ((log(R_NTC / R_25)) / B_param));

	Temp_C = Temp_K - 273.15; //converting into Celsius
	return Temp_C;
}

