#include "dll.h"
#include "gcc-external/libpyin/external/matlabfunctions.h"
#include "gcc-external/libpyin/math-funcs.h"
#include "gcc-external/libpyin/pyin.h"

pyin_config cpyin_init(int nhop)
{
	return pyin_init(nhop);
}

int cpyin_trange(int nq, float fmin, float fmax)
{
	return pyin_trange(nq, fmin, fmax); 
}

float* cpyin_analyze(pyin_config param, float* x, int nx, float fs, int* nfrm)
{
	return pyin_analyze(param, x, nx, fs, nfrm);
}

float * cwavread(char* filename, int *fs, int *nbit, int *wav_length)
{
	return wavread(filename, fs, nbit, wav_length);
}

void cwavwrite(double *x, int x_length, int fs, int nbit, char *filename) {
	return wavwrite(x, x_length, fs, nbit, filename);
}

void array_wav2hz_release(float * arr)
{
	free(arr);
}
