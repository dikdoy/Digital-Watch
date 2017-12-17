/*
 * lcd.h
 *
 *  Created on: 16 Des 2017
 *      Author: Dikdo
 */

#ifndef LCD_H_
#define LCD_H_

// prototipe fungsi
void enable(void);                 // enable pulse for LCD
void lcd_init(void);               // intialization LCD
void lcd_putchar(unsigned char c); // send character to LCD
void lcd_putstr(char *s);          // send string to LCD
void lcd_clear(void);              // clear display
void lcd_gotoxy(unsigned char i,unsigned char j);  //move LCD cursor position

#endif /* LCD_H_ */
