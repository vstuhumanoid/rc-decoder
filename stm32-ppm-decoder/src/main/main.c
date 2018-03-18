#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include <drivers/gpio/gpio.h>

#include "hw_config.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include "config.h"

__IO uint8_t PrevXferComplete = 1;
__IO uint8_t Send_Buffer[100];

void SendUsb()
{
    Send_Buffer[0] = 0x01;
    
   
    
    if ((PrevXferComplete) && (bDeviceState == CONFIGURED))
    {
        Send_Buffer[1] = 1;
        Send_Buffer[2] = 2;
        Send_Buffer[3] = 3;
          
            
        /* Write the descriptor through the endpoint */
        USB_SIL_Write(EP1_IN, (uint8_t*) Send_Buffer, MAX_PPM_CHANNELS + 1);  
        SetEPTxValid(ENDP1);      
        PrevXferComplete = 0;
        GPIOC->ODR^=GPIO_Pin_13;
    }
}

int main()
{    
    Set_System();
    USB_Interrupts_Config();
    Set_USBClock();
    USB_Init();
       
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GpioInit(GPIOC, GPIO_Pin_13, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, 0);

    while (1)
    {
        SendUsb();       
        //Delay_ms(1000);
        for(int i = 0; i<1000000; i++);
    }
    
    return 0;
}