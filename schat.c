//server side

#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(int argc, char **argv)
{
	int n;
	int sockfd, newfd, len;
	struct sockaddr_in servaddr, cliaddr;
	char buff[1024];
	char str[1000];

	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0)
		perror("Bind Error!");

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(6500);
	servaddr.sin_addr.s_addr=INADDR_ANY;

	if(bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))<0)
		perror("Bind Error!!");

	listen(sockfd, 2);
	len=sizeof(cliaddr);
	newfd=accept(sockfd, (struct sockaddr*)&cliaddr, &len);

	while(strcmp(buff,"bye")!=0)
	{
	n=read(newfd, buff, sizeof(buff));
	printf("Client: ");
	puts(buff);

	printf("Server: ");
	gets(buff);
	n=write(newfd, buff, sizeof(buff));
	}
	close(sockfd);
	close(newfd);
	return 0;
}
