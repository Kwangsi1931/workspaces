/**
*   ************************************************************************************
*                               ��о��������޹�˾
*                               www.chipswinner.com
*   ************************************************************************************
*   @Demo   Version     V1.0.0.0
*   @Date               2018.7.16
*   ************************************************************************************
**/

/**************************************************************************************/
#include "HC89S003F4.h"
#include "app_cfg"

/*���R,��ʾֻ��;���W,��ʾֻд;���RW,��ʾ�ɶ���д*/
/**************************************************************************************/
/*ʱ�ӿ��ƼĴ��� CLKCON */
#define CLK_R_HXTALRDY              BIT7        //�ⲿ��Ƶ����״̬λ
#define CLK_R_LXTALRDY              BIT6        //�ⲿ��Ƶ����״̬λ
#define CLK_R_HSRCRDY               BIT5        //�ڲ���ƵRC״̬λ
#define CLK_R_LSCRDY                BIT4        //�ڲ���ƵRC״̬λ
#define CLK_XTALEN                  BIT2        //�ⲿ����ʹ��λ
#define CLK_HSRCEN                  BIT1        //�ڲ���ƵRCʹ��λ
/**************************************************************************************/
/*ʱ��ѡ��Ĵ��� CLKSWR */
/*ϵͳʱ��״̬λ:BIT7,BIT6;ϵͳʱ��ѡ��λ:BIT5,BIT4;�ڲ���ƵRC��Ƶϵ��*/
#define CLK_R_CLKSTA_LRC            B0000_0000  //��ǰϵͳʱ��Ϊ�ڲ���ƵRC
#define CLK_R_CLKSTA_HRC            B0100_0000  //              �ڲ���ƵRC
#define CLK_R_CLKSTA_ELCRYSTAL      B1000_0000  //              �ⲿ��Ƶ����
#define CLK_R_CLKSTA_EHCRYSATL      B1100_0000  //              �ⲿ��Ƶ����
#define CLK_CLKSEL_LRC              B0000_0000  //ѡ��ϵͳʱ��Ϊ�ڲ���ƵRC
#define CLK_CLKSEL_HRC              B0001_0000  //              �ڲ���ƵRC
#define CLK_CLKSEL_ELCRYSTAL        B0010_0000  //              �ⲿ��Ƶ����
#define CLK_CKLSEL_EHCRYSTAL        B0011_0000  //              �ⲿ��Ƶ����
#define CLK_RC32MDIV_1              B0000_0000  //�ڲ���ƵRC��Ƶϵ��1��Ƶ
#define CLK_RC32MDIV_2              B0000_0001  //                  2��Ƶ
#define CLK_RC32MDIV_4              B0000_0010  //                  4��Ƶ
#define CLK_RC32MDIV_8              B0000_0011  //                  8��Ƶ(Ĭ��)
/**************************************************************************************/
/*ʱ�ӷ�Ƶ�Ĵ��� CLKDIV : CPUʱ�ӷ�Ƶϵ��*/
/*���ۿ�������(1~255)��ƵFosc�õ�CPUƵ��,�����оٳ��÷�Ƶϵ��*/
#define CLK_CLKDIV_1                B0000_0001  //CPUƵ��ΪFosc/1
#define CLK_CLKDIV_2                B0000_0010  //CPUƵ��ΪFosc/2(Ĭ��)
#define CLK_CLKDIV_4                B0000_0100  //CPUƵ��ΪFosc/4
#define CLK_CLKDIV_8                B0000_1000  //CPUƵ��ΪFosc/8
#define CLK_CLKDIV_16               B0001_0000  //CPUƵ��ΪFosc/16
#define CLK_CLKDIV_32               B0010_0000  //CPUƵ��ΪFosc/32
#define CLK_CLKDIV_64               B0100_0000  //CPUƵ��ΪFosc/64
#define CLK_CLKDIV_128              B1000_0000  //CPUƵ��ΪFosc/128
/**************************************************************************************/
/*ʱ������Ĵ��� CLKOUT */
/*ʱ�����ʹ��λ:BIT4;ʱ�����ѡ��λBIT2~BIT0 */
#define CLK_CLKOUTEN                BIT4        //ʱ�����ʹ��λ
#define CLK_CLKOUTSEL_CPU           B0000_0000  //ѡ��CPUʱ��
#define CLK_CLKOUTSEL_OSC           B0000_0001  //ѡ��ϵͳʱ��
#define CLK_CLKOUTSEL_WDT           B0000_0010  //ѡ���Ź�ʱ��
#define CLK_CLKOUTSEL_XTAL          B0000_0011  //ѡ���ⲿ����ʱ��
#define CLK_CLKOUTSEL_HRC_1         B0000_0100  //ѡ���ڲ���Ƶ32Mʱ��
#define CLK_CLKOUTSEL_HRC_2         B0000_0101  //ѡ���ڲ���Ƶ32M/2ʱ��
#define CLK_CLKOUTSEL_HRC_4         B0000_0110  //ѡ���ڲ���Ƶ32M/4ʱ��
#define CLK_CLKOUTSEL_HRC_8         B0000_0111  //ѡ���ڲ���Ƶ32M/8ʱ��
/**************************************************************************************/
/*�ⲿ�������üĴ��� XTALCFG */
#define CLK_HXTALCFG_2048           B0000_0000  //�ⲿ��Ƶ����warmup����ֵѡ��(Ĭ��)
#define CLK_HXTALCFG_256            B0100_0000
#define CLK_HXTALCFG_16384          B1000_0000
#define CLK_HXTALCFG_65536          B1100_0000
#define CLK_LXTALCFG_16384          B0000_0000  //�ⲿ��Ƶ����warmup����ֵѡ��(Ĭ��)
#define CLK_LXTALCFG_4096           B0001_0000
#define CLK_LXTALCFG_1024           B0010_0000
#define CLK_LXTALCFG_65536          B0011_0000
#define CLK_HXTAL_MODE_1            B0000_0000  //�ⲿ��Ƶ����ѡ��:4M/8M(Ĭ��)
#define CLK_HXTAL_MODE_2            B0000_0100  //                 4M/8M����������ģʽ,��ѹ����ʱ,����ʱ����ҹ�������
#define CLK_HXTAL_MODE_3            B0000_1100  //                 16M/32M
#define CLK_RCENPD                  BIT1        //ϵͳ����BOR��λʱ,�ڲ���ƵRC�ر��ź�
#define CLK_XTALSEL                 BIT0        //�ⲿ��Ƶ����
/**************************************************************************************/
/*ʱ��Ƶ�ʼĴ��� FREQ_CLK */
#define FREQ_CLK_16MHZ              0x10
#define FREQ_CLK_8MHZ               0x08
#define FREQ_CLK_4MHZ               0x04
#define FREQ_CLK_2MHZ               0x02
#define FREQ_CLK_1MHZ               0x01

/*�ڽ���FLASH��IAP��д����ϵͳ�������ģʽ֮ǰ,��Ҫ������չSFR���FREQ_CLK�Ĵ���,
ָ��ĿǰCPUʱ�ӵ�Ƶ��,FREQ_CLK�Ĵ������õ�ֵ����CPUʱ�ӵ�Ƶ��ֵ,��СΪ 1MHz*/

/*�ڲ���ƵRC����ʹ�ܼĴ��� TRMEN*/

/*�ڲ���ƵRC�������üĴ��� TRMV*/

/**************************************************************************************/
/*WDT ���ƼĴ��� WDTC ,WDTʱ��ԴΪ�ڲ���Ƶ44K */
#define WDT_WDTRST              BIT6        //0/1:��ֹ/����WDT��λ(Ĭ������)
#define WDT_WDTF                BIT5        //WDT�ж������־λ
#define WDT_WDTCLR              BIT4        //WDT����
#define WDT_WDTPD               BIT3        //0/1:����/��ֹ,����/����ģʽ������/��ֹWDT����(Ĭ�Ͻ�ֹ)
#define WDT_WDTPS_8             B0000_0000  //���Ź���ʱ��ʱ��Դ��Ƶ/8
#define WDT_WDTPS_16            B0000_0001  //                      /16
#define WDT_WDTPS_32            B0000_0010  //                      /32
#define WDT_WDTPS_64            B0000_0011  //                      /64
#define WDT_WDTPS_128           B0000_0100  //                      /128
#define WDT_WDTPS_256           B0000_0101  //                      /256
#define WDT_WDTPS_512           B0000_0110  //                      /512
#define WDT_WDTPS_1024          B0000_0111  //                      /1024

/*WDT �����ȽϼĴ��� WDTCCR */

/**************************************************************************************/
/* LVD ���ƼĴ��� LVDC */
#define LVD_LVDEN               BIT7        //0/1:��ֹ/����LVD����
#define LVD_LVDS                BIT6        //0/1:���VDD��ѹ/���P26�˿ڵ�ѹ
#define LVD_LVDIE               BIT5        //0/1:��ֹ/����LVD�ж�
#define LVD_LVDF                BIT3        //�͵�ѹ����־λ
#define LVD_LVDV_19V            B0000_0000  //��ѹѡ��1.9V
#define LVD_LVDV_20V            B0000_0001  //��ѹѡ��2.0V
#define LVD_LVDV_24V            B0000_0010  //��ѹѡ��2.4V
#define LVD_LVDV_26V            B0000_0011  //��ѹѡ��2.6V
#define LVD_LVDV_30V            B0000_0100  //��ѹѡ��3.0V
#define LVD_LVDV_36V            B0000_0101  //��ѹѡ��3.6V
#define LVD_LVDV_39V            B0000_0110  //��ѹѡ��3.9V
#define LVD_LVDV_42V            B0000_0111  //��ѹѡ��4.2V

/* LVD ȥ�����ƼĴ��� LVDDBC */
/* ����ʱ�� = LVDDBC[7:0]*8Tcpu+2Tcpu */
/**************************************************************************************/
/* ��Դ���ƼĴ��� PCON */
#define POWER_GF1               BIT3        //�û�ͨ�ñ�־λ1
#define POWER_GF0               BIT2        //�û�ͨ�ñ�־λ0
#define POWER_PD                BIT1        //0/1:����ģʽ/�������ģʽ
#define POWER_IDL               BIT0        //0/1:����ģʽ/�������ģʽ
/**************************************************************************************/
/* ��λ��־�Ĵ��� RSTFR */
#define RST_PORF                BIT7        //�ϵ縴λ
#define RST_EXRSTF              BIT6        //�ⲿRST��λ
#define RST_BORF                BIT5        //Ƿѹ��λ
#define RST_WDTRF               BIT4        //WDT��λ
#define RST_SWRF                BIT3        //�����λ
#define RST_SPOVF               BIT1        //��ջ���
#define RST_PLVRSTF             BIT0        //�ⲿ�˿ڵ�ѹ���
/**************************************************************************************/
/*BOR ��ѹ�����ƼĴ��� BORC */
#define POWER_BOREN             BIT7        //0/1:��ֹ/ʹ�ܵ͵�ѹ��λ(Ĭ��ʹ��)
#define POWER_BORDBCEN          BIT6        //0/1:��ʹ��/ʹ������(Ĭ�ϲ�ʹ��)
#define POWER_BORVS_18V         B0000_0000  //Ƿѹ��λ����ѹ1.8V
#define POWER_BORVS_20V         B0000_0001  //Ƿѹ��λ����ѹ2.0V
#define POWER_BORVS_24V         B0000_0010  //Ƿѹ��λ����ѹ2.4V
#define POWER_BORVS_26V         B0000_0011  //Ƿѹ��λ����ѹ2.6V
#define POWER_BORVS_30V         B0000_0100  //Ƿѹ��λ����ѹ3.0V
#define POWER_BORVS_36V         B0000_0101  //Ƿѹ��λ����ѹ3.6V
#define POWER_BORVS_39V         B0000_0110  //Ƿѹ��λ����ѹ3.9V
#define POWER_BORVS_42V         B0000_0111  //Ƿѹ��λ����ѹ4.2V

/*BOR ��ѹ���ȥ�����ƼĴ���BORDBC */
/*����ʱ�� = BORDBC[7:0] * 8Tcpu +2Tcpu */

/*�ⲿ ��RST ȥ�����ƼĴ���RSTDBC */
/*����ʱ�� = RSTDBC[7:0] * 8Tcpu +2 Tcpu */

/*��ջ�����λʹ�ܼĴ��� ջ�����λʹ�ܼĴ���SPOV_RSTEN */
#define SPOV_SPOVRSTEN              BIT0        //0/1:������/ʹ�ܶ�ջ�����λ
/**************************************************************************************/
/*�ж�����Ĵ���IE,IE1,IE2 (��ʼֵΪ0) */
#define INT_EA_EN               BIT7        //����CPU�ж�
#define INT_ES2_EN              BIT6        //����UART2�ж�
#define INT_EWDT_EN             BIT5        //����WDT�ж�
#define INT_ES1_EN              BIT4        //����UART1�ж�
#define INT_ET1_EN              BIT3        //����TIM1�ж�
#define INT_EX1_EN              BIT2        //����INT1�ж�
#define INT_ET0_EN              BIT1        //����TIM0�ж�
#define INT_EX0_EN              BIT0        //����INT0�ж�

#define INT_EX8_15_EN           BIT7        //�����ⲿ�ж�8~15
#define INT_EX2_7_EN            BIT6        //�����ⲿ�ж�2~7
#define INT_EADC_EN             BIT5        //����ADC�ж�
#define INT_T5_EN               BIT4        //����TIM5�ж�
#define INT_T4_EN               BIT2        //����TIM4�ж�
#define INT_T3_EN               BIT1        //����TIM3�ж�
#define INT_ESPI_EN             BIT0        //����SPI�ж�

#define INT_IIC_EN              BIT0        //����IIC�ж�

/*�ж����ȼ�ѡ��Ĵ���IP0,IP1,IP2,IP3,IP4(��ʼֵΪ0) */
#define INT_PT1_0               B0000_0000  //T1 �ж����ȼ�0(���)
#define INT_PT1_1               B0100_0000  //               1
#define INT_PT1_2               B1000_0000  //               2
#define INT_PT1_3               B1100_0000  //               3(���)
#define INT_PX1_0               B0000_0000  //INT1 �ж����ȼ�0(���)
#define INT_PX1_1               B0001_0000  //               1
#define INT_PX1_2               B0010_0000  //               2
#define INT_PX1_3               B0011_0000  //               3(���)
#define INT_PT0_0               B0000_0000  //T0 �ж����ȼ�0(���)
#define INT_PT0_1               B0000_0100  //               1
#define INT_PT0_2               B0000_1000  //               2
#define INT_PT0_3               B0000_1100  //               3(���)
#define INT_PX0_0               B0000_0000  //INT0 �ж����ȼ�0(���)
#define INT_PX0_1               B0000_0001  //               1
#define INT_PX0_2               B0000_0010  //               2
#define INT_PX0_3               B0000_0011  //               3(���)

#define INT_PS2_0               B0000_0000  //UART2 �ж����ȼ�0(���)
#define INT_PS2_1               B0100_0000  //               1
#define INT_PS2_2               B1000_0000  //               2
#define INT_PS2_3               B1100_0000  //               3(���)
#define INT_LVD_0               B0000_0000  //LVD �ж����ȼ�0(���)
#define INT_LVD_1               B0001_0000  //               1
#define INT_LVD_2               B0010_0000  //               2
#define INT_LVD_3               B0011_0000  //               3(���)
#define INT_WDT_0               B0000_0000  //WDT �ж����ȼ�0(���)
#define INT_WDT_1               B0000_0100  //               1
#define INT_WDT_2               B0000_1000  //               2
#define INT_WDT_3               B0000_1100  //               3(���)
#define INT_UART1_0             B0000_0000  //UART1 �ж����ȼ�0(���)
#define INT_UART1_1             B0000_0001  //               1
#define INT_UART1_2             B0000_0010  //               2
#define INT_UART1_3             B0000_0011  //               3(���)

#define INT_PPWM_0              B0000_0000  //PWM �ж����ȼ�0(���)
#define INT_PPWM_1              B0100_0000  //               1
#define INT_PPWM_2              B1000_0000  //               2
#define INT_PPWM_3              B1100_0000  //               3(���)
#define INT_PT4_0               B0000_0000  //TIM4 �ж����ȼ�0(���)
#define INT_PT4_1               B0001_0000  //               1
#define INT_PT4_2               B0010_0000  //               2
#define INT_PT4_3               B0011_0000  //               3(���)
#define INT_PT3_0               B0000_0000  //TIM3 �ж����ȼ�0(���)
#define INT_PT3_1               B0000_0100  //               1
#define INT_PT3_2               B0000_1000  //               2
#define INT_PT3_3               B0000_1100  //               3(���)
#define INT_PSPI_0              B0000_0000  //SPI �ж����ȼ�0(���)
#define INT_PSPI_1              B0000_0001  //               1
#define INT_PSPI_2              B0000_0010  //               2
#define INT_PSPI_3              B0000_0011  //               3(���)

#define INT_PX815_0             B0000_0000  //INT8_15 �ж����ȼ�0(���)
#define INT_PX815_1             B0100_0000  //               1
#define INT_PX815_2             B1000_0000  //               2
#define INT_PX815_3             B1100_0000  //               3(���)
#define INT_PX27_0              B0000_0000  //INT2_7 �ж����ȼ�0(���)
#define INT_PX27_1              B0001_0000  //               1
#define INT_PX27_2              B0010_0000  //               2
#define INT_PX27_3              B0011_0000  //               3(���)
#define INT_PADC_0              B0000_0000  //ADC �ж����ȼ�0(���)
#define INT_PADC_1              B0000_0100  //               1
#define INT_PADC_2              B0000_1000  //               2
#define INT_PADC_3              B0000_1100  //               3(���)
#define INT_PT5_0               B0000_0000  //TIM5 �ж����ȼ�0(���)
#define INT_PT5_1               B0000_0001  //               1
#define INT_PT5_2               B0000_0010  //               2
#define INT_PT5_3               B0000_0011  //               3(���)

#define INT_PIIC_0              B0000_0000  //IIC �ж����ȼ�0(���)
#define INT_PIIC_1              B0000_0001  //               1
#define INT_PIIC_2              B0000_0010  //               2
#define INT_PIIC_3              B0000_0011  //               3(���)

/*�ⲿ�жϵ�ƽѡ��Ĵ���PITS0,PITS1,PITS2,PITS3 (��ʼֵΪ0) */
#define INT_IT3_L               B0000_0000  //IT3 �ⲿ�жϴ����� �͵�ƽ
#define INT_IT3_LE              B0100_0000  //                   �½����ж�
#define INT_IT3_HE              B1000_0000  //                   �������ж�
#define INT_IT3_LHE             B1100_0000  //                   �½��������ж�
#define INT_IT2_L               B0000_0000  //IT2 �ⲿ�жϴ����� �͵�ƽ
#define INT_IT2_LE              B0001_0000  //                   �½����ж�
#define INT_IT2_HE              B0010_0000  //                   �������ж�
#define INT_IT2_LHE             B0011_0000  //                   �½��������ж�
#define INT_IT1_L               B0000_0000  //IT1 �ⲿ�жϴ����� �͵�ƽ
#define INT_IT1_LE              B0000_0100  //                   �½����ж�
#define INT_IT1_H               B0000_1000  //                   �������ж�
#define INT_IT1_LHE             B0000_1100  //                   �½��������ж�
#define INT_IT0_L               B0000_0000  //IT0 �ⲿ�жϴ����� �͵�ƽ
#define INT_IT0_LE              B0000_0001  //                   �½����ж�
#define INT_IT0_HE              B0000_0010  //                   �������ж�
#define INT_IT0_LHE             B0000_0011  //                   �½��������ж�

#define INT_IT7_L               B0000_0000  //IT7 �ⲿ�жϴ����� �͵�ƽ
#define INT_IT7_LE              B0100_0000  //                   �½����ж�
#define INT_IT7_HE              B1000_0000  //                   �������ж�
#define INT_IT7_LHE             B1100_0000  //                   �½��������ж�
#define INT_IT6_L               B0000_0000  //IT6 �ⲿ�жϴ����� �͵�ƽ
#define INT_IT6_LE              B0001_0000  //                   �½����ж�
#define INT_IT6_HE              B0010_0000  //                   �������ж�
#define INT_IT6_LHE             B0011_0000  //                   �½��������ж�
#define INT_IT5_L               B0000_0000  //IT5 �ⲿ�жϴ����� �͵�ƽ
#define INT_IT5_LE              B0000_0100  //                   �½����ж�
#define INT_IT5_HE              B0000_1000  //                   �������ж�
#define INT_IT5_LHE             B0000_1100  //                   �½��������ж�
#define INT_IT4_L               B0000_0000  //IT4 �ⲿ�жϴ����� �͵�ƽ
#define INT_IT4_LE              B0000_0001  //                   �½����ж�
#define INT_IT4_HE              B0000_0010  //                   �������ж�
#define INT_IT4_LHE             B0000_0011  //                   �½��������ж�

#define INT_IT11_L              B0000_0000  //IT11 �ⲿ�жϴ����� �͵�ƽ
#define INT_IT11_LE             B0100_0000  //                   �½����ж�
#define INT_IT11_HE             B1000_0000  //                   �������ж�
#define INT_IT11_LHE            B1100_0000  //                   �½��������ж�
#define INT_IT10_L              B0000_0000  //IT10 �ⲿ�жϴ����� �͵�ƽ
#define INT_IT10_LE             B0001_0000  //                   �½����ж�
#define INT_IT10_HE             B0010_0000  //                   �������ж�
#define INT_IT10_LHE            B0011_0000  //                   �½��������ж�
#define INT_IT9_L               B0000_0000  //IT9 �ⲿ�жϴ����� �͵�ƽ
#define INT_IT9_LE              B0000_0100  //                   �½����ж�
#define INT_IT9_HE              B0000_1000  //                   �������ж�
#define INT_IT9_LHE             B0000_1100  //                   �½��������ж�
#define INT_IT8_L               B0000_0000  //IT8 �ⲿ�жϴ����� �͵�ƽ
#define INT_IT8_LE              B0000_0001  //                   �½����ж�
#define INT_IT8_HE              B0000_0010  //                   �������ж�
#define INT_IT8_LHE             B0000_0011  //                   �½��������ж�

#define INT_IT15_L              B0000_0000  //IT15 �ⲿ�жϴ����� �͵�ƽ
#define INT_IT15_LE             B0100_0000  //                   �½����ж�
#define INT_IT15_HE             B1000_0000  //                   �������ж�
#define INT_IT15_LHE            B1100_0000  //                   �½��������ж�
#define INT_IT14_L              B0000_0000  //IT14 �ⲿ�жϴ����� �͵�ƽ
#define INT_IT14_LE             B0001_0000  //                   �½����ж�
#define INT_IT14_HE             B0010_0000  //                   �������ж�
#define INT_IT14_LHE            B0011_0000  //                   �½��������ж�
#define INT_IT13_L              B0000_0000  //IT13 �ⲿ�жϴ����� �͵�ƽ
#define INT_IT13_LE             B0000_0100  //                   �½����ж�
#define INT_IT13_HE             B0000_1000  //                   �������ж�
#define INT_IT13_LHE            B0000_1100  //                   �½��������ж�
#define INT_IT12_L              B0000_0000  //IT12 �ⲿ�жϴ����� �͵�ƽ
#define INT_IT12_LE             B0000_0001  //                   �½����ж�
#define INT_IT12_HE             B0000_0010  //                   �������ж�
#define INT_IT12_LHE            B0000_0011  //                   �½��������ж�

/* �ⲿ�ж�2-15 ʹ�ܿ��ƼĴ���PINTE0,PINTE1(��ʼֵΪ0) */
#define INT_EINT7               BIT7        //0/1:��ֹ / ���� INT7�˿��ж�
#define INT_EINT6               BIT6        //0/1:��ֹ / ���� INT6�˿��ж�
#define INT_EINT5               BIT5        //0/1:��ֹ / ���� INT5�˿��ж�
#define INT_EINT4               BIT4        //0/1:��ֹ / ���� INT4�˿��ж�
#define INT_EINT3               BIT3        //0/1:��ֹ / ���� INT3�˿��ж�
#define INT_EINT2               BIT2        //0/1:��ֹ / ���� INT2�˿��ж�

#define INT_EINT15              BIT7        //0/1:��ֹ / ���� INT15�˿��ж�
#define INT_EINT14              BIT6        //0/1:��ֹ / ���� INT14�˿��ж�
#define INT_EINT13              BIT5        //0/1:��ֹ / ���� INT13�˿��ж�
#define INT_EINT12              BIT4        //0/1:��ֹ / ���� INT12�˿��ж�
#define INT_EINT11              BIT3        //0/1:��ֹ / ���� INT11�˿��ж�
#define INT_EINT10              BIT2        //0/1:��ֹ / ���� INT10�˿��ж�
#define INT_EINT9               BIT1        //0/1:��ֹ / ���� INT9�˿��ж�
#define INT_EINT8               BIT0        //0/1:��ֹ / ���� INT8�˿��ж�

/* �ⲿ�жϱ�־�Ĵ���PINTF0,PINTF1(��ʼֵΪ0) */
#define INT_INT7F               BIT7        //0/1: INT7�ж������־λ,�����0 / Ӳ����1
#define INT_INT6F               BIT6        //0/1: INT6�ж������־λ,�����0 / Ӳ����1
#define INT_INT5F               BIT5        //0/1: INT5�ж������־λ,�����0 / Ӳ����1
#define INT_INT4F               BIT5        //0/1: INT4�ж������־λ,�����0 / Ӳ����1
#define INT_INT3F               BIT3        //0/1: INT3�ж������־λ,�����0 / Ӳ����1
#define INT_INT2F               BIT2        //0/1: INT2�ж������־λ,�����0 / Ӳ����1
#define INT_INT1F               BIT1        //0/1: INT1�ж������־λ,�����0 / Ӳ����1
#define INT_INT0F               BIT0        //0/1: INT0�ж������־λ,�����0 / Ӳ����1

#define INT_INT15F              BIT7        //0/1: INT15�ж������־λ,�����0 / Ӳ����1
#define INT_INT14F              BIT6        //0/1: INT14�ж������־λ,�����0 / Ӳ����1
#define INT_INT13F              BIT5        //0/1: INT13�ж������־λ,�����0 / Ӳ����1
#define INT_INT12F              BIT4        //0/1: INT12�ж������־λ,�����0 / Ӳ����1
#define INT_INT11F              BIT3        //0/1: INT11�ж������־λ,�����0 / Ӳ����1
#define INT_INT10F              BIT2        //0/1: INT10�ж������־λ,�����0 / Ӳ����1
#define INT_INT9F               BIT1        //0/1: INT9�ж������־λ,�����0 / Ӳ����1
#define INT_INT8F               BIT0        //0/1: INT8�ж������־λ,�����0 / Ӳ����1

/* �ⲿ�ж�01 �ܽ�ѡ��Ĵ���INT01_PINS (��ʼֵΪ0) */
#define INT_INT1_P01            B0000_0000  //INT1�ܽ�ѡ�� P01
#define INT_INT1_P11            B0000_0010  //INT1�ܽ�ѡ�� P11
#define INT_INT0_P00            B0000_0000  //INT0�ܽ�ѡ�� P00
#define INT_INT0_P10            B0000_0001  //INT0�ܽ�ѡ�� P10
/**************************************************************************************/
/* CRC ���ƼĴ��� CRCC (Ĭ��0) */
#define CRC_CRCBIT              BIT2        //0/1:CRC BIT ��ת����λ->MSB / LSB first
#define CRC_CRCRSV              BIT1        //0/1:��λ��ֵΪ 0x0000 / 0xFFFF
#define CRC_W_CRCRST            BIT0        //��1��λ CRC ������,Ӳ���Զ���0

/* CRC ���ݼĴ���CRCL,CRCH (Ĭ��0) */
/* CRCL д������ʱΪ CRC ����������������;��������ʱΪ CRC �������ĵ��ֽ� */
/*      д������ʱ�Զ����� CRC ����,����Զ��ر� */
/* CRCH �ԸüĴ���д��������Ч,��������ʱΪ CRC �������ĸ��ֽ� */
/* ÿһ��д����������ݣ��������������ǰһ�μ�������ͬ���� */
/* 16λCRC;CRC����У�����CRC-CCITT����ʽ(��0x1021);��ֵ����Ϊ0x0000��0xFFFF */
/* ������������ͬһ�Ĵ��� */
/**************************************************************************************/



/**************************************************************************************/
extern void Clk_Config_PowerOn(void);
extern void Wdt_TurnOn(void);
extern void Wdt_Clear(void);
extern u16 Crc_Calculate(u8 u8_length, u8 *u8_data_addr);

/**************************************************************************************/

