#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int gen_points_array(int * degnrtDOF, int * arrayPmode, int _NPmode, int _DimMAX)
{	
	for(int pmodeSqur = 0; pmodeSqur < _NPmode; pmodeSqur++){
		int r = (int)(floor(sqrt(pmodeSqur)));
		int	num = 0;

		for(int x=-r; x<=r; x++)
			for(int y=-r; y<=r; y++)
				for(int z=-r; z<=r; z++){

					if(x*x+y*y+z*z == pmodeSqur){
						arrayPmode[pmodeSqur*_DimMAX*3 + num*3 + 0] = x;
						arrayPmode[pmodeSqur*_DimMAX*3 + num*3 + 1] = y;
						arrayPmode[pmodeSqur*_DimMAX*3 + num*3 + 2] = z;

						num = num + 1;
					}
		}

		//degnrtDOF also record those pmodeSqur without any
		//corresponding points, in which case num = 0;
		degnrtDOF[pmodeSqur] = num;
	}
	return 0;
}

/*
void Array_Alloc(int * arrayPoints, int npmode, int dimmax, int innerdim)
{
	printf("The volume of the array is %d.\n", npmode*dimmax*innerdim);
	if((arrayPoints = (int *)malloc(npmode*dimmax*innerdim*sizeof(int))) == NULL)
		{
			printf("Error: void Array_alloc(...\n");
			exit(-1);
		}
}
*/

void Array_Free(int * arrayPoints)
{
	if(arrayPoints == NULL)
		{
			printf("Error: free_alloc(...");
			exit(-1);
		}
	free(arrayPoints);
	arrayPoints = NULL;
}



