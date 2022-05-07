// Client side C/C++ program to demonstrate Socket
// programming
#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
using namespace std;
class Client {
    public:
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char* hello = "Hello from client";
    char buffer[1024] = { 0 };
    Client(){
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		    printf("\n Socket creation error \n");
	    }

	    serv_addr.sin_family = AF_INET;
	    serv_addr.sin_port = htons(PORT);

        // Convert IPv4 and IPv6 addresses from text to binary
        // form
	    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<= 0) {
		    printf("\nInvalid address/ Address not supported \n");
	    }

	    if (connect(sock, (struct sockaddr*)&serv_addr,sizeof(serv_addr))< 0) {
		    printf("\nConnection Failed \n");
	    }
    }
    string message(string msg){
        for(int i=0;i<1024;i++){
           buffer[i]=0;
        }
        const char* hello=msg.c_str();
        send(sock, hello, strlen(hello), 0);
        valread = read(sock, buffer, 1024);
        string mesg(buffer);
        return mesg;
    }


};

#endif

