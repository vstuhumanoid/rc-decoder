#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include <drivers/gpio/gpio.h>
#include <drivers/delay/delay.h>

#include "hw_config.h"
#include "usb_lib.h"
#include "usb_pwr.h"

__IO uint8_t PrevXferComplete = 1;

int main()
{    
    Set_System();

    USB_Interrupts_Config();

    Set_USBClock();

    USB_Init();

    while (1)
    {
    }
    
    return 0;
}