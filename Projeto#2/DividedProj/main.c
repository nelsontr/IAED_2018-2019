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
#include "functions.h"


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
