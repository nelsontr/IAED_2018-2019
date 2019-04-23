#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 81

int main(){
  int i=0;
  char *str=malloc(sizeof(char)*MAX_LINE);

  fgets(str,MAX_LINE,stdin);
  for(i = 0;*(str+i)!='\0'; ++i)
        printf("%s\n",(str+i));
  free(str);
  return 0;
}
