CC:= gcc
CFLAGS:= -Wall -O2 
LDFLAGS:=
LIBS:=

.PHONY: clean all

all: reader writer
	
reader: reader.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)
writer: writer.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)
%*.o: %*.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	-rm *.o reader writer

