; unsigned atodate(char *string);
;
; dd.mm.yy | yyyy
; mm/dd/yy | yyyy
; yyyy-mm-dd
;
; return: yyyyyyymmmmddddd
;
include time.inc
include stdlib.inc

    .code

atodate proc uses ebx edx ecx string:LPSTR

    mov ebx,string
    .if atol(ebx)           ; first number -- must be > 0
        push eax
        .repeat
            inc ebx
            mov al,[ebx]
            .break .if al < '0'
        .until  al > '9'
        inc ebx
        atol(ebx)           ; second number
        push eax
        .repeat
            inc ebx
            mov al,[ebx]
            .break .if al < '0'
        .until  al > '9'
        inc ebx
        atol(ebx)           ; last number
        mov bl,[ebx-1]      ; seperator
        pop edx             ; second number
        pop ecx             ; first number
        .if bl == '-'
            xchg eax,ecx    ; 2000-03-16
        .elseif bl == '/'
            xchg ecx,edx    ; 03/16/00 | 2000
        .endif
        .if eax <= 1900     ; year 00 | 2000
            .if eax < 80
                add eax,100
            .endif
            add eax,1900
        .endif
        sub eax,DT_BASEYEAR
        shl eax,9           ; year
        shl edx,5           ; month
        or  eax,edx
        or  eax,ecx         ; yyyyyyymmmmddddd
        shl eax,16          ; <date>:<time>
    .endif
    ret
atodate endp

    END
