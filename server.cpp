#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <map>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket, activity, valread, sd, max_sd;
    int client_socket[MAX_CLIENTS] = {0};
    std::map<int, std::string> usernames;

    struct sockaddr_in address;
    fd_set readfds;
    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    std::cout << "📡 Server listening on port " << PORT << "...\n";

    while (true) {
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        max_sd = server_fd;

        for (int i = 0; i < MAX_CLIENTS; i++) {
            sd = client_socket[i];
            if (sd > 0) FD_SET(sd, &readfds);
            if (sd > max_sd) max_sd = sd;
        }

        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        // New connection
        if (FD_ISSET(server_fd, &readfds)) {
            socklen_t addrlen = sizeof(address);
            new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
            std::cout << "✅ New connection: " << inet_ntoa(address.sin_addr) << "\n";

            // First message from client = username
            memset(buffer, 0, BUFFER_SIZE);
            read(new_socket, buffer, BUFFER_SIZE);
            usernames[new_socket] = buffer;
            std::cout << "🧑 User joined: " << buffer << "\n";

            // Add to client list
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    break;
                }
            }
        }

        // Incoming messages from clients
        for (int i = 0; i < MAX_CLIENTS; i++) {
            sd = client_socket[i];
            if (FD_ISSET(sd, &readfds)) {
                memset(buffer, 0, BUFFER_SIZE);
                valread = read(sd, buffer, BUFFER_SIZE);

                if (valread <= 0 || strcmp(buffer, "/exit") == 0) {
                    std::cout << "❌ " << usernames[sd] << " disconnected\n";
                    close(sd);
                    client_socket[i] = 0;
                    usernames.erase(sd);
                    continue;
                }

                std::string message = usernames[sd] + ": " + buffer;
                std::cout << "📨 " << message << "\n";

                // Broadcast
                for (int j = 0; j < MAX_CLIENTS; j++) {
                    if (client_socket[j] != 0 && client_socket[j] != sd) {
                        send(client_socket[j], message.c_str(), message.length(), 0);
                    }
                }
            }
        }
    }

    return 0;
}
