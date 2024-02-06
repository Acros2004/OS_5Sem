#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sched.h>


int main()
{
	pid_t pid = getpid();
	void* m = malloc(256*1024*1024);
	int size = 256000000 / 4;
	printf("PID = %d\n", pid);
	printf("m = %p\n", m);

	int* arr = (int*)m;
	for (int i = 0; i < size; i++)
		arr[i] = i;

	sleep(50);
	exit(0);
}