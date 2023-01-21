#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/select.h>
#include <dirent.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
    
#define MAXLINE 508

int main(int argc, char *argv[]) { 
	if(argc < 1) {
		printf("Define a port number\n");
	}
    int sockfd; 
    struct sockaddr_in servaddr; 
    
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    memset(&servaddr, 0, sizeof(servaddr)); 
        
    // Filling server information 
	uint16_t PORT;
    const char *host_port = argv[1];
    // memcpy(&PORT, host_port, sizeof(PORT));  
    PORT = (unsigned short) strtoul(host_port, NULL, 0);
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
        
    uint32_t n, len; 
    len = sizeof(servaddr);  //len is value/result 
    char username[20];
    printf("Enter your username within 20 characters!\n");
    scanf("%s", username);

    sendto(sockfd, (const char *)username, strlen(username), 
        0, (const struct sockaddr *) &servaddr,  
            len); 
    printf("Welcome to ChatRoom, %s!\n", username);
    printf("Up to 4 people can join this chatroom!\n"); 
    printf("Type EXIT to leave the room!\n");
    
    while(1)
    {
        char buffer[MAXLINE]; 
        char message[MAXLINE];
        const int exit_command = 5;    
 
        printf("Type a message, otherwise ENTER to skip...\n");
        scanf("%s", message);
        char c = message[0];
        if(strncmp( message, "EXIT", exit_command )==0) {
            break;
        } else if (c == '\n') {
            continue;
        }
        sendto(sockfd, (const char *)message, strlen(message), 
        0, (const struct sockaddr *) &servaddr,  
            len);

        n = recvfrom(sockfd, (char *)buffer, MAXLINE, 0, (struct sockaddr *) &servaddr, &len); 
        if ( n > 0)
        {
            buffer[n] = '\0'; 
            printf("%s\n", buffer); 
        }//if
    }
    close(sockfd); 
    printf("Bye %s!", username);

    return 0; 
}