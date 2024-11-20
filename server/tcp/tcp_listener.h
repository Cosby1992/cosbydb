#ifndef TCP_LISTENER_H
#define TCP_LISTENER_H

#include <netinet/in.h> // For sockaddr_in

// Starts the TCP server on the given port
int start_server(int port);

// Accepts a client connection and returns the client socket descriptor
int accept_client(int server_fd);

// Reads data from a client socket and echoes it back
void echo_client(int client_fd);

#endif // TCP_LISTENER_H