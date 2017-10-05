#pragma once
#include <Windows.h>

#define FP_TYPE float
	typedef struct {
	  FP_TYPE fmin;     // minimum frequency
	  FP_TYPE fmax;     // maximum frequency
	  int nq;           // quantization
	  int w;            // correlation length
	  FP_TYPE beta_a;   // alpha param. for prior distribution of threshold
	  FP_TYPE beta_u;   // mean param. for prior distribution of threshold
	  FP_TYPE threshold;// increase the probability of a candidate if d'(tau) < threshold
	  FP_TYPE bias;     // voicing bias: > 1: towards voiced, < 1: towards unvoiced
	  FP_TYPE ptrans;   // voicing/unvoicing transition probability
	  int trange;       // maximum allowed transition distance
	  int nf;           // size of analysis frame
	  int nhop;         // hop size between consecutive frames
	} pyin_config;
class libw2m
{
	typedef pyin_config (*pcpyin_init)(int nhop);
	typedef int (*pcpyin_trange)(int nq, float fmin, float fmax);
	typedef float* (*pcpyin_analyze)(pyin_config param, float* x, int nx, float fs, int* nfrm);
	typedef float * (*pcwavread)(char* filename, int *fs, int *nbit, int *wav_length);
	typedef void (*pcwavwrite)(double *x, int x_length, int fs, int nbit, char *filename);
	typedef char* (*pwchar2char)(wchar_t* wcharstring);
private:
	HMODULE hm;
public:
	pcpyin_init pyin_init;
	pcpyin_trange pyin_trange;
	pcpyin_analyze pyin_analyze;
	pcwavread wavread;
	pcwavwrite wavwrite;
	pwchar2char wchar2char;
	libw2m(void);
	~libw2m(void);
};

