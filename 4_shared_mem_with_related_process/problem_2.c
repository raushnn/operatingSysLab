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

#define ROWS 5
#define COLS 3
#define ROWS2 3
#define COLS2 5


int main(int argc, char *argv[]){
    int shmid;
    int mat1[ROWS][COLS] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12},
        {13, 14, 15}
    };
    int mat2[ROWS2][COLS2] = {
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25},
        {26, 27, 28, 29, 30}
    };

    //0666 means read and write permission for owner group and others
    shmid= shmget(IPC_PRIVATE, sizeof(int[ROWS][COLS]), 0666 | IPC_CREAT);
    int (*array)[COLS2]= (int(*)[COLS2]) shmat(shmid, NULL, 0);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS2; j++) {
            if (fork()==0){
                // printf("I'm the child_%d which is calculating multiplication for index array[%d][%d]\n",getpid(), i, j);
                array[i][j] = 0;
                for (int k = 0; k < ROWS2; k++) {
                    array[i][j] += mat1[i][k] * mat2[k][j];
                    }
                // printf("%d\n", array[i][j]);
                shmdt(array);
                exit(EXIT_SUCCESS);
            }
        }
        }
    //wait returns -1 one possible error can be when calling process has no children which is indicated by errno ECHILD
    while (1){
        if (wait(NULL)==-1){
            if (errno==ECHILD){
                break;
            }
        }
    }
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS2; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
    // shmctl(shmid, IPC_RMID, NULL);

    return 0;
}