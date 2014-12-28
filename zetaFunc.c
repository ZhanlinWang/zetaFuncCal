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
  //Tolerance is the accuracy you would like to get.	
  double Tolerance;
  //l,m is the parameter of the spherical harmonics
  int l,m;
  //dVec is the boosted vector
  double dVec[3];
  //Lorenz forctor
  double gamma;
  //Lamda is the partition point of integration range (0, Inf).
  double Lamda;
  //qSqur is the squred moment E = e_1(q) + e_2(q)
  double qSqur;
	//verbose=1 will type out the details,default is 0
	int verbose;
  
  double complex firstPartSum,secondPartInt,thirdPartSum,zetaSum;
  int errorcode[3] = {0,0,0};
  
  int inputflag=1;
  inputflag *= read_d("Tolerance",&Tolerance);
  inputflag *= read_i("l",&l);
  inputflag *= read_i("m",&m);
  inputflag *= read_a("dVec",dVec);
  inputflag *= read_d("gamma",&gamma);
  inputflag *= read_d("Lamda",&Lamda);
  inputflag *= read_d("qSqur",&qSqur);
  inputflag *= read_i("verbose",&verbose);
  if(inputflag == 0){
    printf("There is something wrong when reading in parameters.\n");
    exit(-1);
  }
					
  firstPartSum  = firstPart(Tolerance, l, m, dVec, gamma, Lamda, qSqur, verbose, &errorcode[0]);
  if(errorcode[0]!=0) {
    fprintf(stderr, "GSL error in evaluation of first contribution to Luescher Zeta function, status code %d\n", errorcode[0]);
    exit(-2);
  }
  printf("firstPart  = %.24f %+.24fI\n",creal(firstPartSum),cimag(firstPartSum));
  
  secondPartInt = secondPart( l, gamma, Lamda, qSqur, &errorcode[1]);
  if(errorcode[1]!=0) {
    fprintf(stderr, "GSL error in evaluation of second contribution to Luescher Zeta function, status code %d\n", errorcode[1]);
    exit(-3);
  }
  printf("secondPart = %.24f %+.24fI\n",creal(secondPartInt),cimag(secondPartInt));
  
  thirdPartSum  = thirdPart(Tolerance, l, m, dVec, gamma, Lamda, qSqur, verbose, &errorcode[2]);
  if(errorcode[1]!=0) {
    fprintf(stderr, "GSL error in evaluation of third contribution to Luescher Zeta function, status code %d\n", errorcode[2]);
    exit(-3);
  }
  printf("thirdPart  = %.24f %+.24fI\n",creal(thirdPartSum),cimag(thirdPartSum));
  
  zetaSum = firstPartSum + secondPartInt + thirdPartSum;
  printf("\nzetaFunc   = %.24f %+.24fI\n",creal(zetaSum),cimag(zetaSum));

  if(verbose) {
    luscherZeta(&zetaSum, qSqur, l, m, gamma, Lamda, dVec, Tolerance, verbose, errorcode);
    printf("\nzetaFunc   = %.24f %+.24fI from call to luscherZeta\n",creal(zetaSum),cimag(zetaSum));
  }
	
  return 0;
}



