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


int tcp_open_socket_ipv4(){
  if ((int socket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    fprintf(stderr, "TCP_OPEN_SOCKET_IPV4: Failed to open socket\n");
    return -1;
  }
  return socket;
}

int tcp_open_socket_ipv6(){
  if ((int socket = socket(AF_INET6, SOCK_STREAM, 0)) < 0){
    fprintf(stderr, "TCP_OPEN_SOCKET_IPV6: Failed to open socket\n");
    return -1;
  }
  return socket;
}

struct sockaddr_in tcp_create_address_ipv4(char* ip_address, int port){ 
  struct sockaddr_in address;
                     address.sin_family = AF_INET;
                     address.sin_port = htons(port);

  if (inet_pton(AF_INET, ip_address, &(address.sin_addr)) < 0){
    fprintf(stderr, "TCP_CREATE_ADDRESS_IPV4: Incorrect IP address\n");
    return -1;
  }
  return address;
}

struct sockaddr_in6 tcp_create_address_ipv6(char* ip_address, int port){ 
  struct sockaddr_in6 address;
                     address.sin6_family = AF_INET6;
                     address.sin6_port = htons(port);

  if (inet_pton(AF_INET6, ip_address, &(address.sin6_addr)) < 0){
    fprintf(stderr, "TCP_CREATE_ADDRESS_IPV6: Incorrect IP address\n");
    return -1;
  }
  return address;
}

int tcp_send_ipv4(int socket, struct sockaddr_in address, char* message){}

  if (connect(socket, (struct sockaddr *) &address, sizeof(address)) < 0){
    fprintf(stderr, "TCP_SEND_IPV4: Failed to connect\n");
    return -1;
  }
  if(send(socket, message, strlen(message), 0) < 0){
    fprintf(stderr, "TCP_SEND_IPV4: Failed to send\n");
    return -2;
  }
  return socket;
}

int tcp_send_ipv6(int socket, struct sockaddr_in6 address, char* message){}

  if (connect(socket, (struct sockaddr *) &address, sizeof(address)) < 0){
    fprintf(stderr, "TCP_SEND_IPV6: Failed to connect\n");
    return -1;
  }
  if(send(socket, message, strlen(message), 0) < 0){
    fprintf(stderr, "TCP_SEND_IPV6: Failed to send\n");
    return -2;
  }
  return socket;
}

struct sockaddr_storage tcp_receive_ipv4(int socket, struct sockaddr_in address, char* buffer, uint64_t buffer_size){

    if (bind(socket, (struct sockaddr *) &address, sizeof(address)) < 0){
      fprintf(stderr, "TCP_RECEIVE_IPV4: Failed to bind\n");
      return -1;
    }
    if (listen(socket, 1) < 0){
      fprintf(stderr, "TCP_RECEIVE_IPV4: Failed to listen\n");
      return -2;
    }
    struct sockaddr_storage client_address;
    if ((int client_socket = accept(server_socket, (struct sockaddr *) &client_address, sizeof(client_address))) < 0){
      fprintf(stderr, "TCP_RECEIVE_IPV4: Failed to accept\n");
      return -3;
    }
    if (recv(client_socket, buffer, sizeof(buffer), 0) < 0){
      fprintf(stderr, "TCP_RECEIVE_IPV4: Failed to receive\n");
      return -4;
    }
    if (sizeof(buffer) > buffer_size){
      fprintf(stderr, "TCP_RECEIVE_IPV4: Client message too long\n");
      return -5;
    }
    return client_address;
}

int tcp_receive_ipv6(int socket, struct sockaddr_in6 address, char* buffer, uint64_t buffer_size){

    if (bind(socket, (struct sockaddr *) &address, sizeof(address)) < 0){
      fprintf(stderr, "TCP_RECEIVE_IPV6: Failed to bind\n");
      return -1;
    }
    if (listen(socket, 1) < 0){
      fprintf(stderr, "TCP_RECEIVE_IPV6: Failed to listen\n");
      return -2;
    }
    struct sockaddr_storage client_address;
    if ((int client_socket = accept(server_socket, (struct sockaddr *) client_address, sizeof(client_address))) < 0){
      fprintf(stderr, "TCP_RECEIVE_IPV6: Failed to accept\n");
      return -3;
    }
    if (recv(client_socket, buffer, sizeof(buffer), 0) < 0){
      fprintf(stderr, "TCP_RECEIVE_IPV6: Failed to receive\n");
      return -4;
    }
    if (sizeof(buffer) > buffer_size){
      fprintf(stderr, "TCP_RECEIVE_IPV6: Client message too long\n");
      return -5;
    }
    return client_address;
}

#endif
