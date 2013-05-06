// Generated from version 1305062032 of semantic

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

void SendAsservD(float KPd, float KId, float KDd);

void SendAsservO(float KPo, float KIo, float KDo);

void SendAsservT(float KPt, float KIt, float KDt);

void SendAsservV(float KPv, float KIv, float KDv);

void SendCourbe(float v, float omega);

void SendDone();

void OnGetAngle();

void OnGetAsservD();

void OnGetAsservO();

void OnGetAsservT();

void OnGetAsservV();

void OnGetCourbe();

void OnGetOmega();

void OnGetPos();

void OnGetVit();

void OnOdoBroadcastOff();

void OnOdoBroadcastOn();

void OnOdoBroadcastSetDelay(unsigned int delay);

void SendOmega(float omega);

void SendPos(float x, float y, float theta);

void OnSetAngle(float theta);

void OnSetAsservD(float KPd, float KId, float KDd);

void OnSetAsservO(float KPo, float KIo, float KDo);

void OnSetAsservT(float KPt, float KIt, float KDt);

void OnSetAsservV(float KPv, float KIv, float KDv);

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
