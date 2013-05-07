/*
* Asserv dsPIC33F
* Compiler : Microchip xC16
* µC : 33FJ64MC804
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

#define led1 _LATB4
#define led2 _LATA8

#define DIRA1 _LATC3    //DIRA1 sur RC3
#define DIRB1 _LATC4    //DIRB1 sur RC4
#define DIRA2 _LATA3    //DIRA2 sur RA3
#define DIRB2 _LATA4    //DIRB2 sur RA4

//arbitrairement
#define TICS_BY_METERD 24500
#define TICS_BY_METERG 24500
#define METER_BY_TICD 0.00004
#define METER_BY_TICG 0.00004
#define LARGEUR_ROBOT 0.291       // 29.1cm entre encodeurs droite et gauche

#define PI 3.14159265359

#define CONSIGNE_MAX 800
#define CONSIGNE_MIN 200
#define CONSIGNE_NULLE 20

#define VITESSE_MAX 1
#define OMEGA_MAX 10

#define ACCELERATION_V 2
#define DECELERATION_V 2
#define ACCELERATION_O 0.5
#define DECELERATION_O 0.5

#define SIGN(a) ((a<0)?-1:1)

/******************************************************************************/
/* Function Prototypes                                                        */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void ConfigureOscillator(void);    /* Handles clock switching/osc initialization */

void InitApp(void);             /* I/O and Peripheral Initialization          */

void Set_Asserv_V(float, float, float);
void Set_Asserv_O(float, float, float);
void Set_Asserv_D(float, float, float);
void Set_Asserv_T(float, float, float);

void Set_Position(float, float);           // permet une mise à jour de la position, du robot
void Set_Postion_Angle(float, float, float);  // remet totalement à jour la position
void Get_Position(float*, float*, float*);       // renvoie la position actuelle du robot
float Get_Angle(void);
float Get_Distance_Obj(float, float);          //renvoie la distance entre la consigne et la position actuelle
float Get_Angle_Obj(float, float);             //renvoie l'angle entre la consigne et la position actuelle
void Incremente_Position(int16_t, int16_t, volatile float*, volatile float*, volatile float*, volatile float*);     // recoie les tics, incremente la position, renvoie la vitesse et l'angle (pour l'asserv)

 void Set_Rampe_Position(float, float);
 void Set_Rampe_Distance(float);
 void Set_Rampe_Angle(float);
 void Set_Consigne_Distance(float);
 void Set_Consigne_Angle(float);
 void Set_Consigne_Position(float, float);
 void Set_Consigne_Vitesse(float);
 void Mise_A_Jour_Consignes(void);




//float sin_lut(float);   // prends un nombre en radians, en renvoie son sinus
//float cos_lut(float);   // prends un nombre en radians, en renvoie son cosinus


void Init_PWM(void);
void Set_Vitesse_MoteurD(float);
void Set_Vitesse_MoteurG(float);

