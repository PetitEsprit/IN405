#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	int buffer[2] = {0};
	int fd;
	mkfifo("/tmp/fifo", 0666);
	
	pid_t fils = fork();
	
	if(fils < 0){perror("Fork error !\n");}
	else if(fils == 0)
	{
		fd = open("/tmp/fifo", O_WRONLY);
		int n[2] = {9,53};
		write(fd, n, sizeof(int));
		write(fd, n+1, sizeof(int));
		close(fd);
	}
	else
	{
		fd = open("/tmp/fifo", O_RDONLY);
		read(fd, buffer, sizeof(int));
		read(fd, buffer+1, sizeof(int));
		close(fd);
		printf("Message du fils: %d %d\n", buffer[0] , buffer[1]);
		wait(NULL);
		unlink("/tmp/fifo");
	}
	
	return 0;
}
