//stop and wait
//server side
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(int argc, char** argv)
{
	int n;
	int sockfd, len, newfd;
	struct sockaddr_in servaddr, cliaddr;
	char buff[1024], str[1000];
	char frame[4][5];
	int i, j, count=0;

	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0)
		perror("Socket can't be created!");
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=INADDR_ANY;
	servaddr.sin_port=htons(atoi(argv[1]));

	if(bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))<0)
		perror("Bind error!");
	listen(sockfd, 2);
	len=sizeof(cliaddr);
	newfd=accept(sockfd, (struct sockaddr*)&cliaddr, &len);


	//n=read(newfd, buff, sizeof(buff));
	//printf("Data from client: %s\n", buff);


	n=read(newfd, frame[0], 5);
	printf("Frame from client: %s\n", frame[0]);
	for(i=0;i<4;i++)
	{
		if(frame[0][i]=='1')
			count++;
	}
	//printf("%d %c", count, frame[0][4]);
	if(count%2==0)
	{	if(frame[0][4]=='0')
		strcpy(str,"Positive ack");
		else
		strcpy(str,"Negative ack");
	}
	else if(count%2==1)
	{	if(frame[0][4]=='1')
		strcpy(str,"Positive ack");
		else
		strcpy(str,"Negative ack");
	}
	count=0;
	n=write(newfd, str, sizeof(str));

	n=read(newfd, frame[1], 5);
	printf("Frame from client: %s\n", frame[1]);
	for(i=0;i<4;i++)
	{
		if(frame[1][i]=='1')
			count++;
	}
	//printf("%d %c", count, frame[0][4]);
	if(count%2==0)
	{	if(frame[1][4]=='0')
		strcpy(str,"Positive ack");
		else
		strcpy(str,"Negative ack");
	}
	else if(count%2==1)
	{	if(frame[1][4]=='1')
		strcpy(str,"Positive ack");
		else
		strcpy(str,"Negative ack");
	}
	count=0;
	n=write(newfd, str, sizeof(str));


	n=read(newfd, frame[2], 5);
	printf("Frame from client: %s\n", frame[2]);
	for(i=0;i<4;i++)
	{
		if(frame[2][i]=='1')
			count++;
	}
	//printf("%d %c", count, frame[0][4]);
	if(count%2==0)
	{	if(frame[2][4]=='0')
		strcpy(str,"Positive ack");
		else
		strcpy(str,"Negative ack");
	}
	else if(count%2==1)
	{	if(frame[2][4]=='1')
		strcpy(str,"Positive ack");
		else
		strcpy(str,"Negative ack");
	}
	count=0;
	n=write(newfd, str, sizeof(str));


	n=read(newfd, frame[3], 5);
	printf("Frame from client: %s\n", frame[3]);
	for(i=0;i<4;i++)
	{
		if(frame[3][i]=='1')
			count++;
	}
	//printf("%d %c", count, frame[0][4]);
	if(count%2==0)
	{	if(frame[3][4]=='0')
		strcpy(str,"Positive ack");
		else
		strcpy(str,"Negative ack");
	}
	else if(count%2==1)
	{	if(frame[3][4]=='1')
		strcpy(str,"Positive ack");
		else
		strcpy(str,"Negative ack");
	}
	count=0;
	n=write(newfd, str, sizeof(str));



	close(sockfd);
	close(newfd);


}