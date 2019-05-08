#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*CONSTANTS*/
#define MAX_NAME 1024
#define MAX_EMAIL 512
#define MAX_PHONE 64

/*Structurs*/
typedef struct{
  char *name, *email, *phone;
} *contacts;

typedef struct node{
  contacts contact;   /*VERIFICAR SE E' NECESSARIO COLOCAR POINTER*/
  struct node *next;
} *link;

char* input(char buffer[]){
  char *x = (char*) malloc(sizeof(char) * (strlen(buffer)+1));
  strcpy(x,buffer);
  return x;
}

link add_contact(link head, char name[], char email[], char phone[]){
  contacts contact_aux = malloc(sizeof(contacts));
  link y, x = malloc(sizeof(struct node));
  contact_aux->name = input(name);
  contact_aux->email = input(email);
  contact_aux->phone = input(phone);


  x->contact = contact_aux;
  x->next = NULL;

/* ADD TO THE END */
  if (head==NULL)
    return x;
  for (y=head; y->next != NULL; y = y->next);
  y->next = x;
  return head;
}

void list_contact(link head){
  link t;
  for (t=head;t!=NULL; t=t->next)
    printf("%s %s %s\n", t->contact->name,t->contact->email,t->contact->phone);
}
