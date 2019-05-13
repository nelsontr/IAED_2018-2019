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
#define HASHTABLESIZE 1031
#define DOMAINTABLESIZE 1031

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

void alloc_node(link x){
  if (head==NULL)
    head=x, last=head;
  last->next = x;
  x->prev = last;
  last=x;
}

hash create_hash(link node){
  hash x = malloc(sizeof(struct node2));
  x->node = node;
  x->next = NULL;
  x->prev = NULL;
  return x;
}

hash alloc_hash(hash head, link node){
  hash x=create_hash(node);
  if (head==NULL){
    head=x;
    return head;
  }
  head->prev = x;
  x->next=head;
  x->prev=NULL;
  head=x;
  return head;
}

void print_contact(contacts t){
  printf("%s %s@%s %s\n", t->name, t->email, t->domain, t->phone);
}

void list_contact(link head){
  link t;
  for (t=head;t!=NULL; t=t->next)
    print_contact(t->contact);
}

hash search(hash head, char name_a[]){
  hash current = head;
  while (current != NULL){
    if (strcmp(current->node->contact->name, name_a)==0)
      return current;
    current = current->next;
    }
  return NULL;
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

hash deleteHASH(hash head_ref, hash del){
  if (head_ref == NULL || del == NULL)
    return head_ref;
  if (head_ref == del)
    head_ref = del->next;
  if (del->next != NULL)
    del->next->prev = del->prev;
  if (del->prev != NULL)
    del->prev->next = del->next;
  free(del);
  return head_ref;
}

void freeHASH(hash head){
  hash next, current = head;
  while (current != NULL){
     next = current->next;
     free(current);
     current = next;
   }
   head = NULL;
}

int main(){
  int i=0;
  link node_aux=NULL;
  hash hashtable[HASHTABLESIZE],pos=NULL;
  char name[MAX_NAME],email[MAX_EMAIL],phone[MAX_PHONE];
  for (i=0;i<HASHTABLESIZE;i++)
    hashtable[i]=NULL;

  while (1){
    strcpy(name,""); strcpy(email,""); strcpy(phone,"");
    switch(getchar()){
      case 'a': /*Add a Contact*/
        scanf(" %s %s %s",name,email,phone);
        i=hashcode(name,HASHTABLESIZE);
        if (search(hashtable[i],name)==NULL){
          node_aux=create_node(name,email,phone);
          alloc_node(node_aux);
          hashtable[i]=alloc_hash(hashtable[i],node_aux);
        }
        else
          puts("Nome existente.");
        break;
      case 'l': /*Displays all contacts by order of creation*/
        list_contact(head);
        break;
      case 'p':
        scanf(" %s",name);
        i=hashcode(name,HASHTABLESIZE);
        pos=search(hashtable[i], name);
        if (pos!=NULL)
          print_contact(pos->node->contact);
        else
          puts("Nome inexistente.");
        break;
      case 'r':
        scanf(" %s",name);
        i=hashcode(name,HASHTABLESIZE);
        pos=search(hashtable[i], name);
        if (pos!=NULL){
          deleteNode(pos->node);
          hashtable[i]=deleteHASH(hashtable[i],pos);
        }

        else
          puts("Nome inexistente.");
        break;
      case 'e':
        scanf(" %s %s",name,email);
        i=hashcode(name,HASHTABLESIZE);
        pos=search(hashtable[i], name);
        if (pos!=NULL)
          change_email(pos->node->contact,email);
        else
          puts("Nome inexistente.");
        break;
      case 'c':
        scanf(" %s",email);
        printf("%s:%d\n",email,how_many_domains(head,email));
        break;
      case 'x': /*Exits the Program*/
        freeNODE();
        for (i=0;i<HASHTABLESIZE;i++)
          freeHASH(hashtable[i]);
        exit(0);
        break;
    }
  }
  return 0;
}