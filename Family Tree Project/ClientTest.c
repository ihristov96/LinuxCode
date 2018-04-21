#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "Types.h"
/* Write command to the socket given by file descriptor SOCKET_FD.
*/
void sendCommandRequest (int server_socket_fd, int command)
{
	/* Write the number of bytes in the string, including
	NUL-termination. */
	write (server_socket_fd, &command, sizeof (int));
	/* Write the string. */
	//write (socket_fd, text, length);
}
void showFamilyTree(int server_socket_fd)
{
	int size = 0;

	printf("Client:showFamilyTree command accepted\n");
	if (read (server_socket_fd, &size, sizeof (int)) == 0)return 0;

	printf("Number of structs %d\n",size );
}
void addChildren(int server_socket_fd)
{
	printf("addChildren command accepted\n");
}
void killFamilyMember(int server_socket_fd)
{
	printf("killFamilyMember command accepted\n");

}
void handleCommand(int server_socket_fd, int command)
{
	if( command == showFamilyTree_c )
	{
		showFamilyTree(server_socket_fd);
		printf("showFamilyTree command handled\n");
	}
	else if( command == addChildren_c )
	{
		addChildren(server_socket_fd);
		printf("addChildren command handled\n");
	}
	else if( command == killFamilyMember_c )
	{
		killFamilyMember(server_socket_fd);
		printf("killFamilyMember command handled\n");
	}
}
int main(int argc, char const *argv[])
{
	const char* const socket_name = argv[1];
	int socket_fd;

	struct sockaddr_un name;

	// Create the socket
	socket_fd = socket (PF_LOCAL, SOCK_STREAM, 0);

	/* Store the server's name in the socket address. */
	name.sun_family = AF_LOCAL;
	strcpy (name.sun_path, socket_name);
	/* Connect the socket.
	*/
	connect (socket_fd, &name, SUN_LEN (&name));
	//Write the text on the command line to the socket.
	while(1)
	{
		int command = 0;
		scanf("%d", &command);
	
		sendCommandRequest (socket_fd, command);
		handleCommand(socket_fd, command);
	}
	
	close (socket_fd);

	return 0;
}