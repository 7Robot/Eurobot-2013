/*
* Template dsPIC33F
* Compiler : Microchip xC16
* µC : 33FJ64MC802
* Juillet 2012
*    ____________      _           _
*   |___  /| ___ \    | |         | |
*      / / | |_/ /___ | |__   ___ | |_
*     / /  |    // _ \| '_ \ / _ \| __|
*    / /   | |\ \ (_) | |_) | (_) | |_
*   /_/    |_| \_\___/|____/ \___/'\__|
*			      7robot.fr
*/

#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include "header.h"        /* Function / Parameters                           */
#include <libpic30.h>
#include <uart.h>
#include "ax12.h"




/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */


/******************************************************************************/
/* Configuartion                                                              */
/******************************************************************************/

// Select Oscillator and switching.
_FOSCSEL(FNOSC_FRCPLL & IESO_OFF);
// Select clock.
_FOSC(POSCMD_NONE & OSCIOFNC_ON & IOL1WAY_OFF & FCKSM_CSDCMD);
// Watchdog Timer.
_FWDT(FWDTEN_OFF);
// Select debug channel.
_FICD(ICS_PGD1 & JTAGEN_OFF);



/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/






int16_t main(void)
{
    //int Pos_AX_BRAS[3];

    // Initialize IO ports and peripherals.
    ConfigureOscillator();
    InitApp();
    AtpInit();
    responseReadyAX = 0;

    ODCBbits.ODCB7 = 1;

    __delay_ms(500);
    //PutAX(AX_BROADCAST, AX_MOVING_SPEED, 0x0000);
    //PutAX(AX_BROADCAST, AX_BAUD_RATE, 0x0022);
    //Les AX12 sont à 57600 BAUD
    //OnOnBougies();
    //__delay_ms(500);
  
    while(1) {
/*
        PutAX(4, AX_GOAL_POSITION, 710);
        __delay_ms(200);
        PutAX(13, AX_GOAL_POSITION, 200);
        __delay_ms(10);
        PutAX(10, AX_GOAL_POSITION, 560);

        __delay_ms(600);
        PutAX(4, AX_GOAL_POSITION, 860);
        __delay_ms(100);
        PutAX(13, AX_GOAL_POSITION, 200);
        __delay_ms(10);
        PutAX(10, AX_GOAL_POSITION, 560);

         __delay_ms(300);
        PutAX(4, AX_GOAL_POSITION, 860);
        __delay_ms(10);
        PutAX(13, AX_GOAL_POSITION, 200);
        __delay_ms(10);
        PutAX(10, AX_GOAL_POSITION, 200);

         __delay_ms(230);
        PutAX(4, AX_GOAL_POSITION, 710);
        __delay_ms(10);
        PutAX(13, AX_GOAL_POSITION, 200);
        __delay_ms(10);
        PutAX(10, AX_GOAL_POSITION, 200);

        __delay_ms(200);
        PutAX(4, AX_GOAL_POSITION, 860);
        __delay_ms(10);
        PutAX(13, AX_GOAL_POSITION, 200);
        __delay_ms(160);
        PutAX(10, AX_GOAL_POSITION, 512);

*/


      //led = led ^ 1;
      //GetAX(13,AX_PRESENT_POSITION);
      //Pos_AX_BRAS[0]=responseAX.params[0]*(2^8)+responseAX.params[1];
      //__delay_ms(20);
      //GetAX(10,AX_PRESENT_POSITION);
      //Pos_AX_BRAS[2]=responseAX.params[0]*(2^8)+responseAX.params[1];
      //__delay_ms(5000);
      //GetAX(4,AX_PRESENT_POSITION);
      //Pos_AX_BRAS[3]=responseAX.params[0]*(2^8)+responseAX.params[1];
      //__delay_ms(5000);


       //PosInitBougies();
/*
       OnOnBougies();
       __delay_ms(5000);
       OnHitTopBougies();
       __delay_ms(5000);
       OnHitBotBougies();
       __delay_ms(5000);
       OnOffBougies();
       __delay_ms(5000);
*/

    }
}
