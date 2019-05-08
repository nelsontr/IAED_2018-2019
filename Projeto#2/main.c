/*
 * File:  main.c
 * Author:  Nelson Trindade
 * IST Number: 93743
 * Description: To be decide...
*/

#include "functions.h"

int main(){
  char name[MAX_NAME],email[MAX_EMAIL],phone[MAX_PHONE];
  while (1){
    strcpy(name,""); strcpy(email,""); strcpy(phone,"");
    command=getchar();
    switch(command){
      case 'a': /*Add a Contact*/
        scanf(" %s %s %s\n",name,email,phone);
        head = add_contact(head,name,email,phone);
        break;
      case 'l': /*Displays all contacts by order of creation*/
        list_contact(head);
        break;
      case 'p': /*Searches Contact*/
        search_contact();
        break;
      case 'r': /*Removes a Contact*/
        delete_contact();
        break;
      case 'e': /*Changes the email of a Contact*/
        change_email();
        break;
      case 'c': /*How many contacts as the same email*/
        search_email();
        break;
      case 'x': /*Exits the Program*/
        exit(0);
        break;
    }
  }
  return 0;
}
