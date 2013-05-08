/*
* Asserv dsPIC33F
* Compiler : Microchip xC16
* µC : 33FJ64MC804
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


/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

volatile unsigned int delay = 100; // ms
volatile bool broadcast = true;


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
    float x, y, theta;
    // Initialize IO ports and peripherals.
    ConfigureOscillator();
    InitApp();

    AtpInit();
    SendId(5);

    Set_Epsilons(0.02,100,0.01,50);

    Set_Asserv_D(600,50,1);
    Set_Asserv_T(3000,100,1);
    Set_Asserv_V(2000,50,2);
    Set_Asserv_O(600,50,0.1);

    Stop();

    while(1) {

//        Set_Consigne_Distance(-1);
//        Set_Consigne_Angle(PI/2);
//        Set_Consigne_Position(-0.4,0.5);
        while(1);

        if (broadcast) {
            Get_Position(&x, &y, &theta);
            SendPos(x, y, theta);
        }
        __delay_ms(delay);
    }
}

void OnOdoBroadcastSetDelay(unsigned int new_delay) {
    if (new_delay > 0) {
        delay = new_delay;
    } else {
        SendError();
    }
}

void OnOdoBroadcastOn() { broadcast = true; }
void OnOdoBroadcastOff() { broadcast = false; }
