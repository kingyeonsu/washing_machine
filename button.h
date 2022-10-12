/*
 * button.h
 *
 * Created: 2022-08-12 오후 2:50:39
 *  Author: kccistc
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_DDR DDRD
#define BUTTON_PIN PIND	// PORTD read register

// button1~4에 대한 값만 바꾸면 코딩이 훨씬 간단해진다. 같은 포트의 다른 핀의 값은 유지하기 위한 포석
#define BUTTON0	3	// PORTD.3
#define BUTTON1 4	// PORTD.4
#define BUTTON2 5	// PORTD.5
#define BUTTON3 6	// PORTD.6
#define BUTTON4 7	// PORTD.7


#endif /* BUTTON_H_ */