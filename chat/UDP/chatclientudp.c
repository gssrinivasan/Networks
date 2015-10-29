#include <stdlib.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> 
#include <sys/time.h>
#define MAX_MSG 100
#define SOCKET_ERROR -1
int main(int argc, char *argv[]) 
{
  int sd, rc, i, n, echoLen, flags, error, timeOut;
  struct sockaddr_in cliAddr, remoteServAddr, echoServAddr;
  struct hostent *h;
  char msg[MAX_MSG];
  h = gethostbyname(argv[1]);
  if(h==NULL) 
  {
    printf(" unknown host \n");
    exit(1);
  }
  remoteServAddr.sin_family = h->h_addrtype;
  memcpy((char *)&remoteServAddr.sin_addr.s_addr,h->h_addr_list[0],
    h->h_length);
  remoteServAddr.sin_port = htons(2050);
  sd = socket(AF_INET,SOCK_DGRAM,0);
  if(sd<0) 
  {
    printf("Cannot open socket \n");
  }
  cliAddr.sin_family = AF_INET;
  cliAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  cliAddr.sin_port = htons(0);
  rc = bind(sd,(struct sockaddr *)&cliAddr,sizeof(cliAddr));
  if(rc<0) 
  {
    printf("Cannot bind port\n");
  }
  flags = 0;
  do
  {
     printf("Client : ");
     fgets(msg,100,stdin);
     rc=sendto(sd,msg,strlen(msg),flags,(struct sockaddr *)&remoteServAddr,sizeof(remoteServAddr)); 
     if(rc<0) 
     {
        printf("Cannot send data \n");
        close(sd);
     }
     memset(msg,0x0,MAX_MSG);
     strcpy(msg," ");
     echoLen=sizeof(echoServAddr);
     n=recvfrom(sd,msg,MAX_MSG,flags,(struct sockaddr *)&echoServAddr,&echoLen);
     printf("Server: %s\n\n",msg);
  }while(strcmp(msg,"bye\n")!=0);
  return 0;
}
