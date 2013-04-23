/*
* Turret dsPIC33F
* Compiler : Microchip xC16
* µC : 33FJ64MC802
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

#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "TurretSystem.h"  /* System funct/params, like osc/peripheral config */
#include "TurretUser.h"    /* User funct/params, such as InitApp              */

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
#include <uart.h>
#include <ports.h>
#include <adc.h>
#include <libpic30.h>
#include <pwm12.h>
#include <libpic30.h>
#include <timer.h>

volatile unsigned int i;
int adversaire1[taille_uart] = {1,0,0,1,0,1,1,0}; // Mettre la donnée envoyée
int adversaire2[taille_uart] = {1,0,1,0,1,0,1,0}; // mais complémentée

void acquisition(int donnees[]);
int comparer(int donnees[], int recepteur);
void lissage(void);

int16_t main(void)
{

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();

    TRISAbits.TRISA0 = 0; // Microstick LED
    LATAbits.LATA0 = 1;   // affichage recepteur 1 - adversaire 1
    TRISAbits.TRISA1 = 0;
    LATAbits.LATA0 = 1;   // affichage recepteur 2 - adversaire 1
    TRISBbits.TRISB0 = 0;
    LATBbits.LATB1 = 1;   // affichage recepteur 1 - adversaire 2
    TRISBbits.TRISB1 = 0;
    LATBbits.LATB1 = 1;   // affichage recepteur 2 - adversaire 2
    TRISCbits.TRISC9 = 1;  // TSOP1
    TRISBbits.TRISB5 = 1;  // TSOP2
	// ...

    int donnees[nombre_recepteurs*taille_uart];
    int recu = 0;
	int reperage[nombre_recepteurs]; // Contient : 0 non recu, 1 adversaire1, 2 adversaire2 pour chaque TSOP
    
    __delay_ms(2000);

    while(1)
    {
		// Detection du bit de Start
        if ((TSOP1 == 0) || (TSOP2 == 0) || (TSOP3 == 0) || (TSOP4 == 0) || (TSOP5 == 0) || (TSOP6 == 0) || (TSOP7 == 0) || (TSOP8 == 0) || 
			(TSOP9 == 0) || (TSOP10 == 0) || (TSOP11 == 0) || (TSOP12 == 0) || (TSOP13 == 0) || (TSOP14 == 0) || (TSOP15 == 0) || (TSOP16 == 0) || )
        {
            __delay_us(bit_periode_us/2); // Se place au millieu du bit de Start
            acquisition(int donnees[]);
			__delay_us(bit_periode_us); // Sort de la trame envoyee
            recu = 1;
        }

        if(recu)
        {
            for(i = 0 ; i < nombre_recepteurs ; i++)
			{
				reperage[i] = comparer(donnees, i);
			}
			lissage(); // Corrige les recepteurs defaillants
			recu = 0;
        }
    }
}

void acquisition(int donnees[])
{
    for(i = 0 ; i<taille_uart ; i++)
    {
		__delay_us(bit_periode_us); // Passe au bit suivant
        donnees[i] = TSOP1;
        donnees[taille_uart+i] = TSOP2;
		donnees[2*taille_uart+i] = TSOP3;
		donnees[3*taille_uart+i] = TSOP4;
		donnees[4*taille_uart+i] = TSOP5;
		donnees[5*taille_uart+i] = TSOP6;
		donnees[6*taille_uart+i] = TSOP7;
		donnees[7*taille_uart+i] = TSOP8;
		donnees[8*taille_uart+i] = TSOP9;
		donnees[9*taille_uart+i] = TSOP10;
		donnees[10*taille_uart+i] = TSOP11;
		donnees[11*taille_uart+i] = TSOP12;
		donnees[12*taille_uart+i] = TSOP13;
		donnees[13*taille_uart+i] = TSOP14;
		donnees[14*taille_uart+i] = TSOP15;
		donnees[15*taille_uart+i] = TSOP16;
    }
}

int comparer(int donnees[], int recepteur)
{
	int adversaire = 0;
	// Detection Adversaire 1
	int egal = 1;
    for(i = 0 ; i < taille_uart && egal ; i++)
    {
        if(donnees[recepteur*taille_uart+i] != adversaire1[i]){egal = 0;}
    }
	if(i == taille_uart-1 && egal) {adversaire = 1;}
	// Detection Adversaire 2
	int egal = 1;
    for(i = 0 ; i<taille_uart && egal ; i++)
    {
        if(donnees[recepteur*taille_uart+i] != adversaire2[i]){egal = 0;}
    }
	if(i == taille_uart-1 && egal) {adversaire = 2;}
	
    return adversaire;
}

void lissage(void)
{
	if((reperage[nombre_recepteurs-1] != 0) && (reperage[nombre_recepteurs-1] == reperage[1]) && (reperage[0] != reperage[nombre_recepteurs-1])) {reperage[0] = reperage[nombre_recepteurs-1];}
	for(i= 0 ; i < nombre_recepteurs-2 ; i++)
	{
		if((reperage[i] != 0) && (reperage[i] == reperage[i+2]) && (reperage[i+1] != reperage[i])) {reperage[i+1] = reperage[i];}
	}
	if((reperage[nombre_recepteurs-2] != 0) && (reperage[nombre_recepteurs-2] == reperage[0]) && (reperage[nombre_recepteurs-1] != reperage[nombre_recepteurs-2])) {reperage[nombre_recepteurs-1] = reperage[nombre_recepteurs-2];}
}