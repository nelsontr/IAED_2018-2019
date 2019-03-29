/*links to help: https://www.geeksforgeeks.org/taking-string-input-space-c-3-different-methods/ */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Constants*/
#define MAX_STR 63 /*Constant for string size*/
#define MAX_ROOMS 11 /*1 a 10*/
#define MAX_EVENTS 101 /*1 a 100*/
#define MAX_DATE 9 /*1 a 100*/
#define MAX_MEMBERS 3
#define MAX_INPUT_LINE 567 /*63*9*/

/*Structures*/
typedef struct {
    int begin,min,sala,count_members,date;
    char descripction[MAX_STR],responsable[MAX_STR],members[MAX_MEMBERS][MAX_STR];
} event;

/*Global Variables*/
int count_room[11]={0},count_event=0;
event eve[MAX_EVENTS*MAX_ROOMS];
char list[MAX_EVENTS*MAX_ROOMS][MAX_STR];

/*Functions*/
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void create_event(char str[]){
    int i=0;
    char *token;
    strcpy(eve[++count_event].descripction,strtok(str, ":"));
    eve[count_event].date = strtok(NULL, ":");
    eve[count_event].begin = atoi(strtok(NULL, ":"));
    eve[count_event].min = atoi(strtok(NULL, ":"));
    eve[count_event].sala = atoi(strtok(NULL, ":"));
    strcpy(eve[count_event].responsable,strtok(NULL, ":\n"));
    token=strtok(NULL, ":\n");
    while( token != NULL ) {   
        strcpy(eve[count_event].members[i++],token);
        token = strtok(NULL, ":\n");
    }
    eve[count_event].count_members=i; 
    sort(count_event);
}

void imprime_eve(char sala){
    int i;
    for (i=1;i<=count_event;i++)
        /*if (strcmp(eve[i].descripction,"")!=0)*/{
            printf("%s %s %d %d Sala%d %s\n",eve[i].descripction,eve[i].date,eve[i].begin,
                eve[i].min,eve[i].sala,eve[i].responsable);
            printf("* %s %s %s\n",eve[i].members[0],eve[i].members[1],eve[i].members[2]);
        }        
}

int date(int N){
    return atoi(itoa(eve[N].date%10000) +  itoa(eve[N].date/10000 %100)
            +itoa(eve[N].date/1000000)+itoa(eve[N].begin));
}

int sort(int N){
    int i;
    strcpy(list[N],itoa(date(N)));
    qsort(list,count_event,sizeof(int),cmpfunc);
    for(i=1;i<=count_event;i++)
        for (y=1;y<=count_event;y++)
        if (list[i]==date(y)) 
    
}


/*MAIN PROGRAM*/
int main(){
    int flag=1;
    char comand,aux,str[MAX_STR];
    for (aux=0;aux != 11;aux++) count_room[aux]=0;
    while (1){
        switch(comand=getchar()){
            case 'a': /*Adiciona um evento*/
                getchar();
                fgets(str,MAX_INPUT_LINE,stdin);
                create_event(str);
                break;
            case 's':
                imprime_eve(aux=getchar());
                break;
            case 'x': /*Termina o Programa*/
                exit(0);
                break;  
        }
    }
    return 0;
}