#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	// l_type, l_whence, l_start, l_len, l+pid
	struct flock fl = {F_WRLCK, SEEK_SET, 0, 0, 0};		// WRLCK
	int fd;

	fl.l_pid = getpid();
	if (argc > 1)
		fl.l_type = F_RDLCK;		// RDLCK
	if ((fd = open("lockdemo.c", O_RDWR)) == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}

	printf("Press <Enter> to try to get lock: ");
	getchar();
	printf("Trying to get lock...\n");

	if (fcntl(fd, F_SETLKW, &fl) == -1)
	{
		perror("fcntl");
		exit(EXIT_FAILURE);
	}
	printf("got lock\n");
	printf("Press <Enter> to release lock: ");
	getchar();

	fl.l_type = F_UNLCK;	// set to unlock same region

	if (fcntl(fd, F_SETLK, &fl) == -1)
	{
		perror("fcntl");
		exit(EXIT_FAILURE);
	}

	printf("Unlocked.\n");
	close(fd);

	return 0;
}
