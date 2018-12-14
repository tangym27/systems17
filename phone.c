#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno>
#include <sys/sem.h>

#define SHM_SIZE 500;

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo*_buf;
}

int main(){
  key_t = key;
  int shimid;
  char * shared;
  char command[100];
  key = ftok("./phone.c",'R');
  shmid = shmget(key,SHM_SIZE,0644 | IPC_CREAT);
  shared = shmat(shmid,(void *) 0, 0);
  return 0;
}
