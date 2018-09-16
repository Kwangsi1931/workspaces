/**
*   ************************************************************************************
*                               普芯达电子有限公司
*                               www.chipswinner.com
*   ************************************************************************************
*   @Demo   Version     V1.0.0.0
*   @Date               2018.8.23
*   ************************************************************************************
**/
/***************************************************************************************

***************************************************************************************/


/**************************************************************************************/
#define _IIC_
#include "iic.h"
#include "gpio.h"

/**************************************************************************************/



/***************************************************************************************
* @功能    初始化IIC
* @说明
* @参数
* @返回值
* @注
***************************************************************************************/
void Iic_Master_Config(void)
{
    //SCL PIN 设置推挽输出
    IIC_PORT_M_SCL &= ~(0x0f << ((IIC_PIN_SCL % 2) * 4));
    IIC_PORT_M_SCL |=  (IOL_PUSHPULL_OUT << ((IIC_PIN_SCL % 2) * 4));
    //SDA PIN 设置开漏带上拉输出
    IIC_PORT_M_SDA &= ~(0x0f << ((IIC_PIN_SDA % 2) * 4));
    IIC_PORT_M_SDA |=  (IOL_OPENDRAIN_PULL_OUT << ((IIC_PIN_SDA % 2) * 4));
    //UART TX通道映射P25口
    SCL_MAP = IIC_MAP_PORT_SCL | IIC_MAP_PIN_SCL;
    //UART RX通道映射P26口
    SDA_MAP = IIC_MAP_PORT_SDA | IIC_MAP_PIN_SDA;

    //启动IIC模块,时钟Fose/160 = 200K
    IICCON = IIC_CLK_160 | IIC_EN;
}
/**************************************************************************************/


/***************************************************************************************
* @功能    发送数据(主机)
* @说明
* @参数
* @返回值
* @注
***************************************************************************************/
void Iic_Master_SendData(u8 u8_adr, u8 u8_length, u8 *u8_data)
{
    u8 i;

    //清除中断标志位
    IICCON &= ~ (IIC_SI_INT + IIC_STO_EN);
    //起始位发送起始信号
    IICCON |= IIC_STA_EN;

    while((!(IICCON & IIC_SI_INT)) && (IICSTA != IIC_R_IICSTA_08H));

    //停止起始位信号
    IICCON &= ~ IIC_STA_EN;

    //清除中断标志位
    IICCON &= ~ IIC_SI_INT;
    //写从机地址
    IICDAT = (IIC_SLAVE_ADDR + IIC_CMD_WRITE);

    while((!(IICCON & IIC_SI_INT)) && (IICSTA != IIC_R_IICSTA_18H));

    //清除中断标志位
    IICCON &= ~ IIC_SI_INT;
    //写访问地址
    IICDAT = u8_adr;

    while((!(IICCON & IIC_SI_INT)) && (IICSTA != IIC_R_IICSTA_28H));

    //写数据
    for(i = 0; i < u8_length; i++)
    {
        //清除中断标志位
        IICCON &= ~ IIC_SI_INT;
        IICDAT = u8_data[i];

        while((!(IICCON & IIC_SI_INT)) && (IICSTA != IIC_R_IICSTA_28H));
    }

    //清除中断标志位
    IICCON &= ~ IIC_SI_INT;
    //停止位发送起始信号
    IICCON |= IIC_STO_EN;
    //清除中断标志位
    IICCON &= ~ (IIC_SI_INT + IIC_STO_EN);
}
/**************************************************************************************/


/***************************************************************************************
* @功能    读取数据(主机)
* @说明
* @参数
* @返回值
* @注
***************************************************************************************/
void Iic_Master_ReadData(u8 u8_adr, u8 u8_length, u8 *u8_data)
{
    u8 i;

    //清除中断标志位
    IICCON &= ~ (IIC_SI_INT + IIC_STO_EN);
    //起始位发送起始信号
    IICCON |= IIC_STA_EN;

    //等待START信号发送完毕
    while((!(IICCON & IIC_SI_INT)) && (IICSTA != IIC_R_IICSTA_08H));

    //停止起始位信号
    IICCON &= ~ IIC_STA_EN;

    //清除中断标志位
    IICCON &= ~ IIC_SI_INT;
    //写从机地址
    IICDAT = (IIC_SLAVE_ADDR + IIC_CMD_WRITE);

    //等待从机地址发送完毕
    while((!(IICCON & IIC_SI_INT)) && (IICSTA != IIC_R_IICSTA_18H));

    //清除中断标志位
    IICCON &= ~ IIC_SI_INT;
    //写访问地址
    IICDAT = u8_adr;

    while((!(IICCON & IIC_SI_INT)) && (IICSTA != IIC_R_IICSTA_28H));

    //清除中断标志位
    IICCON &= ~ IIC_SI_INT;
    //起始位发送起始信号
    IICCON |= IIC_STA_EN;

    //等待START信号发送完毕
    while((!(IICCON & IIC_SI_INT)) && (IICSTA != IIC_R_IICSTA_08H));

    //停止起始位信号
    IICCON &= ~ IIC_STA_EN;

    //清除中断标志位
    IICCON &= ~ IIC_SI_INT;
    //写入从机地址+读指令
    IICDAT = (IIC_SLAVE_ADDR + IIC_CMD_READ);

    //等待从机地址发送完毕
    while((!(IICCON & IIC_SI_INT)) && (IICSTA != IIC_R_IICSTA_40H));

    //写数据
    for(i = 0; i < u8_length; i++)
    {
        //回复ACK
        IICCON |= IIC_AA;
        //清除中断标志位
        IICCON &= ~ IIC_SI_INT;

        while((!(IICCON & IIC_SI_INT)) && (IICSTA != IIC_R_IICSTA_50H));

        u8_data[i] = IICDAT;
    }

    //回复NACK
    IICCON &= ~IIC_AA;
    //清除中断标志位
    IICCON &= ~ IIC_SI_INT;

    while((!(IICCON & IIC_SI_INT)) && (IICSTA != IIC_R_IICSTA_58H));

    //清除中断标志位
    IICCON &= ~ IIC_SI_INT;
    //停止位发送起始信号
    IICCON |= IIC_STO_EN;
    //清除中断标志位
    IICCON &= ~ (IIC_SI_INT + IIC_STO_EN);
}
/**************************************************************************************/

