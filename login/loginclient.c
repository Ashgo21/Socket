#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


int main()

{
	printf("ryyd");

        int sock, bytes_recieved;
        char send_data[1024],recv_data[1024],user[50],pass[50];
        struct sockaddr_in server_addr;
       sock = socket(AF_INET, SOCK_STREAM, 0);
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(9059);
        server_addr.sin_addr.s_addr =htonl(INADDR_ANY);       
        //bzero(&(server_addr.sin_zero),8);
        connect(sock, (struct sockaddr *)&server_addr,
                    sizeof(struct sockaddr));
        //send(sock,0,sizeof(int), 0);
	printf("Done:");
	while(1)
        {
		printf("\nEnter username : ");
		scanf("%s",user);


	  printf("\nEnter password : ");
	  scanf("%s",pass);

	  int ref = send(sock,user,strlen(user),0);
          send(sock,pass,strlen(pass), 0);

	  if(ref == -1){
		  printf("\nError");
	 	  continue;
	  }
	  else{
       		bytes_recieved=recv(sock,recv_data,1024,0);
        	recv_data[bytes_recieved] = '\0';
        	printf("\nRecieved data = %s " , recv_data);
	        if(strcmp(recv_data,"LOGIN SUCCESSFUL")==0)
			break;
	  }
        }
/*	while(1)
        {

          	printf("\nSEND (q or Q to quit) : ");
          	scanf("%s",send_data);

          	if (strcmp(send_data , "q") != 0 && strcmp(send_data , "Q") != 0)
           		send(sock,send_data,strlen(send_data), 0);

          	else{
           		send(sock,send_data,strlen(send_data), 0);
           		close(sock);
           		break;
          	}
        	bytes_recieved=recv(sock,recv_data,1024,0);
        	recv_data[bytes_recieved] = '\0';
        	printf("\nRecieved data = %s " , recv_data);

        }*/
	close(sock);
	return 0;
}
