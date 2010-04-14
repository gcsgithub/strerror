# @(#) $Id:$
# $Log:$
# 
-include	.depend


CC=cc

INCLUDE         = -I. -I/usr/local/include
#LDFLAGS         = 
#LDFLAGS         = -arch ppc -arch i386

#DCFLAGS = -g -pthread
DCFLAGS = -g $(INCLUDE)
#DCFLAGS = -O4 -s -falign-loops=16 -funroll-loops -pthread
#DCFLAGS = -O4 -s -falign-loops=16 -funroll-loops -pthread -DDEBUG_THREAD

#DCFLAGS = -g -s -D__NEEDSTRSEP__ -DDEBUG_ONMAC -DDEBUG

CFLAGS	= $(DCFLAGS) $(INCLUDE)
#CFLAGS	= $(DCFLAGS) -arch ppc -arch i386

#DEBUG	= 
DEBUG	= -DDEBUG -DNEEDASPRINTF

SRCS	= strerror.c
OBJS	= strerror.o


PROGS	= strerror

.SUFFIXES: .o

all:	$(PROGS)

.c.o:	
	${CC} ${CFLAGS} ${REDEFS} ${DEBUG} -c $<



$(OBJS):	Makefile

$(PROGS):	$(OBJS) Makefile $<
	$(CC) -o $@ $(LDFLAGS) $(OBJS) $(REOBJS) $(LIBS)

depend:
	mkdep $(DCFLAGS) $(SRCS)

clean:
	-rm -rf  $(OBJS) core $(PROGS) .depend
