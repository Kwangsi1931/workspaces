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
#ifdef  _SPI_
#define _SPI_
#else
#define _SPI_ extern
#endif
#include "HC89S003F4.h"
#include "app_cfg"
/**************************************************************************************/
/* 控制寄存器 SPCTL(默认0) */
#define SPI_SSIG            BIT7        //0/1: SS脚使能 / 普通IO
#define SPI_SPEN            BIT6        //0/1: 禁止 / 使能 SPI模块
#define SPI_DORD            BIT5        //0/1: MSB先发送 / LSB先发送
#define SPI_MSTR            BIT4        //0/1: 从机模式 / 主机模式
#define SPI_CPOL            BIT3        //0/1: SCK空闲时低电平 / 高电平
#define SPI_CPHA            BIT2        //0/1: 数据在SPI时钟的第一个 / 第二个 边沿采样
#define SPI_SPR_FOSC4       B0000_0000  //时钟速率选择:Fosc/4
#define SPI_SPR_FOSC16      B0000_0001  //             Fosc/16
#define SPI_SPR_FOSC64      B0000_0010  //             Fosc/64
#define SPI_SPR_FOSC128     B0000_0011  //             Fosc/128

/* 状态寄存器 SPSTAT(默认0) */
#define SPI_SPIF            BIT7        //0/1: 传输完成标,软件写1清0 / 接收完成硬件置1
#define SPI_WCOL            BIT6        //0/1: 写冲突标志,软件写1清0 / 传输过程中对SPDAT执行写操作置1
#define SPI_RXOV            BIT5        //0/1: 接收溢出标志,软件写1清0 / 发生接收溢出硬件置1
#define SPI_MODF            BIT4        //0/1: 模式故障标志,软件写1清0 / SS PIN电平与SPI模式不一致时置1

/* SPI 数据寄存器 SPDAT(默认0) */
/**************************************************************************************/

/**************************************************************************************/
/* 应用定义SPI PIN */
//#define   SPI_PIN_SS                  7
//#define   SPI_PORT_SS                 P2
//#define   SPI_PORT_M_SS               P2M3

#define SPI_PIN_SCK                 4
#define SPI_PORT_SCK                P0
#define SPI_PORT_M_SCK              P0M2
//MOSI->主输出
#define SPI_PIN_MOSI                2
#define SPI_PORT_MOSI               P0
#define SPI_PORT_M_MOSI             P0M1
//MISO->主输入
#define SPI_PIN_MISO                7
#define SPI_PORT_MISO               P0
#define SPI_PORT_M_MISO             P0M3

//#define   SPI_MAP_PORT_SS             MAP_RW_PORT_P2
//#define   SPI_MAP_PIN_SS              MAP_RW_PIN_7
#define SPI_MAP_PORT_SCK            MAP_RW_PORT_P0
#define SPI_MAP_PIN_SCK             MAP_RW_PIN_4
#define SPI_MAP_PORT_MOSI           MAP_RW_PORT_P0
#define SPI_MAP_PIN_MOSI            MAP_RW_PIN_2
#define SPI_MAP_PORT_MISO           MAP_RW_PORT_P0
#define SPI_MAP_PIN_MISO            MAP_RW_PIN_7
/**************************************************************************************/
#define SPI_SEND_NUM                4
#define SPI_RECEIVE_NUN             4

_SPI_ u8 u8_spi_send_buf[SPI_SEND_NUM];
_SPI_ u8 u8_spi_receive_buf[SPI_RECEIVE_NUN];
_SPI_ u8 u8_spi_receive_cnt;
/**************************************************************************************/
_SPI_ void Spi_Master_Config(void);
_SPI_ void Spi_Master_SendData(u8 u8_length, u8 *u8_data);
_SPI_ void Spi_Master_ReceiveData(u8 u8_length, u8 *u8_data);

_SPI_ void Spi_Slave_Config(void);
_SPI_ void Spi_Slave_ReceiveData(u8 *u8_length, u8 *u8_data);
/**************************************************************************************/
