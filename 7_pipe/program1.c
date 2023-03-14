#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct myStruct
{
        int a;
        double b;
        char c;
} s1;

int pipefds[2]; /* to store the file descriptors pipe() returns */
int flag;       /* to store what system calls (pipe/read/write) return */
char buf[100];  /* see later how it is used in read() to store the data to be read */
char type;

void enqueue(void *p)
{
        scanf("%c", &type);
        if (type == '1')
        {       int *a= (int*)p;
                write(pipefds[1], &type, sizeof(char));
                write(pipefds[1], &a, sizeof(int));
        }
        else if (type == '2')
        {       double *a= (double*)p;
                write(pipefds[1], &type, sizeof(char));
                write(pipefds[1], &a, sizeof(double));
        }
        else if (type == '3')
        {       char *a= (char*)p;
                write(pipefds[1], &type, sizeof(char));
                write(pipefds[1], &a, sizeof(char));
        }
        else if (type == '4')
        {       
                s1 *a= (s1*)p;
                write(pipefds[1], &type, sizeof(char));
                write(pipefds[1], &a, sizeof(s1));
        }
}


void deque()
{
        read(pipefds[0], &type, sizeof(char));
        if (type == '3')
        {
                read(pipefds[0], buf, sizeof(char));
                char *data = (char *)buf;
                printf("Dequed data : %c\n", data[0]);
        }
        else if (type == '1')
        {
                read(pipefds[0], buf, sizeof(int));
                int *data = (int *)buf;
                printf("Dequed data : %d\n", data[0]);
        }
        else if (type == '2')
        {
                read(pipefds[0], buf, sizeof(double));
                double *data = (double *)buf;
                printf("Dequed data : %f\n", data[0]);
        }
        else if (type == '4')
        {
                read(pipefds[0], buf, sizeof(s1));
                s1 *data = (s1 *)buf;
                printf("\nPrinting value of struct\n");
                printf(" %d\n", data->a);
                printf(" %f\n", data->b);
                printf(" %c\n", data->c);
        }
}

int main()
{
        flag = pipe(pipefds);

        if (flag == -1)
        {
                perror("pipe() failed:");
                exit(1);
        }

        int a = 4, b = 9;
        double c = 22.32;
        char x = 'a';
        s1 t1;

        t1.a = 44;
        t1.b = 19.3445;
        t1.c = 'k';

        //now you can call enqueue and dequeue depending upon need;
        enqueue(&t1);
        deque();
        // enqueue(x);
        // deque();
        
        return 0;
}