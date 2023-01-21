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
    
// Driver code 
int main(int argc, char *argv[]) { 
    if(argc < 1) {
		printf("Define a port number\n");
	}
    int sockfd; 
    struct sockaddr_in servaddr, cliaddr1, cliaddr2, cliaddr3, cliaddr4; 
        
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
        
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr1, 0, sizeof(cliaddr1));
    memset(&cliaddr2, 0, sizeof(cliaddr2));  
    memset(&cliaddr3, 0, sizeof(cliaddr3));     
    memset(&cliaddr4, 0, sizeof(cliaddr4)); 

    // Filling server information
    uint16_t PORT = 0;
    const char *host_port = argv[1];
    PORT = (unsigned short) strtoul(host_port, NULL, 0);
    // memcpy(&PORT, host_port, sizeof(PORT)); 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
        
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
        
    uint32_t len1 = 0, len2 = 0, len3 = 0, len4 = 0, n = 0; 
   const char temp[3] = {"..."}; 
    while(1)
    {
        char buffer[MAXLINE]; 
        len1 = sizeof(cliaddr1);  //len is value/result 
        len2 = sizeof(cliaddr2);
        len3 = sizeof(cliaddr3);
        len4 = sizeof(cliaddr4);
        if ((n = recvfrom(sockfd, (char *)buffer, MAXLINE, 0, 
                    ( struct sockaddr *) &cliaddr1, &len1)) > 0)
        {
            buffer[n] = '\0';
            printf("User1 : %s\n", buffer);
            sendto(sockfd, (const char *)temp, strlen(temp),  
                    0, (const struct sockaddr *) &cliaddr1, len1);  
            sendto(sockfd, (const char *)buffer, strlen(buffer),  
                    0, (const struct sockaddr *) &cliaddr2, len2); 
            sendto(sockfd, (const char *)buffer, strlen(buffer),  
                    0, (const struct sockaddr *) &cliaddr3, len3); 
            sendto(sockfd, (const char *)buffer, strlen(buffer),  
                    0, (const struct sockaddr *) &cliaddr4, len4); 
        }
        else if ((n = recvfrom(sockfd, (char *)buffer, MAXLINE, 0, 
                    ( struct sockaddr *) &cliaddr2, &len2)) > 0)
        {
            buffer[n] = '\0';
            printf("User2 : %s\n", buffer); 
            sendto(sockfd, (const char *)buffer, strlen(buffer),  
                    0, (const struct sockaddr *) &cliaddr1, len1); 
            sendto(sockfd, (const char *)temp, strlen(temp),  
                    0, (const struct sockaddr *) &cliaddr2, len2); 
            sendto(sockfd, (const char *)buffer, strlen(buffer),  
                    0, (const struct sockaddr *) &cliaddr3, len3); 
            sendto(sockfd, (const char *)buffer, strlen(buffer),  
                    0, (const struct sockaddr *) &cliaddr4, len4); 
        }
        else if ((n = recvfrom(sockfd, (char *)buffer, MAXLINE, 0, 
                    ( struct sockaddr *) &cliaddr3, &len3)) > 0)
        {
            buffer[n] = '\0';
            printf("User3 : %s\n", buffer); 
            sendto(sockfd, (const char *)buffer, strlen(buffer),  
                    0, (const struct sockaddr *) &cliaddr1, len1); 
            sendto(sockfd, (const char *)buffer, strlen(buffer),  
                    0, (const struct sockaddr *) &cliaddr2, len2);
            sendto(sockfd, (const char *)temp, strlen(temp),  
                    0, (const struct sockaddr *) &cliaddr3, len3); 
            sendto(sockfd, (const char *)buffer, strlen(buffer),  
                    0, (const struct sockaddr *) &cliaddr4, len4); 
        }
        else if ((n = recvfrom(sockfd, (char *)buffer, MAXLINE, 0, 
                    ( struct sockaddr *) &cliaddr4, &len4)) > 0)
        {
            buffer[n] = '\0';
            printf("User4 : %s\n", buffer); 
            sendto(sockfd, (const char *)buffer, strlen(buffer),  
                    0, (const struct sockaddr *) &cliaddr1, len1); 
            sendto(sockfd, (const char *)buffer, strlen(buffer),  
                    0, (const struct sockaddr *) &cliaddr2, len2); 
            sendto(sockfd, (const char *)buffer, strlen(buffer),  
                    0, (const struct sockaddr *) &cliaddr3, len3);
            sendto(sockfd, (const char *)temp, strlen(temp),  
                    0, (const struct sockaddr *) &cliaddr4, len4);
        }//if 
    }//while 
    return 0; 
}