#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "defs.h"

extern int randperm(int *, int );
int randomize(struct deck cardDeck)
{
	int i;
	some_array = cardDeck.cards

	for(i = 0; i < 52; i++)
		some_array[i] = i;

	printf("****************Before*****************\n");
	for(i = 0; i < 52; i++)
		printf("%d ", some_array[i]);

	randperm(some_array, 52);

	printf("\n****************After****************\n");
	for(i = 0; i< 52; i++)
		printf("%d ", some_array[i]);

	printf("\n");
	return(0);
}

int main(int argc, char *argv[])
{
        int sfd;
        char buffer[1024];
        char *words = "Hello World!";
        struct sockaddr_in sockIn;
        int serPort = atoi(argv[1]);
            //the user should input a server port as an argument

        sfd = socket(AF_INET, SOCK_STREAM, 0);
        sockIn.sin_family = AF_INET;
        sockIn.sin_addr.s_addr = INADDR_ANY;
        sockIn.sin_port = htons(serPort);

        int binding = bind(sfd, (struct sockaddr *) &sockIn, sizeof(sockIn));
		if(binding < 0){
            printf("Invalid port binding\n");
			exit(0);
        }

        int listening = listen(sfd, 1);
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

        int reading = read(sfd, words, (size_t) sizeof(sockIn));
        printf("Reading from client...\n");
        if(reading < 0){
            printf("Failed to read\n");
			exit(0);
        }
		
		printf("Received message: %s\n", words);
		char *searchingFor = "deal";
		if(strcmp(words, searchingFor) == 0){
			printf("The deal has begun\n");
			//send to deal function
		}
		else{
			printf("Please input a valid key word\n");
			//return to listening loop
		}
}

//echo -n "deal" | nc 172.17.68.82 12121