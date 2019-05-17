/*
 * File:  main.c
 * Author:  Nelson Trindade
 * IST Number: 93743
 * Description: To be decide...
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void inicialize(){
  int i=0;
  for (i=0;i<TABLESIZE;i++){
    hashtable[i]=NULL;
    domain[i]=NULL;
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
    decrease_c(pos->node->contact->domain);
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
    decrease_c(pos->node->contact->domain);
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
