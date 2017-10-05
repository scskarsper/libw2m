cd /d "%~0dp"
del /q .\Output\*.o
del /q .\Output\*.a
del /q .\Output\*.def
copy .\libw2m.h .\Output\libw2m.h
copy .\libw2m.cpp .\Output\libw2m.cpp