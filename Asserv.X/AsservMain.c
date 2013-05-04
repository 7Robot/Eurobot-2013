/*
* Asserv dsPIC33F
* Compiler : Microchip xC16
* µC : 33FJ64MC802
* Avril 2013
*    ____________      _           _
*   |___  /| ___ \    | |         | |
*      / / | |_/ /___ | |__   ___ | |_
*     / /  |    // _ \| '_ \ / _ \| __|
*    / /   | |\ \ (_) | |_) | (_) | |_
*   /_/    |_| \_\___/|____/ \___/'\__|
*                 7robot.fr
*/

#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include "AsservHeader.h"  /* Function / Parameters                           */
#include <libpic30.h>
#include <uart.h>
#include "atp-asserv.h"
#include "atp.h"


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
_FOSC(POSCMD_NONE & OSCIOFNC_ON & IOL1WAY_ON & FCKSM_CSDCMD);
// Watchdog Timer.
_FWDT(FWDTEN_OFF);
// Select debug channel.
_FICD(ICS_PGD1 & JTAGEN_OFF);


/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int16_t main(void)
{
    // Initialize IO ports and peripherals.
    ConfigureOscillator();
    InitApp();

    AtpInit();
    SendId(5);

    Set_Asserv_V(500,10,0.1);
    Set_Asserv_T(100,10,0.1);
    //float angle = 0;

    while(1)
    {
        //Set_Vitesse_MoteurG(800);

        led1 = led1 ^ 1;
        Set_Consigne_Vitesse(2);
        __delay_ms(3000);
        //Set_Consigne_Vitesse(0.2);
        //__delay_ms(10000);
       // */
         /*Set_Vitesse_MoteurD(800);

        __delay_ms(1500);
        Set_Vitesse_MoteurD(250);
        Set_Vitesse_MoteurG(250);
        __delay_ms(1500);

        __delay_ms(50);*/

    }
}

