#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	char buffer[16];
	int fd;
	mkfifo("/tmp/fifo", 0666);
	
	pid_t fils = fork();
	
	if(fils < 0){perror("Fork error !\n");}
	else if(fils == 0)
	{
		fd = open("/tmp/fifo", O_WRONLY);
		char msg[] = "Hello Papa !";
		write(fd, msg, sizeof(msg));
		close(fd);
	}
	else
	{
		fd = open("/tmp/fifo", O_RDONLY);
		read(fd, buffer, 16);
		close(fd);
		printf("Message du fils: %s\n", buffer);
		wait(NULL);
		unlink("/tmp/fifo");
	}
	
	return 0;
}
