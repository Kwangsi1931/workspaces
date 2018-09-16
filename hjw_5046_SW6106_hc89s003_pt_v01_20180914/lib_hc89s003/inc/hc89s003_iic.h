/**
*   ************************************************************************************
*                               ��о��������޹�˾
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
/* ���ƼĴ��� IICCON(Ĭ��ֵ0) */
#define IIC_CLK_256             0           //IICʱ��ѡ��:Fosc/256
#define IIC_CLK_224             B0000_0001  //            Fosc/224
#define IIC_CLK_192             B0000_0010  //            Fosc/192
#define IIC_CLK_160             B0000_0011  //            Fosc/160
#define IIC_CLK_960             B1000_0000  //            Fosc/960
#define IIC_CLK_120             B1000_0001  //            Fosc/120
#define IIC_CLK_60              B1000_0010  //            Fosc/60
#define IIC_CLK_T5              B1000_0011  //            T5�����/8
#define IIC_EN                  BIT6        //���� IIC ģ��
#define IIC_STA_EN              BIT5        //������ʼ�ź�
#define IIC_STO_EN              BIT4        //����ģʽʱ����ֹͣ�ź�
#define IIC_SI_INT              BIT3        //0/1: û�� / ���� �����жϱ�־λ
#define IIC_AA                  BIT2        //0/1: �ظ�NACK(SDA ��Ϊ�ߵ�ƽ) / �ظ�ACK(SDA��Ϊ�͵�ƽ)

/* IIC ״̬�Ĵ��� IICSTA(ֻ��,Ĭ��ֵF8) */
/* IIC ״̬��,����26�����ܵ�״̬��,״̬���г� 0F8H �ⶼ���� SI ��־ */
#define IIC_R_IICSTA_08H        0x08        //����START�źŷ��ͽ���
#define IIC_R_IICSTA_18H        0x18        //�������ʹӻ���ַ����
#define IIC_R_IICSTA_28H        0x28        //�������ͽ���
#define IIC_R_IICSTA_40H        0x40
#define IIC_R_IICSTA_50H        0x50
#define IIC_R_IICSTA_58H        0x58


/* IIC ���ݼĴ���IICDAT(Ĭ��ֵ0) */

/* IIC ��ַ�Ĵ���IICADR(Ĭ��ֵ0) */
#define IIC_MODE_SLAVE_ADDR         0xFE        //�ӻ�ģʽ,�豸�Ĵӻ���ַ;����ģʽ,��ֵ��Ӱ��

/**************************************************************************************/


/**************************************************************************************/
/* Ӧ�ö���IIC PIN */
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
#define IIC_SLAVE_ADDR              0xA0            //�ӻ���ַ


#define IIC_SEND_NUM                4
#define IIC_RECEIVE_NUN             4
_IIC_ u8 u8_iic_send_buf[IIC_SEND_NUM];
_IIC_ u8 u8_iic_receive_buf[IIC_RECEIVE_NUN];



/**************************************************************************************/
_IIC_ void Iic_Master_Config(void);
_IIC_ void Iic_Master_SendData(u8 u8_adr, u8 u8_length, u8 *u8_data);
_IIC_ void Iic_Master_ReadData(u8 u8_adr, u8 u8_length, u8 *u8_data);

/**************************************************************************************/
