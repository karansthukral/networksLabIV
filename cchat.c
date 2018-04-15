//client program

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>

int main(int argc, char **argv)
{
	int len;
	int sockfd, n;
	struct sockaddr_in servaddr, cliaddr;
	char buff[1024];
	char str[1000];


	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0)
		perror("Socket cant be created!");

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(argv[1]);
	servaddr.sin_port=htons(6500);

	connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	while(strcmp(buff,"bye")!=0)
	{
	printf("Client: ");
	gets(buff);
	n=write(sockfd, buff, sizeof(buff));

	n=read(sockfd, buff, sizeof(buff));	
	printf("Server: ");
	puts(buff);
	}

	close(sockfd);
	return 0;
}