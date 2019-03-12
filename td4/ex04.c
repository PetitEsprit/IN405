#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/times.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	
	char buffer[124];
	struct tms t;
	double dt;
	
	if(argc > 1)
	{
		sprintf(buffer,"ls -R %s", argv[1]);
		
		system(buffer);
		times(&t);
		
		dt = (double)(t.tms_cutime  + t.tms_cstime) / sysconf(_SC_CLK_TCK);
		printf("temps ecoules: %lf\n",  dt);
		
	}
	return 0;
}
