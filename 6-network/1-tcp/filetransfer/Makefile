CC:= gcc
CFLAGS:= -Wall -O2 
LDFLAGS:=
LIBS:=

.PHONY: clean all

all: server client
	
server: server.o md5.o md5core.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)
client: client.o md5.o md5core.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)
%*.o: %*.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	-rm *.o server client

