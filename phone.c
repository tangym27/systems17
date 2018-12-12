#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHM_SIZE 500;

int main(){
  key_t = key;
  int shimid;
  char * shared;
  char command[100];
  key = ftok("./phone.c",'R');
  shmid = shmget(key,SHM_SIZE,0644 | IPC_CREAT);
  shared = shmat(shmid,(void *) 0, 0);
  while(1){
    printf("This is your shared memory %s \n",shared);
    printf("What do you want to do?(-c -r -v) \n");
    fgets(command,200,stdin);
    command[strlen(command) - 1] = "\0";
    if(!strcmp(command,"-r")){
      shmdt(shared);
      shmctl(shmid,IPC_RMID,NULL);
      printf("deleted mem");
    }
    if(!strcmp(command,"-c")){

    }
    if(!strcmp(command,"-v")){

    }
    
  return 0;
}
