#include <stdio.h>
#include <string.h>

int read_i(char *src,int *data)
{
  char checkname[60];
  int err;
  err = scanf("%s %d",checkname,data);
  if(!strcmp(checkname,src)){
    printf("%-40.40s%d\n",checkname,*data);
    return 1;
  }
  else
    return 0;
}

int read_a(char *src,double *data)
{
  char checkname[60];
  int err;
  err = scanf("%s %lf %lf %lf",checkname,data, data+1, data+2);
  if(!strcmp(checkname,src)){
    printf("%-40.40s%.2lf %.2lf %.2lf \n",checkname,*data,*(data+1), *(data+2));
    return 1;
  }
  else
    return 0;
}

int read_d(char *src,double *data)
{
  char checkname[60];
  int err;
  err = scanf("%s %lf",checkname,data);
  if(!strcmp(checkname,src)){
    printf("%-40.40s%le\n",checkname,*data);
    return 1;
  }
  else
    return 0;
}

