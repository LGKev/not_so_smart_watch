/*
 * main.c
 * */
#include "msp.h"
#include "stdlib.h"
#include <stdio.h>
#include "ConfigureRTC.h"
#include "grlib.h"
#include "adc_driver.h"
#include "watch_face_themes.h"
#include "HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
#include  "Crystalfontz128x128_ST7735.h"
#include "watch_defines.h"


/* User Defined Headers */

#include "Lcd.h"

#define SCB_SCR_ENABLE_SLEEPONEXIT (0x00000002)



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

/*============================================*/
/*============================================*/
/*=========       LCD     Globals                         ==========*/
/*============================================*/


volatile char seconds_string[20];
volatile char minutes_string[20];
volatile char hours_string[20];
volatile char years_string[20];
volatile char days_of_week_string[20];
volatile char days_string_number[20];
volatile char months_string[20];

//adc strings
volatile char X_adc_string[20];
volatile char Y_adc_string[20];
volatile char Z_adc_string[20];


char test_string[20];

volatile uint8_t change_watch_face = 1; // 1 is true, 0 is false;
volatile uint8_t    which_face = 0; //0 being defualt, and 1,2,...n, is the number of faces. defined in watch_face_themes


/*============================================*/
/*============================================*/
/*=========       ACCL     Globals                         ==========*/
/*============================================*/
//:Accelerometer globals, used in the adc_driver.c file
volatile uint16_t X_ADC = 0;
volatile uint16_t Y_ADC = 0;
volatile uint16_t Z_ADC = 0;
/*============================================*/


#ifdef temperature_OK
/*============================================*/
/*============================================*/
/*====     Temperature Sensor     Globals                         ==========*/
/*============================================*/
//:Accelerometer globals, used in the adc_driver.c file
volatile float Temperature_C;
volatile float Temperature_F ;
volatile float Temperature_K;

volatile char temperature_C_string[20];
volatile char temperature_F_string[20];
volatile char temperature_K_string[20];


/*============================================*/
#endif

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
/* ==========         end of RTC  configurations             =========*/
/*=============================================*/


      /*============================================*/
      /*======         ADC acclerometer *Kuwata ==========*/
      /*============================================*/

ADC_CONFIG_Accelerometer();

      /*=============================================*/

LCD();

      __enable_interrupt();

//turn display off
//      HAL_LCD_writeCommand(CM_DISPOFF);
//turn backlight off

      Temperature_C = 53.53;
      Temperature_F =44.44;
       Temperature_K = 56.78;

    while(1) {


        //start an ADC conversion
        ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC; //start sample, enable conversion?



        bla++;
        //basic_watch();
      //  large_TIME();
       basic_Temperature();


}
}


