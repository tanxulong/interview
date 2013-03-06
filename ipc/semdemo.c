/*
 * this program creates the semaphore if necessary,
 * and performs some pretend file locking on it in a
 * demo very much like that in the File Locking document
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define MAX_RETRIES 10

union semun
{
	int val;
	struct semid_ds *buf;
	ushort *array;
};

/*
 * initsem() -- more-than-inspired by W. Richard Stevens' 
 * UNIX Network Programming 2nd edition, volume 2, 
 * lockvsem.c page 295
 */

int initsem(key_t key, int nsems)	// key from ftok()
{
	int i;
	union semun arg;
	struct semid_ds buf;
	struct sembuf sb;
	int semid;

	semid = semget(key, nsems, IPC_CREAT | IPC_EXCL | 0666);

	if (semid >= 0)		// we got it first
	{
		sb.sem_op = 1;	
		sb.sem_flg =0;
		arg.val = 1;

		printf("press return\n");
		getchar();

		for(sb.sem_num=0; sb.sem_num < nsems; sb.sem_num++)
		{
			/*
			 * do a semop() to "free" the semaphores.
			 * this sets the sem_otime field,as needed below
			 */
			int e = errno;
			semctl(semid, 0, IPC_RMID);	// clean up
			errno = e;
			return -1;		// error, check errno
		}
	}
	else if (errno == EEXIST)	// Someone else got it first
	{
		int ready = 0;

		semid = semget(key, nsems, 0);	// get the id
		if (semid < 0)
			return semid;	// error, check errno

		// wait for other process to initialize the semaphore:
		arg.buf = &buf;
		for ( i = 0; i < MAX_RETRIES && ! ready; i++)
		{
			semctl(semid, nsems-1, IPC_STAT, arg);
			if (arg.buf->sem_otime != 0)
			{
				ready = 1;
			}
			else
			{
				sleep(1);
			}
		}
		if (!ready)
		{
			errno = ETIME;
			return -1;
		}
	}
	else
	{
		return semid;	// error, check errno
	}
	return semid;
}

int main(void)
{
	key_t key;
	int semid;
	struct sembuf sb;

	sb.sem_num = 0;
	sb.sem_op = -1;		// set to allocate resource
	sb.sem_flg = SEM_UNDO;

	if ((key = ftok("semdemo.c", 'J')) == -1)
	{
		perror("ftok");
		exit(EXIT_FAILURE);
	}

	// grab the semaphore set created by seminit.c
	if ((semid = initsem(key, 1)) == -1)
	{
		perror("initsem FAILED");
		exit(EXIT_FAILURE);
	}

	printf("Press return to lock: ");
	getchar();
	printf("Trying to lock...\n");

	if (semop(semid, &sb, 1) == -1)
	{
		perror("semop");
		exit(EXIT_FAILURE);
	}

	printf("Locked.\n");
	printf("Press return to unlock: ");
	getchar();

	sb.sem_op = 1; // free resource
	if (semop(semid, &sb, 1) == -1)
	{
		perror("semop");
		exit(EXIT_FAILURE);
	}
	printf("Unlocked");
	return 0;
}




