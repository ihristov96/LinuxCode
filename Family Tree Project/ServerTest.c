#include <stdio.h>
#include <sys/un.h> //sockaddr_un
#include <sys/socket.h> //socket, PF_LOCAL,SOCK_STREAM

#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_THREADS     5
int server (void* client_socket_fd)
{
	int client_socket = (int)client_socket_fd;
	while (1) 
	{
		int length;
		char* text;
		/* First, read the length of the text message from the socket. If
		read returns zero, the client closed the connection. */
		if (read (client_socket, &length, sizeof (length)) == 0)return 0;
		/* Allocate a buffer to hold the text.*/
		text = (char*) malloc (length);
		/* Read the text itself, and print it.
		*/
		
		read (client_socket, text, length);
		printf ("%s\n", text);
		/* Free the buffer. */
		free (text);
		/* If the client sent the message "quit," we're all done.*/
		if (!strcmp (text, "quit"))
		return 1;
	}
	pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
	pthread_t threads[NUM_THREADS];
	int t = 0;
	int rc = 0;
	const char* const socket_name = argv[1];
	int socket_fd;

	struct sockaddr_un name;

	int client_sent_quit_message;
	//Create a socket
	socket_fd = socket (PF_LOCAL, SOCK_STREAM, 0);
	
	name.sun_family = AF_LOCAL;
	//Copy socket name(path) to sun_path
	strcpy (name.sun_path, socket_name);
	
	bind (socket_fd, &name, SUN_LEN (&name));

	//Listen for connections
	listen (socket_fd, 5);

	/* Repeatedly accept connections, spinning off one server() to deal
	with each client. Continue until a client sends a "quit"
	message.
	*/
	do {

		struct sockaddr_un client_name;
		socklen_t client_name_len;
		int client_socket_fd;
		/* Accept a connection.
		*/
		client_socket_fd = accept (socket_fd, &client_name, &client_name_len);
		/* Handle the connection.
		*/
		rc = pthread_create(&threads[t], NULL, server, (void *)client_socket_fd);
        if (rc)
        {
           printf("ERROR; return code from pthread_create() is %d\n", rc);
           exit(-1);
        }
        t++;

		//client_sent_quit_message = server (client_socket_fd);
		/* Close our end of the connection.
		*/
		//close (client_socket_fd);
	}
	while (!client_sent_quit_message);
	/* Remove the socket file.*/
	close (socket_fd);
	unlink (socket_name);


	return 0;
}