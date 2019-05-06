
/*CONSTANTS*/
#define MAX_NOME 1024
#define MAX_EMAIL 512
#define MAX_PHONE 64
#define MAX_INPUT_LINE 568  /*Assuming that 63*9 is the limit of input*/

/*Receives the input and sends it to str_list*/
void input_work(){
  int auxd=0;
  char line[MAX_INPUT_LINE];
  for (auxd=0;auxd != 10;auxd++) strcpy(list[auxd],""); /*Puts the vector of strings "list" with "" */
  command=getchar();
  if (command!='x' && command!='l' && command!='\n'){
    getchar();
    fgets(line,MAX_INPUT_LINE,stdin);
    str_list(line);
  }
}


void add_contact(){

}

void list_contact(){

}

void search_contact(){

}

void delete_contact(){

}

void change_email(){

}

void search_email(){

}
