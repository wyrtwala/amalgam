#ifndef TCP_H
#define TCP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

int tcp_send_ipv4(char* ip, int port, char* message, char* buffer, uint_64 buffer_size){}

  if ((int socket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    fprintf(stderr, "TCP_SEND_IPV4: Failed to open socket\n");
    return -1;
  }

  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(port);

  if (inet_aton(ip, (struct in_addr *) &(address.sin_addr.s_addr)) < 0){
    fprintf(stderr, "TCP_SEND_IPV4: Incorrect IP address\n");
    return -1;
  }
  if (connect(socket, (struct sockaddr *) &address, sizeof(address)) < 0){
    fprintf(stderr, "TCP_SEND_IPV4: Failed to connect\n");
    return -1;
  }
  if(send(socket, message, strlen(message), 0) < 0){
    fprintf(stderr, "TCP_SEND_IPV4: Failed to send\n");
    return -1;
  }
  uint64_t return_message_size = buffersize - 1;
  if (recv(socket, buffer, return_message_size, 0) < 0){
    fprintf(stderr, "TCP_SEND_IPV4: Failed to recieve\n");
  }
  if (close(socket) < 0){
    fprintf(stderr, "TCP_SEND_IPV4: Failed to close socket\n");
    return -1;
  }

  return 0;
}

int tcp_simple_server_ipv4(char* ip, int port, uint64_t listen_count, char* message, uint64_t message_size, char* client_message, uint64_t client_message_size){
  
    if ((int server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
      fprintf(stderr, "TCP_SIMPLE_SERVER_IPV4: Failed to open socket\n");
      return -1;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *) &address, sizeof(address)) < 0){
      fprintf(stderr, "TCP_SIMPLE_SERVER_IPV4: Failed to bind\n");
      return -1;
    }
    if (listen(server_socket, listen_count) < 0){
      fprintf(stderr, "TCP_SIMPLE_SERVER_IPV4: Failed listener\n");
      return -1;
    }
    if ((int client_socket = accept(server_socket, NULL, NULL)) < 0){
      fprintf(stderr, "TCP_SIMPLE_SERVER_IPV4: Failed accept\n");
      return -1;
    }
    if (recv(client_socket, client_message, sizeof(client_message), 0) < 0){
      fprintf(stderr, "TCP_SIMPLE_SERVER_IPV4: Failed to recieve\n");
      return -1;
    }
    if (sizeof(client_message) > client_message_size){
      fprintf(stderr, "TCP_SIMPLE_SERVER_IPV4: Client message too long\n");
      return -1;
    }
    if (send(client_socket, message, message_size, 0) < 0){
      fprintf(stderr, "TCP_SIMPLE_SERVER_IPV4: Failed to send message\n");
      return -1;
    }
    if(close(client_socket) < 0){
      fprintf(stderr, "TCP_SIMPLE_SERVER_IPV4: Failed to close socket\n");
      return -1;
    }

    return 0;
}

#endif
