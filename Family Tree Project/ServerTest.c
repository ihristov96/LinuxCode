#include <stdio.h>
#include <sys/un.h> //sockaddr_un
#include <sys/socket.h> //socket, PF_LOCAL,SOCK_STREAM

#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>


#include "Types.h"
#define NUM_THREADS     5
void showFamilyTree(int clientSocketFd)
{
	int size = 4;
	printf("\nServer: showFamilyTree command accepted\n");
	write (clientSocketFd, &size, sizeof (int));
	
}
void addChildren(int clientSocketFd)
{
	printf("addChildren command accepted\n");
}
void killFamilyMember(int clientSocketFd)
{
	printf("killFamilyMember command accepted\n");
}

int clientHandlerThread (void* client_socket_fd)
{
	int client_socket = (int)client_socket_fd;
	while (1) 
	{
		int length;
		char* text;

		int requestedCommand;

		/* First, read the length of the text message from the socket. If
		read returns zero, the client closed the connection. */
		// /if (read (client_socket, &length, sizeof (length)) == 0)return 0;

		//first read command request from the client
		if (read (client_socket, &requestedCommand, sizeof (requestedCommand)) == 0)return 0;

		if( requestedCommand == showFamilyTree_c )
		{
			showFamilyTree(client_socket);
		}
		else if( requestedCommand == addChildren_c )
		{
			addChildren(client_socket);
		}
		else if( requestedCommand == killFamilyMember_c )
		{
			killFamilyMember(client_socket);
		}

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
			break;
	}
	close (client_socket);
	pthread_exit(NULL);
}

void signal_callback_handler(int signum)
{
   printf("Server shut down\n");
   printf("TODO: Save binary tree into file\n");
   exit(signum);
}


int main(int argc, char const *argv[])
{
	signal(SIGINT, signal_callback_handler);

	pthread_t threads[NUM_THREADS];
	int clientCounter = 0;
	int rc = 0;
	const char* const socket_name = argv[1];
	int sockfd;

	struct sockaddr_un addr_serv;

	//Create a socket
	sockfd = socket (PF_LOCAL, SOCK_STREAM, 0);
	
	addr_serv.sun_family = AF_LOCAL;
	//Copy socket addr_serv(path) to sun_path
	strcpy (addr_serv.sun_path, socket_name);
	unlink(addr_serv.sun_path); //premahvane na socket-a ako veche syshtestvuva

	if( bind(sockfd, &addr_serv, SUN_LEN (&addr_serv)) == -1) //svyrzvane na gnezdoto
	{
		perror("bind");
		exit(3);
	}

	//Listen for connections
	if( listen( sockfd, 5) == -1 ) // ochakvane na clienti
	{
		perror("listen");
		exit(4);
	}

	/* Repeatedly accept connections, spinning off one server() to deal
	with each client. Continue until a client sends a "quit"
	message.
	*/
	while(1)
	{
		struct sockaddr_un addr_clnt;
		int client_socket_fd;
		/* Accept a connection.
		*/
		client_socket_fd = accept (sockfd, &addr_clnt, SUN_LEN(&addr_clnt));
		/* Handle the connection.
		*/
		rc = pthread_create(&threads[clientCounter], NULL, clientHandlerThread, (void *)client_socket_fd);
        if (rc)
        {
           printf("ERROR; return code from pthread_create() is %d\n", rc);
           exit(-1);
        }
        clientCounter++;

		//client_sent_quit_message = server (client_socket_fd);
		/* Close our end of the connection.
		*/
		//close (client_socket_fd);
	}

	/* Remove the socket file.*/
	close (sockfd);
	unlink (addr_serv.sun_path);


	return 0;
}