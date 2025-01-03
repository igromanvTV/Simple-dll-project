#include "Communication.hpp"


bool CCommunication::InitializeScriptServer(int port) {
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        Defs::rbx_print(0, "WSAStartup Failed\n");
        return 1;
    }
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        Defs::rbx_print(0, "Socket creation Failed\n");
        WSACleanup();
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        Defs::rbx_print(0, "Bind Failed\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    listen(server_socket, 3);

    return 0;
}
std::string CCommunication::ReceiveScript() {
    std::string script = "";
    int c;
    c = sizeof(struct sockaddr_in);
    while ((client_socket = accept(server_socket, (struct sockaddr*)&client, &c)) != INVALID_SOCKET) {
        char* addr = inet_ntoa(client.sin_addr);
        if (strcmp(addr, "127.0.0.2") == 0) {

            while (1) {
                char recvbuf[501];
                int recvl = recv(client_socket, recvbuf, 500, 0);
                recvbuf[recvl] = 0;

                script.append(recvbuf);

                int ch = 0;
                while (ch < 500) {
                    if (recvbuf[ch] == 0) {
                        return script;
                    }
                    ch++;
                }

            }

            closesocket(client_socket);

        }
        else {
            Defs::rbx_print(0, "WARNING: UNKNOWN CLIENT TRYING TO SEND SCRIPT!11!1111 CLIENT NOT ACCEPTED\n");
        }

    }
    return script;
}