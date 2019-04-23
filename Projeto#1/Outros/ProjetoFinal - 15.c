#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*CONSTANTS*/
#define MAX_STR 64  /*Constant for strings (like names of Events and Members)*/
#define MAX_ROOMS 11        /*Rooms from 1 up to 10*/
#define MAX_EVENTS 101      /*Events from 1 up to 100*/
#define MAX_DATE 9          /*exemple: 20062019 - 8 char +\0*/
#define MAX_HOUR 5          /*exemple: 1005 - 4 char +\0*/
#define MAX_MEMBERS 4       /*1 Responsabel + 3 Members*/
#define MAX_DURATION 1440   /*Duration from 1 up to 1440*/
#define MAX_LIST 9          /*At max, our input is gonna be divided by 9*/
#define MAX_INPUT_LINE 568  /*Assuming that 63*9 is the limit of input*/

/*Structurs*/
typedef struct {
    int room,duration,count_members;
    char descripction[MAX_STR],hour[MAX_HOUR],date[MAX_ROOMS];
    char member[MAX_MEMBERS][MAX_STR];
} event;

/*Global Variables*/
int count_room[MAX_ROOMS];            /*Counter to know many events are in a room*/
char comand,list[MAX_LIST][MAX_STR];  /*Comand that will be used in switch (in main)*/
event eve[MAX_ROOMS][MAX_EVENTS];     /*Variable to use as */
event temp[MAX_ROOMS*MAX_EVENTS];


/*--------Functions--------*/

/*----Erro Functions----*/

/*It takes a date in string format (ex. '01022020') and returns the inverse in
int format (ex. 20200201)*/
int date_int(char d[]){
  int date=atoi(d), year=date%10000, month=((date/10000)%100), day=date/1000000;
  return year*10000 + month*100 + day;
}

/*Calculates the end time of an event*/
int end_hour(int hour, int dura){
    int  min = hour%100+dura%60, hours = hour/100+dura/60+min/60;
    return hours*100 + min%60;
}

/*Searches where is the event with the exact same description*/
int search_eve(char desc[]){
  int room,eve_num;
  for (room=0;room<=10;room++)
      for (eve_num=0;eve_num<=count_room[room];eve_num++)
          if (strcmp(eve[room][eve_num].descripction,desc)==0)
              return room*1000+eve_num;
  printf("Evento %s inexistente.\n",list[0]);
  return 0;
}

/*Seperates the input and adds it to the global variable "list"*/
void str_list(char s[]){
  int i=0;
  char *token;
  token = strtok(s, ":\n");
  while( token != NULL ) {
    strcpy(list[i++],token);
    token = strtok(NULL, ":\n");
  }
}

/*Receives the input and sends it to str_list*/
void input_work(){
  int auxd=0;
  char line[MAX_INPUT_LINE];
  for (auxd=0;auxd != 10;auxd++) strcpy(list[auxd],"");
  comand=getchar();
  if (comand!='x' && comand!='l' && comand!='\n'){
    getchar();
    fgets(line,MAX_INPUT_LINE,stdin);
    str_list(line);
  }
}

/*Turns a matrix in a vector*/
int matrix_to_vector(event *temp){
  int i,j,k=1;
  for ( i = 1; i <= 10; i++){
    for ( j = 1; j <= count_room[i]; j++)
      /*if (strcmp(eve[i][j].descripction,"")!=0){*/
      *temp[k++] = eve[i][j];
    /*}*/
  }
  return --k;
}


/*Sorts the events of a room.*/
void insertionSort(event ev[], int n){
  int i,j;
  event temp;
  for (i = 1; i <= n; i++) {
    temp = ev[i];
    j = i - 1;
    while (j >= 0 && ((date_int(ev[j].date) > date_int(key.date)) ||
      ((date_int(ev[j].date) == date_int(key.date) &&
        atoi(ev[j].hour) > atoi(key.hour))) ||
      ((date_int(ev[j].date) == date_int(key.date) &&
      atoi(ev[j].hour) == atoi(key.hour) && ev[j].room > key.room)))){
        ev[j + 1] = ev[j];
        j--;
      }
    ev[j + 1] = key;
  }
}


/*----Verification Functions----*/

/*Conditions to verify if the room is available*/
int hour_check(int room,int eve_num,int hour,int dura,int date2,int eve_num2){
  event even;
  int eve_begin,end,eve_end;
  even = eve[room][eve_num], eve_begin=atoi(even.hour);
  end = end_hour(hour,dura), eve_end = end_hour(eve_begin,even.duration);
  if ((eve_num!=eve_num2 && atoi(even.date) == date2)
    && ((hour>eve_begin && hour<eve_end) || (eve_begin<end && end<eve_end)
    || (hour>eve_begin && end<eve_end) || (hour<eve_begin && end>eve_end)
    || (hour==eve_begin) || (end==eve_end)))
      return 1;
  return 0;
}

/*Verifies if an event doesn't go on top of other that already existes*/
int room_available(int room,int date2,int hour,int dura,int eve_num){
  int i=1;
  for (i=1;i<=count_room[room];i++){
    if (hour_check(room,i,hour,dura,date2,eve_num))
        return 1;
    }
  return 0;
}

/*Verifies if a member as an event in another room at the same time*/
int member_available(int data2,int hour,int dura,int room2,int escolha){
  int room,eve_num,y,i,flag=0;
  for (room=1;room<=10;room++)
    for (eve_num=1;eve_num<=count_room[room];eve_num++)
      for (y=0;y<=eve[room][eve_num].count_members;y++)
        for (i=5;i!=10;i++)
          if ((room!=room2) && (strcmp(eve[room][eve_num].member[y],list[i])==0
          && strcmp(eve[room][eve_num].member[y],"")!=0
          && hour_check(room,eve_num,hour,dura,data2,0))){
            if (escolha==0) printf("Impossivel agendar evento %s. ",list[0]);
            else printf("Impossivel adicionar participante. ");
            printf("Participante %s tem um evento sobreposto.\n",
                    eve[room][eve_num].member[y]);
            flag=1;
            strcpy(list[i],"");
          }
  return flag;
}

int available(int room,int eve_num,char des[],char date[],char hour[],int dura,int escolha){
  if (atoi(hour)>=0 && atoi(hour)<=2359 && dura>=1 && dura<=1440 && room>0 && room<11){
    if (room_available(room,atoi(date),atoi(hour),dura,eve_num))
      printf("Impossivel agendar evento %s. Sala%d ocupada.\n",des,room);
    else if (member_available(atoi(date),atoi(hour),dura,room,escolha)==0)
      return 1;
  }
  return 0;
}


/*----Regular Functions----*/

/*Print one event*/
void print_eve(event ev[], int i){
  int y = 1;
  if (strcmp(ev[i].descripction,"")!=0){
    y=1;
    printf("%s %s %s %d Sala%d %s\n*",ev[i].descripction,ev[i].date,
    ev[i].hour,ev[i].duration,ev[i].room,ev[i].member[0]);
    while (y<ev[i].count_members)
      printf(" %s",ev[i].member[y++]);
    printf("\n");
  }
}

/*Print the events of a N room*/
void print_room(int room){
  int i=1;
  for (i=1;i<=count_room[room];i++)
    print_eve(eve[room],i);
}

/*Print all events*/
void print_all(){
  event temp
  int i,k=(matrix_to_vector(&temp)-1);
  insertionSort(temp,k);
  for (i=1;i<=k;i++)
    print_eve(temp,i);
}

/*Creates an event*/
void create_event(){
  int i, room = atoi(list[4]) , eve_num= ++count_room[room];
  if (available(room,eve_num,list[0],list[1],list[2],atoi(list[3]),0)){
    strcpy(eve[room][eve_num].descripction,list[0]);
    strcpy(eve[room][eve_num].date,list[1]);
    strcpy(eve[room][eve_num].hour,list[2]);
    eve[room][eve_num].duration = atoi(list[3]);
    eve[room][eve_num].room = room;
    for (i=0;strcmp(list[i+5],"")!=0;i++)
      strcpy(eve[room][eve_num].member[i],list[i+5]);
    eve[room][eve_num].count_members=i; /*if all members are added, then count_members=4*/
    insertionSort(eve[room],eve_num);
    }
  else
    --count_room[room];
  }

/*Removes an event*/
void remove_event(int room, int eve_num){
  for (;eve_num<=count_room[room] && eve_num<100;eve_num++)
      eve[room][eve_num]=eve[room][eve_num+1];
  count_room[room]--;
}

/*Changes the duration of an event*/
void change_duration(int room,int eve_num,int dura){
  if (!(room==0 && eve_num==0) && (dura>=1 && dura<=MAX_DURATION
  && dura!=eve[room][eve_num].duration)){
      if (available(room,eve_num,eve[room][eve_num].descripction,
        eve[room][eve_num].date,eve[room][eve_num].hour,dura,0)){
          eve[room][eve_num].duration=dura;
          insertionSort(eve[room],count_room[room]);
        }
    }
}

/*Changes the room of an event*/
void change_room(int room, int eve_num,int room2){
  if (!(room==0 && eve_num==0)){
    if (room!=room2 && room>0 && room<11 && room2>0 && room2<11){
      if (room_available(room2,atoi(eve[room][eve_num].date),
      atoi(eve[room][eve_num].hour),eve[room][eve_num].duration,0))
        printf("Impossivel agendar evento %s. Sala%d ocupada.\n",
        list[0],room2);
    else{
      eve[room2][++count_room[room2]] = eve[room][eve_num];
      eve[room2][count_room[room2]].room=room2;
      insertionSort(eve[room2],count_room[room2]);
      remove_event(room,eve_num);
      }
    }
  }
}

/*Changes the hour of an even*/
void change_hour(int room,int eve_num,char* hour){
  char hours[MAX_HOUR];
  strcpy(hours,hour);
  if (!(room==0 && eve_num==0))
    if (atoi(hours)>=0 && atoi(hours)<=2359)
      if (available(room,eve_num,eve[room][eve_num].descripction,
        eve[room][eve_num].date,hours,eve[room][eve_num].duration,0)){
        strcpy(eve[room][eve_num].hour,hours);
        insertionSort(eve[room],count_room[room]);
  }
}

/*Removes member from an event*/
void remove_member(int room, int eve_num,char s[]){
  int i,flag=0;
  for (i=1;i<=eve[room][eve_num].count_members;i++)
    if (strcmp(list[1],eve[room][eve_num].member[i])==0)
      flag=1;
  if (eve[room][eve_num].count_members>2){
    for (i=1;i!=eve[room][eve_num].count_members /*Finds were the person is in the event (Finds the position)*/
    && strcmp(eve[room][eve_num].member[i],s)!=0;i++);
    if (i<eve[room][eve_num].count_members){
      for (;i<eve[room][eve_num].count_members;i++){
        strcpy(eve[room][eve_num].member[i],eve[room][eve_num].member[i+1]);
        eve[room][eve_num].count_members--;
      }
    }
  }
  else if (flag==1){
    printf("Impossivel remover participante. ");
    printf("Participante %s e o unico participante no evento %s.\n",
            eve[room][eve_num].member[1],eve[room][eve_num].descripction);
  }
}

/*Adds a member from an event*/
void add_member(int room, int eve_num,char s[]){
  int i,flag=0,auxd=0;
  if (eve[room][eve_num].count_members==4){
    printf("Impossivel adicionar participante. ");
    printf("Evento %s ja tem 3 participantes.\n",eve[room][eve_num].descripction);
  }
  else{
    for (i=1;i<=eve[room][eve_num].count_members;i++)
      if (strcmp(list[1],eve[room][eve_num].member[i])==0)
        flag=1;

    if (flag==0){
      strcpy(eve[room][eve_num].member[eve[room][eve_num].count_members],s);
      eve[room][eve_num].count_members++;
      for (auxd=0;auxd<=eve[room][eve_num].count_members;auxd++)
        strcpy(list[auxd+5],eve[room][eve_num].member[auxd]);
      if (member_available(atoi(eve[room][eve_num].date),atoi(eve[room][eve_num].hour),
      eve[room][eve_num].duration,room,1))
        remove_member(room,eve_num,s);
    }
  }
}








/*MAIN PROGRAM*/
int main(){
  int room=0,eve_num=0,auxd=0;
  for (auxd=0;auxd != 11;auxd++) count_room[auxd]=0;
  while (1){
    input_work();
    if (comand!='a' && comand!='s' && comand!='l' && comand!='x'){
      auxd = search_eve(list[0]), room = auxd/1000,eve_num = auxd%1000;
      for (auxd=0;auxd<=eve[room][eve_num].count_members;auxd++)
        strcpy(list[auxd+5],eve[room][eve_num].member[auxd]);
      }
    switch(comand){
      case 'a': /*Add an Event*/
        create_event();
        break;
      case 'l': /*Organiza Todos os eventos por ordem cornologica*/
        print_all();
        break;
      case 's': /*Displays in sort all the events in one room*/
        if (atoi(list[0])>0 && atoi(list[0])<11)
          print_room(atoi(list[0]));
        break;
      case 'r': /*Retira um evento*/
        remove_event(room,eve_num);
        break;
      case 'i': /*Troca o inicio de um evento*/
        change_hour(room,eve_num,list[1]);
        break;
      case 't': /*Troca a duracao de um evento*/
        change_duration(room,eve_num,atoi(list[1]));
        break;
      case 'm': /*Troca a room de um evento*/
        change_room(room,eve_num,atoi(list[1]));
        break;
      case 'A': /*Adiciona um Membro a um evento*/
        if (!(room==0 && eve_num==0))
          add_member(room,eve_num,list[1]);
        break;
      case 'R': /*Remova um Membro a um evento*/
        if (!(room==0 && eve_num==0))
          remove_member(room,eve_num,list[1]);
        break;
      case 'x': /*Termina o Programa*/
        exit(0);
        break;
    }
  }
  return 0;
}
