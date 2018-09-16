/**
*   ************************************************************************************
*                               ��о��������޹�˾
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
/* ������ѡ��Ĵ��� BRTSEL(Ĭ��0) */
#define UART_UART2SEL_T5        0       //UART2������ѡ��:��ʱ��5�������
#define UART_UART2SEL_T4        BIT1    //               :��ʱ��4�������
#define UART_UART1SEL_T4        0       //UART1������ѡ��:��ʱ��4�������
#define UART_UART1SEL_T5        BIT0    //               :��ʱ��5�������

/* UART1 ���ƼĴ���SCON,SCON2(Ĭ��0) */
#define UART1_FE                BIT7    //0/1:��֡����������0 / ��֡����,Ӳ����1
#define UART1_RXROV             BIT6    //0/1:�޽�������������0 / �������,Ӳ����1
#define UART1_TXCOL             BIT5    //0/1:�޷��ͳ�ͻ�������0 / �з��ͳ�ͻ,Ӳ����1
#define UART1_REN_EN            BIT4    //�����н���
#define UART1_TB8_DATA0         0       //��ʽ2/3ʱ,�������ݵĵ�9λ����Ϊ0
#define UART1_TB8_DATA1         BIT3    //��ʽ2/3ʱ,�������ݵĵ�9λ����Ϊ1
#define UART1_RB8_DATA0         0       //��ʽ2/3ʱ,�������ݵĵ�9λ����Ϊ0;��Ϊ��żУ��λ���ַ֡/����֡�ı�־λ
#define UART1_RB8_DATA1         BIT2    //��ʽ2/3ʱ,�������ݵĵ�9λ����Ϊ1;��Ϊ��żУ��λ���ַ֡/����֡�ı�־λ
#define UART1_INT_T1            BIT1    //�����ж������жϱ�־λ:�����0 / ��ʽ0ʱ,�����з������ݵ�8λ����ʱ��Ӳ���Զ���1
//                                 ������ʽʱ��ֹͣλ��ʼ����ʱ��Ӳ����1
#define UART1_INT_R1            BIT0    //�����ж������жϱ�־λ:�����0 / ��ʽ0ʱ,�����н������ݵ�8λ����ʱ��Ӳ���Զ���1
//                                 ������ʽʱ,���н��յ�ֹͣλ��ʼʱ����Ӳ����1

#define UART1_SMOD_FOSC_64      0       //�ڷ�ʽ2��,������Ϊϵͳʱ��Fosc��1/64
#define UART1_SMOD_FOSC_32      BIT7    //�ڷ�ʽ2��,������Ϊϵͳʱ��Fosc��1/32
#define UART1_UX6_FOSC_12       0       //��ʽ0ʱ��ΪFosc/12
#define UART1_UX6_FOSC_2        BIT5    //��ʽ0ʱ��ΪFosc/2
#define UART1_SM1SM0_MODE0      0       //���ڹ�����ʽ:0,ͬ����λ���з�ʽ
#define UART1_SM1SM0_MODE1      B0000_0010  //            :1,8λUART,�����ʿɱ�
#define UART1_SM1SM0_MODE2      B0000_0100  //            :2,9λUART
#define UART1_SM1SM0_MODE3      B0000_0110  //            :3,9λUART,�����ʿɱ�
#define UART1_SM2_DIS           0       //�ڷ�ʽ1ʱ:�����ֹͣλ,ֹͣλ������0����1������λRI
//�ڷ�ʽ2��3ʱ:������9λ,�κ��ֽڶ�����λRI
#define UART1_SM2_EN            BIT0    //�ڷ�ʽ1ʱ:����ֹͣλȷ�ϼ���,ֻ����Ч��ֹͣλ��1��������λRI
//�ڷ�ʽ2��3ʱ:ֻ�е�ַ�ֽ�(��9λ=��1��)������λRI

/* UART1 ���ݻ���Ĵ���SBUF(Ĭ��0) */
/* дΪ��Ҫ���͵����ݣ���Ϊ���յ������� */

/* UART1 �Զ���ַʶ��SADDR,SADEN (Ĭ��0)*/
/* �ӻ���ַ�Ĵ���SADDR; �ӻ���ַ����Ĵ��� SADEN */

/**************************************************************************************/
/* UART2 ��UART1 ��ͬ�㣺
    1. UART2�ļĴ����������չSFR��;
    2. UART2ֻ�����ֹ�����ʽ;
         ��ʽ0: 8λUART,�ɱ䲨����,�첽ȫ˫��
         ��ʽ1: 9λUART,�ɱ䲨����,�첽ȫ˫��
    3. UART2û�д�����;
    4. UART2û���Զ�Ӳ����ַʶ��;
*/
/* UART2 ���ƼĴ���S2CON,S2CON2(Ĭ��0) */
#define UART2_FE                BIT7    //0/1:��֡����������0 / ��֡����,Ӳ����1
#define UART2_REN_DIS           0       //��ֹ���н���
#define UART2_REN_EN            BIT4    //�����н���
#define UART2_TB8_DATA0         0       //��ʽ1ʱ,�������ݵĵ�9λ����Ϊ0
#define UART2_TB8_DATA1         BIT3    //��ʽ1ʱ,�������ݵĵ�9λ����Ϊ1
#define UART2_RB8_DATA0         0       //��ʽ1ʱ,�������ݵĵ�9λ����Ϊ0;��Ϊ��żУ��λ���ַ֡/����֡�ı�־λ
#define UART2_RB8_DATA1         BIT2    //��ʽ1ʱ,�������ݵĵ�9λ����Ϊ1;��Ϊ��żУ��λ���ַ֡/����֡�ı�־λ
#define UART2_INT_T1            BIT1    //�����ж������жϱ�־λ:�����0 / ��ֹͣλ��ʼ����ʱ��Ӳ����1
#define UART2_INT_R1            BIT0    //�����ж������жϱ�־λ:�����0 / ���н��յ�ֹͣλ��ʼʱ����Ӳ����1

#define UART2_SM1_8BIT          0       //8λUART,��ʱ��5�������/16
#define UART2_SM1_9BIT          BIT1    //8λUART,��ʱ��5�������/16
#define UART2_SM2_DIS           0       //�ڷ�ʽ0ʱ�����ֹͣλ,ֹͣλ������0����1������λRI
//�ڷ�ʽ1ʱ������9λ,��9λ������0����1������λRI
#define UART2_SM2_EN            BIT0    //�ڷ�ʽ0ʱ,ֻ��ֹͣλΪ1������λRI
//�ڷ�ʽ1ʱ,ֻ�е�9λΪ1������λRI

/* UART2 ���ݻ���Ĵ���S2BUF(Ĭ��0) */
/* дΪ��Ҫ���͵����ݣ���Ϊ���յ������� */
/**************************************************************************************/


/**************************************************************************************/
/* Ӧ�ö���UART PIN */
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
//�������
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
