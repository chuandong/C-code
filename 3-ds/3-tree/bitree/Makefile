CC:= gcc
CFLAGS:= -c -Wall -O2 -g
LDFLAGS:=
OBJS:= bitree.o queue.o stack.o
OUT:= bitree

.PHONY: clean

$(OUT): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)
%*.o: %*.c
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	-rm $(OBJS) $(OUT)
