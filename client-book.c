#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
	int sockfd;
	int len;
	struct sockaddr_un addr_serv;//Adresni strukturi na server and client

	char mess[80]; //bufer za predavane na danni

	if( argc != 2 )
	{
		printf("usage %s <socket pathname>\n", argv[0]);
		exit(1);
	}

	if((sockfd = socket(AF_UNIX,SOCK_STREAM,0)) == -1)
	{
		perror("socket");
		exit(2);
	}

	addr_serv.sun_family = AF_UNIX;
	strncpy(addr_serv.sun_path, argv[1],sizeof(addr_serv.sun_path)-1);
	len = strlen(addr_serv.sun_path) + sizeof(addr_serv.sun_family);
	if(connect(sockfd,&addr_serv,len) == -1)//svyrzvane kym syrvera
	{
		perror("connect");
		exit(3);
	}
	printf("\nClient is connected. Type Ctrl-d to exit client\n");
	while( printf("Insert message: "),scanf("%s",mess),!feof(stdin))
	{
		if(write(sockfd,mess,strlen(mess)) == -1)
		{
			perror("write");
			exit(4);
		}
	}
	write(sockfd,"quit",4);
	close(sockfd);
	return 0;
}