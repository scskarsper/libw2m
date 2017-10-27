// w2m-demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <math.h>
#include <stdlib.h>
#include <Windows.h>
#include "libw2m.h"
#include "sox-wapper.h"

float midNote(float freq)
{
	if(freq==0)return 0;
	float mn=69+12*(log(freq/440.0)/log(2.0));
	float mn2=ceil(mn*100)/100;
	return mn2+0.5;
}

char* GetOctave(int Note)
{
	char* ret=(char*)malloc(sizeof(char)*5);
	memset(ret,0,sizeof(char)*5);
	if(Note>0)
	{
		int N=Note%12;
		int O=Note/12;
		switch(N)
		{
			case 0:strcpy(ret,"C ");break;
			case 1:strcpy(ret,"C#");break;
			case 2:strcpy(ret,"D ");break;
			case 3:strcpy(ret,"Eb");break;
			case 4:strcpy(ret,"E ");break;
			case 5:strcpy(ret,"F ");break;
			case 6:strcpy(ret,"F#");break;
			case 7:strcpy(ret,"G ");break;
			case 8:strcpy(ret,"G#");break;
			case 9:strcpy(ret,"A ");break;
			case 10:strcpy(ret,"Bb");break;
			case 11:strcpy(ret,"B ");break;
		}
		char atr[3]="";
		itoa(O-2,atr,10);
		strcat(ret,atr);
	}else
	{
		strcpy(ret,"Sil");
	}
	return &ret[0];
}

int pyin_demo(_TCHAR* filename)
{
  libw2m w2m=libw2m();
  int fs = 0;
  int nbit = 0;
  int nx = 0;
  FP_TYPE* x = w2m.wavread(w2m.wchar2char(filename), & fs, & nbit, & nx);
  //One Point TimeBlock Length
  float block_time=0.005;

  pyin_config param = w2m.pyin_init(ceil(fs * block_time));
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
	float Note=midNote(f0[i]);
    printf("%7.3f sec = %s (%7.3f / %7.2f Hz)  ",i*block_time, GetOctave(Note) , Note ,f0[i]);
    int l = f0[i] > 0 ? ((f0[i] - 50.0) / (800.0 - 50.0)) * 40 + 5 : 0;
    for(int j = 0; j < l; j ++)
      printf("█");
    printf("\n");
  }
  w2m.~libw2m();
  return 0;
}

long Second2Tick(long Second,float BPM)
{
	float Atom=(60000 / (BPM * 480));
	return (float)Second*1000.0/Atom;
}

int pyin_wav2note(_TCHAR* filename)
{
  libw2m w2m=libw2m();
  int fs = 0;
  int nbit = 0;
  int nx = 0;
  FP_TYPE* x = w2m.wavread(w2m.wchar2char(filename), & fs, & nbit, & nx);
  //One Point TimeBlock Length
  float block_time=0.005;

  pyin_config param = w2m.pyin_init(ceil(fs * block_time));
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
  int lastNote=0;
  float lastTick=0;
  float lastFloat=0;
  for(int i = 0; i < nfrm; i ++) {
	float Note=midNote(f0[i]);
	int intNote=Note;
	float Tick=Second2Tick(i*block_time,120);
	if(intNote!=lastNote || i+1==nfrm)
	{
		//printf("%ld Tick / %7.3f Sec ",lastTick,lastFloat);
		printf("= %s (%d / %7.2f Hz)  ",GetOctave(lastNote) , lastNote ,f0[i]);
		printf("\n");
		lastNote=Note;
		lastTick=Tick;
		lastFloat=i*block_time;
	}
  }
  /*
  float startPx=0;
  float endPx=0;
  int lastPy=0;
  for(int i = 0; i < nfrm; i ++) {
	float Note=midNote(f0[i]);
	int Py=Note;
	float Px=i*block_time;

	if(Py!=lastPy || i+1==nfrm)
	{
		int NoteY=lastPy;
		float PosS=Millisecond2Tick(startPx,120);
		float DurS=Millisecond2Tick(endPx-startPx,120);
		if(DurS>0.1)
		{
			printf("%s:form %7.3f sec,during %7.3f\n",GetOctave(Note) , PosS ,DurS);
			lastPy=Py;
			startPx=Px;
			endPx=Px;
		}
	}else
	{
		endPx=Px;
	}
  }*/

  w2m.~libw2m();
  return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{
  if(argc < 2) {
    fprintf(stderr, "Missing argument.\n");
    return 1;
  }
  TCHAR* ssource=argv[1];
  TCHAR* tdir=_file2tdir(argv[1]);
  TCHAR* tsource=_tdir2source(tdir);

  ConvertChannel(ssource,tsource);

  pyin_wav2note(tsource);
  
  _tunlink(tdir);
  return 0;
}

