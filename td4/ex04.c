#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/times.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	
	char buffer[32];
	struct tms start, end;
	int dt;
	
	if(argc > 1)
	{
		sprintf(buffer,"ls -R %s", argv[1]);
	
		pid_t pid = fork();
	
		
		if(pid == 0)
		{
			times(&start);
			system(buffer);
			times(&end);
			dt = (end.tms_cutime  - start.tms_cutime) / sysconf(_SC_CLK_TCK) ;
			exit(dt);
		}
		else
		{
			int i;
			wait(&i);
			
			printf("temps ecoules: %d\n", i);
		}
	}
	return 0;
}
