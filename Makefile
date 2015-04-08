#!/bin/bash
CC		=	gcc
CXX		=	g++
CFLAGS	=	-g -Wall -std=c99 -O3
LIBS	=	-lgsl -lgslcblas -lm
INCLUDE	=	

all: zetaFunc

zetaFunc: zetaFunc.o firstPart.o secondPart.o thirdPart.o spheHarmYlm.o inteSubFunc.o io.o gen_points_array.o luscherZeta.o Makefile
	${CC} -o zetaFunc zetaFunc.o firstPart.o secondPart.o thirdPart.o spheHarmYlm.o inteSubFunc.o io.o gen_points_array.o luscherZeta.o ${LIBS}

%.o: %.c Makefile
	${CC} ${CFLAGS} ${INCLUDE} -o $@ -c $<

clean:
	rm *.o



