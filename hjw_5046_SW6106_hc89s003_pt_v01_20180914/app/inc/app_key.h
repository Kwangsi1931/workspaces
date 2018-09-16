#ifndef _key_h_
#define _key_h_

#ifdef  key_Global
#define key_EXT
#else
#define key_EXT extern
#endif



//#define KEY_EVENT_BASE_ADDR         0xA0

//#define MSG_NONE                  0x00
#define KEY_BREAK                   0x20     //
#define KEY_LONG_START              0x40     //
#define KEY_LONG                    0x80     //
#define KEY_LONG_BREAK              0x60     //important

#define K1                          0x01
#define K1_BREAK                    0x21
#define K1_LONG_START               0x41
#define K1_LONG                     0x81
#define K1_LONG_BREAK               0x61

#define GPIO_KEY_SCAN_TIME          15   //20ms
#define GPIO_KEY_JTTER_TIME         30
#define GPIO_KEY_CP_TIME            1000
#define GPIO_KEY_CPH_TIME           200  //

/*
typedef enum _GPIO_KEY_STATE
{
    GPIO_KEY_STATE_IDLE,
    GPIO_KEY_STATE_JITTER,
    GPIO_KEY_STATE_PRESS_DOWN,
    GPIO_KEY_STATE_SP,
    GPIO_KEY_STATE_CP,
    GPIO_KEY_STATE_CPR
} GPIO_KEY_STATE;
*/
typedef enum _GPIO_KEY_STATE
{
    GPIO_KEY_STATE_IDLE,
    GPIO_KEY_STATE_JITTER,
    GPIO_KEY_STATE_PRESS_DOWN,
    GPIO_KEY_STATE_CP

} GPIO_KEY_STATE;


typedef enum _KEY_EVENT
{
    MSG_NONE = 0x00,

    KEY_POWER = K1,                         // -- [0x01,0x1F]
    //TODO:

    MSG_MODE = K1_BREAK,             // -- [0x21,0x3F]
    MSG_LIGHT,
    //TODO:

    MSG_POWER_ON = K1_LONG_START,   // -- [0x41,0x5F]
    MSG_LIGHT_CPS,
    //TODO:

    KEY_POWER_LONG_BREAK = K1_LONG_BREAK,   // -- [0x61,0x7F]
    MSG_LIGHT_CPR,
    //TODO:

    KEY_POWER_LONG = K1_LONG,               // -- [0x81,0x5F]
    MSG_LIGHT_CPH,
    //TODO:

} KEY_EVENT;


void GpioKeyInit(void);

//KEY_EVENT GpioKeyScan(void);
void ChargingDetProc(void);


static KEY_EVENT GpioKeyScan(void);

//void KeyScan(void);

KEY_EVENT KeyScan(void);


#endif

