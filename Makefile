#!/bin/bash
CC		=	gcc
CXX		=	g++
CFLAGS	=	-g -Wall -std=c99
LIBS	=	-L/home/wangzhanlin/opt/lib -lgsl -lgslcblas -lm
INCLUDE	=	-I/home/wangzhanlin/opt/include 
all:

zetaFunc:zetaFunc.o firstPart.o secondPart.o thirdPart.o spheHarmYlm.o inteSubFunc.o io.o
	${CC} ${LIBS} -o zetaFunc zetaFunc.o firstPart.o secondPart.o thirdPart.o spheHarmYlm.o inteSubFunc.o io.o


%.o:%.c
	${CC} ${CFLAGS} ${INCLUDE} -o $@ -c $<

clean:
	rm *.o



