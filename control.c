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
#include <fcntl.h>

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *_buf;
}
int main(){

}
