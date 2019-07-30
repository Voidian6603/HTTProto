// Core Includes
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>

// Socket Includes
#include <sys/socket.h>
#include <netinet/in.h>

// Other
#include <time.h>
#include <unistd.h>
using namespace std;

 // Defines
#define PORT 6603

vector<string> reqParse (string);

int main(){
	// Socket Creation
	int server_fd, new_socket; long valread;
	struct sockaddr_in address;
	int addrlen = sizeof(address);

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

	string request = "GET / HTTP/1.1\nHost: localhost\n\n";

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
		write(new_socket, request, strlen(request));
		cout << "------Hello message sent------\n" << endl;
		close(new_socket);
	}
	return 0;
}

vector<string> reqParse (string s){
	string delimiter = "\n";
	size_t pos = 0;
    string token;
	vector<string> segments;

	while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        segments.push_back(token);
        s.erase(0, pos + delimiter.length());
    }

	for (int c = 0; c < segments.size(); c++){
		cout << segments[c] << endl;
	}
	return segments;
}