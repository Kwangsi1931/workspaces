
#ifndef __GLOBAL_H_
#define __GLOBAL_H_

#ifdef   APP_GLOBALS
#define  OS_CPU_EXT
#else
#define  OS_CPU_EXT  extern
#endif


OS_CPU_EXT bit bFlag_lcd_display_is_low;
OS_CPU_EXT bit bFlag_display_update;
OS_CPU_EXT volatile unsigned int gSysTick;




void globalvariable(void);//K.S  reentrant;//用户应用程序全局变量初始化

#endif

