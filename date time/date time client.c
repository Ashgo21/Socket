#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include<time.h>

int main()
{
        int sock, connected, bytes_recieved , true = 1;
        char *send_data , recv_data[1025];

        struct sockaddr_in server_addr,client_addr;
        int sin_size;

        sock = socket(AF_INET, SOCK_STREAM, 0);
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(9059);
        server_addr.sin_addr.s_addr = INADDR_ANY;
        bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
        listen(sock, 5);
        printf("\nTCPServer Waiting for client ");
        fflush(stdout);

            sin_size = sizeof(struct sockaddr_in);

            connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);

            printf("\n I got a connection from (%s , %d)",
                   inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
         time_t t;
      time(&t);
     send_data=ctime(&t);

            send(connected, send_data,strlen(send_data), 0);
                close(connected);
      close(sock);
      return 0;
}



