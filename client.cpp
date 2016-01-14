#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

#define SOCKET_ERROR        -1
#define BUFFER_SIZE         100
#define HOST_NAME_SIZE      255

void usage();
void parseFlags(int argc, char* argv[], bool &debug, int &count);
void parseOtherArgs(int argc, char* argv[], string &host, int &port, string &path);
int download(string host, int port, string path, bool debug, bool count);

int main(int argc, char* argv[]) {
	if(argc < 3 || argc > 5) {
		usage();
	} else {
		string host;
		int port;
		string path;
		bool debug;
		int count = 1;
		parseFlags(argc, argv, debug, count);
		if(debug == true) cout << "debug == true";
		else cout << "debug == false";
		cout << "count == " << count;
		parseOtherArgs(argc, argv, host, port, path);
		//download
	}
}

void usage() {
	perror("Usage: download host-name port path");
	abort();
}

void parseFlags(int argc, char* argv[], bool &debug, int &count) {
	int f;
	char* fvalue = NULL;
	int index;
	while(f = getopt(argc, argv, "c:d")) {
		switch(f) {
			case 'd':
				debug = true;
				break;
			case 'c':
				count = stoi(optarg);
				break;
			case '?':
				usage();
				break;
			default:
				usage();
		}
	}
}

void parseOtherArgs(int argc, char* argv[], string &host, int &port, string &path) {
	
}

int download(string host, int port, string path, bool debug, bool count) {
	
}

int  old(int argc, char* argv[])
{
    int hSocket;                 /* handle to socket */
    struct hostent* pHostInfo;   /* holds info about a machine */
    struct sockaddr_in Address;  /* Internet socket address stuct */
    long nHostAddress;
    char pBuffer[BUFFER_SIZE];
    unsigned nReadAmount;
    char strHostName[HOST_NAME_SIZE];
    int nHostPort;

    if(argc < 3)
      {
        printf("\nUsage: client host-name host-port\n");
        return 0;
      }
    else
      {
        strcpy(strHostName,argv[1]);
        nHostPort=atoi(argv[2]);
      }

    printf("\nMaking a socket");
    /* make a socket */
    hSocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    if(hSocket == SOCKET_ERROR)
    {
        printf("\nCould not make a socket\n");
        return 0;
    }

    /* get IP address from name */
    pHostInfo=gethostbyname(strHostName);
    /* copy address into long */
    memcpy(&nHostAddress,pHostInfo->h_addr,pHostInfo->h_length);

    /* fill address struct */
    Address.sin_addr.s_addr=nHostAddress;
    Address.sin_port=htons(nHostPort);
    Address.sin_family=AF_INET;

    printf("\nConnecting to %s (%X) on port %d",strHostName,nHostAddress,nHostPort);

    /* connect to host */
    if(connect(hSocket,(struct sockaddr*)&Address,sizeof(Address)) 
       == SOCKET_ERROR)
    {
        printf("\nCould not connect to host\n");
        return 0;
    }

    /* read from socket into buffer
    ** number returned by read() and write() is the number of bytes
    ** read or written, with -1 being that an error occured */
    nReadAmount=read(hSocket,pBuffer,BUFFER_SIZE);
    printf("\nReceived \"%s\" from server\n",pBuffer);
    /* write what we received back to the server */
    write(hSocket,pBuffer,nReadAmount);
    printf("\nWriting \"%s\" to server",pBuffer);

    printf("\nClosing socket\n");
    /* close socket */                       
    if(close(hSocket) == SOCKET_ERROR)
    {
        printf("\nCould not close socket\n");
        return 0;
    }
}
