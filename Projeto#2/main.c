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

/*----MAIN PROGRAM----*/
int main(){
  while (1){
    input_work();
    switch(command){
      case 'a': /*Add a Contact*/
        add_contact();
        break;
      case 'l': /*Displays all contacts by order of creation*/
        list_contact();
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
