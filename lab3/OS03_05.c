#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void cycle(int counter, char* message)
{
    for (int i = 1; i <= counter; ++i)
    {
        printf("%d. PID = %d [%s]\n", i, getpid(), message);
        sleep(2);
    }
}


int main()
{

    pid_t pid;
    switch (pid = fork())
    {
    case -1: perror("[ERROR] Fork() returned -1");      
             exit(-1);
    case  0: cycle(50, "OS03_05-1");                  
             exit(0);
    default: printf("[INFO] default = %d\n", pid);          
             cycle(100, "OS03_05");
             wait(0);                // ожидается завершение дочернего процесса
    }
    exit(0);
}

// Найти форкнутые процессы: ps -A 