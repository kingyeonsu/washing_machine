/*
 * n298n_dcmotor_pwm_control.c
 *
 * Created: 2022-08-12 오후 2:53:15
 *  Author: kccistc
 */ 
#include "n298n_dcmotor_pwm_control.h"

extern int timer_count_3sec;
extern int timer_state_3sec;
extern int auto_mode_state;
extern int timer_count_manual;
extern int timer_state_manual;
extern int manual_mode_state;
extern int mode_slect;
extern int time_sync_beat;


void pwm_init();
void dc_motor_pwm_control_auto();
void dc_motor_pwm_control_manual();

extern void wash_beat();
extern void wash_led();
extern void rinse_led();
extern void dehydration_led();
extern void I2C_LCD_write_string_XY(uint8_t row, uint8_t col, char *string);

void pwm_init()
{
	// PE.0 PE.2 PE5 출력 모드로 설정
	DC_MOTOR_PWM_DDR |= (1 << DC_MOTOR_CONTROL_IN1) | (1 << DC_MOTOR_CONTROL_IN2) | (1 << DC_MOTOR_PWM_CONTROL);
	
	// 모드5 : 8비트고속PWM모드 timer 3
	TCCR3A |= (1 << WGM30);
	TCCR3B |= (1 << WGM32);
	
	// 비반전 모드 TOP: 0xff 비교일치값 : OCR3C : PE5
	TCCR3A |= (1 << COM3C1);
	// 분주비 64  16000000/64  ==> 250000HZ(250KHZ)
	// 256 / 250000 ==> 1.02ms
	// 127 / 250000 ==> 0.5ms
	TCCR3B |= ( 1 << CS31)  | (1 << CS30);   // 분주비 64
	// 1600000HZ / 64분주 ==> 250000HZ (250KHZ)
	//
	TIMSK |= (1 << TOIE0);
	OCR3C=0;  // PORTE.5
}

// ENA : PORTE.5 (OCR3B(PE5) <=== PORTE.4
// IN1 : PORTE.0
// IN2 : PORTE.2
void dc_motor_pwm_control_auto()
{
	switch (timer_state_3sec)
	{
		case 1:
		wash_led();
		// 정회전 : PE2:0 PE0 1
		PORTE &= 0b11111011;
		PORTE |= 0b00000001;
		OCR3C=127;		// 중간속도
		break;
		case 2:
		wash_led();
		OCR3C=200;		// wash max speed
		break;
		case 3:
		wash_led();
		OCR3C=0;
		PORTE |= 0b00000101;  // 모터정지 : PE0:1 PE2:1
		break;
		case 4:
		wash_led();
		// 역회전 : PE2:1 PE0 0
		PORTE &= 0b11111110;
		PORTE |= 0b00000100;
		break;
		case 5:
		wash_led();
		OCR3C=127;    // 중간속도
		break;
		case 6:
		wash_led();
		OCR3C=200;		// wash max speed
		break;
		case 7:
		rinse_led();
		OCR3C=0;
		PORTE |= 0b00000101;  // 모터정지 : PE0:1 PE2:1
		break;
		case 8:
		rinse_led();
		// 정회전 : PE2:0 PE0 1
		PORTE &= 0b11111011;
		PORTE |= 0b00000001;
		OCR3C=200;		// rinse middle speed
		break;
		case 9:
		rinse_led();
		OCR3C=255;		// max speed
		break;
		case 10:
		rinse_led();
		OCR3C=0;
		PORTE |= 0b00000101;  // 모터정지 : PE0:1 PE2:1
		break;
		case 11:
		rinse_led();
		// 역회전 : PE2:1 PE0 0
		PORTE &= 0b11111110;
		PORTE |= 0b00000100;
		break;
		case 12:
		rinse_led();
		OCR3C=200;		// rinse middle speed
		break;
		case 13:
		rinse_led();
		OCR3C=255;      // max speed
		break;
		case 14:
		dehydration_led();
		OCR3C=0;
		PORTE |= 0b00000101;  // 모터정지 : PE0:1 PE2:1
		break;
		case 15:
		dehydration_led();
		// 정회전 : PE2:0 PE0 1
		PORTE &= 0b11111011;
		PORTE |= 0b00000001;
		OCR3C=255;		// max speed
		break;
		case 16:
		dehydration_led();
		OCR3C=255;		// max speed
		break;
		case 17:
		dehydration_led();
		OCR3C=0;
		PORTE |= 0b00000101;  // 모터정지 : PE0:1 PE2:1
		break;
		case 18:
		dehydration_led();
		// 역회전 : PE2:1 PE0 0
		PORTE &= 0b11111110;
		PORTE |= 0b00000100;
		break;
		case 19:
		dehydration_led();
		OCR3C=255;		// max speed
		break;
		case 20:
		dehydration_led();
		OCR3C=255;      // max speed
		break;
	}
	if (timer_state_3sec >= 21)
	{
		timer_count_3sec=0;
		timer_state_3sec=0;
		auto_mode_state=0;
		
		OCR3C=0;
		PORTE |= 0b00000101;  // 모터정지 : PE0:1 PE2:1
	}
	
}

void dc_motor_pwm_control_manual()
{
	switch (timer_state_manual)
	{
		case 1:
		wash_led();
		// 정회전 : PE2:0 PE0 1
		PORTE &= 0b11111011;
		PORTE |= 0b00000001;
		OCR3C=127;		// 중간속도
		break;
		case 2:
		wash_led();
		OCR3C=200;		// wash max speed
		break;
		case 3:
		wash_led();
		OCR3C=0;
		PORTE |= 0b00000101;  // 모터정지 : PE0:1 PE2:1
		break;
		case 4:
		wash_led();
		// 역회전 : PE2:1 PE0 0
		PORTE &= 0b11111110;
		PORTE |= 0b00000100;
		break;
		case 5:
		wash_led();
		OCR3C=127;    // 중간속도
		break;
		case 6:
		wash_led();
		OCR3C=200;		// wash max speed
		break;
		case 7:
		rinse_led();
		OCR3C=0;
		PORTE |= 0b00000101;  // 모터정지 : PE0:1 PE2:1
		break;
		case 8:
		rinse_led();
		// 정회전 : PE2:0 PE0 1
		PORTE &= 0b11111011;
		PORTE |= 0b00000001;
		OCR3C=200;		// rinse middle speed
		break;
		case 9:
		rinse_led();
		OCR3C=255;		// max speed
		break;
		case 10:
		rinse_led();
		OCR3C=0;
		PORTE |= 0b00000101;  // 모터정지 : PE0:1 PE2:1
		break;
		case 11:
		rinse_led();
		// 역회전 : PE2:1 PE0 0
		PORTE &= 0b11111110;
		PORTE |= 0b00000100;
		break;
		case 12:
		rinse_led();
		OCR3C=200;		// rinse middle speed
		break;
		case 13:
		rinse_led();
		OCR3C=255;      // max speed
		break;
		case 14:
		dehydration_led();
		OCR3C=0;
		PORTE |= 0b00000101;  // 모터정지 : PE0:1 PE2:1
		break;
		case 15:
		dehydration_led();
		// 정회전 : PE2:0 PE0 1
		PORTE &= 0b11111011;
		PORTE |= 0b00000001;
		OCR3C=255;		// max speed
		break;
		case 16:
		dehydration_led();
		OCR3C=255;		// max speed
		break;
		case 17:
		dehydration_led();
		OCR3C=0;
		PORTE |= 0b00000101;  // 모터정지 : PE0:1 PE2:1
		break;
		case 18:
		dehydration_led();
		// 역회전 : PE2:1 PE0 0
		PORTE &= 0b11111110;
		PORTE |= 0b00000100;
		break;
		case 19:
		dehydration_led();
		OCR3C=255;		// max speed
		break;
		case 20:
		dehydration_led();
		OCR3C=255;      // max speed
		break;
	}
	if (timer_state_manual >= 21)
	{
		timer_count_manual=0;
		timer_state_manual=0;
		manual_mode_state=0;
		
		OCR3C=0;
		PORTE |= 0b00000101;  // 모터정지 : PE0:1 PE2:1
	}
	
}

