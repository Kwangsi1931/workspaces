
#include<HC89S003F4.h>
#include "hc89s003_timer0.h"


void Timer0_Init(void)
{
    /**********************************TIM0���ó�ʼ��**************************************/
    TCON1 = 0x00;                       //Tx0��ʱ��ʱ��ΪFosc
    //TMOD = 0x00;                        //16λ��װ�ض�ʱ��/������
    TMOD = TMOD & 0xF0;
    TMOD = TMOD | 0x00; //auto load 16bits

    //Tim0����ʱ��  = (65536 - 0xFACB) * (1 / (Fosc /Timer��Ƶϵ��))
    //              = 1333 / (16000000 / 12)
    //              = 1 ms

    //��ʱ1ms
    //���Ƴ�ֵ  = 65536 - ((1/1000) / (1/(Fosc / Timer��Ƶϵ��)))
    //          = 65536 - ((1/1000) / (1/(16000000 / 12)))
    //          = 65536 - 1333
    //          = 0xFACB
    TH0 = CONST_TIMER0_ARC_H;
    TL0 = CONST_TIMER0_ARC_L;                           //T0��ʱʱ��1ms
    IE |= 0x02;                         //��T0�ж�
    TCON |= 0x10;                       //ʹ��T0
}

#if 0
void Timer0_Init(void)
{
    //����T0��ʱ1MS
    //T0��ʱ��ʱ��Fosc,��ֹT0�Ƚ����������
    TCON1 |= TIM_T0X12_FOSC;
    //T0�ڲ�16λ��װ��ʱ
    TMOD &= ~(TIM_GATE0 + TIM_CT0 + TIM_M0_0);
    //��ʱʱ��T = (65536 - CNT)/Fosc ==> CNT = 65536 - T*Fosc
    TH0 = 0x83;
    TL0 = 0x00;
    //ʹ��T0
    TCON |= TIM_TR0;
    //����T0�ж�
    IE |= INT_ET0_EN;
}
#endif