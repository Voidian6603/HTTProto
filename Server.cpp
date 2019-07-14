#include <stdio.h> // standard input and output library
#include <stdlib.h> // this includes functions regarding memory allocation
#include <string.h> // contains string functions
#include <unistd.h> //contains various constants
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses
#include <time.h>
 
#define PORT 6603

int main(){
	int server_fd, new_socket; long valread;
	struct sockaddr_in address;
	int addrlen = sizeof(address);

	char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";

	// Creating socket descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
		perror("In socket");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	memset(address.sin_zero, '\0', sizeof address.sin_zero);

	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) <0){
		perror ("In bind");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 10) <0){
		perror("In listen");
		exit(EXIT_FAILURE);
	}


	while (1){
		printf("\n------ Waiting for new connection ------\n\n");
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) <0){
			perror("In accept");
			exit(EXIT_FAILURE);
		}
		sleep(5);
		char buffer[30000] = {0};
		valread = read(new_socket, buffer, 30000);
		printf("%s\n",buffer);
		write(new_socket, hello, strlen(hello));
		printf("------Hello message sent------\n");
		close(new_socket);
	}
    return 0;
}