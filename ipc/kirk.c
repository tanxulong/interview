#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msgbuf
{
	long mtype;
	char mtext[200];
};

int main(void)
{
	struct my_msgbuf buf;
	int msqid;
	key_t key;

	if ((key = ftok("kirk.c", 'B')) == -1)
	{
		perror("ftok");
		exit(EXIT_FAILURE);
	}

	if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1)
	{
		perror("msgget");
		exit(EXIT_FAILURE);
	}

	printf("Enter lines of text, ^D to quit:\n");

	buf.mtype = 1;	// we don't really care in this case

	while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL)
	{
		int len = strlen(buf.mtext);

		// ditch newline at end, if it exists
		if (buf.mtext[len - 1] == '\n') 
			buf.mtext[len - 1] = '\0';
		if (msgsnd(msqid, &buf, len+1, 0) == -1)	// _1 for '\0'
			perror("msgsnd");
	}

	if (msgctl(msqid, IPC_RMID, NULL) == -1)
	{
		perror("msgctl");
		exit(EXIT_FAILURE);
	}

	return 0;
}

