#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>

#define P(s) semop(s, &Pop, 1);
#define V(s) semop(s, &Vop, 1);

struct sembuf Pop;
struct sembuf Vop;

int main()
{
    int semid3, semid2;
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

    key_t key_for_p3 = ftok("/home/raushan/lab/operatingSysLab/6_semaphore_assign/p3.c", 1);
    semid3 = semget(key_for_p3, 1, IPC_CREAT | 0666);
    key_t key_for_p2 = ftok("/home/raushan/lab/operatingSysLab/6_semaphore_assign/p2.c", 1);
    semid2 = semget(key_for_p2, 1, IPC_CREAT | 0666);

    while (1) {
        
        P(semid3);
        sleep(6);
        printf("I am p3 \n");
        V(semid2);
    }
    return 0;
}