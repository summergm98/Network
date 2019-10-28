#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
	int client_socket;
	struct sockaddr_in server_addr;

	client_socket = socket(PF_INET, SOCK_STREAM, 0);
	
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);

	printf("> try to connect ip: %s with port: %d\n", argv[1], atoi(argv[2]));

	if(connect(client_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1){
		printf("> connection error\n");
		exit(1);
	}
	
	printf("> connection success!\n\n");
	printf("> send 3 data to server\n");
	
	int byte_sent;
	if( (byte_sent = send(client_socket, "0123456789", strlen("0123456789"), 0)) == -1){
		printf("> sending '0123456789' failed\n");
	}
	
	if( (byte_sent = send(client_socket, "ABCDEFGHIJ", strlen("ABCDEFGHIJ"), 0)) == -1){
		printf("> sending 'ABCDEFGHIJ' failed\n");
	}

	if( (byte_sent = send(client_socket, "KLMNOPQRST", strlen("KLMNOPQRST"), 0)) == -1){
		printf("> sending 'KLMNOPQRST' failed\n");
	}
}
