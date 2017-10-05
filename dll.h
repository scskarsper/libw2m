#ifndef _CPYIN_DLL_H_
#define _CPYIN_DLL_H_

#if BUILDING_DLL
#define CPYIN_DLLIMPORT __declspec(dllexport)
#else
#define CPYIN_DLLIMPORT __declspec(dllimport)
#endif
#if __GNUC__
typedef unsigned short wchar_t ;
#endif
#define FP_TYPE float
#include "gcc-external/libpyin/pyin.h"

CPYIN_DLLIMPORT pyin_config cpyin_init(int nhop);

CPYIN_DLLIMPORT int cpyin_trange(int nq, float fmin, float fmax);

CPYIN_DLLIMPORT float* cpyin_analyze(pyin_config param, float* x, int nx, float fs, int* nfrm);

CPYIN_DLLIMPORT float * cwavread(char* filename, int *fs, int *nbit, int *wav_length);

CPYIN_DLLIMPORT void cwavwrite(double *x, int x_length, int fs, int nbit, char *filename);

CPYIN_DLLIMPORT char* wchar2char(wchar_t* wcharstring);


#endif
