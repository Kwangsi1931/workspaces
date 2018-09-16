#ifndef _APP_CFG_H_
#define _APP_CFG_H_

#define ESP2811S21
//#define ESP2822

//#define FUNC_ADC_KEY_EN

#if  !(defined ESP2822 | defined ESP2811S21 | defined HC89S003)
#error "请先选择芯片类型！！！"
#endif

typedef unsigned char       BOOL;
typedef unsigned char       BOOLEAN;
typedef unsigned char       BYTE;
typedef unsigned char       INT8U;
typedef signed char         INT8S;
typedef unsigned int        INT16U;
typedef signed int          INT16S;
typedef unsigned long       INT32U;
typedef signed long         INT32S;
typedef float               FP32;
typedef double              FP64;
typedef unsigned int        clock_time_t;
typedef unsigned char       u8_t;
typedef signed char         s8_t;
typedef unsigned int        u16_t;
typedef signed int          s16_t;
typedef unsigned long int   u32_t;
typedef signed long int     s32_t;
typedef unsigned char       u8;
typedef signed char         s8;
typedef unsigned int        u16;
typedef signed int          s16;
typedef unsigned long       u32;
typedef signed long         s32;

#ifndef TRUE
#define TRUE    (1)
#endif

#ifndef FALSE
#define FALSE   (0)
#endif


typedef enum _MODE_STATE
{
    MODE_STANDBY,
    MODE_LIGHT_OFF,
    MODE_LIGHT_ON,
    MODE_FAN_OFF,
    MODE_FAN_ON
} MODE_STATE;

#define SEG_A               0X01
#define SEG_B               0X02
#define SEG_C               0X04
#define SEG_D               0X08
#define SEG_E               0X10
#define SEG_F               0X20
#define SEG_G               0X40

struct BITSET
{
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
    unsigned char bit2 : 1;
    unsigned char bit3 : 1;
    unsigned char bit4 : 1;
    unsigned char bit5 : 1;
    unsigned char bit6 : 1;
    unsigned char bit7 : 1;
};

//TYPE-C状态
#define TYPEC_NO_CONNECT                0
#define TYPEC_IN                        1
#define TYPEC_OUT                       2

#define RES_NTC_42                      495
#define RES_NTC_48                      392
#define RES_NTC_58                      270

#define CONST_BAT_4V05_ADC              498
#define CONST_BAT_3V8_ADC               467
#define CONST_BAT_3V75_ADC              461
#define CONST_BAT_3V45_ADC              424
#define CONST_BAT_3V15_ADC              387
#define CONST_BAT_3V20_ADC              412//393
#define CONST_BAT_3V00_ADC              390//368

#define CONST_HEATING_TIMER             32





#define  ETA9640_LED        PA0

#define  LED_BLUE_IN        CPIOPA1 = 1
#define  LED_BLUE_OUT       CPIOPA1 = 0
#define  LED_BLUE_ON        PA1 = 1
#define  LED_BLUE_OFF       PA1 = 0

#define FAN_OUTPUT          CPIOPA2 = 0
#define FAN_OFF             PA2 = 0
#define FAN_ON              PA2 = 1


#define  LED_LIGHT_IN       CPIOPA5 = 1
#define  LED_LIGHT_OUT      CPIOPA5 = 0
#define  LED_LIGHT_ON       PA5 = 1
#define  LED_LIGHT_OFF      PA5 = 0

#define PIN_KEY_LIGHT               RA5
#define KEY_LIGHT_INPUT             CPIOPA5 = 1
#define KEY_LIGHT_OUTPUT             CPIOPA5 = 0


#define PIN_KEY_POWER               RA4
#define KEY_POWER_INPUT             CPIOPA4 = 1
#define KEY_POWER_OUTPUT             CPIOPA4 = 0

//#define PIN_KEY_POWER               RC5
//#define KEY_POWER_INPUT             CPIOPC5 = 1
//#define KEY_POWER_OUTPUT             CPIOPC5 = 0

#define  PIN_DCIN           PA3
#define  DCIN_INPUT         CPIOPA3 = 1
#define  DCIN_OUTPUT        CPIOPA3 = 0




#define ADC_CH_BAT          7  //



///#define OPEN_HEAT_SWITCH
#if 0//def LED_188
#define LED1                            RA5                       //LED输出
#define LED2                            RA4                       //LED输出
#define LED3                            RC5                       //LED输出
#define LED4                            RC4                       //LED输出
#define LED5                            RC1                       //LED输出
#define LED1M                           CPIOPA5
#define LED2M                           CPIOPA4
#define LED3M                           CPIOPC5
#define LED4M                           CPIOPC4
#define LED5M                           CPIOPC1
#endif
#if 0
#define KEY_OUT                         RC3                     //按键输出
#define TEST_PIN                        PA0
#define I2C_EXTI_IN                     RC2                     //I2C外部中断输入
#define I2C_SDA                         RC6                     //I2C数据
#define I2C_SCL                         RC7                     //I2C时钟
#define I2C_SDA_M                       CPIOPC6
#define I2C_SCL_M                       CPIOPC7
#define SET_SCL_OUT()                   I2C_SCL_M=0
#define SET_SDA_OUT()                   I2C_SDA_M=0
#define SET_SCL_IN()                    I2C_SCL_M=1
#define SET_SDA_IN()                    I2C_SDA_M=1
#define TYPE_C_SIM_EN_OUT()             CPIOPC0=0
#define TYPE_C_SIM_EN_IN()              CPIOPC0=1
#define DisableWdt()                    SWDTEN=0               //关看门狗
#define EnableWdt()                     SWDTEN=1              //开看门狗
#define DisableGlobalIntterupt()        GIE=0               //关总中断
#define EnableGlobalIntterupt()         GIE=1               //开总中断
#define DisablePeripheralIntterupt()    PEIE=0               //关外围中断
#define EnablePeripheralIntterupt()     PEIE=1               //开外围中断
#define DisableTimer0Intterupt()        TM0IE=0              //关定时器0中断
#define EnableTimer0Intterupt()         TM0IE=1              //开定时器0中断
#define DisableAdcIntterupt()           ADIE=0              //关AD中断
#define EnableAdcIntterupt()            ADIE=1             //开AD中断
#define DisablePA2ExtIntterupt()        INTE=0              //关PA2外部中断
#define EnablePA2ExtIntterupt()         INTE=1             //开PA2外部中断
#define DisablePortAIntterupt()         RAIE=0              //关PA口边沿中断
#define EnablePortAIntterupt()          RAIE=1             //开PA口边沿中断
#define DisablePA1EdgIntterupt()        PINTA1=0              //关PA1边沿中断
#define EnablePA1EdgIntterupt()         PINTA1=1             //开PA1边沿中断
#define DisablePA2EdgIntterupt()        PINTA2=0              //关PA2边沿中断
#define EnablePA2EdgIntterupt()         PINTA2=1             //开PA2边沿中断
#define DisablePA3EdgIntterupt()        PINTA3=0              //关PA3边沿中断
#define EnablePA3EdgIntterupt()         PINTA3=1             //开PA3边沿中断
#define DisablePC2ExtIntterupt()        INTC2E=0              //关PC2外部中断
#define EnablePC2ExtIntterupt()         INTC2E=1             //开PC2外部中断
#define DisablePC3ExtIntterupt()        INTC3E=0              //关PC3外部中断
#define EnablePC3ExtIntterupt()         INTC3E=1             //开PC3外部中断
#endif
#define ClrWdt()                        asm("clrwdt")
#define Sleep()                         asm("sleep")
#define Reset()                         asm("reset")
#define Nop()                           asm("nop")
#define KEY_DELAY_DET_TIME              100

//定时器0参数
#define TIMER0_CNT                      6                          //定时器0定时初值
#define TIME_CNT_MAX                    250
#define TIME_1MS_CNT                    4
#define TIME_100MS_CNT                  10
#define TIME_150MS_CNT                  15
#define TIME_500MS_CNT                  50
//AD参数
#define AD_12BIT                        0                       //12位AD
#define AD_10BIT                        1                       //10位AD
#define ADC_LOAD_OUT_I                  1                         //普通USBA口拔出采样通道
//#define ADC_LOAD_IN_V                   2                       //普通USBA口插入采样通道

//普通USBA口插入检测
#define AUTO_OUT_SUCCESS                1
#define AUTO_OUT_FAIL                   0
//休眠参数
#define SW6124_SLEEP_MODE               0
#define SW6124_WORK_MODE                1
#define DELAY_SLEEP_TIME                4                     //延时休眠时间-->2S

#define C_TM0_Value                     6 // 6 --> 1ms ;244 ---> 50us        //50us
#define C_IDLE_mode                     0
#define C_charge_on_mode                1
#define C_charge_full_mode              2
#define C_FOD_mode                      3
#define C_error_mode                    4

#define C_PWM_MAX_POWER_PRE             145     //155          //fre_108khz
//fre_175khz
#define C_PWM_MIN_POWER_PRE             80      //fre_208KHZ
#define C_PWM_INI_POWER_PRE             100//30    //66      //95
#define C_PWM_first_POWER_PRE           125     //128
#define C_IDLE_LOOP_DUTY                65
#define C_IDLE_LOOP_TIME                100

#define C_FOD_TEST_VALUE                0X100     //0.625v
#define C_noFOD_TEST_VALUE              (C_FOD_TEST_VALUE-15)
#define C_OVER_LOAD_VALUE               512  //360


#define CONST_DET_JITTER                8
#define CONST_DISP_TIME                 5
#define CONST_5SEC_TIMER                300



#define LED_DISP_TIME                   1
#define KEY_ON                          0            //按键闭合
#define KEY_OFF                         1            //按键弹起

#define CONST_PWM_SCALE_L    224
#define CONST_PWM_SCALE_M    243
#define CONST_PWM_SCALE_H    255



//#define CONST_SCALE_48    (392/(392+3000))
//#define CONST_SCALE_58    (270/(270+3000))

#if 0
#define WorkIn250K   1      //工作在250k 需打开，125k屏蔽
#define PWMEnable()  {T2CON = BIN(1,1,1,1,0,0,0,1);}   //charge pwm setup  60khz
#define PWMDisable() {T2CON = BIN(0,1,1,1,0,0,0,0);}
#if  WorkIn250K
#define PWM2Enable()  {T3CON = BIN(1,1,1,1,0,0,1,1);}
#define PWM2Disable() {T3CON = BIN(0,1,1,1,0,0,1,0);}
#define PWM1Enable()  {T2CON = BIN(1,1,1,1,0,0,1,1);}
#define PWM1Disable() {T2CON = BIN(0,1,1,1,0,0,1,0);}
#else
#define PWM2Enable()  {T3CON = BIN(1,1,1,0,0,0,1,1);}
#define PWM2Disable() {T3CON = BIN(0,1,1,0,0,0,1,0);}
#define PWM1Enable()  {T2CON = BIN(1,1,1,0,0,0,1,1);}
#define PWM1Disable() {T2CON = BIN(0,1,1,0,0,0,1,0);}
#endif
#endif

//#define turn_on_bat_ad()    {ADCON0 &= BIN(1,0,0,0,0,0,0,1);ADCON0 |= BIN(0,0,0,1,1,1,0,0);} //test 1/4 vdd
// {ADCON0 &= BIN(1,0,0,0,0,0,0,1);ADCON0 |= BIN(0,0,0,0,1,0,0,0);}
//#define turn_on_fb_ad()    {ADCON0 &= BIN(1,0,0,0,0,0,0,1);ADCON0 |= BIN(0,0,0,0,1,1,0,0);}
//#define turn_on_fb_ad()      {ADCON0 &= BIN(1,0,0,0,0,0,0,1);ADCON0 |= BIN(0,0,0,1,1,1,0,0);} //test 1/4 vdd
//#define turn_on_current_ad() {ADCON0 &= BIN(1,0,0,0,0,0,0,1);ADCON0 |= BIN(0,0,0,0,0,0,0,0);}     //PA0
//#define turn_on_charge_current_ad() {ADCON0 &= BIN(1,0,0,0,0,0,0,1);ADCON0 |= BIN(0,0,0,0,0,10,0,0);}  //PA0
//#define FB_CH        0
//#define BAT_CH       7
//#define DISCHAR_CH   2
//#define CHAR_CH      3
//#define ADC_CH_IOUT        0  //PA0  //discharge
//#define ADC_CH_BAT        7  //
#endif
