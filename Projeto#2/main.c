/*
 * File:  main.c
 * Author:  Nelson Trindade
 * IST Number: 93743
 * Description: To be decide...
*/

#include "functions.h"


/* GLOBAL VARIABLE */
link head;


int main(){
  char command,name[MAX_NAME],email[MAX_EMAIL],phone[MAX_PHONE];
  while (1){
    strcpy(name,""); strcpy(email,""); strcpy(phone,"");
    command=getchar();
    switch(command){
      case 'a': /*Add a Contact*/
        scanf(" %s %s %s\n",name,email,phone);
        head=add_contact(head,name,email,phone);
        break;
      case 'l': /*Displays all contacts by order of creation*/
        list_contact(head);
        break;

      case 'x': /*Exits the Program*/
        free(head);
        exit(0);
        break;
    }
  }
  return 0;
}
