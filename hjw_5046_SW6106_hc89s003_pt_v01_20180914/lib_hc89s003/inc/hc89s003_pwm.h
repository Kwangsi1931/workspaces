/**
*   ************************************************************************************
*                               普芯达电子有限公司
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
/* PWM 控制寄存器PWMCTRL */
#define PWM_TYP2            BIT7        //0/1:PWM2 边沿对齐 / 中心对齐
#define PWM_TYP1            BIT6        //0/1:PWM1 边沿对齐 / 中心对齐
#define PWM_TYP0            BIT5        //0/1:PWM0 边沿对齐 / 中心对齐
#define PWM_RLOAD2          BIT4        //0/1:PWM2 禁止 / 使能 自动重载(默认使能)
#define PWM_RLOAD1          BIT3        //0/1:PWM1 禁止 / 使能 自动重载(默认使能)
#define PWM_RLOAD0          BIT2        //0/1:PWM0 禁止 / 使能 自动重载(默认使能)
#define PWM_PWMLEN_12B      B0000_0000  //PWM精度:12BIT
#define PWM_PWMLEN_16B      B0000_0010  //PWM精度:16BIT
#define PWM_PENCTRL_EN      B0000_0000  //PWM0_EN,PWM1_EN,PWM2_EN 控制PWM模块使能
#define PWM_PENCTRL_ENA     B0000_0001  //PWMENA 寄存器控制控制PWM模块使能输出

/* PWM 使能寄存器PWMENA (默认值0)*/
#define PWM_PWM21EN         B0100_0000  //使能PWM21输出
#define PWM_PWM11EN         B0010_0000  //使能PWM11输出
#define PWM_PWM01EN         B0001_0000  //使能PWM01输出
#define PWM_PWM2EN          B0000_0100  //使能PWM2输出
#define PWM_PWM1EN          B0000_0010  //使能PWM1输出
#define PWM_PWM0EN          B0000_0001  //使能PWM0输出
/**************************************************************************************/
/* PWM0 使能寄存器PWM0EN (默认值0)*/
#define PWM0_FLT0_M1        B0000_0000  //PWM0故障输出电平:PWM0低,PWM01低
#define PWM0_FLT0_M2        B0010_0000  //                :PWM0低,PWM01高
#define PWM0_FLT0_M3        B0100_0000  //                :PWM0高,PWM01低
#define PWM0_FLT0_M4        B0110_0000  //                :PWM0高,PWM01高
#define PWM0_EFLT0_DIS      B0000_0000  //禁止FLT0(P00)引脚故障检测,当作GPIO
#define PWM0_EFLT0_EN       B0001_0000  //允许FLT0(P00)引脚故障检测
#define PWM0_PWM0M_CPM      B0000_0000  //PWM0&PWM01工作于互补输出模式
#define PWM0_PWM0M_IDP      B0000_1000  //PWM0&PWM01工作于独立输出模式
#define PWM0_PWM01_OENEN    B0000_0100  //允许 PWM01 输出
#define PWM0_PWM0_OENEN     B0000_0010  //允许 PWM0 输出
#define PWM0_PWM0_EN        B0000_0001  //打开 PWM0 模块

/* PWM0控制寄存器PWM0C(默认值0) */
#define PWM0_IEEN           B1000_0000  //使能 PWM0 中断
#define PWM0_IFCLR          B0000_0000  //PWM0中断软件清0
#define PWM0_IFSET          B0100_0000  //PWM0中断硬件置1
#define PWM0_FLT0S_NORMAL   B0000_0000  //PWM0正常状态,软件清0
#define PWM0_FLT0S_CLOSE    B0010_0000  //PWM0输出关闭,硬件置1
#define PWM0_FLT0C_LOW      B0000_0000  //FLT0为低电平时,PWM0输出关闭
#define PWM0_FLT0C_HIGH     B0001_0000  //FLT0为高电平时,PWM0输出关闭
#define PWM0_PWM0S_0H1H     B0000_0000  //PWM0和PWM01输出模式:PWM0高,PWM01高
#define PWM0_PWM0S_0H1L     B0000_0100  //                   :PWM0高,PWM01低
#define PWM0_PWM0S_0L1H     B0000_1000  //                   :PWM0低,PWM01高
#define PWM0_PWM0S_0L1L     B0000_1100  //                   :PWM0低,PWM01低
#define PWM0_CK0_FOSC       B0000_0000  //PWM0时钟源:FOSC
#define PWM0_CK0_FOSC_8     B0000_0001  //          :FOSC/8
#define PWM0_CK0_FOSC_32    B0000_0010  //          :FOSC/32
#define PWM0_CK0_FOSC_128   B0000_0011  //          :FOSC/128

/* PWM0 周期寄存器PWM0PL,PWM0PH(默认值0) */
/* 修改PWM0周期必须先修改高位后修改低位 */
/* PWM0周期 = [ PWM0PH : PWM0PL] * PWM0工作时钟源周期 */
/* PWM0 占空比寄存器PWM0DL,PWM0DH(默认值0) */
/* 修改 PWM0 占空比寄存器,必须先修改高位后修改低位,且修改都在下一个周期才有效 */
/* PWM0 占空比 = [ PWM0DH : PWM0DL] * PWM0 工作时钟周期 */
/* PWM0 死区时间寄存器PWM0DTL,PWM0DTH */
/* 当 PWM0M=1 时,PWM0 工作在 2 路独立模式,此时的死区时间寄存器被用来当做PWM01的占空比寄存器 */
/* 即独立模式的 PWM0 可以产生 2 路周期相同，但占空比可以不同的 PWM 波形 */
/* 互补模式下:PWM0 死区时间 = [ PWM0DTH : PWM0DTL] * PWM0 工作时钟周 */
/* 互补模式下:死区时间必须小于占空比时间，死区时间与占空比时间的和必须小于PWM0周期 */
/* 独立模式下:PWM01 占空比时间 = [ PWM0DTH : PWM0DTL] * PWM0 工作时钟周期 */
/**************************************************************************************/
/* PWM1 使能寄存器PWM1EN (默认值0)*/
#define PWM1_FLT1_M1        B0000_0000  //PWM1故障输出电平:PWM1低,PWM11低
#define PWM1_FLT1_M2        B0010_0000  //                :PWM1低,PWM11高
#define PWM1_FLT1_M3        B0100_0000  //                :PWM1高,PWM11低
#define PWM1_FLT1_M4        B0110_0000  //                :PWM1高,PWM11高
#define PWM1_EFLT1_DIS      B0000_0000  //禁止FLT1(P01)引脚故障检测,当作GPIO
#define PWM1_EFLT1_EN       B0001_0000  //允许FLT1(P01)引脚故障检测
#define PWM1_PWM1M_CPM      B0000_0000  //PWM1&PWM11工作于互补输出模式
#define PWM1_PWM1M_IDP      B0000_1000  //PWM1&PWM11工作于独立输出模式
#define PWM1_PWM11_OENEN    B0000_0100  //允许 PWM11 输出
#define PWM1_PWM1_OENEN     B0000_0010  //允许 PWM1 输出
#define PWM1_PWM1_EN        B0000_0001  //打开 PWM1 模块

/* PWM1控制寄存器PWM1C(默认值0) */
#define PWM1_IEEN           B1000_0000  //使能 PWM1 中断
#define PWM1_IFCLR          B0000_0000  //PWM1中断软件清0
#define PWM1_IFSET          B0100_0000  //PWM1中断硬件置1
#define PWM1_FLT1S_NORMAL   B0000_0000  //PWM1正常状态,软件清0
#define PWM1_FLT1S_CLOSE    B0010_0000  //PWM1输出关闭,硬件置1
#define PWM1_FLT1C_LOW      B0000_0000  //FLT1为低电平时,PWM1输出关闭
#define PWM1_FLT1C_HIGH     B0001_0000  //FLT1为高电平时,PWM1输出关闭
#define PWM1_PWM1S_0H1H     B0000_0000  //PWM1和PWM11输出模式:PWM1高,PWM11高
#define PWM1_PWM1S_0H1L     B0000_0100  //                   :PWM1高,PWM11低
#define PWM1_PWM1S_0L1H     B0000_1000  //                   :PWM1低,PWM11高
#define PWM1_PWM1S_0L1L     B0000_1100  //                   :PWM1低,PWM11低
#define PWM1_CK1_FOSC       B0000_0000  //PWM1时钟源:FOSC
#define PWM1_CK1_FOSC_8     B0000_0001  //          :FOSC/8
#define PWM1_CK1_FOSC_32    B0000_0010  //          :FOSC/32
#define PWM1_CK1_FOSC_128   B0000_0011  //          :FOSC/128

/* PWM1 周期寄存器PWM1PL,PWM1PH(默认值0) */
/* PWM1 占空比寄存器PWM1DL,PWM1DH(默认值0) */
/* PWM1 死区时间寄存器PWM1DTL,PWM1DTH */
/**************************************************************************************/
/* PWM2 使能寄存器PWM2EN (默认值0)*/
#define PWM2_FLT2_M1        B0000_0000  //PWM1故障输出电平:PWM2低,PWM21低
#define PWM2_FLT2_M2        B0010_0000  //                :PWM2低,PWM21高
#define PWM2_FLT2_M3        B0100_0000  //                :PWM2高,PWM21低
#define PWM2_FLT2_M4        B0110_0000  //                :PWM2高,PWM21高
#define PWM2_EFLT2_DIS      B0000_0000  //禁止FLT2(P02)引脚故障检测,当作GPIO
#define PWM2_EFLT2_EN       B0001_0000  //允许FLT2(P02)引脚故障检测
#define PWM2_PWM2M_CPM      B0000_0000  //PWM2&PWM21工作于互补输出模式
#define PWM2_PWM2M_IDP      B0000_1000  //PWM2&PWM21工作于独立输出模式
#define PWM2_PWM21_OENEN    B0000_0100  //允许 PWM21 输出
#define PWM2_PWM2_OENEN     B0000_0010  //允许 PWM2 输出
#define PWM2_PWM2_EN        B0000_0001  //打开 PWM2 模块

/* PWM2 控制寄存器PWM2C(默认值0) */
#define PWM2_IEEN           B1000_0000  //使能 PWM2 中断
#define PWM2_IFCLR          B0000_0000  //PWM2中断软件清0
#define PWM2_IFSET          B0100_0000  //PWM2中断硬件置1
#define PWM2_FLT2S_NORMAL   B0000_0000  //PWM2正常状态,软件清0
#define PWM2_FLT2S_CLOSE    B0010_0000  //PWM2输出关闭,硬件置1
#define PWM2_FLT2C_LOW      B0000_0000  //FLT2为低电平时,PWM2输出关闭
#define PWM2_FLT2C_HIGH     B0001_0000  //FLT2为高电平时,PWM2输出关闭
#define PWM2_PWM2S_0H1H     B0000_0000  //PWM2和PWM21输出模式:PWM2高,PWM21高
#define PWM2_PWM2S_0H1L     B0000_0100  //                   :PWM2高,PWM21低
#define PWM2_PWM2S_0L1H     B0000_1000  //                   :PWM2低,PWM21高
#define PWM2_PWM2S_0L1L     B0000_1100  //                   :PWM2低,PWM21低
#define PWM2_CK2_FOSC       B0000_0000  //PWM2时钟源:FOSC
#define PWM2_CK2_FOSC_8     B0000_0001  //          :FOSC/8
#define PWM2_CK2_FOSC_32    B0000_0010  //          :FOSC/32
#define PWM2_CK2_FOSC_128   B0000_0011  //          :FOSC/128

/* PWM2 周期寄存器PWM2PL,PWM2PH(默认值0) */
/* PWM2 占空比寄存器PWM2DL,PWM2DH(默认值0) */
/* PWM2 死区时间寄存器PWM2DTL,PWM2DTH */
/**************************************************************************************/
/* 用户应用定义PWM 输出PIN */
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
#define PMW0_PERIOD                 (32000000/PWM0_FREQ)        //周期
#define PWM0_DUTY                   (PMW0_PERIOD * 50 /100)     //50%
#define PWM0_DEAD                   (PWM0_DUTY * 5 /100)        //死区时间为DUYT的5%
#define PWM01_DUTY                  (PMW0_PERIOD * 80 /100)     //80%

#define PWM1_FREQ                   50000                       //50K
#define PMW1_PERIOD                 (32000000/PWM1_FREQ)        //周期
#define PWM1_DUTY                   (PMW1_PERIOD * 20 /100)     //20%
#define PWM1_DEAD                   (PWM1_DUTY * 5 /100)        //死区时间为DUYT的5%
#define PWM11_DUTY                  (PMW1_PERIOD * 30 /100)     //30%

#define PWM2_FREQ                   200000                      //200K
#define PMW2_PERIOD                 (32000000/PWM2_FREQ)        //周期
#define PWM2_DUTY                   (PMW2_PERIOD * 50 /100)     //50%
#define PWM2_DEAD                   (PWM2_DUTY * 10 /100)       //死区时间为DUYT的10%
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

