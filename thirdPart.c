#include <stdio.h>
#include <math.h>
#include <complex.h>

#include <gsl/gsl_math.h>
#include "zetaFunc.h"

double complex thirdPart(const double Tolerance, const int l, const int m, double * const dVec, 
                         const double gamma, const double Lamda, const double qSqur, const int verbose,
                         int * const rstatus)
{
  double complex thirdTerms = 0+I*0, pmodeSum=0+I*0, thirdPartSum = 0+I*0;
  double cosPolarAngle=0,azAngle=0;
  double wVecMod=0;

	//Initialization parameters
	double error = 1.0;
	int pmodeSqur, degnrtDOF;

  int n1,n2,n3;
  double dModSqur = dVec[0]*dVec[0]+dVec[1]*dVec[1]+dVec[2]*dVec[2];

  int s1=0, s2=0;

	FILE * rPointSets, *rUsefulPmode;
  rPointSets    = fopen("./genDecartesianPointSets.txt","r");
	rUsefulPmode  = fopen("./genUsefulPmode.txt","r");

	while(error > Tolerance){
		fscanf(rUsefulPmode,"pmode=%d have %d degenaration DOF.\n", &pmodeSqur, &degnrtDOF);

		//The following setense is not so formal,it's used to move the file pointer to 
		//the next pmode 1 points,because point (0, 0, 0) should be passed.
		fscanf(rPointSets,"%d %d %d", &n1, &n2, &n3);

		//From the formula in the paper: w!=0
		if(pmodeSqur == 0)
			continue;
		
		if(verbose)
			printf("pmode=%d have %d degenaration DOF.\n", pmodeSqur, degnrtDOF);
	
		pmodeSum = 0+I*0;
		for(int i=0; i<degnrtDOF; i++){
			//n1,n2,n3 stands for the components of vector w.
			fscanf(rPointSets,"%d %d %d", &n1, &n2, &n3);
			if(verbose)
				printf("%3d %3d %3d\n", n1, n2, n3);

      double nSqur = n1*n1 + n2*n2 + n3*n3;

      //nVec needed by the integrand in the exponential
      int nVec[3] = {n1, n2 ,n3};

      if( dModSqur == 0 ){
        wVecMod = sqrt( nSqur );
        cosPolarAngle =  n3/wVecMod ;
        azAngle = azimutalAngle(n1,n2) ;
        thirdTerms = gamma * pow(wVecMod, l)
          * spheHarm(l, m, cosPolarAngle, azAngle, &s1)
          * trdInteFunc(Lamda, dVec, l, qSqur, nVec, gamma, &s2);
      }
      else{
        double wDotd = n1*dVec[0]+n2*dVec[1]+n3*dVec[2];
        //wVecMod stands for |\hat{gamma} * \vec{w}|
        wVecMod = sqrt((pow(gamma,2)-1) * pow(wDotd,2) /dModSqur
                       + nSqur);
        cosPolarAngle=((gamma-1)*wDotd*dVec[2]/dModSqur + n3)/wVecMod;
        
        
        if(fabs(cosPolarAngle) > 1) {
          // cosPolarAngle must not become larger than 1 
          // we check for this here and drop a warning if unexpectedly large
          if(fabs(1-cosPolarAngle) > DBL_EPSILON) fprintf(stderr, "Warning, cosPolarAngle > 1 by %e\n", 1-cosPolarAngle);
          cosPolarAngle /= fabs(cosPolarAngle);
        }
        
        
        azAngle = azimutalAngle((gamma-1)*wDotd*dVec[0]/dModSqur + n1 ,
                                (gamma-1)*wDotd*dVec[1]/dModSqur + n2);
        thirdTerms = gamma * (cos(M_PI*wDotd) - I*sin(M_PI*wDotd))
          * pow(wVecMod, l) *spheHarm(l, m, cosPolarAngle, azAngle, &s1)
          * trdInteFunc(Lamda, dVec, l, qSqur, nVec, gamma, &s2);
      }
      if(s1 != 0 || s2 != 0) {
        *rstatus = s1 + s2;
        return(thirdPartSum);
      }

			//Add every term within the same pmode into pmodeSum
			pmodeSum += thirdTerms;
		}
      
    thirdPartSum += pmodeSum;
  	error = cabs(pmodeSum) / cabs(thirdPartSum);  
		if(verbose)
			printf("pmode=%d error: %.8f\n\n",pmodeSqur , error);
	}
      
  *rstatus = s1 + s2;
  //printf("qSqur=%.4f,  thirdPartSum=%.24lf %+.24lfI.\n", qSqur, creal(thirdPartSum),cimag(thirdPartSum));
  return thirdPartSum;
}

				








	
