/**
*   ************************************************************************************
*                               普芯达电子有限公司
*                               www.chipswinner.com
*   ************************************************************************************
*   @Demo   Version     V1.0.0.0
*   @Date               2018.8.27
*   ************************************************************************************
**/

/**************************************************************************************/
#define _SPI_
#include "spi.h"
#include "gpio.h"
#include "register.h"
/**************************************************************************************/



/***************************************************************************************
* @功能    初始化SPI(主机)
* @说明
* @参数
* @返回值
* @注
***************************************************************************************/
void Spi_Master_Config(void)
{
    //  //SS PIN 设置推挽输出
    //  SPI_PORT_M_SS &= ~(0x0f << ((SPI_PIN_SS%2)*4));
    //  SPI_PORT_M_SS |=  (IOL_PUSHPULL_OUT << ((SPI_PIN_SS%2)*4));
    //SCK PIN 设置推挽输出
    SPI_PORT_M_SCK &= ~(0x0f << ((SPI_PIN_SCK % 2) * 4));
    SPI_PORT_M_SCK |=  (IOL_PUSHPULL_OUT << ((SPI_PIN_SCK % 2) * 4));
    //MOSI PIN 设置推挽输出
    SPI_PORT_M_MOSI &= ~(0x0f << ((SPI_PIN_MOSI % 2) * 4));
    SPI_PORT_M_MOSI |=  (IOL_PUSHPULL_OUT << ((SPI_PIN_MOSI % 2) * 4));
    //MISO PIN 设置SMT输入
    SPI_PORT_M_MISO &= ~(0x0f << ((SPI_PIN_MISO % 2) * 4));
    SPI_PORT_M_MISO |=  (IOL_SMTIN << ((SPI_PIN_MISO % 2) * 4));

    //  //SS PIN ->P27
    //  SS_MAP = SPI_MAP_PORT_SS | SPI_MAP_PIN_SS;
    //SCK PIN ->P04
    SCK_MAP = SPI_MAP_PORT_SCK | SPI_MAP_PIN_SCK;
    //MOSI PIN ->P02
    MOSI_MAP = SPI_MAP_PORT_MOSI | SPI_MAP_PIN_MOSI;
    //MISO PIN ->P07
    MISO_MAP = SPI_MAP_PORT_MISO | SPI_MAP_PIN_MISO;

    //数据寄存器清0
    SPDAT = 0;
    //状态寄存器清0
    SPSTAT = 0;
    //主机模式(三线),时钟Fosc/128
    SPCTL = SPI_SSIG | SPI_SPEN | SPI_MSTR | SPI_CPHA | SPI_SPR_FOSC128;
}
/**************************************************************************************/


/***************************************************************************************
* @功能    主机发送数据(主机)
* @说明
* @参数
* @返回值
* @注
***************************************************************************************/
void Spi_Master_SendData(u8 u8_length, u8 *u8_data)
{
    u8 i;

    for(i = 0; i < u8_length; i++)
    {
        SPSTAT = SPI_SPIF | SPI_WCOL;
        SPDAT = u8_data[i];

        while(!(SPSTAT & SPI_SPIF));
    }
}
/**************************************************************************************/


/***************************************************************************************
* @功能    主机读数据(主机)
* @说明
* @参数
* @返回值
* @注
***************************************************************************************/
void Spi_Master_ReceiveData(u8 u8_length, u8 *u8_data)
{
    u8 i;

    for(i = 0; i < u8_length; i++)
    {
        SPSTAT = SPI_SPIF | SPI_WCOL;
        SPDAT = 0;

        while(!(SPSTAT & SPI_SPIF));

        SPSTAT = SPI_SPIF | SPI_WCOL;
        u8_data[i] = SPDAT;
    }
}
/**************************************************************************************/


/***************************************************************************************
* @功能    初始化SPI(从机)
* @说明
* @参数
* @返回值
* @注
***************************************************************************************/
void Spi_Slave_Config(void)
{
    //  //SS PIN 设置SMT输入
    //  SPI_PORT_M_SS &= ~(0x0f << ((SPI_PIN_SS%2)*4));
    //  SPI_PORT_M_SS |=  (IOL_SMTIN << ((SPI_PIN_SS%2)*4));
    //SCK PIN 设置SMT输入
    SPI_PORT_M_SCK &= ~(0x0f << ((SPI_PIN_SCK % 2) * 4));
    SPI_PORT_M_SCK |=  (IOL_SMTIN << ((SPI_PIN_SCK % 2) * 4));
    //MOSI PIN 设置SMT输入
    SPI_PORT_M_MOSI &= ~(0x0f << ((SPI_PIN_MOSI % 2) * 4));
    SPI_PORT_M_MOSI |=  (IOL_SMTIN << ((SPI_PIN_MOSI % 2) * 4));
    //MISO PIN 设置推挽输出
    SPI_PORT_M_MISO &= ~(0x0f << ((SPI_PIN_MISO % 2) * 4));
    SPI_PORT_M_MISO |=  (IOL_PUSHPULL_OUT << ((SPI_PIN_MISO % 2) * 4));

    //  //SS PIN ->P27
    //  SS_MAP = SPI_MAP_PORT_SS | SPI_MAP_PIN_SS;
    //SCK PIN ->P04
    SCK_MAP = SPI_MAP_PORT_SCK | SPI_MAP_PIN_SCK;
    //MOSI PIN ->P02
    MOSI_MAP = SPI_MAP_PORT_MOSI | SPI_MAP_PIN_MOSI;
    //MISO PIN ->P07
    MISO_MAP = SPI_MAP_PORT_MISO | SPI_MAP_PIN_MISO;

    //数据寄存器清0
    SPDAT = 0;
    //状态寄存器清0
    SPSTAT = 0;
    //从机模式(三线),时钟Fosc/128
    SPCTL = SPI_SSIG | SPI_SPEN | SPI_CPHA | SPI_SPR_FOSC128;

    //允许SPI中断
    IE1 |= INT_ESPI_EN;

    //
    u8_spi_receive_cnt = 0;
}
/**************************************************************************************/


/***************************************************************************************
* @功能    读数据(从机),中断中调用
* @说明
* @参数
* @返回值
* @注
***************************************************************************************/
void Spi_Slave_ReceiveData(u8 *u8_index, u8 *u8_data)
{
    //清除SPI中断
    SPSTAT |= SPI_SPIF;

    if(*u8_index < SPI_RECEIVE_NUN)
    {
        u8_data[*u8_index] = SPDAT;
        *u8_index += 1;
    }

    if(*u8_index >= SPI_RECEIVE_NUN)
    {
        *u8_index = 0;
    }
}
/**************************************************************************************/
