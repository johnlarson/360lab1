#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include "utils.h"
#include "cs360Utils.h"

using namespace std;

#define SOCKET_ERROR        -1
#define BUFFER_SIZE         100
#define HOST_NAME_SIZE      255

char* buildRequest(char* host, char* port, char* path);
int getResponse(char* request, char* host, int port);
void parseHttp(int socketHandle, char* headers, char* body);
void printDebug(char* request, char* headers);
void spamRequests(char* request, int count);
int getContentLength(int socketHandle);
char* getHeaders(int socketHandle);
char* getBody(int socketHandle, int length);

void download(char* host, char* portStr, char* path, bool debug, bool multi, int count) {
	char* request = buildRequest(host, portStr, path);
	int portInt = stoi(portStr);
	int socketHandle = getResponse(request, host, portInt);
	char* headers;
	char* body;
	parseHttp(socketHandle, headers, body);
	if(debug) {
		printDebug(request, headers);
	}
	if(debug || !multi) {
		cout << body << endl;
	}
	if(multi) {
		int requestsLeft = count - 1;
		spamRequests(request, requestsLeft);
	}
}

char* buildRequest(char* host, char* port, char* path) {
	char* result = (char*)malloc(1000);
	strcat(result, "GET ");
	strcat(result, path);
	strcat(result, " HTTP/1.0");
	strcat(result, "\r\nHost: ");
	strcat(result, host);
	strcat(result, "\r\nAccept: */*");
	strcat(result, "\r\nContent-Type: text/html");
	strcat(result, "\r\nContent-Length: 0");
	strcat(result, "\r\n\r\n");
	return result;
}

int getResponse(char* request, char* host, int port) {
	const int READ_AMOUNT = 2000;
	int socketHandle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(socketHandle == SOCKET_ERROR) {
		errorAndExit("Could not make socket");
	}
	struct hostent* hostInfo = gethostbyname(host);
	long hostIp;
	memcpy(&hostIp, hostInfo->h_addr, hostInfo->h_length);
	struct sockaddr_in address;
	address.sin_addr.s_addr = hostIp;
	address.sin_port = htons(port);
	address.sin_family = AF_INET;
	if(connect(socketHandle, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
		errorAndExit("Could not connect to host");
	}
	write(socketHandle, request, strlen(request));
	return socketHandle;
}

void parseHttp(int socketHandle, char* headers, char* body) {
	printf(GetLine(socketHandle));
	int contentLength = getContentLength(socketHandle);
	headers = getHeaders(socketHandle);
	body = getBody(socketHandle, contentLength);	
}

int getContentLength(int socketHandle) {
	return 1;
}

char* getHeaders(int socketHandle) {
	return "hello";
}

char* getBody(int socketHandle, int length) {
	return "yo";
}

void printDebug(char* request, char* headers) {
	printf(request);
}

void spamRequests(char* request, int count) { 
	
}
