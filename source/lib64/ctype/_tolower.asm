include ctype.inc

    .code

    OPTION PROLOGUE:NONE, EPILOGUE:NONE

_tolower proc char:SINT

    movzx eax,cl
    sub al,'A'+'a'
    ret

_tolower ENDP

    END

