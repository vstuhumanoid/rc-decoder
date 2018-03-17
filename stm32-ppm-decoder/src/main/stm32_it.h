#ifndef __STM32IT_H__
#define __STM32IT_H__

#include "platform_config.h"
#include "usb_istr.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include "hw_config.h"

__IO uint8_t Send_Buffer[2];
extern __IO uint8_t PrevXferComplete;
extern uint32_t ADC_ConvertedValueX;
extern uint32_t ADC_ConvertedValueX_1;
extern __IO uint32_t TimingDelay;


void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void USB_LP_CAN1_RX0_IRQHandler(void);
void DMA1_Channel1_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

#endif