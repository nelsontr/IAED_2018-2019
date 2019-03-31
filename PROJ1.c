#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*CONSTANTES*/
#define MAX_STR 63 /*Constante para strings(como nomes de eventos, Responsaveis, Membros)*/
#define MAX_SALAS 10 
#define MAX_EVENTOS 100
#define MAX_MEMBROS 3
#define MAX_LINHA_INPUT 567 /*63*9*/

/*ESTRUTURAS*/
typedef struct {
    int sala,data,duracao,inicio,cont_membros;
    char descricao[MAX_STR],responsavel[MAX_STR],membros[MAX_MEMBROS][MAX_STR];
} evento;

/*VARIAVEIS GLOBAIS*/
int cont_sala[11];
char lista[9][63];
evento eve[MAX_SALAS][MAX_EVENTOS];

/*FUNCOES*/

/*ERRO FUNCTIONS*/
int fim(int hora, int dura){
    int fim=hora+dura , horas=(fim/100)+(fim%100)/60 , min=(fim%100);
    return horas*100+min;
}

int sala_ocupada(int sala,int data2,int hora,int dura){
    evento even;
    int i,final,final_eve;
    for (i=1;i<=cont_sala[sala];i++){
        even = eve[sala][i], final = fim(hora,dura), final_eve = fim(even.inicio,even.duracao);
        if ((even.data == data2) && ((hora>even.inicio && hora<final_eve) 
        || (even.inicio<final && final<final_eve) || (hora>even.inicio && final<final_eve) 
        || (hora<even.inicio && final>final_eve) || (hora==even.inicio))){
            return 1;
        }
    }
    return 0;
}

int membro_evento(int sala2,int data2,int hora,int dura){
    int sala,num_eve,y,i;
    for (sala=1;sala<=10;sala++){
    printf("\n1.");
        for (num_eve=1;num_eve<=cont_sala[sala];num_eve++){
        printf("\n2.");
            for (y=0;y<=eve[sala][num_eve].cont_membros;y++){
                for (i=7;i!=10;i++){
                printf("\n%s",lista[i]);
                    if (strcmp(eve[sala][num_eve].membros[y],lista[i])==0 && strlen(eve[sala][num_eve].membros[y])!=0
                        && sala_ocupada(sala,data2,hora,dura)){
                        return 1;
                    }
                }
        }
        }
    }
    return 0;
}

int procura_eve(char desc[]){
    int sala,num_eve;
    for (sala=0;sala<=10;sala++)
        for (num_eve=0;num_eve<=cont_sala[sala];num_eve++)
            if (strcmp(eve[sala][num_eve].descricao,desc)==0) 
                return sala*1000+num_eve;
    return 0;
}

void str_lista(char s[]){
    int i=0;
    char *token;
    token = strtok(s, ":");
    while( token != NULL ) {   
        strcpy(lista[i++],token);
        token = strtok(NULL, ":\n");
    }
}

void cria_evento(){
    int i , sala = atoi(lista[4]) , num_eve = ++cont_sala[sala];
    if (sala_ocupada(atoi(lista[4]),atoi(lista[1]),atoi(lista[2]),atoi(lista[3])))
        printf("Impossivel agendar evento %s. Sala%d ocupada.\n",lista[1],sala);
    else if (membro_evento(atoi(lista[4]),atoi(lista[1]),atoi(lista[2]),atoi(lista[3])))
        printf("MEMBRO");
    else {
    	strcpy(eve[sala][num_eve].descricao,lista[0]);
	    eve[sala][num_eve].data = atoi(lista[1]);
	    eve[sala][num_eve].inicio = atoi(lista[2]);
	    eve[sala][num_eve].duracao = atoi(lista[3]);
	    strcpy(eve[sala][num_eve].responsavel,lista[5]);
	    for (i=0;strcmp(lista[i+6],"")!=0;i++){
	        strcpy(eve[sala][num_eve].membros[i],lista[i+6]);
	        strcpy(lista[i],"");
    	}
    eve[sala][num_eve].cont_membros=i;
	}
}

void imprime_eve(int N){
    int i;
    for (i=1;i<=cont_sala[N];i++)
        if (strcmp(eve[N][i].descricao,"")!=0){
            printf("%s %d %d %d Sala%d %s\n",eve[N][i].descricao,eve[N][i].data,eve[N][i].inicio,
                eve[N][i].duracao,N,eve[N][i].responsavel);
            printf("* %s %s %s\n",eve[N][i].membros[0],eve[N][i].membros[1],eve[N][i].membros[2]);
        }        
}

void retira_eve(int sala, int num_eve){
    for (;num_eve<=cont_sala[sala];num_eve++)
        eve[sala][num_eve]=eve[sala][num_eve+1];
}

void adiciona_membro(int sala, int num_eve,char s[]){
    int len=eve[sala][num_eve].cont_membros;
    strcpy(eve[sala][num_eve].membros[len],s);
    eve[sala][num_eve].cont_membros++;
}

void remova_membro(int sala, int num_eve,char s[]){
    int i;
    for (i=0;strcmp(eve[sala][num_eve].membros[i],s)!=0;i++); /*Descobrir em que posição o membro esta*/
    for (;i<eve[sala][num_eve].cont_membros;i++)
        strcpy(eve[sala][num_eve].membros[i],eve[sala][num_eve].membros[i+1]);
    strcpy(eve[sala][num_eve].membros[i],"");
    eve[sala][num_eve].cont_membros--;
}

void troca_sala(int sala, int num_eve,int sala2){
    eve[sala2][cont_sala[sala2]] = eve[sala][num_eve];
    printf("%s",eve[sala2][cont_sala[sala2]].descricao);
    retira_eve(sala,num_eve);
}

/*MAIN PROGRAM*/
int main(){
    int sala,num_eve,auxd;
    char comand,aux[MAX_STR],str[MAX_STR];
    for (auxd=0;auxd != 11;auxd++) cont_sala[auxd]=0;
    while (1){
        comand=getchar();
        if (comand!='x') getchar();
        auxd = procura_eve(lista[1]);
        sala = auxd/1000,num_eve = auxd%1000;
        
        switch(comand){
            case 'a': /*Adiciona um evento*/
        		fgets(str,MAX_LINHA_INPUT,stdin);
                str_lista(str);
        		cria_evento();
                break;
            case 'l': /*Organiza Todos os eventos por ordem cornologica*/
                break;
            case 's': /*Organiza os eventos por ordem cornologica de uma sala*/
                scanf("%d",&auxd);
                imprime_eve(auxd);
                break;
            case 'r': /*Retira um evento*/
                retira_eve(sala,num_eve);             
                break;
            case 'i': /*Troca o inicio de um evento*/
                eve[sala][num_eve].inicio=atoi(lista[2]);             
                break;
            case 't': /*Troca a duracao de um evento*/
                eve[sala][num_eve].duracao=atoi(lista[2]);             
                break;
            case 'm': /*Troca a sala de um evento*/
                troca_sala(sala,num_eve,atoi(lista[2]));
                break;
            case 'A': /*Adiciona um Membro a um evento*/
                if (eve[sala][num_eve].cont_membros<3)
                    adiciona_membro(sala,num_eve,lista[2]);
                else printf("Impossivel remover participante. Evento %s ja tem 3 participantes\n",
                        eve[sala][num_eve].descricao);
                break; 
            case 'R': /*Remova um Membro a um evento*/
                if (eve[sala][num_eve].cont_membros>1)
                    remova_membro(sala,num_eve,lista[2]);
                else printf("Impossivel remover participante. Participante %s e o unico participante no evento %s\n",
                        lista[2],eve[sala][num_eve].descricao);
                break;
            case 'x': /*Termina o Programa*/
                exit(0);
                break;  
        }
    }
    return 0;
}