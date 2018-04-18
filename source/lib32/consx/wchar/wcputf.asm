include consx.inc
include stdio.inc

    .code

wcputf proc c b:PVOID, l, m, format:LPSTR, argptr:VARARG

    ftobufin(format, addr argptr)
    wcputs(b, l, m, addr _bufin)
    ret

wcputf endp

    END
