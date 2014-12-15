#include <stdio.h>
#include <math.h>

int main(void)
{
	int pmode;

	FILE * wPointSets, *wUsefulPmode, * wNousePmode;

	wPointSets 		= fopen("./genDecartesianPointSets.txt","w");
	wUsefulPmode	= fopen("./genUsefulPmode.txt","w");
	wNousePmode	  = fopen("./genNousePmode.txt","w");


	for(pmode=0; pmode<=1000; pmode++){
		int r = (int)(floor(sqrt(pmode)));
		int num = 0;
		//fprintf(wPointSets,"pmode=%d:\n",pmode);
		for(int x=-r; x<=r; x++)
			for(int y=-r; y<=r; y++)
				for(int z=-r; z<=r; z++){
					if(x*x+y*y+z*z == pmode){
						fprintf(wPointSets,"%3d %3d %3d\n", x, y, z);
						num = num + 1;
					}
				}
		if(num == 0)
			fprintf(wNousePmode,"pmode=%d has no corresponding points.\n", pmode);
		else{
			fprintf(wUsefulPmode,"pmode=%d have %d degenaration DOF.\n", pmode, num);
			//fprintf(wPointSets,"pmode=%d have %d degenaration DOF.\n\n", pmode, num);
		}
	}
	fflush(wPointSets);
	fclose(wPointSets);
	fflush(wUsefulPmode);
	fclose(wUsefulPmode);
	fflush(wNousePmode);
	fclose(wNousePmode);
	return 0;
}



