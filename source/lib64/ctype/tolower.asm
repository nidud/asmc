; TOLOWER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

    OPTION PROLOGUE:NONE, EPILOGUE:NONE

tolower proc char:SINT
    mov eax,ecx
    sub al,'A'
    cmp al,'Z'-'A'+1
    sbb ah,ah
    and ah,'a'-'A'
    add al,ah
    add al,'A'
    and eax,0xFF
    ret
tolower endp

    end

