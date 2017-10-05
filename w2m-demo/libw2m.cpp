#include "libw2m.h"


libw2m::libw2m(void)
{
      this->hm=LoadLibraryA("libw2m.dll");

	
	  this->pyin_init=(pcpyin_init)GetProcAddress(hm,"cpyin_init");
	  this->pyin_trange=(pcpyin_trange)GetProcAddress(hm,"cpyin_trange");
	  this->pyin_analyze=(pcpyin_analyze)GetProcAddress(hm,"cpyin_analyze");
	  this->wavread=(pcwavread)GetProcAddress(hm,"cwavread");
	  this->wavwrite=(pcwavwrite)GetProcAddress(hm,"cwavwrite");
	  this->wavwrite=(pcwavwrite)GetProcAddress(hm,"cwavwrite");
	  this->wchar2char=(pwchar2char)GetProcAddress(hm,"wchar2char");


}


libw2m::~libw2m(void)
{
  if(this->hm!=0)FreeLibrary(hm);
}
