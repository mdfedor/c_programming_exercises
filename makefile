OBJS=ch5.o
CC=gcc
CFLAGS+=-c -Wall -g

hello:$(OBJS)
	$(CC) $^ -o $@ -lm
%.o:%.c
	$(CC) $^ $(CFLAGS) -o $@
clean:
	$(RM) *.o hello -r
