#ifndef __CA69F_TIM1_H_
#define __CA69F_TIM1_H_

#define TIM1_CR1_RESET_VALUE   0x00
#define CONST_TIM1_ARC         0x0E //auto Repetition Counter  0.8ms

void Timer1_DeInit(void);
void Timer1_Init(void);


#endif

