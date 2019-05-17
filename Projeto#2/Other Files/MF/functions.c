#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

/*_______________/----- FUNCTIONS -----\_______________*/
char* input(char buffer[]){
  char *x = malloc(sizeof(char) * (strlen(buffer)+1));
  strcpy(x,buffer);
  return x;
}

int hashcode(char *v){
  int h, a = 31415, b = 27183, M = TABLESIZE;
  for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
    h = (a*h + *v) % M;
  return h;
}


/*_______________/----- CONTACT FUNCTIONS -----\_______________*/
contacts create_contact(char name[], char email[], char phone[]){
  int i=0;
  char *token;
  contacts contact_aux = malloc(sizeof(struct cont));
  contact_aux->name = input(name);
  token = strtok(email, "@");
  contact_aux->email = input(token);
  token = strtok(NULL, "\0");
  contact_aux->domain = input(token);
  i=hashcode(contact_aux->domain);
  alloc_domain(i,contact_aux->domain);
  contact_aux->phone = input(phone);
  return contact_aux;
}


/*_______________/----- DOMAIN FUNCTIONS -----\_______________*/
Counter_domain search_domain(int i,char name_a[]){
  Counter_domain current = domain[i];
  while (current != NULL){
    if (strcmp(current->domain, name_a)==0)
      return current;
    current = current->next;
  }
  return NULL;
}

Counter_domain create_domain(char domain[]){
  Counter_domain aux=malloc(sizeof(struct email));
  aux->domain = input(domain);
  aux->count = 1;
  aux->next = NULL;
  aux->prev = NULL;
  return aux;
}

void alloc_domain(int i,char domai[]){
  Counter_domain aux=NULL;

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
  int i=hashcode(domain);
  Counter_domain aux=search_domain(i,domain);
  aux->count--;
}


/*_________/----- HASH AND LINKED LIST FUNCTIONS -----\_________*/
link create_node(char name[], char email[], char phone[]){
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

hash search_hash(int i, char name_a[]){
  hash current = hashtable[i];
  while (current != NULL){
    if (strcmp(current->node->contact->name, name_a)==0)
      return current;
    current = current->next;
  }
  return NULL;
}

hash create_hash(link node){
  hash x = malloc(sizeof(struct Hash));
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


/*_______________/----- OTHER FUNCTIONS -----\_______________*/
void print_contact(contacts t){
  printf("%s %s@%s %s\n", t->name, t->email, t->domain, t->phone);
}

void list_contact(){
  link t;
  for (t=head;t!=NULL; t=t->next)
    print_contact(t->contact);
}

void change_email(contacts aux,char email[]){
  char*token = strtok(email, "@");
  int i=0;
  aux->email = realloc(aux->email,sizeof(char) * (strlen(token)+1));
  strcpy(aux->email,token);

  token = strtok(NULL, "\0");
  aux->domain = realloc(aux->domain,sizeof(char) * (strlen(token)+1));
  strcpy(aux->domain,token);
  i=hashcode(aux->domain);
  alloc_domain(i,aux->domain);
}


/*_______________/----- FREE FUNCTIONS -----\_______________*/
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

void freeDOM(int i){
  Counter_domain next, current = domain[i];
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


/*_______________/----- Remove FUNCTIONS -----\_______________*/
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
