/**
*   ************************************************************************************
*                               普芯达电子有限公司
*                               www.chipswinner.com
*   ************************************************************************************
*   @Demo   Version     V1.0.0.0
*   @Date               2018.7.20
*   ************************************************************************************
**/

/**************************************************************************************/
#include "gpio.h"

/**************************************************************************************/



/***************************************************************************************
* @功能    上电初始化GPIO
* @说明    GPIO设置函数
* @参数    无
* @返回值  无
* @注
***************************************************************************************/
void Gpio_Initial_PowerOn(void)
{
    /*测试IO,所有IO输出高*/
    P0 = 0xff;
    P0M0 = IOH_PULLUP_SMTIN | IOL_PULLUP_IN;
    P0M1 = IOH_PUSHPULL_OUT | IOL_PUSHPULL_OUT;
    P0M2 = IOH_PUSHPULL_OUT | IOL_PUSHPULL_OUT;
    P0M3 = IOH_PUSHPULL_OUT | IOL_PUSHPULL_OUT;

    P1 = 0x03;
    P1M0 = IOH_PUSHPULL_OUT | IOL_PUSHPULL_OUT;

    P2 = 0xff;
    P2M0 = IOH_PUSHPULL_OUT | IOL_PUSHPULL_OUT;
    P2M1 = IOH_T_PUSHPULL_OUT | IOL_PUSHPULL_OUT;
    P2M2 = IOH_T_PUSHPULL_OUT | IOL_T_PUSHPULL_OUT;
    P2M3 = IOH_T_PUSHPULL_OUT | IOL_PUSHPULL_OUT;

    /*
    //P0端口设置,P03调试接口(GF-LINK->TCK)
        P0 = 0x01;
        //P01输入上拉 , P00 推挽输出高
        P0M0 = IOH_PULLUP_IN | IOL_PUSHPULL_OUT;
        //P03输入下拉 , P02 开漏带上拉输出
        P0M1 = IOH_PULLDOWN_IN | IOL_OPENDRAIN_PULL_OUT;
        //P05施密特输入上拉 , P04 开漏输出
        P0M2 = IOH_PULLUP_SMTIN | IOL_OPENDRAIN_OUT;
        //P07施密特输入下拉 , P06 推挽输出低
        P0M3 = IOH_PULLDOWN_SMTIN | IOL_PUSHPULL_OUT;

    //P1端口设置
        P1 = 0x01;
        //P11输入上拉 , P10 推挽输出高
        P1M0 = IOH_PULLUP_IN | IOL_PUSHPULL_OUT;

    //P2端口设置,P21调试接口(GF-LINK->TDO)
        P2 = 0x41;
        //P21输入上拉 , P20 推挽输出高
        P2M0 = IOH_PULLUP_IN | IOL_PUSHPULL_OUT;
        //P23下拉,下拉同时使能 , P22 开漏带上拉输出
        P2M1 = IOH_T_PULLUPDOWN_IN | IOL_OPENDRAIN_PULL_OUT;
        //P25下拉,下拉同时使能, P24 下拉,下拉同时使能
        P2M2 = IOH_T_PULLUPDOWN_IN | IOL_T_PULLUPDOWN_IN;
        //P27施密特输入下拉 , P26 推挽输出高
        P2M3 = IOH_PULLDOWN_SMTIN | IOL_PUSHPULL_OUT;

    //设置端口上拉电阻
        //默认上拉50K
        P0LPU = IO_PULL_RESISTANCE_100K;

    //设置端口消抖
        //默认无消抖功能,消抖时间=FOSC时钟分频*低6位值
        P00DBC = IO_DEBOUNCING_CLOCK_FOSE_4 | 0x20;
        P01DBC = IO_DEBOUNCING_CLOCK_FOSE_4 | 0x20;
        P02DBC = IO_DEBOUNCING_CLOCK_FOSE_4 | 0x20;
    */
}
/**************************************************************************************/



/***************************************************************************************
* @功能    唤醒后初始化IO
* @说明    GPIO设置函数
* @参数    无
* @返回值  无
* @注
***************************************************************************************/
void Gpio_Initial_WakeUp(void)
{


}
/**************************************************************************************/



/***************************************************************************************
* @功能    IDLE前设置IO状态
* @说明    GPIO设置函数
* @参数    无
* @返回值  无
* @注
***************************************************************************************/
void Gpio_Configure_Idle(void)
{


}
/**************************************************************************************/