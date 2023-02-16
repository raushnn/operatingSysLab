#include <stdio.h>
#include <math.h>
#include <sys/types.h> //for wait(), kill()
#include <unistd.h>    //for fork()
#include <signal.h>    //for signal and kill
#include <stdlib.h>
#include <sys/ipc.h>  //for shmget(), shmctl()
#include <sys/wait.h> //for wait()
#include <sys/shm.h>  //for shmget(), shmctl()
#include <errno.h>    //for perror
#include <sys/sem.h>

int shmid;

struct task
{

  int data[100];
  int size;
  pid_t worker_pid;
  int status;
};

typedef void (*sighandler_t)(int);

void releaseSHM(int signum)
{
  if (signum == SIGINT)
  {
    struct task *solve = shmat(shmid, NULL, 0);
    solve->status = -1;
    printf("Server process terminated by keypress\n");
    exit(0);
  }
  int status;
  // int shmctl(int shmid, int cmd, struct shmid_ds *buf); /* Read the manual for shmctl() */
  status = shmctl(shmid, IPC_RMID, NULL); /* IPC_RMID is the command for destroying the shared memory*/
  status = kill(0, SIGKILL);
}

int main(int argc, char *argv[])
{
  int i, status, key;
  sighandler_t shandler;
  shandler = signal(SIGINT, releaseSHM);
  key = ftok("/home/raushan/lab/operatingSysLab/5_shared_mem_with_non_related_process/server.c", 1);
  shmid = shmget(key, sizeof(struct task), 0666 | IPC_CREAT);

  struct task *s = shmat(shmid, NULL, 0);
  s->status = 0;
  while (1)
  {
    printf("\nGenerating random numbers\n");
    int n = rand() % 25;
    s->size = n;
    for (int i = 0; i < n; i++)
    {
      s->data[i] = rand() % 101;
    }
    printf("Numbers generated by server process : \n");
    for (int i = 0; i < n; i++)
    {
      printf("%d ", s->data[i]);
    }
    printf("\n\n");
    s->status = 1;
    printf("Waiting for worker process to sort the data\n\n");
    while (s->status != 3)
    {
      sleep(1);
    }
    printf("Array sorted by worker process with p_id %d : ", s->worker_pid);
    for (int i = 0; i < n; i++)
    {
      printf("%d ", s->data[i]);
    }
    printf("\n\n");
    printf("Process completed\n");
    s->status = 4;

    sleep(1);
  }
  return 0;
}
