// Generated from version 1305061627 of semantic

#ifndef _ASSERV_H_
#define _ASSERV_H_

#define BOARD_ID 5
#define BOARD_NAME Asserv


void SendError();

void OnGetId();

void SendId(unsigned char id);

void OnTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f);

void SendTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f);

void SendAngle(float theta);

void SendCourbe(float v, float omega);

void SendDone();

void OnGetAngle();

void OnGetCourbe();

void OnGetOmega();

void OnGetPos();

void OnGetVit();

void OnOdoBroadcastOff();

void OnOdoBroadcastOn();

void OnOdoBroadcastSetDelay(unsigned int delay);

void SendOmega(float omega);

void SendPos(float x, float y);

void OnSetAngle(float theta);

void OnSetCourbe(float v, float omega);

void OnSetDist(float dist);

void OnSetOmega(float omega);

void OnSetPos(float x, float y);

void OnSetVit(float v);

void OnStop();

void SendVit(float v);


int AtpDecode(int id,
        unsigned char *ucharv, int ucharc,
        unsigned int *ushortv, int ushortc,
        unsigned long int *uintv, int uintc,
        char *charv, int charc,
        int *shortv, int shortc,
        long int *intv, int intc,
        float *floatv, int floatc);

#endif // _ASSERV_H_
