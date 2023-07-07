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
        int sock, connected, bytes_recieved, user_len, pass_len , true = 1;
        char send_data [1024] , recv_data[1024], user[50], pass[25];
       	char users[][25] = {"Ash","Manoj","Aish"};
        char passwords[][25] = {"12345","yoyo","qwerty123"};

	char confirm[] = "LOGIN SUCCESSFUL", error[]="User does'nt exist", wrong[]="Wrong password";
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

	printf("TESTING");
            sin_size = sizeof(struct sockaddr_in);

            connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);
	     printf("\n I got a connection from (%s,%d)\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));


	    while(1){
		    user_len = recv(connected, user,50,0);
		    user[user_len] = '\0';
		    pass_len = recv(connected,pass,50,0);
		    pass[pass_len] = '\0';
		    
		    int count = -1, i = 0;
		    while(i<3){
			    if(strcmp(user,users[i])==0){
				    count = i;
				    break;
			    }else
				    i++;
		    }
		    if(count == -1)
			    send(connected,error,strlen(error),0);
		    else if(strcmp(passwords[i], pass)==0){
			    send(connected,confirm,strlen(confirm),0);
			    break;
		    }else{
			    send(connected,wrong,strlen(wrong),0);
		    }
	    }
	    
      close(connected);
      close(sock);
      return 0;
}

