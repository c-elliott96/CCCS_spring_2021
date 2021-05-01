/* 
   Christian Elliott
   Operating Systems project 02
   2021-04-27
 */

/* 
   TODO:
   1. Set up main to pass connections off to threads, to 
      maintain client connection asynchronously
   2. Implement command parser to decide on command function to call
   3. Implement command functions "info FILE" and "get FILE" and "exit"
 */

/* 
   Compile instructions for thread part
   gcc -pthread *.c -o loops
 */

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <pthread.h> // thread lib
#include <stdlib.h> // atoi() convert char string to integer (for port argv)

#define NTHREADS 4
#define ARRAYSIZE 100000000
#define ITERATIONS ARRAYSIZE / NTHREADS

double sum = 0.0;
double a[ARRAYSIZE];
pthread_mutex_t sum_mutex;

pthread_mutex_t lock;

void *do_work(void *tid)
{
  int i, start, *mytid, end;
  double mysum = 0.0;

  // Initialize my part of the global array and keep local sum
  mytid = (int *) tid;
  start = (*mytid * ITERATIONS);
  end = start + ITERATIONS;
  printf("\n[Thread %5d] Doing iterations \t%10d to \t %10d", *mytid, start, end - 1);
  for (i = start; i < end; i++)
    {
      a[i] = i * 1.0;
      mysum = mysum + a[i];
    }

  // Lock the mutex and update the global sum, then exit
  pthread_mutex_lock (&sum_mutex);
  sum = sum + mysum;
  pthread_mutex_unlock (&sum_mutex);
  pthread_exit(NULL);
}



void dispatch_worker(void *WORKERS)
{
  
}

int main(int argc, char *argv[])
{
  int socket_desc, client_sock, c, read_size;
  struct sockaddr_in server, client;
  char client_message[2000];

  // Create socket
  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_desc == -1)
    {
      printf("Could not create socket");
    }
  puts("Socket created");

  // Get port number; currently expecting argv[1] to be port
  int port = 8888;
  if (argc >= 2)
    {
      port = atoi(argv[1]);
    }
  
  // Prepare the sockaddr_in structure
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(port);

  // Bind
  if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
      perror("bind failed. Error");
      return 1;
    }
  puts("Bind done");

  // Listen
  listen(socket_desc, 3);

  // Accept incoming connection
  puts("Waiting for incoming connections ...");
  c = sizeof(struct sockaddr_in);

  // Accept connection from an incoming client
  client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
  if (client_sock < 0)
    {
      perror("accept failed");
      return 1;
    }
  puts("Connection accepted");

  // Set up worker threads
  int NUM_THREADS = 1; // default = 1
  if (argc >= 3)
    {
      NUM_THREADS = atoi(argv[2]);
    }
  pthread_t WORKERS[NUM_THREADS];
  pthread_attr_t attr;

  pthread_mutex_init(&lock, NULL);
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  /* 
     @param WORKERS[]: worker container. Likely to be switched to FIFO queue
     @param attr: I think it's used for making threads "detached"... need
       more info here. Might not need to modify its behavior.
   */

  // Receive message from client
  while((read_size = recv(client_sock, client_message, 2000, 0)) > 0)
    {
      // receive message, send to parser and then to dispatcher accordingly
      printf("Client message: %s\n", client_message);
      fflush(stdout);
      
      // Send the message back to the client
      write(client_sock, client_message, strlen(client_message));

      // reset client_message
      memset(client_message, 0, sizeof client_message);      
    }

  if (read_size == 0)
    {
      puts("Client disconnected");
      fflush(stdout);
    }
  else if (read_size == -1)
    {
      perror("recv failed");
    }

  return 0;
}
