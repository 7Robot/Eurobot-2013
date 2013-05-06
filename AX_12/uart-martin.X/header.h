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



#include <p33Fxxxx.h>
#include "osc.h"
#include <stdint.h>        // Includes uint16_t definition
#include <stdbool.h>       // Includes true/false definition

/******************************************************************************/
/* #define Macros                                                             */
/******************************************************************************/

#define led _LATA0

volatile int received = 0;
/******************************************************************************/
/*                                                                            */
/******************************************************************************/


void InitApp(void);       // I/O and Peripheral Initialization
