#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*CONSTANTS*/
#define MAX_NAME 1024
#define MAX_EMAIL 512
#define MAX_PHONE 64



char* input(char buffer[]);

link add_contact(link head, char name[], char email[], char phone[]);

void list_contact(link head);
