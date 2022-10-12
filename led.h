/*
 * led.h
 *
 * Created: 2022-08-14 오후 3:42:08
 *  Author: kccistc
 */ 


#ifndef LED_H_
#define LED_H_

#define F_CPU 16000000UL
#include <avr/io.h>

// 상황에 맞게, 목적에 맞게 프로그래밍하기 편하기 위해
// COMPILER 명령어를 할당

#define MODE_LED_DDR DDRF
#define MODE_LED_PORT PORTF



#endif /* LED_H_ */