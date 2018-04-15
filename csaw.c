//stop and wait
//client side
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
	int sockfd, len;
	struct sockaddr_in servaddr, cliaddr;
	char buff[1024], str[1000];
	char frame[4][5];
	int flag;
	int error;


	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0)
		perror("Socket can't be created!");
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(argv[1]);
	servaddr.sin_port=htons(atoi(argv[2]));

	connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	printf("Enter 16 bit data to be sent: ");
	gets(buff);

	//write(sockfd, buff, sizeof(buff));
	int i, j=0, k=0, count=0;
	for(i=0;i<16;i++)
	{
		frame[j][k]=buff[i];
		k++;
		if(k==4)
		{
			k=0;
			j++;
		}
	}

	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(frame[i][j]=='1')
				count++;
		}
		if(count%2==0)
			frame[i][4]='0';
		else
			frame[i][4]='1';
		count=0;
	}

	for(i=0;i<4;i++)
	{
		printf("\nFrame%d: ", i);
		for(j=0;j<4;j++)
			printf("%c", frame[i][j]);
		printf(" - %c", frame[i][4]);
	}

	printf("\nSending Frame0");
	printf("\nDo you wanna introduce error of Frame0 (0/1)");
	scanf("%d", &flag);
	if(flag==1)
	{
		printf("\nEnter position for error: ");
		scanf("%d", &error);
		if(frame[0][error-1]=='1')
			frame[0][error-1]='0';
		else
			frame[0][error-1]='1';
	}
	write(sockfd, frame[0], 5);
	n=read(sockfd, str, sizeof(str));
	printf("\n%s\n", str);
	if(strcmp(str,"Negative ack")==0)
	{
		close(sockfd);
		return 0;
	}
	
	printf("\nSending Frame1");
	printf("\nDo you wanna introduce error of Frame0 (0/1)");
	scanf("%d", &flag);
	if(flag==1)
	{
		printf("\nEnter position for error: ");
		scanf("%d",&error);
		if(frame[1][error-1]=='1')
			frame[1][error-1]='0';
		else
			frame[1][error-1]='1';
	}
	write(sockfd, frame[1], 5);
	n=read(sockfd, str, sizeof(str));
	printf("\n%s\n", str);
	if(strcmp(str,"Negative ack")==0)
	{
		close(sockfd);
		return 0;
	}
	
	printf("\nSending Frame2");
	printf("\nDo you wanna introduce error of Frame2 (0/1)");
	scanf("%d", &flag);
	if(flag==1)
	{
		printf("\nEnter position for error: ");
		scanf("%d",&error);
		if(frame[2][error-1]=='1')
			frame[2][error-1]='0';
		else
			frame[2][error-1]='1';
	}
	write(sockfd, frame[2], 5);
	n=read(sockfd, str, sizeof(str));
	printf("\n%s\n", str);
	if(strcmp(str,"Negative ack")==0)
	{
		close(sockfd);
		return 0;
	}
	
	printf("\nSending Frame3");
	printf("\nDo you wanna introduce error of Frame3 (0/1)");
	scanf("%d", &flag);
	if(flag==1)
	{
		printf("\nEnter position for error: ");
		scanf("%d",&error);
		if(frame[3][error-1]=='1')
			frame[3][error-1]='0';
		else
			frame[3][error-1]='1';
	}
	write(sockfd, frame[3], 5);
	n=read(sockfd, str, sizeof(str));
	printf("\n%s\n", str);
	if(strcmp(str,"Negative ack")==0)
	{
		close(sockfd);
		return 0;
	}

	close(sockfd);


}
