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
    shmid= shmget(IPC_PRIVATE, sizeof(int), 0666 | IPC_CREAT);
    int *data= (int *)shmat(shmid, NULL, 0);
    int n= atoi(argv[1]);
    while (n){

        int r= rand();
        r%=35;
        printf("The number generated is %d\n", r);
        *data= r;
        // printf("data %d\n", data);
        if(fork()==0){
            data=  (int *)shmat(shmid, NULL, 0);
            int val= *data;
            int k=2;
            
            int ans=0;
            while (val)
            {
                int count=0;
                for(int i=2; i*i<= k; i++){
                    if (k%i==0){
                        count++;
                        break;
                        }
                    }
                    if(count==0){
                        val--;
                        ans= k;
                    }
                    k+=1;
            }
            
            printf("The %dth prime number is %d\n",*data, ans);
            shmdt(data);
            exit(EXIT_SUCCESS);
        }
        wait(NULL);
        // printf("%d\n", r);
        n--;
    }
    wait(NULL);
    shmctl(shmid, IPC_RMID, NULL);
    
    return 0;
}