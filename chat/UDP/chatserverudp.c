#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> 
#include <string.h> 
#define MAX_MSG 100
int main(int argc, char *argv[]) 
{
  int sd, rc, n, cliLen, flags,i=0;
  struct sockaddr_in cliAddr, servAddr;
  char msg[MAX_MSG];
  sd=socket(AF_INET, SOCK_DGRAM, 0);
  if(sd<0) {
    printf("Cannot open socket \n");
    exit(1);
  }
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(2050);
  rc=bind(sd,(struct sockaddr *)&servAddr,sizeof(servAddr));
  if(rc<0)
  {
     printf("Cannot bind port number......\n");
     exit(1);
  }
  printf("Waiting for request ............\n");
  for(i=1; ;i++)
  {
     flags = 0;
     do
     {
        memset(msg,0x0,MAX_MSG);
        cliLen = sizeof(cliAddr);
        n=recvfrom(sd,msg,MAX_MSG,flags,(struct sockaddr *)&cliAddr,&cliLen);
        if(n<0) 
          printf("Cannot receive data \n");
        printf("Client %d : %s\n",i,msg);
        strcpy(msg," ");
        printf("Server : ");
        fgets(msg,100,stdin);
        printf("\n");
        n=sendto(sd,msg,n,flags,(struct sockaddr *)&cliAddr,cliLen); 
        if(n<0)
          printf("\nCannot receive data ....... \n");
     }while(strcmp(msg,"bye\n")!=0);
     printf("Client %d exit ..............\n",i);
     printf("\nWaiting for next request ......\n");
  }
return 0;
}
