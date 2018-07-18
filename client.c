#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main()
{
	int clientSocket;
	struct sockaddr_in addr;

	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);

	inet_aton("127.0.0.1", &addr.sin_addr);

	connect(clientSocket,&addr, sizeof(addr));

	send(clientSocket, "sucessfully connected" , strlen("sucessfully connected"), 0);

	return 0;
} 
