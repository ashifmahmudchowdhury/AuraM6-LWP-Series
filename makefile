# Phoenix 1.2 Makefile
# Written by Lukas Lipka and Julien Etelain

CFLAGS   = -O3 -funroll-loops -Iinclude -Ilwp -Idjgpp/watt32/inc -Ldjgpp/watt32/lib -lcurses
CPPFLAGS = -O3 -funroll-loops -Iinclude -Ilwp -Idjgpp/watt32/inc -Ldjgpp/watt32/lib
AFLAGS = -ddjgpp -fcoff

# cflag -std=c99
REMOVE = del
OBJ_DIR = obj
DYNLDLNK = dynldlnk.exe
MAIN = bin/main.exe
OBJ_LIST2 = $(OBJ_DIR)/vfile/msdos.o
LIB_LIST = lib/libz.a lib/libalttf.a -lalleg lib/libwatt.a lib/libmpeg2.a lib/judaslib.a lwp/liblwp.a
LIB_DYNLNK = lib/libz.a
# OBJ_LWP = lwp/lwp.o lwp/lwpasm.o obj/xlib/lwpaura.o
# OBJ_LWP = obj/xlib/lwpaura.o
LIB_LWP = lwp/liblwp.a 

include common.mak