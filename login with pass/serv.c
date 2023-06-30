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
        int sock, connected, bytes_recieved ,key_len , true = 1;
        char send_data [1024] , recv_data[1024], pass[50];

	char confirm[] = "LOGIN SUCCESSFUL",error[]="LOGIN FAILED";
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
       while(1)
        {

            sin_size = sizeof(struct sockaddr_in);

            connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);
	     printf("\n I got a connection from (%s , %d)",
                                        inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));


	    while(1){
		    key_len = recv(connected,pass,50,0);
		    pass[key_len] = '\0';
		    if (strcmp(pass, "12345")==0){
            		send(connected,confirm, strlen(confirm),0);
			break;
		    }
		    else
			    send(connected,error,strlen(error),0);
	    }
	    

           /* while (1)
            {
		    bytes_recieved = recv(connected,recv_data,1024,0);
		    recv_data[bytes_recieved] = '\0';
		    if (strcmp(recv_data , "q") == 0 || strcmp(recv_data , "Q") == 0){
			    close(connected);
			    break;	
		    }
            	 printf("\n RECIEVED DATA = %s" , recv_data);
		       //sending data
                 send(connected, recv_data,strlen(recv_data), 0);
                fflush(stdout);
            }
        }*/
      close(connected);
     }
      close(sock);
      return 0;
}

