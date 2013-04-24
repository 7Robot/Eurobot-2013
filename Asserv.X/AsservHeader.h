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
*			      7robot.fr
*/

/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        80000000 //7370000L
#define FCY             SYS_FREQ/2

/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

#define led _LATA0

//arbitrairement
#define TICS_BY_METERD 25000
#define TICS_BY_METERG 25000
#define METER_BY_TICD 0.00004
#define METER_BY_TICG 0.00004
#define LARGEUR_ROBOT 0.3       // 30cm entre droite et gauche

/******************************************************************************/
/* Function Prototypes                                                        */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void ConfigureOscillator(void);    /* Handles clock switching/osc initialization */

void InitApp(void);             /* I/O and Peripheral Initialization          */

void Set_Asserv_V(float, float, float);
void Set_Asserv_T(float, float, float);




void Set_Position(float, float);           // permet une mise à jour de la position, du robot
void Set_Postion_Angle(float, float, float);  // remet totalement à jour la position
void Get_Position (float*, float*, float*);       // renvoie la position actuelle du robot
void Incremente_Position(int16_t, int16_t, float*, float*);     // recoie les tics, incremente la position, renvoie la vitesse et l'angle (pour l'asserv)




float sin_lut (float);   // prends un nombre en radians, en renvoie son sinus
float cos_lut (float);   // prends un nombre en radians, en renvoie son cosinus


void Init_PWM(void);
void Set_Vitesse_MoteurD(float);
void Set_Vitesse_MoteurG(float);

