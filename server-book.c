#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/un.h>
#include <sys/socket.h>

int main(int argc, char const *argv[])
{
	int sockfd;
	int sockfd_slave;
	struct sockaddr_un addr_serv,addr_clnt;//Adresni strukturi na server and client
	socklen_t addr_len; //dyljina na addr_clnt
	char mess_buff[80]; //bufer za predavane na danni

	if( argc != 2 )
	{
		printf("usage %s <socket pathname>\n", argv[0]);
		exit(1);
	}
	if((sockfd = socket(PF_UNIX, SOCK_STREAM,0)) == -1)//syzdavame socket
	{
		perror("socket");
		exit(2);
	}
	
	addr_serv.sun_family = AF_UNIX; //zadaveme domen UNIX
	strcpy(addr_serv.sun_path,argv[1]); //zadavame pyt na socket-a - podaden ot komandniq red
	unlink(addr_serv.sun_path); //premahvane na socket-a ako veche syshtestvuva

	addr_len = strlen(addr_serv.sun_path) + sizeof(addr_serv.sun_family);

	if( bind(sockfd,&addr_serv,addr_len) == -1) //svyrzvane na gnezdoto
	{
		perror("bind");
		exit(3);
	}

	if( listen( sockfd, 5) == -1 ) // ochakvane na clienti
	{
		perror("listen");
		exit(4);
	}
	
	while(1)
	{
		int done = 0;
		int numb;

		printf("Server is waiting for a connection.\n");
		addr_len = sizeof(addr_clnt);

		if((sockfd_slave = accept(sockfd,&addr_clnt,&addr_len)) == -1 )
		{
			perror("accept");
			continue;
		}
		
		printf("\nServer is connected\n");

		do
		{
			numb = read(sockfd_slave,mess_buff,80);//chetene na syobshtenie
			if( numb < 0 )
			{
				perror("read");
				done = 1;
			}
			mess_buff[numb] = '\0';
			if(!strcmp(mess_buff,"quit"))
			{
				printf("Communication ended.\n");//komunikaciqta e prikluchila
				done = 1;
			}
			//obrabotka na syobshtenieto i vryshtane na otgovor
			printf("%s\n",mess_buff);
		}
		while(!done);

		close(sockfd_slave);
		int ch;
		puts("Exit server? [y/n]");
		if((ch = getc(stdin)) == 'y')
		{
			close(sockfd);
			unlink(addr_serv.sun_path);
			return 0;
		}
	}	
}