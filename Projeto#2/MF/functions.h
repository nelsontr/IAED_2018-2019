#ifndef FUNCTIONS
#define FUNCTIONS

/* CONSTANTS */
#define MAX_NAME 1024
#define MAX_EMAIL 512
#define MAX_PHONE 64
#define TABLESIZE 1031

/* STRUCTURS */
typedef struct Contact *contacts;
typedef struct node *link;
typedef struct Hash *hash;
typedef struct email *Count_email;


/*--------Functions--------*/
char* input(char buffer[]);
contacts create_contact(char name[], char email[], char phone[]);
link create_node( char name[], char email[], char phone[]);
int hashcode(char *v,int M);
hash create_hash(link node);
hash alloc_hash(hash head, link node);
void print_contact(contacts t);
hash search(hash head, char name_a[]);
link alloc_node(link head, link x);
void change_email(contacts aux,char email[]);
int how_many_domains(link t,char domain[]);
link deleteNode(link head_ref, link del);
hash deleteHASH(hash head_ref, hash del);
void clean(link current);
void freeNODE(link head);
void freeHASH(hash head);

#endif
