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
char DMAC[15];
int main()
{
   int listenfd,connfd,i=0,flag=0,j=0;
   socklen_t len;
   struct sockaddr_in servaddr,cliaddr;
   char * pch;
   char datasend[100];
   char SIP[20],DIP[20],SMAC[20],data[20];
   char response[100],broadcast[100];
   printf("ARP SERVER...\n");
   listenfd=socket(AF_INET,SOCK_STREAM,0);
   printf("ARP Server Started\n");
   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family=AF_INET;
   servaddr.sin_port=htons(PORT);
   servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
   bind(listenfd,(SA *)&servaddr,sizeof(servaddr));
   listen(listenfd,10);
   printf("\n= = = = = = Enter the Packet Details = = = = = =\n");
   printf("\nEnter the Destination IP Address : ");
   scanf("%s",DIP);
   printf("\nEnter the Source IP Address : ");
   scanf("%s",SIP);
   printf("\nEnter the Source MAC Address : ");
   scanf("%s",SMAC);
   printf("\nEnter the Data : ");
   scanf("%s",data);
   len=sizeof(cliaddr);
   for(i=1; ;i++)
   {
       connfd=accept(listenfd,(SA *)&cliaddr,&len);
       broadcast[0]='\0';
       strcat(broadcast,SIP);
       strcat(broadcast,"|");
       strcat(broadcast,SMAC);
       strcat(broadcast,"|");
       strcat(broadcast,DIP);
       write(connfd,broadcast,sizeof(broadcast));
       if(flag == 0)
       {
           flag=1;
           printf("\n********* Developing ARP Query packet *********\n");
           printf("\n    %s\n",broadcast);
           printf("\nThe ARP Query packet is broadcasted.");
           printf("\nWaiting for response....");
           printf("\n");
       }
       read(connfd,response,sizeof(response));
       if(strcmp(response," ")==0);
       else
       {
          printf("\nARP Response received :\n     %s\n",response);
          pch = strtok (response,"|");
          while (pch != NULL)
          { 
             strcpy(DMAC,pch);
             pch = strtok (NULL, "|");
          }
          broadcast[0]='\0';
          strcat(broadcast,SIP);
          strcat(broadcast,"|");
          strcat(broadcast,SMAC);
          strcat(broadcast,"|");
          strcat(broadcast,data);
          printf("\nThe broadcast is : \n%s\n",broadcast);
          datasend[0]='\0';
          strcat(datasend,DIP);
          strcat(datasend,"|");
          strcat(datasend,DMAC);
          strcat(datasend,"|");
          strcat(datasend,broadcast);
          printf("\nThe send data is : \n%s\n",datasend);
          printf("\nSending the packet to : \n      %s\n",DMAC);
          write(connfd,datasend,sizeof(datasend));
       }
   }
   return 0;
}
