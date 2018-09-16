
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

//��ʱ����
/*
unsigned int a, b;
void delay10ms()
{
    for(a = 255; a > 0; a--)
        for(b = 255; b > 0; b--);
}
*/
//����2�������־λ
//��̬�ֲ������ĳ�ʼ�����ʽ������һ���������߳������ʽ����ʹ�ֲ���������ʱû�и�
//��ֵϵͳ���Զ�����ֵ0��������ֵ�ͱ����� ���߿��ַ������ַ�����������̬�����ĳ�ֵΪ0.
#if 0
static int  led1_flag, led2_flag;
//������һ������
static int led1(struct pt *pt)
{
    PT_BEGIN(pt);//����ʼ

    while(1)
    {
        //ִ�д���
        PT_WAIT_UNTIL(pt, led2_flag != 0);//���led2_flag != 0����������������˳���ǰ����led1(struct pt *pt),�������ִ�С�
        LED1 = 1;
        //delay10ms();
        LED1 = 0;
        led2_flag = 0;
        led1_flag = 1;
    }

    PT_END(pt);//�������
}

//�����ڶ�����
static int led2(struct pt *pt)
{
    PT_BEGIN(pt);//����ʼ

    while(1)
    {

        led2_flag = 1;
        PT_WAIT_UNTIL(pt, led1_flag != 0);
        LED2 = 1;
        delay10ms();
        LED2 = 0;
        led1_flag = 0;
    }

    PT_END(pt);//�������
}
#endif


static PT_THREAD (protothreads_led1_blink(struct pt *pt))
{
    //static unsigned char mt, hr;
    PT_BEGIN(pt);//����ʼ

    while(TRUE)
    {
        //LED1 ^= 1;
        P1_0 = ~ P1_0;
        PT_SEM_SIGNAL(&pt2, &sem);
        PT_YIELD_TIME_msec(500);// 5 X 125
    }

    PT_END(pt);//�������
}

static PT_THREAD (protothreads_led2_blink(struct pt *pt))

{
    PT_BEGIN(pt);//����ʼ

    while(TRUE)
    {

        PT_SEM_WAIT(&pt2, &sem);//wait for rate-limiting thread to release semaphore
        //LED2 ^= 1;
        P1_1 = ~ P1_1;

    }

    PT_END(pt);//�������
}





int main()
{
    globalvariable();
    /************************************ϵͳ��ʼ��****************************************/

    WDTCCR = 0x00;                      //�رտ��Ź�

    while((CLKCON & 0x20) != 0x20);     //�ȴ��ڲ���ƵRC����

    CLKSWR = 0x51;                      //ѡ���ڲ���Ƶʱ��Ϊ��ʱ�ӣ��ڲ���ƵRC2��Ƶ��Fosc=16MHz

    while((CLKSWR & 0xC0) != 0x40);     //�ȴ��ڲ���Ƶ�л����

    CLKDIV = 0x01;                      //Fosc1��Ƶ�õ�Fcpu��Fcpu=16MHz

    Timer0_Init();

    /***********************************����IO��ģʽ***************************************/
    P0M1 = P0M1 & 0xF0 | 0x00;          //P02����Ϊ����(��SMT)
    P0M0 = P0M0 & 0x0F | 0x10;          //P01����Ϊ����������(��SMT)
    P0M0 = P0M0 & 0xF0 | 0x02;          //P00����Ϊ����������(��SMT)

    //P1M0 = P1M0 & 0x0F | 0x30;          //P11����Ϊ��ģ������

    P1 = 0x03;
    P1M0 = IOH_PUSHPULL_OUT | IOL_PUSHPULL_OUT;

    P2M0 = P2M0 & 0xF0 | 0x04;          //P20����Ϊ����(SMT)
    P0M2 = P0M2 & 0x0F | 0x50;          //P05����Ϊ����������(SMT)
    P0M2 = P0M2 & 0xF0 | 0x06;          //P04����Ϊ����������(SMT)
    P0M3 = P0M3 & 0x0F | 0x80;          //P07����Ϊ�������
    P0M3 = P0M3 & 0xF0 | 0x09;          //P06����Ϊ��©���
    //P2M1 = P2M1 & 0xF0 | 0x0A;          //P22����Ϊ��������©���
    P2M1 = P2M1 & 0xF0 | 0x08;          //P22����Ϊ�������
    EA = 1;                             //�����ж�

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