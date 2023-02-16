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
#include <sys/sem.h>


#define P(s) semop(s, &Pop, 1);
#define V(s) semop(s, &Vop, 1);

struct sembuf Pop;
struct sembuf Vop;

int main(){
    int semid, semid2, semid3, semid4, semid5;
    struct sembuf sops;
    union semun {
		int              val;    /* Value for SETVAL */
		struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
		unsigned short  *array;  /* Array for GETALL, SETALL */
		struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
	} setvalArg;

	setvalArg.val = 1;
    Pop.sem_num = 0;
	Pop.sem_op = -1;
	Pop.sem_flg = SEM_UNDO;

	Vop.sem_num = 0;
	Vop.sem_op = 1;
	Vop.sem_flg = SEM_UNDO;
    key_t key_for_p1 = ftok("/home/raushan/lab/operatingSysLab/6_semaphore_assign/p1.c", 1);
    semid= semget(key_for_p1, 1, IPC_CREAT | 0666);
    semctl(semid, 0, SETVAL, 1);
    key_t key_for_p2 = ftok("/home/raushan/lab/operatingSysLab/6_semaphore_assign/p2.c", 1);
    semid2= semget(key_for_p2, 1, IPC_CREAT | 0666);
    semctl(semid2, 0, SETVAL, 0);
    key_t key_for_p3 = ftok("/home/raushan/lab/operatingSysLab/6_semaphore_assign/p3.c", 1);
    semid3= semget(key_for_p3, 1, IPC_CREAT | 0666);
    semctl(semid3, 0, SETVAL, 0);
    key_t key_for_p4 = ftok("/home/raushan/lab/operatingSysLab/6_semaphore_assign/p4.c", 1);
    semid4= semget(key_for_p4, 1, IPC_CREAT | 0666);
    semctl(semid4, 0, SETVAL, 0);
    key_t key_for_p5 = ftok("/home/raushan/lab/operatingSysLab/6_semaphore_assign/p5.c", 1);
    semid5= semget(key_for_p5, 1, IPC_CREAT | 0666);
    semctl(semid5, 0, SETVAL, 0);

    
    while (1){
        P(semid); //Checking weather the first semaphore is free or not
        sleep(6);
        printf("I am p1\n");
        V(semid2); //freeing the second semaphore

    }
    semctl(semid, 0, IPC_RMID, 0);
    return 0;
}

