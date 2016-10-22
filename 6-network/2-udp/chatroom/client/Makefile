CC:= gcc
HEADER?= -I../comm
CFLAGS:= -Wall -O2 $(HEADER) 
LDFLAGS:=					#it`s unnecessary now
LIBS:= -lpthread
OBJS:= main.o
CLIENT:= client

.PHONY: clean memcheck

$(CLIENT): $(OBJS)
	$(CC) -o $@ $^ $(LDLAGS) $(LIBS)

%*.o:%*.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	-rm $(CLIENT) $(OBJS)
memcheck:
	valgrind --tool=memcheck ./$(CLIENT)
