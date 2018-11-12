CC = gcc
RM = rm
CFLAGS = -c -Wall -I../inc

all: chatroom sender receiver

chatroom: chatroom.o list.o
	$(CC) $^ -lpthread -o ../bin/$@

chatroom.o: chatroom.c
	$(CC) $(CFLAGS) $^

list.o: list.c
	$(CC) $(CFLAGS) $^

sender: sender.o
	$(CC) $^ -o ../bin/$@

sender.o: sender.c
	$(CC) $(CFLAGS) $^

receiver: receiver.o
	$(CC) $^ -o ../bin/$@

receiver.o: receiver.c
	$(CC) $(CFLAGS) $^

clean:
	$(RM) *.o \
	../bin/chatroom \
	../bin/sender \
	../bin/receiver
