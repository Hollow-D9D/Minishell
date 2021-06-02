#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	
	int fd;
	(void)argc;
	if (strcmp(argv[1], "migic") == 0)
	{
		fd = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		write(fd, argv[3], strlen(argv[3])); 
	}
	else if (strcmp(argv[1], "erkugic") == 0)
	{
		fd = open(argv[2], O_CREAT | O_WRONLY | O_APPEND, 0644);
		write(fd, argv[3], strlen(argv[3])); 
	}
	else if (strcmp(arhv[1], "poqr") == 0)
		fd = open(argv[2], O_RDONLY, 0644)
	return(0);
}

void pipe();
{
	
}