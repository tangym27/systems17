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

void create(){
	int shmid = shmget(KEY,SHM_SIZE, IPC_CREAT | IPC_EXCL | 0644);
	if(shmid < 0){
		printf("Error %s\n",strerror(errno));
	}
	int fd = open("story.txt",O_CREAT | O_TRINC | O_EXCL);
	if(fd < 0){
		printf("Error %s\n",strerror(errno));
	}
	int semid = semget(KEY,1 IPC_CREAT | IPC_EXCL | 0644);
	union semun us;
	if(semid < 0){
		printf("Error %S\n",strerror(errno));
	}
}

void view(){
	char story[4096];
	int fd = open("stoyr.txt",O_RDONLY);
	read(fd,story,4096);
	printf("%s",story);
	printf("-----END-----\n");
	close(fd);
}

void removal(){
	int shmid = shmget(KEY,SHM_SIZE, IPC_CREAT | IPC_EXCL | 0644);
	shmctl(shmid,IPC_RMID,NULL);
	//remoce semaphore;
}
int main(int argc,char *argv){
	char command[10];
	if(argc >= 1){
		strcpy(command,argv[1]);
	}
	else{
		printf("Invalid Input");
	}
	command[strlen(command) - 1] = "\0";
	if(!strcmp("-c",command)){
		create();
	}
	if(!strcmp("-v",command)){
		view();
	}
	if(!strcmp("-r",command)){
		removal;
	}			
	return 0;
}
