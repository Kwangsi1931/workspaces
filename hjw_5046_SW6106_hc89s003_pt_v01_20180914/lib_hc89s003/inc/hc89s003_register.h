/**
*   ************************************************************************************
*                               普芯达电子有限公司
*                               www.chipswinner.com
*   ************************************************************************************
*   @Demo   Version     V1.0.0.0
*   @Date               2018.7.16
*   ************************************************************************************
**/

/**************************************************************************************/
#include "HC89S003F4.h"
#include "app_cfg"

/*标记R,表示只读;标记W,表示只写;标记RW,表示可读可写*/
/**************************************************************************************/
/*时钟控制寄存器 CLKCON */
#define CLK_R_HXTALRDY              BIT7        //外部高频晶体状态位
#define CLK_R_LXTALRDY              BIT6        //外部低频晶体状态位
#define CLK_R_HSRCRDY               BIT5        //内部高频RC状态位
#define CLK_R_LSCRDY                BIT4        //内部低频RC状态位
#define CLK_XTALEN                  BIT2        //外部晶体使能位
#define CLK_HSRCEN                  BIT1        //内部高频RC使能位
/**************************************************************************************/
/*时钟选择寄存器 CLKSWR */
/*系统时钟状态位:BIT7,BIT6;系统时钟选择位:BIT5,BIT4;内部高频RC分频系数*/
#define CLK_R_CLKSTA_LRC            B0000_0000  //当前系统时钟为内部低频RC
#define CLK_R_CLKSTA_HRC            B0100_0000  //              内部高频RC
#define CLK_R_CLKSTA_ELCRYSTAL      B1000_0000  //              外部低频晶体
#define CLK_R_CLKSTA_EHCRYSATL      B1100_0000  //              外部高频晶体
#define CLK_CLKSEL_LRC              B0000_0000  //选择系统时钟为内部低频RC
#define CLK_CLKSEL_HRC              B0001_0000  //              内部高频RC
#define CLK_CLKSEL_ELCRYSTAL        B0010_0000  //              外部低频晶体
#define CLK_CKLSEL_EHCRYSTAL        B0011_0000  //              外部高频晶体
#define CLK_RC32MDIV_1              B0000_0000  //内部高频RC分频系数1分频
#define CLK_RC32MDIV_2              B0000_0001  //                  2分频
#define CLK_RC32MDIV_4              B0000_0010  //                  4分频
#define CLK_RC32MDIV_8              B0000_0011  //                  8分频(默认)
/**************************************************************************************/
/*时钟分频寄存器 CLKDIV : CPU时钟分频系数*/
/*理论可以任意(1~255)分频Fosc得到CPU频率,定义列举常用分频系数*/
#define CLK_CLKDIV_1                B0000_0001  //CPU频率为Fosc/1
#define CLK_CLKDIV_2                B0000_0010  //CPU频率为Fosc/2(默认)
#define CLK_CLKDIV_4                B0000_0100  //CPU频率为Fosc/4
#define CLK_CLKDIV_8                B0000_1000  //CPU频率为Fosc/8
#define CLK_CLKDIV_16               B0001_0000  //CPU频率为Fosc/16
#define CLK_CLKDIV_32               B0010_0000  //CPU频率为Fosc/32
#define CLK_CLKDIV_64               B0100_0000  //CPU频率为Fosc/64
#define CLK_CLKDIV_128              B1000_0000  //CPU频率为Fosc/128
/**************************************************************************************/
/*时钟输出寄存器 CLKOUT */
/*时钟输出使能位:BIT4;时钟输出选择位BIT2~BIT0 */
#define CLK_CLKOUTEN                BIT4        //时钟输出使能位
#define CLK_CLKOUTSEL_CPU           B0000_0000  //选择CPU时钟
#define CLK_CLKOUTSEL_OSC           B0000_0001  //选择系统时钟
#define CLK_CLKOUTSEL_WDT           B0000_0010  //选择看门狗时钟
#define CLK_CLKOUTSEL_XTAL          B0000_0011  //选择外部晶体时钟
#define CLK_CLKOUTSEL_HRC_1         B0000_0100  //选择内部高频32M时钟
#define CLK_CLKOUTSEL_HRC_2         B0000_0101  //选择内部高频32M/2时钟
#define CLK_CLKOUTSEL_HRC_4         B0000_0110  //选择内部高频32M/4时钟
#define CLK_CLKOUTSEL_HRC_8         B0000_0111  //选择内部高频32M/8时钟
/**************************************************************************************/
/*外部晶体配置寄存器 XTALCFG */
#define CLK_HXTALCFG_2048           B0000_0000  //外部高频晶体warmup基数值选择(默认)
#define CLK_HXTALCFG_256            B0100_0000
#define CLK_HXTALCFG_16384          B1000_0000
#define CLK_HXTALCFG_65536          B1100_0000
#define CLK_LXTALCFG_16384          B0000_0000  //外部低频晶体warmup基数值选择(默认)
#define CLK_LXTALCFG_4096           B0001_0000
#define CLK_LXTALCFG_1024           B0010_0000
#define CLK_LXTALCFG_65536          B0011_0000
#define CLK_HXTAL_MODE_1            B0000_0000  //外部高频晶体选择:4M/8M(默认)
#define CLK_HXTAL_MODE_2            B0000_0100  //                 4M/8M大驱动能力模式,低压工作时,起振时间短且功耗适中
#define CLK_HXTAL_MODE_3            B0000_1100  //                 16M/32M
#define CLK_RCENPD                  BIT1        //系统产生BOR复位时,内部高频RC关闭信号
#define CLK_XTALSEL                 BIT0        //外部高频晶体
/**************************************************************************************/
/*时钟频率寄存器 FREQ_CLK */
#define FREQ_CLK_16MHZ              0x10
#define FREQ_CLK_8MHZ               0x08
#define FREQ_CLK_4MHZ               0x04
#define FREQ_CLK_2MHZ               0x02
#define FREQ_CLK_1MHZ               0x01

/*在进行FLASH的IAP擦写或者系统进入掉电模式之前,需要配置扩展SFR里的FREQ_CLK寄存器,
指明目前CPU时钟的频率,FREQ_CLK寄存器配置的值等于CPU时钟的频率值,最小为 1MHz*/

/*内部高频RC调整使能寄存器 TRMEN*/

/*内部高频RC调整配置寄存器 TRMV*/

/**************************************************************************************/
/*WDT 控制寄存器 WDTC ,WDT时钟源为内部低频44K */
#define WDT_WDTRST              BIT6        //0/1:禁止/允许WDT复位(默认允许)
#define WDT_WDTF                BIT5        //WDT中断请求标志位
#define WDT_WDTCLR              BIT4        //WDT清零
#define WDT_WDTPD               BIT3        //0/1:允许/禁止,空闲/掉电模式下允许/禁止WDT运行(默认禁止)
#define WDT_WDTPS_8             B0000_0000  //看门狗定时器时钟源分频/8
#define WDT_WDTPS_16            B0000_0001  //                      /16
#define WDT_WDTPS_32            B0000_0010  //                      /32
#define WDT_WDTPS_64            B0000_0011  //                      /64
#define WDT_WDTPS_128           B0000_0100  //                      /128
#define WDT_WDTPS_256           B0000_0101  //                      /256
#define WDT_WDTPS_512           B0000_0110  //                      /512
#define WDT_WDTPS_1024          B0000_0111  //                      /1024

/*WDT 计数比较寄存器 WDTCCR */

/**************************************************************************************/
/* LVD 控制寄存器 LVDC */
#define LVD_LVDEN               BIT7        //0/1:禁止/允许LVD功能
#define LVD_LVDS                BIT6        //0/1:检测VDD电压/检测P26端口电压
#define LVD_LVDIE               BIT5        //0/1:禁止/允许LVD中断
#define LVD_LVDF                BIT3        //低电压检测标志位
#define LVD_LVDV_19V            B0000_0000  //电压选择1.9V
#define LVD_LVDV_20V            B0000_0001  //电压选择2.0V
#define LVD_LVDV_24V            B0000_0010  //电压选择2.4V
#define LVD_LVDV_26V            B0000_0011  //电压选择2.6V
#define LVD_LVDV_30V            B0000_0100  //电压选择3.0V
#define LVD_LVDV_36V            B0000_0101  //电压选择3.6V
#define LVD_LVDV_39V            B0000_0110  //电压选择3.9V
#define LVD_LVDV_42V            B0000_0111  //电压选择4.2V

/* LVD 去抖控制寄存器 LVDDBC */
/* 消抖时间 = LVDDBC[7:0]*8Tcpu+2Tcpu */
/**************************************************************************************/
/* 电源控制寄存器 PCON */
#define POWER_GF1               BIT3        //用户通用标志位1
#define POWER_GF0               BIT2        //用户通用标志位0
#define POWER_PD                BIT1        //0/1:正常模式/进入掉电模式
#define POWER_IDL               BIT0        //0/1:正常模式/进入空闲模式
/**************************************************************************************/
/* 复位标志寄存器 RSTFR */
#define RST_PORF                BIT7        //上电复位
#define RST_EXRSTF              BIT6        //外部RST复位
#define RST_BORF                BIT5        //欠压复位
#define RST_WDTRF               BIT4        //WDT复位
#define RST_SWRF                BIT3        //软件复位
#define RST_SPOVF               BIT1        //堆栈溢出
#define RST_PLVRSTF             BIT0        //外部端口电压检测
/**************************************************************************************/
/*BOR 电压检测控制寄存器 BORC */
#define POWER_BOREN             BIT7        //0/1:禁止/使能低电压复位(默认使能)
#define POWER_BORDBCEN          BIT6        //0/1:不使能/使能消抖(默认不使能)
#define POWER_BORVS_18V         B0000_0000  //欠压复位检测电压1.8V
#define POWER_BORVS_20V         B0000_0001  //欠压复位检测电压2.0V
#define POWER_BORVS_24V         B0000_0010  //欠压复位检测电压2.4V
#define POWER_BORVS_26V         B0000_0011  //欠压复位检测电压2.6V
#define POWER_BORVS_30V         B0000_0100  //欠压复位检测电压3.0V
#define POWER_BORVS_36V         B0000_0101  //欠压复位检测电压3.6V
#define POWER_BORVS_39V         B0000_0110  //欠压复位检测电压3.9V
#define POWER_BORVS_42V         B0000_0111  //欠压复位检测电压4.2V

/*BOR 电压检测去抖控制寄存器BORDBC */
/*消抖时间 = BORDBC[7:0] * 8Tcpu +2Tcpu */

/*外部 部RST 去抖控制寄存器RSTDBC */
/*消抖时间 = RSTDBC[7:0] * 8Tcpu +2 Tcpu */

/*堆栈溢出复位使能寄存器 栈溢出复位使能寄存器SPOV_RSTEN */
#define SPOV_SPOVRSTEN              BIT0        //0/1:不是能/使能堆栈溢出复位
/**************************************************************************************/
/*中断允许寄存器IE,IE1,IE2 (初始值为0) */
#define INT_EA_EN               BIT7        //允许CPU中断
#define INT_ES2_EN              BIT6        //允许UART2中断
#define INT_EWDT_EN             BIT5        //允许WDT中断
#define INT_ES1_EN              BIT4        //允许UART1中断
#define INT_ET1_EN              BIT3        //允许TIM1中断
#define INT_EX1_EN              BIT2        //允许INT1中断
#define INT_ET0_EN              BIT1        //允许TIM0中断
#define INT_EX0_EN              BIT0        //允许INT0中断

#define INT_EX8_15_EN           BIT7        //允许外部中断8~15
#define INT_EX2_7_EN            BIT6        //允许外部中断2~7
#define INT_EADC_EN             BIT5        //允许ADC中断
#define INT_T5_EN               BIT4        //允许TIM5中断
#define INT_T4_EN               BIT2        //允许TIM4中断
#define INT_T3_EN               BIT1        //允许TIM3中断
#define INT_ESPI_EN             BIT0        //允许SPI中断

#define INT_IIC_EN              BIT0        //允许IIC中断

/*中断优先级选择寄存器IP0,IP1,IP2,IP3,IP4(初始值为0) */
#define INT_PT1_0               B0000_0000  //T1 中断优先级0(最低)
#define INT_PT1_1               B0100_0000  //               1
#define INT_PT1_2               B1000_0000  //               2
#define INT_PT1_3               B1100_0000  //               3(最高)
#define INT_PX1_0               B0000_0000  //INT1 中断优先级0(最低)
#define INT_PX1_1               B0001_0000  //               1
#define INT_PX1_2               B0010_0000  //               2
#define INT_PX1_3               B0011_0000  //               3(最高)
#define INT_PT0_0               B0000_0000  //T0 中断优先级0(最低)
#define INT_PT0_1               B0000_0100  //               1
#define INT_PT0_2               B0000_1000  //               2
#define INT_PT0_3               B0000_1100  //               3(最高)
#define INT_PX0_0               B0000_0000  //INT0 中断优先级0(最低)
#define INT_PX0_1               B0000_0001  //               1
#define INT_PX0_2               B0000_0010  //               2
#define INT_PX0_3               B0000_0011  //               3(最高)

#define INT_PS2_0               B0000_0000  //UART2 中断优先级0(最低)
#define INT_PS2_1               B0100_0000  //               1
#define INT_PS2_2               B1000_0000  //               2
#define INT_PS2_3               B1100_0000  //               3(最高)
#define INT_LVD_0               B0000_0000  //LVD 中断优先级0(最低)
#define INT_LVD_1               B0001_0000  //               1
#define INT_LVD_2               B0010_0000  //               2
#define INT_LVD_3               B0011_0000  //               3(最高)
#define INT_WDT_0               B0000_0000  //WDT 中断优先级0(最低)
#define INT_WDT_1               B0000_0100  //               1
#define INT_WDT_2               B0000_1000  //               2
#define INT_WDT_3               B0000_1100  //               3(最高)
#define INT_UART1_0             B0000_0000  //UART1 中断优先级0(最低)
#define INT_UART1_1             B0000_0001  //               1
#define INT_UART1_2             B0000_0010  //               2
#define INT_UART1_3             B0000_0011  //               3(最高)

#define INT_PPWM_0              B0000_0000  //PWM 中断优先级0(最低)
#define INT_PPWM_1              B0100_0000  //               1
#define INT_PPWM_2              B1000_0000  //               2
#define INT_PPWM_3              B1100_0000  //               3(最高)
#define INT_PT4_0               B0000_0000  //TIM4 中断优先级0(最低)
#define INT_PT4_1               B0001_0000  //               1
#define INT_PT4_2               B0010_0000  //               2
#define INT_PT4_3               B0011_0000  //               3(最高)
#define INT_PT3_0               B0000_0000  //TIM3 中断优先级0(最低)
#define INT_PT3_1               B0000_0100  //               1
#define INT_PT3_2               B0000_1000  //               2
#define INT_PT3_3               B0000_1100  //               3(最高)
#define INT_PSPI_0              B0000_0000  //SPI 中断优先级0(最低)
#define INT_PSPI_1              B0000_0001  //               1
#define INT_PSPI_2              B0000_0010  //               2
#define INT_PSPI_3              B0000_0011  //               3(最高)

#define INT_PX815_0             B0000_0000  //INT8_15 中断优先级0(最低)
#define INT_PX815_1             B0100_0000  //               1
#define INT_PX815_2             B1000_0000  //               2
#define INT_PX815_3             B1100_0000  //               3(最高)
#define INT_PX27_0              B0000_0000  //INT2_7 中断优先级0(最低)
#define INT_PX27_1              B0001_0000  //               1
#define INT_PX27_2              B0010_0000  //               2
#define INT_PX27_3              B0011_0000  //               3(最高)
#define INT_PADC_0              B0000_0000  //ADC 中断优先级0(最低)
#define INT_PADC_1              B0000_0100  //               1
#define INT_PADC_2              B0000_1000  //               2
#define INT_PADC_3              B0000_1100  //               3(最高)
#define INT_PT5_0               B0000_0000  //TIM5 中断优先级0(最低)
#define INT_PT5_1               B0000_0001  //               1
#define INT_PT5_2               B0000_0010  //               2
#define INT_PT5_3               B0000_0011  //               3(最高)

#define INT_PIIC_0              B0000_0000  //IIC 中断优先级0(最低)
#define INT_PIIC_1              B0000_0001  //               1
#define INT_PIIC_2              B0000_0010  //               2
#define INT_PIIC_3              B0000_0011  //               3(最高)

/*外部中断电平选择寄存器PITS0,PITS1,PITS2,PITS3 (初始值为0) */
#define INT_IT3_L               B0000_0000  //IT3 外部中断触发沿 低电平
#define INT_IT3_LE              B0100_0000  //                   下降沿中断
#define INT_IT3_HE              B1000_0000  //                   上升沿中断
#define INT_IT3_LHE             B1100_0000  //                   下降上升沿中断
#define INT_IT2_L               B0000_0000  //IT2 外部中断触发沿 低电平
#define INT_IT2_LE              B0001_0000  //                   下降沿中断
#define INT_IT2_HE              B0010_0000  //                   上升沿中断
#define INT_IT2_LHE             B0011_0000  //                   下降上升沿中断
#define INT_IT1_L               B0000_0000  //IT1 外部中断触发沿 低电平
#define INT_IT1_LE              B0000_0100  //                   下降沿中断
#define INT_IT1_H               B0000_1000  //                   上升沿中断
#define INT_IT1_LHE             B0000_1100  //                   下降上升沿中断
#define INT_IT0_L               B0000_0000  //IT0 外部中断触发沿 低电平
#define INT_IT0_LE              B0000_0001  //                   下降沿中断
#define INT_IT0_HE              B0000_0010  //                   上升沿中断
#define INT_IT0_LHE             B0000_0011  //                   下降上升沿中断

#define INT_IT7_L               B0000_0000  //IT7 外部中断触发沿 低电平
#define INT_IT7_LE              B0100_0000  //                   下降沿中断
#define INT_IT7_HE              B1000_0000  //                   上升沿中断
#define INT_IT7_LHE             B1100_0000  //                   下降上升沿中断
#define INT_IT6_L               B0000_0000  //IT6 外部中断触发沿 低电平
#define INT_IT6_LE              B0001_0000  //                   下降沿中断
#define INT_IT6_HE              B0010_0000  //                   上升沿中断
#define INT_IT6_LHE             B0011_0000  //                   下降上升沿中断
#define INT_IT5_L               B0000_0000  //IT5 外部中断触发沿 低电平
#define INT_IT5_LE              B0000_0100  //                   下降沿中断
#define INT_IT5_HE              B0000_1000  //                   上升沿中断
#define INT_IT5_LHE             B0000_1100  //                   下降上升沿中断
#define INT_IT4_L               B0000_0000  //IT4 外部中断触发沿 低电平
#define INT_IT4_LE              B0000_0001  //                   下降沿中断
#define INT_IT4_HE              B0000_0010  //                   上升沿中断
#define INT_IT4_LHE             B0000_0011  //                   下降上升沿中断

#define INT_IT11_L              B0000_0000  //IT11 外部中断触发沿 低电平
#define INT_IT11_LE             B0100_0000  //                   下降沿中断
#define INT_IT11_HE             B1000_0000  //                   上升沿中断
#define INT_IT11_LHE            B1100_0000  //                   下降上升沿中断
#define INT_IT10_L              B0000_0000  //IT10 外部中断触发沿 低电平
#define INT_IT10_LE             B0001_0000  //                   下降沿中断
#define INT_IT10_HE             B0010_0000  //                   上升沿中断
#define INT_IT10_LHE            B0011_0000  //                   下降上升沿中断
#define INT_IT9_L               B0000_0000  //IT9 外部中断触发沿 低电平
#define INT_IT9_LE              B0000_0100  //                   下降沿中断
#define INT_IT9_HE              B0000_1000  //                   上升沿中断
#define INT_IT9_LHE             B0000_1100  //                   下降上升沿中断
#define INT_IT8_L               B0000_0000  //IT8 外部中断触发沿 低电平
#define INT_IT8_LE              B0000_0001  //                   下降沿中断
#define INT_IT8_HE              B0000_0010  //                   上升沿中断
#define INT_IT8_LHE             B0000_0011  //                   下降上升沿中断

#define INT_IT15_L              B0000_0000  //IT15 外部中断触发沿 低电平
#define INT_IT15_LE             B0100_0000  //                   下降沿中断
#define INT_IT15_HE             B1000_0000  //                   上升沿中断
#define INT_IT15_LHE            B1100_0000  //                   下降上升沿中断
#define INT_IT14_L              B0000_0000  //IT14 外部中断触发沿 低电平
#define INT_IT14_LE             B0001_0000  //                   下降沿中断
#define INT_IT14_HE             B0010_0000  //                   上升沿中断
#define INT_IT14_LHE            B0011_0000  //                   下降上升沿中断
#define INT_IT13_L              B0000_0000  //IT13 外部中断触发沿 低电平
#define INT_IT13_LE             B0000_0100  //                   下降沿中断
#define INT_IT13_HE             B0000_1000  //                   上升沿中断
#define INT_IT13_LHE            B0000_1100  //                   下降上升沿中断
#define INT_IT12_L              B0000_0000  //IT12 外部中断触发沿 低电平
#define INT_IT12_LE             B0000_0001  //                   下降沿中断
#define INT_IT12_HE             B0000_0010  //                   上升沿中断
#define INT_IT12_LHE            B0000_0011  //                   下降上升沿中断

/* 外部中断2-15 使能控制寄存器PINTE0,PINTE1(初始值为0) */
#define INT_EINT7               BIT7        //0/1:禁止 / 允许 INT7端口中断
#define INT_EINT6               BIT6        //0/1:禁止 / 允许 INT6端口中断
#define INT_EINT5               BIT5        //0/1:禁止 / 允许 INT5端口中断
#define INT_EINT4               BIT4        //0/1:禁止 / 允许 INT4端口中断
#define INT_EINT3               BIT3        //0/1:禁止 / 允许 INT3端口中断
#define INT_EINT2               BIT2        //0/1:禁止 / 允许 INT2端口中断

#define INT_EINT15              BIT7        //0/1:禁止 / 允许 INT15端口中断
#define INT_EINT14              BIT6        //0/1:禁止 / 允许 INT14端口中断
#define INT_EINT13              BIT5        //0/1:禁止 / 允许 INT13端口中断
#define INT_EINT12              BIT4        //0/1:禁止 / 允许 INT12端口中断
#define INT_EINT11              BIT3        //0/1:禁止 / 允许 INT11端口中断
#define INT_EINT10              BIT2        //0/1:禁止 / 允许 INT10端口中断
#define INT_EINT9               BIT1        //0/1:禁止 / 允许 INT9端口中断
#define INT_EINT8               BIT0        //0/1:禁止 / 允许 INT8端口中断

/* 外部中断标志寄存器PINTF0,PINTF1(初始值为0) */
#define INT_INT7F               BIT7        //0/1: INT7中断请求标志位,软件清0 / 硬件置1
#define INT_INT6F               BIT6        //0/1: INT6中断请求标志位,软件清0 / 硬件置1
#define INT_INT5F               BIT5        //0/1: INT5中断请求标志位,软件清0 / 硬件置1
#define INT_INT4F               BIT5        //0/1: INT4中断请求标志位,软件清0 / 硬件置1
#define INT_INT3F               BIT3        //0/1: INT3中断请求标志位,软件清0 / 硬件置1
#define INT_INT2F               BIT2        //0/1: INT2中断请求标志位,软件清0 / 硬件置1
#define INT_INT1F               BIT1        //0/1: INT1中断请求标志位,软件清0 / 硬件置1
#define INT_INT0F               BIT0        //0/1: INT0中断请求标志位,软件清0 / 硬件置1

#define INT_INT15F              BIT7        //0/1: INT15中断请求标志位,软件清0 / 硬件置1
#define INT_INT14F              BIT6        //0/1: INT14中断请求标志位,软件清0 / 硬件置1
#define INT_INT13F              BIT5        //0/1: INT13中断请求标志位,软件清0 / 硬件置1
#define INT_INT12F              BIT4        //0/1: INT12中断请求标志位,软件清0 / 硬件置1
#define INT_INT11F              BIT3        //0/1: INT11中断请求标志位,软件清0 / 硬件置1
#define INT_INT10F              BIT2        //0/1: INT10中断请求标志位,软件清0 / 硬件置1
#define INT_INT9F               BIT1        //0/1: INT9中断请求标志位,软件清0 / 硬件置1
#define INT_INT8F               BIT0        //0/1: INT8中断请求标志位,软件清0 / 硬件置1

/* 外部中断01 管脚选择寄存器INT01_PINS (初始值为0) */
#define INT_INT1_P01            B0000_0000  //INT1管脚选择 P01
#define INT_INT1_P11            B0000_0010  //INT1管脚选择 P11
#define INT_INT0_P00            B0000_0000  //INT0管脚选择 P00
#define INT_INT0_P10            B0000_0001  //INT0管脚选择 P10
/**************************************************************************************/
/* CRC 控制寄存器 CRCC (默认0) */
#define CRC_CRCBIT              BIT2        //0/1:CRC BIT 翻转控制位->MSB / LSB first
#define CRC_CRCRSV              BIT1        //0/1:复位初值为 0x0000 / 0xFFFF
#define CRC_W_CRCRST            BIT0        //置1复位 CRC 计算器,硬件自动清0

/* CRC 数据寄存器CRCL,CRCH (默认0) */
/* CRCL 写入数据时为 CRC 计算器的输入数据;读出数据时为 CRC 计算结果的低字节 */
/*      写入数据时自动启动 CRC 计算,完后自动关闭 */
/* CRCH 对该寄存器写入数据无效,读出数据时为 CRC 计算结果的高字节 */
/* 每一次写入待计算数据，其计算结果是由与前一次计算结果共同生成 */
/* 16位CRC;CRC生成校验遵从CRC-CCITT多项式(即0x1021);初值可设为0x0000或0xFFFF */
/* 计算与结果共用同一寄存器 */
/**************************************************************************************/



/**************************************************************************************/
extern void Clk_Config_PowerOn(void);
extern void Wdt_TurnOn(void);
extern void Wdt_Clear(void);
extern u16 Crc_Calculate(u8 u8_length, u8 *u8_data_addr);

/**************************************************************************************/

