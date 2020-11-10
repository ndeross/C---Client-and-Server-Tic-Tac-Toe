// Client program

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
int ServerFD; 

char ClientFIFO[30];
char *ServerFIFO = "/tmp/ServerFIFO";
pid_t ClientID; 
char processStr[10]; 


ServerFD = open(ServerFIFO, O_WRONLY); 

ClientID = getpid();  
sprintf(processStr, "%ld", ClientID); 
strcpy(ClientFIFO, "/tmp/ClientFIFO"); 
strcat(ClientFIFO, processStr);

write(ServerFD, &ClientFIFO, sizeof(ClientFIFO)); 

mkfifo(ClientFIFO, 0666);



return 0; 

} 
