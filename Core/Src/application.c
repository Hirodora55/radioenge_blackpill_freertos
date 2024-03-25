#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "radioenge_modem.h"

extern osTimerId_t PeriodicSendTimerHandle;
extern osThreadId_t AppSendTaskHandle;
extern ADC_HandleTypeDef hadc1;
extern osEventFlagsId_t ModemStatusFlagsHandle;
extern TIM_HandleTypeDef htim3;

void LoRaWAN_RxEventCallback(uint8_t *data, uint32_t length, uint32_t port, int32_t rssi, int32_t snr)
{
}

void PeriodicSendTimerCallback(void *argument)
{
}

void AppSendTaskCode(void *argument)
{
    /* USER CODE BEGIN 5 */
    /* Infinite loop */
    uint32_t read;
    int32_t temp;
    uint8_t sendStr[64]; //seleciona quantos caracteres a msg terá

    while (1)
    {
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 100);
        read = HAL_ADC_GetValue(&hadc1);
        temp = (int32_t)(33000 * ((float)read / 4096));
        sprintf(sendStr, "Temperature: %2d.%2d", temp / 100, temp % 100);
        //imprimindo o dado no TERA TERM
        LoRaWaitDutyCycle();
        LoRaSendNow(3, sendStr); //preciso imprimir a variavel "sedStr"
        osDelay(30000);
    }
}