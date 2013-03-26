CC	= ${CROSS_COMPILE}gcc -mcpu=${ARCH} ${THUMB}
CFLAGS	= -g -O2
INCDIR	= ../../include
OBJS	= dispatch.o

all: $(OBJS)
	
.c.o:
	$(CC) $(CFLAGS) -I$(INCDIR) -c -o$@ $<

clean:
	rm -rf *.o


