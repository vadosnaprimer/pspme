ifeq ($(ROOT),)
ROOT = ..
endif

TARGET = pspME
OBJS = pspME.o

INCDIR = 
CFLAGS = -G0 -Wall -I$(ROOT)/javacall/configuration/phoneMEAdvanced/psp_mips/output/inc
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

ifeq ($(USE_DEBUG), true)
g = _g
CFLAGS += -g
else
g =
CFLAGS += -O2
endif
LIBDIR =
LDFLAGS =  -L$(ROOT)/cdc/build/psp-mips-generic/lib -L$(ROOT)/cdc/build/psp-mips-generic/bin -L$(ROOT)/pcsl/output/psp_mips/lib 
LIBS := -lSDL -lSDL_mixer -lpsphprm -lvorbis -lvorbisfile -logg -lpspaudiolib -lpspaudio -lpspgu -l psprtc -lm
LIBS := -lpcsl_file -lpcsl_print -lpcsl_memory -lpcsl_string -lpcsl_network -ljavacall$(g) $(LIBS) 

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = pspME v0.2.1
PSP_EBOOT_ICON = java-duke-guitar.png

PSPSDK=$(shell psp-config --pspsdk-path)
include build.mak
