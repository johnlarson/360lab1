CC = g++ -std=c++11 -c

all: objs exe rmobjs

objs: main download utils

debug:
	g++ -std=c++11 -g main.cpp download.cpp utils.cpp -o dbfile

main:
	$(CC) main.cpp

download:
	$(CC) download.cpp

utils:
	$(CC) utils.cpp

exe:
	g++ *.o -o download

rmobjs:
	rm *.o

clean: rmobjs
	rm download dbfile
