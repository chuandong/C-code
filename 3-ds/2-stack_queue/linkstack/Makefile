CC:= gcc
CFLAGS:= -Wall -O2 
LDFLAGS:=					#it`s unnecessary now
OBJS:= main.o stack.o

.PHONY: clean memcheck

main.out: $(OBJS)
	$(CC) -o $@ $^ $(LDLAGS)

%*.o:%*.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	-rm *.out $(OBJS)
memcheck:
	valgrind --tool=memcheck ./main.out
