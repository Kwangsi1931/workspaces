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
#ifdef  _SPI_
#define _SPI_
#else
#define _SPI_ extern
#endif
#include "HC89S003F4.h"
#include "app_cfg"
/**************************************************************************************/
/* ���ƼĴ��� SPCTL(Ĭ��0) */
#define SPI_SSIG            BIT7        //0/1: SS��ʹ�� / ��ͨIO
#define SPI_SPEN            BIT6        //0/1: ��ֹ / ʹ�� SPIģ��
#define SPI_DORD            BIT5        //0/1: MSB�ȷ��� / LSB�ȷ���
#define SPI_MSTR            BIT4        //0/1: �ӻ�ģʽ / ����ģʽ
#define SPI_CPOL            BIT3        //0/1: SCK����ʱ�͵�ƽ / �ߵ�ƽ
#define SPI_CPHA            BIT2        //0/1: ������SPIʱ�ӵĵ�һ�� / �ڶ��� ���ز���
#define SPI_SPR_FOSC4       B0000_0000  //ʱ������ѡ��:Fosc/4
#define SPI_SPR_FOSC16      B0000_0001  //             Fosc/16
#define SPI_SPR_FOSC64      B0000_0010  //             Fosc/64
#define SPI_SPR_FOSC128     B0000_0011  //             Fosc/128

/* ״̬�Ĵ��� SPSTAT(Ĭ��0) */
#define SPI_SPIF            BIT7        //0/1: ������ɱ�,���д1��0 / �������Ӳ����1
#define SPI_WCOL            BIT6        //0/1: д��ͻ��־,���д1��0 / ��������ж�SPDATִ��д������1
#define SPI_RXOV            BIT5        //0/1: ���������־,���д1��0 / �����������Ӳ����1
#define SPI_MODF            BIT4        //0/1: ģʽ���ϱ�־,���д1��0 / SS PIN��ƽ��SPIģʽ��һ��ʱ��1

/* SPI ���ݼĴ��� SPDAT(Ĭ��0) */
/**************************************************************************************/

/**************************************************************************************/
/* Ӧ�ö���SPI PIN */
//#define   SPI_PIN_SS                  7
//#define   SPI_PORT_SS                 P2
//#define   SPI_PORT_M_SS               P2M3

#define SPI_PIN_SCK                 4
#define SPI_PORT_SCK                P0
#define SPI_PORT_M_SCK              P0M2
//MOSI->�����
#define SPI_PIN_MOSI                2
#define SPI_PORT_MOSI               P0
#define SPI_PORT_M_MOSI             P0M1
//MISO->������
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
