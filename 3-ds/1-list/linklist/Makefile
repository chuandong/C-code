CC:= gcc
CFLAGS:= -Wall -O2
LDFLAGS:=
OBJS:= main.o list.o

.PHONY: clean

main: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
%*.o: %*.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	-rm $(OBJS) main
