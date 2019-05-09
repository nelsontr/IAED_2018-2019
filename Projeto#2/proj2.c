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
typedef struct cont{
  char *name, *email, *domain, *phone;
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

contacts create_contact(char name[], char email[], char phone[]){
  contacts contact_aux = malloc(sizeof(struct cont));
  char *token;
  contact_aux->name = malloc(sizeof(char) * (strlen(name)+1));
  strcpy(contact_aux->name,name);

  token = strtok(email, "@");
  contact_aux->email = malloc(sizeof(char) * (strlen(token)+1));
  strcpy(contact_aux->email,token);

  token = strtok(NULL, "\0");
  contact_aux->domain = malloc(sizeof(char) * (strlen(token)+1));
  strcpy(contact_aux->domain,token);

  contact_aux->phone = malloc(sizeof(char) * (strlen(phone)+1));
  strcpy(contact_aux->phone,phone);

  return contact_aux;
}


link add_contact(link head, char name[], char email[], char phone[]){
  link y, x = malloc(sizeof(struct node));
    x->contact=create_contact(name,email,phone);
    x->next = NULL;

/* ADD TO THE END */
  if (head==NULL)
    return x;
  for (y=head; y->next != NULL; y = y->next);
  y->next = x;
  return head;
}

void clean(link current){
  free(current->contact->name);
  free(current->contact->email);
  free(current->contact->domain);
  free(current->contact->phone);
  free(current->contact);
  free(current);
}

void freeNODE(link head){
  link next, current = head;
  while (current != NULL){
       next = current->next;
       clean(current);
       current = next;
   }
   head = NULL;
}

void print_contact(contacts t){
  printf("%s %s@%s %s\n", t->name, t->email, t->domain, t->phone);
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
  for(t=head, prev = NULL;t!=NULL;prev=t,t=t->next){
    if(strcmp(t->contact->name, aux->name) == 0){
      if(t==head)
        head =t->next;
      else
        prev->next=t->next;
      clean(t);
      return head;
    }
  }
  return head;
}

void change_email(contacts aux,char email[]){
  char*token = strtok(email, "@");
  aux->email = realloc(aux->email,sizeof(char) * (strlen(token)+1));
  strcpy(aux->email,token);

  token = strtok(NULL, "\0");
  aux->domain = realloc(aux->domain,sizeof(char) * (strlen(token)+1));
  strcpy(aux->domain,token);
}

int how_many_domains(link t,char domain[]){
  if (t==NULL)
    return 0;
  else if (strcmp(t->contact->domain,domain)==0)
    return 1+how_many_domains(t->next,domain);
  else
    return how_many_domains(t->next,domain);
}

int main(){
  link head=NULL;
  contacts contact_aux=NULL;
  char name[MAX_NAME],email[MAX_EMAIL],phone[MAX_PHONE];
  while (1){
    strcpy(name,""); strcpy(email,""); strcpy(phone,"");
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
        contact_aux = search(head,name);
        if (search(head,name)!=NULL)
          head=delete(head,contact_aux);
        else
          puts("Nome inexistente.");
        break;
      case 'e':
        scanf(" %s %s",name,email);
        contact_aux = search(head,name);
        if (search(head,name)!=NULL)
          change_email(contact_aux,email);
        else
          puts("Nome inexistente.");
        break;
      case 'c':
        scanf(" %s",email);
        printf("%s:%d\n",email,how_many_domains(head,email));
        break;
      case 'x': /*Exits the Program*/
        freeNODE(head);
        exit(0);
        break;
    }
  }
  return 0;
}
