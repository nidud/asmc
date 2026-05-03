; ASMC2.ASM--
;
; The size of the _iobuf (FILE) structure needs
; to be correct for the _iob function.
;

include stdio.inc
include tchar.inc

.code
_tmain proc
    mov rcx,__iob_func()
    _tprintf(
        "stdin._file:  %d (0)\n"
        "stdout._file: %d (1)\n"
        "stderr._file: %d (2)\n", [rcx].FILE._file, [rcx+FILE].FILE._file, [rcx+FILE*2].FILE._file )
    .return( 0 )
    endp
    end _tstart
