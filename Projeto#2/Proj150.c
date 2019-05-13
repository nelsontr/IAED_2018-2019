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
#define TABLESIZE 1031

/* STRUCTURS */
typedef struct cont{
  char *name, *email, *domain, *phone;
} *contacts;

typedef struct node{
  contacts contact;
  struct node *next,*prev;
} *link;

typedef struct node2{
  link node;
  struct node2 *next,*prev;
} *hash;

typedef struct email{
  char *domain;
  int count;
  struct email *next,*prev;
} *Count_email;

/* GLOBAL VARIABLES */
link head=NULL, last = NULL;
hash hashtable[TABLESIZE];
Count_email domain[TABLESIZE];

/* FUNCTIONS */
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

Count_email search_domain(int i,char name_a[]){
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
    aux=search_domain(i,domai);
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

void decrease_c(char domain[]){
  int i=hashcode(domain,TABLESIZE);
  Count_email aux=search_domain(i,domain);
  aux->count-=1;
}


contacts create_contact(char name[], char email[], char phone[]){
  contacts contact_aux = malloc(sizeof(struct cont));
  char *token;
  int i=0;
  contact_aux->name = input(name);
  token = strtok(email, "@");
  contact_aux->email = input(token);
  token = strtok(NULL, "\0");
  contact_aux->domain = input(token);
  i=hashcode(contact_aux->domain,TABLESIZE);
  alloc_domain(i,contact_aux->domain);
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

void alloc_node(link x){
  if (head==NULL)
    head=x, last=head;
  else{
    last->next = x;
    x->prev = last;
    last=x;
  }
}

hash create_hash(link node){
  hash x = malloc(sizeof(struct node2));
  x->node = node;
  x->next = NULL;
  x->prev = NULL;
  return x;
}

void alloc_hash(int i, link node){
  hash x=create_hash(node);
  if (hashtable[i]==NULL)
    hashtable[i]=x;
  else{
    hashtable[i]->prev = x;
    x->next=hashtable[i];
    x->prev=NULL;
    hashtable[i]=x;
  }
}

void print_contact(contacts t){
  printf("%s %s@%s %s\n", t->name, t->email, t->domain, t->phone);
}

void list_contact(){
  link t;
  for (t=head;t!=NULL; t=t->next)
    print_contact(t->contact);
}

hash search(int i, char name_a[]){
  hash current = hashtable[i];
  while (current != NULL){
    if (strcmp(current->node->contact->name, name_a)==0)
      return current;
    current = current->next;
  }
  return NULL;
}

void change_email(contacts aux,char email[]){
  char*token = strtok(email, "@");
  int i=0;
  aux->email = realloc(aux->email,sizeof(char) * (strlen(token)+1));
  strcpy(aux->email,token);

  token = strtok(NULL, "\0");
  aux->domain = realloc(aux->domain,sizeof(char) * (strlen(token)+1));
  strcpy(aux->domain,token);
  i=hashcode(aux->domain,TABLESIZE);
  alloc_domain(i,aux->domain);
}

void clean(link current){
  free(current->contact->name);
  free(current->contact->email);
  free(current->contact->domain);
  free(current->contact->phone);
  free(current->contact);
  free(current);
}

void freeNODE(){
  link next, current = head;
  while (current != NULL){
    next = current->next;
    clean(current);
    current = next;
  }
  head = NULL;
}

void deleteNode(link del){
  if (head != NULL || del != NULL){
    if (head == del)
      head = del->next;
    if (del->next != NULL)
      del->next->prev = del->prev;
    else
      last=del->prev;
    if (del->prev != NULL)
      del->prev->next = del->next;
    clean(del);
  }
}

void deleteHASH(int i, hash del){
  if (hashtable[i] != NULL || del != NULL){
    if (hashtable[i] == del)
      hashtable[i] = del->next;
    if (del->next != NULL)
      del->next->prev = del->prev;
    if (del->prev != NULL)
      del->prev->next = del->next;
    free(del);
  }
}

void freeDOM(int i){
  Count_email next, current = domain[i];
  while (current != NULL){
    next = current->next;
    free(current->domain);
    free(current);
    current = next;
  }
  hashtable[i] = NULL;
}

void freeHASH(int i){
  hash next, current = hashtable[i];
  while (current != NULL){
    next = current->next;
    free(current);
    current = next;
  }
  hashtable[i] = NULL;
}

int main(){
  int i=0;
  link node_aux=NULL;
  hash pos=NULL;
  char name[MAX_NAME],email[MAX_EMAIL],phone[MAX_PHONE];
  Count_email aux=NULL;
  for (i=0;i<TABLESIZE;i++){
    hashtable[i]=NULL;
    domain[i]=NULL;
  }

  while (1){
    strcpy(name,""); strcpy(email,""); strcpy(phone,"");
    switch(getchar()){
      case 'a': /*Add a Contact*/
        scanf(" %s %s %s",name,email,phone);
        i=hashcode(name,TABLESIZE);
        if (search(i,name)==NULL){
          node_aux=create_node(name,email,phone);
          alloc_node(node_aux);
          alloc_hash(i,node_aux);
        }
        else
          puts("Nome existente.");
        break;
      case 'l': /*Displays all contacts by order of creation*/
        list_contact();
        break;
      case 'p':
        scanf(" %s",name);
        i=hashcode(name,TABLESIZE);
        pos=search(i, name);
        if (pos!=NULL)
          print_contact(pos->node->contact);
        else
          puts("Nome inexistente.");
        break;
      case 'r':
        scanf(" %s",name);
        i=hashcode(name,TABLESIZE);
        pos=search(i, name);
        if (pos!=NULL){
          decrease_c(pos->node->contact->domain);
          deleteNode(pos->node);
          deleteHASH(i,pos);
        }
        else
          puts("Nome inexistente.");
        break;
      case 'e':
        scanf(" %s %s",name,email);
        i=hashcode(name,TABLESIZE);
        pos=search(i, name);
        if (pos!=NULL){
          decrease_c(pos->node->contact->domain);
          change_email(pos->node->contact,email);
        }
        else
          puts("Nome inexistente.");
        break;
      case 'c':
        scanf(" %s",email);
        i=hashcode(email,TABLESIZE);
        aux=search_domain(i,email);
        if (aux!=NULL)
          printf("%s:%d\n",aux->domain,aux->count);
        else
          printf("%s:%d\n",email,0);
        break;
      case 'x': /*Exits the Program*/
      freeNODE();
        for (i=0;i<TABLESIZE;i++){
          freeHASH(i);
        }
        for (i=0;i<TABLESIZE;i++){
          freeDOM(i);
        }
        exit(0);
        break;
    }
  }
  return 0;
}
