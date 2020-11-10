
// Nicholas DeRoss 
// Systems Programming 
// Tic-Tac-Toe client 
// 3/30/20



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

char buf[BUFSIZE]; 

char board[SIDE][SIDE]; 
char serverBoard[SIDE][SIDE]; 
int  moves[SIDE*SIDE]; 

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
  



// A function that takes in a player number, and a move number 
//  and makes that move, if possible, incriments moveCount 
//   which checks for a draw 
void MakeMove(int player, int move) { 

char marker; 
int input; 
int playerNum; 

playerNum = player; 
input = move; 


if (playerNum == 1) { marker = 'X'; }
if (playerNum == 2) { marker = 'O'; } 


switch (input) { 

	case 0: printf("Thanks for Playing!\n"); exit(0); 

	case 1: 
	
	if (board[0][0] == ' ') 
	{ board[0][0] = marker;
	  movesMade++; }
	else { printf("Space already marked!"); } 

	break; 
	
	case 2: 
	
	if (board[0][1] == ' ') 
	{ board[0][1] = marker;
	  movesMade++; }
	else { printf("Space already marked!"); } 
		
	break; 

	case 3: 

	if (board[0][2] == ' ') 
	{  board[0][2] = marker;
	  movesMade++; }
	else { printf("Space already marked!"); } 
 
	break; 
	
	case 4:

	if (board[1][0] == ' ') 
	{ board[1][0] = marker; 
          movesMade++;}
	else { printf("Space already marked!"); } 

	break; 

	case 5: 

	if (board[1][1] == ' ') 
	{ board[1][1] = marker; 
	  movesMade++; }
	else { printf("Space already marked!"); } 

	break; 
	
	case 6: 

	if (board[1][2] == ' ') 
	{ board[1][2] = marker;
          movesMade++; }
	else { printf("Space already marked!"); }  

	break; 

	case 7: 

	if (board[2][0] == ' ') 
	{ board[2][0] = marker;
	  movesMade++; }
	else { printf("Space already marked!"); } 
 
	break; 
	
	case 8:
	
	if (board[2][1] == ' ') 
	{ board[2][1] = marker;
	  movesMade++; }
	else { printf("Space already marked!"); }  

	break; 

	case 9:

	if (board[2][2] == ' ') 
	{ board[2][2] = marker;
	  movesMade++; }
	else { printf("Space already marked!"); } 
 
	break; 
	
	default: printf("Invalid Move!\n"); 

}

return; 

} 



// the main program for tic-tac-toe, broken up into two sections
// one for player 1 and one for player 2, which is determined by 
// reading from the server pipe their order of connection 

int main()
{
 
int fd; 
int ServerFD; 

char ClientFIFO[30];
char *ServerFIFO = "/tmp/ServerFIFO";
pid_t ClientID; 
char processStr[10]; 
int clientNumber = 0;
char marker;  
int move;
char moveChar;  
 
bool GameOver = false; 


// creates the fifo name based on PID, appending it to the end of the 
//  predetermined string 

ClientID = getpid();  
sprintf(processStr, "%ld", ClientID);
strcpy(ClientFIFO, "/tmp/ClientFIFO"); 
strcat(ClientFIFO, processStr);


// This block writes the client fifo name, determined by the pid 
//  to the server
///////////////////////////////////////////////////////////////

ServerFD = open(ServerFIFO, O_WRONLY); 
if (ServerFD == -1) 
	{ perror("Can't connect to server.. terminating"); 
	  exit(-1); 
	}


write(ServerFD, &ClientFIFO, sizeof(ClientFIFO)); 
if (ServerFD == -1) 
	{ perror("Can't connect to server.. terminating"); 
	  exit(-1); 
	}
  
close(ServerFD); 
if (fd == -1) 
	{ perror("Can't close connection.. terminating"); 
	  exit(-1); 
	}


if (ServerFD == -1) { perror("ERROR CLOSING FILE"); } 

////////////////////////////////////////////////////////////




printf("Waiting on other player, please stand by...\n"); 

mkfifo(ClientFIFO, 0666); 

fd = open(ClientFIFO, O_RDONLY); 
if (fd == -1) 
	{ perror("Can't connect.. terminating"); 
	  exit(-1); 
	}


read(fd, &clientNumber, sizeof(clientNumber));
if (fd == -1) 
	{ perror("Can't connect.. terminating"); 
	  exit(-1); 
	}


close(fd); 
if (fd == -1) 
	{ perror("Can't close connection.. terminating"); 
	  exit(-1); 
	}



printf("Recived: "); printf("%d", clientNumber); // reads the client number
						 // whatever this number is determines which player it is 
printf("\n"); 




// The following executes for player 1 
// player 1 makes a move, sends it to player 2 
// through the server, and waits for player 2's move 

if (clientNumber == 1) {

printf("Welcome Player 1!\n\n");
marker = 'X'; 

ShowInstructions(); 
Initialize(board, moves);
ShowBoard(board);


while(1) {


printf("Player "); printf("%d", clientNumber); printf(" Make your move!\n");

scanf(" %c", &moveChar); // scan move

move = atoi(&moveChar); // convert to int 
 
ShowBoard(board); // show the board 

MakeMove(clientNumber, move); // execute the move 

GameOver = gameOver(board); 


// This block writes the move to the server to send to player 2 
//   to maintain board on server 

//////////////////////////////////////////////////
fd = open(ClientFIFO, O_WRONLY);
if (fd == -1) 
	{ perror("CONNECTION ISSUE.. terminating"); 
	  exit(-1); 
	}

write(fd, &moveChar, sizeof(moveChar));
if (fd == -1) 
	{ perror("Can't write to server.. terminating"); 
	  exit(-1); 
	}

 
close(fd); 
if (fd == -1) 
	{ perror("Can't close connection.. terminating"); 
	  exit(-1); 
	}

//////////////////////////////////////////////////

if (GameOver == true)              // check win conditions 
    {printf("YOU WON!\n");
	ShowBoard(board);
	 exit(0);  } 

if (movesMade == 9) 
    {printf("It's a Draw! \n"); 
	ShowBoard(board);
	exit(0); } 

/////////////////////////////////////////////////

ShowBoard(board);


// Waits for player2 move and makes it on the board 

//////////////////////////////////////////////

printf("Player 2's turn... Waiting\n"); 

fd = open(ClientFIFO, O_RDONLY);
if (fd == -1) 
	{ perror("Can't connect.. terminating"); 
	  exit(-1); 
	}


read(fd, &moveChar, sizeof(moveChar)); 
if (fd == -1) 
	{ perror("Can't connect.. terminating"); 
	  exit(-1); 
	}

move = atoi(&moveChar); 
MakeMove(2, move); 
ShowBoard(board); 
GameOver = gameOver(board);

close(fd);
if (fd == -1) 
	{ perror("Can't close connection.. terminating"); 
	  exit(-1); 
	}


// check win conditions 

if (GameOver == true) 
    {printf("YOU LOST!\n");
     ShowBoard(board);
	 exit(0); } 

if (movesMade == 9) 
    {printf("It's a Draw! \n");
     ShowBoard(board);
     exit(0); } 


fflush(stdin); // flush input 

   }

}


// If the player is 2, its the same process as player 1 in 
//  reverse, except it reads and then writes 



if (clientNumber == 2) {

printf("Welcome Player 2!\n\n"); 
marker = 'X'; 

ShowInstructions(); 
Initialize(board, moves);
ShowBoard(board);

while (1) {

printf("Player 1's turn... Waiting\n"); 

fd = open(ClientFIFO, O_RDONLY);
if (fd == -1) 
	{ perror("Can't connect.. terminating"); 
	  exit(-1); 
	}


read(fd, &moveChar, sizeof(moveChar)); 
if (fd == -1) 
	{ perror("Can't connect.. terminating"); // reads player1 move 
	  exit(-1); 
	}
                                                  
move = atoi(&moveChar); 
MakeMove(1, move);
ShowBoard(board); 
 
GameOver = gameOver(board);

close(fd); 
if (fd == -1) 
	{ perror("Can't connect.. terminating"); 
	  exit(-1); 
	}



if (GameOver == true) 
    {printf("YOU LOST!\n");
     ShowBoard(board); 
	 exit(0);  } 

if (movesMade == 9) 
    {printf("It's a Draw! \n");
     ShowBoard(board);
	 exit(0); } 


printf("Player "); printf("%d", clientNumber); printf(" Make your move!\n");

ShowBoard(board); 

fflush(stdin); 

scanf(" %c", &moveChar);


fd = open(ClientFIFO, O_WRONLY);
if (fd == -1) 
	{ perror("Can't connect.. terminating"); 
	  exit(-1); 
	}


write(fd, &moveChar, sizeof(moveChar));
if (fd == -1) 
	{ perror("Can't write to server.. terminating"); 
	  exit(-1); 
	}
 
close(fd);
if (fd == -1) 
	{ perror("Can't close connection.. terminating"); 
	  exit(-1); 
	}



move = atoi(&moveChar);

MakeMove(2, move); 
ShowBoard(board);
GameOver = gameOver(board); 

if (GameOver == true) 
    {printf("YOU WON!\n");
	ShowBoard(board);
	 exit(0);  } 

if (movesMade == 9) 
    {printf("It's a Draw! \n");
	ShowBoard(board);
	 exit(0); } 


fflush(stdin);  

}

}


// unlink both servers 

unlink(ServerFIFO);  
unlink(ClientFIFO); 
 
return 0; 

}
