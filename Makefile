# @(#) $Id: Makefile,v 1.1 2010/04/14 03:37:24 mark Exp $
# $Log: Makefile,v $
# Revision 1.1  2010/04/14 03:37:24  mark
# Initial revision
#
# 
-include	.depend

INCLUDE         = -I. -I/usr/local/include

DCFLAGS = -g $(INCLUDE)

CFLAGS	= $(DCFLAGS) $(INCLUDE)
CFLAGS	= $(DCFLAGS)
LDFLAGS         = 

SRCS	= strerror.c
OBJS	= strerror.o
PROGS	= strerror

all:	$(PROGS)

#DEBUG	= -DDEBUG 
DEBUG	= 




.SUFFIXES: .o


.c.o:	
	${CC} ${CFLAGS} ${REDEFS} ${DEBUG} -c $<

$(OBJS):	Makefile

$(PROGS):	$(OBJS) Makefile $<
	$(CC) -o $@ $(LDFLAGS) $(OBJS) $(REOBJS) $(LIBS)

depend:
	mkdep $(DCFLAGS) $(SRCS)

clean:
	-rm -rf  $(OBJS) core $(PROGS) .depend
