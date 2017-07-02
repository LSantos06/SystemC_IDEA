SYSTEMC_HOME    = /usr/local/systemc-2.3
TARGET_ARCH     = linux

SYSTEMC_INC_DIR = $(SYSTEMC_HOME)/include
SYSTEMC_LIB_DIR = $(SYSTEMC_HOME)/lib-$(TARGET_ARCH)

# LIBTOOL Setting
SHELL           = /bin/bash
LIBTOOL_DIR     = /usr/bin
LIBTOOL         = $(SHELL) $(LIBTOOL_DIR)/libtool

GXX             = g++
GCC             = gcc
LD              = g++

FLAGS           = -g -Wall -pedantic -Wno-long-long \
                 -DSC_INCLUDE_DYNAMIC_PROCESSES -fpermissive \
                 -I$(SYSTEMC_INC_DIR) 
LDFLAGS         = -L$(SYSTEMC_LIB_DIR) -lsystemc -lm

SRCS = IDEA.cpp IDEA_operations.cpp IDEA_rounds.cpp IDEA_shell.cpp mastershell.cpp networkinterfacefrontendbase.cpp specialkernel.cpp main.cpp
OBJS=$(SRCS:.cpp=.o)

# main
main: $(OBJS)
	$(LIBTOOL) --mode=link --tag=CXX g++ -o $@ $(OBJS) $(LDFLAGS)

.cpp.o:
	$(LIBTOOL) --mode=compile g++ -c $(FLAGS) $<

%.o: %.c
	$(LIBTOOL) --mode=compile gcc -Wall -c $<

clean:
	rm -f main *.o *.lo
	rm -rf .libs
