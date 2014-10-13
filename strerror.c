static const char *rcsid="@(#) $Id: strerror.c,v 1.3 2013/02/17 20:00:01 mark Exp $";
/*
 *  strerror
 *
 *  Created by mark on 14/04/2010.
 *  Copyright 2010 Garetech Computer Solutions. All rights reserved.
 * $Log: strerror.c,v $
 * Revision 1.3  2013/02/17 20:00:01  mark
 * MG20130218- add curl error lookups
 *
 * Revision 1.2  2010/09/08 08:01:23  mark
 * output error string to stdout stderr is a bit usless in this context
 *
 * Revision 1.1  2010/04/14 03:37:18  mark
 * Initial revision
 *
 *
 */
#include <stdio.h>
#include <errno.h>
#include <sysexits.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <stdarg.h>
#include <unistd.h>

static const char *version(void)
{
    return(rcsid);
}

void dousage(char *prognam);

void dousage(char *prognam)
{
    fprintf(stderr, "Usage: %s [-c|-s|-g|-<errno>] <errno>\nprint error message matching errno and exit with status errno\n", prognam);
    fprintf(stderr, "-c use curl error lookups\n");
    fprintf(stderr, "-s use sysexits\n");
    fprintf(stderr, "-g use gia_strerror\n");
    fprintf(stderr, "-<errno> report using standard system errors even when -c,-s,-g enabled\n");
    
    exit(EINVAL);
}

typedef struct {
    int         err;
    const char  *errmsg;
} SYSERR_LST_t;

const SYSERR_LST_t SYSERR_LST[] = {
    { EX_OK          , "successful termination"			},
    { EX__BASE       , "base value for error messages"		},
    { EX_USAGE       , "command line usage error"			},
    { EX_DATAERR     , "data format error"				},
    { EX_NOINPUT     , "cannot open input"				},
    { EX_NOUSER      , "addressee unknown"				},
    { EX_NOHOST      , "host name unknown"				},
    { EX_UNAVAILABLE , "service unavailable"			},
    { EX_SOFTWARE    , "internal software error"			},
    { EX_OSERR       , "system error (e.g., can't fork)"		},
    { EX_OSFILE      , "critical OS file missing"			},
    { EX_CANTCREAT   , "can't create (user) output file"		},
    { EX_IOERR       , "input/output error"				},
    { EX_TEMPFAIL    , "temp failure; user is invited to retry"	},
    { EX_PROTOCOL    , "remote error in protocol"			},
    { EX_NOPERM      , "permission denied"				},
    { -1             , NULL						}
};

const SYSERR_LST_t *lookup_syserr(const SYSERR_LST_t *errlist, int err);

const SYSERR_LST_t CURLERR_LST[] = {
    { 1, "Unsupported protocol. This build of curl has no support for this protocol." },
    { 2, "Failed to initialize." },
    { 3, "URL malformed. The syntax was not correct." },
    { 4, "A feature or option that was needed to perform the desired request was not enabled or was  explicitly  disabled at build-time. To make curl able to do this, you probably need another build of libcurl!" },
    { 5, "Couldn't resolve proxy. The given proxy host could not be resolved." },
    { 6, "Couldn't resolve host. The given remote host was not resolved." },
    { 7, "Failed to connect to host." },
    { 8, "FTP weird server reply. The server sent data curl couldn't parse." },
    { 9, "FTP  access  denied.  The  server denied login or denied access to the particular resource or directory you wanted to reach. Most often you tried to change to a directory that doesn't exist on the server." },
    { 11 ,"FTP weird PASS reply. Curl couldn't parse the reply sent to the PASS request." },
    { 13 ,"FTP weird PASV reply, Curl couldn't parse the reply sent to the PASV request." },
    { 14 ,"FTP weird 227 format. Curl couldn't parse the 227-line the server sent." },
    { 15 ,"FTP can't get host. Couldn't resolve the host IP we got in the 227-line." },
    { 17 ,"FTP couldn't set binary. Couldn't change transfer method to binary." },
    { 18 ,"Partial file. Only a part of the file was transferred." },
    { 19 ,"FTP couldn't download/access the given file, the RETR (or similar) command failed." },
    { 21 ,"FTP quote error. A quote command returned error from the server." },
    { 22 ,"HTTP page not retrieved. The requested url was not found or returned another error with the HTTP error code being 400 or above. This return code only appears if -f, --fail is used." },
    { 23 ,"Write error. Curl couldn't write data to a local filesystem or similar." },
    { 25 ,"FTP couldn't STOR file. The server denied the STOR operation, used for FTP uploading." },
    { 26 ,"Read error. Various reading problems." },
    { 27 ,"Out of memory. A memory allocation request failed." },
    { 28 ,"Operation timeout. The specified time-out period was reached according to the conditions." },
    { 30 ,"FTP  PORT failed. The PORT command failed. Not all FTP servers support the PORT command, try doing a transfer using PASV instead!" },
    { 31 ,"FTP couldn't use REST. The REST command failed. This command is used for resumed FTP transfers." },
    { 33 ,"HTTP range error. The range \"command\" didn't work." },
    { 34 ,"HTTP post error. Internal post-request generation error." },
    { 35 ,"SSL connect error. The SSL handshaking failed." },
    { 36 ,"FTP bad download resume. Couldn't continue an earlier aborted download." },
    { 37 ,"FILE couldn't read file. Failed to open the file. Permissions?" },
    { 38 ,"LDAP cannot bind. LDAP bind operation failed." },
    { 39 ,"LDAP search failed." },
    { 41 ,"Function not found. A required LDAP function was not found." },
    { 42 ,"Aborted by callback. An application told curl to abort the operation." },
    { 43 ,"Internal error. A function was called with a bad parameter." },
    { 45 ,"Interface error. A specified outgoing interface could not be used." },
    { 47 ,"Too many redirects. When following redirects, curl hit the maximum amount." },
    { 48 ,"Unknown option specified to libcurl. This indicates that you passed a weird option to curl that was  passed on to libcurl and rejected. Read up in the manual!" },
    { 49 ,"Malformed telnet option." },
    { 51 ,"The peer's SSL certificate or SSH MD5 fingerprint was not OK." },
    { 52 ,"The server didn't reply anything, which here is considered an error." },
    { 53 ,"SSL crypto engine not found." },
    { 54 ,"Cannot set SSL crypto engine as default." },
    { 55 ,"Failed sending network data." },
    { 56 ,"Failure in receiving network data." },
    { 58 ,"Problem with the local certificate." },
    { 59 ,"Couldn't use specified SSL cipher." },
    { 60 ,"Peer certificate cannot be authenticated with known CA certificates." },
    { 61 ,"Unrecognized transfer encoding." },
    { 62 ,"Invalid LDAP URL." },
    { 63 ,"Maximum file size exceeded." },
    { 64 ,"Requested FTP SSL level failed." },
    { 65 ,"Sending the data requires a rewind that failed." },
    { 66 ,"Failed to initialise SSL Engine." },
    { 67 ,"The user name, password, or similar was not accepted and curl failed to log in." },
    { 68 ,"File not found on TFTP server." },
    { 69 ,"Permission problem on TFTP server." },
    { 70 ,"Out of disk space on TFTP server." },
    { 71 ,"Illegal TFTP operation." },
    { 72 ,"Unknown TFTP transfer ID." },
    { 73 ,"File already exists (TFTP)." },
    { 74 ,"No such user (TFTP)." },
    { 75 ,"Character conversion failed." },
    { 76 ,"Character conversion functions required." },
    { 77 ,"Problem with reading the SSL CA cert (path? access rights?)." },
    { 78 ,"The resource referenced in the URL does not exist." },
    { 79 ,"An unspecified error occurred during the SSH session." },
    { 80 ,"Failed to shut down the SSL connection." },
    { 82 ,"Could not load CRL file, missing or wrong format" },
    { 83 ,"Issuer check failed" },
    { 84 ,"The FTP PRET command failed" },
    { 85 ,"RTSP: mismatch of CSeq numbers" },
    { 86 ,"RTSP: mismatch of Session Identifiers" },
    { 87 ,"unable to parse FTP file list" },
    { 88 ,"FTP chunk callback reported error" },
    { -1 ,NULL }
};

typedef enum { opt_none, opt_c, opt_s, opt_g, opt_std } opt_t;

int main (int argc,  char * argv[])
{
    char        c;
    int         usage;
    char        *prognam;
    ssize_t     buf_len;
    char        *buf_dyn;
    int         err;
    const char  *errstr;
    opt_t       opt;
    const SYSERR_LST_t  *errent;
    
    prognam = argv[0];
    opt     = opt_std;
    errent  = NULL;
    errstr  = NULL;
    usage   = 0;
    optarg  = NULL;
    
    err = 0;
    
    while (!usage && ((c=getopt(argc,argv, "csgh?0123456789")) != -1 )) {
        switch(c) {
            case 'c':
                opt = opt_c;
                break;
                
            case 's':
                opt = opt_s;
                break;
                
            case 'g':
                opt = opt_g;
                break;
                
            case '?': // maybe still valid check optopt
                    usage++;
                break;
                
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                //
                // -errno defaults back to standard system errors
                // this allows a system error to be reported using -c -s -g
                //
                opt = opt_std;
                err = (err*10) + (c-'0');
                
                break;
                
            default:
                opt = opt_std;
                usage++;
                break;
        }
    }
    argc -= (optind);
    argv += (optind);
    
    if (err == 0) { // Don't yet have err number so check we have an argument
        if (argc < 1 ) {
            usage++;
        }
        else {
            sscanf(argv[0],"%d", &err);
        }
    }
    
    if (usage) {
        dousage(prognam);
        exit(EINVAL);
    }
    
    
    switch(opt) {
        case opt_none:
            dousage(prognam);
            exit(EINVAL);
            break;
            
        case opt_c:
            errent = lookup_syserr(CURLERR_LST, err);
            break;
            
        case opt_s:
            errent = lookup_syserr(SYSERR_LST, err);
            break;
            
        case opt_g:
            errstr = gai_strerror(err);
            break;
            
        case opt_std:
            errstr = strerror(err);
            break;
    }
    
    if (errent) {
        errstr = errent->errmsg;
    }
    
    if (!errstr) {
        errstr="Unknown error";
    }
    
    fprintf(stdout, "%s\n", errstr);
    exit(err);
}

const SYSERR_LST_t *lookup_syserr(const SYSERR_LST_t *errlist, int err)
{
    const SYSERR_LST_t *rval;
    int idx;
    
    rval = (SYSERR_LST_t *) NULL;
    
    for (idx=0;errlist[idx].errmsg; idx++) {
        if (errlist[idx].err == err) {
            rval = &errlist[idx];
            break;
        }
    }
    return(rval);
}

