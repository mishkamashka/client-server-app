#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "linked-list.h"
#include "functions.h"
#include "file_io.h"

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

int main()
{
    const char *filepath = "/home/mishka/Desktop/sp/sp-lab4/sources/file";
    const char *wfilepath = "/home/mishka/Desktop/sp/sp-lab4/sources/wfile";
    const char *bfilepath = "/home/mishka/Desktop/sp/sp-lab4/sources/file.bin";

    linked_list_t *linked_list = NULL;
    if (load(&linked_list, filepath) == false)
    {
        printf("Could not load list\n");
        return 0;
    }

    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and varification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT 
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket 
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    while (1) {
//        for (int i = 0; i < list_length(linked_list); i++)
//        {
//            write(sockfd, list_get(linked_list, i), sizeof(int));
//        }

        int n = 5;
        write(sockfd, n, sizeof(int));

        int buff;
        read(sockfd, &buff, sizeof(int));
        printf("From Server : %s", buff);
        if (buff == 0) {
            printf("Client Exit...\n");
            break;
        }
    }

    // close the socket 
    close(sockfd);
} 