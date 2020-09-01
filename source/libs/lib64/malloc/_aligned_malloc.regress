;
; https://msdn.microsoft.com/en-us/library/8z34s9c6.aspx
;
include stdio.inc
include malloc.inc

    .code

main proc
    ;
    ; Note alignment should be 2^N where N is any positive int.
    ;
    mov ebx,512
    ;
    ; Using _aligned_malloc
    ;
    mov rdi,_aligned_malloc(100, ebx)
    .if rdi
        mov ecx,ebx
        dec ecx
        .if !( rdi & rcx )
            xor eax,eax
        .else
            mov eax,1
        .endif
    .else
        mov eax,2
    .endif
    ret

main endp

    end
