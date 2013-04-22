


#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include "AsservHeader.h"  /* Function / Parameters                           */
#include <libpic30.h>
#include <p33Fxxxx.h>      /* Includes device header file                     */


    volatile float PosX = 0.0, PosY = 0.0, Theta = 0.0;
    volatile float avancement = 0.0, delta_theta = 0.0;



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
