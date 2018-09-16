/**
*   ************************************************************************************
*                               ��о��������޹�˾
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
* @����    ��ʼ��IIC
* @˵��
* @����
* @����ֵ
* @ע
***************************************************************************************/
void Iic_Master_Config(void)
{
    //SCL PIN �����������
    IIC_PORT_M_SCL &= ~(0x0f << ((IIC_PIN_SCL % 2) * 4));
    IIC_PORT_M_SCL |=  (IOL_PUSHPULL_OUT << ((IIC_PIN_SCL % 2) * 4));
    //SDA PIN ���ÿ�©���������
    IIC_PORT_M_SDA &= ~(0x0f << ((IIC_PIN_SDA % 2) * 4));
    IIC_PORT_M_SDA |=  (IOL_OPENDRAIN_PULL_OUT << ((IIC_PIN_SDA % 2) * 4));
    //UART TXͨ��ӳ��P25��
    SCL_MAP = IIC_MAP_PORT_SCL | IIC_MAP_PIN_SCL;
    //UART RXͨ��ӳ��P26��
    SDA_MAP = IIC_MAP_PORT_SDA | IIC_MAP_PIN_SDA;

    //����IICģ��,ʱ��Fose/160 = 200K
    IICCON = IIC_CLK_160 | IIC_EN;
}
/**************************************************************************************/


/***************************************************************************************
* @����    ��������(����)
* @˵��
* @����
* @����ֵ
* @ע
***************************************************************************************/
void Iic_Master_SendData(u8 u8_adr, u8 u8_length, u8 *u8_data)
{
    u8 i;

    //����жϱ�־λ
    IICCON &= ~ (IIC_SI_INT + IIC_STO_EN);
    //��ʼλ������ʼ�ź�
    IICCON |= IIC_STA_EN;

    while((!(IICCON & IIC_SI_INT)) && (IICSTA != IIC_R_IICSTA_08H));

    //ֹͣ��ʼλ�ź�
    IICCON &= ~ IIC_STA_EN;

    //����жϱ�־λ
    IICCON &= ~ IIC_SI_INT;
    //д�ӻ���ַ
    IICDAT = (IIC_SLAVE_ADDR + IIC_CMD_WRITE);

    while((!(IICCON & IIC_SI_INT)) && (IICSTA != IIC_R_IICSTA_18H));

    //����жϱ�־λ
    IICCON &= ~ IIC_SI_INT;
    //д���ʵ�ַ
    IICDAT = u8_adr;

    while((!(IICCON & IIC_SI_INT)) && (IICSTA != IIC_R_IICSTA_28H));

    //д����
    for(i = 0; i < u8_length; i++)
    {
        //����жϱ�־λ
        IICCON &= ~ IIC_SI_INT;
        IICDAT = u8_data[i];

        while((!(IICCON & IIC_SI_INT)) && (IICSTA != IIC_R_IICSTA_28H));
    }

    //����жϱ�־λ
    IICCON &= ~ IIC_SI_INT;
    //ֹͣλ������ʼ�ź�
    IICCON |= IIC_STO_EN;
    //����жϱ�־λ
    IICCON &= ~ (IIC_SI_INT + IIC_STO_EN);
}
/**************************************************************************************/


/***************************************************************************************
* @����    ��ȡ����(����)
* @˵��
* @����
* @����ֵ
* @ע
***************************************************************************************/
void Iic_Master_ReadData(u8 u8_adr, u8 u8_length, u8 *u8_data)
{
    u8 i;

    //����жϱ�־λ
    IICCON &= ~ (IIC_SI_INT + IIC_STO_EN);
    //��ʼλ������ʼ�ź�
    IICCON |= IIC_STA_EN;

    //�ȴ�START�źŷ������
    while((!(IICCON & IIC_SI_INT)) && (IICSTA != IIC_R_IICSTA_08H));

    //ֹͣ��ʼλ�ź�
    IICCON &= ~ IIC_STA_EN;

    //����жϱ�־λ
    IICCON &= ~ IIC_SI_INT;
    //д�ӻ���ַ
    IICDAT = (IIC_SLAVE_ADDR + IIC_CMD_WRITE);

    //�ȴ��ӻ���ַ�������
    while((!(IICCON & IIC_SI_INT)) && (IICSTA != IIC_R_IICSTA_18H));

    //����жϱ�־λ
    IICCON &= ~ IIC_SI_INT;
    //д���ʵ�ַ
    IICDAT = u8_adr;

    while((!(IICCON & IIC_SI_INT)) && (IICSTA != IIC_R_IICSTA_28H));

    //����жϱ�־λ
    IICCON &= ~ IIC_SI_INT;
    //��ʼλ������ʼ�ź�
    IICCON |= IIC_STA_EN;

    //�ȴ�START�źŷ������
    while((!(IICCON & IIC_SI_INT)) && (IICSTA != IIC_R_IICSTA_08H));

    //ֹͣ��ʼλ�ź�
    IICCON &= ~ IIC_STA_EN;

    //����жϱ�־λ
    IICCON &= ~ IIC_SI_INT;
    //д��ӻ���ַ+��ָ��
    IICDAT = (IIC_SLAVE_ADDR + IIC_CMD_READ);

    //�ȴ��ӻ���ַ�������
    while((!(IICCON & IIC_SI_INT)) && (IICSTA != IIC_R_IICSTA_40H));

    //д����
    for(i = 0; i < u8_length; i++)
    {
        //�ظ�ACK
        IICCON |= IIC_AA;
        //����жϱ�־λ
        IICCON &= ~ IIC_SI_INT;

        while((!(IICCON & IIC_SI_INT)) && (IICSTA != IIC_R_IICSTA_50H));

        u8_data[i] = IICDAT;
    }

    //�ظ�NACK
    IICCON &= ~IIC_AA;
    //����жϱ�־λ
    IICCON &= ~ IIC_SI_INT;

    while((!(IICCON & IIC_SI_INT)) && (IICSTA != IIC_R_IICSTA_58H));

    //����жϱ�־λ
    IICCON &= ~ IIC_SI_INT;
    //ֹͣλ������ʼ�ź�
    IICCON |= IIC_STO_EN;
    //����жϱ�־λ
    IICCON &= ~ (IIC_SI_INT + IIC_STO_EN);
}
/**************************************************************************************/

