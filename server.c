
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//thu vien de chay tren windows
#include <ws2tcpip.h>
#include <winsock2.h>
#include <windows.h>

#define SIZE 1024

void write_file(int sockfd){
    int n;
    FILE *fp;
    char *filename = "textfile2.txt";
    char buffer[SIZE];

    fp = fopen(filename, "w");
    if(fp == NULL){
        perror("Error in creating file");
        exit(1);
    }
    while(1){
        n = recv(sockfd, buffer, SIZE, 0);
        if (n <= 0) {
            if (n == 0)
                printf("Client disconnected.\n");
            else
                perror("Error receiving data");
            break;
        }
        printf("Received data: %s\n", buffer); 
        fprintf(fp, "%s", buffer);
        bzero(buffer, SIZE);
    }
    fclose(fp);
}

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


    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
        printf("WSAStartup failed.\n");
        return 1;
    }

    //tạo socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1){
        perror("Error");
        exit(1);
    }
    printf("Socket created\n");

    //dịa chỉ server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    //bind socket
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
        perror("Bind failed");
        exit(1);
    }
    printf("Bind done\n");

    

    //Listening
    e=listen(sockfd, 10);

    if (e == 0){
    printf("Listening...\n");
    }else{
    perror("listening eRROR");
    exit(1);
    }

    //Accept
    addr_size = sizeof(new_addr);
    new_sock = accept(sockfd, (struct sockaddr *)&new_addr, &addr_size);
    if(new_sock==-1){
        perror("Accept failed");
        exit(1);
    }printf("Connection accept\n");


    write_file(new_sock);
    printf("Data written in the file successfully\n");

    //dong winsock
    closesocket(new_sock);
    closesocket(sockfd);
    WSACleanup();
}
//./server.exe
