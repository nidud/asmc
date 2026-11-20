include conio.inc
include errno.inc
include tchar.inc

.code

_tmain proc
    _set_errno(22)
    _syserr("Error open file", "Can't open the file:\n%s", __FILE__)
   .return(0)
    endp

    end
