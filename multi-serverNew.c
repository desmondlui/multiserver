/*
    C socket server example, handles multiple clients using threads
    Compile
    cc server.c -lpthread -o server
*/
 
#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread
 
//the thread function
void *connection_handler(void *);
int createSocket();
 
int main(int argc , char *argv[])
{
	int serverSocket;//server Socket
	int clientSocket;//client Socket
	int connetionValue;
	struct sockaddr_in server , client;
     
	//Create socket
	serverSocket = createSocket();
     
    	//Prepare the sockaddr_in structure
    	server.sin_family = AF_INET;
    	server.sin_addr.s_addr = INADDR_ANY;
    	server.sin_port = htons(8000);
     
    	//Bind
    	if( bind(serverSocket,(struct sockaddr *)&server , sizeof(server)) < 0)
    	{
        	//print the error message
        	perror("bind failed. Error");
        	return 1;
    	}
    	puts("bind done");
     
    	//Listen
    	listen(serverSocket , 3);
     
    	//Accept and incoming connection
    	puts("Waiting for incoming connections...");
    	connetionValue = sizeof(struct sockaddr_in);
     
     
    	//Accept and incoming connection
    	puts("Waiting for incoming connections...");
    	connetionValue = sizeof(struct sockaddr_in);
	pthread_t thread_id;
	
    	while( (clientSocket = accept(serverSocket, (struct sockaddr *)&client, (socklen_t*)&connetionValue)) )
    	{
        	puts("Connection sucessfull");
         
        	if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &clientSocket) < 0)
        	{
            	perror("Error, system could not create thread");
            	return 1;
        	}
         
        //Now join the thread , so that we dont terminate before the thread
        //pthread_join( thread_id , NULL);
        puts("Handler assigned");
    }
     
    if (clientSocket < 0)
    {
        perror("accept failed");
        return 1;
    }
     
    return 0;
}

//crareteSocket allow the software to create a socket
int createSocket()
{	
	int targetSocket = socket(AF_INET , SOCK_STREAM , 0);	
    	if (targetSocket == -1)//fail to create
    	{
        	printf("Could not create socket");
    	}
    	puts("Socket created");
	return targetSocket;
}
 
/*
 * This will handle connection for each client
 * */
void *connection_handler(void *targetSocket)
{
    //Get the socket descriptor
    int socket = *(int*)targetSocket;
    int read_size;
    char *message , client_message[2000];
     
    //Send some messages to the client
    message = "Hello! I am your connection handler\n";
    write(socket , message , strlen(message));
     
    message = "Now type something and I shall repeat your command \n";
    write(socket , message , strlen(message));
     
    //Receive a message from client
    while( (read_size = recv(socket , client_message , 2000 , 0)) > 0 )
    {
        //end of string marker
		client_message[read_size] = '\0';
		
		//Send the message back to client
        write(socket , client_message , strlen(client_message));
		
		//clear the message buffer
		memset(client_message, 0, 2000);
    }
     
    if(read_size == 0)
    {
        puts("Client has disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv has failed");
    }
         
    return 0;
} 
