#include <stdio.h>	
#include <stdlib.h>
#include <ctype.h>
#include <string.h>	
#include <sys/socket.h>	
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>	
#include <unistd.h>

int main(int argc , char *argv[])
{
	int clientSocket, port;
	struct sockaddr_in serveraddr;
	char message[1000]={0} , answer[2000]={0}, *str;
	
	// Create the socket using socket() function
	clientSocket = socket(AF_INET , SOCK_STREAM , 0);
	if (clientSocket == -1)
	{
		printf("(!) Error creating socket\n");
		return 0;
	}
	puts("Socket Created");

	// port <- insert the number the user entered in cmd 
	port = atoi(argv[2]);

	/* Thetoume thn IP address sto localhost */
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	/* Address family = Internet Protocol v4 addresses */
	serveraddr.sin_family = AF_INET;
	/* Bazoume to port number. Xrhsimopoioume thn fuction htons gia th sosth seira ton bytes kai port to port pou anaferthike parapano*/
	serveraddr.sin_port = htons( port );

    //Sundesh tou socket me ton server xrhsimopoiontas to address struct kai thn sunarthsh connect()
	if (connect(clientSocket , (struct sockaddr *)&serveraddr , sizeof(serveraddr)) < 0)
	{
		puts("(!) Error Failed To Connect");
		return 0;
	}
	
	puts("->Connected\n");


		str = argv[3];
		strcpy(message, (char*)str);

		// Send the data user typed in cmd
		// Stelnoume ta dedomena pou plhktrologithikan sth katallhlh thesh ths grammhs entolwn
		if( send(clientSocket , message , strlen(message) , 0) < 0)
		{
			puts("(!) Error Send Failed");
			return 0;
		}
		else
			  printf("Data sent to server: %s\n", message);

		//Receive server's answer
		if( recv(clientSocket , answer , 2000 , 0) < 0)
		{
			puts("(!) Error Receive Failed");
			return 0;
		}
		
		//Print the received message
    	printf("Data received from server: %s\n", answer);   
		printf("\n-----Communication completed-----\n");


	close(clientSocket);//close the socket using socket() function

	return 0;
}
