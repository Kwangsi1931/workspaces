
#define APP_GLOBALS

#include "app_global.h"



//用户应用程序全局变量初始化
void globalvariable (void) //K.S reentrant
{
    bFlag_lcd_display_is_low = 0;
    bFlag_display_update = 0;
}

