#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int pid;
	int status;

	pid = fork();
	printf("%d\n", pid);
	if(pid)
		waitpid(pid, &status, WUNTRACED);
		fork();
		printf("%d\n", pid);
}
