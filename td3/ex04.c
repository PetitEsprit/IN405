#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>

int main(int ac, char **av)
{
	if(ac == 2 )
	{
		int i = 0;
		int fd = open(av[1], O_RDWR);
		struct stat fdstat;
		if(fstat(fd, &fdstat) < 0) perror("Error stat\n");
		char *fstr = mmap(NULL, fdstat.st_size, PROT_READ |PROT_WRITE, MAP_SHARED, fd, 0);
		
		if(fstr == NULL) printf("Error mmap\n");
		
		while(fstr[i] != '\0')
		{
			if(fstr[i]=='a' | fstr[i]=='e' | fstr[i]=='i' |
			fstr[i]=='o' | fstr[i]=='u' | fstr[i]=='y' )
			{
				fstr[i] = '*';
			}
			i++;
		}
		
		msync(fstr, fdstat.st_size, MS_SYNC);
		munmap(fstr, fdstat.st_size);
		close(fd);
	}
	else
	{
		printf("Invalid Number of Arguments !\n");
	}
	return 0;
}
