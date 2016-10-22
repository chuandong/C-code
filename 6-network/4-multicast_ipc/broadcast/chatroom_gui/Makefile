CC:= gcc
CFLAGS:= -Wall -O2
LDFLAGS:= -lncurses -lpthread
OBJS:= window.o main.o netdevice.o network.o userlist.o
OUT:= fschatroom

.PHONY: clean

$(OUT): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
%*.o: %*.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	-rm $(OBJS) $(OUT)
