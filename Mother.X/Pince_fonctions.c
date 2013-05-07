/*
* Template dsPIC33F
* Compiler : Microchip xC16
* �C : 33FJ64MC804
* Juillet 2012
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
#include <timer.h>
#include <qei.h>           /* Includes qei functions */
#include <uart.h>
#include "Mother_Header.h"  /* Function / Parameters                           */
#include <libpic30.h>
#include "ax12.h"
#include "atp-mother.h"

volatile int ready = 0;
volatile int full  = 0;
volatile unsigned int nbverres = 0;
volatile char actionPince = 0;
volatile unsigned char num_ax;
volatile unsigned char data;

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
            verreok = Serrer_verre_en_bas();
            Serrer_stockage();
            if (verreok)
            {
                Set_Consigne_Hauteur(500); //mi hauteur
                __delay_ms(400);
                Set_Consigne_Hauteur(50);
                __delay_ms(200);

                full = 1;
                nbverres++;
            }
            else
            {
                Ouvrir_pince_bas();
            }
        }
        else
        {
            verreok = Serrer_verre_en_bas();
            Serrer_stockage();
            if (verreok)
            {
                Set_Consigne_Hauteur(500); //mi hauteur
                __delay_ms(350);
                Semi_ouvrir_stockage();
                Set_Consigne_Hauteur(3700); //full hauteur
                __delay_ms(2200);
                Serrer_stockage();
                __delay_ms(200);
                Ouvrir_pince_bas();
                reset_pince();
                __delay_ms(2000);

                nbverres++;
            }
            else
            {
                SendPasDeVerreEvent()
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
            Set_Consigne_Hauteur(3700); //full hauteur
            __delay_ms(2200);
            Serrer_verre_en_haut();
            Semi_ouvrir_stockage();
            reset_pince();
            __delay_ms(2500);
        }
        Ouvrir_pince_bas();
        Serrer_stockage();
        __delay_ms(400);
        Ouvrir_stockage();
        __delay_ms(10);
        //Ouvrir FULL open :
        PutAX(AX_HD1, AX_GOAL_POSITION, 360);
        __delay_ms(10);
        PutAX(AX_HD2, AX_GOAL_POSITION, 677);
        __delay_ms(10);
        PutAX(AX_HG1, AX_GOAL_POSITION, 680);
        __delay_ms(10);
        PutAX(AX_HG2, AX_GOAL_POSITION, 364);
        __delay_ms(10);
    }
    nbverres = 0;
}


void Ouvrir_pince_bas()
{
//Ouvrir pince en position basse :
    PutAX(AX_BG, AX_GOAL_POSITION, 710);
    __delay_ms(10);
    PutAX(AX_BD, AX_GOAL_POSITION, 310);
    __delay_ms(200);
}

void Serrer_verre_en_haut()
{
    PutAX(AX_BG, AX_GOAL_POSITION, 845);
    __delay_ms(10);
    PutAX(AX_BD, AX_GOAL_POSITION, 170);
    __delay_ms(400);
}

volatile int retour=0;
int Serrer_verre_en_bas()
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
    __delay_ms(250);
    //valeur = 159;
    num_ax = AX_BD;
    data = AX_PRESENT_POSITION;
    GetAXnoWait();

    int verreok = 0;
    if (retour > 170) verreok = 1;
    return verreok;
}

void GetAXnoWait()
{
    GetAX(num_ax, data);
    //TMR5 = 0;
    while(!responseReadyAX)
        {
    //    T5CONbits.TON = 1;
        }
    retour = (responseAX.params[1]*256 + responseAX.params[0]);
    //T5CONbits.TON = 0;
    //TMR5 = 0;
}

void Serrer_stockage()
{
//Serrer la pince stockage
        PutAX(AX_HD1, AX_GOAL_POSITION, 263);
        __delay_ms(10);
        PutAX(AX_HD2, AX_GOAL_POSITION, 612);
        __delay_ms(10);
        PutAX(AX_HG1, AX_GOAL_POSITION, 760);
        __delay_ms(10);
        PutAX(AX_HG2, AX_GOAL_POSITION, 392);
        __delay_ms(10);
}

void Semi_ouvrir_stockage()
{
//Semi_ouvrir pince stockage
        PutAX(AX_HD1, AX_GOAL_POSITION, 307);
        __delay_ms(10);
        PutAX(AX_HD2, AX_GOAL_POSITION, 657);
        __delay_ms(10);
        PutAX(AX_HG1, AX_GOAL_POSITION, 718);
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

// ATP
void OnGetNombreVerres() { SendNombreVerres(nbverres); }

void OnSortirPince() {
    actionPince |= SORTIR_PINCE;
    IFS2bits.SPI2IF = 1;
}

void OnChopperVerre() {
    actionPince |= CHOPPER_VERRE;
    IFS2bits.SPI2IF = 1;
}

void OnLacherVerres() {
    actionPince |= LACHER_VERRE;
    IFS2bits.SPI2IF = 1;
}

