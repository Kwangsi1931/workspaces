/**
*   ************************************************************************************
*                               ��о��������޹�˾
*                               www.chipswinner.com
*   ************************************************************************************
*   @Demo   Version     V1.0.0.0
*   @Date               2018.8.6
*   ************************************************************************************
**/

/**************************************************************************************/
#ifdef  _PWM_
#define _PWM_
#else
#define _PWM_ extern
#endif
#include "HC89S003F4.h"
#include "app_cfg"
/**************************************************************************************/
/* PWM ���ƼĴ���PWMCTRL */
#define PWM_TYP2            BIT7        //0/1:PWM2 ���ض��� / ���Ķ���
#define PWM_TYP1            BIT6        //0/1:PWM1 ���ض��� / ���Ķ���
#define PWM_TYP0            BIT5        //0/1:PWM0 ���ض��� / ���Ķ���
#define PWM_RLOAD2          BIT4        //0/1:PWM2 ��ֹ / ʹ�� �Զ�����(Ĭ��ʹ��)
#define PWM_RLOAD1          BIT3        //0/1:PWM1 ��ֹ / ʹ�� �Զ�����(Ĭ��ʹ��)
#define PWM_RLOAD0          BIT2        //0/1:PWM0 ��ֹ / ʹ�� �Զ�����(Ĭ��ʹ��)
#define PWM_PWMLEN_12B      B0000_0000  //PWM����:12BIT
#define PWM_PWMLEN_16B      B0000_0010  //PWM����:16BIT
#define PWM_PENCTRL_EN      B0000_0000  //PWM0_EN,PWM1_EN,PWM2_EN ����PWMģ��ʹ��
#define PWM_PENCTRL_ENA     B0000_0001  //PWMENA �Ĵ������ƿ���PWMģ��ʹ�����

/* PWM ʹ�ܼĴ���PWMENA (Ĭ��ֵ0)*/
#define PWM_PWM21EN         B0100_0000  //ʹ��PWM21���
#define PWM_PWM11EN         B0010_0000  //ʹ��PWM11���
#define PWM_PWM01EN         B0001_0000  //ʹ��PWM01���
#define PWM_PWM2EN          B0000_0100  //ʹ��PWM2���
#define PWM_PWM1EN          B0000_0010  //ʹ��PWM1���
#define PWM_PWM0EN          B0000_0001  //ʹ��PWM0���
/**************************************************************************************/
/* PWM0 ʹ�ܼĴ���PWM0EN (Ĭ��ֵ0)*/
#define PWM0_FLT0_M1        B0000_0000  //PWM0���������ƽ:PWM0��,PWM01��
#define PWM0_FLT0_M2        B0010_0000  //                :PWM0��,PWM01��
#define PWM0_FLT0_M3        B0100_0000  //                :PWM0��,PWM01��
#define PWM0_FLT0_M4        B0110_0000  //                :PWM0��,PWM01��
#define PWM0_EFLT0_DIS      B0000_0000  //��ֹFLT0(P00)���Ź��ϼ��,����GPIO
#define PWM0_EFLT0_EN       B0001_0000  //����FLT0(P00)���Ź��ϼ��
#define PWM0_PWM0M_CPM      B0000_0000  //PWM0&PWM01�����ڻ������ģʽ
#define PWM0_PWM0M_IDP      B0000_1000  //PWM0&PWM01�����ڶ������ģʽ
#define PWM0_PWM01_OENEN    B0000_0100  //���� PWM01 ���
#define PWM0_PWM0_OENEN     B0000_0010  //���� PWM0 ���
#define PWM0_PWM0_EN        B0000_0001  //�� PWM0 ģ��

/* PWM0���ƼĴ���PWM0C(Ĭ��ֵ0) */
#define PWM0_IEEN           B1000_0000  //ʹ�� PWM0 �ж�
#define PWM0_IFCLR          B0000_0000  //PWM0�ж������0
#define PWM0_IFSET          B0100_0000  //PWM0�ж�Ӳ����1
#define PWM0_FLT0S_NORMAL   B0000_0000  //PWM0����״̬,�����0
#define PWM0_FLT0S_CLOSE    B0010_0000  //PWM0����ر�,Ӳ����1
#define PWM0_FLT0C_LOW      B0000_0000  //FLT0Ϊ�͵�ƽʱ,PWM0����ر�
#define PWM0_FLT0C_HIGH     B0001_0000  //FLT0Ϊ�ߵ�ƽʱ,PWM0����ر�
#define PWM0_PWM0S_0H1H     B0000_0000  //PWM0��PWM01���ģʽ:PWM0��,PWM01��
#define PWM0_PWM0S_0H1L     B0000_0100  //                   :PWM0��,PWM01��
#define PWM0_PWM0S_0L1H     B0000_1000  //                   :PWM0��,PWM01��
#define PWM0_PWM0S_0L1L     B0000_1100  //                   :PWM0��,PWM01��
#define PWM0_CK0_FOSC       B0000_0000  //PWM0ʱ��Դ:FOSC
#define PWM0_CK0_FOSC_8     B0000_0001  //          :FOSC/8
#define PWM0_CK0_FOSC_32    B0000_0010  //          :FOSC/32
#define PWM0_CK0_FOSC_128   B0000_0011  //          :FOSC/128

/* PWM0 ���ڼĴ���PWM0PL,PWM0PH(Ĭ��ֵ0) */
/* �޸�PWM0���ڱ������޸ĸ�λ���޸ĵ�λ */
/* PWM0���� = [ PWM0PH : PWM0PL] * PWM0����ʱ��Դ���� */
/* PWM0 ռ�ձȼĴ���PWM0DL,PWM0DH(Ĭ��ֵ0) */
/* �޸� PWM0 ռ�ձȼĴ���,�������޸ĸ�λ���޸ĵ�λ,���޸Ķ�����һ�����ڲ���Ч */
/* PWM0 ռ�ձ� = [ PWM0DH : PWM0DL] * PWM0 ����ʱ������ */
/* PWM0 ����ʱ��Ĵ���PWM0DTL,PWM0DTH */
/* �� PWM0M=1 ʱ,PWM0 ������ 2 ·����ģʽ,��ʱ������ʱ��Ĵ�������������PWM01��ռ�ձȼĴ��� */
/* ������ģʽ�� PWM0 ���Բ��� 2 ·������ͬ����ռ�ձȿ��Բ�ͬ�� PWM ���� */
/* ����ģʽ��:PWM0 ����ʱ�� = [ PWM0DTH : PWM0DTL] * PWM0 ����ʱ���� */
/* ����ģʽ��:����ʱ�����С��ռ�ձ�ʱ�䣬����ʱ����ռ�ձ�ʱ��ĺͱ���С��PWM0���� */
/* ����ģʽ��:PWM01 ռ�ձ�ʱ�� = [ PWM0DTH : PWM0DTL] * PWM0 ����ʱ������ */
/**************************************************************************************/
/* PWM1 ʹ�ܼĴ���PWM1EN (Ĭ��ֵ0)*/
#define PWM1_FLT1_M1        B0000_0000  //PWM1���������ƽ:PWM1��,PWM11��
#define PWM1_FLT1_M2        B0010_0000  //                :PWM1��,PWM11��
#define PWM1_FLT1_M3        B0100_0000  //                :PWM1��,PWM11��
#define PWM1_FLT1_M4        B0110_0000  //                :PWM1��,PWM11��
#define PWM1_EFLT1_DIS      B0000_0000  //��ֹFLT1(P01)���Ź��ϼ��,����GPIO
#define PWM1_EFLT1_EN       B0001_0000  //����FLT1(P01)���Ź��ϼ��
#define PWM1_PWM1M_CPM      B0000_0000  //PWM1&PWM11�����ڻ������ģʽ
#define PWM1_PWM1M_IDP      B0000_1000  //PWM1&PWM11�����ڶ������ģʽ
#define PWM1_PWM11_OENEN    B0000_0100  //���� PWM11 ���
#define PWM1_PWM1_OENEN     B0000_0010  //���� PWM1 ���
#define PWM1_PWM1_EN        B0000_0001  //�� PWM1 ģ��

/* PWM1���ƼĴ���PWM1C(Ĭ��ֵ0) */
#define PWM1_IEEN           B1000_0000  //ʹ�� PWM1 �ж�
#define PWM1_IFCLR          B0000_0000  //PWM1�ж������0
#define PWM1_IFSET          B0100_0000  //PWM1�ж�Ӳ����1
#define PWM1_FLT1S_NORMAL   B0000_0000  //PWM1����״̬,�����0
#define PWM1_FLT1S_CLOSE    B0010_0000  //PWM1����ر�,Ӳ����1
#define PWM1_FLT1C_LOW      B0000_0000  //FLT1Ϊ�͵�ƽʱ,PWM1����ر�
#define PWM1_FLT1C_HIGH     B0001_0000  //FLT1Ϊ�ߵ�ƽʱ,PWM1����ر�
#define PWM1_PWM1S_0H1H     B0000_0000  //PWM1��PWM11���ģʽ:PWM1��,PWM11��
#define PWM1_PWM1S_0H1L     B0000_0100  //                   :PWM1��,PWM11��
#define PWM1_PWM1S_0L1H     B0000_1000  //                   :PWM1��,PWM11��
#define PWM1_PWM1S_0L1L     B0000_1100  //                   :PWM1��,PWM11��
#define PWM1_CK1_FOSC       B0000_0000  //PWM1ʱ��Դ:FOSC
#define PWM1_CK1_FOSC_8     B0000_0001  //          :FOSC/8
#define PWM1_CK1_FOSC_32    B0000_0010  //          :FOSC/32
#define PWM1_CK1_FOSC_128   B0000_0011  //          :FOSC/128

/* PWM1 ���ڼĴ���PWM1PL,PWM1PH(Ĭ��ֵ0) */
/* PWM1 ռ�ձȼĴ���PWM1DL,PWM1DH(Ĭ��ֵ0) */
/* PWM1 ����ʱ��Ĵ���PWM1DTL,PWM1DTH */
/**************************************************************************************/
/* PWM2 ʹ�ܼĴ���PWM2EN (Ĭ��ֵ0)*/
#define PWM2_FLT2_M1        B0000_0000  //PWM1���������ƽ:PWM2��,PWM21��
#define PWM2_FLT2_M2        B0010_0000  //                :PWM2��,PWM21��
#define PWM2_FLT2_M3        B0100_0000  //                :PWM2��,PWM21��
#define PWM2_FLT2_M4        B0110_0000  //                :PWM2��,PWM21��
#define PWM2_EFLT2_DIS      B0000_0000  //��ֹFLT2(P02)���Ź��ϼ��,����GPIO
#define PWM2_EFLT2_EN       B0001_0000  //����FLT2(P02)���Ź��ϼ��
#define PWM2_PWM2M_CPM      B0000_0000  //PWM2&PWM21�����ڻ������ģʽ
#define PWM2_PWM2M_IDP      B0000_1000  //PWM2&PWM21�����ڶ������ģʽ
#define PWM2_PWM21_OENEN    B0000_0100  //���� PWM21 ���
#define PWM2_PWM2_OENEN     B0000_0010  //���� PWM2 ���
#define PWM2_PWM2_EN        B0000_0001  //�� PWM2 ģ��

/* PWM2 ���ƼĴ���PWM2C(Ĭ��ֵ0) */
#define PWM2_IEEN           B1000_0000  //ʹ�� PWM2 �ж�
#define PWM2_IFCLR          B0000_0000  //PWM2�ж������0
#define PWM2_IFSET          B0100_0000  //PWM2�ж�Ӳ����1
#define PWM2_FLT2S_NORMAL   B0000_0000  //PWM2����״̬,�����0
#define PWM2_FLT2S_CLOSE    B0010_0000  //PWM2����ر�,Ӳ����1
#define PWM2_FLT2C_LOW      B0000_0000  //FLT2Ϊ�͵�ƽʱ,PWM2����ر�
#define PWM2_FLT2C_HIGH     B0001_0000  //FLT2Ϊ�ߵ�ƽʱ,PWM2����ر�
#define PWM2_PWM2S_0H1H     B0000_0000  //PWM2��PWM21���ģʽ:PWM2��,PWM21��
#define PWM2_PWM2S_0H1L     B0000_0100  //                   :PWM2��,PWM21��
#define PWM2_PWM2S_0L1H     B0000_1000  //                   :PWM2��,PWM21��
#define PWM2_PWM2S_0L1L     B0000_1100  //                   :PWM2��,PWM21��
#define PWM2_CK2_FOSC       B0000_0000  //PWM2ʱ��Դ:FOSC
#define PWM2_CK2_FOSC_8     B0000_0001  //          :FOSC/8
#define PWM2_CK2_FOSC_32    B0000_0010  //          :FOSC/32
#define PWM2_CK2_FOSC_128   B0000_0011  //          :FOSC/128

/* PWM2 ���ڼĴ���PWM2PL,PWM2PH(Ĭ��ֵ0) */
/* PWM2 ռ�ձȼĴ���PWM2DL,PWM2DH(Ĭ��ֵ0) */
/* PWM2 ����ʱ��Ĵ���PWM2DTL,PWM2DTH */
/**************************************************************************************/
/* �û�Ӧ�ö���PWM ���PIN */
#define PWM_PIN_INDEX1              5
#define PWM_PIN_INDEX2              6
#define PWM_PIN_INDEX3              3
#define PWM_PIN_INDEX4              4
#define PWM_PIN_INDEX5              1
#define PWM_PIN_INDEX6              3

#define PWM_PORT_INDEX1             P0
#define PWM_PORT_INDEX2             P0
#define PWM_PORT_INDEX3             P2
#define PWM_PORT_INDEX4             P2
#define PWM_PORT_INDEX5             P2
#define PWM_PORT_INDEX6             P0

#define PWM_PORT_M_INDEX1           P0M2
#define PWM_PORT_M_INDEX2           P0M3
#define PWM_PORT_M_INDEX3           P2M1
#define PWM_PORT_M_INDEX4           P2M2
#define PWM_PORT_M_INDEX5           P2M0
#define PWM_PORT_M_INDEX6           P0M1

#define PWM_MAP_PORT_INDEX1         MAP_RW_PORT_P0
#define PWM_MAP_PIN_INDEX1          MAP_RW_PIN_5
#define PWM_MAP_PORT_INDEX2         MAP_RW_PORT_P0
#define PWM_MAP_PIN_INDEX2          MAP_RW_PIN_6
#define PWM_MAP_PORT_INDEX3         MAP_RW_PORT_P2
#define PWM_MAP_PIN_INDEX3          MAP_RW_PIN_3
#define PWM_MAP_PORT_INDEX4         MAP_RW_PORT_P2
#define PWM_MAP_PIN_INDEX4          MAP_RW_PIN_4
#define PWM_MAP_PORT_INDEX5         MAP_RW_PORT_P2
#define PWM_MAP_PIN_INDEX5          MAP_RW_PIN_1
#define PWM_MAP_PORT_INDEX6         MAP_RW_PORT_P0
#define PWM_MAP_PIN_INDEX6          MAP_RW_PIN_3

#define PWM0_FREQ                   100000                      //100K
#define PMW0_PERIOD                 (32000000/PWM0_FREQ)        //����
#define PWM0_DUTY                   (PMW0_PERIOD * 50 /100)     //50%
#define PWM0_DEAD                   (PWM0_DUTY * 5 /100)        //����ʱ��ΪDUYT��5%
#define PWM01_DUTY                  (PMW0_PERIOD * 80 /100)     //80%

#define PWM1_FREQ                   50000                       //50K
#define PMW1_PERIOD                 (32000000/PWM1_FREQ)        //����
#define PWM1_DUTY                   (PMW1_PERIOD * 20 /100)     //20%
#define PWM1_DEAD                   (PWM1_DUTY * 5 /100)        //����ʱ��ΪDUYT��5%
#define PWM11_DUTY                  (PMW1_PERIOD * 30 /100)     //30%

#define PWM2_FREQ                   200000                      //200K
#define PMW2_PERIOD                 (32000000/PWM2_FREQ)        //����
#define PWM2_DUTY                   (PMW2_PERIOD * 50 /100)     //50%
#define PWM2_DEAD                   (PWM2_DUTY * 10 /100)       //����ʱ��ΪDUYT��10%
#define PWM21_DUTY                  (PMW2_PERIOD * 50 /100)     //50%
/**************************************************************************************/
_PWM_ u16 u16_pwm0_period_cnt;
_PWM_ u16 u16_pwm0_duty;
_PWM_ u16 u16_pwm01_duty;

_PWM_ u16 u16_pwm1_duty;
_PWM_ u16 u16_pwm11_duty;

_PWM_ u16 u16_pwm2_duty;
_PWM_ u16 u16_pwm21_duty;
/**************************************************************************************/
_PWM_ void Pwm0_Config(void);
_PWM_ void Pwm0CPM_TurnOn(void);
_PWM_ void Pwm0CPM_DutyChange(u16 u16_duty);
_PWM_ void Pwm0IDP_TurnOn(void);
_PWM_ void Pwm0IDP_DutyChange(u16 u16_duty);
_PWM_ void Pwm01IDP_DutyChange(u16 u16_duty);
_PWM_ void Pwm0_TurnOff(void);

_PWM_ void Pwm1_Config(void);
_PWM_ void Pwm1CPM_TurnOn(void);
_PWM_ void Pwm1CPM_DutyChange(u16 u16_duty);
_PWM_ void Pwm1IDP_TurnOn(void);
_PWM_ void Pwm1IDP_DutyChange(u16 u16_duty);
_PWM_ void Pwm11IDP_DutyChange(u16 u16_duty);
_PWM_ void Pwm1_TurnOff(void);

_PWM_ void Pwm2_Config(void);
_PWM_ void Pwm2CPM_TurnOn(void);
_PWM_ void Pwm2CPM_DutyChange(u16 u16_duty);
_PWM_ void Pwm2IDP_TurnOn(void);
_PWM_ void Pwm2IDP_DutyChange(u16 u16_duty);
_PWM_ void Pwm21IDP_DutyChange(u16 u16_duty);
_PWM_ void Pwm2_TurnOff(void);
/**************************************************************************************/

