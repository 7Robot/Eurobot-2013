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

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include "AsservHeader.h"  /* Function / Parameters                           */
#include "lut.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/



float sin_lut (float angle)   // prends un nombre en radians, en renvoie son sinus
{

    int Indice_Lut = ((int)(angle * Points_par_radian)% TAILLE_LUT);

    return Lut_sinus[Indice_Lut];
}


float cos_lut (float angle)   // prends un nombre en radians, en renvoie son cosinus
{

    int Indice_Lut = ((int)(angle * Points_par_radian) + DEPHASAGE) % TAILLE_LUT;

    return Lut_sinus[Indice_Lut];
}
