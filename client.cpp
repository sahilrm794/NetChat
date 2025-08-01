#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    std::string username;
    std::cout << "Enter your username: ";
    std::getline(std::cin, username);
    send(sock, username.c_str(), username.length(), 0);

    std::cout << "✅ Connected as " << username << ". Type messages or /exit to quit.\n";

    while (true) {
        std::string msg;
        std::cout << "> ";
        std::getline(std::cin, msg);

        send(sock, msg.c_str(), msg.length(), 0);
        if (msg == "/exit") break;

        memset(buffer, 0, BUFFER_SIZE);
        int valread = read(sock, buffer, BUFFER_SIZE);
        if (valread <= 0) break;
        std::cout << buffer << "\n";
    }

    close(sock);
    return 0;
}
