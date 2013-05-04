// Generated from version 1303020239 of semantic

#include "atp.h"


void SendError() {
    char bytes[] = {
        129,
        253,
        128
    };
    SendBytes(bytes, 3);
}

// You should redefine this function
__attribute__((weak)) void OnGetId() { SendBoardId(); }

void SendId(unsigned char id) {
    char bytes[] = {
        129,
        255,
        1,
        id,
        128
    };
    SendBytes(bytes, 5);
}

// You should redefine this function
__attribute__((weak)) void OnTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f) { SendTest(B, H, I, b, h, i, f); }

void SendTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f) {
    char bytes[] = {
        129,
        252,
        1,
        B,
        2,
        ((char*)&H)[0],
        ((char*)&H)[1],
        4,
        ((char*)&I)[0],
        ((char*)&I)[1],
        ((char*)&I)[2],
        ((char*)&I)[3],
        17,
        b,
        18,
        ((char*)&h)[0],
        ((char*)&h)[1],
        20,
        ((char*)&i)[0],
        ((char*)&i)[1],
        ((char*)&i)[2],
        ((char*)&i)[3],
        36,
        ((char*)&f)[0],
        ((char*)&f)[1],
        ((char*)&f)[2],
        ((char*)&f)[3],
        128
    };
    SendBytes(bytes, 28);
}

// You should redefine this function
__attribute__((weak)) void OnDist(unsigned long int dist) {}

void SendDone() {
    char bytes[] = {
        129,
        12,
        128
    };
    SendBytes(bytes, 3);
}

// You should redefine this function
__attribute__((weak)) void OnGetPos() {}

// You should redefine this function
__attribute__((weak)) void OnGoTo(float x, float y, float theta) {}

// You should redefine this function
__attribute__((weak)) void OnOdoBroadcastOff() {}

// You should redefine this function
__attribute__((weak)) void OnOdoBroadcastOn() {}

// You should redefine this function
__attribute__((weak)) void OnOdoBroadcastSetDelay(unsigned int delay) {}

void SendPos(float x, float y, float theta) {
    char bytes[] = {
        129,
        21,
        36,
        ((char*)&x)[0],
        ((char*)&x)[1],
        ((char*)&x)[2],
        ((char*)&x)[3],
        36,
        ((char*)&y)[0],
        ((char*)&y)[1],
        ((char*)&y)[2],
        ((char*)&y)[3],
        36,
        ((char*)&theta)[0],
        ((char*)&theta)[1],
        ((char*)&theta)[2],
        ((char*)&theta)[3],
        128
    };
    SendBytes(bytes, 18);
}

// You should redefine this function
__attribute__((weak)) void OnSetPos(float x, float y, float theta) {}

// You should redefine this function
__attribute__((weak)) void OnSetSpeed(char v, char omega) {}

// You should redefine this function
__attribute__((weak)) void OnStop() {}


int AtpDecode(int id,
        unsigned char *ucharv, int ucharc,
        unsigned int *ushortv, int ushortc,
        unsigned long int *uintv, int uintc,
        char *charv, int charc,
        int *shortv, int shortc,
        long int *intv, int intc,
        float *floatv, int floatc)
{
    if (id == 254) {
        OnGetId();
        return 1;
    }
    if (id == 252) {
        OnTest(ucharv[0], ushortv[0], uintv[0], charv[0], shortv[0], intv[0], floatv[0]);
        return 1;
    }
    if (id == 10) {
        OnDist(uintv[0]);
        return 1;
    }
    if (id == 20) {
        OnGetPos();
        return 1;
    }
    if (id == 126) {
        OnGoTo(floatv[0], floatv[1], floatv[2]);
        return 1;
    }
    if (id == 16) {
        OnOdoBroadcastOff();
        return 1;
    }
    if (id == 15) {
        OnOdoBroadcastOn();
        return 1;
    }
    if (id == 17) {
        OnOdoBroadcastSetDelay(ushortv[0]);
        return 1;
    }
    if (id == 19) {
        OnSetPos(floatv[0], floatv[1], floatv[2]);
        return 1;
    }
    if (id == 127) {
        OnSetSpeed(charv[0], charv[1]);
        return 1;
    }
    if (id == 11) {
        OnStop();
        return 1;
    }
    return 0;
}

