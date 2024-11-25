#include <winsock2.h>
#include <ws2tcpip.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define PORT 8080

WSADATA wsaData;
if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    printf("WSAStartup failed.\n");
    return 1;
}


int main(int a,char const* a[]){
    int status;
    int read;
    int client;
    struct socketaddress address;
    char buffer[1024] = {0};
    if((client = socket(AF_INET, SOCK_STREAM, 0))<0){
        perror("Faild");
        return -1;
    }

    address.family = AF_INET;
    address.port = htons(PORT);

    //IPv4 and IPv6 adđ to binary//

    if(inet(AF_INET, 127.0.0.1 ", &address.sin_addr)<=0){
        printf("Address is invalid);
        return -1;
    }

    if(status = connect(client, (struct sockaddr *)&address, sizeof(address))<0){
        printf("Faild");
        return -1;
    }

    send(client, a[1], strlen(a[1]), 0);
    printf("Welcome\n");
    read = read(client=, buffer, 1024-1);

    close(client);
    return 0;
    WSACleanup();


}