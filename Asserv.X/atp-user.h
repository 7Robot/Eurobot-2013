/* 
 * File:   atp-user.h
 * Author: elie
 *
 * Created on 8 f�vrier 2013, 23:25
 */

#ifndef ATP_USER_H
#define	ATP_USER_H

// Fonction de communication sp�cifique au r�le du pic
#include "atp-asserv.h"

// Vitesse de transmission, d�faut : 115200
#define BAUDRATE 115200

// Taille des buffers de transmission
// Doit �tre sup�rieur � la longueur maximal du plus long paquet envoy�
// Valeur conseill� : 64, valeur minimal conseill� : 32
#define BUF_SIZE 64


// Priorit� de RX INTERRUPT, doit �tre sup�rieur ou �gal � 1
#define RECV_PRIO 5
// Priorit� de TX INTERRUPT, doit �tre strictement sup�rieur � RECV_PRIO
// Vous pouvez envoyer des paquets seulement depuis des interruption de priorit�
// inf�rieur strictement � SEND_PRIO (ie si vous voulez envoyer un paquet depuis
// une interruption d�clench� par un capteur, cette interruption doit �tre de
// priorit� strictement inf�rieur � SEND_PRIO ; rien ne vous emp�che d'utiliser
// des interruptions de priorit� sup�rieur � �gal � SEND_PRIO tant que vous
// n'envoyez aucun paquet).
#define SEND_PRIO 6

// La d�finition de cette variable d�clenche l'envoit d'un paquet de
// notification d'erreur (message d'id inconnu)
#define REPORT_UNKNOW_PACKET

// La d�finition de cette variable provoque le clignotement de la led � la
// r�ception d?un packett
//#define BLINK_ON_PACKET


#define MAX_UCHAR 8
#define MAX_USHORT 8
#define MAX_UINT 8
#define MAX_CHAR 8
#define MAX_SHORT 8
#define MAX_INT 8
#define MAX_FLOAT 8

#endif	/* ATP_USER_H */

