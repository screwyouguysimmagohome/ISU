#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
//#include "iknlib.h"

using namespace std;

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char* argv[])
{

char sendbuffer []="Hej Server";
char recvbuffer[50];

sockaddr_in server_addr = {0};
socklen_t server_len=sizeof(server_addr);

int portno = atoi(argv[2]);

int sockfd=socket(AF_INET,SOCK_DGRAM, 0);

if (sockfd<0)
error("fejl ved etablering af socket");

server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(9000);
server_addr.sin_addr.s_addr=INADDR_ANY;

int s=sendto(sockfd, sendbuffer, sizeof(sendbuffer), 0, (sockaddr*)&server_addr, sizeof(server_addr));

if(s<0)
    error("fejl ved sendmsg");



// %%%%%%%%% NU SKAL VI TIL AT MODTAGE SVARET!! %%%%%%%%%%

int n=recvfrom(sockfd, recvbuffer, sizeof(recvbuffer), 0, (sockaddr*)&server_addr, &server_len);

if(n<0)
    error("fejl ved sendmsg");

cout<<recvbuffer<<endl;

memset(&recvbuffer, 0, sizeof(recvbuffer));
memset(&sendbuffer, 0, sizeof(sendbuffer));

close(sockfd);


return 0;

}