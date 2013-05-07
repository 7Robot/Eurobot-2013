// Fichier auto-généré à partir de la version 1302110058 du fichier de protocole

#ifndef _CAPTOR_H_
#define _CAPTOR_H_

#define BOARD_ID 2
#define BOARD_NAME Captor
#define BOARD_PROCESSOR processCaptor

// You should define this function
void OnGetValue(unsigned char id);

void SendValue(unsigned char id, float value);

int processCaptor(int id,
            unsigned char *ucharv, int ucharc,
            unsigned int *ushortv, int ushortc,
            unsigned long int *uintv, int uintc,
            char *charv, int charc,
            int *shortv, int shortc,
            long int *intv, int intc,
            float *floatv, int floatc);

#endif
