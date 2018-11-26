#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>

#include "../include/linked_list.h"
#include "../include/functions.h"
#include "../include/file_io.h"

#define MAX 80
#define PORT 8081
#define SA struct sockaddr

linked_list_t *read_list();

void print_list(linked_list_t *linked_list);

void print_list_with_newline(linked_list_t *linked_list);

void send_list(linked_list_t *linked_list, int sockfd)
{
    char element_buf[50];
    for (int i = 0; i < list_length(linked_list); i++)
    {
        printf("%d\n", list_get(linked_list, i));
        sprintf(element_buf, "%d", list_get(linked_list, i));
        send(sockfd, (char *) element_buf, sizeof(element_buf), 0);
        bzero(&element_buf, sizeof(element_buf));
    }
}

linked_list_t *receive_list(int sockfd, int n)
{
    linked_list_t *linked_list = NULL;
    char element_buf[50];
    bzero(&element_buf, sizeof(element_buf));
    for (int i = 0; i < n; i++)
    {
        recv(sockfd, &element_buf, sizeof(element_buf), 0);
        if (linked_list == NULL)
        {
            linked_list = list_create(atoi(element_buf));
        } else
        {
            list_add_back(atoi(element_buf), linked_list);
        }
        bzero(&element_buf, sizeof(element_buf));
    }
    return linked_list;
}


int main(int argc, char const *argv[])
{
//    const char *filepath = "/home/mishka/Desktop/sp/sp-lab4/sources/file";
    const char *filepath = "/home/mishka/Desktop/sp/client-server-app/sources/file";

    linked_list_t *linked_list = NULL;
    if (load(&linked_list, filepath) == false)
    {
        printf("Could not load list\n");
        return 0;
    }
    print_list(linked_list);

    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    } else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) != 0)
    {
        printf("connection with the server failed...\n");
        exit(0);
    } else
        printf("connected to the server..\n");

    char buf[50];
    sprintf(buf, "%d", list_length(linked_list));
    send(sockfd, (char *) buf, sizeof(buf), 0);

    send_list(linked_list, sockfd);

    //accept and print square values
    printf("Square values:\n");
    print_list(receive_list(sockfd, list_length(linked_list)));


    //accept and print cube values
    printf("Cube values:\n");
    print_list(receive_list(sockfd, list_length(linked_list)));

    //accept and print max and min values
    printf("Min value: ");
    recv(sockfd, &buf, sizeof(buf), 0);
    printf("%d\n", atoi(buf));
    bzero(&buf, sizeof(buf));

    printf("Max value: ");
    recv(sockfd, &buf, sizeof(buf), 0);
    printf("%d\n", atoi(buf));
    bzero(&buf, sizeof(buf));

    //accept and print sum
    printf("Sum: ");
    recv(sockfd, &buf, sizeof(buf), 0);
    printf("%d\n", atoi(buf));
    bzero(&buf, sizeof(buf));

    //accept and print modules
    printf("Modules:\n");
    print_list(receive_list(sockfd, list_length(linked_list)));

    //accept and print pows of 2
    printf("Pows of 2:\n");
    print_list(receive_list(sockfd, list_length(linked_list)));

    list_free(linked_list);
    close(sockfd);
}

linked_list_t *read_list()
{
    int input_value;
    linked_list_t *linked_list = NULL;
    printf("Enter integer numbers:\n");
    int ret;
    while ((ret = scanf("%d", &input_value)) != EOF)
    {
        if (ret == 1)
        {
            if (linked_list == NULL)
            {
                linked_list = list_create(input_value);
            } else
            {
                linked_list = list_add_front(input_value, &linked_list);
            }
        } else
        {
            printf("Discarding junk in buffer: ");
            int c;
            while ((c = getchar()) != EOF && c != '\n')
                putchar(c);
            putchar('\n');
            if (c == EOF)
                break;
        }
    }
    return linked_list;
}

void print_list(linked_list_t *linked_list)
{
    while (linked_list != NULL)
    {
        printf("%d ", linked_list->value);
        linked_list = linked_list->next;
    }
    printf("\n");
}

void print_list_with_newline(linked_list_t *linked_list)
{
    while (linked_list != NULL)
    {
        printf("%d\n", linked_list->value);
        linked_list = linked_list->next;
    }
}

