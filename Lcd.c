#include "msp.h"
#include <driverlib.h>
#include <grlib.h>
#include "Crystalfontz128x128_ST7735.h"
#include <stdio.h>



/* Graphic library context */
Graphics_Context g_sContext;


void LCD(void)
{
    MAP_Interrupt_disableMaster();

   /* Initializes display */
   Crystalfontz128x128_Init();

   /* Set default screen orientation */
   Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

   /* Initializes graphics context */
   Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128);
   Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_AQUAMARINE);
   Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_RED);
   //GrContextFontSet(&g_sContext, &g_sFontFixed6x8);
   GrContextFontSet(&g_sContext, &g_sFontCm18i);
   Graphics_clearDisplay(&g_sContext);
}

void display_center(int8_t title [20], uint16_t x, uint16_t y){
   Graphics_drawStringCentered(&g_sContext, title, AUTO_STRING_LENGTH, x, y, OPAQUE_TEXT);
}

void display_horizontal_Line(uint8_t x_start, uint8_t x_end, uint8_t y, uint32_t value){
    Graphics_drawHorizontalLineOnDisplay(&g_sContext, x_start, x_end, y, value);
}

void set_font(Graphics_Font  font){
    GrContextFontSet(&g_sContext, &font);
}

//void set_background_color();
