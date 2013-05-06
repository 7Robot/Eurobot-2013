// Fichier auto-généré à partir de la version 1302111628 du fichier de protocole

#include "atp.h"

__attribute__((weak)) void OnFloodOff() {}

__attribute__((weak)) void OnFloodOn() {}

__attribute__((weak)) void OnGetValue(unsigned char id) {}

void SendValue(unsigned char id, unsigned int value) {
    char bytes[] = { 
            129,
            2,
            1,
            id,
            2,
            ((char*)&value)[0],
            ((char*)&value)[1],
            128
        };
    SendBytes(bytes, 8);
}

void SendZone(unsigned char id, unsigned char zone) {
    char bytes[] = { 
            129,
            3,
            1,
            id,
            1,
            zone,
            128
        };
    SendBytes(bytes, 7);
}

int processSensor(int id,
            unsigned char *ucharv, int ucharc,
            unsigned int *ushortv, int ushortc,
            unsigned long int *uintv, int uintc,
            char *charv, int charc,
            int *shortv, int shortc,
            long int *intv, int intc,
            float *floatv, int floatc) {
    if (id == 5) {
        OnFloodOff();
        return 1;
    }
    if (id == 4) {
        OnFloodOn();
        return 1;
    }
    if (id == 1) {
        OnGetValue(ucharv[0]);
        return 1;
    }
    return 0;
}
