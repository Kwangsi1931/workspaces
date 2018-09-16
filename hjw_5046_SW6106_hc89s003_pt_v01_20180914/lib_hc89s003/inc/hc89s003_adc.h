/**
*   ************************************************************************************
*                               普芯达电子有限公司
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
/* ADC 控制寄存器 ADCC0 */
#define AD_ADCEN                BIT7        //0/1:关闭/打开ADC转换电源
#define AD_ADCST                BIT6        //1:启动转换,硬件自动清零
#define AD_ADCIF                BIT5        //0/1:无/有AD中断(软件清零)
#define AD_VREFO                BIT3        //0/1:VREF不输出/输出
#define AD_VREFS                BIT2        //0/1:选择内部/外部VREF
#define AD_INREF_VDD            B0000_0000  //内部参考电压VDD
#define AD_INREF_4V             B0000_0001  //            4V
#define AD_INREF_3V             B0000_0010  //            3V
#define AD_INREF_2V             B0000_0011  //            2V

/* ADC 控制寄存器 ADCC1 */
#define AD_ICHS_DIS             B0000_0000  //禁止ADC内部通道接入
#define AD_ICHS_VDD_4           B0100_0000  //1/4VDD作为ADC输入通道
#define AD_ICHS_GND             B1100_0000  //GND
#define AD_XCHS_AIN0            0           //外部输入通道AIN0
#define AD_XCHS_AIN1            1           //外部输入通道AIN1
#define AD_XCHS_AIN2            2           //外部输入通道AIN2
#define AD_XCHS_AIN3            3           //外部输入通道AIN3
#define AD_XCHS_AIN4            4           //外部输入通道AIN4
#define AD_XCHS_AIN5            5           //外部输入通道AIN5
#define AD_XCHS_AIN6            6           //外部输入通道AIN6
#define AD_XCHS_AIN7            7           //外部输入通道AIN7
#define AD_XCHS_AIN8            8           //外部输入通道AIN8
#define AD_XCHS_AIN9            9           //外部输入通道AIN9
#define AD_XCHS_AIN10           10          //外部输入通道AIN10
#define AD_XCHS_ICHS            15          //选择内部通道,外部通道必须配置为1111

/* ADC 控制寄存器 ADCC2 */
#define AD_12B_H8L4             B0000_0000  //ADCRH 8位+ADCRL低4位
#define AD_12B_H4L8             B0100_0000  //ADCRH低4位+ADCRL 8位
#define AD_10B_H8L2             B1000_0000  //ADCRH 8位+ADCRL低2位
#define AD_10B_H2L8             B1100_0000  //ADCRH低2位+ADCRL 8位
#define AD_ADCTS_CLK4M          B0000_0000  //ADC时钟4M,一次转换需22个ADC_CLK
#define AD_ADCTS_CLK21M         B0001_0000  //ADC时钟2M或者1M,一次转换需19个ADC_CLK
#define AD_ADCTS_CLKLOW         B0010_0000  //ADC时钟小于1M,一次转换需15个ADC_CLK
#define AD_CLK_FOSC2            B0000_0000  //ADC时钟选择Fosc/2
#define AD_CLK_FOSC4            B0000_0001  //ADC时钟选择Fosc/4
#define AD_CLK_FOSC6            B0000_0010  //ADC时钟选择Fosc/6
#define AD_CLK_FOSC8            B0000_0011  //ADC时钟选择Fosc/8
#define AD_CLK_FOSC12           B0000_0100  //ADC时钟选择Fosc/12
#define AD_CLK_FOSC16           B0000_0101  //ADC时钟选择Fosc/16
#define AD_CLK_FOSC24           B0000_0110  //ADC时钟选择Fosc/24
#define AD_CLK_FOSC32           B0000_0111  //ADC时钟选择Fosc/32
/* ADC 转换结果寄存器 ADCRL,ADCRH */

/* ADC 外部触发控制寄存器ADCEX */
#define AD_R_EXTTYP             BIT3        //0/1:一个PWM周期的中点/一个PWM周期的终点
#define AD_EXTSEL_PWM0          B0000_0000  //外部触发源选择位
#define AD_EXTSEL_PWM1          B0000_0010  //外部触发源选择位
#define AD_EXTSEL_PWM2          B0000_0100  //外部触发源选择位
#define AD_EXTRIG               BIT0        //0/1:ADC 转换启动仅由 ADCST(ADCC0.6)控制/ADCST(ADCC0.6)置 1 后，还需要外部触发信号触发才启动

/* ADC 唤醒控制寄存器 ADCWC */
#define AD_W_AMWEN              BIT7        //0/1:禁止/允许ADC唤醒模块
#define AD_W_AMWIF              BIT6        //0/1:无ADC唤醒模块中断,软件清0/发生ADC唤醒模块中断,硬件置 1

/**************************************************************************************/



/**************************************************************************************/
#define D_ADC_VALID_TIMES           8                       //ADC有效的采样次数
#define D_ADC_TOTAL_TIMES           (D_ADC_VALID_TIMES+2)   //ADC总的采样次数
#define D_ADC_BUF_NUM               D_ADC_TOTAL_TIMES
_ADC_ u16 u16_adc_value_buf[D_ADC_BUF_NUM];                 //采样结果缓存BUF
_ADC_ u16 u16_adc_value;                                    //采样结果
_ADC_ u8  u8_adc_times;                                     //采样次数
/**************************************************************************************/
_ADC_ void Adc_Config_PowerOn(void);
_ADC_ void Adc_Config_PowerDown(void);
_ADC_ void Adc_Buffer_Initail(void);
_ADC_ void Adc_Sample_Cycle(void);
/**************************************************************************************/

