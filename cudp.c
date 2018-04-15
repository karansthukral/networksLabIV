//ftp udp
//client side
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(int argc, char** argv)
{
	int n;
	int sockfd, nbytes, len;
	struct sockaddr_in servaddr, cliaddr;
	char buff[100];

	sockfd=socket(PF_INET, SOCK_DGRAM, 0);
	if(sockfd<0)
		perror("Socket cant be created");

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(atoi(argv[2]));
	servaddr.sin_addr.s_addr=inet_addr(argv[1]);

	printf("Enter file name: ");
	scanf("%s", buff);

	len=sizeof(servaddr);
	sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&servaddr, len);

	printf("\nWaiting for file to be sent.....\n");
	FILE* F;
	F=fopen("recieved txt", "a+");

	while(recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&servaddr, &len)>0&&strcmp(buff,"end")!=0)
	{
		fprintf(F, "%s", buff);
		puts(buff);
		bzero(buff, 100);
	}
	close(sockfd);
}