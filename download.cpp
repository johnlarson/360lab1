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

#define SOCKET_ERROR	-1
#define MAX_HTTP_SIZE	8192

char* buildRequest(char* host, char* port, char* path);
void setPrintables(char* &headers, char* &body, char* request, char* host, int port);
int getResponse(char* request, char* host, int port);
void parseHttp(int socketHandle, char* &headers, char* &body);
void printDebug(char* request, char* headers);
void spamRequests(char* request, char* host, int port, int count);
void getHeaders(int socketHandle, char* &headers, int &contentLength);

void download(char* host, char* portStr, char* path, bool debug, bool multi, int count) {
	char* request = buildRequest(host, portStr, path);
	int portInt = stoi(portStr);
	char* headers;
	char* body;
	setPrintables(headers, body, request, host, portInt);
	printf("\n");
	if(debug) {
		printDebug(request, headers);
	}
	if(debug || !multi) {
		printf(body);
	}
	if(multi) {
		int requestsLeft = count - 1;
		spamRequests(request, host, portInt, requestsLeft);
	}
}

char* buildRequest(char* host, char* port, char* path) {
	char* result = (char*)malloc(MAX_HTTP_SIZE);
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

void setPrintables(char* &headers, char* &body, char* request, char* host, int port) {	
	int socketHandle = getResponse(request, host, port);
	parseHttp(socketHandle, headers, body);
	if(close(socketHandle) == SOCKET_ERROR) {
		errorAndExit("Could not close socket");
	}
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

void parseHttp(int socketHandle, char* &headers, char* &body) {
	int contentLength;
	getHeaders(socketHandle, headers, contentLength);
	body = (char*)malloc(contentLength);
	read(socketHandle, body, contentLength);	
}

void getHeaders(int socketHandle, char* &headers, int &contentLength) {
	headers = (char*)malloc(MAX_HTTP_SIZE);
	char* line = GetLine(socketHandle);
	while(strlen(line) != 0) {
		char* originalLine = (char*)malloc(strlen(line));
		strcpy(originalLine, line);
		char* key = strtok(line, ":");
		if(strstr(key, "Content-Length")) {
			char* value = strtok(NULL, ":");
			contentLength = stoi(value);
		}
		strcat(headers, originalLine);
		strcat(headers, "\n");
		line = GetLine(socketHandle);
	}
	strcat(headers, "\n");
}

void printDebug(char* request, char* headers) {
	printf(request);
	printf(headers);
}

void spamRequests(char* request, char* host, int port, int count) { 
	int responses = 0;
	for(int i = count; i > 0; i--) {
		char* headers;
		char* body;
		setPrintables(headers, body, request, host, port);
	}
	printf("Got %i responses", responses);
}
