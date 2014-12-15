#include <stdio.h>
#include <math.h>
#include <float.h>
#include <complex.h>
#include <stdlib.h>

#include "zetaFunc.h"


double complex firstPart(const double Tolerance, const int l, const int m, const double * dVec, const double gamma, const double Lamda, const double qSqur, const int verbose, int * const rstatus)
{
  double complex firstTerms=0+I*0, pmodeSum=0+I*0, firstPartSum=0+I*0;
  double cosPolarAngle,azAngle;
  double rVecMod;

	//Initialization parameters
	double error = 1.0;
	int pmodeSqur, degnrtDOF;
	
	int n1,n2,n3;
  double dModSqur=dVec[0]*dVec[0]+dVec[1]*dVec[1]+dVec[2]*dVec[2];

	FILE * rPointSets, *rUsefulPmode;
	rPointSets 		= fopen("./genDecartesianPointSets.txt","r");
	rUsefulPmode 	= fopen("./genUsefulPmode.txt","r");

	while(error > Tolerance){
		fscanf(rUsefulPmode,"pmode=%d have %d degenaration DOF.\n", &pmodeSqur, &degnrtDOF);
		if(verbose)
			printf("Pmode=%d have %d degenaration DOF.\n", pmodeSqur, degnrtDOF);

		pmodeSum = 0+I*0;
		for(int i=0; i<degnrtDOF; i++){
			fscanf(rPointSets,"%d %d %d", &n1, &n2, &n3);
			if(verbose)
				printf("%3d %3d %3d\n", n1, n2, n3);
      
			double nSqur = n1*n1+n2*n2+n3*n3; 

			if( dModSqur == 0 ){
        rVecMod = sqrt( nSqur );
        if(n1==0 && n2==0 && n3==0){
          cosPolarAngle =0;
          azAngle =0;
        }
        else{
          cosPolarAngle =  n3/sqrt(nSqur) ;
          azAngle = azimutalAngle(n1,n2) ;
        }
      }
      else{
        double nDotd = n1*dVec[0]+n2*dVec[1]+n3*dVec[2];
        rVecMod = sqrt( (pow(nDotd,2.0)/dModSqur + dModSqur/4.0 - nDotd)/pow(gamma,2.0)
                        + nSqur  - pow(nDotd,2.0)/dModSqur);
        cosPolarAngle = ((nDotd*dVec[2]/dModSqur-dVec[2]/2.0)/gamma + (n3-nDotd*dVec[2]/dModSqur))
          / rVecMod;
        azAngle=azimutalAngle((nDotd*dVec[0]/dModSqur-dVec[0]/2.0)/gamma+(n1-nDotd*dVec[0]/dModSqur),
                              (nDotd*dVec[1]/dModSqur-dVec[1]/2.0)/gamma + (n2-nDotd*dVec[1]/dModSqur));
      }
      
      if(fabs(cosPolarAngle) > 1) {
        // cosPolarAngle must not become larger than 1 
        // we check for this here and drop a warning if unexpectedly large
        if(fabs(1-fabs(cosPolarAngle)) > DBL_EPSILON) fprintf(stderr, "Warning, cosPolarAngle > 1 by %e\n", 1-fabs(cosPolarAngle));
        cosPolarAngle /= fabs(cosPolarAngle);
      }
      
      firstTerms = exp(-Lamda*(pow(rVecMod,2.0)-qSqur)) * pow(rVecMod,l)
        * spheHarm(l, m, cosPolarAngle, azAngle, rstatus)
        / (pow(rVecMod,2.0) - qSqur);
      if(*rstatus != 0) {
        return(firstPartSum);
      }
			
			//Add every term within the same pmode into pmodeSum
			pmodeSum += firstTerms;
		}

		firstPartSum += pmodeSum;
		//Both pmodeSum and firstPartSum are complex numbers,cabs take the mode of these variables.
		error = cabs(pmodeSum) / cabs(firstPartSum);
		if(verbose)
			printf("pmode%d error: %.8f\n\n",pmodeSqur , error);
	}

  //printf("qSqur=%.4f,	 firstPartSum = %.24f %+.24fI.\n",qSqur, creal(firstPartSum), cimag(firstPartSum));
  return firstPartSum;
}
				





/*
		double coordntArray[][3];
		if(NULL == (* coordntArray = (double)malloc(degnrtDOF*3*sizeof(double)))){
			printf("Error mallocing for Descartesian coordinate sets.\n");
			exit(-1);
		}

			fscanf(rPointSets,"%d %d %d",(*coordntArray + i), (*coordntArray + i)+1, (coordntArray + i)+2);
			printf("%3d %3d %3d\n",(*coordntArray + i)[0], (*coordntArray + i)[1], (*coordntArray + i)[2]);
*/
