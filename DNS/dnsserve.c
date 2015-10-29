#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netdb.h>
#include <stdlib.h> 
#include <arpa/inet.h>
#include <unistd.h>
#define SA struct sockaddr
#define PORT 7090
struct dnstable
{
   char dnsname[50];
   char IP[50];
}dns[20];

int main()
{
int listenfd,connfd,i=0,flag=0,j=0;
socklen_t len;
struct sockaddr_in servaddr,cliaddr;
char host[100],ip[20]=" ",ch[4];
printf("DNS SERVER...\n");
listenfd=socket(AF_INET,SOCK_STREAM,0);
printf("DNS Server Started\n");
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(PORT);
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
bind(listenfd,(SA *)&servaddr,sizeof(servaddr));
listen(listenfd,10);
strcpy(dns[0].dnsname,"www.google.co.in");
strcpy(dns[0].IP,"142.89.78.66");
strcpy(dns[1].dnsname,"www.yahoo.com");
strcpy(dns[1].IP,"10.2.45.67");
strcpy(dns[2].dnsname,"www.annauniv.edu");
strcpy(dns[2].IP,"197.34.53.122");
strcpy(dns[3].dnsname,"www.gmail.com");
strcpy(dns[3].IP,"157.94.54.9");
strcpy(dns[4].dnsname,"www.ssn.edu.in");
strcpy(dns[4].IP,"175.98.42.1");
strcpy(dns[5].dnsname,"www.yahoomail.com");
strcpy(dns[5].IP,"69.147.76.15");
printf("\nDomain Name\t\tIP Address");
for(i=0;i<6;i++)
   printf("\n%s\t\t%s",dns[i].dnsname,dns[i].IP);
for(j=0; ;j++)
{
     len=sizeof(cliaddr);
     connfd=accept(listenfd,(SA *)&cliaddr,&len);
     printf("\nClient %d : ",j);
     do
     {
         read(connfd,host,sizeof(host));
         printf("Request is for %s\n",host);
         flag=0;
         for(i=0;i<6;i++)
         {
	    if(strcmp(host,dns[i].dnsname)==0)
            {
               flag=1;
               strcpy(ip,dns[i].IP);
               break;
            }
         }
         if(flag==0)
         {
           write(connfd,"IP not found",15);
         }
         else
         {           
           write(connfd,ip,sizeof(ip));
         }
         read(connfd,ch,sizeof(ch));
      }while(strcmp(ch,"0")!=0);
      close(connfd);
      printf("\nWaiting for next request ......\n ");
   }
return 0;
}
