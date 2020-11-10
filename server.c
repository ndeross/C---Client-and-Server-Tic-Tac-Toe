// Server program 


#include <string.h>
#include <stdbool.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h> 
#include <pthread.h> 
#include <stdlib.h>

#define BUFSIZE 1000

int main()
{

int fd;
int dummyfd; 
int clientOneFD; 
int clientTwoFD; 

int numClients = 0; 
char *ServerFIFO = "/tmp/ServerFIFO";

pid_t clientOne; 
pid_t clientTwo; 

char client1Name[25]; 
char client2Name[25]; 


mkfifo(ServerFIFO, 0666);

printf("waiting...\n"); 

fd = open(ServerFIFO, O_RDONLY);

while (1) { 
if (read(fd, &client1Name, sizeof(client1Name))) {break;} }

close(fd); 
unlink(ServerFIFO); 


mkfifo(ServerFIFO, 0666);

printf("waiting...\n"); 

dummyfd = open(ServerFIFO, O_RDONLY);

while (1) { 
if (read(fd, &client2Name, sizeof(client2Name))) {break;} }


printf(client1Name); 
printf("\n"); 

printf(client2Name); 
printf("\n"); 


clientOneFD = open(client1Name, O_RDWR); 
clientTwoFD = open(client2Name, O_RDWR); 



return 0; 

} 
