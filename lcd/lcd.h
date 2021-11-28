#ifndef __LCD_H__
#define __LCD_H__

#include <avr/delay.h>

#define LCD_DATA_DDR		DDRB
#define LCD_DATA_PORT		PORTB
#define LCD_CTRL_DDR		DDRD
#define LCD_CTRL_PORT		PORTD
#define RS					PD5
#define RW					PD6
#define EN					PD7

void whisper();
void checkReadiness();
void LCD_send_command(unsigned char command);
void LCD_init();
void LCD_send_character(unsigned char character);
void LCD_send_string(char * data);
void LCD_goTo(uint8_t Row, uint8_t Col);
void LCD_clear();

#endif