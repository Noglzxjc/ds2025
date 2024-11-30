
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//thu vien de chay tren windows
#include <ws2tcpip.h>
#include <winsock2.h>
#include <windows.h>

#define SIZE 1024



int main(){
    WSADATA wsaData; 
    char *ip = "127.0.0.1";
    int port = 8000;
    int e;


    int sockfd;
    int new_sock;
    struct sockaddr_in server_addr;
    struct sockaddr_in new_addr;
    socklen_t addr_size;

    char buffer[SIZE] = {0};

    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
        printf("WSAStartup failed.\n");
        return 1;
    }

    //tạo socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == 0){
        perror("Error");
        exit(1);
    }
    printf("Socket created\n");


    //dịa chỉ server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    //gán địa chỉ cho socket
    e=bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(e<0){
        perror("Error in Binding");
        exit(1);
    }
    printf("Binding done\n");

    //Listening
    e=listen(sockfd, 10);

    if (e == 0){
    printf("Listening...\n");
    }else{
    perror("listening eRROR");
    exit(1);
    }


    addr_size = sizeof(new_addr);
    new_sock = accept(sockfd, (struct sockaddr *)&new_addr, &addr_size);

    //dong winsock
    closesocket(new_sock);
    closesocket(sockfd);
    WSACleanup();
}
//./server.exe
