#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "randperm.c"
#include "defs.h"

;int randperm(int *, int);
struct deck;

void randomize(struct deck cardDeck)
{
	int i;

	for(i = 0; i < 52; i++)
		cardDeck.cards[i] = i;

	printf("****************Before*****************\n");
	for(i = 0; i < 52; i++)
		printf("%d ", cardDeck.cards[i]);

	printf("\n");
	randperm(cardDeck.cards, 52);

	printf("\n****************After****************\n");
	for(i = 0; i< 52; i++)
		printf("%d ", cardDeck.cards[i]);

	printf("\n");
}

/*struct card
{
    suit card_suit;
    value card_value;
};

struct card parse_card(int the_card)
{
    struct card temp_card;
    temp_card.suit = the_card / 13;
    temp_card.value = the_card % 13;
    return(temp_card);
};*/

int main(int argc, char *argv[])
{
	int sfd, i;
	char buffer[1024] = {0};
	char *words = "Hello World!";
	struct sockaddr_in sockIn;
	struct deck cardDeck;
	int serPort = atoi(argv[1]);				//the user should input a server port as an argument

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	sockIn.sin_family = AF_INET;
	sockIn.sin_addr.s_addr = INADDR_ANY;
	sockIn.sin_port = htons(serPort);

	int binding = bind(sfd, (struct sockaddr *) &sockIn, sizeof(sockIn));
	if(binding < 0){
		printf("Invalid port binding\n");
		exit(0);
	}

	int listening = listen(sfd, 5);
	printf("Listening for a message...\n");
	if(listening < 0){
		printf("Failed to listen\n");
		exit(0);
	}

	int accepting = accept(sfd, (struct sockaddr *) &sockIn, (socklen_t *)sizeof(sockIn));
	//blocking call
	if(accepting < 0){
		printf("Connection not accepted\n");
		exit(0);
	}
	printf("Accepted the connection!\n");

	int reading = read(sfd, buffer, (size_t) sizeof(sockIn));
	printf("Reading from client...\n");
	if(reading < 0){
		printf("Failed to read\n");
		exit(0);
	}
	
	printf("Received message: %s\n", buffer);
	char *searchingFor = "deal";
	if(strcmp(buffer, searchingFor) == 0){
		printf("The deal has begun\n");
	}
	else{
		printf("Please input a valid key word\n");
		exit(0);
	}
	
	randomize(cardDeck);
	
	int sending = write(sfd, cardDeck.cards, 208);
	printf("Sending to client...\n");
	if(sending < 0){
		printf("Failed to send\n");
		exit(0);
	}
}

//echo -n "deal" | nc 172.17.68.82 12121