// Fichier auto-généré à partir de la version 1302111628 du fichier de protocole

#ifndef _SENSOR_H_
#define _SENSOR_H_

#define BOARD_ID 2
#define BOARD_NAME Sensor
#define BOARD_PROCESSOR processSensor

// You should define this function
void OnFloodOff();

// You should define this function
void OnFloodOn();

// You should define this function
void OnGetValue(unsigned char id);

void SendValue(unsigned char id, unsigned int value);

void SendZone(unsigned char id, unsigned char zone);

int processSensor(int id,
            unsigned char *ucharv, int ucharc,
            unsigned int *ushortv, int ushortc,
            unsigned long int *uintv, int uintc,
            char *charv, int charc,
            int *shortv, int shortc,
            long int *intv, int intc,
            float *floatv, int floatc);

#endif
