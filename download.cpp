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

using namespace std;

#define SOCKET_ERROR        -1
#define BUFFER_SIZE         100
#define HOST_NAME_SIZE      255

char* buildRequest(char* host, char* port, char* path);
string getResponse(char* request, char* host, int port);
void parseHttp(string response, map<string, string> &headers, string body);
void printDebug(char* request, map<string, string> headers);
void spamRequests(char* request, int count);

void download(char* host, char* portStr, char* path, bool debug, bool multi, int count) {
	char* request = buildRequest(host, portStr, path);
	int portInt = stoi(portStr);
	string response = getResponse(request, host, portInt);
	map<string, string> headers;
	string body;
	parseHttp(response, headers, body);
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
	char* result = (char*)malloc(50);
	strcat(result, "GET ");
	strcat(result, path);
	strcat(result, " HTTP/1.0\n");
	strcat(result, "Host: ");
	strcat(result, host);
	return result;
}

string getResponse(char* request, char* host, int port) {
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
	char* responseBuffer;
	read(socketHandle, responseBuffer, READ_AMOUNT);
	return string(responseBuffer);
}

void parseHttp(string response, map<string, string> &headers, string body) {
	/* while getline !=0 { nothing } body = get the rest*/ 
}

void printDebug(char* request, map<string, string> headers) {
	printf(request);
}

void spamRequests(char* request, int count) { 
	
}
