/*
 * time_count.c
 *
 * Created: 2022-08-12 오후 5:09:09
 *  Author: kccistc
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

void init_timer0();
extern void init_fnd();

int timer_count_music=0;
int timer_state_music=0;
int timer_count_1sec=0;
int timer_count_3sec=0;
int timer_state_3sec=0;
int timer_count_manual=0;
int timer_state_manual=0;

extern int manual_time;
extern int auto_time;
extern int manual_time_set1;
extern int manual_time_set2;
extern int manual_time_set3;
extern int manual_time_set4;
extern int time_sync1;
extern int time_sync2;
extern int music_sync;


ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6;
	
	if (music_sync)
	{
		timer_count_music++;
		
		if (timer_count_music > 500)
		{
			timer_count_music=0;
			timer_state_music++;
			if (timer_state_music > 2)
			{
				timer_state_music=0;
				music_sync = !music_sync;
			}
		}
	}
	
	if (time_sync1)
	{
		timer_count_3sec++;
		timer_count_1sec++;
		
		if (timer_count_3sec > 3000)
		{
			timer_count_3sec=0;
			timer_state_3sec++;
		}
		
		if (timer_count_1sec > 1000)
		{
			timer_count_1sec=0;
			auto_time--;
			if (auto_time < 0)
			{
				auto_time=0;
				init_fnd();
			}
		}	
	}
	
	if (time_sync2)
	{
		timer_count_manual++;
		timer_count_1sec++;
		
		if (timer_count_manual > manual_time)
		{
			timer_count_manual=0;
			timer_state_manual++;
		}
		
		if (timer_count_1sec > 1000)
		{
			timer_count_1sec=0;
			manual_time_set1--;
			manual_time_set2--;
			manual_time_set3--;
			manual_time_set4--;
			
			if (manual_time_set1 < 0)
			{
				manual_time_set1=0;
				init_fnd();
			}
			if (manual_time_set2 < 0)
			{
				manual_time_set2=0;
				init_fnd();
			}
			if (manual_time_set3 < 0)
			{
				manual_time_set3=0;
				init_fnd();
			}
			if (manual_time_set4 < 0)
			{
				manual_time_set4=0;
				init_fnd();
			}
		}
	}
}

void init_timer0()
{
	// 분주비 64로 설정
	TCCR0 |= (1 << CS02) | (0 << CS01) | (0 << CS00);
	
	//	인터럽트 활성화 비트 TIMSK (Timer/Counter Interrupt Mask Register)
	//	그림 13-5 참고
	//	오버플로 인터럽트 활성화(허용) 비트 TOIE0 (Timer/Counter0 Overflow Interrupt Enable)
	//	TIMER0_OVF_vect -->	TOIE0
	TIMSK |= (1 << TOIE0);		// 오버플로 인터럽트 허용
}