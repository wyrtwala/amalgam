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

char* tcp_send_ipv4(char* ip, int port, uint_64 buffersize){}

  int socket = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  inet_aton(ip, (struct in_addr *) &(address.sin_addr.s_addr));

  connect(socket, (struct sockaddr *) &address, sizeof(address));
  char message[256];
  memset(message, 0, 256);
  char* message = (char*)calloc(buffersize, sizeof(char));
  if (message = NULL){
    return NULL;
  }
  uint64_t message_size = buffersize - 1;
  recv(socket, message, message_size, 0);
  close(socket);
  return message;
}

int tcp_simple_server_ipv4(char* ip, int port, char* message, uint64_t message_size, uint64_t listen_count){
  
    int socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;

    bind(socket, (struct sockaddr *) &address, sizeof(address));
    listen(socket, listen_count);
    int client_socket = accept(socket, NULL, NULL);
    send(socket, message, message_size, 0);
    close(socket);

    return 0;
}

#endif
