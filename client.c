#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//thu vien de chay tren windows
#include <ws2tcpip.h>
#include <winsock2.h>
#include <windows.h>

#define SIZE 1024

//in ra lỗi winsock
void print_winsock_error() {
    int error_code = WSAGetLastError();
    printf("Winsock Error Code: %d\n", error_code);

    switch (error_code) {
        case WSAECONNREFUSED:
            printf("Error: Connection refused by the server.\n");
            break;
        case WSAETIMEDOUT:
            printf("Error: Connection timed out.\n");
            break;
        case WSAEHOSTUNREACH:
            printf("Error: Host unreachable.\n");
            break;
        case WSAEINVAL:
            printf("Error: Invalid argument.\n");
            break;
        default:
            printf("Error: Unknown error occurred.\n");
            break;
    }
}

void send_file(FILE *fp, int sockfd){
        char data[SIZE] = {0};
        while(fgets(data, SIZE, fp) != NULL){
            if(send(sockfd, data, sizeof(data), 0) == -1){
                perror("Error Sending");
                exit(1);
            }
            memset(data, 0, SIZE);
        }
    }

int main(){
    WSADATA wsaData; 
    char *ip = "127.0.0.1";
    int port = 8000;
    int e;


    int sockfd;
    struct sockaddr_in server_addr;
    FILE *fp;
    char *filename = "textfile.txt";    


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

    //kết nối tơi server
    e=connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(e==-1){
        perror("Connect failed");
        print_winsock_error();
        exit(1);
    }printf("Connected successful\n");

    //mở file
    fp=fopen(filename, "r");
    if(fp==NULL){
        perror("Error in reading file.");
        exit(1);
    }
    send_file(fp, sockfd);
    printf("File data sent successfully.\n");

    fclose(fp);
    closesocket(sockfd);
    WSACleanup();
    
}

    