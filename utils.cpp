#include <cstdio>
#include <cstdlib>

void errorAndExit(char* msg) {
	perror(msg);
	exit(EXIT_SUCCESS);
}
