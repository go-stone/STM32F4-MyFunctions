/**
 * @file F4xxMyFunctions.c
 * @author ZhangYi
 * 
 * */
#include "F4xxMyFunctions.h"
#include "stm32f4xx.h"
/**
 * @brief (简化为Simplified_GPIOx_OutPutPP_Init)将指定引脚组的指定引脚初始化为推挽输出，引脚速率为25MHz，引脚电平下拉
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
 * @brief (简化为Simplified_TIMx_Init)初始化指定的定时器，并指定其预分频系数和计数周期(已经-1，为真实系数和周期)，常与NVICx_Init()配合使用
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
 * @brief (简化为Simplified_NVICx_Init)初始化指定的内嵌向量中断，通常与TIMx_Init()配合使用
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
 * @brief (简化为Simplified_GPIOx_Input_Init)将指定GPIOx的指定引脚设为输入模式，引脚速率25MHz，引脚电平下拉
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
/**
 * @brief (简化为Simplified_ADCx_Init)初始化指定的ADCx和ADC的通道Channelx，并将采样频率设为四分频(21MHz)
 * @param RCC_GPIOx外设，RCC_ADCx外设，GPIO结构体，引脚编号，GPIOx组别，ADC_CommonInitTypeDef结构体，ADC_InitTypeDef结构体，ADCx组别，数据对齐方式，分辨率(位数)
 * @retval void
 * */
void ADCx_Init(uint32_t RCC_GPIOx, uint32_t RCC_ADCx, GPIO_InitTypeDef *GPIO_ITD, uint16_t Pinx, GPIO_TypeDef *GPIOx, ADC_CommonInitTypeDef *ADC_CITD, ADC_InitTypeDef *ADC_ITD, ADC_TypeDef *ADCx, uint32_t Data_Align, uint32_t Resolution)
{
    RCC_AHB1PeriphClockCmd(RCC_GPIOx, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_ADCx, ENABLE);
    GPIO_ITD->GPIO_Mode = GPIO_Mode_AN;
    GPIO_ITD->GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_ITD->GPIO_Pin = Pinx;
    GPIO_Init(GPIOx, GPIO_ITD);

    RCC_APB2PeriphResetCmd(RCC_ADCx, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_ADCx, DISABLE);
    ADC_CITD->ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CITD->ADC_Mode = ADC_Mode_Independent;
    ADC_CITD->ADC_Prescaler = ADC_Prescaler_Div4;
    ADC_CITD->ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(ADC_CITD);
    ADC_ITD->ADC_ScanConvMode = DISABLE;
    ADC_ITD->ADC_ContinuousConvMode = DISABLE;
    ADC_ITD->ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_ITD->ADC_DataAlign = Data_Align;
    ADC_ITD->ADC_Resolution = Resolution;
    ADC_ITD->ADC_NbrOfConversion = 1;
    ADC_Init(ADCx, ADC_ITD);
    ADC_Cmd(ADCx, ENABLE);
}
/**
 * @brief 获取指定ADCx指定通道Channelx上采样的平均值
 * @param ADC采样通道，采样平均次数，ADCx组别，两次采样之间的间隔时间
 * @retval int
 * */
int Get_ADC_Average(uint8_t ADC_Channelx, int AVG_Times, ADC_TypeDef *ADCx, uint8_t ADC_SampleTime)
{
    int Temp_Value = 0;
    int i;
    int AVG_Value = 0;
    ADC_RegularChannelConfig(ADCx, ADC_Channelx, 1, ADC_SampleTime);
    ADC_SoftwareStartConv(ADCx);
    while (ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) != SET)
    {
    }
    for (i = 0; i < AVG_Times; i++)
    {
        Temp_Value += ADC_GetConversionValue(ADCx);
    }
    AVG_Value = Temp_Value / AVG_Times;
    return AVG_Value;
}
/**
 * @brief 简化了GPIOx_Out_PP_Init(),将结构体的定义放在了函数体内；将GPIOx初始化为推挽输出，引脚速率为25MHz
 * @param RCC_AHB_GPIOx外设，pinx引脚编号，GPIOx引脚组别
 * @retval void
 * */
void Simplified_GPIOx_OutPutPP_Init(uint32_t RCC_AHB_GPIOx, uint32_t Pinx, GPIO_TypeDef *GPIOx)
{
    GPIO_InitTypeDef GPIO_ITD;
    RCC_AHB1PeriphClockCmd(RCC_AHB_GPIOx, ENABLE);
    GPIO_ITD.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_ITD.GPIO_OType = GPIO_OType_PP;
    GPIO_ITD.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_ITD.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_ITD.GPIO_Pin = Pinx;
    GPIO_Init(GPIOx, &GPIO_ITD);
}
/**
 * @brief 简化后的TIMx初始化函数，初始化为向上计数，使能Update中断
 * @param RCC_APBx_TIMx，TIMx组别，APBx时钟线，预分频系数，重装载值
 * @retval void
 * */
void Simplified_TIMx_Init(uint32_t RCC_APBx_TIMx, TIM_TypeDef *TIMx, int APBx, int T_psc, int T_per)
{
    TIM_TimeBaseInitTypeDef TIM_TBITD;
    if (APBx == 1)
    {
        RCC_APB1PeriphClockCmd(RCC_APBx_TIMx, ENABLE);
    }
    if (APBx == 2)
    {
        RCC_APB2PeriphClockCmd(RCC_APBx_TIMx, ENABLE);
    }
    TIM_TBITD.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TBITD.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TBITD.TIM_Prescaler = T_psc - 1;
    TIM_TBITD.TIM_Period = T_per - 1;
    TIM_TimeBaseInit(TIMx, &TIM_TBITD);
    TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIMx, ENABLE);
}
/**
 * @brief 简化后的NVICx初始化函数，指定了优先级分组为NVIC_PriorityGroup_2
 * @param IRQ通道，抢占优先级（主），响应优先级（次）
 * @retval void
 * */
void Simplified_NVICx_Init(uint8_t IRQChannel, int Main_Pri, int Sub_Pri)
{
    NVIC_InitTypeDef NVIC_ITD;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_ITD.NVIC_IRQChannel = IRQChannel;
    NVIC_ITD.NVIC_IRQChannelCmd = ENABLE;
    NVIC_ITD.NVIC_IRQChannelPreemptionPriority = Main_Pri;
    NVIC_ITD.NVIC_IRQChannelSubPriority = Sub_Pri;
    NVIC_Init(&NVIC_ITD);
}
/**
 * @brief 将指定的引脚指定为输入模式，电平下拉，引脚速率25MHz
 * @param RCC_AHB_GPIOx外设，GPIOx，Pinx引脚编号
 * @retval void
 * */
void Simplified_GPIOx_Input_Init(uint32_t RCC_AHB_GPIOx, GPIO_TypeDef *GPIOx, uint16_t Pinx)
{
    GPIO_InitTypeDef GPIO_ITD;
    RCC_AHB1PeriphClockCmd(RCC_AHB_GPIOx, ENABLE);
    GPIO_ITD.GPIO_Mode = GPIO_Mode_IN;
    GPIO_ITD.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_ITD.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_ITD.GPIO_Pin = Pinx;
    GPIO_Init(GPIOx, &GPIO_ITD);
}
/**
 * @brief 初始化指定的ADCx，时钟4分频(21MHz),采样间隔5个时钟脉冲，独立模式，DMA失能，数据右对齐，禁用扫描和连续转换，无外部触发边沿
 * @param RCC_AHB_GPIOx外设，RCC_ADCx外设，Pinx引脚编号，GPIOx，ADCx，ADC分辨率
 * @retval void
 * */
void Simplified_ADCx_Init(uint32_t RCC_GPIOx, uint32_t RCC_ADCx, uint16_t Pinx, GPIO_TypeDef *GPIOx, ADC_TypeDef *ADCx, uint32_t Resolution)
{
    GPIO_InitTypeDef GPIO_ITD;
    ADC_CommonInitTypeDef ADC_CITD;
    ADC_InitTypeDef ADC_ITD;
    RCC_AHB1PeriphClockCmd(RCC_GPIOx, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_ADCx, ENABLE);
    GPIO_ITD.GPIO_Mode = GPIO_Mode_AN;
    GPIO_ITD.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_ITD.GPIO_Pin = Pinx;
    GPIO_Init(GPIOx, &GPIO_ITD);

    RCC_APB2PeriphResetCmd(RCC_ADCx, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_ADCx, DISABLE);
    ADC_CITD.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CITD.ADC_Mode = ADC_Mode_Independent;
    ADC_CITD.ADC_Prescaler = ADC_Prescaler_Div4;
    ADC_CITD.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(&ADC_CITD);
    ADC_ITD.ADC_ScanConvMode = DISABLE;
    ADC_ITD.ADC_ContinuousConvMode = DISABLE;
    ADC_ITD.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_ITD.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_ITD.ADC_Resolution = Resolution;
    ADC_ITD.ADC_NbrOfConversion = 1;
    ADC_Init(ADCx, &ADC_ITD);
    ADC_Cmd(ADCx, ENABLE);
}
