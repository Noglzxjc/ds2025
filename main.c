#include <winsock2.h>
#include <ws2tcpip.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#define PORT 8080

WSADATA wsaData;


int main(){
    int server, int new_socket
    struct sockaddr_in address;
    int otp = 1;
    soclen_t addrlen = sizeof(address);
    char buffer[1024] = {0};

/* tạo file socket description*/
    if ((server = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if ((setsockopt(server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) < 0){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    adddress.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    printf("WSAStartup failed.\n");
    return 1;
}


    if(bind(server, (struct sockaddr *)&address, sizeof(address))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if(listen(server, 3) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if((new_socket = accept(server, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read(new_socket, buffer, 1024-1);
    // subtract 1 for the null
    // terminator at the end
    printf("%s\n", buffer);
    send(new_socket, hello, strlen(hello), 0);  
    printf("Hello message sent\n");
    return 0;


    WSACleanup();
    //close connection socket
    close(new_socket);
    //close server
    close(server);
    
        
}

