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



/*MAIN PROGRAM*/
int main(){
  char name[MAX_NAME],email[MAX_EMAIL],phone[MAX_PHONE];
  inicialize();
  while (1){
    switch(getchar()){
      case 'a':
        scanf(" %s %s %s",name,email,phone);
        command_a(name,email,phone);
        break;
      case 'l':
        list_contact();
        break;
      case 'p':
        scanf(" %s",name);
        command_p(name);
        break;
      case 'r':
        scanf(" %s",name);
        command_r(name);
        break;
      case 'e':
        scanf(" %s %s",name,email);
        command_e(name,email);
        break;
      case 'c':
        scanf(" %s",email);
        command_c(email);
        break;
      case 'x':
        command_x();
        exit(0);
        break;
    }
  }
  return 0;
}
