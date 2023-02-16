/*
 * @Author Raushan K. Singh
 * Write a complete, user-friendly, well-documented and nicely-indented C
 * program which when executed as "./a.out executable1 executable2 ...
 * executableN" creates N child processes where the 1st child process 1st
 * executes the 1st executable file (given by executable1). 2nd executes the 2nd
 * executable file (given by executable2) and so on.
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    // char *const param[]= {"-a"};
    for (int i=1; i<argc; i++){
        if (fork()==0){
            execvp(argv[i], NULL);
        }
        wait(NULL);
    }
    return 0;
}
