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

void usage();
void parseFlags(int argc, char* argv[], bool &debug, int &count);
char* getArg(int argc, char* argv[], int &i);

int main(int argc, char* argv[]) {
	if(argc < 3) {
		perror("Wrong number of args\n");
		usage();
	} else {
		int i = 1;
		char* host = getArg(argc, argv, i);
		cout << "host: " << host << endl;
		char* port = getArg(argc, argv, i);
		cout << "port: " << port << endl;
		char* path = getArg(argc, argv, i); 
		cout << "path: " << path << endl;
		bool debug = false;
		int count = 1;
		parseFlags(argc, argv, debug, count);
		if(debug == true) cout << "debug == true" << endl;
		else cout << "debug == false" << endl;
		cout << "count == " << count << endl;
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

char* getArg(int argc, char* argv[], int &i) {
	while(i < argc) {
		if(argv[i][0] != '-') {
			char* result =  argv[i];
			i++;
			return result;
		} 
		i++;
	}
}
