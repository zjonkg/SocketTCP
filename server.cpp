#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#define PORT 8080

int main() {
    WSADATA wsaData;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int addrlen = sizeof(client_addr);
    char buffer[1024] = { 0 };
    const char* response = "¡Hola desde el servidor!";

    // Iniciar Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error al inicializar Winsock" << std::endl;
        return 1;
    }

    // Crear el socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Error al crear el socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Configurar dirección del servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Enlazar el socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Error en bind: " << WSAGetLastError() << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    // Escuchar conexiones
    if (listen(server_socket, 3) == SOCKET_ERROR) {
        std::cerr << "Error en listen: " << WSAGetLastError() << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    std::cout << "Esperando conexiones..." << std::endl;

    // Aceptar conexiones
    if ((client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addrlen)) == INVALID_SOCKET) {
        std::cerr << "Error en accept: " << WSAGetLastError() << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    // Recibir mensaje del cliente
    int valread = recv(client_socket, buffer, 1024, 0);
    if (valread > 0) {
        std::cout << "Mensaje recibido del cliente: " << buffer << std::endl;

        // Enviar respuesta al cliente
        send(client_socket, response, strlen(response), 0);
        std::cout << "Respuesta enviada al cliente." << std::endl;
    }

    // Cerrar sockets
    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();

    return 0;
}
