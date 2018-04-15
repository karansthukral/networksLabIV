//tcp ftp
//client side
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int main(int argc, char** argv)
{
	int n;
	int sockfd, len;
	char buff[200];
	struct sockaddr_in servaddr;

	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0)
		perror("Socket can't be created!");

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(argv[1]);
	servaddr.sin_port=htons(atoi(argv[2]));

	connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	printf("Enter the file name: ");
	scanf("%s", buff);

	FILE *F;
	write(sockfd, buff, sizeof(buff));

	F=fopen("recieved.txt", "a+");
	printf("\nWaiting for server to send file.....\n");
	while(read(sockfd, buff, sizeof(buff))>0&&strcmp(buff,"end")!=0)
	{
		fprintf(F,"%s", buff);
		puts(buff);
		bzero(buff,100);
	}
	close(sockfd);
}
