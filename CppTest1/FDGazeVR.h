#pragma once

//#include "logc.h"

//#define PDVIVEDK2 1
//#define CONST_P_POINT 1

static const int nglints = 8;


struct EyeGlint
{
	EyeGlint() {};
	EyeGlint(float xi, float yi) :x(xi), y(yi) {};
    float x, y, re;
};

//NOTE: all unused field should be set to -1;

struct PupilGlint
{
	PupilGlint() {};
	PupilGlint(float px, float py) :pupilx(px), pupily(py) {};
    float pupilx;
    float pupily;
    EyeGlint glints[nglints];
    float Ex[8];
};
