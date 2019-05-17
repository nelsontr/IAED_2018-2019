/*
 * File:  main.c
 * Author:  Nelson Trindade
 * IST Number: 93743
 * Description: To be decide...
*/
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

/* GLOBAL VARIABLE */
link head;

char* input(char buffer[]){
  char *x = (char*) malloc(sizeof(char) * (strlen(buffer)+1));
  strcpy(x,buffer);
  return x;
}

link add_contact(link head, char name[], char email[], char phone[]){
  contacts contact_aux = malloc(sizeof(contacts));
  link y, x = malloc(sizeof(link));
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

void print_contact(contacts t){
  printf("%s %s %s\n", t->name, t->email, t->phone);
}

void list_contact(link head){
  link t;
  for (t=head;t!=NULL; t=t->next)
    print_contact(t->contact);
}

contacts search(link head, char name_a[]){
  link current = head;
  while (current != NULL){
    if (strcmp(current->contact->name, name_a)==0){
      return current->contact;
    }
    current = current->next;
  }
  return NULL;
}


link delete(link head, contacts aux){
  link t,prev;
  for(t=head, prev = NULL;t->next!=NULL;prev=t,t=t->next){
    if(strcmp(t->contact->name, aux->name) == 0){
      if(t==head)
        head =t->next;
      else
        prev->next=t->next;
      free(t->next);
      free(t);
    }
  }
  return head;
}


int main(){
  contacts contact_aux;
  char name[MAX_NAME],email[MAX_EMAIL],phone[MAX_PHONE];
  while (1){
    strcpy(name,""); strcpy(email,""); strcpy(phone,"");
    contact_aux=NULL;
    switch(getchar()){
      case 'a': /*Add a Contact*/
        scanf(" %s %s %s",name,email,phone);
        if (search(head,name)==NULL)
          head=add_contact(head,name,email,phone);
        else
          puts("Nome existente.");
        break;
      case 'l': /*Displays all contacts by order of creation*/
        list_contact(head);
        break;
      case 'p':
        scanf(" %s",name);
        contact_aux=search(head, name);
        if (contact_aux!=NULL)
          print_contact(contact_aux);
        else
          puts("Nome inexistente.");
        break;
      case 'r':
        scanf(" %s",name);
        contact_aux = search(head, name);
        head=delete(head,contact_aux);
        break;
      case 'x': /*Exits the Program*/
        free(head);
        exit(0);
        break;
    }
  }
  return 0;
}
