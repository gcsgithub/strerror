static const char *rcsid="@(#) $Id: strerror.c,v 1.1 2010/04/14 03:37:18 mark Exp mark $";
/*
 *  strerror
 *
 *  Created by mark on 14/04/2010.
 *  Copyright 2010 Garetech Computer Solutions. All rights reserved.
 * $Log: strerror.c,v $
 * Revision 1.1  2010/04/14 03:37:18  mark
 * Initial revision
 *
 *
 */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
static const char *version(void)
{
    return(rcsid);
}

int main (int argc, const char * argv[]) {
    
    int err;
    if ( argc == 2 ) {
	sscanf(argv[1],"%d", &err);
    } else {
	fprintf(stderr, "Usage: %s <errno>\nprint error message matching errno and exit with status errno\n", argv[0]);
	err=EINVAL;
    }
    fprintf(stdout, "%s\n", strerror(err));
    exit(err);
}
