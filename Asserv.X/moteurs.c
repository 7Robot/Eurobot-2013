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

#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include "AsservHeader.h"  /* Function / Parameters                           */
#include <libpic30.h>
#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <math.h>




void Init_PWM(void)
{
        PTCONbits.PTEN   = 0;   // Timer Enable bit:		    DISABLE MCPWM
	PWMCON1bits.PEN1H = 1;  // PWM1H (pin 37) is enabled for PWM output
	PWMCON1bits.PEN2H = 1;  // PWM2H (pin 35) is enabled for PWM output
	PTCONbits.PTCKPS = 1;   // Input Clock Prescale bits:   1:4
	PTCONbits.PTOPS  = 0;   // Output Clock Postscale bits: 1:1
	PTCONbits.PTSIDL = 1;	// Stop in Idle Mode:           YES
	PTCONbits.PTMOD  = 0;   // Mode Select bits:			Free Running Mode
	PTCONbits.PTEN   = 1;   // Timer Enable bit:		 	ENABLE MCPWM

	/**** PTPER: PWM Time Base Period Register ****/
	PTPERbits.PTPER = 500; // Period Value bits


/*
    // voir section 14 PWM DSPIC33F de microchip
    P1TCON = 0x8000;        // demarre le PWM1
    P1TPER = 0x01F4;        // defini la periode de PWM à 1000 coup d'horloge
    P1SECMP = 0;            // "desactive" le SPECIAL EVENT ...

    //A REVOIR : FAIT FONCTIONNER AUSSI LES PINS L
    PWM1CON1 = 0x033;       // defini que les 2 pin H en sortie
    PWM1CON2 = 0x0000;      // defini les moments d'update des registres
    P1DTCON1 = 0;           // disable les dead-time
    P1DTCON2 = 0;           // idem
    P1FLTACON = 0;          // disable le faultA
    //P1FLTBCON = 0;            // disable le faultB  (inulite)

    // A REVOIR AUSSI : TOUCHE AUX PINS 3...
    P1OVDCON = 0x3F00;      //  Override
    */
    P1DC1 = 0;
    P1DC2 = 0;          // rapport cycliques nuls pour les moteurs

    _TRISC3 = 0;    //DIRA1 sur RC3 en sortie
    _TRISC4 = 0;    //DIRB1 sur RC4 en sortie
    _TRISA3 = 0;    //DIRA2 sur RA3 en sortie
    _TRISA4 = 0;    //DIRB2 sur RA4 en sortie

}

void Set_Vitesse_MoteurD(float Consigne)
{
    if (Consigne < 0.0)
    {//MISE DES PATES SENS INVERSE
        Consigne = -Consigne;
        DIRA1 = 0;
        DIRB1 = 1;
    }
    else
    { // MISE DES PATES EN SENS NORMAL
        DIRA1 = 1;
        DIRB1 = 0;
    }

    if (Consigne < CONSIGNE_NULLE) Consigne = 0;
    if (Consigne < CONSIGNE_MIN && Consigne > CONSIGNE_NULLE)          Consigne = CONSIGNE_MIN;
    if (Consigne > CONSIGNE_MAX)      Consigne = CONSIGNE_MAX;
    P1DC1 = (int)(Consigne);
}

void Set_Vitesse_MoteurG(float Consigne)
{
    if (Consigne < 0.0)
    {//MISE DES PATES SENS INVERSE
        Consigne = -Consigne;
        DIRA2 = 0;
        DIRB2 = 1;
    }
    else
    { // MISE DES PATES EN SENS NORMAL
        DIRA2 = 1;
        DIRB2 = 0;
    }

    if (Consigne < CONSIGNE_NULLE) Consigne = 0;
    if (Consigne < CONSIGNE_MIN && Consigne > CONSIGNE_NULLE)          Consigne = CONSIGNE_MIN;
    if (Consigne > CONSIGNE_MAX)      Consigne = CONSIGNE_MAX;
    P1DC2 = (int)(Consigne);

}
