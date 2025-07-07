echo clean directories:
del obj\xlib\*.o
del obj\xlib\widget\*.o
del obj\xapps\*.o
del obj\dms\*.o
del obj\dms\png\*.o
del obj\dms\jpg\*.o
del obj\dms\jpg\*.o
del obj\dms\mp3\*.o
del obj\dms\mp3\decoder\*.o
del obj\vfile\*.o
del bin\xapps\*.app
del bin\xlib\*.dl
del bin\main.exe

echo Aura M6 builder august 2023 build :4000 
if exist c:\dj.bat goto cpath
if exist c:\auragui\dj.bat goto full
goto error

:full
echo DJGPP was detected in the ROOT of C:\AURAGUI

set path=c:\AURAGUI\DJGPP\BIN;%path%;c:\AURAGUI\djgpp\watt32\src;c:\AURAGUI\djgpp\watt32\bin;c:\AURAGUI\djgpp\watt32\util;c:\AURAGUI\djgpp\watt32\lib;c:\AURAGUI\djgpp\watt32\inc;c:\AURAGUI\include\pdcurses\
set DJGPP=c:\AURAGUI\DJGPP\DJGPP.env
set WATT_ROOT=c:\AURAGUI\DJGPP\watt32
set PDCURSES_SRCDIR==c:\AURAGUI\include\pdcurses\
make
goto end

:cpath
echo DJGPP was detected in the ROOT of C:\
set path=c:\DJGPP\BIN;%path%;c:\djgpp\watt32\src;c:\djgpp\watt32\bin;c:\djgpp\watt32\util;c:\djgpp\watt32\lib;c:\djgpp\watt32\inc;c:\include\pdcurses\
set DJGPP=c:\DJGPP\DJGPP.env
set WATT_ROOT=c:\DJGPP\watt32
set PDCURSES_SRCDIR=c:\include\pdcurses\
make > 
goto end

:error
if exist c:\bin\main.exe goto end
if exist c:\auragui\bin\main.exe goto end
echo well youre fucked lol.
pause

:end
if exist c:\bin\main.exe echo Aura has been Built. 
if exist c:\auragui\bin\main.exe echo Aura has been Built. 
