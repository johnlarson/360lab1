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
string getArg(int argc, char* argv[], int &i);

int main(int argc, char* argv[]) {
	if(argc < 3) {
		perror("Wrong number of args\n");
		usage();
	} else {
		int i = 1;
		string host = getArg(argc, argv, i);
		cout << "host: " << host << endl;
		string port = getArg(argc, argv, i);
		cout << "port: " << port << endl;
		string path = getArg(argc, argv, i); 
		cout << "path: " << path << endl;
		bool debug;
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
