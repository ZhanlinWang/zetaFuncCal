#include <stdio.h>
#include <string.h>

int read_i(char *src,int *data)
{
	char checkname[60];
	scanf("%s %d",checkname,data);
	if(!strcmp(checkname,src)){
		printf("%-40.40s%d\n",checkname,*data);
		return 1;
	}
	else
		return 0;
	}

int read_a(char *src,int *data)
{
	char checkname[60];
	scanf("%s %d %d %d",checkname,data, data+1, data+2);
	if(!strcmp(checkname,src)){
		printf("%-40.40s%d %d %d \n",checkname,*data,*(data+1), *(data+2));
		return 1;
	}
	else
		return 0;
	}

int read_d(char *src,double *data)
{
	char checkname[60];
	scanf("%s %lf",checkname,data);
	if(!strcmp(checkname,src)){
		printf("%-40.40s %lf\n",checkname,*data);
		return 1;
	}
	else
		return 0;
	}

