#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <fcntl.h>
#include <signal.h>
#include <math.h>
#include <netdb.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/utsname.h>
#include <sys/select.h>
#include <sys/resource.h>                                                                           

struct info_bot {
  char *nick;
  char *servidor;
  char *password;
  char *ident;
  char *ircname;
  int porta;
} bot;


int sock_num, portno, s, n, k, i, p=0;

 pid_t ForkPID;

void error(char *msg) {
    perror(msg); exit(0);
}

void ctrlc() {
  //int w;
    printf("Disconectado!\n");
   sends("QUIT :CobraX IRC Client v1.0 by SouLshaKer & Spoofing");
    sleep(5);
   close(sock_num);
 exit(0);
}

int sends(char *buff_send) {
  
 n=write(sock_num,buff_send,strlen(buff_send));
 n=write(sock_num,"\n",strlen("\n"));
  return 0;
}

/*void fcmdparse(const char buf[]) {

  char *ptr;

  fcmd_i = 0;  ptr = strtok(fbuf, " ");
  
  while(ptr) {
    strncpy(fcmd[fcmd_i++], ptr, sizeof(fcmd[fcmd_i++]));
    ptr=strtok(NULL, " ");
  }
	fcmd[fcmd_i-1][strlen(fcmd[fcmd_i-1])-1]='\0';
} */

void files() {

FILE *fp;

char *aux;
char linha[80]; int cont;

if((fp=fopen("irc.conf","r"))!= NULL) {

 for(cont=1; cont<=80; cont++) {
     fgets(linha,80,fp);
   if(strstr(linha,"[servidores]")!=0)  {
      fgets(linha,80,fp);
      aux=strpbrk(linha," ");
      printf("A conectar ao servidor %s...",aux);
      bot.servidor=linha; cont=40;
      }              
   }
   fclose(fp);
  }
  else
    printf("O ficheiro NAO foi encontrado!! :(\n");

}
  

void main() {                                            //            Main()

  //ForkPID = fork(); //segundo processo...
     
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[500], ping[50]="PONG ";

   bot.nick="NICK CobraX";
   bot.password="NICKSERV IDENTIFY morte";
   bot.porta=6667;
      files();
   
    sock_num = socket(AF_INET, SOCK_STREAM, 0);  // abre 1 socket

  
    if (sock_num < 0) {
        error("ERRO ao abrir o socket!"); exit(0);
        }

      server = gethostbyname(bot.servidor);
      
    if (server == NULL) {
        fprintf(stderr,"ERRO, host nao encontrado!\n"); exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;  //protocolo de rede nest caso tcp_ip    
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);    
    serv_addr.sin_port = htons(bot.porta);

    if (connect(sock_num,&serv_addr,sizeof(serv_addr)) < 0)
        error("ERRO ao tentar conectar!");

   sends(bot.nick);      sends("USER CobraX fault.lala.org irc.netcabo.pt :CObraX :)");
  
    if (n < 0)
        error("ERROR writing to socket");

         //  bzero(buffer,256);   // fgets(buffer,255,stdin);
                      

    n = read(sock_num,buffer,sizeof(buffer));  printf("%s\r\n",buffer);
           
    if(strstr(buffer,"PING :")!=0) 
       for(k=1; k<=strlen(buffer); k++)
         if((buffer[k]=='P')&&(buffer[k+1]=='I')&&(buffer[k+2]=='N')&&(buffer[k+3]=='G')) 
            for(i=k+5; i<=strlen(buffer); i++)
              if(buffer[i]!=':')  
                ping[5+p++]=buffer[i];
               else
                 if(p>3)
                  i=strlen(buffer);        

                  sends(ping);        sends(bot.password);  sends("JOIN :#testescobrax");


   signal(SIGINT, ctrlc);
 while(1)  // main loop
    for (s = 0; s <= sock_num; s++)
      while(n>=1) {     // enquanto ouver coisas pra ler..

   bzero(buffer,256); // limpa o buffer...

   
   n = read(sock_num,buffer,sizeof(buffer));  printf("%s\r\n",buffer);

     
             
    if (n < 0) error("ERROR reading from socket");
     //else
       // error("Server disconnected"); //n==0 kd o servidor morre...
        }
           
            exit(1);
}
