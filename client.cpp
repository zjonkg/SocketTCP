#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#define PORT 8080

int main() {
    WSADATA wsaData;
    SOCKET client_socket;
    struct sockaddr_in server_addr;
    const char* message = "Hola servidor!";
    char buffer[1024] = { 0 };


    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error al inicializar Winsock" << std::endl;
        return 1;
    }

   
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Error al crear el socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

 
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);


    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        std::cerr << "Direccion no válida o no soportada" << std::endl;
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Conexion fallida: " << WSAGetLastError() << std::endl;
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    std::cout << "Conexion establecida con el servidor." << std::endl;

  
    send(client_socket, message, strlen(message), 0);
    std::cout << "Enviando mensaje: " << message << std::endl;

   
    int valread = recv(client_socket, buffer, 1024, 0);
    if (valread > 0) {
        std::cout << "Respuesta del servidor: " << buffer << std::endl;
    }

    
    closesocket(client_socket);
    WSACleanup();

    return 0;
}
