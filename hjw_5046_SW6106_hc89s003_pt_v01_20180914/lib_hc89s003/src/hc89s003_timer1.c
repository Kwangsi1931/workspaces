#include <reg51_ca.h>
#include "ca69f_timer1.h"

void Timer1_DeInit(void)
{
    //TODO:
    //TIM1->CR1  = TIM1_CR1_RESET_VALUE;
}

void Timer1_Init(void)
{
    TMOD = TMOD & 0x0F;
    TMOD = TMOD | 0x20;  //auto 8bits
    PT1 = 1;//���ȼ�
    TH1 = CONST_TIM1_ARC;
    TL1 = CONST_TIM1_ARC;
    TR1 = 1;        //����T1������
    ET1 = 1;
}




