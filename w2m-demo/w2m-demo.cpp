// w2m-demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <math.h>
#include <stdlib.h>
#include <Windows.h>
#include "libw2m.h"


int pyin_demo(_TCHAR* filename)
{
	
  libw2m w2m=libw2m();
  int fs = 0;
  int nbit = 0;
  int nx = 0;
  FP_TYPE* x = w2m.wavread(w2m.wchar2char(filename), & fs, & nbit, & nx);
  
  pyin_config param = w2m.pyin_init(ceil(fs * 0.005));
  param.fmin = 50.0;
  param.fmax = 800.0;
  param.trange = w2m.pyin_trange(param.nq, param.fmin, param.fmax);
  param.nf = ceil(fs * 0.025);
  param.w = param.nf / 3;
  
  int nfrm = 0;
  FP_TYPE* f0 = w2m.pyin_analyze(param, x, nx, fs, & nfrm);
  
  FP_TYPE min = param.fmax;
  FP_TYPE max = param.fmin;
  for(int i = 0; i < nfrm; i ++) {
    if(f0[i] > 0) {
      if(f0[i] < min) min = f0[i];
      if(f0[i] > max) max = f0[i];
    }
  }
  
  for(int i = 0; i < nfrm; i ++) {
    printf("%7.2f  ", f0[i]);
    int l = f0[i] > 0 ? ((f0[i] - 50.0) / (800.0 - 50.0)) * 40 + 5 : 0;
    for(int j = 0; j < l; j ++)
      printf("█");
    printf("\n");
  }
  w2m.~libw2m();
  return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
  if(argc < 2) {
    fprintf(stderr, "Missing argument.\n");
    return 1;
  }
  pyin_demo(argv[1]);
  return 0;
}

