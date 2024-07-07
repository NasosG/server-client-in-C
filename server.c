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
    int welcomeSocket, clientSocket, clilen, n, port, i;
    struct sockaddr_in serveraddr, clientaddr;
    char client_message[2000] = {0};
     
    //create a socket using socket() function
    welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (welcomeSocket == -1) 
    {
        printf("(!) Error creating socket\n");
        return 0;
    }
    puts("Socket Created");

    // port <- insert the number the user entered in cmd 
    port = atoi(argv[1]);
	
    /* set server's address struct*/
    // Address family = Internet Protocol v4 addresses
    serveraddr.sin_family = AF_INET;
    /* Set the server to receive connections from  "every" interface*/
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    /* Set the port number. htons function is used for the right order of bytes*/
    serveraddr.sin_port = htons( port );
     
    //Bind
    if (bind(welcomeSocket,(struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    {
        //print error message
        puts("(!) Bind Failed");
        return 0;
    }
    puts("->Bind Done");
 
    //Listen on the socket, with 5 max connection requests queued 
    if (listen(welcomeSocket , 5) == 0)
   	printf("->Waiting for incoming connections...\n");
    else
   	printf("(!) Error\n");
    while (1)
    {  
        clilen = sizeof(struct sockaddr_in);
     
        //accept the oncoming connection from the client	
        clientSocket = accept(welcomeSocket, (struct sockaddr *)&clientaddr, (socklen_t*)&clilen);
        if (clientSocket < 0)
        {
            puts("(!) Accept Failed");
            return 0;
        }
        system("clear");
        puts("->Connection accepted");
		 
        //Receive a message from the client
        while ( (n = recv(clientSocket , client_message , 2000 , 0)) > 0 )
        {
            printf("\nData received from client: %s\n",client_message);
            //capitalize the letters
            i = 0;
            while (client_message[i])
            {
                client_message[i] = toupper(client_message[i]);
                i++;
            }
            //send it back to the client
            write(clientSocket , client_message , strlen(client_message));
            printf("Data sent to client: %s\n", client_message);
        }
		 
        if (n == 0) //successful completion
        {
            puts("\n-----Client disconnected-----");
        }
        else //failure
        {
            puts("\n-----Receive failed-----");
        }
			
        close(clientSocket);
        //katharizoume ton pinaka etsi oste na mhn meinoun skoupidia otan xanaxrhsimopoihthei
        for (i = 0; client_message[i]; i++)
            client_message[i] = '\0';

        printf("\n->Waiting for incoming connections...\n");
    }
	
    return 0;
}
