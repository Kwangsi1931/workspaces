#define key_Global
#include "app_cfg.h"
#include "app_timer.h"
#include "app_key.h"


const BYTE GpioKeyEvent[][5] =
{
    //PDS(按键开始)      SPR(短按松开)      CPS(长按开始)       CPH(长按保持)           CPR(长按松开)
    {MSG_NONE,           MSG_MODE,          MSG_POWER_ON,       KEY_POWER_LONG,         KEY_POWER_LONG_BREAK},  //K1
    {MSG_NONE,           MSG_LIGHT,         MSG_LIGHT_CPS,      MSG_LIGHT_CPH,          MSG_LIGHT_CPR       },  //K2
};

TIMER gpioKeyWaitTimer;
//TIMER gpioKeyScanTimer;
GPIO_KEY_STATE GpioKeyState;

void GpioKeyInit(void)
{
    GpioKeyState = GPIO_KEY_STATE_IDLE;
    //timer_set(&gpioKeyScanTimer, 0);
}

static u8_t GetGpioKeyIndex(void)
{
    u8_t pin_store = PORTA;
    u8_t KeyIndex = 0xFF;
    KEY_POWER_INPUT;
    KEY_LIGHT_INPUT;
    _dly_us(10);

    if(PIN_KEY_POWER == 0)
    {
        KeyIndex = 0;
    }
    else
    {

        KEY_POWER_OUTPUT;
        PIN_KEY_POWER = 0;
        _dly_us(100);

        if(PIN_KEY_LIGHT == 0)
        {
            KeyIndex = 1;
        }


    }

    KEY_POWER_INPUT;
    KEY_LIGHT_OUTPUT;
    PORTA = pin_store;

    return KeyIndex;

}

static KEY_EVENT GpioKeyScan(void)
//KEY_EVENT GpioKeyScan(void)
{
    static  unsigned char    PreKeyIndex = 0xFF;
    BYTE KeyIndex;
    KeyIndex = GetGpioKeyIndex();

    switch(GpioKeyState)
    {
        case GPIO_KEY_STATE_IDLE:
            if(KeyIndex == 0xFF)
            {
                return MSG_NONE;
            }

            PreKeyIndex = KeyIndex;
            timer_set(&gpioKeyWaitTimer, GPIO_KEY_JTTER_TIME);
            //DBG(("GOTO JITTER!\n"));
            GpioKeyState = GPIO_KEY_STATE_JITTER;

        case GPIO_KEY_STATE_JITTER:
            if(PreKeyIndex != KeyIndex)
            {
                //DBG(("GOTO IDLE Because jitter!\n"));
                GpioKeyState = GPIO_KEY_STATE_IDLE;
            }
            else if(timer_expired(&gpioKeyWaitTimer))
            {
                //DBG(("GOTO PRESS_DOWN!\n"));
                //KEY_OUT = 0;
                timer_set(&gpioKeyWaitTimer, GPIO_KEY_CP_TIME);
                GpioKeyState = GPIO_KEY_STATE_PRESS_DOWN;
                return GpioKeyEvent[PreKeyIndex][0];//PDS(按键开始)
            }

            break;

        case GPIO_KEY_STATE_PRESS_DOWN:
            if(PreKeyIndex != KeyIndex)
            {
                //DBG(("ADC KEY SP!**********\n"));
                //KEY_OUT = 1;
                GpioKeyState = GPIO_KEY_STATE_IDLE;
                return GpioKeyEvent[PreKeyIndex][1]; //SPR(短按松开)
            }
            else if(timer_expired(&gpioKeyWaitTimer))
            {
                //DBG(("ADC KEY CP!*****************************\n"));
                //KEY_OUT = 1;
                timer_set(&gpioKeyWaitTimer, GPIO_KEY_CPH_TIME);
                GpioKeyState = GPIO_KEY_STATE_CP;
                return GpioKeyEvent[PreKeyIndex][2];  //CPS(长按开始)
            }

            break;

        case GPIO_KEY_STATE_CP:
            if(PreKeyIndex != KeyIndex)
            {
                //DBG(("ADC KEY CPR!****************************************************\n"));
                GpioKeyState = GPIO_KEY_STATE_IDLE;
                return GpioKeyEvent[PreKeyIndex][4]; //CPR(长按松开)
            }
            else if(timer_expired(&gpioKeyWaitTimer))
            {
                timer_set(&gpioKeyWaitTimer, GPIO_KEY_CPH_TIME);
                return GpioKeyEvent[PreKeyIndex][3]; // CPH(长按保持)
            }

            break;

        default:
            GpioKeyState = GPIO_KEY_STATE_IDLE;
            break;
    }

    return MSG_NONE;

}


KEY_EVENT KeyScan(void)
{
    KEY_EVENT   imsg = MSG_NONE;//MSG_NONE;

    if(imsg == MSG_NONE)
    {
        imsg = GpioKeyScan();
    }

#ifdef FUNC_ADC_KEY_EN

    if(imsg == MSG_NONE)
    {
        imsg = AdcKeyScan();
    }

#endif

#ifdef FUNC_IR_DECD_EN

    if(imsg == MSG_NONE)
    {
        imsg = IrKeyScan();//IrKeyEventGet();
    }

#endif

#if 0

    if(imsg != MSG_NONE)
    {
        //uart0_send_byte(0xff);
        //uart0_send_byte(imsg);
        //MessageSend(MSG_FIFO_PLAY_CTRL, imsg);
        //MessageSend(MSG_FIFO_DEV_CTRL, imsg);
        //MessageSend(MSG_FIFO_FS_CTRL, imsg);
        //MessageSend(MSG_FIFO_EXT_CTRL, imsg);
        //MessageSend(MSG_FIFO_DISP_CTRL, imsg);
        if(imsg == MSG_POWER_ON)
        {

        }
        else if(imsg == MSG_MODE)
        {

        }
    }

#endif

    return imsg;                                   //cache key value for respective module
}

