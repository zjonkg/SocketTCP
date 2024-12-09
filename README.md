# Cliente-Servidor con Sockets TCP en C++ (Windows)

Este repositorio contiene la implementación de una aplicación cliente-servidor en C++ diseñada para ejecutarse en sistemas Windows utilizando la API **Winsock**. El cliente envía un mensaje al servidor, y este responde con un mensaje predefinido.

---

## Descripción del Proyecto

### Servidor
El servidor realiza las siguientes tareas:
1. **Inicialización de Winsock**: Configura el entorno de sockets utilizando la función `WSAStartup`.
2. **Creación de un socket**: Utiliza la función `socket` para crear un socket TCP.
3. **Enlace del socket**: Asocia el socket con una dirección IP y puerto (por defecto, el **puerto 8080**).
4. **Escucha de conexiones**: El servidor espera conexiones entrantes utilizando la función `listen`.
5. **Aceptación de conexiones**: Una vez que un cliente se conecta, el servidor:
   - Recibe un mensaje del cliente y lo muestra en la consola.
   - Envía un mensaje predefinido de respuesta: **"¡Hola desde el servidor!"**.
6. **Cierre del socket**: Cierra el socket y libera recursos utilizando `closesocket` y `WSACleanup`.

### Cliente
El cliente realiza las siguientes tareas:
1. **Inicialización de Winsock**: Configura el entorno de sockets utilizando `WSAStartup`.
2. **Creación de un socket**: Utiliza la función `socket` para establecer un socket TCP.
3. **Conexión al servidor**: Conecta al servidor (por defecto, `127.0.0.1`) en el **puerto 8080**.
4. **Intercambio de mensajes**:
   - Envía un mensaje al servidor: **"Hola servidor!"**.
   - Recibe la respuesta del servidor y la muestra en la consola.
5. **Cierre del socket**: Libera recursos al finalizar.

---

## Requisitos

- **Sistema Operativo**: Windows 10 o superior.
- **Compilador**: MinGW o Visual Studio.
- **Bibliotecas**: 
  - **Winsock**: La biblioteca `Ws2_32.lib` debe enlazarse al compilar.

---

## Archivos

- **servidor.cpp**: Código del servidor.
- **cliente.cpp**: Código del cliente.

---

## Ejecución

### Compilación (Windows)

1. **Usando MinGW**:
   Compila ambos programas asegurándote de enlazar la biblioteca `Ws2_32.lib`:
   ```bash
   g++ -o servidor servidor.cpp -lws2_32
   g++ -o cliente cliente.cpp -lws2_32
