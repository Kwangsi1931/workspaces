/**
*   ************************************************************************************
*                               ��о��������޹�˾
*                               www.chipswinner.com
*   ************************************************************************************
*   @Demo   Version     V1.0.0.0
*   @Date               2018.7.12
*   ************************************************************************************
**/

/**************************************************************************************/
//#include "HC89S003F4.h"
#include "app_cfg.h"
/**************************************************************************************/
/*�˿����ݼĴ��� P0,P1,P2 */

/*�˿ڹ���ѡ��Ĵ��� P0M0,P0M1,P0M2,P0M3,P1M0,P2M0,P2M1,P2M2,P2M3*/
#define IOL_IN                      B0000_0000      //����,��ʩ����
#define IOL_PULLDOWN_IN             B0000_0001      //��������,��ʩ����
#define IOL_PULLUP_IN               B0000_0010      //��������,��ʩ����
#define IOL_ANALOG_IN               B0000_0011      //ģ������
#define IOL_SMTIN                   B0000_0100      //����,ʩ����
#define IOL_PULLDOWN_SMTIN          B0000_0101      //��������,ʩ����
#define IOL_PULLUP_SMTIN            B0000_0110      //��������,ʩ����
#define IOL_PUSHPULL_OUT            B0000_1000      //�������
#define IOL_OPENDRAIN_OUT           B0000_1001      //��©���
#define IOL_OPENDRAIN_PULL_OUT      B0000_1010      //��©���������

#define IOH_IN                      B0000_0000
#define IOH_PULLDOWN_IN             B0001_0000
#define IOH_PULLUP_IN               B0010_0000
#define IOH_ANALOG_IN               B0011_0000
#define IOH_SMTIN                   B0100_0000
#define IOH_PULLDOWN_SMTIN          B0101_0000
#define IOH_PULLUP_SMTIN            B0110_0000
#define IOH_PUSHPULL_OUT            B1000_0000
#define IOH_OPENDRAIN_OUT           B1001_0000
#define IOH_OPENDRAIN_PULL_OUT      B1010_0000

/*P23,P24,P25,P27 ֧�ֶ˿�������ͬʱʹ�ܹ���,��ʱ�˿������ѹԼΪ1/2VDD */
/*P23,P24,P25,P27ʹ����������*/
#define IOL_T_IN                    B0000_0000      //����,��ʩ����
#define IOL_T_ANALOG_IN             B0000_0011      //ģ������
#define IOL_T_SMTIN                 B0000_0100      //����,ʩ����
#define IOL_T_PULLDOWN_SMTIN        B0000_0101      //��������,ʩ����
#define IOL_T_PULLUP_SMTIN          B0000_0110      //��������,ʩ����
#define IOL_T_PULLUPDOWN_IN         B0000_0111      //ģ��ͨ��,������ͬʱʹ��
#define IOL_T_PUSHPULL_OUT          B0000_1000      //�������
#define IOL_T_OPENDRAIN_OUT         B0000_1101      //��©���
#define IOL_T_OPENDRAIN_PULL_OUT    B0000_1110      //��©���������

#define IOH_T_IN                    B0000_0000
#define IOH_T_ANALOG_IN             B0011_0000
#define IOH_T_SMTIN                 B0100_0000
#define IOH_T_PULLDOWN_SMTIN        B0101_0000
#define IOH_T_PULLUP_SMTIN          B0110_0000
#define IOH_T_PULLUPDOWN_IN         B0111_0000
#define IOH_T_PUSHPULL_OUT          B1000_0000
#define IOH_T_OPENDRAIN_OUT         B1101_0000
#define IOH_T_OPENDRAIN_PULL_OUT    B1110_0000
/**************************************************************************************/
/*�˿���������ѡ��Ĵ��� P0LPU */
/*����λ BIT5,BIT4*/
#define IO_PULL_RESISTANCE_50K      B0000_0000
#define IO_PULL_RESISTANCE_100K     B0001_0000
#define IO_PULL_RESISTANCE_150K     B0010_0000
#define IO_PULL_RESISTANCE_300K     B0011_0000
/**************************************************************************************/
/*�˿��������ƼĴ��� P00DBC,P01DBC,P02DBC */
/*ʱ��ѡ��BIT7,BIT6;ʱ��BIT5~BIT0*/
#define IO_DEBOUNCING_CLOCK_FOSE_1  B0000_0000
#define IO_DEBOUNCING_CLOCK_FOSE_4  B0100_0000
#define IO_DEBOUNCING_CLOCK_FOSE_16 B1000_0000
#define IO_DEBOUNCING_CLOCK_FOSE_64 B1100_0000
/**************************************************************************************/
/* ���蹦��ӳ��ſ��ƼĴ���,��ʹ�����蹦�ܽ�֮ǰ�������������蹦��ӳ��Ĵ���,�������蹦�ܽ��޷�ʹ�� */
#define MAP_RW_PORT_P0              B0000_0000  //ӳ��˿�ѡ��:P0
#define MAP_RW_PORT_P1              B0001_0000  //             P1
#define MAP_RW_PORT_P2              B0010_0000  //             P2
#define MAP_RW_PORT_GPIO            B0011_0000  //             Ĭ��GPIO
#define MAP_RW_PIN_0                0           //ӳ�������λ:0
#define MAP_RW_PIN_1                1           //             1
#define MAP_RW_PIN_2                2           //             2
#define MAP_RW_PIN_3                3           //             3
#define MAP_RW_PIN_4                4           //             4
#define MAP_RW_PIN_5                5           //             5
#define MAP_RW_PIN_6                6           //             6
#define MAP_RW_PIN_7                7           //             7
#define MAP_RW_PIN_GPIO             7           //             Ĭ��GPIO
/**************************************************************************************/
/* T0_MAP,T1_MAP,T3_MAP,T4_MAP,T5_MAP */
/* PWM0_MAP,PWM01_MAP,PWM1_MAP,PWM11_MAP,PWM2_MAP,PWM21_MAP,PWM3_MAP */
/* TXD_MAP,RXD_MAP,TXD2_MAP,RXD2_MAP */
/* SCL_MAP,SDA_MAP */
/* CLKO_MAP */
/* SS_MAP,SCK_MAP,MOSI_MAP,MISO_MAP */

extern void Gpio_Initial_PowerOn(void);
extern void Gpio_Configure_Idle(void);
extern void Gpio_Initial_WakeUp(void);



