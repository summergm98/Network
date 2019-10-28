#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
	int server_socket, client_socket;
	struct sockaddr_in server_addr, client_addr;
	int client_addr_size = sizeof(client_addr);

	if((server_socket = socket(PF_INET, SOCK_STREAM, 0)) == -1){
		printf("> creating socket failed\n");
		exit(1);
	}

	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(atoi(argv[1]));
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1){
		printf("> bind error\n");
		exit(1);
	}
	
	printf("> server on...\n");
	
	if(listen(server_socket, 5) < 0){
		printf("> listen failed\n");
		exit(1);
	}
	
	client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &client_addr_size);
	
	char *data;
	data = (char *) malloc(sizeof(char) * atoi(argv[2]));
	
	while(1){
		printf("> listening to client...\n");
		recv(client_socket, data, strlen(data), 0);
	}	
}
