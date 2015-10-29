#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
int main(int argc,char **argv)
{
  int len,count;
  int sockfd,newfd;
  struct sockaddr_in servaddr,cliaddr;
  char buff[1024],fname[10];
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  if(sockfd<0)
    perror("cannot create socket");
  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=INADDR_ANY;
  servaddr.sin_port=htons(7223);
  if(bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
     perror("Bind error");
  listen(sockfd,2);
  len=sizeof(cliaddr);
  newfd=accept(sockfd,(struct sockaddr*)&cliaddr,&len);
  read(newfd,fname,10);
  printf("\nThe file name is read from the client is : %s\n",fname);
  count=open(fname,O_RDONLY);
  read(count,buff,1000);
  write(newfd,buff,strlen(buff));
  printf("\nThe message is sent to client ...........\n");
  close(newfd);
  close(sockfd);
}
