#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


int main()
{
        int sock, connected, bytes_recieved, domain_len, address_len , true = 1;
        char send_data [1024] , recv_data[1024], domain[50], address[25];
       	char domains[][50] = {"www.google.com","https://youtube.com","python.com"};
        char addresses[][25] = {"10.1.1.121","1.1.1.1","0.0.0.0"};

	char confirm[] = "URL successfully retrieved", error[]="url cannot be retrieved";
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
	     printf("\n I got a connection from (%s,%d)\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));


	    while(1){
		    domain_len = recv(connected, domain,50,0);
		    domain[domain_len] = '\0';
		    
		    int count = -1, i = 0;
		    while(i<3){
			    if(strcmp(domain,domains[i])==0){
				    count = i;
				    break;
			    }else
				    i++;
		    }
		    if(count == -1)
			    send(connected,error,strlen(error),0);
		    else{
			    send(connected,confirm,strlen(confirm),0);
			    send(connected,addresses[i],strlen(addresses[i]),0);
			    break;
		    }
	    }
	    
      close(connected);
      close(sock);
      return 0;
}

