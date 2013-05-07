/* 
 * File:   atp-user.h
 * Author: elie
 *
 * Created on 8 février 2013, 23:25
 */

#ifndef ATP_USER_H
#define	ATP_USER_H

// Fonction de communication spécifique au rôle du pic
#include "atp-asserv.h"

// Vitesse de transmission, défaut : 115200
#define BAUDRATE 115200

// Taille des buffers de transmission
// Doit être supérieur à la longueur maximal du plus long paquet envoyé
// Valeur conseillé : 64, valeur minimal conseillé : 32
#define BUF_SIZE 64


// Priorité de RX INTERRUPT, doit être supérieur ou égal à 1
#define RECV_PRIO 5
// Priorité de TX INTERRUPT, doit être strictement supérieur à RECV_PRIO
// Vous pouvez envoyer des paquets seulement depuis des interruption de priorité
// inférieur strictement à SEND_PRIO (ie si vous voulez envoyer un paquet depuis
// une interruption déclenché par un capteur, cette interruption doit être de
// priorité strictement inférieur à SEND_PRIO ; rien ne vous empèche d'utiliser
// des interruptions de priorité supérieur à égal à SEND_PRIO tant que vous
// n'envoyez aucun paquet).
#define SEND_PRIO 6

// La définition de cette variable déclenche l'envoit d'un paquet de
// notification d'erreur (message d'id inconnu)
#define REPORT_UNKNOW_PACKET

// La définition de cette variable provoque le clignotement de la led à la
// réception d?un packett
//#define BLINK_ON_PACKET


#define MAX_UCHAR 8
#define MAX_USHORT 8
#define MAX_UINT 8
#define MAX_CHAR 8
#define MAX_SHORT 8
#define MAX_INT 8
#define MAX_FLOAT 8

#endif	/* ATP_USER_H */

