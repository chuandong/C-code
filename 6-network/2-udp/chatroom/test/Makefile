CC:= gcc
HEADER?= -I../comm
CFLAGS:= -Wall -O2 $(HEADER) 
LDFLAGS:=					#it`s unnecessary now
LIBS:= -lpthread

.PHONY: clean all

all: test_login test_talk


test_login: test_login.o
	$(CC) -o $@ $^ $(LDLAGS) $(LIBS)

test_talk: test_talk.o
	$(CC) -o $@ $^ $(LDLAGS) $(LIBS)

%*.o:%*.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	-rm  *.o  test_login test_talk
