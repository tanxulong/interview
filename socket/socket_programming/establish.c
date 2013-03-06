/*
 * Code too establish a socket;
 */
int establish(unsigned short port)
{
	char myName[MAXHOSTNAME + 1];
	int s;
	struct sockaddr_in sa;
	struct hostent *hp;

	memset(&sa, 0, sizeof(struct sockaddr_in)); // clear our address
	gethostname(myname, MAXHOSTNAME); // who are we?
	hp = gethostbyname(myname);	// get our address info
	if (hp == NULL)	// don't exist
		return (-1);
	sa.sin_family = hp->h_addrtype;	// host address
	sa.sin_port = htons(port);	// port number
	if ((s = socket(AF_INET, SOCKET_STREAM, 0)) < 0) // create socket
		return (-1);
	if (bind(s, &sa, sizeof(struct sockaddr_in)) < 0)
	{
		close(s);
		return (-1); // bind address to socket
	}
	listen(s, 3);	// max # of queued connects
	return (s);
}
