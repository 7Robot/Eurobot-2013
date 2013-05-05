/*
* Pince merged dsPIC33F
* Compiler : Microchip xC16
* uC : 33FJ64MC804
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
#include "PinceHeader.h"  /* Function / Parameters                           */
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
    Init_PWM();
    int vitesse = 0;
    responseReadyAX = 0;

    __delay_ms(10);
    PutAX(AX_BROADCAST, AX_MOVING_SPEED, 250);
    __delay_ms(10);
    PutAX(AX_BROADCAST, AX_MAX_TORQUE, 1100);
    __delay_ms(10);

    //Set_Consigne_Hauteur(0);
    Set_Asserv_h(0.5, 0.25);
    Set_Vitesse(1000);

    //reset_pince();

    //Sortir_Pince();
    //__delay_ms(10000);
    //Chopper_verre();
    Cinematique_inverse();
    while(1)
    {
        led = !led;
        //Set_Consigne_Hauteur(-1000);
        __delay_ms(1000);
//        Set_Consigne_Hauteur(0);
//        __delay_ms(2000);
    }

}

