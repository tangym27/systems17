#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#define KEY 199
#define KEY2 271


int main() {
  int sem_id=semget(KEY,1,0644);
  int * count;
  struct sembuf sem1;

// DOWN THE SEMPAHORE
  sem1.sem_flg=SEM_UNDO;
  sem1.sem_num=0;
  sem1.sem_op=-1;
  semop(sem_id,&sem1,1);

  int fd=open("story.txt",O_RDWR | O_APPEND,0644);

  if (fd==-1) { //in case theres an error, restart/reup everything
    printf("Oh no! There was an error when opening: %s\n",strerror(errno));
    sem1.sem_op=1;
    semop(sem_id,&sem1,1);
    return 0;
  }

  int shmid=shmget(KEY2,sizeof(int),IPC_CREAT | IPC_EXCL | 0644);
  char last_line[256];
  if (shmid==-1) {//bc of excl
    shmid=shmget(KEY2,sizeof(int),IPC_CREAT | 0644); //re shmid!
    count=shmat(shmid,0,0);

    //start reading at the end
    lseek(fd,-1*(*count),SEEK_END);
    read(fd,last_line,*count);
    printf("Last line:\n%s",last_line);
  }
  else { // very first time!
    printf("Last line: N/A\n");
    count=shmat(shmid,0,0);
  }

// WRITING TO THE FILE
  char message[256];
  printf("What would you like the next line to be? ");
  fgets(message,256,stdin);
  *count=strlen(message);
  shmdt(count);

  write(fd,message,strlen(message));
  close(fd);

// UP THE SEMAPHORE!
  sem1.sem_op=1;
  semop(sem_id,&sem1,1);

  return 0;
}
