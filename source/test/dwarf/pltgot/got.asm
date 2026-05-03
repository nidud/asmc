; GOT.ASM--
;
; Data access to shared libraries using -fpic or -fPIC
;

include stdio.inc

.code

__acrt_iob_func proc id:dword
ifdef _WIN64
    .if ( edi == 0 )
        mov rax,stdin
    .elseif ( edi == 1 )
        mov rax,stdout
    .else
        mov rax,stderr
    .endif
if __PIC__ eq 1 ; -fpic
    mov rax,[rax]
endif
else
    call @F
@@: pop eax
    add eax,_GLOBAL_OFFSET_TABLE_ + 2
    .if ( id == 0 )
        mov eax,stdin[eax]
    .elseif ( id == 1 )
        mov eax,stdout[eax]
    .else
        mov eax,stderr[eax]
    .endif
endif
    ret
    endp

    end
