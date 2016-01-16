all: objs exe rmobjs

objs: main.o download.o

main.o:
	g++ -c main.cpp

download.o:
	g++ -c download.cpp

exe:
	g++ *.o download

rmobjs:
	rm *.o

clean: rmobjs
	rm download
