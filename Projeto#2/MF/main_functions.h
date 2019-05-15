#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H

/* CONSTANTS */
#define MAX_NAME 1024
#define MAX_EMAIL 512
#define MAX_PHONE 64
#define TABLESIZE 1031

/* GLOBAL VARIABLES */
link head=NULL, last = NULL;
hash hashtable[TABLESIZE];
Counter_domain domain[TABLESIZE];

/*prototips*/
void inicialize();
void command_a(char name[], char email[], char phone[]);
void command_p(char name[]);
void command_r(char name[]);
void command_e(char name[],char email[]);
void command_c(char email[]);
void command_x();
#endif
