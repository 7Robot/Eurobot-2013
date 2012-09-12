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


/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */


/******************************************************************************/
/* Configuartion                                                              */
/******************************************************************************/

    // Select Internal FRC at POR
    _FOSCSEL(FNOSC_FRC);
    // Enable Clock Switching and Configure POSC in XT mode
    _FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_HS);
    /* Turns off JTAG and selects debug channel */
    _FICD(JTAGEN_OFF & ICS_PGD1);
    // Watchdog Timer disabled
    _FWDT(FWDTEN_OFF);


/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int16_t main(void)
{

    /* Configure the oscillator for the device */
    SwitchOscillator();
    /* Initialize IO ports and peripherals */
    InitApp();

    while(1)
    {
//        __delay32(5000000);
//        led = led^1;
    }
}

