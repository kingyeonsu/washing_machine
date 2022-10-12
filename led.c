/*
 * led.c
 *
 * Created: 2022-08-12 오후 6:56:42
 *  Author: kccistc
 */ 
#include "led.h"

void init_led();
void reset_led();
void power_led();
void wash_led();
void rinse_led();
void dehydration_led();

void init_led()
{
	MODE_LED_DDR = 0x0f;
	MODE_LED_PORT = 0x00;
}

void reset_led()
{
	MODE_LED_PORT = 0x00;
}

void power_led()
{
	MODE_LED_PORT = 0x01;
}

void wash_led()
{
	MODE_LED_PORT = 0x03;
}

void rinse_led()
{

	MODE_LED_PORT = 0x05;
}

void dehydration_led()
{
	MODE_LED_PORT = 0x09;
}
