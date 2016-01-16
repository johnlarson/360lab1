#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define SOCKET_ERROR        -1
#define BUFFER_SIZE         100
#define HOST_NAME_SIZE      255

void download(char* host, char* port, char* path, bool debug, bool multi, int count) {
	char* request = makeRequest(host, port, path);
	string response = getResponse(request);
	//make a stringstream
	map<string, string> headers;
	string body;
	parseHttp(/*stringstream*/, headers, body);
	if(debug) {
		printDebug(request, headers);
	}
	if(debug || !multi) {
		cout << body << endl;
	}
	if(multi) {
		spamRequests(count);
	}
}
