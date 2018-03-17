#include "stm32_it.h"



/*******************************************************************************
* Function Name  : USB_IRQHandler
* Description    : This function handles USB Low Priority interrupts
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
#if defined(STM32L1XX_MD) || defined(STM32L1XX_HD)|| defined(STM32L1XX_MD_PLUS) || defined (STM32F37X)
void USB_LP_IRQHandler(void)
#else
void USB_LP_CAN1_RX0_IRQHandler(void)
#endif
{
  USB_Istr();
}


#if defined(STM32L1XX_MD)
/*******************************************************************************
* Function Name  : EXTI15_10_IRQHandler
* Description    : This function handles External lines 15 to 10 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI15_10_IRQHandler(void)
{
  /* Check on the RIGHT button */
  if(EXTI_GetITStatus(RIGHT_BUTTON_EXTI_LINE) != RESET)
  {  
    if ((PrevXferComplete) && (bDeviceState == CONFIGURED))
    {
      Send_Buffer[0] = 0x05; 
      
      if (STM_EVAL_PBGetState(Button_RIGHT) == Bit_RESET)
      {
        Send_Buffer[1] = 0x01;
      }
      else 
      {
        Send_Buffer[1] = 0x00;
      }  
      
      /* Write the descriptor through the endpoint */
      USB_SIL_Write(EP1_IN, (uint8_t*) Send_Buffer, 2);  
      
      SetEPTxValid(ENDP1);
      
      PrevXferComplete = 0;
    }
    /* Clear the EXTI line  pending bit */
    EXTI_ClearITPendingBit(RIGHT_BUTTON_EXTI_LINE);
  }  

  /* Check on the LEFT button */
  if(EXTI_GetITStatus(LEFT_BUTTON_EXTI_LINE) != RESET)
  {  
    if ((PrevXferComplete) && (bDeviceState == CONFIGURED))
    {
      Send_Buffer[0] = 0x06; 
      
      if (STM_EVAL_PBGetState(Button_LEFT) == Bit_RESET)
      {
        Send_Buffer[1] = 0x01;
      }
      else 
      {
        Send_Buffer[1] = 0x00;
      }  
      
      /* Write the descriptor through the endpoint */
      USB_SIL_Write(EP1_IN, (uint8_t*) Send_Buffer, 2);  
      
      SetEPTxValid(ENDP1);
      
      PrevXferComplete = 0;
    }
    /* Clear the EXTI line  pending bit */
    EXTI_ClearITPendingBit(LEFT_BUTTON_EXTI_LINE);
  }  
}
#endif


/*******************************************************************************
* Function Name  : DMA1_Channel1_IRQHandler
* Description    : This function handles DMA1 Channel 1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel1_IRQHandler(void)
{  
  Send_Buffer[0] = 0x07;
  
  if((ADC_ConvertedValueX >>4) - (ADC_ConvertedValueX_1 >>4) > 4)
  {
    if ((PrevXferComplete) && (bDeviceState == CONFIGURED))
    {
      Send_Buffer[1] = (uint8_t)(ADC_ConvertedValueX >>4);
      
      /* Write the descriptor through the endpoint */
      USB_SIL_Write(EP1_IN, (uint8_t*) Send_Buffer, 2);  
      SetEPTxValid(ENDP1);
      ADC_ConvertedValueX_1 = ADC_ConvertedValueX;
      PrevXferComplete = 0;
    }
  }
  
  DMA_ClearFlag(DMA1_FLAG_TC1);
}

/*******************************************************************************
* Function Name  : EXTI_IRQHandler
* Description    : This function handles External lines interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
#if defined(STM32L1XX_MD) || defined(STM32L1XX_HD)|| defined(STM32L1XX_MD_PLUS)
void EXTI0_IRQHandler(void)
#elif defined (STM32F37X)
void EXTI2_TS_IRQHandler(void)
#else
void EXTI9_5_IRQHandler(void)
#endif
{
  if(EXTI_GetITStatus(KEY_BUTTON_EXTI_LINE) != RESET)
  {  
    if ((PrevXferComplete) && (bDeviceState == CONFIGURED))
    {
      Send_Buffer[0] = 0x05; 
#if defined(STM32L1XX_HD)|| defined(STM32L1XX_MD_PLUS)
      if (!STM_EVAL_PBGetState(Button_KEY) == Bit_RESET)
#else
      if (STM_EVAL_PBGetState(Button_KEY) == Bit_RESET)       
#endif      
      {
        Send_Buffer[1] = 0x01;
      }
      else 
      {
        Send_Buffer[1] = 0x00;
      }  
      
      /* Write the descriptor through the endpoint */
      USB_SIL_Write(EP1_IN, (uint8_t*) Send_Buffer, 2);  
      SetEPTxValid(ENDP1);
      PrevXferComplete = 0;
    }
    /* Clear the EXTI line  pending bit */
    EXTI_ClearITPendingBit(KEY_BUTTON_EXTI_LINE);
  }
}
#if !defined(STM32L1XX_MD) &&  !defined(STM32L1XX_HD) && !defined(STM32L1XX_MD_PLUS)&& ! defined (STM32F37X) && !defined(STM32F303xC) && !defined(STM32F303xE)
/*******************************************************************************
* Function Name  : EXTI15_10_IRQHandler
* Description    : This function handles External lines 15 to 10 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI15_10_IRQHandler(void)
{
  if(EXTI_GetITStatus(TAMPER_BUTTON_EXTI_LINE) != RESET)
  {  
    if ((PrevXferComplete) && (bDeviceState == CONFIGURED))
    {
      Send_Buffer[0] = 0x06;
      
      if (STM_EVAL_PBGetState(Button_TAMPER) == Bit_RESET)
      {
        Send_Buffer[1] = 0x01;
      }
      else 
      {
        Send_Buffer[1] = 0x00;
      }
      
      /* Write the descriptor through the endpoint */    
      USB_SIL_Write(EP1_IN, (uint8_t*) Send_Buffer, 2);  
     
      SetEPTxValid(ENDP1);

      PrevXferComplete = 0;
    }
    /* Clear the EXTI line 13 pending bit */
    EXTI_ClearITPendingBit(TAMPER_BUTTON_EXTI_LINE);
  }
}

#endif /*STM32L1XX_HD*/

/*******************************************************************************
* Function Name  : USB_FS_WKUP_IRQHandler
* Description    : This function handles USB WakeUp interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

#if defined(STM32L1XX_MD) || defined(STM32L1XX_HD)|| defined(STM32L1XX_MD_PLUS)
void USB_FS_WKUP_IRQHandler(void)
#else
void USBWakeUp_IRQHandler(void)
#endif
{
  EXTI_ClearITPendingBit(EXTI_Line18);
}
