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

//function to send a message
void sendMessage(int socketID, char *messageForClient)
{
	char sendBuffer[4096];
    sprintf(sendBuffer, messageForClient);
    int sendSuccess = write(socketID , sendBuffer , strlen(sendBuffer));
}

int main(int argc, char *argv[])
{
	int Port = atoi(argv[1]);
	struct deck cardDeck;
	int i;
	
	struct sockaddr_in sockIn;
	int sockLen=sizeof(sockIn);
	
	sockIn.sin_family = AF_INET;
	sockIn.sin_addr.s_addr = INADDR_ANY;
	sockIn.sin_port = htons(Port);

	int socketState1=socket(AF_INET, SOCK_STREAM, 0);

	int bindState1=bind(socketState1, (struct sockaddr *)&sockIn, sockLen);
	printf("Binding server socket to address...\n");
	if(bindState1<0)
	{
		printf("Failed to bind Socket 1\n");
		exit(0);
	}
	
	//Listen for incoming connection
	int listenState1=listen(socketState1, 5);
	printf("Listening for incoming connection...\n");
	//Accept connection
	int socketID = accept(socketState1,(struct sockaddr *)&sockIn,(socklen_t*)&sockLen);
	printf("Accepting incoming connection...\n");

	//Create buffer to read command from client
	char buffer[1024]={0};
	//Read buffer, check for 'deal'
	int readToBuffer = read(socketID, buffer, 1024);
	printf("Reading from buffer...\n");

	//Create string to find in buffer
	//Use strncmp to compare only the first 4 characters of buffer
	char* stringFind = "deal";
	if(strncmp (buffer,stringFind, 4) == 0)
	{
		printf("The Deal Has Begun...\n");
		for (i=0;i<52;i++)
		{
			cardDeck.cards[i]=i;
		}
		randperm(cardDeck.cards,52);
		write(socketID , cardDeck.cards , 208);
	}
	else
	{
		printf("Please send a valid command\n");
		exit(0);
	}

}