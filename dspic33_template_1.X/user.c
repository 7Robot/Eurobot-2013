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

#include "user.h"            /* variables/params used by user.c               */

#include <timer.h>           /* Librairie pour les timer                      */

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */

    _TRISA0 = 0;
    led = 0;

    /* Setup analog functionality and port direction */

    /* Initialize peripherals */


//    // activation de la priorité des interruptions
//    _NSTDIS = 0;
//    // on choisit (complètement arbitairement) la priorité 3 pour l'interruption T1.
//    // Comme on n?a qu?une interruption, tout nombre >0 aurait aussi bien marché.
//    _T1IP = 3;
//    // Activation de l'interruption T1
//    _T1IE = 1;

    OpenTimer1(T1_ON & T1_GATE_OFF & T1_PS_1_256 & T1_SYNC_EXT_OFF & T1_SOURCE_INT, 0xFFF);
    EnableIntT1;

}
