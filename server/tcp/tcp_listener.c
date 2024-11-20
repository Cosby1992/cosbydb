#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "tcp_listener.h"

#define BUFFER_SIZE 128

int start_server(int port) {
    int server_fd;
    struct sockaddr_in server_addr;

    // Create a socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // Bind the socket
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Start listening
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", port);
    return server_fd;
}

int accept_client(int server_fd) {
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Accept a client connection
    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0) {
        perror("Accept failed");
        return -1;
    }

    printf("Client connected\n");
    return client_fd;
}

void echo_client(int client_fd) {
    char buffer[BUFFER_SIZE];
    int bytes_read;

    // Echo loop
    while ((bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_read] = '\0'; // Null-terminate the string
        printf("Received: %s", buffer);
        send(client_fd, buffer, bytes_read, 0); // Echo back to the client
    }

    if (bytes_read == 0) {
        printf("Client disconnected\n");
    } else {
        perror("Receive failed");
    }

    close(client_fd);
}
