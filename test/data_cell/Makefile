SRC = $(shell ls *.cc)
OBJs = $(SRC:.cc=.o)
PROG = data_cell_test

#########################################################
# set path
#########################################################
DIR_TOP = $(PWD)/../..


LAL_lib = $(DIR_TOP)/src/matrix_vector.o

CXX = g++
LINK = g++

INCs = -I$(DIR_TOP)/include

MKL_lib = 

LIBs = $(LAL_lib) $(MKL_lib)
CFLAGS = -Wall -O3 -g -std=c++11

all: $(OBJs)
	$(LINK) $(CFLAGS) $(OBJs) $(LIBs) -o $(PROG)  
	
%.o:%.cc
	$(CXX) $(CFLAGS) $(INCs) -c $<

clean :
	rm -rf $(OLIB) $(PROG) *.o
	
