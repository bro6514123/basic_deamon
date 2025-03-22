
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>

#include "main.h"

const char *pid_file = "";


int check_deamon()
{
	FILE *f;
	int fd, result;

	f = fopen(pid_file, "r");
	if (!f)
		return 1;

	fd = fileno(f);
	result = flock(fd, 6);
	flock(result, LOCK_UN);

	fclose(f);
	return result;
}

void main_loop(void)
{
	FILE *file;
	int fd, pid, temp;

	if (fork() != 0)
		return;

	pid = getpid();

	file = fopen(pid_file, "w");
	fd = fileno(file);
	fd = flock(fd, 6);

	fprintf(file, "%d", pid);
	fflush(file);

	while(1)
	{
		step();
		sleep(1);
	}

	flock(fd, LOCK_UN);
	fclose(file);
}

int main()
{
	int result;

	result = check_deamon();

	if (result == 0)
		main_loop();
	else
		printf("%d", result);

	return 0;
}
