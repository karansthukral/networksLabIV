//ftp udp
//server side
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<fcntl.h>

int main(int argc, char** argv)
{
	int n;
	int sockfd, nbytes;
	socklen_t len;
	struct sockaddr_in servaddr, cliaddr;
	char buff[200];

	sockfd=socket(PF_INET, SOCK_DGRAM, 0);
	if(sockfd<0)
		perror("Socket can't be created");

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(atoi(argv[1]));
	servaddr.sin_addr.s_addr=INADDR_ANY;

	if(bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))<0)
		perror("Socket bind error!");

	len=sizeof(cliaddr);
	n=recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&cliaddr, &len);

	printf("Enter file name: %s", buff);

	printf("\nFile is being recieved.....\n");
	FILE* F;
	F=fopen(buff, "r");
	if(F==NULL)
	{
		strcpy(buff,"File doesn't exist!");
		sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&cliaddr, len);
	}
	else
	{	
		while(fgets(buff,100,F) > 0)
			sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&cliaddr, len);
		sendto(sockfd, "end", 4, 0, (struct sockaddr*)&cliaddr, len);
		printf("File is found and sent!");
	}
	close(sockfd);
}