#set environment variable RM_INCLUDE_DIR to the location of redismodule.h
# find the OS
uname_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')

# Compile flags for linux / osx
ifeq ($(uname_S),Linux)
	SHOBJ_CFLAGS ?=  -fno-common -g -ggdb
	SHOBJ_LDFLAGS ?= -shared -Bsymbolic
else
	SHOBJ_CFLAGS ?= -dynamic -fno-common -g -ggdb
	SHOBJ_LDFLAGS ?= -bundle -undefined dynamic_lookup
endif

CFLAGS = -I./deps/cpu_features/include -Wall -g -fPIC -lc -lm -std=gnu99 -O3
CC ?=gcc

ifeq ($(ARCH_NATIVE),1)
CFLAGS+= -march=native
endif


all: cpu_features_lib cpu_features.o cpu_features.so

cpu_features_lib: FORCE
	cd deps/cpu_features; mkdir -p build; cd build; cmake ..; make; cd ../../.. 

cpu_features.so: cpu_features.o 
	$(LD) -o $@ cpu_features.o $(SHOBJ_LDFLAGS) $(LIBS) -L ./deps/cpu_features/build  -lcpu_features -lc 

clean:
	rm -rf deps/cpu_features/build *.xo *.so *.o

FORCE: