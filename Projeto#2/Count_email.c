#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct email{
  char *domain;
  int count;
  struct email *next,*prev;
} *Count_email;

Count_email domain[10];

char* input(char buffer[]){
  char *x = malloc(sizeof(char) * (strlen(buffer)+1));
  strcpy(x,buffer);
  return x;
}

int hashcode(char *v,int M){
  int h, a = 31415, b = 27183;
  for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
  h = (a*h + *v) % M;
  return h;
}

Count_email search_domain(char name_a[]){
  int i=hashcode(name_a,10);
  Count_email current = domain[i];
  while (current != NULL){
    if (strcmp(current->domain, name_a)==0)
      return current;
    current = current->next;
  }
  return NULL;
}

Count_email create_domain(char domai[]){
  Count_email aux=malloc(sizeof(struct email));
  aux->domain=input(domai);
  aux->count=1;
  aux->next=NULL;
  aux->prev=NULL;
  return aux;
}

void alloc_domain(int i,char domai[]){
  Count_email aux=NULL;

  if (domain[i]==NULL)
    domain[i]=create_domain(domai);
  else {
    aux=search_domain(domai);
    if (aux==NULL){
      aux=create_domain(domai);
      domain[i]->prev = aux;
      aux->next=domain[i];
      aux->prev=NULL;
      domain[i]=aux;
    }
    else
      aux->count+=1;
  }
}

int main() {
  int i=0;
  Count_email aux=NULL;
  alloc_domain(9,"google.com");
  alloc_domain(9,"google.com");
  alloc_domain(9,"hash.com");
  aux=search_domain("google.com");
  printf("%s:%d\n",aux->domain,aux->count);
  return 0;
}
