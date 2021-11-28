#include "lcd.h"

void whisper()
{
	LCD_CTRL_PORT |=(1<<EN);
	asm volatile ("nop");
	asm volatile ("nop");
	LCD_CTRL_PORT &=~(1<<EN);
}

void checkReadiness()
{
	//data direction as input
	LCD_DATA_DDR = 0x00;
	//Reading from the lcd
	LCD_CTRL_PORT |= (1 << RW);
	//Enabling the command mode
	LCD_CTRL_PORT &= ~(1 << RS);

	while (LCD_DATA_PORT >= 0x80)
	{
		whisper();
	}
	//bringing the dataPort back as output
	LCD_DATA_DDR=0xFF;
}

void LCD_send_command(unsigned char command)
{
	checkReadiness();
	LCD_DATA_PORT = command;
	LCD_CTRL_PORT &=~(1<<RS);	//command mode
	LCD_CTRL_PORT &=~(1<<RW);	//write mode
	whisper();
	LCD_DATA_PORT = 0;
	_delay_ms(5);
}

void LCD_init()
{
	//Turning the control pins into outputs
	LCD_CTRL_DDR |= (1<<RS)|(1<<RW)|(1<<EN);
	// configure data port as output initially
	LCD_DATA_DDR |= 0xFF;
	_delay_ms(15);
	//Clear Display
	LCD_send_command(0x01);
	_delay_ms(2);
	//8-bit mode 2 lines display
	LCD_send_command(0x3C);
	_delay_us(50);
	//display and cursor on,blinking off
	LCD_send_command(0x0C);
	_delay_us(50);
}

void LCD_send_character(unsigned char character)
{
	checkReadiness();
	LCD_DATA_PORT = character;
	LCD_CTRL_PORT |=(1<<RS);		//sending character
	LCD_CTRL_PORT &=~(1<<RW);		//write mode
	whisper();
	LCD_DATA_PORT = 0;
}

void LCD_send_string(char * data)
{
	while (*data>0)
	{
		LCD_send_character(*data);
		_delay_ms(5);
		data++;
	}
	
}

void LCD_goTo(uint8_t Row, uint8_t Col)
{
	uint8_t location=0;
	//return home
	LCD_send_command(0x02);
	_delay_ms(2);
	//Go to some destination
	if (Row==2)
	{
		location=0x40;
	}
	location+=Col;
	LCD_send_command(0x80+location-0x01);
	_delay_us(50);
}

void LCD_clear()
{
	LCD_send_command(0x01);
}