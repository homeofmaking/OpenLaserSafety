#include "main.h"
#include "config.h"
#include "check.h"
#include "string.h"
#include "stdio.h"
#include "tlc59116.h"
#include "stdbool.h"

bool wait_for_gpio_state_timeout(GPIO_TypeDef *port, uint16_t pin, GPIO_PinState state, uint32_t timeout)
 {
    uint32_t Tickstart = HAL_GetTick();
    bool ret = true;
    /* Wait until flag is set */
    for(;(state != HAL_GPIO_ReadPin(port, pin)) && (true == ret);)
    {
        /* Check for the timeout */
        if (timeout != HAL_MAX_DELAY)
        {
            if ((timeout == 0U) || ((HAL_GetTick() - Tickstart) > timeout))
            {
                ret = false;
            }
            else
            {
            }
        }
        asm("nop");
    }
    return ret;
}



void I2C_ClearBusyFlagErratum(I2C_HandleTypeDef* handle, uint32_t timeout)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 1. Clear PE bit.
    CLEAR_BIT(handle->Instance->CR1, I2C_CR1_PE);

    //  2. Configure the SCL and SDA I/Os as General Purpose Output Open-Drain, High level (Write 1 to GPIOx_ODR).
    HAL_I2C_DeInit(handle);

    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStructure.Pull = GPIO_NOPULL;

    GPIO_InitStructure.Pin = I2C1_SCL_Pin;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = I2C1_SDA_Pin;
    HAL_GPIO_Init(I2C1_SDA_GPIO_Port, &GPIO_InitStructure);

    // 3. Check SCL and SDA High level in GPIOx_IDR.
    HAL_GPIO_WritePin(I2C1_SDA_GPIO_Port, I2C1_SDA_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(I2C1_SCL_GPIO_Port, I2C1_SCL_Pin, GPIO_PIN_SET);

    wait_for_gpio_state_timeout(I2C1_SCL_GPIO_Port, I2C1_SCL_Pin, GPIO_PIN_SET, timeout);
    wait_for_gpio_state_timeout(I2C1_SDA_GPIO_Port, I2C1_SDA_Pin, GPIO_PIN_SET, timeout);

    // 4. Configure the SDA I/O as General Purpose Output Open-Drain, Low level (Write 0 to GPIOx_ODR).
    HAL_GPIO_WritePin(I2C1_SDA_GPIO_Port, I2C1_SDA_Pin, GPIO_PIN_RESET);

    // 5. Check SDA Low level in GPIOx_IDR.
    wait_for_gpio_state_timeout(I2C1_SDA_GPIO_Port, I2C1_SDA_Pin, GPIO_PIN_RESET, timeout);

    // 6. Configure the SCL I/O as General Purpose Output Open-Drain, Low level (Write 0 to GPIOx_ODR).
    HAL_GPIO_WritePin(I2C1_SCL_GPIO_Port, I2C1_SCL_Pin, GPIO_PIN_RESET);

    // 7. Check SCL Low level in GPIOx_IDR.
    wait_for_gpio_state_timeout(I2C1_SCL_GPIO_Port, I2C1_SCL_Pin, GPIO_PIN_RESET, timeout);

    // 8. Configure the SCL I/O as General Purpose Output Open-Drain, High level (Write 1 to GPIOx_ODR).
    HAL_GPIO_WritePin(I2C1_SCL_GPIO_Port, I2C1_SCL_Pin, GPIO_PIN_SET);

    // 9. Check SCL High level in GPIOx_IDR.
    wait_for_gpio_state_timeout(I2C1_SCL_GPIO_Port, I2C1_SCL_Pin, GPIO_PIN_SET, timeout);

    // 10. Configure the SDA I/O as General Purpose Output Open-Drain , High level (Write 1 to GPIOx_ODR).
    HAL_GPIO_WritePin(I2C1_SDA_GPIO_Port, I2C1_SDA_Pin, GPIO_PIN_SET);

    // 11. Check SDA High level in GPIOx_IDR.
    wait_for_gpio_state_timeout(I2C1_SDA_GPIO_Port, I2C1_SDA_Pin, GPIO_PIN_SET, timeout);

    // 12. Configure the SCL and SDA I/Os as Alternate function Open-Drain.
    GPIO_InitStructure.Mode = GPIO_MODE_AF_OD;
    //GPIO_InitStructure.Alternate = GPIO_AF1_I2C1;

    GPIO_InitStructure.Pin = I2C1_SCL_Pin;
    HAL_GPIO_Init(I2C1_SCL_GPIO_Port, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = I2C1_SDA_Pin;
    HAL_GPIO_Init(I2C1_SDA_GPIO_Port, &GPIO_InitStructure);

    // 13. Set SWRST bit in I2Cx_CR1 register.
    SET_BIT(handle->Instance->CR1, I2C_CR1_SWRST);
    asm("nop");

    /* 14. Clear SWRST bit in I2Cx_CR1 register. */
    CLEAR_BIT(handle->Instance->CR1, I2C_CR1_SWRST);
    asm("nop");

    /* 15. Enable the I2C peripheral by setting the PE bit in I2Cx_CR1 register */
    SET_BIT(handle->Instance->CR1, I2C_CR1_PE);
    asm("nop");

    // Call initialization function.
    HAL_I2C_Init(handle);
}



void tlc59116_init(I2C_HandleTypeDef *hi2c, UART_HandleTypeDef *huart) {

	uint8_t aTxBuffer[] = {
			0x80, // inc
			0x00,  //mod1
			0x00,
			0x00, //led1
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00, // led16
			0xFF, // Register 12 /  Group duty cycle control
			0x00, // Register 13 /  Group frequency
			0xAA, // Register 14 /  LED output state 0  // Default alle LEDs auf PWM
			0xAA, // Register 15 /  LED output state 1  // Default alle LEDs auf PWM
			0xAA, // Register 16 /  LED output state 2  // Default alle LEDs auf PWM
			0xAA, // Register 17 /  LED output state 3  // Default alle LEDs auf PWM
			0x00, // Register 18 /  I2C bus subaddress 1
			0x00, // Register 19 /  I2C bus subaddress 2
			0x00, // Register 1A /  I2C bus subaddress 3
			0x00, // Register 1B /  All Call I2C bus address
			0xFF, // Register 1C /  IREF configuration
		};

	/* while (HAL_I2C_Master_Transmit(hi2c, TLC59116_ADDRESS, aTxBuffer, sizeof(aTxBuffer), 1000) == HAL_BUSY) {
		  I2C_ClearBusyFlagErratum(hi2c, 1000);

		  char msgbuf[512]= {'\0'};
		  sprintf(msgbuf, "Waiting for I2C transmit\r\n");
		  HAL_UART_Transmit(huart, (uint8_t*)msgbuf, strlen(msgbuf), 100);
		  HAL_Delay(200);
	}*/
	HAL_I2C_Master_Transmit(hi2c, TLC59116_ADDRESS, aTxBuffer, sizeof(aTxBuffer), 1000);
}


void tlc59116_setLEDs(I2C_HandleTypeDef hi2c, CheckResults data) {

	uint8_t aTXBuffer[] = {
			TLC59116_PWM0_AUTOINCR,
			data.door1 * 255,
			!data.door1 * 255,
			data.flow * 255,
			!data.flow * 255,
			data.temp1 * 255,
			!data.temp1 * 255,
			data.temp2 * 255,
			!data.temp2 * 255,
			0,
			0,
			0,
			0,
			0,
			0,
			data.all * 255,
			!data.all* 255
	};
    HAL_I2C_Master_Transmit(&hi2c, TLC59116_ADDRESS, aTXBuffer, sizeof(aTXBuffer), 100);

}
