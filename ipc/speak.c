// Speak.c using FIFO
/*
 * Speak create the FIFO, then try to open() it.
 * open() call will block until some other process opens
 * the other end of the pipe for reading
 * that process is tick
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>

#define FIFO_NAME "american_maid"

int main(void)
{
	char s[300];
	int num, fd;

	//assert(mknod(FIFO_NAME, S_IFIFO | 0644, 0) == 0);
	if (mknod(FIFO_NAME, S_IFIFO | S_IRWXU | S_IRWXG | S_IRWXO, 0) == -1)
	{
		perror("mknod");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("mknod successed\n");
	}

	printf("waiting for readers...\n");
	fd = open(FIFO_NAME, O_WRONLY);
	printf("got a reader -- type some stuff\n");
	while (gets(s), !feof(stdin))
	{
		if ((num = write(fd, s, strlen(s))) == -1)
			perror("write");
		else
			printf("speak: wrote %d bytes\n", num);
	}
	return 0;
}
