/**
*   ************************************************************************************
*                               ��о��������޹�˾
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
* @����    ��ʼ��SPI(����)
* @˵��
* @����
* @����ֵ
* @ע
***************************************************************************************/
void Spi_Master_Config(void)
{
    //  //SS PIN �����������
    //  SPI_PORT_M_SS &= ~(0x0f << ((SPI_PIN_SS%2)*4));
    //  SPI_PORT_M_SS |=  (IOL_PUSHPULL_OUT << ((SPI_PIN_SS%2)*4));
    //SCK PIN �����������
    SPI_PORT_M_SCK &= ~(0x0f << ((SPI_PIN_SCK % 2) * 4));
    SPI_PORT_M_SCK |=  (IOL_PUSHPULL_OUT << ((SPI_PIN_SCK % 2) * 4));
    //MOSI PIN �����������
    SPI_PORT_M_MOSI &= ~(0x0f << ((SPI_PIN_MOSI % 2) * 4));
    SPI_PORT_M_MOSI |=  (IOL_PUSHPULL_OUT << ((SPI_PIN_MOSI % 2) * 4));
    //MISO PIN ����SMT����
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

    //���ݼĴ�����0
    SPDAT = 0;
    //״̬�Ĵ�����0
    SPSTAT = 0;
    //����ģʽ(����),ʱ��Fosc/128
    SPCTL = SPI_SSIG | SPI_SPEN | SPI_MSTR | SPI_CPHA | SPI_SPR_FOSC128;
}
/**************************************************************************************/


/***************************************************************************************
* @����    ������������(����)
* @˵��
* @����
* @����ֵ
* @ע
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
* @����    ����������(����)
* @˵��
* @����
* @����ֵ
* @ע
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
* @����    ��ʼ��SPI(�ӻ�)
* @˵��
* @����
* @����ֵ
* @ע
***************************************************************************************/
void Spi_Slave_Config(void)
{
    //  //SS PIN ����SMT����
    //  SPI_PORT_M_SS &= ~(0x0f << ((SPI_PIN_SS%2)*4));
    //  SPI_PORT_M_SS |=  (IOL_SMTIN << ((SPI_PIN_SS%2)*4));
    //SCK PIN ����SMT����
    SPI_PORT_M_SCK &= ~(0x0f << ((SPI_PIN_SCK % 2) * 4));
    SPI_PORT_M_SCK |=  (IOL_SMTIN << ((SPI_PIN_SCK % 2) * 4));
    //MOSI PIN ����SMT����
    SPI_PORT_M_MOSI &= ~(0x0f << ((SPI_PIN_MOSI % 2) * 4));
    SPI_PORT_M_MOSI |=  (IOL_SMTIN << ((SPI_PIN_MOSI % 2) * 4));
    //MISO PIN �����������
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

    //���ݼĴ�����0
    SPDAT = 0;
    //״̬�Ĵ�����0
    SPSTAT = 0;
    //�ӻ�ģʽ(����),ʱ��Fosc/128
    SPCTL = SPI_SSIG | SPI_SPEN | SPI_CPHA | SPI_SPR_FOSC128;

    //����SPI�ж�
    IE1 |= INT_ESPI_EN;

    //
    u8_spi_receive_cnt = 0;
}
/**************************************************************************************/


/***************************************************************************************
* @����    ������(�ӻ�),�ж��е���
* @˵��
* @����
* @����ֵ
* @ע
***************************************************************************************/
void Spi_Slave_ReceiveData(u8 *u8_index, u8 *u8_data)
{
    //���SPI�ж�
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
