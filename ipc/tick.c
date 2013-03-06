// tick.c using FIFO
/*
 * tick will block on the open() if there is no one writing
 * to the FIFO.As soon as someone opens the FIFO for writing,
 * tick will spring to life
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

	/*if(mknod(FIFO_NAME, S_IFIFO | S_IRWXU | S_IRWXG | S_IRWXO, 0) == -1)
	{
		perror("mknod");
		exit(EXIT_FAILURE);
	}
	else
		printf("mknod successed\n");
	*/
	printf("waiting for writers...\n");
	fd = open(FIFO_NAME, O_RDONLY);

	do{
		if ((num = read(fd, s, 300)) == -1)
		{
			perror("read");
		}
		else
		{
			s[num] = '\0';
			printf("tick: read %d bytes: \"%s\"\n", num, s);
		}
	} while (num > 0);

	return 0;
}
