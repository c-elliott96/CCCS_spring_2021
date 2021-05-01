//Example code: A simple server side code, which echos back the received message.
//Handle multiple socket connections with select and fd_set on Linux
#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h> //close
#include <arpa/inet.h> //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros

#include <iostream>
#include <cstring>
#include <sys/stat.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
	
#define TRUE 1
#define FALSE 0
// #define PORT 8888

struct info_out
{
  std::string time;
  std::string size;
} ;

char * str_cstr(std::string);
std::string cstr_str(char *);
int parse_cmd(std::string);
info_out get_stat(char *);
std::string int_to_str(int);
std::string get_info_file_name(std::string);
std::string get_get_file_name(std::string);
std::string strip_slashes(std::string);
	
int main(int argc , char *argv[])
{
  // ################################################################
  // Checking args
  // for (int i = 0; i < argc; i++)
  // {
  //   std::cout << argv[i] << '\t';
  // }
  // std::cout << '\n';

  int PORT = 8888;      // default 8888
  int CONS = 40;        // default 40
  int TIMEOUT = 10000;  // default 10000 (seconds? double check)
  std::string DIR = ""; // default ""
  if (argc == 5)
  {
    PORT = atoi(argv[1]);
    CONS = atoi(argv[2]);
    TIMEOUT = atoi(argv[3]);
    DIR = argv[4];
  }

  // std::cout << PORT << '\t'
  //           << CONS << '\t'
  //           << TIMEOUT << '\t'
  //           << DIR << '\n';
  
  // End checking args
  // ################################################################

	int opt = TRUE;
	int master_socket , addrlen , new_socket , client_socket[30] ,
		max_clients = 30 , activity, i , valread , sd;
	int max_sd;
	struct sockaddr_in address;
		
	char buffer[1025]; //data buffer of 1K
		
	//set of socket descriptors
	fd_set readfds;
		
	//a message
	// char *message = "ECHO Daemon v1.0 \r\n";

  std::string message = "OS Project - C. Elliott \r\n";
	
	//initialise all client_socket[] to 0 so not checked
	for (i = 0; i < max_clients; i++)
	{
		client_socket[i] = 0;
	}
		
	//create a master socket
	if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	
	//set master socket to allow multiple connections ,
	//this is just a good habit, it will work without this
	if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
		sizeof(opt)) < 0 )
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	
	//type of socket created
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );
		
	//bind the socket to localhost port 8888
	if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	printf("Listener on port %d \n", PORT);
		
	//try to specify maximum of 3 pending connections for the master socket
	if (listen(master_socket, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
		
	//accept the incoming connection
	addrlen = sizeof(address);
	puts("Waiting for connections ...");
		
	while(TRUE)
	{
		//clear the socket set
		FD_ZERO(&readfds);
	
		//add master socket to set
		FD_SET(master_socket, &readfds);
		max_sd = master_socket;
			
		//add child sockets to set
		for ( i = 0 ; i < max_clients ; i++)
		{
			//socket descriptor
			sd = client_socket[i];
				
			//if valid socket descriptor then add to read list
			if(sd > 0)
				FD_SET( sd , &readfds);
				
			//highest file descriptor number, need it for the select function
			if(sd > max_sd)
				max_sd = sd;
		}
	
		//wait for an activity on one of the sockets , timeout is NULL ,
		//so wait indefinitely
		activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
	
		if ((activity < 0) && (errno!=EINTR))
		{
			printf("select error");
		}
			
		//If something happened on the master socket ,
		//then its an incoming connection
		if (FD_ISSET(master_socket, &readfds))
		{
			if ((new_socket = accept(master_socket,
					(struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
			{
				perror("accept");
				exit(EXIT_FAILURE);
			}
			
			//inform user of socket number - used in send and receive commands
			printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
		
      // Set up message to send
      char * msg = str_cstr(message);

			//send new connection greeting message
			if( send(new_socket, msg, strlen(msg), 0) != strlen(msg) )
			{
				perror("send");
			}
				
			puts("greeting message sent successfully");
				
			//add new socket to array of sockets
			for (i = 0; i < max_clients; i++)
			{
				//if position is empty
				if( client_socket[i] == 0 )
				{
					client_socket[i] = new_socket;
					printf("Adding to list of sockets as %d\n" , i);
						
					break;
				}
			}
		}
			
		//else its some IO operation on some other socket
		for (i = 0; i < max_clients; i++)
		{
			sd = client_socket[i];
				
			if (FD_ISSET( sd , &readfds))
			{
				//Check if it was for closing , and also read the
				//incoming message
				if ((valread = read( sd , buffer, 1024)) == 0)
				{
					//Somebody disconnected , get his details and print
					getpeername(sd , (struct sockaddr*)&address , \
						(socklen_t*)&addrlen);
					printf("Client disconnected , ip %s , port %d \n" ,
						inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
						
					//Close the socket and mark as 0 in list for reuse
					close( sd );
					client_socket[i] = 0;
				}
					
				// Client has sent message: parse and respond
				else
				{
					//set the string terminating NULL byte on the end
					//of the data read
					buffer[valread] = '\0';

          // capture buffer into std::string for easier parsing
          std::string cmd = cstr_str(buffer);
          int cmd_num = parse_cmd(cmd);

          switch(cmd_num)
          {
            case -1:
            {
              std::cout << "error: unk command\n";
              // send error to client
              break;
            }
            case 0:
            {
              std::cout << "Exit command received. Exiting ...\n";
              getpeername(sd , (struct sockaddr*)&address , \
						    (socklen_t*)&addrlen);
					    printf("Client disconnected , ip %s , port %d \n" ,
						    inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
						
					    //Close the socket and mark as 0 in list for reuse
              close( sd );
              client_socket[i] = 0;
              break;
            }
            case 1:
            {
              std::cout << "get placeholder\n";

              std::string TMP_DIR = DIR;
              TMP_DIR.append(get_info_file_name(cmd));
              std::string get_path = TMP_DIR; // to be changed to DIR
              // get_path.append(get_info_file_name(cmd));
              char * get_dir = str_cstr(get_path);

              printf("running get on dir: %s\n", get_dir);
              info_out get_out = get_stat(get_dir);
              
              std::string get_buf_string = get_out.size;
              if (get_buf_string == "-1")
              {
                // set up c_buf_str
                char * get_c_buf_str = str_cstr(get_buf_string);
                memcpy(buffer, get_c_buf_str, strlen(get_c_buf_str)+1);
              }
              else
              {
                // we got a good get FILE command; proceed to set up
                // c_buf_str and download file contents

                // download file contents
                std::ifstream ifs(get_path);
                std::string content( (std::istreambuf_iterator<char>(ifs) ),
                                     (std::istreambuf_iterator<char>()    ));
                
                std::cout << "file content: " << content << '\n';

                std::cout << "writing file...";

                // get file name to write out
                std::string file_name = strip_slashes(cmd);
                std::cout << file_name << '\n';

                // write file to local dir
                std::ofstream out(file_name);
                out << content;
                out.close();

                // write newline to buffer, then copy file content to pass to
                // client
                
                get_buf_string.append("\n").append(content);
                char * get_c_buf_str = str_cstr(get_buf_string);
                memcpy(buffer, get_c_buf_str, strlen(get_c_buf_str)+1);
              }

              break;
            }
            case 2:
            {
              // set up info request path
              std::string info_path = DIR;
              info_path.append(get_info_file_name(cmd));
              char * info_dir = str_cstr(info_path);
              printf("running stat on dir: %s\n", info_dir);
              info_out info_out = get_stat(info_dir);

              // reset path; not sure if necessary
              info_path.clear();

              // set up output string
              std::string info_buf_string = info_out.time.append("\t").append(info_out.size).append("\n");
              char * info_c_buf_str = str_cstr(info_buf_string);
              memcpy(buffer, info_c_buf_str, strlen(info_c_buf_str)+1);

              fflush(stdout);
              break;
            }
          }

					send(sd , buffer , strlen(buffer) , 0 );
          fflush(stdout);

          // testing
          std::cout << cstr_str(buffer) << '\n';
          // end testing

          // Zero out the buffer so no residual data next iteration
          bzero(buffer, 1025);
				}
			}
		}
	}
		
	return 0;
}

char * str_cstr(std::string msg)
{
  char * cstr_msg = new char [msg.length() + 1];
  std::strcpy (cstr_msg, msg.c_str());
  return cstr_msg;
}

std::string cstr_str(char * msg)
{
  std::string str = msg;
  return str;
}

int parse_cmd(std::string cmd)
{
  // return int for cmd type:
  // 2 for info FILE
  // 1 for get FILE
  // 0 for exit
  // -1 for unknown

  if (cmd.substr(0, 4) == "info")
  {
    std::cout << "We got an info request" << '\n';
    return 2;
  }
  else if (cmd.substr(0, 3) == "get")
  {
    std::cout << "We got a get request" << '\n';
    return 1;
  } else if (cmd.substr(0, 4) == "exit")
  {
    std::cout << "We got an exit request" << '\n';
    return 0;
  }
  else return -1;
}

info_out get_stat(char * path)
{
  struct stat buf;
  int success = stat(path, &buf);
  info_out out;
  if (success == -1)
  {
    out.size = "-1";
    out.time = "-1";
    return out;
  }

  // time setup
  struct timespec t = buf.st_mtim;
  time_t t_mod = time((time_t*)&t.tv_sec);
  tm *tm = localtime(&t_mod);
  std::string year = int_to_str(tm->tm_year + 1900);
  std::string month = int_to_str(tm->tm_mon + 1);
  std::string day = int_to_str(tm->tm_mday);
  std::string hour = int_to_str(tm->tm_hour);
  std::string min = int_to_str(tm->tm_min);
  std::string sec = int_to_str(tm->tm_sec).append(".0000");

  std::string out_str = year.append("-").append(month).append("-").append(day).append(" ");
  out_str.append(hour).append(":").append(min).append(":").append(sec);
  
  // std::cout << tm->tm_mday << '\n';
    
  // std::cout << "file size:\t" << buf.st_size
  //           << "\nfile modified:\t" << out_str;
  
  // std::cout << std::endl;

  out.time = out_str;
  out.size = std::to_string(buf.st_size);

  return out;
}

std::string int_to_str(int t)
{
  return std::to_string(t);
}

std::string get_info_file_name(std::string s)
{
  int s_len = s.length();
  std::string f_name = "";
  f_name.append(s.substr(5, s.length() - 1));

  return f_name;
}

std::string get_get_file_name(std::string s)
{
  int s_len = s.length();
  std::string f_name = "";
  f_name.append(s.substr(4, s.length() - 1));

  return f_name;
}

std::string strip_slashes(std::string s)
{
  // use rfind to find last '/' char
  std::string out;
  out = s.substr(s.rfind('/') + 1, s.length() - 1);
  return out;
}