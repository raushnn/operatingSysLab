/*
* @author Raushan k. Singh (raushan026@gmail.com)
* @task Pass command line argument to executable 
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    
    for (int i=1; i<argc; i++){
        if (fork()==0){
            if (i+1<argc && argv[i+1][0]=='-'){
                char *param[]={argv[i],argv[i+1], NULL};
                execvp(argv[i], param);
                ++i;
            }
            else{
                execvp(argv[i], NULL);
                ++i;
            }
            printf("%d", getpid());
        }
        wait(NULL);

    }
    return 0;
}
