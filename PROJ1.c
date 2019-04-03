#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*CONSTANTS*/
#define MAX_STR 64 /*Constant for strings (like names of Events and Members)*/
#define MAX_ROOMS 11
#define MAX_EVENTS 101
#define MAX_DATE 9
#define MAX_HOUR 5
#define MAX_MEMBERS 4
#define MAX_DURATION 1440
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
event temp[MAX_ROOMS*MAX_EVENTS];

/*Functions*/

/*Erro Functions*/
int date_int(char d[]){ /*Transforma '01022020' em 20200201 de modo a comparar*/
  int date=atoi(d), ano=date%10000, mes=((date/10000)%100), dia=date/1000000;
  return ano*10000 + mes*100 + dia;
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

void str_list(char s[]){
  int i=0;
  char *token;
  token = strtok(s, ":\n");
  while( token != NULL ) {
    strcpy(list[i++],token);
    token = strtok(NULL, ":\n");
  }
}

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
/*
void Bsort(event ev[],int s){ BubleSort to organize events in rooms
  int i, j;
  event tempo;
  for (i = 1; i <= s; i++)
    for (j = 1; j <= s-i; j++)
      if ((date_int(ev[j].date) > date_int(ev[j + 1].date)) || ((date_int(ev[j].date) == date_int(ev[j + 1].date) &&
      atoi(ev[j].hour) > atoi(ev[j + 1].hour)))){
        tempo = ev[j];
        ev[j] = ev[j + 1];
        ev[j + 1] = tempo;
  }
}*/

/*Verification Functions*/
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

int room_available(int room,int date2,int hour,int dura,int eve_num){
  int i=1;
  for (i=1;i<=count_room[room];i++){
    if (hour_check(room,i,hour,dura,date2,eve_num))
        return 1;
    }
  return 0;
}

int member_available(int data2,int hour,int dura,int room2,int escolha){
  int room,eve_num,y,i,flag=0;
  for (room=1;room<=10;room++)
    for (eve_num=1;eve_num<=count_room[room];eve_num++)
      for (y=0;y<=eve[room][eve_num].count_members;y++)
        for (i=5;i!=9;i++)
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

/*int available(int room,int eve_num,char des[],char date[],char hour[],int dura){
  if (room_available(room,atoi(date),atoi(hour),dura,eve_num))
    printf("Impossivel agendar evento %s. Sala%d ocupada.\n",des,room);
  else if (member_available(atoi(date),atoi(hour),dura,room)==0)
    return 1;
  return 0;
}*/

/*Regular Functions*/
void print_eve(int N){
  int i,y;
  for (i=1;i<=count_room[N];i++)
    if (strcmp(eve[N][i].descripction,"")!=0){
      y=1;
      printf("%s %s %s %d Sala%d %s\n*",eve[N][i].descripction,eve[N][i].date,
      eve[N][i].hour,eve[N][i].duration,N,eve[N][i].member[0]);
      while (y<eve[N][i].count_members)
        printf(" %s",eve[N][i].member[y++]);
      printf("\n");
    }
}

void insertionSort(event arr[], int n)
{
  int i,j;
  event key;
    for (i = 1; i <= n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && ((date_int(arr[j].date) > date_int(key.date)) || ((date_int(arr[j].date) == date_int(key.date) &&
        atoi(arr[j].hour) > atoi(key.hour))) || ((date_int(arr[j].date) == date_int(arr[j + 1].date) &&
        atoi(arr[j].hour) == atoi(arr[j + 1].hour) && arr[j].room > arr[j+1].room)))){
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void create_event(){
    int i, room = atoi(list[4]) , eve_num;
    if (room_available(room,atoi(list[1]),atoi(list[2]),atoi(list[3]),0))
        printf("Impossivel agendar evento %s. Sala%d ocupada.\n",list[0],room);
    else if (member_available(atoi(list[1]),atoi(list[2]),atoi(list[3]),room,0)==0){
        eve_num = ++count_room[room];
    	strcpy(eve[room][eve_num].descripction,list[0]);
	    strcpy(eve[room][eve_num].date,list[1]);
	    strcpy(eve[room][eve_num].hour,list[2]);
      eve[room][eve_num].duration = atoi(list[3]);
      eve[room][eve_num].room = atoi(list[4]);
      for (i=0;strcmp(list[i+5],"")!=0;i++)
	        strcpy(eve[room][eve_num].member[i],list[i+5]);
      eve[room][eve_num].count_members=i;
      insertionSort(eve[room],eve_num);
    }
}

void remove_event(int room, int eve_num){
    for (;eve_num<=count_room[room];eve_num++)
        eve[room][eve_num]=eve[room][eve_num+1];
    count_room[room]--;

}

void change_room(int room, int eve_num,int room2){
    eve[room2][++count_room[room2]] = eve[room][eve_num];
    eve[room2][count_room[room2]].room=room2;
    insertionSort(eve[room2],count_room[room2]);
    remove_event(room,eve_num);

}




/*AINDA POR VER*/
void sortMat(){
  int i,j,k=1,y = 1;
  for ( i = 1; i <= 10; i++)
    for ( j = 1; j <= count_room[i]; j++)
      if (eve[i][j].duration!=0){
        temp[k] = eve[i][j];
        k++;}

  insertionSort(temp,k);

  for (i=1;i<=k;i++){
    if (temp[i].duration!=0){
    y=1;
    printf("%s %s %s %d Sala%d %s\n*",temp[i].descripction,temp[i].date,
    temp[i].hour,temp[i].duration,temp[i].room,temp[i].member[0]);
    while (y<temp[i].count_members) printf(" %s",temp[i].member[y++]);
    printf("\n");
    }
  }
}


void remova_membro(int room, int eve_num,char s[]){
    int i,flag=0;
    for (i=1;i<=eve[room][eve_num].count_members;i++)
      if (strcmp(list[1],eve[room][eve_num].member[i])==0)
        flag=1;
    if (eve[room][eve_num].count_members>2){
      for (i=1;i!=eve[room][eve_num].count_members && strcmp(eve[room][eve_num].member[i],s)!=0;i++); /*Descobrir em que posição o membro esta*/
      if (i<eve[room][eve_num].count_members){
        for (;i<eve[room][eve_num].count_members;i++)
        strcpy(eve[room][eve_num].member[i],eve[room][eve_num].member[i+1]);
      eve[room][eve_num].count_members--;
      }
    }
    else if (flag==1)
        printf("Impossivel remover participante. Participante %s e o unico participante no evento %s.\n",
                eve[room][eve_num].member[1],eve[room][eve_num].descripction);
}

void adiciona_membro(int room, int eve_num,char s[]){
  int i,flag=0,auxd=0;
  if (eve[room][eve_num].count_members==4)
    printf("Impossivel adicionar participante. Evento %s ja tem 3 participantes.\n",eve[room][eve_num].descripction);
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
              eve[room][eve_num].duration,room,1)==1)
              remova_membro(room,eve_num,s);
      }
  }
}





/*MAIN PROGRAM*/
int main(){
  int room,eve_num,auxd;
  for (auxd=0;auxd != 11;auxd++) count_room[auxd]=0;
  while (1){
    input_work();
    if (comand!='a')
      auxd = search_eve(list[0]), room = auxd/1000,eve_num = auxd%1000;
    switch(comand){
      case 'a': /*Add an Event*/
        create_event();
        break;
      case 'l': /*Organiza Todos os eventos por ordem cornologica*/
        sortMat();
        break;
      case 's': /*Displays in sort all the events in one room*/
        print_eve(atoi(list[0]));
        break;
      case 'r': /*Retira um evento*/
        /*printf("room=%d & eve_num=%d",room,eve_num);*/
        if (room==0 && eve_num==0)
        printf("Evento %s inexistente.\n",list[0]);
        else
        remove_event(room,eve_num);
        break;
      case 'i': /*Troca o inicio de um evento*/
        if (room==0 && eve_num==0)
          printf("Evento %s inexistente.\n",list[0]);
        else{
          for (auxd=0;auxd<=eve[room][eve_num].count_members;auxd++)
            strcpy(list[auxd+5],eve[room][eve_num].member[auxd]);
          if (room_available(room,atoi(eve[room][eve_num].date),atoi(list[1]),
              eve[room][eve_num].duration,eve_num))
              printf("Impossivel agendar evento %s. Sala%d ocupada.\n",list[0],room);
          else if (member_available(atoi(eve[room][eve_num].date),atoi(list[1]),
              eve[room][eve_num].duration,room,0)==0){
                strcpy(eve[room][eve_num].hour,list[1]);
                insertionSort(eve[room],count_room[room]);}

        }
        break;
      case 't': /*Troca a duracao de um evento*/
      if (room==0 && eve_num==0)
        printf("Evento %s inexistente.\n",list[0]);
      else if (atoi(list[1])>=1 && atoi(list[1])<=MAX_DURATION
          && atoi(list[1])!=eve[room][eve_num].duration){
        for (auxd=0;auxd<=eve[room][eve_num].count_members;auxd++)
          strcpy(list[auxd+5],eve[room][eve_num].member[auxd]);
        if (room_available(room,atoi(eve[room][eve_num].date),atoi(eve[room][eve_num].hour),
            atoi(list[1]),eve_num))
            printf("Impossivel agendar evento %s. Sala%d ocupada.\n",list[0],room);
        else if (member_available(atoi(eve[room][eve_num].date),atoi(eve[room][eve_num].hour),
            atoi(list[1]),room,0)==0){
            eve[room][eve_num].duration=atoi(list[1]);
            insertionSort(eve[room],count_room[room]);}

          }
        break;
      case 'm': /*Troca a room de um evento*/
      if (room==0 && eve_num==0)
        printf("Evento %s inexistente.\n",list[0]);
      else{
        if (room!=atoi(list[1])){
          if (room_available(atoi(list[1]),atoi(eve[room][eve_num].date),atoi(eve[room][eve_num].hour),
              eve[room][eve_num].duration,0))
              printf("Impossivel agendar evento %s. Sala%d ocupada.\n",list[0],atoi(list[1]));
          else if (member_available(atoi(eve[room][eve_num].date),atoi(eve[room][eve_num].hour),
                  eve[room][eve_num].duration,atoi(list[1]),0)==0)
          change_room(room,eve_num,atoi(list[1]));}
      }
        break;
      case 'A': /*Adiciona um Membro a um evento*/
        if (room==0 && eve_num==0)
          printf("Evento %s inexistente.\n",list[0]);
        else{
          adiciona_membro(room,eve_num,list[1]);
        }
      break;
      case 'R': /*Remova um Membro a um evento*/
        if (room==0 && eve_num==0)
          printf("Evento %s inexistente.\n",list[0]);
        else
          remova_membro(room,eve_num,list[1]);
        break;
      case 'x': /*Termina o Programa*/
        exit(0);
        break;
    }
  }
  return 0;
}
