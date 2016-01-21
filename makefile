CC = g++ -std=c++11 -c

all: objs exe rmobjs

objs: utils.o download.o main.o

debug:
	g++ -std=c++11 -g main.cpp download.cpp utils.cpp -o dbfile

main.o:
	$(CC) main.cpp

download.o:
	$(CC) download.cpp

utils.o:
	$(CC) utils.cpp

exe: download.o utils.o main.o
	g++ *.o -o download

rmobjs:
	rm *.o

clean: rmobjs
	rm download
	rm dbfile
