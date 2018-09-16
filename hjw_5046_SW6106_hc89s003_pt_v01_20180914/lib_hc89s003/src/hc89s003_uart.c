/**
*   ************************************************************************************
*                               普芯达电子有限公司
*                               www.chipswinner.com
*   ************************************************************************************
*   @Demo   Version     V1.0.0.0
*   @Date               2018.8.15
*   ************************************************************************************
**/

/**************************************************************************************/
#define _UART_
#include "uart.h"
#include "gpio.h"
#include "timer.h"
#include "register.h"
#include ".\Main\com.h"
/***************************************************************************************/


/***************************************************************************************
* @功能    初始化UART1
* @说明
* @参数
* @返回值
* @注
***************************************************************************************/
void Uart1_Config(void)
{
    //TX PIN 设置推挽输出低
    UART1_PORT_M_TX &= ~(0x0f << ((UART1_PIN_TX % 2) * 4));
    UART1_PORT_M_TX |=  (IOL_PUSHPULL_OUT << ((UART1_PIN_TX % 2) * 4));
    UART1_PORT_TX &= ~(0x01 << UART1_PIN_TX);
    //RX PIN 设置输入上拉
    UART1_PORT_M_RX &= ~(0x0f << ((UART1_PIN_RX % 2) * 4));
    UART1_PORT_M_RX |=  (IOL_PULLUP_IN << ((UART1_PIN_RX % 2) * 4));
    //UART TX通道映射P00口
    TXD_MAP = UART1_MAP_PORT_TX | UART1_MAP_PIN_TX;
    //UART RX通道映射P01口
    RXD_MAP = UART1_MAP_PORT_RX | UART1_MAP_PIN_RX;

    //波特率 => 9600 = T4时钟源频率/(16*(65536-[TH4:TL4]))
    //32000000/(16*(65536-65328)) ~= 9615 误差约0.16%
    //FF30->9600;FF98->19200;FFEF->115200
    TH4 = 0xFF;
    TL4 = 0xEF;
    //设置T4工作模式:作为UART1波特率发生器,时钟Fosc不分频,使能T4
    T4CON = TIM_T4PS_1 | TIM_T4M_1 | TIM_TR4_EN | TIM_T4CLKS_FOSC;
    BRTSEL = UART_UART1SEL_T4;

    //UART1工作方式1,允许串行接收
    SCON2 = UART1_SM1SM0_MODE1;
    SCON = UART1_REN_EN;

    //允许UART1中断
    IE |= INT_ES1_EN;

    u8_uart1_tx_data_index = 0;
    u8_uart1_rx_data_index = 0;
}
/**************************************************************************************/


/***************************************************************************************
* @功能    UART1发送数据
* @说明
* @参数     u8_length ： 发送数据长度(取值范围：0x00-0xFF)
* @参数     *u8_data_addr ：读取数据存放的区域首地址
* @返回值   无
* @注       无
***************************************************************************************/
void Uart1_SendData(u8 u8_length, u8 *u8_data_buf)
{
    //连续发送所有数据
    u8 i;

    for(i = 0; i < u8_length; i++)
    {
        SBUF = u8_data_buf[i];

        while(!(SCON & UART1_INT_T1));

        SCON &= ~UART1_INT_T1;
    }
}
/**************************************************************************************/
void Uart1_SendData_Start(u8 *u8_index, u8 *u8_data_buf)
{
    //发送第一个字节,其它字节中断中发送
    *u8_index = 0;
    SBUF = *u8_data_buf;
}
/**************************************************************************************/
void Uart1_SendData_Int(u8 *u8_index, u8 *u8_data_buf)
{
    //UART启动发送第一个BYTE数据后,其余数据在中断中发送
    if(SCON & UART1_INT_T1)
    {
        SCON &= ~UART1_INT_T1;
        *u8_index += 1;

        if(*u8_index < UART1_TX_NUM)
        {
            SBUF = u8_data_buf[*u8_index];
        }
    }
}
/**************************************************************************************/


/***************************************************************************************
* @功能    在UART1中断中获取 UART_RX_NUM 个数据,并设置数据标志
* @说明    函数在UART1中断中调用
* @参数
* @返回值
* @注
***************************************************************************************/
void Uart1_ReceiveData(u8 *u8_index, u8 *u8_data_buf)
{
    //接收数据
    /*
        if(SCON & UART1_INT_R1)
        {   //按数据长度接收数据
            SCON &= ~UART1_INT_R1;
            u8_data_buf[*u8_index] = SBUF;
            *u8_index += 1;
            if(*u8_index >= UART1_RX_NUM)
            {
                *u8_index = 0;
                b_uart1_rx_end = FLAG_EN;
            }
        }
    */
    u8 buf;

    if(SCON & UART1_INT_R1)
    {
        //按协议格式接收数据
        SCON &= ~UART1_INT_R1;
        buf = SBUF;

        if(*u8_index >= UART1_RX_NUM)
        {
            //数据存储指针异常
            *u8_index = 0;
        }
        else
        {
            if(0x78 == buf)
            {
                //数据开始
                *u8_index = 0;
                u8_data_buf[0] = 0x78;
            }
            else
            {
                *u8_index += 1;
                u8_data_buf[*u8_index] = buf;

                if(0xff == buf)
                {
                    //数据结束
                    b_uart1_rx_end = FLAG_EN;
                    *u8_index = 0;
                }
            }
        }
    }
}
/**************************************************************************************/
