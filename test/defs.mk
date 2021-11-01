CC  = gcc -fdiagnostics-color=always

CCV = $(shell $(CC) -v 2>&1 |grep ' version '|awk '{print $$3}'|sed 's/\..*//')
ifeq "$(CCV)" "7"
    Wv := -Wimplicit-fallthrough=1
endif
ifeq "$(CCV)" "8"
    Wv := -Wimplicit-fallthrough=1
endif

ifeq (,$(findstring +,$(CC)))
    STD = -std=gnu11
else
    STD = -std=gnu++14
endif

A   = -march=native -mtune=native -mno-omit-leaf-frame-pointer
#A  = -m32

E   = -D_GNU_SOURCE # -Dinline=__inline__

Ob  = -O3 -fbuiltin # -funroll-all-loops
Ot  = # -ftree-loop-linear -ftree-vectorize -funswitch-loops #-ftree-combine-temps
Oi  = # -fkeep-inline-functions
Of  = -fno-omit-frame-pointer
Om  = -mfpmath=sse,387 -mfancy-math-387
OM  = # -ffast-math -fno-finite-math-only # sigh.  Fast but hopeless
Ow  = -fwhole-program -flto # (not for a library)
Os  = -Os
Oa  = -fstrict-aliasing -Wstrict-aliasing
O   = $(Ob) $(Oa) $(Of) $(Ot) $(Oi) $(Om) $(OM)

# ped g++ warns->err
W  := -W -Wall -Wextra -Wno-long-long -Wno-variadic-macros -Wno-unused-parameter -Wstrict-prototypes $(Wv)
G   = -ggdb -g3

PIC = -fPIC
SLD = $(CC) -shared
LIBX = 64

CFLAGS = $A $E $I $(STD) $W $D $O $(Ox) $G # may want $(Ow), -Os, etc.
