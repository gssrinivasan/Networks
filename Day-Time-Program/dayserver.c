//tcpd.c -- TCP DAYTIME SERVER
#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<sys/time.h>
#include<time.h>
#define PORT 7784
int main(int argc,char *argv[])
{
   time_t today;
   struct tm *ts;
   char buff[30],buf[30];
   int sockfd,newfd,len,i=0;
   struct sockaddr_in servaddr,cliaddr;
   sockfd=socket(AF_INET,SOCK_STREAM,0);
   if(sockfd==-1)
      printf("Error creating Socket\n");
   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family=AF_INET;
   servaddr.sin_port=htons(PORT);
   servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
   bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
   if(listen(sockfd,5)<0)
      printf("Error in Listen Function");
   len=sizeof(cliaddr);
   today=time(0);
   ts=localtime(&today);
   printf("Waiting for request ............\n");
   for(i=1; ;i++)
   {
      if((newfd=accept(sockfd,(struct sockaddr*)&cliaddr,&len))<0) 
         printf("Error in accept");
      printf("\nClient %d request the server .... \n",i);
      do
      {         
         strcpy(buf," ");
         read(newfd,buff,sizeof(buff));
         if(strcmp(buff,"1")==0)
           strftime(buf,sizeof(buf),"%d",ts);
         else if(strcmp(buff,"2")==0)
           strftime(buf,sizeof(buf),"%a",ts);
         else if(strcmp(buff,"3")==0)
           strftime(buf,sizeof(buf),"%m",ts);
         else if(strcmp(buff,"4")==0)
           strftime(buf,sizeof(buf),"%Y",ts);
         else if(strcmp(buff,"5")==0)
           strftime(buf,sizeof(buf)," %H:%M:%S ",ts);
         write(newfd,buf,sizeof(buf));
      }while(strcmp(buff,"6")!=0);
      close(newfd);
      printf("Client %d exit ..............\n",i);
      printf("\nWaiting for next request ......\n ");
   }
}
