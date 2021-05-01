// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <cstring>
#define PORT 8888

int main(int argc, char const *argv[])
{
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	
	char buffer[1024] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}

  valread = read(sock, buffer, 1024);
  printf("%s\n", buffer);
  bzero(buffer, 1024);

  while(1)
  {
    // set up msg string
    std::string msg;
    std::cout << "Give me a command: ";
    std::getline(std::cin, msg);

    // convert string to c string
    char * cstr_msg = new char [msg.length() + 1];
    std::strcpy (cstr_msg, msg.c_str());

    // send our request
    send(sock , cstr_msg , strlen(cstr_msg) , 0 );

    // read a response; locks
	  valread = read( sock , buffer, 1024);

    // print what we get back
	  printf("%s\n",buffer );

    // zero out the recv buffer
    bzero(buffer, 1024);
  }

	return 0;
}
