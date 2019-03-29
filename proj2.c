#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*CONSTANTS*/
#define MAX_STR 63 /*Constante para strings(como nomes de eventos, Responsaveis, Membros)*/
#define MAX_ROOMS 11 
#define MAX_EVENTS 101
#define MAX_MEMBERS 4
#define MAX_INPUT_LINE 567 /*63*9*/

/*Structurs*/
typedef struct {
    int begin,min,sala,count_members;
    char date[MAX_ROOMS],descripction[MAX_STR],member[MAX_MEMBERS][MAX_STR];
} event;

/*Global Variables*/
int count_room[11];
char list[9][63];
event eve[MAX_ROOMS][MAX_EVENTS];

/*Functions*/

/*Erro Functions*/
int fim(int hora, int dura){
    int fim=hora+dura , horas=(fim/100)+(fim%100)/60 , min=(fim%100)%60;
    return horas*100+min;
}

int sala_ocupada(int sala,int data2,int hora,int dura){
    event even;
    int i,final,final_eve;
    for (i=1;i<=count_room[sala];i++){
        even = eve[sala][i], final = fim(hora,dura), final_eve = fim(even.begin,even.min);
        if ((atoi(even.date) == data2) && ((hora>even.begin && hora<final_eve) 
        || (even.begin<final && final<final_eve) || (hora>even.begin && final<final_eve) 
        || (hora<even.begin && final>final_eve) || (hora==even.begin))){
            return 1;
        }
    }
    return 0;
}

int membro_evento(int data2,int hora,int dura){
    int sala,num_eve,y,i,flag=0;
    for (sala=1;sala<=10;sala++)
        for (num_eve=1;num_eve<=count_room[sala];num_eve++)
            for (y=0;y<=eve[sala][num_eve].count_members;y++)
                for (i=5;i!=9;i++)
                    if (strcmp(eve[sala][num_eve].member[y],list[i])==0 && strcmp(eve[sala][num_eve].member[y],"")!=0
                    && sala_ocupada(sala,data2,hora,dura)){
                    printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n",
                    list[0],eve[sala][num_eve].member[y]);
                        flag=1;
                    }
    return flag;
}

void str_list(char s[]){
    int i=0;
    char *token;
    token = strtok(s, ":\n");
    while( token != NULL ) {   
        strcpy(list[i++],token);
        token = strtok(NULL, ":\n");
    }
}

void cria_evento(){
    int i, sala = atoi(list[4]) , num_eve;
    if (sala_ocupada(atoi(list[4]),atoi(list[1]),atoi(list[2]),atoi(list[3])))
        printf("Impossivel agendar evento %s. Sala%d ocupada.\n",list[0],sala);
    else if (membro_evento(atoi(list[1]),atoi(list[2]),atoi(list[3]))==0){
        num_eve = ++count_room[sala];
    	strcpy(eve[sala][num_eve].descripction,list[0]);
	    strcpy(eve[sala][num_eve].date,list[1]);
	    eve[sala][num_eve].begin = atoi(list[2]);
	    eve[sala][num_eve].min = atoi(list[3]);
	    for (i=0;strcmp(list[i+5],"")!=0;i++){
	        strcpy(eve[sala][num_eve].member[i],list[i+5]);
	        strcpy(list[i],"");
    	}
        eve[sala][num_eve].count_members=i;
    }
}

int search_eve(char desc[]){
    int sala,num_eve;
    for (sala=0;sala<=10;sala++)
        for (num_eve=0;num_eve<=count_room[sala];num_eve++)
            if (strcmp(eve[sala][num_eve].descripction,desc)==0) 
                return sala*1000+num_eve;
    return 0;
}

void print_eve(int N){
    int i;
    for (i=1;i<=count_room[N];i++)
        if (strcmp(eve[N][i].descripction,"")!=0){
            printf("%s %s %d %d Sala%d %s\n",eve[N][i].descripction,eve[N][i].date,
            eve[N][i].begin,eve[N][i].min,N,eve[N][i].member[0]);
            printf("* %s %s %s\n",eve[N][i].member[1],eve[N][i].member[2],eve[N][i].member[3]);
        }        
}

void retira_eve(int sala, int num_eve){
    for (;num_eve<=count_room[sala];num_eve++)
        eve[sala][num_eve]=eve[sala][num_eve+1];
}

void adiciona_membro(int sala, int num_eve,char s[]){
    int len=eve[sala][num_eve].count_members;
    if (eve[sala][num_eve].count_members<3){
        strcpy(eve[sala][num_eve].member[len],s);
        eve[sala][num_eve].count_members++;}
    else printf("Impossivel remover participante. Evento %s ja tem 3 participantes\n",
                eve[sala][num_eve].descripction);
}

void remova_membro(int sala, int num_eve,char s[]){
    int i;
    if (eve[sala][num_eve].count_members>1){
        for (i=0;strcmp(eve[sala][num_eve].member[i],s)!=0;i++); /*Descobrir em que posição o membro esta*/
        for (;i<eve[sala][num_eve].count_members;i++)
            strcpy(eve[sala][num_eve].member[i],eve[sala][num_eve].member[i+1]);
        strcpy(eve[sala][num_eve].member[i],"");
        eve[sala][num_eve].count_members--;}
    else 
        printf("Impossivel remover participante. Participante %s e o unico participanteno evento %s\n",
                list[1],eve[sala][num_eve].descripction);
}

void troca_sala(int sala, int num_eve,int sala2){
    eve[sala2][count_room[sala2]] = eve[sala][num_eve];
    printf("%s",eve[sala2][count_room[sala2]].descripction);
    retira_eve(sala,num_eve);
}

/*MAIN PROGRAM*/
int main(){
    int room,num_eve,auxd;
    char comand,str[MAX_STR];
    for (auxd=0;auxd != 11;auxd++) count_room[auxd]=0;
    while (1){
        for (auxd=0;auxd != 10;auxd++) strcpy(list[auxd],"");
        comand=getchar();
        if (comand!='x' || comand!='\n') getchar();
        fgets(str,MAX_INPUT_LINE,stdin);
        str_list(str);
        auxd = search_eve(list[0]), room = auxd/1000,num_eve = auxd%1000;
        switch(comand){
            case 'a': /*Add an Event*/
        		cria_evento();
                break;
            case 'l': /*Organiza Todos os eventos por ordem cornologica*/
                break;
            case 's': /*Displays in sort all the events in one room*/
                print_eve(atoi(list[0]));
                break;
            case 'r': /*Retira um evento*/
                /*printf("sala=%d & num_eve=%d",room,num_eve);*/
                if (room==0 && num_eve==0)
                    printf("Evento %s inexistente.\n",list[0]);
                else
                    retira_eve(room,num_eve);             
                break;
            case 'i': /*Troca o inicio de um evento*/
                eve[room][num_eve].begin=atoi(list[1]);             
                break;
            case 't': /*Troca a duracao de um evento*/
                eve[room][num_eve].min=atoi(list[1]);             
                break;
            case 'm': /*Troca a sala de um evento*/
                troca_sala(room,num_eve,atoi(list[1]));
                break;
            case 'A': /*Adiciona um Membro a um evento*/
                adiciona_membro(room,num_eve,list[1]);
                break; 
            case 'R': /*Remova um Membro a um evento*/
                remova_membro(room,num_eve,list[1]);
                break;
            case 'x': /*Termina o Programa*/
                exit(0);
                break; 
        }
    }
    return 0;
}