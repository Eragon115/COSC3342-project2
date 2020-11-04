#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include "defs.h"

;enum suit{spades,hearts,diamonds,clubs};
enum value{ace,two,three,four,five,six,seven,eight,nine,ten,jack,queen,king};

struct card
{
	enum suit card_suit;
	enum value card_value;
};

struct card parse_card(int the_card){
	struct card temp_card;
	temp_card.card_suit=the_card/13;
	temp_card.card_value=the_card%13;
	return(temp_card);
};

int main(int argc, char *argv[]){
	int sfd, i;
	char buffer[1024];
	int intArray[52]={0};
	struct sockaddr_in sockIn;
	struct deck cardDeck;
	char *clientAddress = argv[1];					//the user should input IP Address as the first argument
	int clientPort = atoi(argv[2]);					//the user should input the port as the second argument
	
	char *suitStrings[] = {"Spades", "Hearts","Diamonds", "Clubs"};
	char *valueStrings[] = {"Ace","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King"};

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	sockIn.sin_family = AF_INET;				//set up client socket in struct
	sockIn.sin_addr.s_addr = INADDR_ANY;
	sockIn.sin_port = htons(clientPort);
	
	int INET_addr = inet_pton(AF_INET, clientAddress, &sockIn.sin_addr);
	if(INET_addr<0){
		printf("Failed to convert string to usable IP\n");
        exit(0);
    }
	
	int connecting = connect(sfd, (struct sockaddr *) &sockIn, sizeof(sockIn));
	if(connecting < 0){
		printf("Failed to connect to the server.\n");
		exit(0);
	}

	sprintf(buffer, "deal");
	ssize_t sending = send(sfd, buffer, strlen(buffer), 0);

    int reading = recv(sfd, intArray, 1024, 0);
	
	for (i = 0; i < 52; i++){
		struct card temp = parse_card(intArray[i]);
		int cardSuit = temp.card_suit;
		int cardVal = temp.card_value;

		printf("Card %d: %s of %s\n", i+1, valueStrings[cardVal], suitStrings[cardSuit]);
    }
}