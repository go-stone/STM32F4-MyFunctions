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
