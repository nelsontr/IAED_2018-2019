/*
 * File:  main.c
 * Author:  Nelson Trindade
 * IST Number: 93743
 * Description: To be decide...
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"


/*Global Variables*/
link last=NULL;


/*----MAIN PROGRAM----*/
int main(){
  int i=0;
  link head=NULL,node_aux=NULL;
  hash hashtable[TABLESIZE],pos=NULL;
  char name[MAX_NAME],email[MAX_EMAIL],phone[MAX_PHONE];

  for (i=0;i<TABLESIZE;i++)
    hashtable[i]=NULL;
  while (1){
    strcpy(name,""); strcpy(email,""); strcpy(phone,"");
    switch(getchar()){
      case 'a': /*Add a Contact*/
        scanf(" %s %s %s",name,email,phone);
        i=hashcode(name,TABLESIZE);
        if (search(hashtable[i],name)==NULL){
          node_aux=create_node(name,email,phone);
          head=alloc_node(head,node_aux);
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
        i=hashcode(name,TABLESIZE);
        pos=search(hashtable[i], name);
        if (pos!=NULL)
          print_contact(pos->node->contact);
        else
          puts("Nome inexistente.");
        break;
      case 'r':
        scanf(" %s",name);
        i=hashcode(name,TABLESIZE);
        pos=search(hashtable[i], name);
        if (pos!=NULL){
          head=deleteNode(head,pos->node);
          hashtable[i]=deleteHASH(hashtable[i],pos);
        }
        else
          puts("Nome inexistente.");
        break;
      case 'e':
        scanf(" %s %s",name,email);
        i=hashcode(name,TABLESIZE);
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
        for (i=0;i<TABLESIZE;i++)
          freeHASH(hashtable[i]);
        exit(0);
        break;
    }
  }
  return 0;
}
