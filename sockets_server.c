#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "randperm.c"
#include "defs.h"

;int randperm(int *,int );
struct deck;

//function to send a message, makes body of code nice and short
void sendMessage(int socketID, char *messageForClient)
{
	char sendBuffer[4096];
    sprintf(sendBuffer, messageForClient);
    int sendSuccess = write(socketID , sendBuffer , strlen(sendBuffer));
}

int main(int argc, char *argv[])
{
	int firstPort=atoi(argv[1]);
	struct deck deckOfCards;
	int i;
	
	struct sockaddr_in serverParameters1;
	int addrlen1=sizeof(serverParameters1);
	
	serverParameters1.sin_family = AF_INET;
	serverParameters1.sin_addr.s_addr = INADDR_ANY;
	serverParameters1.sin_port = htons(firstPort);

	int socketState1=socket(AF_INET, SOCK_STREAM, 0);

	int bindState1=bind(socketState1, (struct sockaddr *)&serverParameters1, addrlen1);
	if(bindState1<0)
	{
		printf("Failed to bind Socket 1\n");
		exit(0);
	}
	
	//Listen for incoming connection
	int listenState1=listen(socketState1, 5);
	printf("Listening for incoming connection.../n");
	//Accept connection
	int socketID = accept(socketState1,(struct sockaddr *)&serverParameters1,(socklen_t*)&addrlen1);
	printf("Accepting incoming connection.../n");

	//Create buffer to read command from client
	char buffer[1024]={0};
	//Read buffer, check for 'deal'
	int readToBuffer = read(socketID, buffer, 1024);
	printf("Reading from buffer.../n");

	//Create string for desired command, then 
	//Use strncmp to compare only the first 4 characters of buffer
	char* stringFind = "deal";
	if(strncmp (buffer,stringFind, 4) == 0)
	{
		printf("The Deal Has Begun...\n");
		for (i=0;i<52;i++)
		{
			deckOfCards.cards[i]=i;
		}
		randperm(deckOfCards.cards,52);
		write(socketID , deckOfCards.cards , 208);
	}
	else
	{
		printf("Invalid Command\n");
		exit(0);
	}

}