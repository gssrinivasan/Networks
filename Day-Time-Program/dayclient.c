//tcpdcli.c -- TCP DAYTIME CLIENT
#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#define PORT 7784
int main(int argc,char *argv[])
{
   int sockfd;
   struct sockaddr_in serv;
   char buff[30],ch[5];
   sockfd=socket(AF_INET,SOCK_STREAM,0);
   memset(&serv,0,sizeof(serv));
   serv.sin_family=AF_INET;
   serv.sin_port=htons(PORT);
   serv.sin_addr.s_addr=inet_addr(argv[1]);
   if(connect(sockfd,(struct sockaddr *)&serv,sizeof(serv))<0)
     printf("Error in Connect");
   do
   {
      printf("\n1.Date\n2.Day\n3.Month\n4.Year\n5.Time\n6.Exit\n");
      printf("\nEnter your choice : ");
      scanf("%s",ch);
      write(sockfd,ch,sizeof(ch));
      if(strcmp(ch,"1")==0)          
         printf("\nDate : ");
      else if(strcmp(ch,"2")==0)
         printf("\nDay : ");
      else if(strcmp(ch,"3")==0)
         printf("\nMonth : ");
      else if(strcmp(ch,"4")==0)
         printf("\nYear : ");
      else if(strcmp(ch,"5")==0)
         printf("\nTime : ");
      else if(strcmp(ch,"6")==0)
         exit(0);
      strcpy(buff," ");
      read(sockfd,buff,sizeof(buff));
      printf("%s\n",buff);
   }while(strcmp(ch,"6")!=0);
   close(sockfd);
}
