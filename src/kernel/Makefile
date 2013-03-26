CC	= $(CROSS_COMPILE)gcc -mcpu=$(ARCH) $(THUMB)
CFLAGS	= -g -O2
INCDIR	= ../include
OBJS	= TaskManagement.o

all: $(OBJS)

.c.o: $(OBJS)
	$(CC) $(CFLAGS) -I$(INCDIR) -c -o$@ $<

clean:
	rm -rf *.o

