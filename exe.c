#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int end_hour(int hour, int dura){

    int  min=(hour%100+dura%60), hours=(hour/100)+(dura/60)+min/60;
    return hours*100+min%60;
}

int main(){

  int a,d;
  scanf("%d",&a);
  scanf("%d",&d);

  printf("%d\n",end_hour(a,d));
  return 0;
}
