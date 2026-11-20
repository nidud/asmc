;
; https://docs.microsoft.com/en-us/cpp/c-runtime-library/cgets-cgetws?view=vs-2019
;
include conio.inc
include stdio.inc
include errno.inc
include tchar.inc

.code

_tmain proc

  local buffer[83]:tchar_t
  local result:tstring_t

    mov buffer,80 ; Maximum characters in 1st byte
    _tprintf( "Input line of text, followed by carriage return:\n" )
    mov result,_cgetts( &buffer ) ;; C4996
    .if ( !result )
        _tprintf( "An error occurred reading from the console:"
                " error code %d\n", _get_errno(NULL) )
    .else
        _tprintf( "\nLine length = %d\nText = %s\n", buffer[tchar_t], result )
    .endif
    ret
    endp

    end _tstart
