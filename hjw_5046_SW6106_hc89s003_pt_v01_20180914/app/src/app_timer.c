#include "HC89S003F4.h"
#define TIMER_GLOBALS
#include "app_timer.h"
#include "app_cfg.h"
#include "app_global.h"

#define TM0IE  ET0

void timer_set(TIMER *timer, unsigned int timeout)
{
    TM0IE = 0;
    timer->start = gSysTick;
    TM0IE = 1;
    timer->interval = timeout;
    timer->IsTimeOut = FALSE;


}

//�����ж�timer�Ƿ���
BOOL timer_expired(TIMER *timer)
{

    if(!timer->IsTimeOut)
    {
        TM0IE = 0;

        if((unsigned int)(gSysTick - timer->start) > timer->interval )
        {
            timer->IsTimeOut = TRUE;
        }

        TM0IE = 1;
    }

    return timer->IsTimeOut;
}

// Get now time from system start.
//
unsigned int TimeNow(void)
{
    unsigned int   time;
    TM0IE = 0;
    time = gSysTick;
    TM0IE = 1;
    return time;

}


//����Ϊ���ϴε��ڣ�expired����ʱ�俪ʼ��ʱ��
void timer_reset(TIMER *t)
{
    t->start += t->interval;
}

//��timer����Ϊ�ӵ�ǰʱ�俪ʼ��ʱ��
void timer_restart(TIMER *t)
{
    TM0IE = 0;
    t->start = gSysTick;
    TM0IE = 1;
}

//timer_remaining���ڻ����timer���ڵļ����return the time until the timer expires��
//ʣ��ʱ��
clock_time_t timer_remaining(TIMER *t)
{
	unsigned int   time;
	TM0IE = 0;
    time = gSysTick;
    TM0IE = 1;
    return (t->start + t->interval - time);
}

//����ʱ��(��ʱ�˶���?)
unsigned int PastTimeGet(TIMER   *timer)
{
    unsigned int    temp;
    TM0IE = 0;
    temp = gSysTick - timer->start;
    TM0IE = 1;
    return temp;
}


