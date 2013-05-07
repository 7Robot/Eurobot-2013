/*
* Template dsPIC33F
* Compiler : Microchip xC16
* µC : 33FJ64MC804
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
/* System Level #define Macros                                                */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        80000000 //7370000L
#define FCY             SYS_FREQ/2

/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

//Baud Rate pour la liaison UART AX_12
#define BAUDRATEAX12 57600
#define BRGVALAX12 ((FCY / BAUDRATEAX12 / 16) - 1)

#define led _LATA0
#define led2 _LATA1

#define AX_BG 8
#define AX_BD 11
#define AX_HG1 16
#define AX_HG2 17
#define AX_HD1 6
#define AX_HD2 7

#define microswitch_bas_de_pince _RC5
//etat du microswitch bas de course pour la pince : 1 = pince en bas, 0 = pas detecte

/******************************************************************************/
/* Function Prototypes                                                        */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */
void InitApp(void);             /* I/O and Peripheral Initialization          */

//protos AX12 pince
void Cinematique_inverse();
void Ouvrir_pince_bas();
int Serrer_verre_en_bas();
void Serrer_verre_en_haut();
void Serrer_stockage();
void Semi_ouvrir_stockage();
void Ouvrir_stockage();
void Rangement_stockage();
void Rangement_pince();
void Sortir_Pince();
void Chopper_verre();
void Lacher_verres();
int GetAXnoWait();

//protos de asserv pince
void Set_Vitesse(int);
void Set_Consigne_Hauteur(long);
void Set_Asserv_h(float, float);
void reset_pince(void);
void Init_PWM(void);
void Set_Vitesse_MoteurH(long);
void pince_en_descente(void);
void pince_en_montee(void);

// From Bras_AX12
extern volatile char actionAx;
