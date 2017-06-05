SRC = $(shell ls *.cc)
OBJs = $(SRC:.cc=.o)
PROG = matrix_vector_test

#########################################################
# set path
#########################################################
DIR_TOP = $(PWD)/../..


LAL_lib = -L$(DIR_TOP)/lib -lLAL

CXX = g++
LINK = g++

MKL_inc = $(MKLROOT)/include
MKL_lib = -L$(MKLROOT)/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread	

INCs = -I$(DIR_TOP)/include \
	-I${MKL_inc}

LIBs = $(LAL_lib) $(MKL_lib)
CFLAGS = -Wall -O3 -g -std=c++11

all: $(OBJs)
	$(LINK) $(CFLAGS) $(OBJs) $(LIBs) -o $(PROG)  
	
%.o:%.cc
	$(CXX) $(CFLAGS) $(INCs) -c $<

clean :
	rm -rf $(OLIB) $(PROG) *.o
	
