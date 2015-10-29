#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
   int sockfd;
   struct sockaddr_in serv;
   char buff[30],buf[30];
   sockfd=socket(AF_INET,SOCK_STREAM,0);
   memset(&serv,0,sizeof(serv));
   serv.sin_family=AF_INET;
   serv.sin_port=htons(4771);
   serv.sin_addr.s_addr=inet_addr(argv[1]);
   if(connect(sockfd,(struct sockaddr *)&serv,sizeof(serv))<0)
      printf("Error in connection ..........\n");
   do
   {
      strcpy(buf," ");
      strcpy(buff," ");
      printf("\nClient : ");
      fgets(buf,100,stdin);
      write(sockfd,buf,sizeof(buf));
      read(sockfd,buff,sizeof(buff));
      printf("Server : %s\n",buff);
   }while(strcmp(buf,"bye\n")!=0);
   close(sockfd);
   return 0;
}
