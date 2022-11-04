#include <netdb.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "iknlib.h"
#include <arpa/inet.h>
#include <fstream>
#include <fcntl.h>
#include <sstream>

using namespace std;

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(void){

char recvbuffer [50];
char sendbuffer = 'Hej Client';


//%%%%%%%%%%% socket setup!! %%%%%%%%%%%%%%


sockaddr_in server_addr;
sockaddr_in client_addr;

int sockfd=socket(AF_INET,SOCK_DGRAM, 0);

if (sockfd<0)
error("fejl ved etablering af socket");

server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(9000);
server_addr.sin_addr.s_addr=INADDR_ANY;

socklen_t client_len=sizeof(client_addr);

int rc = bind(sockfd, (sockaddr*) &server_addr, sizeof(server_addr)); //binder socket til ip og port.

if(rc<0)
error("Fejl ved binding....");


///////%%%%%%%%%%%% Kører server!! %%%%%%%%%%%%%

cout<<"Server starter..."<<endl;

for(;;){

	int n = recvfrom(sockfd, recvbuffer, sizeof(recvbuffer), 0, (sockaddr*)&client_addr, &client_len);

	if (n<0)
		error("fejl ved modtagelse af besked");

	else{
		cout<<recvbuffer<<endl;

		int s = sendto(sockfd, &sendbuffer, sizeof(sendbuffer), 0, (sockaddr*)&client_addr, client_len);

		memset(&recvbuffer, 0, sizeof(recvbuffer));
		memset(&sendbuffer, 0, sizeof(sendbuffer));
	}

	
}


close(sockfd);

return 0;
} 