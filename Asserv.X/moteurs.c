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

    P1DC1 = 0;
    P1DC2 = 0;          // rapport cycliques nuls pour les moteurs

    _TRISB0 = 0;//Pin de programmation
    _TRISB1 = 0;//Pin de programmation
    _TRISB2 = 0;
    _TRISB3 = 0;

}

void Set_Vitesse_MoteurD(float Consigne)
{
    if (Consigne < 0.0)
    {
        Consigne = -Consigne;
        _LATB0 = 1;
        _LATB1 = 0;
        //MISE DES PATES SENS INVERSE
    }
    else
    {
        _LATB0 = 0;
        _LATB1 = 1;
        // MISE DES PATES EN SENS NORMAL
    }

    if (Consigne > 1000.0)        Consigne = 1000.0;
    P1DC1 = (int)(Consigne);
}

void Set_Vitesse_MoteurG(float Consigne)
{
    if (Consigne < 0.0)
    {
        Consigne = -Consigne;
        _LATB2 = 1;
        _LATB3 = 0;

        //MISE DES PATES SENS INVERSE
    }
    else
    {
        _LATB2 = 0;
        _LATB3 = 1;
        // MISE DES PATES EN SENS NORMAL
    }

    if (Consigne > 1000.0)        Consigne = 1000.0;
    P1DC2 = (int)(Consigne);

}
