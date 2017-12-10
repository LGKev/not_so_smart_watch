/*
* LCD.h
*
*  Created on: Nov 4, 2017
*      Author: Jean-Christophe
*/

#include "stdint.h"

#ifndef LCD_H_
#define LCD_H_

void LCD(void);
void display_center(int8_t title [20], uint16_t x, uint16_t y);


//not functional: what is value for the ti library.
void display_horizontal_Line(uint8_t x_start, uint8_t x_end, uint8_t y, uint32_t value);


//need a way to change fonts on the fly.
//possibly enum or a lookup table/case statement
//void set_font(Graphics_Font  font);



#endif /* LCD_H_ */
