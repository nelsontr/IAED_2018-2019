#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*CONSTANTS*/
#define MAX_NAME 1024
#define MAX_EMAIL 512
#define MAX_PHONE 64

/*Structurs*/
typedef struct{
    char name[MAX_NAME], email[MAX_EMAIL], phone[MAX_PHONE];
} Contacts;

struct node{
  Contacts contact;
  struct node *next;
};




void add_contact(){

}

void list_contact(){

}

void search_contact(){

}

void delete_contact(){

}

void change_email(){

}

void search_email(){

}
