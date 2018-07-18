#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>  // structures for networking
#include <pthread.h> 
int main()
{
    int serverSocket;
    struct sockaddr_in addr;

    serverSocket = socket(PF_INET,SOCK_STREAM,0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(socket, &addr, sizeof(addr));
    listen(serverSocket, 20);

    int addr_len = sizeof(addr);
    int clientsd = accept(serverSocket, &addr, &addr_len);

    char buffer[64]= {};
    memset(buffer , 0 , 64);

//    recv(buf,0,64,0);

    recv(clientsd, buffer, 64, 0);
    printf("Client-> %s\n", buffer);

    close(clientsd);
    close(serverSocket);

    return 0;
}
