/*
 * File:  main_functions.c
 * Author:  Nelson Trindade
 * IST Number: 93743
 * Description: Principal functions used in the switch of main.c.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main_functions.h"
#include "functions.h"

/*_______________/----- MAIN FUNCTIONS -----\_______________*/

/* Function that adds a contact, by creating a node in the principal list
and on the hashtable */
void command_a(char name[], char email[], char phone[]){
  link node_aux = NULL;
  int i=hashcode(name);
  if (search_hash(i,name)==NULL){
    node_aux = create_node(name,email,phone);
    alloc_node(node_aux);
    alloc_hash(i,node_aux);
  }
  else
    puts("Nome existente.");
}

/* Prints all elements of the linked list */
void command_l(){
  list_contact();
}

/* Searches and prints the contact that is associated with the name given */
void command_p(char name[]){
  int i=hashcode(name);
  hash element=search_hash(i, name);
  if (element!=NULL)
    print_contact(element->node->contact);
  else
    puts("Nome inexistente.");
}

/* Removes the contact associated with the name given */
void command_r(char name[]){
  int i=hashcode(name);
  hash element=search_hash(i, name);
  if (element!=NULL){
    decrease_domain(element->node->contact->domain);
    deleteNode(element->node);
    deleteHASH(i,element);
  }
  else
    puts("Nome inexistente.");
}

/* Changes the email of a contact,
by giving the name of the contact and the new email  */
void command_e(char name[],char email[]){
  int i=hashcode(name);
  hash element=search_hash(i, name);
  if (element!=NULL){
    decrease_domain(element->node->contact->domain);
    change_email(element->node->contact,email);
  }
  else
    puts("Nome inexistente.");
}

/* Shows how many specific domains exists in the all contacts */
void command_c(char email[]){
  int i=hashcode(email);
  Counter_domain count_aux=search_domain(i,email);
  if (count_aux!=NULL)
    printf("%s:%d\n",count_aux->domain,count_aux->count);
  else
    printf("%s:%d\n",email,0);
}

/* Exits the program and give free's to every malloc made */
void command_x(){
  int i=0;
  freeNODE();
  for (;i<TABLESIZE;i++){
    freeHASH(i);
    freeDOM(i);
  }
}
