/*
 * watch_face_themes.c
 *
 *  Created on: Dec 9, 2017
 *      Author: kwat1
 */

#include "msp.h"
#include "watch_face_themes.h"
#include "Lcd.h"
#include "grlib.h"

/**string globals/
 *
 */
extern char seconds_string[20];
extern char minutes_string[20];
extern char hours_string[20];
extern char years_string[20];
extern char days_of_week_string[20];
extern char days_string_number[20];
extern char months_string[20];

//adc strings
extern char X_adc_string[20];
extern char Y_adc_string[20];
extern char Z_adc_string[20];

/* RTC globals defined in main.*/
extern uint8_t second;
extern uint8_t minute;
extern uint8_t hour;
extern uint8_t day_of_week;
extern uint8_t day;
extern uint8_t month;
extern uint16_t year;

extern  uint8_t  reset_seconds;
extern uint8_t update_time;

extern uint8_t AM;    //AM is 0, and PM is 1

extern  Graphics_Context g_sContext;

extern uint8_t change_watch_face ; // 1 is true, 0 is false;
extern uint8_t    which_face ; //0 being defualt, and 1,2,...n, is the number of faces. defined in watch_face_themes


void basic_watch(){
    if(change_watch_face == 1){
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_AQUAMARINE);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_LIME_GREEN);
    Graphics_clearDisplay(&g_sContext);


    change_watch_face = 0;
    }

//empty for now, but will move from main.
    sprintf(hours_string, "%02X:", hour );
         display_center(hours_string, 25, 60);

         sprintf(minutes_string, "%02X:", minute );
         display_center(minutes_string, 48, 60);

         sprintf(seconds_string, "%02X", second );
         display_center(seconds_string, 69, 60);



    //  set_font(g_sFontCm18i);
           sprintf(months_string, "%02X", month );
           display_center(months_string, 20, 30);

           sprintf(days_string_number, "/%02X/", day);
           display_center(days_string_number, 50, 30);

           sprintf(years_string, "%02X", year );
           display_center(years_string, 90, 30);

           if(AM == 0){
               display_center("AM", 100, 60);
           }
           else{
               display_center("PM", 100, 60);
           }


           switch(day_of_week){
           case 0: display_center("Sunday", 64, 100);
                   break;
           case 1: display_center("Monday", 64, 100);
                    break;
           default: display_center("Saturday", 64, 100);
           }//end of day of week case


           /*
            *  To be honest I could probably make a function to
            *  measure the length of the string
            *  then do a for loop to loop over to adjust the sizing.
            *  i'll save that for Saturday. wooo yay today's only sautrday thank goodnsess.
            *
            * */
}

void large_TIME(){
    LCD();
}
