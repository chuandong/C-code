CC:= gcc
HEADER:= -I../comm
CFLAGS:= -Wall -O2 $(HEADER) 
LDFLAGS:=					#it`s unnecessary now
LIBS:= -lpthread
OBJS:= main.o queue.o list.o
SERVER?= server

.PHONY: clean memcheck

$(SERVER): $(OBJS)
	$(CC) -o $@ $^ $(LDLAGS) $(LIBS)

%*.o:%*.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	-rm $(SERVER) $(OBJS)
memcheck:
	valgrind --tool=memcheck ./$(SERVER)
