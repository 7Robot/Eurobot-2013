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
    volatile float Consigne_Dist = 0, Consigne_Angle = 0, Consigne_Vit = 0, Consigne_Tourner = 0;
    volatile float Vitesse_Max = 0.5; // M/s, à revoir dans le futur pour l'étalonage
    volatile float Acceleration = 0.05;
    



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

 float Get_Distance (void)            //renvoie la distance entre la consigne et la position actuelle
 {
     return sqrt((PosX - Consigne_PosX)*(PosX - Consigne_PosX) + (PosY - Consigne_PosY)*(PosY - Consigne_PosY));
 }

 float Get_Angle (void)             //renvoie l'angle entre la consigne et la position actuelle
 {
     //return atan((Consigne_PosX - PosX)/(Consigne_PosY - PosY));
     return atan2((Consigne_PosX - PosX),(Consigne_PosY - PosY));
 }

 void Incremente_Position(int16_t Diff_D, int16_t Diff_G, float *Vitesse, float *Omega, volatile float *Distance, volatile float *Angle)
 {
     float Avancement, Rotation;

     Avancement = (float)((Diff_D * METER_BY_TICD) + (Diff_G * METER_BY_TICG)) * 0.5;       // distance en metres parcourue par le milieu du robot
     *Vitesse = Avancement*100; // correpond à une vitesse en m/s: intervale de temps fixe (10ms)
     Rotation = (float)((Diff_D * METER_BY_TICD) - (Diff_G * METER_BY_TICG))/ LARGEUR_ROBOT;    // delta theta du robot
     *Omega = Rotation;         //correspond à une vitesse angulaire en ??

     *Distance += Avancement;
     PosX += Avancement * cos(Theta);
     PosY += Avancement * sin(Theta);
     Theta += Rotation;

     *Angle = Theta;
     //PosX = 0;
 }


 void Mise_A_Jour_Consignes(volatile char Mode_Consigne, volatile float *Consigne_Distance, volatile float *Consigne_Theta, volatile float *Consigne_Vitesse, volatile float *Consigne_Omega)
 {
     //float Distance, Angle;
     if (Mode_Consigne == 0)
     {
        //Rampe de vitesse ???
     }
     else if (Mode_Consigne == 1)
     {
         *Consigne_Theta = 0;
         *Consigne_Distance = Consigne_Dist;
     }
     else if (Mode_Consigne ==2)
     {
         *Consigne_Theta = Consigne_Angle;
         *Consigne_Distance = 0;
     }
     else if (Mode_Consigne == 3)
     {
         *Consigne_Theta = Get_Angle();
         *Consigne_Distance = Get_Distance();
         Distance_Actu = 0;
     }
     else if (Mode_Consigne == 4)
     {
         *Consigne_Omega = 0;
         *Consigne_Vitesse = Consigne_Vit;
     }
     else if (Mode_Consigne == 5)
     {
         *Consigne_Omega = Consigne_Tourner;
         *Consigne_Vitesse = 0;
     }
     else if (Mode_Consigne == 6)
     {
         *Consigne_Omega = Consigne_Tourner;
         *Consigne_Vitesse = Consigne_Vit;
     }
 }

 void Set_Consigne_Distance(float Consigne)
 {
     Distance_Actu = 0;
     Consigne_Dist = Consigne;
     Mode_Consigne = 1;
 }

 void Set_Consigne_Angle(float Consigne)
 {
     Consigne_Angle = Consigne;
     Mode_Consigne = 2;
 }

 void Set_Consigne(float New_Consigne_PosX, float New_Consigne_PosY)
{
    Consigne_PosX = New_Consigne_PosX;
    Consigne_PosY = New_Consigne_PosY;
    Mode_Consigne = 3;
}

 void Set_Consigne_Vitesse(float Consigne)
 {
     Consigne_Vit = Consigne;
     Mode_Consigne = 4;
 }

 void Set_Consigne_Omega(float Consigne)
 {
     Consigne_Tourner = Consigne;
     Mode_Consigne = 5;
 }

 void Set_Consigne_Courbe(float Consigne_V, float Consigne_O)
 {
     Consigne_Tourner = Consigne_O;
     Consigne_Vit = Consigne_V;
     Mode_Consigne = 6;
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
