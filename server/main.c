#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tcp/tcp_listener.h"

#define PORT 9054

int main() {
    int server_fd, client_fd;

    // Start the server
    server_fd = start_server(PORT);

    // Accept and handle clients
    while (1) {
        client_fd = accept_client(server_fd);
        if (client_fd >= 0) {
            echo_client(client_fd);
        }
    }

    close(server_fd);
    return 0;
}
