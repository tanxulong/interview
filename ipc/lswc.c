// implement "ls | wc -l" in c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int pfds[2];

	pipe(pfds);

	if (!fork())
	{
		close(1);		// close normal stdout
		dup(pfds[1]);	// make stdout same pfds[1]
		close(pfds[0]);	// we don't need this
		execlp("wc", "wc", "-l", NULL);
	}
	else
	{
		close(0);		// close normal stdin
		dup(pfds[0]);	// make stdin same as pfds[0]
		close(1);		// we don't need this
		execlp("wc", "wc", "-l", NULL);
	}

	return 0;
}
