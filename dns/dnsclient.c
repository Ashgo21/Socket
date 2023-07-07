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

        int sock, bytes_recieved,address_len;
        char send_data[1024],recv_data[1024],address[1024],domain[50];
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
		printf("\nEnter domain : ");
		scanf("%s",domain);

	  int ref = send(sock,domain,strlen(domain),0);

	  if(ref == -1){
		  printf("\nError");
	 	  continue;
	  }
	  else{
       		bytes_recieved=recv(sock,recv_data,1024,0);
        	recv_data[bytes_recieved] = '\0';
        	printf("\nRecieved data = %s " , recv_data);
	        if(strcmp(recv_data,"URL successfully retrieved")==0)
		{
			address_len = recv(sock,address,1024,0);
			address[address_len] = '\0';
			printf("\n Address : %s\n",address);
			break;
		}
	  }
       }
	close(sock);
	return 0;
}
