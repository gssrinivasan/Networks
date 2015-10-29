#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc,char **argv)
{
  int len,count;
  int sockfd,n;
  struct sockaddr_in servaddr,cliaddr;
  char str[1000],buff[1024];
  char fname[10],fname1[10];
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  if(sockfd<0)
    perror("cannot create socket");
  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=inet_addr(argv[1]);
  servaddr.sin_port=htons(7223);
  connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
  printf("\nEnter the file name to read : ");
  scanf("%s",fname);
  write(sockfd,fname,sizeof(fname));
  printf("\n%s file is sent to the server....\n",fname);
  read(sockfd,buff,1000);
  printf("\nMessage from the server is : \n%s",buff);
  count=fopen("output.txt","w");
  fprintf(count,"%s",buff);
  printf("\nThe message is saved in the output.txt file ......\n");
  printf("\n");
  close(sockfd);
}
