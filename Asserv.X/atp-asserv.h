// Generated from version 1303020239 of semantic

#ifndef _ASSERV_H_
#define _ASSERV_H_

#define BOARD_ID 5
#define BOARD_NAME Asserv


void SendError();

void OnGetId();

void SendId(unsigned char id);

void OnTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f);

void SendTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f);

void OnDist(unsigned long int dist);

void SendDone();

void OnGetPos();

void OnGoTo(float x, float y, float theta);

void OnOdoBroadcastOff();

void OnOdoBroadcastOn();

void OnOdoBroadcastSetDelay(unsigned int delay);

void SendPos(float x, float y, float theta);

void OnSetPos(float x, float y, float theta);

void OnSetSpeed(char v, char omega);

void OnStop();


int AtpDecode(int id,
        unsigned char *ucharv, int ucharc,
        unsigned int *ushortv, int ushortc,
        unsigned long int *uintv, int uintc,
        char *charv, int charc,
        int *shortv, int shortc,
        long int *intv, int intc,
        float *floatv, int floatc);

#endif // _ASSERV_H_
