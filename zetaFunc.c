/*************************************************
 * 
 * Author: Zhanlin Wang
 * Date	 : October 2014
 * email : zhanlin_wang@126.com
 *
 * ************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#include "zetaFunc.h"

int main(void)
{
	//N is the number of terms summed.	
	int N;
	//qSqur is the squred moment E = e_1(q) + e_2(q)
	double qSqur;
	//l,m is the parameter of the spherical harmonics
	int l,m;
	//dVec is the boosted vector
	int dVec[3];
	//Lorenz forctor
	double gamma;
	//Lamda is the partition point of integration range (0, Inf).
	double Lamda;

	double complex firstPartSum,secondPartInt,thirdPartSum,zetaSum;

	int inputflag=1;
	inputflag *= read_i("N",&N);
	inputflag *= read_i("l",&l);
	inputflag *= read_i("m",&m);
	inputflag *= read_a("dVec",dVec);
	inputflag *= read_d("gamma",&gamma);
	inputflag *= read_d("Lamda",&Lamda);
	inputflag *= read_d("qSqur",&qSqur);
	if(inputflag == 0){
		printf("There is something wrong when reading in parameters.\n");
		exit(-1);
	}

	firstPartSum  = firstPart(N, l, m, dVec, gamma, Lamda, qSqur);
	printf("firstPart  = %.24f %+.24fI\n",creal(firstPartSum),cimag(firstPartSum));
	secondPartInt = secondPart( l, gamma, Lamda, qSqur);
	printf("secondPart = %.24f %+.24fI\n",creal(secondPartInt),cimag(secondPartInt));
	thirdPartSum  = thirdPart(N, l, m, dVec, gamma, Lamda, qSqur);
	printf("thirdPart  = %.24f %+.24fI\n",creal(thirdPartSum),cimag(thirdPartSum));

	zetaSum = firstPartSum + secondPartInt + thirdPartSum;
	printf("\nzetaFunc   = %.24f %+.24fI\n",creal(zetaSum),cimag(zetaSum));

	return 0;
}
