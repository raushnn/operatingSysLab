#include <stdio.h>
#include <math.h>
#include <sys/types.h> //for wait(), kill()
#include <unistd.h> //for fork()
#include <signal.h> //for signal and kill
#include <stdlib.h>
#include <sys/ipc.h> //for shmget(), shmctl()
#include <sys/wait.h> //for wait()
#include <sys/shm.h> //for shmget(), shmctl()
#include <errno.h> //for perror

int main(int argc, char *argv[]){
    int shmid;
    int rows = 10;
    int column=10;
    shmid= shmget(IPC_PRIVATE, sizeof(int[rows][column]), 0666 | IPC_CREAT);
    int (*array)[column]= (int(*)[column]) shmat(shmid, NULL, 0);
    
    if (fork()==0){

    }
    return 0;
}