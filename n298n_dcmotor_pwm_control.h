/*
 * n298n_dcmotor_pwm_control.h
 *
 * Created: 2022-08-12 오후 6:22:55
 *  Author: kccistc
 */ 


#ifndef N298N_DCMOTOR_PWM_CONTROL_H_
#define N298N_DCMOTOR_PWM_CONTROL_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

#define DC_MOTOR_PWM_DDR DDRE
#define DC_MOTOR_PWM_PORT PORTE

#define DC_MOTOR_CONTROL_IN1 0	//	PORTE.0
#define DC_MOTOR_CONTROL_IN2 2	//	PORTE.2
#define	DC_MOTOR_PWM_CONTROL 5	//	PORTE.5





#endif /* N298N_DCMOTOR_PWM_CONTROL_H_ */