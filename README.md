This utility is useful to format err numbers return by various parts of the 
system for display inside scripts or generally instead of grep'ng them in errno.h


Usage: ./strerror [-c|-s|-g|-<errno>] <errno>
print error message matching errno and exit with status errno
-c use curl error lookups
-s use sysexits
-g use gia_strerror
-<errno> report using standard system errors even when -c,-s,-g enabled
