/*
 * delay.c
 *
 *  Created on: 2014��5��6��
 *      Author: Administrator
 */

#include <includes.h>
void rt_delay_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	rt_sem_init(&sem_delay, "delay", 0, RT_IPC_FLAG_FIFO);

//	    SystemCoreClock =SystemCoreClock;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

//	    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
//	    ϵͳʱ��ΪSystemCoreClock = 168MHz,��105��Ƶ
//	    �õ�1.6MH����������ڼĴ���Ϊ500����Ƶ��Ϊ1.6M/500 = 3.2K��0.3125mS
//	    TIM3CLK = 2 * PCLK1
//	    PCLK1 = HCLK / 4
//	    => TIM3CLK = HCLK / 2 = SystemCoreClock /2	TODO ĿǰTIM��Ƶ��Ϊ3.2K������һ�ܲ�64���Ҫ��
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Prescaler = 83;
	TIM_TimeBaseStructure.TIM_Period = 99;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);

	TIM_SetCounter(TIM7, 0);

	TIM_SelectOnePulseMode(TIM7, TIM_OPMode_Single);

	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	TIM_ClearFlag(TIM7, TIM_FLAG_Update);
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM7, DISABLE);
}

void rt_delay_us(uint32_t t)
{
	TIM_SetCounter(TIM7, 0);
	TIM_SetAutoreload(TIM7,t);
	TIM_Cmd(TIM7,ENABLE);
	rt_sem_take(&sem_delay,RT_WAITING_FOREVER);
}
