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
        network_socket = socket(AF_INET, SOCK_STREAM, 0);               //AF_INET: socket domain, defined on the header files imported with <netinet/in.h>
                                                                        //SOCK_STREAM: type of the socket (TCP)
                                                                        //0: specifies protocol, it's 0 because already using TCP



//specify an address for the socket
        struct sockaddr_in server_address;
        server_address.sin_family = AF_INET;                            //sets the address so  it knows what type of address is being used
        server_address.sin_port = htons(9002);                          //htons() is a conversion function that converts the port integer to the appropriate data forma>

return 0;

}

