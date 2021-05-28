#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
// void migic(char hay)

int main(int argc, char **argv)
{
	
	int fd;
	(void)argc;
	if(strcmp(argv[1], "migic") == 0)
	{
		fd = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		write(fd, argv[3], strlen(argv[3])); 
	}
	else if(strcmp(argv[1], "erkugic") == 0)
	{
		fd = open(argv[2], O_CREAT | O_WRONLY | O_APPEND, 0644);
		write(fd, argv[3], strlen(argv[3])); 
	}		
	return(0);
}

