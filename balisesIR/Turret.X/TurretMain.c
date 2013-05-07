/*
* Turret dsPIC33F
* Compiler : Microchip xC16
* dsPIC33FJ64MC804
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
#include "TurretUser.h"    /* User funct/params, such as InitApp              */
#include "atp.h"

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
#include "atp-turret.h"

// Declarations de variable globales
volatile unsigned int i;
volatile unsigned int j;
volatile unsigned int adversaire;
volatile unsigned int distance;
volatile unsigned int direction;
int adversaire1[taille_uart] = {0,1,0,1,1,1,1,1};
int adversaire2[taille_uart] = {1,0,0,1,1,1,1,1};
int reperage[nombre_recepteurs]; // Contient : 0 non recu, 1 adversaire1, 2 adversaire2 pour chaque TSOP
int donnees[nombre_recepteurs*taille_uart];

// Prototypes des fonctions
void acquisition(int donnees[]);
int comparer(int donnees[], int recepteur);
void lissage(void);
int who (int reperage[]);
int howFar (int reperage[], int adversaire);
int wichDirection (int reperage[], int adversaire);

int16_t main(void)
{

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
    AtpInit();
    __delay_ms(500);
    SendId(BOARD_ID);


    int recu = 0;

    int y;
    for (y=0;y<10;y++)
    {
        led1 = !led1;
        led2 = !led1;
        __delay_ms(200);
    }
    __delay_ms(1000);

    while(1)
    {
		// Detection du bit de Start
        if (!TSOP1 || !TSOP2 || !TSOP3 || !TSOP4 || !TSOP5 || !TSOP6 || !TSOP7 || !TSOP8 || 
            !TSOP9 || !TSOP10 || !TSOP11 || !TSOP12 || !TSOP13 || !TSOP14 || !TSOP15 || !TSOP16)
        {
            __delay_us(bit_periode_us/2); // Se place au millieu du bit de Start
            acquisition(donnees);
            __delay_us(bit_periode_us); // Sort de la trame envoyee
            recu = 1;
        }

        if(recu)
        {
            for(j = 0 ; j < nombre_recepteurs ; j++)
            {
        	reperage[j] = comparer(donnees, j);
            }
            lissage(); // Corrige les recepteurs defaillants
			adversaire = who(reperage); // Indique si on vient de recevoir adversaire 1 ou 2
			distance = howFar(reperage, adversaire); // Donne le nombre de TSOP allumes
			direction = wichDirection(reperage, adversaire); // de 0 TSOP0 a 32 TSOP16
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
    for(i = 0 ; i < taille_uart-1 ; i++)
    {
        if(donnees[recepteur*taille_uart+i] != adversaire1[i]) break;
    }
	if(i == taille_uart-1 && donnees[recepteur*taille_uart+i] == adversaire1[i])
	{
		adversaire = 1;
                led2 = 0;
                led1 = 1;
	}

	// Detection Adversaire 2
    for(i = 0 ; i<taille_uart-1; i++)
    {
        if(donnees[recepteur*taille_uart+i] != adversaire2[i]) break;
    }
	if(i == taille_uart-1 && donnees[recepteur*taille_uart+i] == adversaire2[i])
	{
		adversaire = 2;
                led1 = 0;
                led2 = 1;
	}
	
    return adversaire;
}

void lissage(void)
{
	if((reperage[nombre_recepteurs-1] != 0) && (reperage[nombre_recepteurs-1] == reperage[1]) && (reperage[0] != reperage[nombre_recepteurs-1]))
	{
		reperage[0] = reperage[nombre_recepteurs-1];
	}
	for(i= 0 ; i < nombre_recepteurs-2 ; i++)
	{
		if((reperage[i] != 0) && (reperage[i] == reperage[i+2]) && (reperage[i+1] != reperage[i])) 
		{
			reperage[i+1] = reperage[i];
		}
	}
	if((reperage[nombre_recepteurs-2] != 0) && (reperage[nombre_recepteurs-2] == reperage[0]) && (reperage[nombre_recepteurs-1] != reperage[nombre_recepteurs-2])) 
	{
		reperage[nombre_recepteurs-1] = reperage[nombre_recepteurs-2];
	}
}

int who (int reperage[])
{
	int k = 0, sortie = 0;
	while(!reperage[k] && k < nombre_recepteurs) k++;
	sortie = reperage[k];
	return sortie;
}

int howFar (int reperage[], int adversaire)
{
	int k = 0, first = 0, last = 0, longueur = 0;
	if (!reperage[0]) // TSOP0 ne reçoit rien
	{
		while(reperage[k] != adversaire && k < nombre_recepteurs) k++;
		first = k;
		while(reperage[k] == adversaire && k < nombre_recepteurs) k++;
		last = k;
		longueur = last - first;
	}
	else if (!reperage[nombre_recepteurs-1]  && reperage[0] == adversaire) // TSOP0 est first
	{
		k++;
		while(reperage[k] == adversaire && k < nombre_recepteurs) k++;
		// last = k;
		longueur = k;
	}
	else	// TSOP0 est entre first et last
	{
		while(reperage[k] == adversaire && k < nombre_recepteurs) k++;
		last = k;
		while(reperage[k] != adversaire && k < nombre_recepteurs) k++;
		first = k;
		longueur = (last + nombre_recepteurs - first) % nombre_recepteurs;
	}
	return longueur;
}

int wichDirection (int reperage[], int adversaire)
{
	int k = 0, first = 0, last = 0, angle = 0;
	if (!reperage[0]) // TSOP0 ne reçoit rien
	{
		while(reperage[k] != adversaire && k < nombre_recepteurs) k++;
		first = k;
		while(reperage[k] == adversaire && k < nombre_recepteurs) k++;
		last = k;
		angle = last + first;
	}
	else if (!reperage[nombre_recepteurs-1]  && reperage[0] == adversaire) // TSOP0 est first
	{
		k++;
		while(reperage[k] == adversaire && k < nombre_recepteurs) k++;
		// last = k;
		angle = k;
	}
	else	// TSOP0 est entre first et last
	{
		while(reperage[k] == adversaire && k < nombre_recepteurs) k++;
		last = k;
		while(reperage[k] != adversaire && k < nombre_recepteurs) k++;
		first = k;
		angle = (last + nombre_recepteurs + first) % (2*nombre_recepteurs);
	}
	return angle;
}
