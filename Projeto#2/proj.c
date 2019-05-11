/*
 * File:  main.c
 * Author:  Nelson Trindade
 * IST Number: 93743
 * Description: To be decide...
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* CONSTANTS */
#define MAX_NAME 1024
#define MAX_EMAIL 512
#define MAX_PHONE 64

/* STRUCTURS */
typedef struct cont{
  char *name, *email, *domain, *phone;
} *contacts;

typedef struct node{
  contacts contact;   /*VERIFICAR SE E' NECESSARIO COLOCAR POINTER*/
  struct node *next,*prev;
} *link;

typedef struct node2{
  link node;   /*VERIFICAR SE E' NECESSARIO COLOCAR POINTER*/
  struct node2 *next,*prev;
} *link2;


/* FUNCTIONS */
char* input(char buffer[]){
  char *x = malloc(sizeof(char) * (strlen(buffer)+1));
  strcpy(x,buffer);
  return x;
}

contacts create_contact(char name[], char email[], char phone[]){
  contacts contact_aux = malloc(sizeof(struct cont));
  char *token;

  contact_aux->name = input(name);
  token = strtok(email, "@");
  contact_aux->email = input(token);
  token = strtok(NULL, "\0");
  contact_aux->domain = input(token);
  contact_aux->phone = input(phone);
  return contact_aux;
}


link create_node( char name[], char email[], char phone[]){
  link x = malloc(sizeof(struct node));
  x->contact = create_contact(name,email,phone);
  x->next = NULL;
  x->prev = NULL;
  return x;
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

link search(link head, char name_a[]){
  link current = head;
  while (current != NULL){
    if (strcmp(current->contact->name, name_a)==0){
      return current;
    }
    current = current->next;
  }
  return NULL;
}

link alloc_node(link head, link x){
  link y;
  if (head==NULL){
    head=x;
    return head;}
  for (y=head; y->next != NULL; y = y->next);
  y->next = x;
  x->prev = y;
  return head;
}



link deleteNode(link head_ref, link del){
    if (head_ref == NULL || del == NULL)
        return head_ref;
    if (head_ref == del)
        head_ref = del->next;
    if (del->next != NULL)
        del->next->prev = del->prev;
    if (del->prev != NULL)
        del->prev->next = del->next;
    clean(del);
    return head_ref;
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

int hash(char *v,int M){
  int h, a = 31415, b = 27183;
  for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
    h = (a*h + *v) % M;
  return h;
}

int main(){
  int i;
  link head=NULL,pos;
  link2 list[10];
  char name[10],email[10],phone[10];
  for (i=0;i<10;i++) list[i]=NULL;
  strcpy(name,"Ok"); strcpy(email,"tre@dfg"); strcpy(phone,"986");
    i=hash(name,10);
    if(list[i]==NULL)
      list[i]=malloc(sizeof(struct node2));
      list[i]->Node->contact->name=NULL;
    if (search(list[i],name)==NULL){
      pos=create_node(name,email,phone);
      head=alloc_node(head,pos);
      list[i]->Node=pos;}

  strcpy(name,"Ok1"); strcpy(email,"lk@dfg"); strcpy(phone,"986");
    i=hash(name,10);
    if(list[i]==NULL)
      list[i]=malloc(sizeof(struct node2));
    if (search(list[i],name)==NULL){
      pos=create_node(name,email,phone);
      head=alloc_node(head,pos);
      list[1]->next=pos;
      list[i]->Node=pos;
      }
  pos=search(list[i],"Ok1");
  print_contact(pos->contact);
  list_contact(head);
  return 0;
}
