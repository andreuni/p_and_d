CC=gcc
CCOPTS=-Wall -std=gnu99 -O3
CXX=g++
CXXOPTS=-Wall -std=gnu++11 -O3

#COBJS=proc_control.o
HEADERS= header.h 
#OBJS=proc_shell.o env.o

.phony=clean all

BINS= main #reader_db #proc_shell simple
all:	$(BINS)


%.o:	%.c $(HEADERS)
	$(CC) -c $(CCOPTS) $<

%.o:	%.cpp $(HEADERS)
	$(CXX) -c $(CXXOPTS) $<

main:	main.cpp websocket.o reader_db.o
	$(CXX) -o $@ $^ $(CXXOPTS) -lpthread -lwebsockets -lmysqlclient -lssl -lcrypto -L/usr/include/mysql

#reader_db: reader_db.cpp 
#	$(CXX) -o $@ $^ $(CXXOPTS) -lmysqlclient -lssl -lcrypto -lpthread -L/usr/include/mysql

clean:
	rm -f *~ *.o $(BINS)
