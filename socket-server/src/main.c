#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "../include/linked_list.h"
#include "../include/functions.h"
#include "../include/file_io.h"

#define PORT 8081
#define SA struct sockaddr

linked_list_t *read_list();

void print_list(linked_list_t *linked_list);

int square(int number);

int cube(int number);

int get_max(int a, int b);

int get_min(int a, int b);

int get_sum(int a, int b);

int pow_of_two(int a);

void send_list(linked_list_t *linked_list, int connfd)
{
    char element_buf[50];
    for (int i = 0; i < list_length(linked_list); i++)
    {
        sprintf(element_buf, "%d", list_get(linked_list, i));
        send(connfd, (char *) element_buf, sizeof(element_buf), 0);
        bzero(&element_buf, sizeof(element_buf));
    }
}

linked_list_t *receive_list(int connfd, int n)
{
    linked_list_t *linked_list = NULL;
    char element_buf[50];
    for (int i = 0; i < n; i++)
    {
        recv(connfd, &element_buf, sizeof(element_buf), 0);
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


void server(int connfd, int sockfd)
{
    int n;
    char buf[50];
    recv(connfd, &buf, sizeof(buf), 0);
    n = atoi(buf);
    printf("Number of accepting elements: %d\n", n);
    linked_list_t *linked_list = receive_list(connfd, n);

    printf("Accepted list:\n");
    print_list(linked_list);

    //calculate and send square values
    linked_list_t *modified_linked_list = map(square, linked_list);
    send_list(modified_linked_list, connfd);

    //calculate and send cube values
    modified_linked_list = map(cube, linked_list);
    send_list(modified_linked_list, connfd);

    //find and send min and max values
    int max = INT_MIN;
    int min = INT_MAX;
    int sum = 0;

    sprintf(buf, "%d", foldl(max, get_max, linked_list));
    send(connfd, (char *) buf, sizeof(buf), 0);
    bzero(&buf, sizeof(buf));

    sprintf(buf, "%d", foldl(min, get_min, linked_list));
    send(connfd, (char *) buf, sizeof(buf), 0);
    bzero(&buf, sizeof(buf));

    //find and send sum
    sprintf(buf, "%d", foldl(sum, get_sum, linked_list));
    send(connfd, (char *) buf, sizeof(buf), 0);
    bzero(&buf, sizeof(buf));

    //calculate and send modules
    map_mut(abs, linked_list);
    send_list(linked_list, connfd);

    //calculate and send pows of 2
    send_list(iterate(1, 10, pow_of_two), connfd);

    list_free(linked_list);
    list_free(modified_linked_list);
}

int main(int argc, char const *argv[])
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA *) &servaddr, sizeof(servaddr))) != 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    } else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    } else
        printf("Server listening..\n");
    len = sizeof(cli);

    // Accept the data packet from client and verification
    while (true)
    {
        connfd = accept(sockfd, (SA *) &cli, &len);
        if (connfd < 0)
        {
            printf("server accept failed...\n");
            exit(0);
        } else
        {
            printf("server accept the client...\n");
            server(connfd, sockfd);
//            close(connfd);
        }
    }
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

int square(int number)
{
    return number * number;
}

int cube(int number)
{
    return number * number * number;
}

int get_max(int a, int b)
{
    return a > b ? a : b;
}

int get_min(int a, int b)
{
    return a < b ? a : b;
}

int get_sum(int a, int b)
{
    return a + b;
}

int pow_of_two(int a)
{
    return 2 * a;
}
