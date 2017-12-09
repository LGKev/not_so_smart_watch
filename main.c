/*
 * main.c
 * */
#include "msp.h"
#include "stdlib.h"
#include <stdio.h>
#include "ConfigureRTC.h"

/* User Defined Headers */

#include "Lcd.h"

#define SCB_SCR_ENABLE_SLEEPONEXIT (0x00000002)

char seconds_string[20];
char minutes_string[20];
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

//Global for control.
volatile uint8_t    reset_seconds =0; //not true, 1 is true
volatile uint8_t      update_time = 1; // 1 is true, 0 is false;

volatile  uint32_t bla=0;
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

    display_center(" version 1.1",64,35);

    sprintf(test_string, "Vel: %2.3f \n", 53.49);
     display_center(test_string, 64, 60);

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

      sprintf(test_string, "Vel: %2.3f \n", 69.423);
       display_center(test_string, 64, 60);
      __enable_interrupt();

    while(1) {

    }
}


