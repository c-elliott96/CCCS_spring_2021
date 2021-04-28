/* 
   Christian Elliott
   Operating Systems project 02
   2021-04-27
 */

/* 
   1. Server:
   - set up socket connection using port from argv [DONE]
   - set up proper number of threads
     - #CON argv[2]
 */

/* 
   Compile instructions for thread part
   gcc -pthread *.c -o loops
 */

#include <stdio.h>
#include <stdlib.h> // atoi() convert char string to integer (for port argv)
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <pthread.h> // thread lib

#define NTHREADS 4
#define ARRAYSIZE 100000000
#define ITERATIONS ARRAYSIZE / NTHREADS

double sum = 0.0;
double a[ARRAYSIZE];
pthread_mutex_t sum_mutex;

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

int main(int argc, char *argv[])
{
  /* 
     Pthreads setup: initialize mutex and explicitly create threads in a
     joinable state (for portability). Pass each thread its loop offset
  */
  /* int i, start, tids[NTHREADS]; */
  /* pthread_t threads[NTHREADS]; */
  /* pthread_attr_t attr; */

  /* pthread_mutex_init(&sum_mutex, NULL); */
  /* pthread_attr_init(&attr); */
  /* pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); */
  /* for (i = 0; i < NTHREADS; i++) */
  /*   { */
  /*     tids[i] = i; */
  /*     pthread_create(&threads[i], &attr, do_work, (void *) &tids[i]); */
  /*   } */

  /* // Wait for all threads to complete and then print global sum */
  /* for (i = 0; i < NTHREADS; i++) */
  /*   { */
  /*     pthread_join(threads[i], NULL); */
  /*   } */
  /* printf("\n[MAIN] Done. Sum = %e", sum); */

  /* // check sum value synchronously */
  /* sum = 0.0; */
  /* for (i = 0; i < ARRAYSIZE; i++) */
  /*   { */
  /*     a[i] = i * 1.0; */
  /*     sum = sum + a[i]; */
  /*   } */
  /* printf("\n[MAIN] Check sum = %e", sum); */

  /* // Clean up and exit */
  /* pthread_attr_destroy(&attr); */
  /* pthread_mutex_destroy(&sum_mutex); */
  /* pthread_exit(NULL); */

  // Set up worker threads
  int NUM_THREADS = 1; // default = 1
  if (argc >= 3)
    {
      NUM_THREADS = atoi(argv[2]);
    }
  

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

  // Receive message from client
  while((read_size = recv(client_sock, client_message, 2000, 0)) > 0)
    {
      // Send the message back to the client
      write(client_sock, client_message, strlen(client_message));
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
