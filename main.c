/*
 * main.c
 * */
#include "msp.h"
#include "stdlib.h"
#include <stdio.h>
#include "ConfigureRTC.h"
#include "grlib.h"


/* User Defined Headers */

#include "Lcd.h"

#define SCB_SCR_ENABLE_SLEEPONEXIT (0x00000002)

char seconds_string[20];
char minutes_string[20];
char hours_string[20];
char years_string[20];
char days_of_week_string[20];
char days_string_number[20];
char months_string[20];
char test_string[20];

/*============================================*/
/*============================================*/
/*=========       RTC Config Globals               ==========*/
/*============================================*/
volatile uint32_t second;
volatile uint8_t minute;
volatile uint8_t hour;
volatile uint8_t day_of_week;
volatile uint8_t day;
volatile uint8_t month;
volatile uint16_t year;

volatile uint8_t AM;    //AM is 0, and PM is 1

//Global for control.
volatile uint8_t    reset_seconds = 0; //not true, 1 is true
volatile uint8_t      update_time = 1; // 1 is true, 0 is false;

volatile  uint32_t bla = 0;
/*                                  */
/*============================================*/
void main(void) {
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer
    uint32_t kk = 0;
    //visual output for minutes
    P1DIR = BIT0;
    P1SEL0 = 0;
    P1SEL1 = 0;
    P1OUT |= BIT0;
    for(kk=0; kk<2000; kk++);
    P1OUT^=BIT0;

    LCD();

    __enable_irq();

   // display_center(" version 1.1",64,20);
   // display_horizontal_Line(40, 60, 89, 33);
    /*============================================*/
    /*======         RTC         *jordan Wright  ==========*/
    /*============================================*/
    // Select lower power clock for low power mode
      CS->CTL1 &= ~(CS_CTL1_SELA_MASK) | CS_CTL1_SELA_0;
      CS->KEY = 0;         // Lock the module
      configure_rtc();
      //DO I NEED TO REENABLE BANK EACH TIME I GO TO LPM???
      //This enables all SRAM banks during low power mode
      SYSCTL->SRAM_BANKEN |= SYSCTL_SRAM_BANKRET_BNK7_RET; //enables all banks
 /*============================================*/
/* ==========         end of configurations             =========*/
/*=============================================*/

      __enable_interrupt();
     // set_font(g_sFontCm18i);
      //this settting font doesn't work. i need to find out the correct way.
      //I need a helper funciton to acces the protectedd.

      display_center("K^2", 64, 85);



    while(1) {
        bla++;

        if(bla%3000 == 0){

      sprintf(hours_string, "%02X:", hour );
      display_center(hours_string, 25, 60);

      sprintf(minutes_string, "%02X:", minute );
      display_center(minutes_string, 48, 60);

      sprintf(seconds_string, "%02X", second );
      display_center(seconds_string, 69, 60);


        }

        //date , month, day, year, day of week.
        //near the top of display.
        if(bla%10000==0){
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
    }
}


