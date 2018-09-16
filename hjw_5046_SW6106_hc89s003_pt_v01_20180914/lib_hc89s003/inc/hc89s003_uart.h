/**
*   ************************************************************************************
*                               普芯达电子有限公司
*                               www.chipswinner.com
*   ************************************************************************************
*   @Demo   Version     V1.0.0.0
*   @Date               2018.6.22
*   ************************************************************************************
**/

/**************************************************************************************/
#ifdef  _UART_
#define _UART_
#else
#define _UART_ extern
#endif

#include "HC89S003F4.h"
#include "app_cfg"
/**************************************************************************************/
/* 波特率选择寄存器 BRTSEL(默认0) */
#define UART_UART2SEL_T5        0       //UART2波特率选择:定时器5的溢出率
#define UART_UART2SEL_T4        BIT1    //               :定时器4的溢出率
#define UART_UART1SEL_T4        0       //UART1波特率选择:定时器4的溢出率
#define UART_UART1SEL_T5        BIT0    //               :定时器5的溢出率

/* UART1 控制寄存器SCON,SCON2(默认0) */
#define UART1_FE                BIT7    //0/1:无帧错误或软件清0 / 有帧错误,硬件置1
#define UART1_RXROV             BIT6    //0/1:无接收溢出或软件清0 / 接收溢出,硬件置1
#define UART1_TXCOL             BIT5    //0/1:无发送冲突或软件清0 / 有发送冲突,硬件置1
#define UART1_REN_EN            BIT4    //允许串行接收
#define UART1_TB8_DATA0         0       //方式2/3时,发送数据的第9位数据为0
#define UART1_TB8_DATA1         BIT3    //方式2/3时,发送数据的第9位数据为1
#define UART1_RB8_DATA0         0       //方式2/3时,接收数据的第9位数据为0;作为奇偶校验位或地址帧/数据帧的标志位
#define UART1_RB8_DATA1         BIT2    //方式2/3时,接收数据的第9位数据为1;作为奇偶校验位或地址帧/数据帧的标志位
#define UART1_INT_T1            BIT1    //发送中断请求中断标志位:软件清0 / 方式0时,当串行发送数据第8位结束时由硬件自动置1
//                                 其它方式时在停止位开始发送时由硬件置1
#define UART1_INT_R1            BIT0    //接收中断请求中断标志位:软件清0 / 方式0时,当串行接收数据第8位结束时由硬件自动置1
//                                 其它方式时,串行接收到停止位开始时刻由硬件置1

#define UART1_SMOD_FOSC_64      0       //在方式2中,波特率为系统时钟Fosc的1/64
#define UART1_SMOD_FOSC_32      BIT7    //在方式2中,波特率为系统时钟Fosc的1/32
#define UART1_UX6_FOSC_12       0       //方式0时钟为Fosc/12
#define UART1_UX6_FOSC_2        BIT5    //方式0时钟为Fosc/2
#define UART1_SM1SM0_MODE0      0       //串口工作方式:0,同步移位串行方式
#define UART1_SM1SM0_MODE1      B0000_0010  //            :1,8位UART,波特率可变
#define UART1_SM1SM0_MODE2      B0000_0100  //            :2,9位UART
#define UART1_SM1SM0_MODE3      B0000_0110  //            :3,9位UART,波特率可变
#define UART1_SM2_DIS           0       //在方式1时:不检测停止位,停止位无论是0还是1都会置位RI
//在方式2和3时:不检测第9位,任何字节都会置位RI
#define UART1_SM2_EN            BIT0    //在方式1时:允许停止位确认检验,只有有效的停止位“1”才能置位RI
//在方式2和3时:只有地址字节(第9位=“1”)才能置位RI

/* UART1 数据缓冲寄存器SBUF(默认0) */
/* 写为需要发送的数据，读为接收到的数据 */

/* UART1 自动地址识别SADDR,SADEN (默认0)*/
/* 从机地址寄存器SADDR; 从机地址掩码寄存器 SADEN */

/**************************************************************************************/
/* UART2 与UART1 不同点：
    1. UART2的寄存器存放在扩展SFR中;
    2. UART2只有两种工作方式;
         方式0: 8位UART,可变波特率,异步全双工
         方式1: 9位UART,可变波特率,异步全双工
    3. UART2没有错误检测;
    4. UART2没有自动硬件地址识别;
*/
/* UART2 控制寄存器S2CON,S2CON2(默认0) */
#define UART2_FE                BIT7    //0/1:无帧错误或软件清0 / 有帧错误,硬件置1
#define UART2_REN_DIS           0       //禁止串行接收
#define UART2_REN_EN            BIT4    //允许串行接收
#define UART2_TB8_DATA0         0       //方式1时,发送数据的第9位数据为0
#define UART2_TB8_DATA1         BIT3    //方式1时,发送数据的第9位数据为1
#define UART2_RB8_DATA0         0       //方式1时,接收数据的第9位数据为0;作为奇偶校验位或地址帧/数据帧的标志位
#define UART2_RB8_DATA1         BIT2    //方式1时,接收数据的第9位数据为1;作为奇偶校验位或地址帧/数据帧的标志位
#define UART2_INT_T1            BIT1    //发送中断请求中断标志位:软件清0 / 在停止位开始发送时由硬件置1
#define UART2_INT_R1            BIT0    //接收中断请求中断标志位:软件清0 / 串行接收到停止位开始时刻由硬件置1

#define UART2_SM1_8BIT          0       //8位UART,定时器5的溢出率/16
#define UART2_SM1_9BIT          BIT1    //8位UART,定时器5的溢出率/16
#define UART2_SM2_DIS           0       //在方式0时不检测停止位,停止位无论是0还是1都会置位RI
//在方式1时不检测第9位,第9位无论是0还是1都会置位RI
#define UART2_SM2_EN            BIT0    //在方式0时,只有停止位为1才能置位RI
//在方式1时,只有第9位为1才能置位RI

/* UART2 数据缓冲寄存器S2BUF(默认0) */
/* 写为需要发送的数据，读为接收到的数据 */
/**************************************************************************************/


/**************************************************************************************/
/* 应用定义UART PIN */
#define UART1_PIN_TX                0
#define UART1_PORT_TX               P0
#define UART1_PORT_M_TX             P0M0

#define UART1_PIN_RX                1
#define UART1_PORT_RX               P0
#define UART1_PORT_M_RX             P0M0

#define UART1_MAP_PORT_TX           MAP_RW_PORT_P0
#define UART1_MAP_PIN_TX            MAP_RW_PIN_0
#define UART1_MAP_PORT_RX           MAP_RW_PORT_P0
#define UART1_MAP_PIN_RX            MAP_RW_PIN_1
/**************************************************************************************/
//定义变量
#define UART1_TX_NUM                        5
#define UART1_RX_NUM                        5
_UART_ bit b_uart1_rx_end;
_UART_ u8 u8_uart1_tx_data[UART1_TX_NUM];
_UART_ u8 u8_uart1_tx_data_index;
_UART_ u8 u8_uart1_rx_data[UART1_RX_NUM];
_UART_ u8 u8_uart1_rx_data_index;
/**************************************************************************************/
_UART_ void Uart1_Config(void);
_UART_ void Uart1_SendData(u8 u8_length, u8 *u8_data_addr);
_UART_ void Uart1_SendData_Start(u8 *u8_index, u8 *u8_data_buf);
_UART_ void Uart1_SendData_Int(u8 *u8_index, u8 *u8_data_buf);
_UART_ void Uart1_ReceiveData(u8 *u8_index, u8 *u8_data_buf);
