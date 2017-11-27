; char *strspace(char *) - search a string for the character SPACE and TAB
;
; If found the char is returned in CL and the pointer in EAX
; Else zero is returned and ECX points to the last char in the string
;
include strlib.inc

    .code

strspace proc string:LPSTR

    mov ecx,string

    .repeat
        .repeat
            mov al,[ecx]
            inc ecx
            .if al == ' ' || al == 9
                mov eax,ecx
                dec eax
                movzx ecx,byte ptr [eax]
                .break(1)
            .endif
        .until !al
        dec ecx
        xor eax,eax
    .until 1
    ret

strspace endp

    END

