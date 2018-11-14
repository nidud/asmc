; TOUPPER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

    OPTION PROLOGUE:NONE, EPILOGUE:NONE

toupper proc char:SINT
    mov eax,ecx
    sub al,'a'
    cmp al,'z'-'a'+1
    sbb ah,ah
    and ah,'a'-'A'
    sub al,ah
    add al,'a'
    and eax,0xFF
    ret
toupper endp

    end

