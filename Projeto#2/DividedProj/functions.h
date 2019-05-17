#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/*_______________/----- CONSTANTS -----\_______________*/
#define MAX_NAME 1024
#define MAX_EMAIL 512  /*Bowth for email and domain*/
#define MAX_PHONE 64
#define TABLESIZE 1031  /*For Hashtable to search_hash and Domain List*/

/*_______________/----- STRUCTURES -----\_______________*/
typedef struct cont{
  char *name, *email, *domain, *phone;
} *contacts;

typedef struct node{
  contacts contact;
  struct node *next,*prev;
} *link;

typedef struct Hash{
  link node;
  struct Hash *next,*prev;
} *hash;

typedef struct email{
  char *domain;
  int count;
  struct email *next,*prev;
} *Counter_domain;


/*_______________/----- PROTOTYPES -----\_______________*/
void Initializes();
char* input(char buffer[]);
int hashcode(char *v);
Counter_domain search_domain(int i,char name_a[]);
Counter_domain create_domain(char domain[]);
void alloc_domain(int i,char domai[]);
void decrease_domain(char domain[]);
contacts create_contact(char name[], char email[], char phone[]);
link create_node(char name[], char email[], char phone[]);
void alloc_node(link x);
hash search_hash(int i, char name_a[]);
hash create_hash(link node);
void alloc_hash(int i, link node);
void print_contact(contacts t);
void list_contact();
void change_email(contacts aux,char email[]);
void clean_node(link current);
void freeNODE();
void freeDOM(int i);
void freeHASH(int i);
void deleteNode(link del);
void deleteHASH(int i, hash del);

#endif
