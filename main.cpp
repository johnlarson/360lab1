#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <string>
#include "download.h"
#include "utils.h"

using namespace std;

void usage();
void parseFlags(int argc, char* argv[], bool &debug, bool &multi, int &count);
char* getArg(int argc, char* argv[], int &i);

int main(int argc, char* argv[]) {
	if(argc < 3) {
		usage();
	} else {
		int i = 1;
		char* host = getArg(argc, argv, i);
		char* port = getArg(argc, argv, i);
		char* path = getArg(argc, argv, i); 
		bool debug = false;
		bool multi = false;
		int count = 0;
		parseFlags(argc, argv, debug, multi, count);
		download(host, port, path, debug, multi, count);
	}
}

void usage() {
	errorAndExit("Usage: download host-name port path\n");
}

void parseFlags(int argc, char* argv[], bool &debug, bool &multi, int &count) {
	int f;
	char* fvalue = NULL;
	int index;
	while((f = getopt(argc, argv, "c:d")) != -1) {
		switch(f) {
			case 'd':
				debug = true;
				break;
			case 'c':
				multi = true;
				count = stoi(optarg);
				break;
			case '?':
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
