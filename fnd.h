/*
 * fnd.h
 *
 * Created: 2022-08-15 오후 4:12:34
 *  Author: kccistc
 */ 


#ifndef FND_H_
#define FND_H_

#define F_CPU 16000000UL
#include <avr/io.h>

#define FND_DATA_DDR   DDRC
#define FND_DATA_PORT  PORTC

#define FND_DIGHT_DDR  DDRA
#define FND_DIGHT_PORT PORTA
#define FND_DIGHT_D1   0
#define FND_DIGHT_D2   2
#define FND_DIGHT_D3   3
#define FND_DIGHT_D4   4


void set_fnd_data(uint16_t data);
uint16_t get_fnd_data(void);
void display_fnd(void);
void init_fnd();



#endif /* FND_H_ */