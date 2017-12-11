/*
 * kk_gpio.c
 *
 *  Created on: Dec 10, 2017
 *      Author: Kevin Kuwata
 */
#include "msp.h"
#include "kk_gpio.h"

extern uint8_t change_watch_face ; // 1 is true, 0 is false;
extern uint8_t    which_face ; //0 being defualt, and 1,2,...n, is the number of faces. defined in watch_face_themes

void Left_Right_Button_Config(){
    /* Right button configure */
        P1->SEL0 &= ~BIT1;
        P1->SEL1 &= ~BIT1;
        P1->DIR &= ~BIT1; //amazing that this even works. its a fluke. it is set as output right now.
        P1->REN |= BIT1;
        P1->OUT |= BIT1;
        P1->IFG &= ~BIT1; //interrupt flag to be cleared first
        P1->IES |= BIT1; //high to low
        P1->IE |= BIT1;

        /* LEFT button configure */
        P1->SEL0 &= ~BIT4;
        P1->SEL1 &= ~BIT4;
        P1->DIR &= ~BIT4;
        P1->REN |= BIT4;
        P1->OUT |= BIT4;
        P1->IFG &= ~BIT4; //interrupt flag to be cleared first
        P1->IES |= BIT4; //high to low
        P1->IE |= BIT4;


        /* Enable Interrupts in the NVIC */
        NVIC_EnableIRQ(PORT1_IRQn);
}

void config_redLED(){
        P1SEL0 &=~BIT0;
        P1SEL1 &=~BIT0;
        P1DIR |= BIT0;
        P1OUT |= BIT0;
}

/*===================================*/
/*===================================*/
/*         ISR for the button interrupt                 */
/*===================================*/

void  PORT1_IRQHandler(){
    uint8_t delay;
    for(delay =0; delay<200; delay++);

    if(P1IFG & BIT1){
        //left button
        which_face--;
        change_watch_face = 1;

        P1->IFG &= ~BIT1;
        P1OUT^=BIT0;
        if(which_face <=0){
            which_face = 0;
        }
    }

    if(P1IFG & BIT4){
           //right button
        P1OUT^=BIT0;
        which_face++;
           P1->IFG &= ~BIT4;
           change_watch_face = 1;

           if(which_face >2){
               which_face = 0;
           }
       }

}


