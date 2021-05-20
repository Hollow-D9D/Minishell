#include <stdio.h>

typedef	struct	s_process
{
	char	*pr; //process name
	char	*args; //arguments
	int		fd[2]; //input output for pipe
	int		rtnv; //process return value
}				t_process;

int main(void)
{
	int fd[2];
	char *args;
	int rtnv;
	t_process *suka;

	suka = malloc(sizeof(suka) * 6);
	suka[5] = 0;
	for(int i = 0; i < 6; i++)
	{
		suka[i].rtnv = i;
		printf("%d\n", suka[i].rtnv);
	}
	printf("%lu\n", sizeof(rtnv));
	printf("%lu\n", sizeof(t_process));
	return 0;
}