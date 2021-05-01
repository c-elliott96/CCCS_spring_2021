/*
	C socket server example, handles multiple clients using threads
*/

#include<stdio.h>
#include<string.h>	//strlen
#include<stdlib.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write
#include<pthread.h> //for threading , link with lpthread

pthread_mutex_t lock; // global workers thread mutex

// queue handler
pthread_t* thread_queue_setup(int n_threads);

//the thread function
void *connection_handler(void *);

int main(int argc , char *argv[])
{
	int socket_desc , client_sock , c , *new_sock;
	struct sockaddr_in server , client;
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");

	// Get manual port number
	int port = 8888;
	if (argc > 1)
	{
		port = atoi(argv[1]);
	}
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( port );
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");
	
	//Listen
	listen(socket_desc , 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	
	while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
	{
		puts("Connection accepted");
		
		pthread_t sniffer_thread;
		new_sock = malloc(1);
		*new_sock = client_sock;
		
		if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
		{
			perror("could not create thread");
			return 1;
		}
		
		//Now join the thread , so that we dont terminate before the thread
		pthread_join( sniffer_thread , NULL);
		puts("Handler assigned");
	}
	
	if (client_sock < 0)
	{
		perror("accept failed");
		return 1;
	}
	
	return 0;
}

/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
{
	//Get the socket descriptor
	int sock = *(int*)socket_desc;
	int read_size;
	char *message , client_message[2000];
	
	//Send some messages to the client
	message = "Greetings! I am your connection handler\n";
	write(sock , message , strlen(message));
	
	message = "Now type something and i shall repeat what you type \n";
	write(sock , message , strlen(message));
	
	// First, wipe previous client message
	// memset(client_message, 0, sizeof client_message);
	// Try clearing server message
	// memset(message, 0, sizeof message);
	//Receive a message from client

	// flush stdout before writing client_message
	fflush(stdout);
	while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
	{
		// Copy client_message for parsing
		char msg_copy[strlen(client_message)];
		strcpy(msg_copy, client_message);
		//Send the message back to client
		write(sock , client_message , strlen(client_message));


		// Parse command
		// info FILE
		// get FILE
		// exit
		// printf("Client message: %s\n", client_message);

		if (strlen(msg_copy) >= 4)
		{
			char sub[4];
			for (int i = 0; i < 4; i++)
			{
				sub[i] = msg_copy[i];
			}
		}
		if (strcmp(msg_copy, "info\n") == 0)
		{
			printf("We got an \"info\" request\n");
		}

		memset(client_message, 0, sizeof client_message);
	}
	
	if(read_size == 0)
	{
		puts("Client disconnected");
		fflush(stdout);
	}
	else if(read_size == -1)
	{
		perror("recv failed");
	}
		
	//Free the socket pointer
	free(socket_desc);
	
	return 0;
}