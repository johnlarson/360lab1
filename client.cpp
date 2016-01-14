#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

#define SOCKET_ERROR        -1
#define BUFFER_SIZE         100
#define HOST_NAME_SIZE      255

void usage();
void parseFlags(int argc, char* argv[], bool &debug, int &count);
string getArg(int argc, char* argv[], int &i);
void download(string host, int port, string path, bool debug, bool count);

int main(int argc, char* argv[]) {
	if(argc < 3) {
		perror("Wrong number of args\n");
		usage();
	} else {
		bool debug;
		int count = 1;
		parseFlags(argc, argv, debug, count);
		if(debug == true) cout << "debug == true" << endl;
		else cout << "debug == false" << endl;
		cout << "count == " << count << endl;
		int i = 1;
		string host = getArg(argc, argv, i);
		cout << "host: " << host << endl;
		string portStr = getArg(argc, argv, i);
		cout << "portStr: " << portStr << endl;
		int port = stoi(portStr);
		cout << "port: " << port << endl;
		string path = getArg(argc, argv, i); 
		cout << "path: " << path << endl;
		download(host, port, path, debug, count);
	}
}

void usage() {
	perror("Usage: download host-name port path\n");
	exit(EXIT_SUCCESS);
}

void parseFlags(int argc, char* argv[], bool &debug, int &count) {
	int f;
	char* fvalue = NULL;
	int index;
	while((f = getopt(argc, argv, "c:d")) != -1) {
		switch(f) {
			case 'd':
				debug = true;
				break;
			case 'c':
				count = stoi(optarg);
				break;
			case '?':
				//usage();
				break;
		}
	}
}

string getArg(int argc, char* argv[], int &i) {
	while(i < argc) {
		if(argv[i][0] != '-') {
			string result =  string(argv[i]);
			i++;
			return result;
		} 
		i++;
	}
}

void download(string host, int port, string path, bool debug, bool count) {
	cout << "DOWNLOAD" << endl;
	cout << "host: " << host << endl;
	cout << "port: " << port << endl;
	cout << "path: " << path << endl;
	cout << "debug: " << debug << endl;
	cout << "count: " << count << endl;	
}

