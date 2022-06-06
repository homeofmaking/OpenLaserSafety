/* #include "main.h"
#include "config.h"
#include "tlc59116.h"
#include "adc.h"
#include "stdio.h"
#include "string.h"

uint16_t adc_dma_average(int channel, AdcBuf *adcBuf)
{
	uint32_t adc_sum;
	int i;


	adc_sum = 0;
	if(channel < NUMBER_ADC_CHANNEL )
	{
		for(i=0; i<NUMBER_ADC_CHANNEL_AVERAGE_PER_CHANNEL; i++)
			adc_sum += *adcBuf[channel+i*NUMBER_ADC_CHANNEL];
	}
	else
		return 1;

	return adc_sum/NUMBER_ADC_CHANNEL_AVERAGE_PER_CHANNEL;
}
*/
