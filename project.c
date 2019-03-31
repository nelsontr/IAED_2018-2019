#include <stdio.h>
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
  return 0; /*Means that there is no event with that descripction*/
}

void str_list(char str[]){
  int i=0;
  char *token;
  token = strtok(str, ":\n");
  while( token != NULL ) {
    strcpy(list[i++],token);
    token = strtok(NULL, ":\n");
  }
}

void input_work(){
  int aux=0;
  char str[MAX_STR];
  for (aux=0;aux!=MAX_LIST;aux++) strcpy(list[aux],""); /*Reset to list*/
  comand=getchar();
  if (comand!='x' || comand!='\n') getchar(); /*Remove the space from input line*/
  fgets(str,MAX_INPUT_LINE,stdin);
  str_list(str); /*Seperates input and creates a list of it*/
}

void sort_room(event ev[],int s){/*BubleSort to organize events in rooms*/
  int i, j;
  event temp;
  for (i=1; i<=s ;i++)
    for (j=1; j<=s-i ;j++)
      if (date_int(ev[j].date) >= date_int(ev[j + 1].date)
          && atoi(ev[j].hour) > atoi(ev[j + 1].hour)){
          temp = ev[j];
          ev[j] = ev[j+1];
          ev[j+1] = temp;
      }
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

int member_available(int date,int hour,int dura,int room2){
  int room,eve_num,y,i,flag=0;
  for (room=1;room<=10;room++)
    for (eve_num=1;eve_num<=count_room[room];eve_num++)
      for (y=0;y<=eve[room][eve_num].count_members;y++)
        for (i=5;i!=MAX_LIST;i++)
          if (room!=room2 && strcmp(eve[room][eve_num].member[y],list[i])==0
          && strcmp(eve[room][eve_num].member[y],"")!=0
          && room_available(room,date,hour,dura,0)){
          printf("Impossivel agendar evento %s. ",list[0]);
          printf("Participante %s tem um evento sobreposto.\n",
                  eve[room][eve_num].member[y]);
          flag=1;
          strcpy(list[i],"");
          }
  return flag;
}

int available(int room,int eve_num,char des[],char date[],char hour[],int dura){
  if (room_available(room,atoi(date),atoi(hour),dura,eve_num))
    printf("Impossivel agendar evento %s. Sala%d ocupada.\n",des,room);
  else if (member_available(atoi(date),atoi(hour),dura,room)==0)
    return 1;
  return 0;
}

/*Regular Functions*/
void print_room(int room){
  int i,y=1;
  for (i=1;i<=count_room[room];i++,y=1)
    if (strcmp(eve[room][i].descripction,"")!=0){
      printf("%s %s %s %d Sala%d %s\n*",eve[room][i].descripction,eve[room][i].date,
      eve[room][i].hour,eve[room][i].duration,room,eve[room][i].member[0]);
      while (y<eve[room][i].count_members)
        printf(" %s",eve[room][i].member[y++]);
      printf("\n");
    }
}

void create_event(){
  int i, room = atoi(list[4]) , eve_num;
    eve_num = ++count_room[room]; /*Increases the number of events in the room*/
    strcpy(eve[room][eve_num].descripction,list[0]);
    strcpy(eve[room][eve_num].date,list[1]);
    strcpy(eve[room][eve_num].hour,list[2]);
    eve[room][eve_num].duration = atoi(list[3]);
    for (i=0;strcmp(list[i+5],"")!=0;i++){
      strcpy(eve[room][eve_num].member[i],list[i+5]);
      /*strcpy(list[i],"");*/
    }
    eve[room][eve_num].count_members=i; /*Except Responsabel*/
}

void remove_event(int room, int eve_num){
    for (;eve_num<=count_room[room];eve_num++)
        eve[room][eve_num]=eve[room][eve_num+1];
}

void change_room(int room, int eve_num,int room2){
    eve[room2][++count_room[room2]] = eve[room][eve_num];
    remove_event(room,eve_num);
    count_room[room]--;
}

/*MAIN PROGRAM*/
int main(){
  int aux,room,eve_num;
  for (aux=0;aux!=MAX_ROOMS;aux++) count_room[aux]=0;
  while (1){
    input_work();
    aux = search_eve(list[0]), room = aux/1000, eve_num = aux%1000;
    switch(comand){
      case 'a': /*Add an Event*/
        if (available(atoi(list[4]),0,list[0],list[1],list[2],atoi(list[3])))
          create_event();
        break;
      case 'l': /**/
        break;
      case 's': /*Displays in sort all the events in one room*/
        sort_room(eve[atoi(list[0])],count_room[atoi(list[0])]);
        print_room(atoi(list[0]));
        break;
      case 'r': /*Removes an event*/
        if (room!=0 && eve_num!=0)
          remove_event(room,eve_num);
        else
          printf("Evento %s inexistente.\n",list[0]);
        break;
      case 'i': /*Change the hour of an event*/
        for (aux=0;aux<=eve[room][eve_num].count_members;aux++)
          strcpy(list[aux+5],eve[room][eve_num].member[aux]); /*Updates list to display members of the event searched*/
        if (room!=0 && eve_num!=0){
          if (available(room,eve_num,eve[room][eve_num].descripction,
            eve[room][eve_num].date,list[1],eve[room][eve_num].duration))
              strcpy(eve[room][eve_num].hour,list[1]);}
        else
          printf("Evento %s inexistente.\n",list[0]);
        break;
      case 't': /*Change the duration of an event*/
        for (aux=0;aux<=eve[room][eve_num].count_members;aux++)
          strcpy(list[aux+5],eve[room][eve_num].member[aux]); /*Updates list to display members of the event searched*/
        if (room!=0 && eve_num!=0){
          if (available(room,eve_num,eve[room][eve_num].descripction,
            eve[room][eve_num].date,eve[room][eve_num].hour,atoi(list[1])))
              eve[room][eve_num].duration = atoi(list[1]);}
        else
          printf("Evento %s inexistente.\n",list[0]);
        break;
      case 'm': /*Troca a sala de um evento*/
        for (aux=0;aux<=eve[room][eve_num].count_members;aux++)
          strcpy(list[aux+5],eve[room][eve_num].member[aux]); /*Updates list to display members of the event searched*/
        if (room!=0 && eve_num!=0){
          if (available(atoi(list[1]),eve_num,eve[room][eve_num].descripction,
            eve[room][eve_num].date,eve[room][eve_num].hour,eve[room][eve_num].duration))
              change_room(room,eve_num,atoi(list[1]));}
        else
          printf("Evento %s inexistente.\n",list[0]);
        break;
      case 'A': /*Adiciona um Membro a um evento*/
        /*adiciona_membro(room,eve_num,list[1]);*/
        break;
      case 'R': /*Remova um Membro a um evento*/
        /*remova_membro(room,eve_num,list[1]);*/
        break;
      case 'x': /*Termina o Programa*/
        exit(0);
        break;
    }
  }
  return 0;
}
