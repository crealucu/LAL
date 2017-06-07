
SRC = $(shell ls *.cc)
OBJs = $(SRC:.cc=.o)
PROG = memory_check

#########################################################
# set path
#########################################################
DIR_TOP = $(PWD)/../..
include $(DIR_TOP)/make.in

INCs = -I$(DIR_TOP)/include -I$(MKL_inc)
LIBs = $(MKL_lib)

all: $(OBJs)
	$(LINK) $(CFLAGS) $(OBJs) $(MKL_lib) -o $(PROG)  
	
%.o:%.cc
	$(CXX) $(CFLAGS) $(INCs) -c $<

clean :
	rm -rf $(OLIB) $(PROG) *.o
	
