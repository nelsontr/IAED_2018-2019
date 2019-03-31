date2#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*CONSTANTS*/
#define MAX_STR 63 /*Constant for strings (like names of Events and Members)*/
#define MAX_ROOMS 11
#define MAX_EVENTS 101
#define MAX_DATE 9
#define MAX_HOUR 5
#define MAX_MEMBERS 4
#define MAX_LIST 9
#define MAX_INPUT_LINE 568 /*Assuming that 63*9 is the limit of input*/

/*Structurs*/
typedef struct {
  int room,duration,count_members;
  char descripction[MAX_STR],hour[MAX_HOUR],date[MAX_ROOMS];
  char member[MAX_MEMBERS][MAX_STR];
} event;

/*Global Variables*/
int count_room[MAX_ROOMS];
char comand,list[MAX_LIST][MAX_STR];
event eve[MAX_ROOMS][MAX_EVENTS];

/*Functions*/

/*Essential Functions*/
int date_int(char d[]){ /*Transforma '01022020' em 20200201 de modo a comparar*/
  int date=atoi(d), ano=date%10000, mes=((date/10000)%100), dia=date/1000000;
  return ano*1000 + mes*100 + dia;
}

int end_hour(int hour, int dura){
  int end=hour+dura , hours=(end/100)+(end%100)/60 , min=(end%100)%60;
  return hours*100+min;
}

int search_eve(char desc[]){
  int room,eve_num;
  for (room=0;room<=10;room++)
    for (eve_num=0;eve_num<=count_room[room];eve_num++)
      if (strcmp(eve[room][eve_num].descripction,desc)==0)
        return room*1000+eve_num;
  return 0;
}

void str_list(char str[]){
  int i=0;
  char *token;
  token = strtok(s, ":\n");
  while( token != NULL ) {
    strcpy(list[i++],token);
    token = strtok(NULL, ":\n");
  }
}

void input_work(){
  for (aux=0;aux!=MAX_LIST;aux++) strcpy(list[aux],""); /*Reset to list*/
  comand=getchar();
  if (comand!='x' || comand!='\n') getchar(); /*Remove the space from input line*/
  fgets(str,MAX_INPUT_LINE,stdin);
  str_list(str); /*Seperates input and creates a list of it*/
}

/*Verification Functions*/
int room_available(int room,int date2,int hour,int dura,int eve_num){
  event even; /*Auxiliar evento to check if it coud be an event*/
  int i,eve_begin,end,eve_end;
  for (i=1;i<=count_room[room];i++){
    even = eve[room][i], eve_begin=atoi(even.hour);
    end = end_hour(hour,dura), eve_end = end_hour(eve_begin,even.duration);
    if ((eve_num!=i && atoi(even.date) == date2)
    && ((hour>eve_begin && hour<eve_end) || (eve_begin<end && end<eve_end)
    || (hour>eve_begin && end<eve_end) || (hour<eve_begin && end>eve_end)
    || (hour==eve_begin) || (end==eve_end)))
        return 1;
  }
  return 0;
}

int membro_evento(int date,int hour,int dura,int room2){
  int room,eve_num,y,i,flag=0;
  for (room=1;room<=10;room++)
    for (eve_num=1;eve_num<=count_room[room];eve_num++)
      for (y=0;y<=eve[room][eve_num].count_members;y++)
        for (i=5;i!=9;i++)
          if (room!=room2 && strcmp(eve[room][eve_num].member[y],list[i])==0
          && strcmp(eve[room][eve_num].member[y],"")!=0
          && room_ocupada(room,date,hour,dura,0))){
          printf("Impossivel agendar evento %s. ",list[0]);
          printf("Participante %s tem um evento sobreposto.\n",
                  eve[room][eve_num].member[y]);
          flag=1;
          }
  return flag;
}


/*MAIN PROGRAM*/
int main(){
  int room,eve_num,aux;
  char comand,str[MAX_STR];
  for (aux=0;aux!=MAX_ROOMS;aux++) count_room[aux]=0;
  while (1){
    input_work();
    aux = search_eve(list[0]), room = aux/1000, eve_num = aux%1000;
    switch(comand){
      case 'a': /*Add an Event*/
        /*cria_evento();*/
        break;
      case 'l': /*Organiza Todos os eventos por ordem cornologica*/
        break;
      case 's': /*Displays in sort all the events in one room*/
        /*Bsort(eve[atoi(list[0])],count_room[atoi(list[0])]);
        print_eve(atoi(list[0]));*/
        break;
      case 'r': /*Retira um evento*/
        /*printf("sala=%d & num_eve=%d",room,num_eve);
        if (room==0 && num_eve==0)
        printf("Evento %s inexistente.\n",list[0]);
        else
        retira_eve(room,num_eve);*/
        break;
      case 'i': /*Troca o inicio de um evento*/
        /*if (room==0 && num_eve==0)
        printf("Evento %s inexistente.\n",list[0]);
        else{
        for (aux=0;aux<=eve[room][num_eve].count_members;aux++)
        strcpy(list[aux+5],eve[room][num_eve].member[aux]);
        if (sala_ocupada(room,atoi(eve[room][num_eve].date),atoi(list[1]),
        eve[room][num_eve].min,num_eve))
        printf("Impossivel agendar evento %s. Sala%d ocupada.\n",list[0],room);
        else if (membro_evento(atoi(eve[room][num_eve].date),atoi(list[1]),
        eve[room][num_eve].min,room)==0)
        strcpy(eve[room][num_eve].begin,list[1]);
        }*/
        break;
      case 't': /*Troca a duracao de um evento*/
        /*if (room==0 && num_eve==0)
        printf("Evento %s inexistente.\n",list[0]);
        else{
        for (aux=0;aux<=eve[room][num_eve].count_members;aux++)
        strcpy(list[aux+5],eve[room][num_eve].member[aux]);
        if (sala_ocupada(room,atoi(eve[room][num_eve].date),atoi(eve[room][num_eve].begin),
        atoi(list[1]),num_eve))
        printf("Impossivel agendar evento %s. Sala%d ocupada.\n",list[0],room);
        else if (membro_evento(atoi(eve[room][num_eve].date),atoi(eve[room][num_eve].begin),
        atoi(list[1]),room)==0)
        eve[room][num_eve].min=atoi(list[1]);
        }*/
        break;
      case 'm': /*Troca a sala de um evento*/
        /*if (room==0 && num_eve==0)
        printf("Evento %s inexistente.\n",list[0]);
        else{
        if (sala_ocupada(atoi(list[1]),atoi(eve[room][num_eve].date),atoi(eve[room][num_eve].begin),
        eve[room][num_eve].min,0))
        printf("Impossivel agendar evento %s. Sala%d ocupada.\n",list[0],atoi(list[1]));
        else if (membro_evento(atoi(eve[room][num_eve].date),atoi(eve[room][num_eve].begin),
        eve[room][num_eve].min,atoi(list[1]))==0)
        troca_sala(room,num_eve,atoi(list[1]));
        }*/
        break;
      case 'A': /*Adiciona um Membro a um evento*/
        /*adiciona_membro(room,num_eve,list[1]);*/
        break;
      case 'R': /*Remova um Membro a um evento*/
        /*remova_membro(room,num_eve,list[1]);*/
        break;
      case 'x': /*Termina o Programa*/
        exit(0);
        break;
    }
  }
  return 0;
}
