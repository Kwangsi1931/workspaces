//#include <reg51_ca.h>
//#include "io_define.h"
//#include "app_cfg"

//#include "ca69f_uart0.h"

#include "HC89S003F4.h"
#include "app_global.h"

//GPIO0 ^= BIT7;//GPIO7
//GPIO1 ^= BIT6;//GPIO14
//GPIO1 ^= BIT7;//GPIO15

// system time

#if 0
#define CONST_ERROR          168
#define CONST_ERROR1          89

#define Timer0_dwlimit_135   (4148 - CONST_ERROR)// 9+4.5=13.5ms  13500 / 3.255 = 4148
#define Timer0_uplimit_135   (4148 + CONST_ERROR)

#define Timer0_dwlimit_115    (3400 - CONST_ERROR)// 9+2.5=11.5ms 11500/3.255 = 3533
#define Timer0_uplimit_115    (3400 + CONST_ERROR)

#define Timer0_dwlimit_112    (345 - CONST_ERROR1)//0.565+0.56=1.125ms  1125/3.255 = 345  50//
#define Timer0_uplimit_112    (345 + CONST_ERROR1)

#define Timer0_dwlimit_225     (691 - CONST_ERROR1)//0.565+1.685=2.25ms  2250/3.255 = 691
#define Timer0_uplimit_225     (691 + CONST_ERROR1)

//#define Timer0_erorr_count     (46083)//150ms   150000/3.255 = 46083
#if 0
void Default_state(void)
{
    bFlag_start_timer1 = 0;
    bFlag_get_data = 0;
    TR1 = 0;//Timer0_stop();
}
#endif

void EXINT0_ISR (void) interrupt 0 //using 1
{
    u16_t  temp2;
    static volatile u16_t  pulse_width;

    static volatile u8_t IR_Data_Number;

    if (bFlag_start_timer1 == 0)
    {
        EA = 0;
        //TR1 = 0;
        Timer1_data = ((u16_t)TH1) << 8 | (u16_t)TL1;
        TR1 = 1;
        EA = 1;
        bFlag_start_timer1 = 1;
        IR_Data_Number = 32;
        pulse_width = 0xFFFF;


    }
    else
    {
        EA = 0;
        TR1 = 0;
        temp2 = ((u16_t)TH1) << 8 | (u16_t)TL1;
        TR1 = 1;
        EA = 1;
        pulse_width = temp2 - Timer1_data;
        Timer1_data = temp2;


        if (0 == bFlag_get_data)
        {

            if ((pulse_width < Timer0_uplimit_135) && (pulse_width > Timer0_dwlimit_135)) //key is pressed

            {
                bFlag_get_data = 1;

            }
            else if ((pulse_width < Timer0_uplimit_115) && (pulse_width > Timer0_dwlimit_115)) //continue key

            {

                IR_KEY_TO_SYS = IR_KEY_DATA;
                Series_key_flag = TRUE;
                IR_KEY_ON = TRUE;
                irc_break_timer = gp_10ms_timer;
                Default_state();

            }
            else//no key
            {
                Default_state();
            }
        }
        else
        {

            if ((Timer0_dwlimit_225 < pulse_width) && (Timer0_uplimit_225 > pulse_width)) //value is: 1

            {
                IR_Data_Number--;
                IR_KEY_DATA |= (1L << IR_Data_Number);

            }
            else if ((Timer0_dwlimit_112 < pulse_width) && (Timer0_uplimit_112 > pulse_width)) //value is: 0

            {
                IR_Data_Number--;
                IR_KEY_DATA &= ~(1L << IR_Data_Number);

            }
            else//key error
            {
                Default_state();
            }



            if (!IR_Data_Number)//finish to decode
            {
                IR_KEY_TO_SYS = IR_KEY_DATA;
                IR_KEY_ON = TRUE;
                Series_key_flag = FALSE;
                IR_Data_Number = 32;
                //bFlag_IR_Timer_Out = 0;//
                irc_break_timer = gp_10ms_timer;
                Default_state();
            }

        }

    }

}
#endif

//TIMER0_VECTOR
//1ms
void TIMER0_ISR (void) interrupt TIMER0_VECTOR //using 1
{

    gSysTick++;
    P2_2 = ~ P2_2;                      //P22·­×ª

}

void EXINT1_ISR (void) interrupt 2 //using 1
{

}



void TIMER1_ISR (void) interrupt 3 //using 1
{

    //gSysTick++;
}



#ifdef HAVE_TIME2_EN
//#define T2_LOW      0x00
//#define T2_HIGH         0xEE            //1ms
void TIMER2_ISR (void) interrupt 5 //using 1
{
    //static bit flag=0;
    // static INT8U timecnt=0,timecnt2=0,i=0;
    //TL2 = T2_LOW;
    //TH2 = T2_HIGH;
    TR2 = 0;

    if(TF2)
    {
        TF2 = 0;
#if 0//def LED_IO_PWM_EN
        led_io_pwm_scan();
#endif
        // flag=!flag;
        // if(flag)
        // {
        // GPIO0_CFG_OUTPUT;
        // GPIO0(1);
        // }
        // else
        // {
        // GPIO0_CFG_OUTPUT;
        // GPIO0(0);
        // }
    }

    //TR2 = 1;
}
#endif


//===========================UART0
#ifdef USE_UART0
void UART0_ISR (void) interrupt 4 //using 1
{
    if(RI0)
    {
        RI0 = 0;

        if(uart0_rev.head >= UART0_RX_BUF_SIZE - 1)
        {
            uart0_rev.head = 0;
        }
        else
        {
            uart0_rev.head++;
        }

        uart0_rx_buf[uart0_rev.head] = S0BUF;
    }

    //  if(TI0)
    //  {
    //      TI0=0;
    //      f_uart0_tx=0;
    //
    //      if(uart0_send.head!=uart0_send.tail)
    //      {
    //          if(uart0_send.tail>=UART0_TX_BUF_SIZE-1)
    //          {
    //              uart0_send.tail=0;
    //          }
    //          else
    //          {
    //              uart0_send.tail++;
    //          }
    //          SBUF=uart0_tx_buf[uart0_send.tail];
    //          f_uart0_tx=1;
    //      }
    //  }
}
#endif


//void TIMER2_ISR (void) interrupt 5 //using 1
//{
//  // clear interrupt in 8051
//  TL2 = 0X00;
//  TH2 = 0Xed;
//}
#ifdef USE_UART1
void UART1_ISR (void) interrupt 6 //using 1
{

    if(S1CON & BIT0)
    {
        S1CON = (S1CON & ~BIT1) | BIT0;

        if(uart1_rev.head >= UART1_RX_BUF_SIZE - 1)
        {
            uart1_rev.head = 0;
        }
        else
        {
            uart1_rev.head++;
        }

        uart1_rx_buf[uart1_rev.head] = S1BUF;
    }

    if(S1CON & BIT1)
    {
        //S1CON = (S1CON&~BIT0)|BIT1;
        //      f_uart1_tx=0;
        //
        //      if(uart1_send.head!=uart1_send.tail)
        //      {
        //          if(uart1_send.tail>=UART1_TX_BUF_SIZE-1)
        //          {
        //              uart1_send.tail=0;
        //          }
        //          else
        //          {
        //              uart1_send.tail++;
        //          }
        //          S1BUF=uart1_tx_buf[uart1_send.tail];
        //          f_uart1_tx=1;
        //      }
    }

}
#endif
//ADC
//Comparator
//External interrupt 2
#if 0
void EXINT2_ISR (void) interrupt 7 //using 1
{
    // clear interrupt in 8051

    if(ADCON & BIT5)
        ADCON |= BIT5;

    if(EPIF & BIT0)
        EPIF = BIT0;
}
#endif
//UART2
//External interrupt 3
#ifdef USE_UART2
void EXINT3_ISR (void) interrupt 8 //using 1
{
    // clear interrupt in 8051
    if(S2CON & BIT0)
    {
        S2CON = (S2CON & ~BIT1) | BIT0;

        if(uart2_rev.head >= UART2_RX_BUF_SIZE - 1)
        {
            uart2_rev.head = 0;
        }
        else
        {
            uart2_rev.head++;
        }

        uart2_rx_buf[uart2_rev.head] = S2BUF;
    }

    //  if(S2CON & BIT1)
    //  {
    //      S2CON = (S2CON&~BIT0)|BIT1;
    //      f_uart2_tx=0;
    //
    //      if(uart2_send.head!=uart2_send.tail)
    //      {
    //          if(uart2_send.tail>=UART2_TX_BUF_SIZE-1)
    //          {
    //              uart2_send.tail=0;
    //          }
    //          else
    //          {
    //              uart2_send.tail++;
    //          }
    //          S2BUF=uart2_tx_buf[uart2_send.tail];
    //          f_uart2_tx=1;
    //      }
    //  }
    if(EPIF & BIT1)
        EPIF = BIT1;
}
#endif
//LVD
#ifdef HAVE_LVD_FUNC
//External interrupt 4
void EXINT4_ISR (void) interrupt 9 //using 1
{
    // clear interrupt in 8051
    if(LVDCON & BIT5)
    {
#if defined HAVE_LOW_POWER_DET | defined HAVE_BATTER_DET
        LVDFLAG = 1;
#endif
        LVDCON |= BIT5;
#ifdef HAVE_BATTER_DET
        LVDCON = LVDCON & ~BIT7;
#endif
    }

    if(EPIF & BIT2)
        EPIF = BIT2;

}
#endif
//SPI
//External interrupt 5
#ifdef HAVE_SPI_FUNC
void EXINT5_ISR (void) interrupt 10 //using 1
{
    // clear interrupt in 8051
    if(SPCON & BIT7)
    {
        SPCON |= BIT7;
        //      spi_flag = 1;
    }

    if(EPIF & BIT3)
        EPIF = BIT3;
}
#endif
//I2C
//External interrupt 6
#ifdef HAVE_I2C_HARD_FUNC
void EXINT6_ISR (void) interrupt 11 //using 1
{
    // clear interrupt in 8051
    if(I2CCON & BIT3)
    {
        //      i2c_flag = 1;



        I2CCON |= BIT3;
    }

    if(EPIF & BIT4)
        EPIF = BIT4;
}
#endif
//WDT
//External interrupt 7
#ifdef HAVE_WDT_FUNC
void EXINT7_ISR (void) interrupt 12 //using 1
{
    // clear interrupt in 8051
    if(WDCON & 0x02)
    {
        //      wdt_flag = 1;
        WDCON = 0xA5;
    }

    if(EPIF & BIT5)
    {
        EPIF = BIT5;
#ifdef CA9620
        EXINT_radio_flag = 1;
#endif
    }

}
#endif
//RTC
//External interrupt 8
#ifdef HAVE_RTC_FUNC
void EXINT8_ISR (void) interrupt 13 //using 1
{
#ifdef HAVE_RUN_OSC_32768_AND_DISPLAY
    static unsigned char half_flag = 0;
#endif

    // clear interrupt in 8051
    if(RTCON & BIT0)            //RTC alarm int
    {
        RTCON = (RTCON & ~BIT1) | BIT0;
        //      rtc_flag = 1;
    }

    if(RTCON & BIT1)            //RTC half second int
    {
        RTCON = (RTCON & ~BIT0) | BIT1;
        //      rtc_half_flag = 1;
#ifdef HAVE_RUN_OSC_32768_AND_DISPLAY

        if(HalfSecTimer) HalfSecTimer--;

        if(half_flag)
        {
            RTC_HalfSecFlag = 1;
            half_flag = 0;
        }
        else
        {
            RTC_HalfSecFlag = 2;
            half_flag = 1;
        }

#endif
    }

    if(EPIF & BIT6)
        EPIF = BIT6;
}
#endif
#ifdef HAVE_IR_EXINT
#if  defined CA69F08S3
void EXINT9_ISR (void) interrupt 14 //using 1
{

    INT16U crt_t0, pulse_width, tmp;
    //if(PINT1FG&0x02)
    {
        //PINT1FG = 0xFD;
        TR2 = 0;
        crt_t0 = ((INT16U)TH2) << 8 | (INT16U)TL2;
        TR2 = 1;
        //      S0BUF=crt_t0&0XFF;
        //      while(!TI0);
        //      TI0=0;
        //      S0BUF = crt_t0>>8;
        //      while(!TI0);
        //      TI0=0;

        if(irc_timer)
        {
            pulse_width = crt_t0 - last_t0;

            if(pulse_width < 60) //small than 200us will be think that is spikes
            {
                //IE0=0;
                return;
            }

            tmp = ir_buf_info.head;

            if(tmp < ir_buf_info.tail)
            {
                tmp += IR_BUF_MAX;
            }

            tmp -= ir_buf_info.tail;

            if(tmp >= IR_BUF_MAX - 1)
            {
                if(ir_buf_info.tail == IR_BUF_MAX - 1)
                {
                    ir_buf_info.tail = 0;
                }
                else
                {
                    ir_buf_info.tail++;
                }
            }

            if(ir_buf_info.head == IR_BUF_MAX - 1)
            {
                ir_buf_info.head = 0;
            }
            else
            {
                ir_buf_info.head++;
            }

            ir_pulse_buf[ir_buf_info.head] = pulse_width;

            // S0BUF=pulse_width&0XFF;
            // S0BUF=0X11;
            // while(!TI0);
            // TI0=0;
            // S0BUF = pulse_width>>8;
            // while(!TI0);
            // TI0=0;
        }

        last_t0 = crt_t0;
        irc_timer = 3;
        irc_break_timer = 12;
    }

    if(EPIF & BIT7)
        EPIF = BIT7;
}
#endif
#endif

