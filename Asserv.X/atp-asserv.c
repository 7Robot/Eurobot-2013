// Generated from version 1305062032 of semantic

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

void SendAngle(float theta) {
    char bytes[] = {
        129,
        42,
        36,
        ((char*)&theta)[0],
        ((char*)&theta)[1],
        ((char*)&theta)[2],
        ((char*)&theta)[3],
        128
    };
    SendBytes(bytes, 8);
}

void SendAsservD(float KPd, float KId, float KDd) {
    char bytes[] = {
        129,
        122,
        36,
        ((char*)&KPd)[0],
        ((char*)&KPd)[1],
        ((char*)&KPd)[2],
        ((char*)&KPd)[3],
        36,
        ((char*)&KId)[0],
        ((char*)&KId)[1],
        ((char*)&KId)[2],
        ((char*)&KId)[3],
        36,
        ((char*)&KDd)[0],
        ((char*)&KDd)[1],
        ((char*)&KDd)[2],
        ((char*)&KDd)[3],
        128
    };
    SendBytes(bytes, 18);
}

void SendAsservO(float KPo, float KIo, float KDo) {
    char bytes[] = {
        129,
        112,
        36,
        ((char*)&KPo)[0],
        ((char*)&KPo)[1],
        ((char*)&KPo)[2],
        ((char*)&KPo)[3],
        36,
        ((char*)&KIo)[0],
        ((char*)&KIo)[1],
        ((char*)&KIo)[2],
        ((char*)&KIo)[3],
        36,
        ((char*)&KDo)[0],
        ((char*)&KDo)[1],
        ((char*)&KDo)[2],
        ((char*)&KDo)[3],
        128
    };
    SendBytes(bytes, 18);
}

void SendAsservT(float KPt, float KIt, float KDt) {
    char bytes[] = {
        129,
        132,
        36,
        ((char*)&KPt)[0],
        ((char*)&KPt)[1],
        ((char*)&KPt)[2],
        ((char*)&KPt)[3],
        36,
        ((char*)&KIt)[0],
        ((char*)&KIt)[1],
        ((char*)&KIt)[2],
        ((char*)&KIt)[3],
        36,
        ((char*)&KDt)[0],
        ((char*)&KDt)[1],
        ((char*)&KDt)[2],
        ((char*)&KDt)[3],
        128
    };
    SendBytes(bytes, 18);
}

void SendAsservV(float KPv, float KIv, float KDv) {
    char bytes[] = {
        129,
        102,
        36,
        ((char*)&KPv)[0],
        ((char*)&KPv)[1],
        ((char*)&KPv)[2],
        ((char*)&KPv)[3],
        36,
        ((char*)&KIv)[0],
        ((char*)&KIv)[1],
        ((char*)&KIv)[2],
        ((char*)&KIv)[3],
        36,
        ((char*)&KDv)[0],
        ((char*)&KDv)[1],
        ((char*)&KDv)[2],
        ((char*)&KDv)[3],
        128
    };
    SendBytes(bytes, 18);
}

void SendCourbe(float v, float omega) {
    char bytes[] = {
        129,
        72,
        36,
        ((char*)&v)[0],
        ((char*)&v)[1],
        ((char*)&v)[2],
        ((char*)&v)[3],
        36,
        ((char*)&omega)[0],
        ((char*)&omega)[1],
        ((char*)&omega)[2],
        ((char*)&omega)[3],
        128
    };
    SendBytes(bytes, 13);
}

void SendDone() {
    char bytes[] = {
        129,
        2,
        128
    };
    SendBytes(bytes, 3);
}

// You should redefine this function
__attribute__((weak)) void OnGetAngle() {}

// You should redefine this function
__attribute__((weak)) void OnGetAsservD() {}

// You should redefine this function
__attribute__((weak)) void OnGetAsservO() {}

// You should redefine this function
__attribute__((weak)) void OnGetAsservT() {}

// You should redefine this function
__attribute__((weak)) void OnGetAsservV() {}

// You should redefine this function
__attribute__((weak)) void OnGetCourbe() {}

// You should redefine this function
__attribute__((weak)) void OnGetOmega() {}

// You should redefine this function
__attribute__((weak)) void OnGetPos() {}

// You should redefine this function
__attribute__((weak)) void OnGetVit() {}

// You should redefine this function
__attribute__((weak)) void OnOdoBroadcastOff() {}

// You should redefine this function
__attribute__((weak)) void OnOdoBroadcastOn() {}

// You should redefine this function
__attribute__((weak)) void OnOdoBroadcastSetDelay(unsigned int delay) {}

void SendOmega(float omega) {
    char bytes[] = {
        129,
        62,
        36,
        ((char*)&omega)[0],
        ((char*)&omega)[1],
        ((char*)&omega)[2],
        ((char*)&omega)[3],
        128
    };
    SendBytes(bytes, 8);
}

void SendPos(float x, float y, float theta) {
    char bytes[] = {
        129,
        32,
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
__attribute__((weak)) void OnSetAngle(float theta) {}

// You should redefine this function
__attribute__((weak)) void OnSetAsservD(float KPd, float KId, float KDd) {}

// You should redefine this function
__attribute__((weak)) void OnSetAsservO(float KPo, float KIo, float KDo) {}

// You should redefine this function
__attribute__((weak)) void OnSetAsservT(float KPt, float KIt, float KDt) {}

// You should redefine this function
__attribute__((weak)) void OnSetAsservV(float KPv, float KIv, float KDv) {}

// You should redefine this function
__attribute__((weak)) void OnSetCourbe(float v, float omega) {}

// You should redefine this function
__attribute__((weak)) void OnSetDist(float dist) {}

// You should redefine this function
__attribute__((weak)) void OnSetOmega(float omega) {}

// You should redefine this function
__attribute__((weak)) void OnSetPos(float x, float y) {}

// You should redefine this function
__attribute__((weak)) void OnSetVit(float v) {}

// You should redefine this function
__attribute__((weak)) void OnStop() {}

void SendVit(float v) {
    char bytes[] = {
        129,
        52,
        36,
        ((char*)&v)[0],
        ((char*)&v)[1],
        ((char*)&v)[2],
        ((char*)&v)[3],
        128
    };
    SendBytes(bytes, 8);
}


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
    if (id == 41) {
        OnGetAngle();
        return 1;
    }
    if (id == 121) {
        OnGetAsservD();
        return 1;
    }
    if (id == 111) {
        OnGetAsservO();
        return 1;
    }
    if (id == 131) {
        OnGetAsservT();
        return 1;
    }
    if (id == 101) {
        OnGetAsservV();
        return 1;
    }
    if (id == 71) {
        OnGetCourbe();
        return 1;
    }
    if (id == 61) {
        OnGetOmega();
        return 1;
    }
    if (id == 31) {
        OnGetPos();
        return 1;
    }
    if (id == 51) {
        OnGetVit();
        return 1;
    }
    if (id == 11) {
        OnOdoBroadcastOff();
        return 1;
    }
    if (id == 10) {
        OnOdoBroadcastOn();
        return 1;
    }
    if (id == 12) {
        OnOdoBroadcastSetDelay(ushortv[0]);
        return 1;
    }
    if (id == 40) {
        OnSetAngle(floatv[0]);
        return 1;
    }
    if (id == 120) {
        OnSetAsservD(floatv[0], floatv[1], floatv[2]);
        return 1;
    }
    if (id == 110) {
        OnSetAsservO(floatv[0], floatv[1], floatv[2]);
        return 1;
    }
    if (id == 130) {
        OnSetAsservT(floatv[0], floatv[1], floatv[2]);
        return 1;
    }
    if (id == 100) {
        OnSetAsservV(floatv[0], floatv[1], floatv[2]);
        return 1;
    }
    if (id == 70) {
        OnSetCourbe(floatv[0], floatv[1]);
        return 1;
    }
    if (id == 20) {
        OnSetDist(floatv[0]);
        return 1;
    }
    if (id == 60) {
        OnSetOmega(floatv[0]);
        return 1;
    }
    if (id == 30) {
        OnSetPos(floatv[0], floatv[1]);
        return 1;
    }
    if (id == 50) {
        OnSetVit(floatv[0]);
        return 1;
    }
    if (id == 1) {
        OnStop();
        return 1;
    }
    return 0;
}

