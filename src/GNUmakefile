RM=rm -rfv
AR=ar
ARFLAGS=rsv
ifndef LIBPVN
LIBPVN=../../libpvn
endif # !LIBPVN
include $(LIBPVN)/src/pvn.mk
CC=$(PVN_CC)
CFLAGS=$(PVN_CFLAGS) $(PVN_CPPFLAGS)
LDFLAGS=$(PVN_LDFLAGS) $(PVN_LIBS)

SRCS=afmt.c bf.c ddet.c sdet.c
EXES=$(SRCS:.c=.exe)

.PHONY: all help clean

all: $(EXES)

help:
	@echo $(MAKE) "[all|clean|help]"

%.exe : %.c
	$(CC) $(CFLAGS) -DVKASDET2_TEST="\"dynamic_exe\"" $< -o $@ $(LDFLAGS)

bf.exe : bf.c
	$(CC) $(CFLAGS) -frounding-math -DVKASDET2_TEST="\"dynamic_exe\"" $< -o $@ $(LDFLAGS)

clean:
	-$(RM) $(EXES)
	-$(RM) *.optrpt
	-$(RM) *.dSYM
