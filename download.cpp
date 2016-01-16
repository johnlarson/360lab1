#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define SOCKET_ERROR        -1
#define BUFFER_SIZE         100
#define HOST_NAME_SIZE      255

void download(char* host, char* port, char* path, bool debug, int count) {
	cout << "DOWNLOAD" << endl;
	cout << "host: " << host << endl;
	cout << "port: " << port << endl;
	cout << "path: " << path << endl;
	cout << "debug: " << debug << endl;
	cout << "count: " << count << endl;	
}

