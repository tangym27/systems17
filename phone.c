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
#define KEY 0xRINGING

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo*_buf;
}

int main(){
  int semid = semget(KEY,1,IPC_CREAT | IPC_EXCL | 0644);
  return 0;
}
