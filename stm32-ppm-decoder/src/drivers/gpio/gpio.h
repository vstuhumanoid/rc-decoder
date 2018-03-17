#ifndef __DRIVERS_GPIO_H__
#define __DRIVERS_GPIO_H__

#include <stm32f10x_gpio.h>

/**
 * @brief Более удобная инициализация GPIO
 * @param gpio:  порт GPIO
 * @param pin:   выбор пина
 * @param mode:  режим GPIO
 * @param speed: скорость
 */
void GpioInit(GPIO_TypeDef* gpio,  uint16_t pin,  GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed);

#endif
