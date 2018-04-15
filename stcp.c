//tcp ftp
//server side
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<fcntl.h>

int main(int argc, char** argv)
{
	int n;
	int sockfd, newfd;
	socklen_t len;
	struct sockaddr_in servaddr, cliaddr;
	char buff[200];

	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	
	if(sockfd<0)
		perror("Socket can't be created!");

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=INADDR_ANY;
	servaddr.sin_port=htons(atoi(argv[1]));

	if(bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))<0)
		perror("Socket bind error!");

	len=sizeof(cliaddr);
	listen(sockfd, 1);
	newfd=accept(sockfd, (struct sockaddr*)&cliaddr, &len);
	read(newfd, buff, sizeof(buff));
	printf("File requested by client: %s\n", buff);

	FILE* F;
	F=fopen(buff,"r");
	if(F==NULL)
	{
		strcpy(buff,"File doesn't exist!");
		write(newfd, buff, sizeof(buff));
	}
	else
	{
		while(fgets(buff,100,F)>0)
			write(newfd, buff, sizeof(buff));
		printf("\nFile found and sent to client!");
	}
	close(sockfd);
	close(newfd);

}