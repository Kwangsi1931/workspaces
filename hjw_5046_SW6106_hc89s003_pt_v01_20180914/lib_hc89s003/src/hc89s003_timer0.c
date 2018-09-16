
#include<HC89S003F4.h>
#include "hc89s003_timer0.h"


void Timer0_Init(void)
{
    /**********************************TIM0配置初始化**************************************/
    TCON1 = 0x00;                       //Tx0定时器时钟为Fosc
    //TMOD = 0x00;                        //16位重装载定时器/计数器
    TMOD = TMOD & 0xF0;
    TMOD = TMOD | 0x00; //auto load 16bits

    //Tim0计算时间  = (65536 - 0xFACB) * (1 / (Fosc /Timer分频系数))
    //              = 1333 / (16000000 / 12)
    //              = 1 ms

    //定时1ms
    //反推初值  = 65536 - ((1/1000) / (1/(Fosc / Timer分频系数)))
    //          = 65536 - ((1/1000) / (1/(16000000 / 12)))
    //          = 65536 - 1333
    //          = 0xFACB
    TH0 = CONST_TIMER0_ARC_H;
    TL0 = CONST_TIMER0_ARC_L;                           //T0定时时间1ms
    IE |= 0x02;                         //打开T0中断
    TCON |= 0x10;                       //使能T0
}

#if 0
void Timer0_Init(void)
{
    //配置T0定时1MS
    //T0定时器时钟Fosc,禁止T0比较器输出功能
    TCON1 |= TIM_T0X12_FOSC;
    //T0内部16位重装定时
    TMOD &= ~(TIM_GATE0 + TIM_CT0 + TIM_M0_0);
    //定时时间T = (65536 - CNT)/Fosc ==> CNT = 65536 - T*Fosc
    TH0 = 0x83;
    TL0 = 0x00;
    //使能T0
    TCON |= TIM_TR0;
    //开启T0中断
    IE |= INT_ET0_EN;
}
#endif