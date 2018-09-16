/**
*   ************************************************************************************
*                               ��о��������޹�˾
*                               www.chipswinner.com
*   ************************************************************************************
*   @Demo   Version     V1.0.0.0
*   @Date               2018.7.22
*   ************************************************************************************
**/

/**************************************************************************************/
#ifdef  _ADC_
#define _ADC_
#else
#define _ADC_ extern
#endif
#include "HC89S003F4.h"
#include "app_cfg"
/**************************************************************************************/
/* ADC ���ƼĴ��� ADCC0 */
#define AD_ADCEN                BIT7        //0/1:�ر�/��ADCת����Դ
#define AD_ADCST                BIT6        //1:����ת��,Ӳ���Զ�����
#define AD_ADCIF                BIT5        //0/1:��/��AD�ж�(�������)
#define AD_VREFO                BIT3        //0/1:VREF�����/���
#define AD_VREFS                BIT2        //0/1:ѡ���ڲ�/�ⲿVREF
#define AD_INREF_VDD            B0000_0000  //�ڲ��ο���ѹVDD
#define AD_INREF_4V             B0000_0001  //            4V
#define AD_INREF_3V             B0000_0010  //            3V
#define AD_INREF_2V             B0000_0011  //            2V

/* ADC ���ƼĴ��� ADCC1 */
#define AD_ICHS_DIS             B0000_0000  //��ֹADC�ڲ�ͨ������
#define AD_ICHS_VDD_4           B0100_0000  //1/4VDD��ΪADC����ͨ��
#define AD_ICHS_GND             B1100_0000  //GND
#define AD_XCHS_AIN0            0           //�ⲿ����ͨ��AIN0
#define AD_XCHS_AIN1            1           //�ⲿ����ͨ��AIN1
#define AD_XCHS_AIN2            2           //�ⲿ����ͨ��AIN2
#define AD_XCHS_AIN3            3           //�ⲿ����ͨ��AIN3
#define AD_XCHS_AIN4            4           //�ⲿ����ͨ��AIN4
#define AD_XCHS_AIN5            5           //�ⲿ����ͨ��AIN5
#define AD_XCHS_AIN6            6           //�ⲿ����ͨ��AIN6
#define AD_XCHS_AIN7            7           //�ⲿ����ͨ��AIN7
#define AD_XCHS_AIN8            8           //�ⲿ����ͨ��AIN8
#define AD_XCHS_AIN9            9           //�ⲿ����ͨ��AIN9
#define AD_XCHS_AIN10           10          //�ⲿ����ͨ��AIN10
#define AD_XCHS_ICHS            15          //ѡ���ڲ�ͨ��,�ⲿͨ����������Ϊ1111

/* ADC ���ƼĴ��� ADCC2 */
#define AD_12B_H8L4             B0000_0000  //ADCRH 8λ+ADCRL��4λ
#define AD_12B_H4L8             B0100_0000  //ADCRH��4λ+ADCRL 8λ
#define AD_10B_H8L2             B1000_0000  //ADCRH 8λ+ADCRL��2λ
#define AD_10B_H2L8             B1100_0000  //ADCRH��2λ+ADCRL 8λ
#define AD_ADCTS_CLK4M          B0000_0000  //ADCʱ��4M,һ��ת����22��ADC_CLK
#define AD_ADCTS_CLK21M         B0001_0000  //ADCʱ��2M����1M,һ��ת����19��ADC_CLK
#define AD_ADCTS_CLKLOW         B0010_0000  //ADCʱ��С��1M,һ��ת����15��ADC_CLK
#define AD_CLK_FOSC2            B0000_0000  //ADCʱ��ѡ��Fosc/2
#define AD_CLK_FOSC4            B0000_0001  //ADCʱ��ѡ��Fosc/4
#define AD_CLK_FOSC6            B0000_0010  //ADCʱ��ѡ��Fosc/6
#define AD_CLK_FOSC8            B0000_0011  //ADCʱ��ѡ��Fosc/8
#define AD_CLK_FOSC12           B0000_0100  //ADCʱ��ѡ��Fosc/12
#define AD_CLK_FOSC16           B0000_0101  //ADCʱ��ѡ��Fosc/16
#define AD_CLK_FOSC24           B0000_0110  //ADCʱ��ѡ��Fosc/24
#define AD_CLK_FOSC32           B0000_0111  //ADCʱ��ѡ��Fosc/32
/* ADC ת������Ĵ��� ADCRL,ADCRH */

/* ADC �ⲿ�������ƼĴ���ADCEX */
#define AD_R_EXTTYP             BIT3        //0/1:һ��PWM���ڵ��е�/һ��PWM���ڵ��յ�
#define AD_EXTSEL_PWM0          B0000_0000  //�ⲿ����Դѡ��λ
#define AD_EXTSEL_PWM1          B0000_0010  //�ⲿ����Դѡ��λ
#define AD_EXTSEL_PWM2          B0000_0100  //�ⲿ����Դѡ��λ
#define AD_EXTRIG               BIT0        //0/1:ADC ת���������� ADCST(ADCC0.6)����/ADCST(ADCC0.6)�� 1 �󣬻���Ҫ�ⲿ�����źŴ���������

/* ADC ���ѿ��ƼĴ��� ADCWC */
#define AD_W_AMWEN              BIT7        //0/1:��ֹ/����ADC����ģ��
#define AD_W_AMWIF              BIT6        //0/1:��ADC����ģ���ж�,�����0/����ADC����ģ���ж�,Ӳ���� 1

/**************************************************************************************/



/**************************************************************************************/
#define D_ADC_VALID_TIMES           8                       //ADC��Ч�Ĳ�������
#define D_ADC_TOTAL_TIMES           (D_ADC_VALID_TIMES+2)   //ADC�ܵĲ�������
#define D_ADC_BUF_NUM               D_ADC_TOTAL_TIMES
_ADC_ u16 u16_adc_value_buf[D_ADC_BUF_NUM];                 //�����������BUF
_ADC_ u16 u16_adc_value;                                    //�������
_ADC_ u8  u8_adc_times;                                     //��������
/**************************************************************************************/
_ADC_ void Adc_Config_PowerOn(void);
_ADC_ void Adc_Config_PowerDown(void);
_ADC_ void Adc_Buffer_Initail(void);
_ADC_ void Adc_Sample_Cycle(void);
/**************************************************************************************/

