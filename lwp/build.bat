if exist c:\AuraGUI\lwp\build.bat goto clean
echo lwp root not detected ( c:\AuraGUI\lwp)
goto end

:clean
if exist example1.exe del example1.exe
if exist example.exe del example.exe
if exist example2.exe del example2.exe
if exist example3.exe del example3.exe
if exist example4.exe del example4.exe
if exist lwp.o del lwp.o
if exist lwpasm.o del lwpasm.o
if exist liblwp.a del liblwp.a
goto cpath

:cpath
set path=c:\AuraGUI\DJGPP\BIN;%path%;c:\AuraGUI\djgpp\watt32\src;c:\AuraGUI\djgpp\watt32\bin;c:\AuraGUI\djgpp\watt32\util;c:\AuraGUI\djgpp\watt32\lib;c:\AuraGUI\djgpp\watt32\inc;c:\AuraGUI\include\pdcurses\
set DJGPP=c:\AuraGUI\DJGPP\DJGPP.env
set WATT_ROOT=c:\AuraGUI\DJGPP\watt32
set PDCURSES_SRCDIR=c:\AuraGUI\include\pdcurses\
make

if exist liblwp.a echo lwp has build successfully

:end
