#if !defined(__TIMER_H__)
#define __TIMER_H__

#include "app_cfg.h"

/*
**********************************************************
*                   GLOBAL DATA TYPE
**********************************************************
*/
// define softtimer structure.
typedef struct  _TIMER
{
    unsigned int start;                                 //time out value
    unsigned int interval;                                 //softtimer setting value
    BOOL IsTimeOut;                                  //time out flag
} TIMER;



/*
**********************************************************
*                   GLOBAL VARIABLE
**********************************************************
*/
#ifdef  TIMER_GLOBALS
#define TIMER_EXT
#else
#define TIMER_EXT   extern
#endif
/*TIMER_EXT*/  //extern unsigned int       gSysTick;                   //system tick counter
//PB70 TIMER_EXT   unsigned int            gTimer0Count;

/*
**********************************************************
*                   GLOBAL FUNCTIONS PROTOTYPE
**********************************************************
*/
//
// Get now time from system start.
//
unsigned int TimeNow(void);

//
// Get time of some softtimer from setting to now.
//
unsigned int PastTimeGet(TIMER   *timer);

//
// Set time out value of softtimer.
//
void timer_set(TIMER *timer, unsigned int timeout);

//
// Check whether time out.
//
BOOL timer_expired(TIMER *timer);

#endif
