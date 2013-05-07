/*
* Template dsPIC33F
* Compiler : Microchip xC16
* �C : 33FJ64MC804
* Juillet 2012
*    ____________      _           _
*   |___  /| ___ \    | |         | |
*      / / | |_/ /___ | |__   ___ | |_
*     / /  |    // _ \| '_ \ / _ \| __|
*    / /   | |\ \ (_) | |_) | (_) | |_
*   /_/    |_| \_\___/|____/ \___/'\__|
*                 7robot.fr
*/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include "Mother_Header.h" /* Function / Parameters                           */
#include <timer.h>         /* Include timer fonctions                         */
#include <uart.h>
#include "ax12.h"
#include <libpic30.h>
#include "atp-mother.h"

#define AX_BOUGIES_1 13
#define AX_BOUGIES_2 10
#define AX_BOUGIES_3 4

#define AX_PINCE_GAUCHE 8
#define AX_PINCE_DROITE 11

#define AX_GUIDE_GAUCHE_1 16
#define AX_GUIDE_GAUCHE_2 17
#define AX_GUIDE_DROIT_1 6
#define AX_GUIDE_DROIT_2 7

#define BOUGIE_ON (1<<1)
#define BOUGIE_OFF (1<<2)
#define BOUGIE_TOP (1<<3)
#define BOUGIE_BOT (1<<4)


volatile char actionAx =0;


/*************************************************
 *                 Bougies                       *
 *************************************************/



void PosInitBougies(int Bot){
    if(Bot==1){
        PutAX(AX_BOUGIES_3, AX_GOAL_POSITION, 0x0358);
        __delay_ms(100);
        PutAX(AX_BOUGIES_2, AX_GOAL_POSITION, 0x029C);
        __delay_ms(300);
    }
    PutAX(AX_BOUGIES_1, AX_GOAL_POSITION, 0x0207);
    __delay_ms(10);
    PutAX(AX_BOUGIES_2, AX_GOAL_POSITION, 0x029C);
    __delay_ms(10);
    PutAX(AX_BOUGIES_3, AX_GOAL_POSITION, 0x0180);
    __delay_ms(10);

}

//Taper sur les bougies du haut
void OnBougiesHitTop(){
   actionAx |= BOUGIE_TOP;
   IFS2bits.SPI2IF = 1;
}
void DoHitTopBougie(){
        PutAX(AX_BOUGIES_1, AX_GOAL_POSITION, 0x0207);
        __delay_ms(10);
        PutAX(AX_BOUGIES_2, AX_GOAL_POSITION, 0x0234);
        __delay_ms(10);
        PutAX(AX_BOUGIES_3, AX_GOAL_POSITION, 0x0158);
        __delay_ms(500);
        PosInitBougies(0);
        SendBougiesHitTopConfirm();
}

//Taper sur les bougies du bas

void OnBougiesHitBot(){
    actionAx |=  BOUGIE_BOT;
    IFS2bits.SPI2IF = 1;
}
void DoHitBotBougie(){
    PutAX(AX_BOUGIES_1, AX_GOAL_POSITION, 0x0207);
    __delay_ms(10);
    PutAX(AX_BOUGIES_3, AX_GOAL_POSITION, 0x034E);
    __delay_ms(200);
    PutAX(AX_BOUGIES_2, AX_GOAL_POSITION, 0x00B9);
    __delay_ms(800);
    PutAX(AX_BOUGIES_3, AX_GOAL_POSITION, 0x02D9);
    __delay_ms(800);
    PosInitBougies(1);
    SendBougiesHitBotConfirm();
}

//Position pli�e bras AX Bougies
void OnBougiesOff(){ //DONE
    actionAx |= BOUGIE_OFF;
    IFS2bits.SPI2IF = 1;
}
void DoOffBougie(){

        PutAX(AX_BOUGIES_1, AX_GOAL_POSITION, 0x0141);
        __delay_ms(50);
        PutAX(AX_BOUGIES_2, AX_GOAL_POSITION, 0x00D2);
        __delay_ms(10);
        PutAX(AX_BOUGIES_3, AX_GOAL_POSITION, 0x00AD);
        __delay_ms(800);
        PutAX(AX_BOUGIES_1, AX_GOAL_POSITION, 0x0086);
        __delay_ms(100);
        SendBougiesOffConfirm();
}

//Position d�pli�e bras AX Bougies
void OnBougiesOn(){
    actionAx |= BOUGIE_ON;
    IFS2bits.SPI2IF = 1;
}

void DoOnBougie(){

        PutAX(AX_BOUGIES_1, AX_GOAL_POSITION, 0x0141);
        __delay_ms(300);
        PutAX(AX_BOUGIES_2, AX_GOAL_POSITION, 0x029C);
        __delay_ms(10);
        PutAX(AX_BOUGIES_3, AX_GOAL_POSITION, 0x0180);
        __delay_ms(500);
        PutAX(AX_BOUGIES_1, AX_GOAL_POSITION, 0x0207);
        __delay_ms(100);
        SendBougiesOnConfirm();
}


void __attribute__((interrupt, no_auto_psv)) _SPI2Interrupt(void){
    led=1;
    IFS2bits.SPI2IF = 0;
    if((actionAx & BOUGIE_ON) == BOUGIE_ON){
        DoOnBougie();
        actionAx &= ~BOUGIE_ON;
    }else if((actionAx & BOUGIE_OFF) == BOUGIE_OFF){
        DoOffBougie();
        actionAx &= ~BOUGIE_OFF;
    }else if((actionAx & BOUGIE_BOT) == BOUGIE_BOT){
        DoHitBotBougie();
        actionAx &= ~BOUGIE_BOT;
    }else if((actionAx & BOUGIE_TOP) == BOUGIE_TOP){
        DoHitTopBougie();
        actionAx &= ~BOUGIE_TOP;
    }
    led=0;
}
