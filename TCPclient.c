#include <stdio.h>
#include <stdlib.h>

//definitions about the socket functions
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
        //create a socket
        int network_socket;
        network_socket = socket(AF_INET, SOCK_STREAM, 0);               							//AF_INET: socket domain, defined on the header files imported with <netinet/in.h>
                                                                       								//SOCK_STREAM: type of the socket (TCP)
                                                                       								//0: specifies protocol, it's 0 because already using TCP

	//specify an address for the socket
        struct sockaddr_in server_address;
        server_address.sin_family = AF_INET;                    							        //sets the address so  it knows what type of address is being used
        server_address.sin_port = htons(9002);                  							        //htons() is a conversion function that converts the port integer to the appropriate data forma>
	server_address.sin_addr.s_addr = INADDR_ANY;										//defines the address to connect

	int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));		//first parameter takes the actual socket
																//second parameter: server address in a different structure (no idea what's going on here)
	//check for error with the connection
	if(connection_status == -1)
	{
		printf("There was an error making a connection to the remote socket. \n");
	}

	//receive data from the server
	char server_response[256];												//holds the information received
	recv(network_socket, &server_response, sizeof(server_response), 0); 

	//print out the server's response
	printf("The server sent the data: %s\n", server_response);

	//close the socket
	close(network_socket);
	return 0;

}

