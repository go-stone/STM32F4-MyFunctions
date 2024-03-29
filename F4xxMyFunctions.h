/**
 * @file F4xxMyFunctions.h
 * @author ZhangYi
 * */
#include "stm32f4xx.h"
void GPIOx_OutPP_Init(uint32_t RCC_AHB_GPIOx, GPIO_InitTypeDef *GPIO_ITD, uint16_t Pinx, GPIO_TypeDef *GPIOx);
void TIMx_Init(uint32_t RCC_APBx_TIMx, TIM_TimeBaseInitTypeDef *TIM_TBITD, TIM_TypeDef *TIMx, int APBx, int T_psc, int T_per);
void NVICx_Init(NVIC_InitTypeDef *NVIC_ITD, uint8_t IRQChannel, int Main_Pri, int Sub_Pri);
void Flip_GPIO_Out(GPIO_TypeDef *GPIOx, uint16_t Pinx);
void GPIOx_Input_Init(uint32_t RCC_AHB_GPIOx, GPIO_InitTypeDef *GPIO_ITD, GPIO_TypeDef *GPIOx, uint16_t Pinx);
void ADCx_Init(uint32_t RCC_GPIOx, uint32_t RCC_ADCx, GPIO_InitTypeDef *GPIO_ITD, uint16_t Pinx, GPIO_TypeDef *GPIOx, ADC_CommonInitTypeDef *ADC_CITD, ADC_InitTypeDef *ADC_ITD, ADC_TypeDef *ADCx, uint32_t Data_Align, uint32_t Resolution);
int Get_ADC_Average(uint8_t ADC_Channelx, int AVG_Times, ADC_TypeDef *ADCx, uint8_t ADC_SampleTime);
void Simplified_GPIOx_OutPutPP_Init(uint32_t RCC_AHB_GPIOx, uint32_t Pinx, GPIO_TypeDef *GPIOx);
void Simplified_TIMx_Init(uint32_t RCC_APBx_TIMx, TIM_TypeDef *TIMx, int APBx, int T_psc, int T_per);
void Simplified_NVICx_Init(uint8_t IRQChannel, int Main_Pri, int Sub_Pri);
void Simplified_GPIOx_Input_Init(uint32_t RCC_AHB_GPIOx, GPIO_TypeDef *GPIOx, uint16_t Pinx);
void TIM_InputCaptureInit(uint32_t RCC_GPIO, uint32_t RCC_TIM, int APBx, uint32_t Pinx, GPIO_TypeDef *GPIOx, uint16_t Pinsrc, uint8_t AF_TIM, TIM_TypeDef *TIMx, uint16_t TIM_CHN, uint8_t TIMx_IRQn, uint16_t IT_CC, int TIM_psc);
void CalculateHighTime_InTIM(uint8_t *STA, uint32_t *VAL, TIM_TypeDef *TIMx, uint16_t IT_CC);
void PullUp_GPIOx_Input_Init(uint32_t RCC_AHB_GPIOx, GPIO_TypeDef *GPIOx, uint16_t Pinx);
int Usart_HelpCalculateHighTime(uint8_t *STA, uint32_t *VAL, int AVG_times, float *Sum_HTV, int *Sum_rpsV, int *i, float *AVG_HT, int *AVG_rps, int *Is_ShowUsart);
