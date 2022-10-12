/*
 * WASHING_MACHINE.c
 *
 * Created: 2022-08-12 오후 2:40:52
 * Author : kccistc
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>

extern void init_speaker(void);
extern void init_timer0();
extern int get_button0();
extern int get_button1();
extern int get_button2();
extern int get_button3();
extern int get_button4();
extern int get_manual_start_stop_button();
extern void pwm_init();
extern void dc_motor_pwm_control_auto();
extern void dc_motor_pwm_control_manual();

extern void I2C_LCD_init(void);
extern void I2C_LCD_write_string_XY(uint8_t row, uint8_t col, char *string);
extern void init_led();
extern void reset_led();
extern void power_led();
extern void init_fnd();
extern void display_fnd(void);
extern void set_fnd_data(uint16_t data);
extern void Music_Player(int *tone, int *Beats);

int power_state=0;
int auto_mode_state=0;
int manual_mode_state=0;
int manual_time_check=0;
int manual_time=0;
int mode_slect=0;

int music_sync=0;
int time_sync1=0;
int time_sync2=0;
int auto_time = 63;
int manual_time_setting=0;
int manual_time_set0=3;
int manual_time_set1=23;
int manual_time_set2=43;
int manual_time_set3=63;
int manual_time_set4=83;

extern int timer_state_music;
extern const int Elise_Tune_start[];
extern const int Elise_Beats_start[];

int main(void)
{	
	char s_buff[30];
	
	init_speaker();
	init_fnd();
	I2C_LCD_init();
	init_led();
	init_timer0();
	pwm_init();
	
	sei();
	
	while (1)
	{
		if (get_button0())
		{
			power_state = !power_state;
			music_sync = !music_sync;
		}
		if (!power_state)
		{
			init_fnd();
			reset_led();
			I2C_LCD_write_string_XY(0, 0, "Power: Off      ");
			I2C_LCD_write_string_XY(1, 0 , "                     ");
			OCR3C=0;
			PORTE |= 0b00000101;  // 모터정지 : PE0:1 PE2:1
		}
		if (power_state)
		{
			I2C_LCD_write_string_XY(0, 0, "Power: On       ");
			power_led();
			if (music_sync)
			{
				if (timer_state_music)
				{
					Music_Player(Elise_Tune_start, Elise_Beats_start);
				}
			}
			
			
			
			if (get_button1())
			{
				mode_slect++;
				
				if (mode_slect > 2)
				{
					auto_mode_state=0;
					manual_mode_state=0;
					mode_slect=0;
					time_sync1 = 0;
				}
			}
			if (mode_slect == 0)
			{
				auto_time = 63;
				manual_time_set1=23;
				manual_time_set2=43;
				manual_time_set3=63;
				manual_time_set4=83;
				OCR3C=0;
				PORTE |= 0b00000101;  // 모터정지 : PE0:1 PE2:1
				I2C_LCD_write_string_XY(1, 0 , "Mode select        ");
			}
			if (mode_slect == 1)
			{
				manual_mode_state=0;
				set_fnd_data(auto_time);
				sprintf(s_buff, "Auto time: %2ds" , auto_time);
				I2C_LCD_write_string_XY(1, 0 , s_buff);
				if (get_button4())
				{
					auto_mode_state = !auto_mode_state;
				}
				if (auto_mode_state)
				{
					time_sync1 = 1;
					display_fnd();
					dc_motor_pwm_control_auto();
				}
			}
			if (mode_slect == 2) 
			{
				auto_mode_state=0;
				if (get_button2())
				{
					manual_time += 1000;
					manual_time_check++;
				}
				if (get_button3())
				{
					manual_time -= 1000;
					manual_time_check--;
				}
				manual_time_setting = manual_time_check * 20 + 3;
				switch (manual_time_setting)
				{
					case 3:
					sprintf(s_buff, "Manual time:%3ds" , manual_time_set0);
					set_fnd_data(manual_time_set0);
					break;
					case 23:
					sprintf(s_buff, "Manual time:%3ds" , manual_time_set1);
					set_fnd_data(manual_time_set1);
					break;
					case 43:
					sprintf(s_buff, "Manual time:%3ds" , manual_time_set2);
					set_fnd_data(manual_time_set2);
					break;
					case 63:
					sprintf(s_buff, "Manual time:%3ds" , manual_time_set3);
					set_fnd_data(manual_time_set3);
					break;
					case 83:
					sprintf(s_buff, "Manual time:%3ds" , manual_time_set4);
					set_fnd_data(manual_time_set4);
					break;
				}
				I2C_LCD_write_string_XY(1, 0, s_buff);
				if (get_button4())
				{
					manual_mode_state = !manual_mode_state;
				}
				if (manual_mode_state)
				{
					time_sync2 = 1;
					display_fnd();
					dc_motor_pwm_control_manual();
				}
			}
		}	
	}
}