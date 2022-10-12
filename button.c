/*
 * button.c
 *
 * Created: 2022-08-12 오후 2:50:03
 *  Author: kccistc
 */ 

#include "button.h"

int get_button0();
int get_button1();
int get_button2();
int get_button3();
int get_button4();

void init_button()
{
	BUTTON_DDR &= ~((1 << BUTTON0) | (1 << BUTTON1) | (1 << BUTTON2) | (1 << BUTTON3) | (1 << BUTTON4)); // input --> 0 setting
}

int get_button0()
{
	static uint8_t prev_state=0; // 버튼의 상태 0: off 1: on
	uint8_t current_state;	// unsigend char 와 같다. (8비트) <open source type>
	
	current_state = BUTTON_PIN & (1 << BUTTON0); // button0 값을 읽는다. on --> 0x10
	
	if (prev_state == 0 && current_state != 0)
	{
		_delay_ms(60);	// ** NOISE가 지나가길 기다린다.
		prev_state = 1; // 처음 눌러진 상태가 아니다.
		
		return 0;	// 아직 진짜가 아니다. --> 다시 버튼이 눌린 효과 --> 초기값 1로 설정
	}
	else if (prev_state == 1 && current_state == 0) // 버튼이 눌렸다prev_state == 1 떠이진 상태 current_state == 0
	{
		prev_state = 0;
		_delay_ms(30);	// 노이즈가 지나가기를 기다린다.
		return 1;	// 완전히 눌렸다 떼어진 상태로 인정
	}
	
	return 0; // 어작 S/W를 완전히 눌렀다 때지 않은 상태
}

int get_button1()
{
	static uint8_t prev_state=0; // 버튼의 상태 0: off 1: on
	uint8_t current_state;	// unsigend char 와 같다. (8비트) <open source type>
	
	current_state = BUTTON_PIN & (1 << BUTTON1); // button1 값을 읽는다. on --> 0x10
	
	if (prev_state == 0 && current_state != 0)
	{
		_delay_ms(60);	// ** NOISE가 지나가길 기다린다.
		prev_state = 1; // 처음 눌러진 상태가 아니다.
		
		return 0;	// 아직 진짜가 아니다. --> 다시 버튼이 눌린 효과 --> 초기값 1로 설정
	}
	else if (prev_state == 1 && current_state == 0) // 버튼이 눌렸다prev_state == 1 떠이진 상태 current_state == 0
	{
		prev_state = 0;
		_delay_ms(30);	// 노이즈가 지나가기를 기다린다.
		return 1;	// 완전히 눌렸다 떼어진 상태로 인정
	}
	
	return 0; // 어작 S/W를 완전히 눌렀다 때지 않은 상태
}

int get_button2()
{
	static uint8_t prev_state=0;  // 버튼의 상태 0: off 1: on
	uint8_t current_state;  // unsigned char current_state
	
	current_state = BUTTON_PIN & (1 << BUTTON2);  // button2 값을 읽는다. 0x10
	if (prev_state == 0 && current_state !=0)  // 버튼이 처음 눌려진 상태
	{
		_delay_ms(60);   // 노이즈가 지나가기를 기다린다.
		prev_state=1;    // 처음 눌려진 상태 가 아니다.
		return 0;        // 아직은 진짜로 눌려진 상태가 아니다.
	}
	else if (prev_state == 1 && current_state == 0) // 버튼이 눌렸다prev_state == 1 떠이진 상태 current_state == 0
	{
		prev_state=0;
		_delay_ms(30);  // 노이즈가 지나가기를 기다린다.
		return 1;    // 완전히 눌렸다 떼어진 상태로 인정
	}
	return 0;  // 아직 완전히 S/W를 눌렀다  떼지않은 상태
}

int get_button3()
{
	static uint8_t prev_state=0;  // 버튼의 상태 0: off 1: on
	uint8_t current_state;  // unsigned char current_state
	
	current_state = BUTTON_PIN & (1 << BUTTON3);  // button3 값을 읽는다. 0x10
	if (prev_state == 0 && current_state !=0)  // 버튼이 처음 눌려진 상태
	{
		_delay_ms(60);   // 노이즈가 지나가기를 기다린다.
		prev_state=1;    // 처음 눌려진 상태 가 아니다.
		return 0;        // 아직은 진짜로 눌려진 상태가 아니다.
	}
	else if (prev_state == 1 && current_state == 0) // 버튼이 눌렸다prev_state == 1 떠이진 상태 current_state == 0
	{
		prev_state=0;
		_delay_ms(30);  // 노이즈가 지나가기를 기다린다.
		return 1;    // 완전히 눌렸다 떼어진 상태로 인정
	}
	return 0;  // 아직 완전히 S/W를 눌렀다  떼지않은 상태
}

int get_button4()
{
	static uint8_t prev_state=0;  // 버튼의 상태 0: off 1: on
	uint8_t current_state;  // unsigned char current_state
	
	current_state = BUTTON_PIN & (1 << BUTTON4);  // button4 값을 읽는다. 0x10
	if (prev_state == 0 && current_state !=0)  // 버튼이 처음 눌려진 상태
	{
		_delay_ms(60);   // 노이즈가 지나가기를 기다린다.
		prev_state=1;    // 처음 눌려진 상태 가 아니다.
		return 0;        // 아직은 진짜로 눌려진 상태가 아니다.
	}
	else if (prev_state == 1 && current_state == 0) // 버튼이 눌렸다prev_state == 1 떠이진 상태 current_state == 0
	{
		prev_state=0;
		_delay_ms(30);  // 노이즈가 지나가기를 기다린다.
		return 1;    // 완전히 눌렸다 떼어진 상태로 인정
	}
	return 0;  // 아직 완전히 S/W를 눌렀다  떼지않은 상태
}