/*
 * File:  functions.c
 * Author:  Nelson Trindade
 * IST Number: 93743
 * Description: Functions used in main.c and main_functions.c
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"
#include "main_functions.h"

/*___________/----- GLOBAL VARIABLES -----\___________*/
link head=NULL, last = NULL; /*Principal List, a.k.a. Linked list to contacts*/
hash hashtable[TABLESIZE];  /*For searching reasons*/
Counter_domain domain[TABLESIZE];  /*For giving the number of domains*/


/*_______________/----- FUNCTIONS -----\_______________*/
/* Initializes both hashtables with NULL value */
void Initializes(){
  int i=0;
  for (;i<TABLESIZE;i++)
    hashtable[i]=NULL, domain[i]=NULL;
}

/* Allocs only the memory necessary for a string. */
char* input(char buffer[]){
  char *x = malloc(sizeof(char) * (strlen(buffer)+1));
  strcpy(x,buffer);
  return x;
}

/* Returns a code by inserting a string.
It is used to make both hashtables more efficient */
int hashcode(char *str){
  int x=0, a=31415, b=27183, M=TABLESIZE;
  for (x = 0; *str != '\0'; str++, a = a*b % (M-1))
    x = (a*x + *str) % M;
  return x;
}


/*_______________/----- DOMAIN FUNCTIONS -----\_______________*/
/* It searches in the hashtable domains for the specific hashtable element*/
Counter_domain search_domain(int i,char name_a[]){
  Counter_domain current = domain[i];
  for(;current!=NULL;current=current->next)
    if (!strcmp(current->domain, name_a))
      return current;
  return NULL;
}

/* It creates and returns a domain */
Counter_domain create_domain(char domain[]){
  Counter_domain aux=malloc(sizeof(struct email));
  aux->domain=input(domain);
  aux->count=1;
  aux->next=NULL;
  aux->prev=NULL;
  return aux;
}

/* Allocs a domain, witch means that it chooses were to create or were
to add 1 to the counter of a domain */
void alloc_domain(int i,char domai[]){
  Counter_domain aux=NULL;
  if (domain[i]==NULL)  /* If it's the first element on the hashtable */
    domain[i]=create_domain(domai);
  else {
    aux=search_domain(i,domai);
    if (aux==NULL){ /* If it's not the first element, and there is not one
                    hashtable element for that domain */
      aux=create_domain(domai);
      domain[i]->prev = aux;
      aux->next=domain[i];
      aux->prev=NULL;
      domain[i]=aux;
    }
    else  /* If exists, and its not the first one, add 1 to counter */
      aux->count++;
  }
}

/* It finds the domain by giving a name and decreases one value of the count */
void decrease_domain(char domain_a[]){
  int i=hashcode(domain_a);
  Counter_domain aux=search_domain(i,domain_a);
  aux->count--;
}


/*_______________/----- CONTACT FUNCTIONS -----\_______________*/
/* Function that creates and returns a contact.
While doing it, calls function to alloc the domain. */
contacts create_contact(char name[], char email[], char phone[]){
  int i=0;
  char *token;
  contacts contact_aux = malloc(sizeof(struct cont));

  contact_aux->name = input(name);
  token = strtok(email, "@");   /* Strtok to separate email and domain */
  contact_aux->email = input(token);
  token = strtok(NULL, "\0");
  contact_aux->domain = input(token);
  i=hashcode(contact_aux->domain);
  /* Step needed to know the local were the domain needs to update */
  alloc_domain(i,contact_aux->domain);
  contact_aux->phone = input(phone);
  return contact_aux;
}


/*_________/----- HASH AND LINKED LIST FUNCTIONS -----\_________*/
/* Creates and returns a node.
Also creates a contact that is asocciated with the node */
link create_node(char name[], char email[], char phone[]){
  link x = malloc(sizeof(struct node));
  x->contact = create_contact(name,email,phone);
  x->next = NULL;
  x->prev = NULL;
  return x;
}

/* Function that puts the last node created in the last position
of the principal list */
void alloc_node(link x){
  if (head!=NULL){
    last->next = x;
    x->prev = last;
    last=x;
    return;
  }
  head=x, last=head;
}

/* Function that searches what element is the one that I'm looking for in hash */
hash search_hash(int i, char name_a[]){
  hash current = hashtable[i];
  for(;current!=NULL;current=current->next)
    if (!strcmp(current->node->contact->name, name_a))
      return current;
  return NULL;
}
/* Creates and returns a new hashtable element with node associated to it */
hash create_hash(link node){
  hash x = malloc(sizeof(struct Hash));
  x->node = node;
  x->next = NULL;
  x->prev = NULL;
  return x;
}

/* Allocs memory to guard a new hashtable element, associating with node */
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
/* Prints a contact that was given */
void print_contact(contacts t){
  printf("%s %s@%s %s\n", t->name, t->email, t->domain, t->phone);
}

/* Prints all contacts in the principal list (Linked list) */
void list_contact(){
  link t=head;
  for (;t!=NULL; t=t->next)
    print_contact(t->contact);
}

/* It changes a email of a contact to the new email given */
void change_email(contacts aux,char email[]){
  int i=0;
  char*token = strtok(email, "@");
  aux->email = realloc(aux->email,sizeof(char) * (strlen(token)+1));
  strcpy(aux->email,token);

  token = strtok(NULL, "\0");
  aux->domain = realloc(aux->domain,sizeof(char) * (strlen(token)+1));
  strcpy(aux->domain,token);

  i=hashcode(aux->domain);
  alloc_domain(i,aux->domain);
}


/*_______________/----- FREE FUNCTIONS -----\_______________*/
/* Function that free all the variables of contact and the node of the contact. */
void clean_node(link current){
  free(current->contact->name);
  free(current->contact->email);
  free(current->contact->domain);
  free(current->contact->phone);
  free(current->contact);
  free(current);
}

/* Function that free all nodes in the linked list. It calls the clean function */
void freeNODE(){
  link next, current = head;
  while (current != NULL){
    next = current->next;
    clean_node(current);
    current = next;
  }
  head = NULL;
}

/* Function that free a specific Domain */
void freeDOM(int i){
  Counter_domain next, current = domain[i];
  while (current != NULL){
    next = current->next;
    free(current->domain);
    free(current);
    current = next;
  }
  domain[i] = NULL;
}

/* Function that free a specific hashtable element */
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
/* Deletes a Node and all mallocs made in contatcs */
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
    clean_node(del);
  }
}

/* Deletes a Hash */
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
