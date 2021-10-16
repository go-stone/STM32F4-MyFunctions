/**
 * @file F4xxMyFunctions.c
 * @author ZhangYi
 * 
 * */
#include "F4xxMyFunctions.h"
/**
 * @brief 将指定引脚组的指定引脚初始化为推挽输出，引脚速率为25MHz，引脚电平下拉
 * @param RCC_AHB_GPIOx外设，GPIO结构体，引脚编号，引脚编组
 * @retval void
 * */
void GPIOx_OutPP_Init(uint32_t RCC_AHB_GPIOx, GPIO_InitTypeDef *GPIO_ITD, uint16_t Pinx, GPIO_TypeDef *GPIOx)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB_GPIOx, ENABLE);
    GPIO_ITD->GPIO_Mode = GPIO_Mode_OUT;
    GPIO_ITD->GPIO_OType = GPIO_OType_PP;
    GPIO_ITD->GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_ITD->GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_ITD->GPIO_Pin = Pinx;
    GPIO_Init(GPIOx, GPIO_ITD);
}
/**
 * @brief 初始化指定的定时器，并指定其预分频系数和计数周期(已经-1，为真实系数和周期)，常与NVICx_Init()配合使用
 * @param RCC_APBx_TIMx外设，TIM时基结构体，TIMx，真实预分频系数，真实计数周期
 * @retval void
 * */
void TIMx_Init(uint32_t RCC_APBx_TIMx, TIM_TimeBaseInitTypeDef *TIM_TBITD, TIM_TypeDef *TIMx, int APBx, int T_psc, int T_per)
{
    if (APBx == 1)
    {
        RCC_APB1PeriphClockCmd(RCC_APBx_TIMx, ENABLE);
    }
    if (APBx == 2)
    {
        RCC_APB2PeriphClockCmd(RCC_APBx_TIMx, ENABLE);
    }
    TIM_TBITD->TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TBITD->TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TBITD->TIM_Prescaler = T_psc - 1;
    TIM_TBITD->TIM_Period = T_per - 1;
    TIM_TimeBaseInit(TIMx, TIM_TBITD);
    TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIMx, ENABLE);
}
/**
 * @brief 初始化指定的内嵌向量中断，通常与TIMx_Init()配合使用
 * @param NVIC中断结构体，IRQn中断通道，抢占优先级(0~3)，响应优先级(0~3)
 * @retval void
 * */
void NVICx_Init(NVIC_InitTypeDef *NVIC_ITD, uint8_t IRQChannel, int Main_Pri, int Sub_Pri)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_ITD->NVIC_IRQChannel = IRQChannel;
    NVIC_ITD->NVIC_IRQChannelCmd = ENABLE;
    NVIC_ITD->NVIC_IRQChannelPreemptionPriority = Main_Pri;
    NVIC_ITD->NVIC_IRQChannelSubPriority = Sub_Pri;
    NVIC_Init(NVIC_ITD);
}
/**
 * @brief 翻转指定GPIO引脚上的电平
 * @param GPIOx组号，引脚编号
 * @retval void
 * */
void Flip_GPIO_Out(GPIO_TypeDef *GPIOx, uint16_t Pinx)
{
    int state = GPIO_ReadOutputDataBit(GPIOx, Pinx);
    if (state == Bit_SET)
    {
        GPIO_WriteBit(GPIOx, Pinx, Bit_RESET);
    }
    else if (state == Bit_RESET)
    {
        GPIO_WriteBit(GPIOx, Pinx, Bit_SET);
    }
}
/**
 * @brief 将指定GPIOx的指定引脚设为输入模式，引脚速率25MHz，引脚电平下拉
 * @param RCC_AHB_GPIO外设，GPIO结构体，GPIOx编组，引脚编号
 * @retval void
 * */
void GPIOx_Input_Init(uint32_t RCC_AHB_GPIOx, GPIO_InitTypeDef *GPIO_ITD, GPIO_TypeDef *GPIOx, uint16_t Pinx)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB_GPIOx, ENABLE);
    GPIO_ITD->GPIO_Mode = GPIO_Mode_IN;
    GPIO_ITD->GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_ITD->GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_ITD->GPIO_Pin = Pinx;
    GPIO_Init(GPIOx, GPIO_ITD);
}