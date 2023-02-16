#include <stdio.h>
#include <unistd.h> /* for fork() */
#include <sys/wait.h> /* for wait() */
#include <sys/types.h> /* for wait() kill(2)*/
#include <sys/ipc.h> /* for shmget() shmctl() */
#include <sys/shm.h> /* for shmget() shmctl() */
#include <signal.h> /* for signal(2) kill(2) */
#include <errno.h> /* for perror */
#include <stdlib.h>

int shmid;

struct task {
  int data[100]; 
  int size;
  pid_t worker_pid; 
  int status; 
}task;


int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main(){
  int i, shm_key;
  shm_key=ftok("/home/raushan/lab/operatingSysLab/5_shared_mem_with_non_related_process/server.c", 1);
  shmid=shmget(shm_key, sizeof(struct task), 0666|IPC_CREAT);

  struct task *s=shmat(shmid, NULL, 0);
  while(1){
    
    while(s->status!=1);
    s->status=2;
    qsort(s->data, s->size, sizeof(int), cmpfunc);
    s->worker_pid=getpid();
    s->status=3;
  }
  if(s->status==-1){
    printf("Worker process with pid %d terminated", getpid());
    exit(0);
  }

  return 0;
}
