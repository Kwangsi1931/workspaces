/**
*   ************************************************************************************
*                               普芯达电子有限公司
*                               www.chipswinner.com
*   ************************************************************************************
*   @Demo   Version     V1.0.0.0
*   @Date               2018.8.23
*   ************************************************************************************
**/

/**************************************************************************************/
#ifdef  _IIC_
#define _IIC_
#else
#define _IIC_ extern
#endif
#include "HC89S003F4.h"
#include "app_cfg"
/**************************************************************************************/
/* 控制寄存器 IICCON(默认值0) */
#define IIC_CLK_256             0           //IIC时钟选择:Fosc/256
#define IIC_CLK_224             B0000_0001  //            Fosc/224
#define IIC_CLK_192             B0000_0010  //            Fosc/192
#define IIC_CLK_160             B0000_0011  //            Fosc/160
#define IIC_CLK_960             B1000_0000  //            Fosc/960
#define IIC_CLK_120             B1000_0001  //            Fosc/120
#define IIC_CLK_60              B1000_0010  //            Fosc/60
#define IIC_CLK_T5              B1000_0011  //            T5溢出率/8
#define IIC_EN                  BIT6        //启动 IIC 模块
#define IIC_STA_EN              BIT5        //产生起始信号
#define IIC_STO_EN              BIT4        //主机模式时产生停止信号
#define IIC_SI_INT              BIT3        //0/1: 没有 / 产生 串行中断标志位
#define IIC_AA                  BIT2        //0/1: 回复NACK(SDA 上为高电平) / 回复ACK(SDA上为低电平)

/* IIC 状态寄存器 IICSTA(只读,默认值F8) */
/* IIC 状态码,共有26个可能的状态码,状态码中除 0F8H 外都可置 SI 标志 */
#define IIC_R_IICSTA_08H        0x08        //主机START信号发送结束
#define IIC_R_IICSTA_18H        0x18        //主机发送从机地址结束
#define IIC_R_IICSTA_28H        0x28        //主机发送结束
#define IIC_R_IICSTA_40H        0x40
#define IIC_R_IICSTA_50H        0x50
#define IIC_R_IICSTA_58H        0x58


/* IIC 数据寄存器IICDAT(默认值0) */

/* IIC 地址寄存器IICADR(默认值0) */
#define IIC_MODE_SLAVE_ADDR         0xFE        //从机模式,设备的从机地址;主机模式,该值无影响

/**************************************************************************************/


/**************************************************************************************/
/* 应用定义IIC PIN */
#define IIC_PIN_SCL                 5
#define IIC_PORT_SCL                P2
#define IIC_PORT_M_SCL              P2M2

#define IIC_PIN_SDA                 6
#define IIC_PORT_SDA                P2
#define IIC_PORT_M_SDA              P2M3

#define IIC_MAP_PORT_SCL            MAP_RW_PORT_P2
#define IIC_MAP_PIN_SCL             MAP_RW_PIN_5
#define IIC_MAP_PORT_SDA            MAP_RW_PORT_P2
#define IIC_MAP_PIN_SDA             MAP_RW_PIN_6
/**************************************************************************************/
#define IIC_CMD_WRITE               0x00
#define IIC_CMD_READ                0x01
#define IIC_SLAVE_ADDR              0xA0            //从机地址


#define IIC_SEND_NUM                4
#define IIC_RECEIVE_NUN             4
_IIC_ u8 u8_iic_send_buf[IIC_SEND_NUM];
_IIC_ u8 u8_iic_receive_buf[IIC_RECEIVE_NUN];



/**************************************************************************************/
_IIC_ void Iic_Master_Config(void);
_IIC_ void Iic_Master_SendData(u8 u8_adr, u8 u8_length, u8 *u8_data);
_IIC_ void Iic_Master_ReadData(u8 u8_adr, u8 u8_length, u8 *u8_data);

/**************************************************************************************/
