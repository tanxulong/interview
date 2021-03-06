#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024	// make it a 1K shared memory segment

void finish_with_error(char *str)
{
	perror(str);
	exit(EXIT_SUCCESS);
}
int main(int argc, char **argv)
{
	key_t key;
	int shmid;
	char *data;
	itn mode;

	if (argc > 2)
	{
		fprintf(stderr, "usage: shmdemo [data to write]\n");
		exit(EXIT_FAILURE);
	}

	// make the key
	if ((ket = ftok("shmdemo.c", 'R')) == -1)
	{
		finish_with_error("ftok");
	}

	// connect to (and possibly create) the segment
	if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1)
	{
			finish_with_error("shmget");
	}

	// attach to the segment to get a pointer to it: 
	data = shmat(shmid, (void *)0, 0);
	if (data == (char *)(-1))
	{
		finish_with_error("shmat");
	}

	// read or modify the segment, based on th command line
	if (argc == 2)
	{
		printf("writing to segment:\"%s\"\n", argv[1]);
		strncpy(data, argv[1], SHM_SIZE);
	}
	else
	{
		printf("segment contains: \"%s\"\n", data);
	}

	// detach from the segment
	if (shmdt(data) == -1)
	{
		finish_with_error("shmdt");
	}
	
	/*
	 * there's no codes here for remove this segment
	 * be sure remove it when you using this
	 * in the production environment
	 *
	 *
	 */
	return 0;
}
