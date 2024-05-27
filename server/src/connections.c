// /*
// ** EPITECH PROJECT, 2024
// ** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
// ** File description:
// ** connections
// */

// #include "../include/main.h"

// #define BUFFER_SIZE 1024

// int main(int argc, char *argv[]) {
//     int opt = true;
//     int master_socket, addrlen, new_socket, client_socket[MAX_CLIENTS], max_clients = MAX_CLIENTS, activity, i, valread, sd;
//     int max_sd;
//     struct sockaddr_in address;
//     char buffer[BUFFER_SIZE];

//     fd_set readfds;

//     // Initialize all client_socket[] to 0 so not checked
//     for (i = 0; i < max_clients; i++) {
//         client_socket[i] = 0;
//     }

//     // Create a master socket
//     if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
//         perror("Socket failed");
//         exit(EXIT_FAILURE);
//     }

//     // Set master socket to allow multiple connections
//     if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0) {
//         perror("setsockopt");
//         exit(EXIT_FAILURE);
//     }

//     // Type of socket created
//     address.sin_family = AF_INET;
//     address.sin_addr.s_addr = INADDR_ANY;
//     address.sin_port = htons(PORT);

//     // Bind the socket to the address
//     if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
//         perror("Bind failed");
//         exit(EXIT_FAILURE);
//     }

//     printf("Listener on port %d \n", PORT);

//     // Try to specify maximum of 3 pending connections for the master socket
//     if (listen(master_socket, 3) < 0) {
//         perror("Listen");
//         exit(EXIT_FAILURE);
//     }

//     // Accept the incoming connection
//     addrlen = sizeof(address);
//     puts("Waiting for connections ...");

//     while (true) {
//         // Clear the socket set
//         FD_ZERO(&readfds);

//         // Add master socket to set
//         FD_SET(master_socket, &readfds);
//         max_sd = master_socket;

//         // Add child sockets to set
//         for (i = 0; i < max_clients; i++) {
//             // Socket descriptor
//             sd = client_socket[i];

//             // If valid socket descriptor then add to read list
//             if (sd > 0) {
//                 FD_SET(sd, &readfds);
//             }

//             // Highest file descriptor number, need it for the select function
//             if (sd > max_sd) {
//                 max_sd = sd;
//             }
//         }

//         // Wait for an activity on one of the sockets
//         activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

//         if ((activity < 0) && (errno != EINTR)) {
//             printf("Select error");
//         }

//         // If something happened on the master socket, then it's an incoming connection
//         if (FD_ISSET(master_socket, &readfds)) {
//             if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
//                 perror("Accept");
//                 exit(EXIT_FAILURE);
//             }

//             // Inform user of socket number - used in send and receive commands
//             printf("New connection, socket fd is %d, ip is : %s, port : %d \n", new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

//             // Add new socket to array of sockets
//             for (i = 0; i < max_clients; i++) {
//                 // If position is empty
//                 if (client_socket[i] == 0) {
//                     client_socket[i] = new_socket;
//                     printf("Adding to list of sockets as %d\n", i);
//                     break;
//                 }
//             }
//         }

//         // Else it's some IO operation on some other socket
//         for (i = 0; i < max_clients; i++) {
//             sd = client_socket[i];

//             if (FD_ISSET(sd, &readfds)) {
//                 // Check if it was for closing, and also read the incoming message
//                 if ((valread = read(sd, buffer, BUFFER_SIZE)) == 0) {
//                     // Somebody disconnected, get his details and print
//                     getpeername(sd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
//                     printf("Host disconnected, ip %s, port %d \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

//                     // Close the socket and mark as 0 in list for reuse
//                     close(sd);
//                     client_socket[i] = 0;
//                 } else {
//                     // Set the string terminating NULL byte on the end of the data read
//                     buffer[valread] = '\0';
//                     send(sd, buffer, strlen(buffer), 0);
//                 }
//             }
//         }
//     }

//     return 0;
// }
