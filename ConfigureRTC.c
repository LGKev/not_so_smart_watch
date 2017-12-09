/*
 * ConfigureRTC.c
 *
 *  Created on: Nov 13, 2017
 *      Author: Jordan Wright
 */
#include "msp.h"
#include "ConfigureRTC.h"

extern uint8_t second;
extern uint8_t minute;
extern uint8_t hour;
extern uint8_t day_of_week;
extern uint8_t day;
extern uint8_t month;
extern uint16_t year;

extern  uint8_t  reset_seconds;
extern uint8_t update_time;

void configure_rtc(){
    RTC_C->CTL0 = RTC_C_KEY | RTC_C_CTL0_TEVIE | RTC_C_CTL0_RDYIE; //Real time clock key (for activation)

    //RTC_C->CTL0 = RTC_C_KEY | RTC_C_CTL0_TEVIE | RTC_C_CTL0_RDYIE; //Real time clock key (for activation)
   // RTC_C->CTL0 |= RTC_C_CTL0_RDYIE; //Real time clock read ready interrupt enable
    //RTC_C->CTL0 &= ~(RTCRDYIFG) //associated flag

    //RTC_C->CTL0 |= RTC_C_CTL0_TEVIE; //Real time clock time even interrupt enable
    //RTC_C->CTL0 &= ~(RTCTEVIFG); //associated flag

    RTC_C->CTL13 = RTC_C_CTL13_HOLD | //disable clock while adjusting settings
             RTC_C_CTL13_MODE | //set calendar mode
             RTC_C_CTL13_BCD ; //bcd mode
            // RTC_C_CTL13_TEV_0; //trigger time event every minute

    //(RTC_C_TYPE->CTL13 & RTCRDY) RTC time values safe for reading

    //Set Initial Time Values

    //RTC_C_BCD_Type->TIM0 = seconds(6-4 high digit) (3-0 low digit)
    //RTC_C_BCD_Type->TIM0 = minutes(12-15 high digit) (8-11 low digit)
    RTC_C_BCD->TIM0= 0x3500;   //minutes, seconds

    //RTC_C_BCD_Type->TIM1 =  hours(4-5 high digit) (3-0 low digit)
    //RTC_C_BCD_Type->TIM1 = day of week(8-10)
    RTC_C_BCD->TIM1=0x0704;  //day of week, hour

    //RTC_C_BCD_Type->DATE = days of month(4-5 high digit) (0-3 low digit)
    //RTC_C_BCD_Type->DATE = month(12 high) (8-11 low digit)
    RTC_C_BCD->DATE=0x1209;  //month, day

    //RTC_C_BCD_Type->YEAR = year(0-3 lowest dig)(7-4 decade)(11-8 century)(12-14 century)
    RTC_C_BCD->YEAR=0x2017;  //year


    RTC_C->CTL13 &= ~RTC_C_CTL13_HOLD; //enable clock
    RTC_C->CTL0 &= ~(RTC_C_CTL0_KEY_MASK); //lock the registers


    //RTC_C->AMINHR alarm register
    //RTC_C->ADOWDAY day alarm register
    //RTC_C->IV flags

    NVIC_EnableIRQ(RTC_C_IRQn);

}

/*============================================*/
/*============================================*/
/*            ~~~ IRQ Handler for RTC                                              */
/*============================================*/

void RTC_C_IRQHandler(void)
{
    //occurs every 1 second
    if(RTC_C->CTL0 & RTCRDYIFG)
    {
        //BCD output registers

        //TIM0 is 16 bit seconds and minutes register
        second = RTC_C_BCD->TIM0;

        minute = (RTC_C_BCD->TIM0 >> RTC_C_TIM0_MIN_OFS);
        //TIM1 is 16 bit hour and day of week register
        hour = RTC_C_BCD->TIM1;
        day_of_week = (RTC_C_BCD->TIM1 >> RTC_C_TIM1_DOW_OFS);
        //DATE is 16 bit day and month register
        day = RTC_C_BCD->DATE;
        month = (RTC_C_BCD->DATE >> RTC_C_DATE_MON_OFS);
        //YEAR
        year = RTC_C_BCD->YEAR;

        // Unlock the RTC module and clear time event interrupt flag
        RTC_C->CTL0 = (RTC_C->CTL0 & ~(RTC_C_CTL0_KEY_MASK |  RTCRDYIFG)) | RTC_C_KEY;

        //RTC_C_CTL0_TEVIFG time event flag

        // Re-lock the RTC
        RTC_C->CTL0 = RTC_C->CTL0 & ~(RTC_C_CTL0_KEY_MASK);
    }
//clear any flags
    RTC_C->CTL0 = (RTC_C->CTL0 & ~(RTC_C_CTL0_KEY_MASK |  RTCRDYIFG | RTCOFIFG| RTCTEVIFG)) | RTC_C_KEY;
    RTC_C->CTL0 = RTC_C->CTL0 & ~(RTC_C_CTL0_KEY_MASK);

}
