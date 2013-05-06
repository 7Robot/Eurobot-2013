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

 float Get_Angle(void)
 {
     return Theta;
 }

 float Get_Consigne_Distance (float Consigne_PosX, float Consigne_PosY)            //renvoie la distance entre la consigne et la position actuelle
 {
     return sqrt(pow(PosX - Consigne_PosX, 2) + pow(PosY - Consigne_PosY, 2));
 }

 float Get_Consigne_Angle (float Consigne_PosX, float Consigne_PosY)             //renvoie l'angle entre la consigne et la position actuelle
 {
     //return atan((Consigne_PosX - PosX)/(Consigne_PosY - PosY));
     return atan2(Consigne_PosX - PosX, Consigne_PosY - PosY);
 }

 void Incremente_Position(int16_t Diff_D, int16_t Diff_G, volatile float *Vitesse, volatile float *Omega, volatile float *Distance, volatile float *Angle)
 {
     float Avancement, Rotation;

     Avancement = (float)((Diff_D * METER_BY_TICD) + (Diff_G * METER_BY_TICG)) * 0.5;       // distance en metres parcourue par le milieu du robot
     *Vitesse = Avancement*100; // correpond à une vitesse en m/s: intervale de temps fixe (10ms)
     Rotation = (float)(Diff_D * METER_BY_TICD - Diff_G * METER_BY_TICG)/ LARGEUR_ROBOT;    // delta theta du robot
     *Omega = Rotation;         //correspond à une vitesse angulaire en ??

     *Distance += Avancement;
     PosX += Avancement * sin(Theta);
     PosY += Avancement * cos(Theta);
     Theta += Rotation;

     *Angle = Theta;
     //PosX = 0;
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
