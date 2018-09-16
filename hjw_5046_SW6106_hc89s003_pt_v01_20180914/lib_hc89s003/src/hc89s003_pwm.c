/**
*   ************************************************************************************
*                               普芯达电子有限公司
*                               www.chipswinner.com
*   ************************************************************************************
*   @Demo   Version     V1.0.0.0
*   @Date               2018.8.6
*   ************************************************************************************
**/

/**************************************************************************************/
#define _PWM_
#include "pwm.h"
#include "gpio.h"

/**************************************************************************************/
/*应用中需要三组PWM0,PWM1,PWM2同时输出,可设置PWMCTRL和PWMENA寄存器.*/
/*先设置PENCTRL的BIT0位为1,再使能PWMENA的BIT6,5,4,2,1,0位.*/


/***************************************************************************************
* @功能   硬体 PWM0 初始化
* @说明
* @参数
* @返回值
* @注
***************************************************************************************/
void Pwm0_Config(void)
{
    //定义 INDEX1&INDEX2 两路输出在PMW0模块的PMW0和PWM01
    PWM_PORT_M_INDEX1 &= ~(0x0f << ((PWM_PIN_INDEX1 % 2) * 4));
    PWM_PORT_M_INDEX1 |=  (IOL_PUSHPULL_OUT << ((PWM_PIN_INDEX1 % 2) * 4));
    PWM_PORT_INDEX1 &= ~(0x01 << PWM_PIN_INDEX1);

    PWM_PORT_M_INDEX2 &= ~(0x0f << ((PWM_PIN_INDEX2 % 2) * 4));
    PWM_PORT_M_INDEX2 |=  (IOL_PUSHPULL_OUT << ((PWM_PIN_INDEX2 % 2) * 4));
    PWM_PORT_INDEX2 &= ~(0x01 << PWM_PIN_INDEX2);

    //PWM0通道映射P05口
    PWM0_MAP = PWM_MAP_PORT_INDEX1 | PWM_MAP_PIN_INDEX1;
    //PWM01通道映射P06口
    PWM01_MAP = PWM_MAP_PORT_INDEX1 | PWM_MAP_PIN_INDEX2;
    //PWM0为高有效，时钟Fosc
    PWM0C = PWM0_IEEN | PWM0_PWM0S_0H1H | PWM0_CK0_FOSC;
    PWM0EN = 0;

    //PWM0 频率 = (Fosc/PWM分频)/[PWM0PH:PWM0PL]
    PWM0PH = (PMW0_PERIOD >> 8);
    PWM0PL = PMW0_PERIOD;

    /*
        //PWM0 占空比 = (PWM0PH:PWM0PL) * 50%
        PWM0DH = (PWM0_DUTY >> 8);
        PWM0DL = PWM0_DUTY;
        //死区调节的是PWM01相对于PWM0左右各缩减的时间(实际就是占空比时间)
        //因此死区时间必须远远小于占空比时间,否则将影响占空比
        //独立输出模式时,死区时间被作为PWM01的占空比寄存器
        PWM0DTH = (PWM0_DEAD >> 8);
        PWM0DTL = PWM0_DEAD;
    */
}
/***************************************************************************************
* @功能   PWM0 互补模式输出开启,占空比调整
* @说明
* @参数
* @返回值
* @注
***************************************************************************************/
void Pwm0CPM_TurnOn(void)
{
    u16_pwm0_period_cnt = 0;
    u16_pwm0_duty = PWM0_DUTY;

    PWM0DH = (PWM0_DUTY >> 8);
    PWM0DL = PWM0_DUTY;
    PWM0DTH = (PWM0_DEAD >> 8);
    PWM0DTL = PWM0_DEAD;
    //清除PWM0中断标志
    PWM0C &= ~PWM0_IFSET;
    PWM0EN = PWM0_PWM0M_CPM + PWM0_PWM01_OENEN + PWM0_PWM0_OENEN + PWM0_PWM0_EN;
}
/**************************************************************************************/
void Pwm0CPM_DutyChange(u16 u16_duty)
{
    //duty
    PWM0DH = u16_duty >> 8;
    PWM0DL = u16_duty;
    //dead time,duty 的5%
    PWM0DTH = (u16_duty * 5 / 100) >> 8;
    PWM0DTL = (u16_duty * 5 / 100);
}
/***************************************************************************************
* @功能   PWM0 独立模式输出开启,占空比调整
* @说明
* @参数
* @返回值
* @注
***************************************************************************************/
void Pwm0IDP_TurnOn(void)
{
    u16_pwm0_period_cnt = 0;
    u16_pwm0_duty = PWM0_DUTY;
    u16_pwm01_duty = PWM01_DUTY;

    PWM0DH = (PWM0_DUTY >> 8);
    PWM0DL = PWM0_DUTY;
    PWM0DTH = (PWM01_DUTY >> 8);
    PWM0DTL = PWM01_DUTY;
    //清除PWM0中断标志
    PWM0C &= ~PWM0_IFSET;
    PWM0EN = PWM0_PWM0M_IDP + PWM0_PWM01_OENEN + PWM0_PWM0_OENEN + PWM0_PWM0_EN;
}
/**************************************************************************************/
void Pwm0IDP_DutyChange(u16 u16_duty)
{
    PWM0DH = u16_duty >> 8;
    PWM0DL = u16_duty;
}
/**************************************************************************************/
void Pwm01IDP_DutyChange(u16 u16_duty)
{
    PWM0DTH = u16_duty >> 8;
    PWM0DTL = u16_duty;
}
/***************************************************************************************
* @功能   PWM0 输出关闭
* @说明
* @参数
* @返回值
* @注
***************************************************************************************/
void Pwm0_Turnoff(void)
{
    PWM0EN = 0;

    PWM_PORT_INDEX1 &= ~(0x01 << PWM_PIN_INDEX1);
    PWM_PORT_INDEX2 &= ~(0x01 << PWM_PIN_INDEX2);
}
/**************************************************************************************/



///***************************************************************************************
//* @功能   硬体 PWM1 初始化
//* @说明
//* @参数
//* @返回值
//* @注
//***************************************************************************************/
//void Pwm1_Config(void)
//{
//  //定义 INDEX3&INDEX4 两路输出在PMW1模块的PMW1和PWM11
//  PWM_PORT_M_INDEX3 &= ~(0x0f << ((PWM_PIN_INDEX3%2)*4));
//  PWM_PORT_M_INDEX3 |=  (IOL_PUSHPULL_OUT << ((PWM_PIN_INDEX3%2)*4));
//  PWM_PORT_INDEX3 &= ~(0x01 << PWM_PIN_INDEX3);
//
//  PWM_PORT_M_INDEX4 &= ~(0x0f << ((PWM_PIN_INDEX4%2)*4));
//  PWM_PORT_M_INDEX4 |=  (IOL_PUSHPULL_OUT << ((PWM_PIN_INDEX4%2)*4));
//  PWM_PORT_INDEX4 &= ~(0x01 << PWM_PIN_INDEX4);
//
//  //PWM1通道映射P23口
//  PWM1_MAP = PWM_MAP_PORT_INDEX3 | PWM_MAP_PIN_INDEX3;
//  //PWM11通道映射P24口
//  PWM11_MAP = PWM_MAP_PORT_INDEX4 | PWM_MAP_PIN_INDEX4;
//  //PWM1为高有效，时钟Fosc
//  PWM1C = PWM1_PWM1S_0H1H | PWM1_CK1_FOSC;
//  PWM1EN = 0;
//
//  //PWM1 频率 = (Fosc/PWM分频)/[PWM1PH:PWM1PL]
//  PWM1PH = (PMW1_PERIOD >> 8);
//  PWM1PL = PMW1_PERIOD;
//
///*
//  PWM1DH = (PWM1_DUTY >> 8);
//  PWM1DL = PWM1_DUTY;
//  PWM1DTH = (PWM1_DEAD >> 8);
//  PWM1DTL = PWM1_DEAD;
//*/
//}
///***************************************************************************************
//* @功能   PWM1 互补模式输出开启,占空比调整
//* @说明
//* @参数
//* @返回值
//* @注
//***************************************************************************************/
//void Pwm1CPM_TurnOn(void)
//{
//  u16_pwm1_duty = PWM1_DUTY;
//
//  PWM1DH = (PWM1_DUTY >> 8);
//  PWM1DL = PWM1_DUTY;
//  PWM1DTH = (PWM1_DEAD >> 8);
//  PWM1DTL = PWM1_DEAD;
//
//  PWM1EN = PWM1_PWM1M_CPM + PWM1_PWM11_OENEN + PWM1_PWM1_OENEN + PWM1_PWM1_EN;
//}
///**************************************************************************************/
//void Pwm1CPM_DutyChange(u16 u16_duty)
//{
//  //duty
//  PWM1DH = u16_duty >> 8;
//  PWM1DL = u16_duty;
//  //dead time,duty 的5%
//  PWM1DTH = (u16_duty * 5 / 100) >> 8;
//  PWM1DTL = (u16_duty * 5 / 100);
//}
///***************************************************************************************
//* @功能   PWM1 独立模式输出开启,占空比调整
//* @说明
//* @参数
//* @返回值
//* @注
//***************************************************************************************/
//void Pwm1IDP_TurnOn(void)
//{
//  u16_pwm1_duty = PWM1_DUTY;
//  u16_pwm11_duty = PWM11_DUTY;
//
//  PWM1DH = (PWM1_DUTY >> 8);
//  PWM1DL = PWM1_DUTY;
//  PWM1DTH = (PWM11_DUTY >> 8);
//  PWM1DTL = PWM11_DUTY;
//
//  PWM1EN = PWM1_PWM1M_IDP + PWM1_PWM11_OENEN + PWM1_PWM1_OENEN + PWM1_PWM1_EN;
//}
///**************************************************************************************/
//void Pwm1IDP_DutyChange(u16 u16_duty)
//{
//  PWM1DH = u16_duty >> 8;
//  PWM1DL = u16_duty;
//}
///**************************************************************************************/
//void Pwm11IDP_DutyChange(u16 u16_duty)
//{
//  PWM1DTH = u16_duty >> 8;
//  PWM1DTL = u16_duty;
//}
///***************************************************************************************
//* @功能   PWM1 输出关闭
//* @说明
//* @参数
//* @返回值
//* @注
//***************************************************************************************/
//void Pwm1_Turnoff(void)
//{
//  PWM1EN = 0;
//
//  PWM_PORT_INDEX3 &= ~(0x01 << PWM_PIN_INDEX3);
//  PWM_PORT_INDEX4 &= ~(0x01 << PWM_PIN_INDEX4);
//}
///**************************************************************************************/



///***************************************************************************************
//* @功能   硬体 PWM2 初始化
//* @说明
//* @参数
//* @返回值
//* @注
//***************************************************************************************/
//void Pwm2_Config(void)
//{
//  //定义 INDEX3&INDEX4 两路输出在PMW1模块的PMW1和PWM11
//  PWM_PORT_M_INDEX5 &= ~(0x0f << ((PWM_PIN_INDEX5%2)*4));
//  PWM_PORT_M_INDEX5 |=  (IOL_PUSHPULL_OUT << ((PWM_PIN_INDEX5%2)*4));
//  PWM_PORT_INDEX5 &= ~(0x01 << PWM_PIN_INDEX5);
//
//  PWM_PORT_M_INDEX6 &= ~(0x0f << ((PWM_PIN_INDEX6%2)*4));
//  PWM_PORT_M_INDEX6 |=  (IOL_PUSHPULL_OUT << ((PWM_PIN_INDEX6%2)*4));
//  PWM_PORT_INDEX6 &= ~(0x01 << PWM_PIN_INDEX6);
//
//  //PWM2通道映射P21口
//  PWM2_MAP = PWM_MAP_PORT_INDEX5 | PWM_MAP_PIN_INDEX5;
//  //PWM21通道映射P03口
//  PWM21_MAP = PWM_MAP_PORT_INDEX6 | PWM_MAP_PIN_INDEX6;
//  //PWM2为高有效，时钟Fosc
//  PWM2C = PWM2_PWM2S_0H1H | PWM2_CK2_FOSC;
//  PWM2EN = 0;
//
//  //PWM2 频率 = (Fosc/PWM分频)/[PWM2PH:PWM2PL]
//  PWM2PH = (PMW2_PERIOD >> 8);
//  PWM2PL = PMW2_PERIOD;
//
///*
//  PWM2DH = (PWM2_DUTY >> 8);
//  PWM2DL = PWM2_DUTY;
//  PWM2DTH = (PWM2_DEAD >> 8);
//  PWM2DTL = PWM2_DEAD;
//*/
//}
///***************************************************************************************
//* @功能   PWM2 互补模式输出开启,占空比调整
//* @说明
//* @参数
//* @返回值
//* @注
//***************************************************************************************/
//void Pwm2CPM_TurnOn(void)
//{
//  u16_pwm2_duty = PWM2_DUTY;
//
//  PWM2DH = (PWM2_DUTY >> 8);
//  PWM2DL = PWM2_DUTY;
//  PWM2DTH = (PWM2_DEAD >> 8);
//  PWM2DTL = PWM2_DEAD;
//
//  PWM2EN = PWM2_PWM2M_CPM + PWM2_PWM21_OENEN + PWM2_PWM2_OENEN + PWM2_PWM2_EN;
//}
///**************************************************************************************/
//void Pwm2CPM_DutyChange(u16 u16_duty)
//{
//  //duty
//  PWM2DH = u16_duty >> 8;
//  PWM2DL = u16_duty;
//  //dead time,duty 的10%
//  PWM2DTH = (u16_duty * 10 / 100) >> 8;
//  PWM2DTL = (u16_duty * 10 / 100);
//}
///***************************************************************************************
//* @功能   PWM2 独立模式输出开启,占空比调整
//* @说明
//* @参数
//* @返回值
//* @注
//***************************************************************************************/
//void Pwm2IDP_TurnOn(void)
//{
//  u16_pwm2_duty = PWM2_DUTY;
//  u16_pwm21_duty = PWM21_DUTY;
//
//  PWM2DH = (PWM2_DUTY >> 8);
//  PWM2DL = PWM2_DUTY;
//  PWM2DTH = (PWM21_DUTY >> 8);
//  PWM2DTL = PWM21_DUTY;
//
//  PWM2EN = PWM2_PWM2M_IDP + PWM2_PWM21_OENEN + PWM2_PWM2_OENEN + PWM2_PWM2_EN;
//}
///**************************************************************************************/
//void Pwm2IDP_DutyChange(u16 u16_duty)
//{
//  PWM2DH = u16_duty >> 8;
//  PWM2DL = u16_duty;
//}
///**************************************************************************************/
//void Pwm21IDP_DutyChange(u16 u16_duty)
//{
//  PWM2DTH = u16_duty >> 8;
//  PWM2DTL = u16_duty;
//}
///***************************************************************************************
//* @功能   PWM1 输出关闭
//* @说明
//* @参数
//* @返回值
//* @注
//***************************************************************************************/
//void Pwm2_Turnoff(void)
//{
//  PWM2EN = 0;
//
//  PWM_PORT_INDEX5 &= ~(0x01 << PWM_PIN_INDEX5);
//  PWM_PORT_INDEX6 &= ~(0x01 << PWM_PIN_INDEX6);
//}
///**************************************************************************************/