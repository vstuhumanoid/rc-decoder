#include "delay.h"

void DelayInit(void)
{
    //разрешаем использовать счётчик
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    //обнуляем значение счётного регистра
	DWT->CYCCNT  = 0;
    //запускаем счётчик
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk; 
}

void Delay_us(uint32_t us)
{
    uint32_t t0 =  DWT->CYCCNT;
    uint32_t us_count_tic =  us * (SystemCoreClock/1000000);
    while ((DWT->CYCCNT - t0) < us_count_tic) ;
}

void Delay_ms(uint32_t ms)
{
    uint32_t t0 =  DWT->CYCCNT;
    uint32_t us_count_tic =  ms * (SystemCoreClock/1000);
    while ((DWT->CYCCNT - t0) < us_count_tic) ;
}