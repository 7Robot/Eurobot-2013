/*
* Beacon dsPIC33F
* Compiler : Microchip xC16
* �C : 33FJ64MC802
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
/* System Level #define Macros                                                */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        7370000L //80000000
#define FCY             SYS_FREQ/2
#define baud            (FCY/9600)/16-1
#define adversaire1     0x69
#define adversaire2     0x55

#define led1            _LATA0
#define led2            _LATA1

#define UnlockRP        __builtin_write_OSCCONL(OSCCON & 0xBF)
#define LockRP          __builtin_write_OSCCONL(OSCCON | 0x40)
/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */

