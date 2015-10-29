#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netdb.h>
#include <stdlib.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SA struct sockaddr
#define PORT 7090
int main(int argc,char **argv)
{
char ch[4];
struct sockaddr_in servaddr;
char buff[200],host[100];
int sockfd;
sockfd=socket(AF_INET,SOCK_STREAM,0);
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(PORT);
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
if(connect(sockfd,(SA *)&servaddr,sizeof(servaddr))<0)
        printf("Connect error");
do
{
printf("Enter the domain name");
scanf("%s",host);
write(sockfd,host,sizeof(host));
if(read(sockfd,buff,sizeof(buff))<0)
        printf("Read error");
printf("\nThe host address is %s\n",buff);
printf("\nDo you want to continue press 1 else 0 .....");
scanf("%s",ch);
write(sockfd,ch,sizeof(ch));
}while(strcmp(ch,"0")!=0);
return 0;
}
