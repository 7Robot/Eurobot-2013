/*
* Template dsPIC33F
* Compiler : Microchip xC16
* �C : 33FJ64MC802
* Juillet 2012
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

#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <timer.h>
#include <qei.h>           /* Includes qei functions */
#include <uart.h>
#include "PinceHeader.h"  /* Function / Parameters                           */
#include <libpic30.h>
#include "ax12.h"

/*
 * 
 */
volatile int ready = 0;
volatile int full  = 0;
volatile int nbverres = 0;
unsigned char num_ax;
unsigned char data;

void Sortir_Pince()
{
    Ouvrir_pince_bas(); //on ouvre la pince
    Ouvrir_stockage();
    reset_pince(); //on reset le zero de la glissiere
    __delay_ms(2000);

    ready = 1;
}

void Chopper_verre()
{
    int verreok;
    if(ready && !full)
    {
        if (nbverres >= 3)
        {
            verreok = Serrer_verre();
            Serrer_stockage();
            if (verreok)
            {
                Set_Consigne_Hauteur(1000); //mi hauteur
                __delay_ms(2000);

                full = 1;
            }
            else
            {
                Ouvrir_pince_bas();
            }
        }
        else
        {
            verreok = Serrer_verre();
            Serrer_stockage();
            if (verreok)
            {
                Set_Consigne_Hauteur(1000); //mi hauteur
                __delay_ms(2000);
                Semi_ouvrir_stockage();
                Set_Consigne_Hauteur(2000); //full hauteur
                __delay_ms(2000);
                Serrer_stockage();

                Ouvrir_pince_bas();
                reset_pince();
                __delay_ms(2000);

                nbverres++;
            }
            else
            {
                Ouvrir_pince_bas();
            }
        }
    }
}

void Lacher_verres()
{
    if(ready)
    {
        if (full)
        {
            Semi_ouvrir_stockage();
            reset_pince();
            __delay_ms(2000);
        }
        else
        {
            Ouvrir_pince_bas();
            Set_Consigne_Hauteur(2000);
            __delay_ms(2000);
            Serrer_verre();
            Semi_ouvrir_stockage();
            reset_pince();
        }
        Ouvrir_pince_bas();
        Ouvrir_stockage();
    }
}


void Ouvrir_pince_bas()
{
//Ouvrir pince en position basse :
        PutAX(AX_BG, AX_GOAL_POSITION, 710);
        __delay_ms(10);
        PutAX(AX_BD, AX_GOAL_POSITION, 310);
        __delay_ms(400);
}

int Serrer_verre()
{
//Serrer un verre en position basse :
	PutAX(AX_BG, AX_GOAL_POSITION, 845);
        __delay_ms(10);
        PutAX(AX_BD, AX_GOAL_POSITION, 170);
        __delay_ms(400);
        PutAX(AX_BG, AX_GOAL_POSITION, 800);
        __delay_ms(10);
        PutAX(AX_BD, AX_GOAL_POSITION, 220);
        __delay_ms(200);
        PutAX(AX_BG, AX_GOAL_POSITION, 845);
        __delay_ms(10);
        PutAX(AX_BD, AX_GOAL_POSITION, 170);
        __delay_ms(10);
        int valeur;
        num_ax = AX_BD;
        data = AX_PRESENT_POSITION;
        valeur = GetAXnoWait();

    int verreok = 0;
    if (valeur < 160) verreok = 1;
    return verreok;
}

int GetAXnoWait()
{
    int valeur=0;
    GetAX(num_ax, data);
    while(!responseReadyAX)
        {
        T5CONbits.TON = 1;
        }
    valeur = (responseAX.params[1]*256 + responseAX.params[0]);
    
    return valeur;
}

void Serrer_stockage()
{
//Serrer la pince stockage
        PutAX(AX_HD1, AX_GOAL_POSITION, 273);
        __delay_ms(10);
        PutAX(AX_HD2, AX_GOAL_POSITION, 622);
        __delay_ms(10);
        PutAX(AX_HG1, AX_GOAL_POSITION, 738);
        __delay_ms(10);
        PutAX(AX_HG2, AX_GOAL_POSITION, 371);
        __delay_ms(10);
}

void Semi_ouvrir_stockage()
{
//Semi_ouvrir pince stockage
        PutAX(AX_HD1, AX_GOAL_POSITION, 307);
        __delay_ms(10);
        PutAX(AX_HD2, AX_GOAL_POSITION, 657);
        __delay_ms(10);
        PutAX(AX_HG1, AX_GOAL_POSITION, 728);
        __delay_ms(10);
        PutAX(AX_HG2, AX_GOAL_POSITION, 368);
        __delay_ms(10);
}

void Ouvrir_stockage()
{
     PutAX(AX_HD1, AX_GOAL_POSITION, 337);
     __delay_ms(10);
     PutAX(AX_HD2, AX_GOAL_POSITION, 677);
     __delay_ms(10);
     PutAX(AX_HG1, AX_GOAL_POSITION, 718);
     __delay_ms(10);
     PutAX(AX_HG2, AX_GOAL_POSITION, 364);
     __delay_ms(10);

}

void Rangement_stockage()
{
//Rangement pince stockage
		PutAX(AX_HD1, AX_GOAL_POSITION, 585);
        __delay_ms(10);
        PutAX(AX_HD2, AX_GOAL_POSITION, 170);
        __delay_ms(10);
        PutAX(AX_HG1, AX_GOAL_POSITION, 450);
        __delay_ms(10);
        PutAX(AX_HG2, AX_GOAL_POSITION, 850);
        __delay_ms(10);
}

void Rangement_pince()
/* /!\ Ne pas utiliser n'importe comment sous peine de tout casser !! */
{
//Rangement pince bas à refaire après modif des pinces
        PutAX(AX_BD, AX_GOAL_POSITION, 621);
        __delay_ms(10);
        PutAX(AX_BG, AX_GOAL_POSITION, 393);
        __delay_ms(10);
}

//fonction cinematique inverse pour debug et tests
int valeur[6];
void Cinematique_inverse()
{
    GetAX(AX_BD, AX_PRESENT_POSITION);
    while(!responseReadyAX);
    valeur[0] = (responseAX.params[1]*256 + responseAX.params[0]);
    __delay_ms(10);

    GetAX(AX_BG, AX_PRESENT_POSITION);
    while(!responseReadyAX);
    valeur[1] = (responseAX.params[1]*256 + responseAX.params[0]);
    __delay_ms(10);

    GetAX(AX_HD1, AX_PRESENT_POSITION);
    while(!responseReadyAX);
    valeur[2] = (responseAX.params[1]*256 + responseAX.params[0]);
    __delay_ms(10);

    GetAX(AX_HD2, AX_PRESENT_POSITION);
    while(!responseReadyAX);
    valeur[3] = (responseAX.params[1]*256 + responseAX.params[0]);
    __delay_ms(10);

    GetAX(AX_HG1, AX_PRESENT_POSITION);
    while(!responseReadyAX);
    valeur[4] = (responseAX.params[1]*256 + responseAX.params[0]);
    __delay_ms(10);

    GetAX(AX_HG2, AX_PRESENT_POSITION);
    while(!responseReadyAX);
    valeur[5] = (responseAX.params[1]*256 + responseAX.params[0]);
    __delay_ms(10);
}
