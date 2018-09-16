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

//ÓÃÓÚÅĞ¶ÏtimerÊÇ·ñµ½ÆÚ
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


//ÖØÖÃÎª´ÓÉÏ´Îµ½ÆÚ£¨expired£©µÄÊ±¼ä¿ªÊ¼¼ÆÊ±¡£
void timer_reset(TIMER *t)
{
    t->start += t->interval;
}

//½«timerÖØÖÃÎª´Óµ±Ç°Ê±¼ä¿ªÊ¼¼ÆÊ±¡£
void timer_restart(TIMER *t)
{
    TM0IE = 0;
    t->start = gSysTick;
    TM0IE = 1;
}

//timer_remainingÓÃÓÚ»ñµÃÀëtimerµ½ÆÚµÄ¼ä¸ô£¨return the time until the timer expires£©
//Ê£ÓàÊ±¼ä
clock_time_t timer_remaining(TIMER *t)
{
	unsigned int   time;
	TM0IE = 0;
    time = gSysTick;
    TM0IE = 1;
    return (t->start + t->interval - time);
}

//²¥·ÅÊ±¼ä(¼ÆÊ±ÁË¶à¾Ãå?)
unsigned int PastTimeGet(TIMER   *timer)
{
    unsigned int    temp;
    TM0IE = 0;
    temp = gSysTick - timer->start;
    TM0IE = 1;
    return temp;
}


