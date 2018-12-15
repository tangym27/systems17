#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/shm.h>
#define KEY 314159
#define SHM_KEY 38


void create(){
  printf("You have chosen to CREATE the story\n");
  union semun semaphore;
  int sem_id=semget(KEY,1,IPC_CREAT | IPC_EXCL | 0600);
  if (sem_id>=0) {
    semaphore.val=1;
    semctl(sem_id,0,SETVAL,semaphore.val);
    int fd=open("story.txt",O_CREAT | O_TRUNC,0644);
    if (fd == -1){
      printf("Oh no! Error in opening: %s\n", strerror(errno));
      return;
    }
    //printf("fd is %d\n",fd );
    close(fd);
  }
  else{
    printf("Already created. Try running ./client or ./control -v\n");
  }
}

void view(){
  printf("You have chosen to VIEW the story:\n");
  int fd = open("story.txt", O_RDONLY);
  if (fd == -1){
    printf("Oh no! Error in opening: %s\n", strerror(errno));
    return;
  }
  char * file = calloc(2056, sizeof(char));
  int last = read(fd, file, 2056);
  if (last == -1){
    printf("Oh no! Error in reading: %s\n", strerror(errno));
    return;
  }
  char* text = strrchr(file, '\n');
  //reset for future use
  if (text){
     *text = 0;
   }
  printf("%s\n", file);

  close(fd);
  return;
}

void delete(){
  printf("You have chosen to REMOVE the story\n");
  remove("story.txt");
  int shmid = shmget(KEY, 100, 0);
  shmctl(shmid, IPC_RMID, NULL);
  int semid = semget(KEY, 1, 0);
  semctl(semid, 0, IPC_RMID);
  printf("Removed!\n");
}

int main(int argc, char * argv[]) {
  union semun {
    int val;
    struct semid_ds *buf;
    unsigned short * array;
    struct seminfo * __buf;
  } semaphore;
  int sem_id;

  if (argc==2) {
    if (!strcmp(argv[1],"-c")) {
      create();
    }
    else if (!strcmp(argv[1],"-v")) {
      view();
    }
    else if (!strcmp(argv[1],"-r")) {
      delete();
    }
    else
      printf("Oh no! Your input was wrong. Try ./control -c or ./control -v or ./control -r\n");
  }
  else{
    printf("Oh no! Your input was wrong. Try ./control -c or ./control -v or ./control -r\n");
  }

  return 0;
}
