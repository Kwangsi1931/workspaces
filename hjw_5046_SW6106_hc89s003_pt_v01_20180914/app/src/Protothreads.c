
#define ALLOCATE_EXTERN
#include "HC89S003F4.h"
#include "app_cfg.h"
#include "app_global.h"
#include "hc89s003_gpio.h"

#include "hc89s003_timer0.h"

#include "pt_cornell_1_1.h"


sbit LED1 = P1 ^ 0;
sbit LED2 = P1 ^ 1;



static struct pt pt1, pt2;
static struct pt_sem sem;

//延时函数
/*
unsigned int a, b;
void delay10ms()
{
    for(a = 255; a > 0; a--)
        for(b = 255; b > 0; b--);
}
*/
//创建2个任务标志位
//静态局部变量的初始化表达式必须是一个常量或者常量表达式。即使局部变量定义时没有付
//初值系统会自动付初值0（对于数值型变量） 或者空字符（对字符变量），静态变量的初值为0.
#if 0
static int  led1_flag, led2_flag;
//创建第一个任务
static int led1(struct pt *pt)
{
    PT_BEGIN(pt);//任务开始

    while(1)
    {
        //执行代码
        PT_WAIT_UNTIL(pt, led2_flag != 0);//如果led2_flag != 0这个条件不成立则退出当前任务led1(struct pt *pt),否则继续执行。
        LED1 = 1;
        //delay10ms();
        LED1 = 0;
        led2_flag = 0;
        led1_flag = 1;
    }

    PT_END(pt);//任务结束
}

//创建第二任务
static int led2(struct pt *pt)
{
    PT_BEGIN(pt);//任务开始

    while(1)
    {

        led2_flag = 1;
        PT_WAIT_UNTIL(pt, led1_flag != 0);
        LED2 = 1;
        delay10ms();
        LED2 = 0;
        led1_flag = 0;
    }

    PT_END(pt);//任务结束
}
#endif


static PT_THREAD (protothreads_led1_blink(struct pt *pt))
{
    //static unsigned char mt, hr;
    PT_BEGIN(pt);//任务开始

    while(TRUE)
    {
        //LED1 ^= 1;
        P1_0 = ~ P1_0;
        PT_SEM_SIGNAL(&pt2, &sem);
        PT_YIELD_TIME_msec(500);// 5 X 125
    }

    PT_END(pt);//任务结束
}

static PT_THREAD (protothreads_led2_blink(struct pt *pt))

{
    PT_BEGIN(pt);//任务开始

    while(TRUE)
    {

        PT_SEM_WAIT(&pt2, &sem);//wait for rate-limiting thread to release semaphore
        //LED2 ^= 1;
        P1_1 = ~ P1_1;

    }

    PT_END(pt);//任务结束
}





int main()
{
    globalvariable();
    /************************************系统初始化****************************************/

    WDTCCR = 0x00;                      //关闭看门狗

    while((CLKCON & 0x20) != 0x20);     //等待内部高频RC起振

    CLKSWR = 0x51;                      //选择内部高频时钟为主时钟，内部高频RC2分频，Fosc=16MHz

    while((CLKSWR & 0xC0) != 0x40);     //等待内部高频切换完成

    CLKDIV = 0x01;                      //Fosc1分频得到Fcpu，Fcpu=16MHz

    Timer0_Init();

    /***********************************设置IO口模式***************************************/
    P0M1 = P0M1 & 0xF0 | 0x00;          //P02设置为输入(无SMT)
    P0M0 = P0M0 & 0x0F | 0x10;          //P01设置为带下拉输入(无SMT)
    P0M0 = P0M0 & 0xF0 | 0x02;          //P00设置为带上拉输入(无SMT)

    //P1M0 = P1M0 & 0x0F | 0x30;          //P11设置为带模拟输入

    P1 = 0x03;
    P1M0 = IOH_PUSHPULL_OUT | IOL_PUSHPULL_OUT;

    P2M0 = P2M0 & 0xF0 | 0x04;          //P20设置为输入(SMT)
    P0M2 = P0M2 & 0x0F | 0x50;          //P05设置为带下拉输入(SMT)
    P0M2 = P0M2 & 0xF0 | 0x06;          //P04设置为带上拉输入(SMT)
    P0M3 = P0M3 & 0x0F | 0x80;          //P07设置为推挽输出
    P0M3 = P0M3 & 0xF0 | 0x09;          //P06设置为开漏输出
    //P2M1 = P2M1 & 0xF0 | 0x0A;          //P22设置为带上拉开漏输出
    P2M1 = P2M1 & 0xF0 | 0x08;          //P22设置为推挽输出
    EA = 1;                             //打开总中断

    PT_INIT(&pt1);
    PT_INIT(&pt2);

    LED1 = 1;
    LED2 = 1;

    while(1)
    {

        protothreads_led1_blink(&pt1);
        protothreads_led2_blink(&pt2);
    }
}