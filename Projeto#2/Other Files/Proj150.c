/*
 * File:  main.c
 * Author:  Nelson Trindade
 * IST Number: 93743
 * Description: Code for a Contact list. It uses linked lists, Hashtables for
    searching contacts and other for domains.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*_______________/----- CONTACTS -----\_______________*/
#define MAX_NAME 1024
#define MAX_EMAIL 512  /*Bowth for email and domain*/
#define MAX_PHONE 64
#define TABLESIZE 1031  /*For Hashtable to search_hash and Domain List*/

/*_______________/----- STRUCTURS -----\_______________*/
typedef struct cont{
  char *name, *email, *domain, *phone;
} *contacts;

typedef struct node{
  contacts contact;
  struct node *next,*prev;
} *link;

typedef struct Hash{
  link node;
  struct Hash *next,*prev;
} *hash;

typedef struct email{
  char *domain;
  int count;
  struct email *next,*prev;
} *Counter_domain;

/* GLOBAL VARIABLES */
link head=NULL, last = NULL; /*Principal List, a.k.a. Linked list*/
hash hashtable[TABLESIZE];  /*For searching reasons*/
Counter_domain domain[TABLESIZE];  /*For giving the number of domains*/


/*_______________/----- FUNCTIONS -----\_______________*/
/*Initializes all HashTables with NULL*/
void Initializes(){
  int i=0;
  for (i=0;i<TABLESIZE;i++)
    hashtable[i]=NULL, domain[i]=NULL;
}

/*Allocs the only the memory necessary.*/
char* input(char buffer[]){
  char *x = malloc(sizeof(char) * (strlen(buffer)+1));
  strcpy(x,buffer);
  return x;
}

/*Returns a code by inserting a string.
It is used to make the HashTable more efficient*/
int hashcode(char *v){
  int h, a = 31415, b = 27183, M=TABLESIZE;
  for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
  h = (a*h + *v) % M;
  return h;
}


/*_______________/----- DOMAIN FUNCTIONS -----\_______________*/
/*It searches in the HashTable designed to search domains*/
Counter_domain search_domain(int i,char name_a[]){
  Counter_domain current = domain[i];
  while (current != NULL){
    if (strcmp(current->domain, name_a)==0)
      return current;
    current = current->next;
  }
  return NULL;
}

/*It creates and returns a domain*/
Counter_domain create_domain(char domain[]){
  Counter_domain aux=malloc(sizeof(struct email));
  aux->domain=input(domain);
  aux->count=1;
  aux->next=NULL;
  aux->prev=NULL;
  return aux;
}

/*Allocs a domain, witch means that it chooses were to create or were
to add 1 to the counter a domain*/
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
      aux->count++;
  }
}

/*It finds the domain by giving a name and decreases one value to the count*/
void decrease_domain(char domain[]){
  int i=hashcode(domain);
  Counter_domain aux=search_domain(i,domain);
  aux->count--;
}


/*_______________/----- CONTACT FUNCTIONS -----\_______________*/
/*Function that creates and returns a contact. Besides that, increases the counter
of domain existing*/
contacts create_contact(char name[], char email[], char phone[]){
  int i=0;
  char *token;
  contacts contact_aux = malloc(sizeof(struct cont));

  contact_aux->name = input(name);
  token = strtok(email, "@");   /*Strtok to separate email and domain*/
  contact_aux->email = input(token);
  token = strtok(NULL, "\0");
  contact_aux->domain = input(token);
  i=hashcode(contact_aux->domain);
  /*Step needed to know the local were the domain needs to update*/
  alloc_domain(i,contact_aux->domain);
  contact_aux->phone = input(phone);
  return contact_aux;
}


/*_________/----- HASH AND LINKED LIST FUNCTIONS -----\_________*/
/*Creates and returns a node. Also creates a contact that is asocciated with the node*/
link create_node(char name[], char email[], char phone[]){
  link x = malloc(sizeof(struct node));
  x->contact = create_contact(name,email,phone);
  x->next = NULL;
  x->prev = NULL;
  return x;
}

/*Function that puts the last node created in the last position of the principal list*/
void alloc_node(link x){
  if (head==NULL)
    head=x, last=head;
  else{
    last->next = x;
    x->prev = last;
    last=x;
  }
}

/*Function that searches what hash is the one that I'm looking for*/
hash search_hash(int i, char name_a[]){
  hash current = hashtable[i];
  while (current != NULL){
    if (strcmp(current->node->contact->name, name_a)==0)
      return current;
    current = current->next;
  }
  return NULL;
}
/*Creates and returns a new hash with node associated to it*/
hash create_hash(link node){
  hash x = malloc(sizeof(struct Hash));
  x->node = node;
  x->next = NULL;
  x->prev = NULL;
  return x;
}

/*Allocs memory to guard a new hash, associating with node*/
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
/*Prints a contact given*/
void print_contact(contacts t){
  printf("%s %s@%s %s\n", t->name, t->email, t->domain, t->phone);
}

/*Prints all contacts in the principal list*/
void list_contact(){
  link t;
  for (t=head;t!=NULL; t=t->next)
    print_contact(t->contact);
}

/*It changes a email of a contact given to a new email*/
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
/*Function that free all the variables of contact and the contact it selfS*/
void clean(link current){
  free(current->contact->name);
  free(current->contact->email);
  free(current->contact->domain);
  free(current->contact->phone);
  free(current->contact);
  free(current);
}

/*Function that free all nodes in the linked list. It calls the clean funct.*/
void freeNODE(){
  link next, current = head;
  while (current != NULL){
    next = current->next;
    clean(current);
    current = next;
  }
  head = NULL;
}

/*Function that free all Doman HashTable*/
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

/*Function that free all Search HashTable*/
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
/*Deletes a Node and all mallocs made in contatcs*/
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

/*Deletes a Hash*/
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

/*Function that adds a contact, by creating a node in */
void command_a(char name[], char email[], char phone[]){
  link node_aux=NULL;
  int i=hashcode(name);
  if (search_hash(i,name)==NULL){
    node_aux=create_node(name,email,phone);
    alloc_node(node_aux);
    alloc_hash(i,node_aux);
  }
  else
    puts("Nome existente.");
}

/*Searches and prints the contact by giving the name*/
void command_p(char name[]){
  int i=hashcode(name);
  hash pos=search_hash(i, name);

  if (pos!=NULL)
    print_contact(pos->node->contact);
  else
    puts("Nome inexistente.");
}

/*Removes a contact by givving a name*/
void command_r(char name[]){
  int i=hashcode(name);
  hash pos=search_hash(i, name);

  if (pos!=NULL){
    decrease_domain(pos->node->contact->domain);
    deleteNode(pos->node);
    deleteHASH(i,pos);
  }
  else
    puts("Nome inexistente.");
}

/*Changes the email of a contact, by givving a name and the new email*/
void command_e(char name[],char email[]){
  int i=hashcode(name);
  hash pos=search_hash(i, name);

  if (pos!=NULL){
    decrease_domain(pos->node->contact->domain);
    change_email(pos->node->contact,email);
  }
  else
    puts("Nome inexistente.");
}

/*Shows how many domains exists in the list*/
void command_c(char email[]){
  int i=hashcode(email);
  Counter_domain aux=search_domain(i,email);
  if (aux!=NULL)
    printf("%s:%d\n",aux->domain,aux->count);
  else
    printf("%s:%d\n",email,0);
}

/*Exits the program and give free's to every malloc giveen*/
void command_x(){
  int i=0;
  freeNODE();
  for (i=0;i<TABLESIZE;i++){
    freeHASH(i);
    freeDOM(i);
  }
}


int main(){
  char name[MAX_NAME],email[MAX_EMAIL],phone[MAX_PHONE];
  Initializes();
  while (1){
    switch(getchar()){
      case 'a':  /*ADDS CONTACT*/
        scanf(" %s %s %s",name,email,phone);
        command_a(name,email,phone);
        break;
      case 'l':  /*lIST ALL CONTACTS*/
        list_contact();
        break;
      case 'p':  /*SEARCHES A CONTACT*/
        scanf(" %s",name);
        command_p(name);
        break;
      case 'r':  /*REMOVES A CONTACT*/
        scanf(" %s",name);
        command_r(name);
        break;
      case 'e':  /*CHANGES EMAIL OF A CONTACT*/
        scanf(" %s %s",name,email);
        command_e(name,email);
        break;
      case 'c':  /*PRINTS THE NUMBER OF THE DOMAIN GIVEN*/
        scanf(" %s",email);
        command_c(email);
        break;
      case 'x':  /*EXITS PROGRAM*/
        command_x();
        exit(0);
        break;
    }
  }
  return 0;
}
