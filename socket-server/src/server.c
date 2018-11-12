#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    char sendBuff[1025];
    time_t ticks;

    if (listenfd = socket(AF_INET, SOCK_STREAM, 0) < 0)
    {
        perror("Cannot open socket.\n");
        return 1;
    }
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    if (bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Cannot bind socket.\n");
        return 1;
    }

    if (listen(listenfd, 10) < 0)
    {
        perror("Cannot listen.\n");
        return 1;
    }

    puts("[SYSTEM_MSG]: Server has been started.\n")

    while(1) {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

        n = scanf(connfd, buffer, )
        //what to do with client

        //можно прочитать строку, пока читается, а потом преобразовать ее в массив чисел
        //ответ будет просто в виде строки

        //char *response; (all answer)
        //if (send(connfd, response, sizeof(response)/sizeof(char), 0) == -1)
        //                perror("Cannot send response.\n");

        close(connfd);
        sleep(1);
    }
}