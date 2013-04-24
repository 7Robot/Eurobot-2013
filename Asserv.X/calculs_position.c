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


    volatile float PosX = 0.0, PosY = 0.0, Theta = 0.0;
    volatile float avancement = 0.0, delta_theta = 0.0;
    volatile float Consigne_PosX = 0, Consigne_PosY = 0, Consigne_Thet = 0;
    volatile float Consigne Vit = 0;
    volatile float Vitesse_Max = 1; // M/s, à revoir dans le futur pour l'étalonage
    volatile char Mode_Consigne = 0;



void Set_Position(float NewX, float NewY)           // permet une mise à jour de la position, du robot
{
    PosX = NewX;
    PosY = NewY;
}

 void Set_Postion_Angle(float NewX, float NewY, float NewTheta)  // remet totalement à jour la position
 {
     Theta = NewTheta;
     PosX = NewX;
     PosY = NewY;
 }


 void Get_Position (float* X, float* Y, float* angle)       // renvoie la position actuelle du robot
 {
     *X = PosX;
     *Y = PosY;
     *angle = Theta;
 }
 float Get_Distance (void)
 {
     return sqrt((PosX - Consigne_PosX)^2 + (PosY - Consigne_PosY)^2);
 }

 void Incremente_Position(int16_t Diff_D, int16_t Diff_G, float* Vitesse, float* Angle)
 {
     float Avancement, Rotation;


     Avancement = (float)((Diff_D * METER_BY_TICD) + (Diff_G * METER_BY_TICG)) * 0.5;       // distance en metres parcourue par le milieu du robot
     *Vitesse = Avancement; // correpond aussi à une vitesse : intervale de temps fixe
     Rotation = (float)((Diff_D * METER_BY_TICD) - (Diff_G * METER_BY_TICG))/ LARGEUR_ROBOT;    // delta theta du robot

     PosX += Avancement * cos_lut(Theta);
     PosY += Avancement * sin_lut(Theta);
     Theta += Rotation;

     *Angle = Theta;
     //PosX = 0;
 }

 void Mise_A_Jour_Consignes(float* Consigne_Vitesse, float* Consigne_Theta, float Vitesse_Actu)
 {
     float Distance;
     if (Mode_Consigne == 0)
     {
         Distance = Get_Distance();

     }
     else
     {
         *Consigne_Theta = Consigne_Thet;
         *Consigne_Vitesse = Consigne_Vit; // NIM: cette variable n'existe nulle part ailleurs :)
     }
 }

 /* plan plateau
  * Y
  * ^
  * |
  * |
  * |
  * |
  * |
  * |
  * 0------------> X
  *
  *
  *
  */
