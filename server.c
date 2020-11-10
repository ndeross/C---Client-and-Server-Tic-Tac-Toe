// Nicholas DeRoss
// HW5 - Systems Programming 
// Mr. Molnar 
// 2/24/2020 

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
#define SIDE 3 


char board[SIDE][SIDE]; 
char serverBoard[SIDE][SIDE]; 
int  moves[SIDE*SIDE];  
int  playerNum; 
char inputChar[1]; 
char buf[BUFSIZE]; 

int movesMade = 0;


void ShowInstructions() 
{ 
	printf("\t\t\t Tic-Tac-Toe\n\n"); 
	printf("Choose a cell numbered from 1 to 9 as below"
			" and play\n\n\n"); 

	printf("Enter a '0' to end the game\n\n"); 
	
	printf("\t\t\t 1 | 2 | 3 \n"); 
	printf("\t\t\t--------------\n"); 
	printf("\t\t\t 4 | 5 | 6 \n"); 
	printf("\t\t\t--------------\n"); 
	printf("\t\t\t 7 | 8 | 9 \n\n"); 
	
	printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n"); 

	return; 
} 



  
// A function to show the current board status 
void ShowBoard(char board[][SIDE]) 
{ 
    printf("\n\n"); 
      
    printf("\t\t\t  %c | %c  | %c  \n", board[0][0], 
                             board[0][1], board[0][2]); 
    printf("\t\t\t--------------\n"); 
    printf("\t\t\t  %c | %c  | %c  \n", board[1][0], 
                             board[1][1], board[1][2]); 
    printf("\t\t\t--------------\n"); 
    printf("\t\t\t  %c | %c  | %c  \n\n", board[2][0], 
                             board[2][1], board[2][2]); 
   
    return; 
} 

 
void Initialize(char board[][SIDE], int moves[]) 
{      

int i;
int j;  

    // Initially the board is empty 
    for (i = 0; i < SIDE; i++) 
    { 
        for (j = 0; j < SIDE; j++) 
            board[i][j] = ' '; 
    } 
      
    for (i = 0; i < SIDE*SIDE; i++) 
         { moves[i] = i; }

return; 

} 

  
// A function that returns true if any of the row 
// is crossed with the same player's move 
bool rowCrossed(char board[][SIDE]) 
{ 

int i; 

    for  (i = 0; i < SIDE; i++) 
    { 
        if (board[i][0] == board[i][1] && 
            board[i][1] == board[i][2] &&  
            board[i][0] != ' ') 
            return (true); 
    } 
    return(false); 
} 
  
// A function that returns true if any of the column 
// is crossed with the same player's move 
bool columnCrossed(char board[][SIDE]) 
{ 

int i; 

    for (i=0; i<SIDE; i++) 
    { 
        if (board[0][i] == board[1][i] && 
            board[1][i] == board[2][i] &&  
            board[0][i] != ' ') 
            return (true); 
    } 
    return(false); 
} 
  
// A function that returns true if any of the diagonal 
// is crossed with the same player's move 
bool diagonalCrossed(char board[][SIDE]) 
{ 
    if (board[0][0] == board[1][1] && 
        board[1][1] == board[2][2] &&  
        board[0][0] != ' ') 
        return(true); 
          
    if (board[0][2] == board[1][1] && 
        board[1][1] == board[2][0] && 
         board[0][2] != ' ') 
        return(true); 
  
    return(false); 
} 
  
// A function that returns true if the game is over 
// else it returns a false 

bool gameOver(char board[][SIDE]) 
{ 
    return(rowCrossed(board) || columnCrossed(board) 
            || diagonalCrossed(board) ); 
} 
  

// The same make move as client, to maintin board integrity 

void MakeMove(int player, int move) { 

char marker; 
int input; 
int playerNum; 

playerNum = player; 
input = move; 


if (playerNum == 1) { marker = 'X'; }
if (playerNum == 2) { marker = 'O'; } 


switch (input) { 

	case 0: perror("One of the clients have chosen to end the game\n"); exit(0); 

	case 1: 
	
	if (board[0][0] == ' ') 
	{ board[0][0] = marker;
	  movesMade++; }
	else { } 

	break; 
	
	case 2: 
	
	if (board[0][1] == ' ') 
	{ board[0][1] = marker;
	  movesMade++; }
	else { } 
		
	break; 

	case 3: 

	if (board[0][2] == ' ') 
	{  board[0][2] = marker;
	  movesMade++; }
	else { } 
 
	break; 
	
	case 4:

	if (board[1][0] == ' ') 
	{ board[1][0] = marker; 
          movesMade++;}
	else { } 

	break; 

	case 5: 

	if (board[1][1] == ' ') 
	{ board[1][1] = marker; 
	  movesMade++; }
	else { } 

	break; 
	
	case 6: 

	if (board[1][2] == ' ') 
	{ board[1][2] = marker;
          movesMade++; }
	else { }  

	break; 

	case 7: 

	if (board[2][0] == ' ') 
	{ board[2][0] = marker;
	  movesMade++; }
	else { } 
 
	break; 
	
	case 8:
	
	if (board[2][1] == ' ') 
	{ board[2][1] = marker;
	  movesMade++; }
	else { }  

	break; 

	case 9:

	if (board[2][2] == ' ') 
	{ board[2][2] = marker;
	  movesMade++; }
	else { } 
 
	break; 
	
	default: printf("Invalid Move!\n"); 

}

return; 


} 


int main(int argc, char* argv[])
{

int ServerFD;
int ClientFD;
 
int clientOneFD; 
int clientTwoFD; 

int numClients = 0; 
char *ServerFIFO = "/tmp/ServerFIFO";

pid_t clientOne; 
pid_t clientTwo; 

char client1Name[25]; 
char client2Name[25]; 

int client1 = 1; 
int client2 = 2; 

char player1move; 
char player2move[2]; 

int  currentMove;
int  currentMove2; 

bool GameOver = false;  
 

// Connect to player 1, read fifo name, establish connection 

/////////////////////////////////////////////////


printf("Waiting for player 1...\n"); 


int check = mkfifo(ServerFIFO, 0666); 

ServerFD = open(ServerFIFO, O_RDONLY); 
if (ServerFD == -1) { 
perror("Cant open inital fifo for client 1 input"); 
exit(1); 
} else { printf("FIFO FOR CLIENT 1 OPEN\n"); sleep(1); } 

check = read(ServerFD, &client1Name, sizeof(client1Name));
if (check == -1) { 
perror("Error reading client name 1"); 
exit(-1);}

else { printf("Recieved: "); printf("%s", client1Name); } 

printf("\n");

close(ServerFD); 
if (ServerFD == -1) { 
perror("CLOSING FILE - disconnected"); 
exit(1); 
}

///////////////////////////////////////////////////



// Connect to player 1, read fifo name, establish connection 

/////////////////////////////////////////////////

printf("Waiting for player 2 to connect...\n"); 


ServerFD = open(ServerFIFO, O_RDONLY); 
if (ServerFD == -1) { 
perror("Cant open inital fifo for client 2 input -- DISCONNECTED"); 
exit(1); 
} 

else { printf("FIFO FOR CLIENT 2 OPEN\n"); sleep(1); } 


check = read(ServerFD, &client2Name, sizeof(client2Name));
if (check == -1) { 
perror("Error reading client name 2"); 
exit(-1);
} 

printf("\n");

close(ServerFD); 
if (ServerFD == -1) { 
perror("Closing file -- disconnected"); 
exit(1); 
}



ClientFD = open(client1Name, O_WRONLY); 
if (ClientFD == -1) { 
perror("Cant open inital fifo for client 1 output 'x'"); 
exit(1); 
} 

check = write(ClientFD, &client1, sizeof(client1));
if (check == -1) { 
perror("ERROR WRITING TO CLIENT 1 'X' "); 
exit(-1);
} 

printf("\n");

/////////////////////////////////////////////////////

close(ClientFD); 


ClientFD = open(client2Name, O_WRONLY); 
if (ClientFD == -1) { 
perror("Cant open inital fifo for client 2 output 'x'"); // opens for output 
exit(1); 
}  


check = write(ClientFD, &client2, sizeof(client2));
if (check == -1) { 
perror("ERROR WRITING TO CLIENT 2 'X' "); 
exit(-1);
}  

printf("\n");

close(ClientFD);
if (ClientFD == -1) { 
perror("CLosing file -- disconnected"); 
exit(1);  
}


Initialize(board, moves);
ShowBoard(board);  



// runs the game in the form of taking input from 1, 
//  making the move, sending to 2, and vice versa 
//  loops until game over 

do {

fflush(stdin); 

sleep(1); 

ClientFD = open(client1Name, O_RDONLY);
 
if (ClientFD == -1) { 
perror("Opening file - disconnected"); 
exit(1); 
} 

check = read(ClientFD, &player1move, sizeof(player1move));
if (check == -1) { 
perror("ERROR READING CLIENT 1 MOVE - disconnected "); 
exit(-1);
} 

close(ClientFD);
if (ClientFD == -1) { 
perror("Closing file - disconnected");
exit(1); 
}

currentMove = atoi(&player1move);  // reads player 1's move 
MakeMove(client1, currentMove);   // makes it on the board 
GameOver = gameOver(board);   
ShowBoard(board); 


ClientFD = open(client2Name, O_WRONLY);
 
if (ClientFD == -1) { 
perror("Opening file -- disconnected"); 
exit(1); 
} 

check = write(ClientFD, &player1move, sizeof(player1move)); // writes to player 2 

if (check == -1) { 
perror("ERROR READING CLIENT 2 MOVE -- disconnected"); 
exit(-1);
} 

close(ClientFD);
if (ClientFD == -1) 
{ perror("Error closing FIFO file"); 
  exit(-1); 
} 


if (GameOver == true) 
    { printf("GAME OVER!\n"); exit(0);  } 


ClientFD = open(client2Name, O_RDONLY);  
if (ClientFD == -1) { 
perror("opening connection error"); 
exit(-1); 
} 

check = read(ClientFD, &player2move, sizeof(player2move)); // reads player 2's move
if (check == -1) { 
perror("ERROR READING CLIENT 2 MOVE "); 
exit(-1);
}


close(ClientFD);
if (ClientFD == -1) 
	{ perror("CLOSING FILE"); exit(-1); }  


// this line is producing a warning but nothing else works 
//  so to get this in on time I had to leave it to 
//   work on the rest 

currentMove = atoi(&player2move);


MakeMove(client2, currentMove);  // makes the move after converting
GameOver = gameOver(board); 


ClientFD = open(client1Name, O_WRONLY);
if (ClientFD == -1) { 
perror("Opening file"); 
exit(-1); }


check = write(ClientFD, &player2move, sizeof(player2move));
  if (check == -1) 
	{ perror("CONNECTING TO CLIENT 2, POSSIBLE DISCONNECT"); exit(-1); }


close(ClientFD); 
if (ClientFD == -1) 
	{ perror("CLOSING FILE"); exit(-1); } 


ShowBoard(board);


if (movesMade == 9) 
   { printf("DRAW!\n"); exit(0); } 


if (GameOver == true) 
    { printf("GAME OVER!\n"); exit(0); }  


} while(1); 


// unlinks the fifos 

unlink(ServerFIFO);  
unlink(client1Name); 
unlink(client2Name); 

return 0; 


}

 
      
    
    


























      
      
                   
                                   
