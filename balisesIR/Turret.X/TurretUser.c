/*
* Turret dsPIC33F
* Compiler : Microchip xC16
* dsPIC33FJ64MC802
* Avril 2013
*    ____________      _           _
*   |___  /| ___ \    | |         | |
*      / / | |_/ /___ | |__   ___ | |_
*     / /  |    // _ \| '_ \ / _ \| __|
*    / /   | |\ \ (_) | |_) | (_) | |_
*   /_/    |_| \_\___/|____/ \___/'\__|
*			      7robot.fr
*/
/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__dsPIC33E__)
	#include <p33Exxxx.h>
#elif defined(__dsPIC33F__)
	#include <p33Fxxxx.h>
#endif

#include <stdint.h>          /* For uint32_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */
#include "TurretUser.h"      /* variables/params used by user.c               */

// Select Oscillator and switching.
_FOSCSEL(FNOSC_FRCPLL & IESO_OFF);
// Select clock.
_FOSC(POSCMD_NONE & OSCIOFNC_ON & IOL1WAY_ON & FCKSM_CSDCMD);
// Watchdog Timer.
_FWDT(FWDTEN_OFF);
// Select debug channel.
_FICD(ICS_PGD1 & JTAGEN_OFF);

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureOscillator(void) /* Handles clock switching/osc initialization */
{
    PLLFBDbits.PLLDIV = 41; // M=43
    CLKDIVbits.PLLPOST = 0; // N1=2
    CLKDIVbits.PLLPRE  = 0; // N2=2
}

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    //On a un interrupteur sur la pin RC2, on la met en entrée
    _TRISC2 = 1;
    //Et on active la pullup qui va bien (registres CNPU1 et CNPU2)
    _CN10PUE = 1; // not sure

    _TRISA0 = 0; //led 1
    _TRISA1 = 0; //led 2
    led1 = 0; 
    led2 = 0;
    _TRISC9 = 1;  // TSOP1
    _TRISB5 = 1;  // TSOP2
    _TRISB6 = 1;  // TSOP3
    _TRISB7 = 1;  // TSOP4
    _TRISB8 = 1;  // TSOP5
    _TRISB9 = 1;  // TSOP6
    _TRISB10 = 1;  // TSOP7
    _TRISB11 = 1;  // TSOP8
    _TRISC7 = 1;  // TSOP9
    _TRISC8 = 1;  // TSOP10
    _TRISA7 = 1;  // TSOP11
    _TRISA8 = 1;  // TSOP12
    _TRISC3 = 1;  // TSOP13
    _TRISC4 = 1;  // TSOP14
    _TRISC5 = 1;  // TSOP15
    _TRISC6 = 1; // TSOP16
}
