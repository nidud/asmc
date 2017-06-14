;
; https://msdn.microsoft.com/en-us/library/8z34s9c6.aspx
;
include stdio.inc
include alloc.inc

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
            printf("This pointer, %p, is aligned on %u\n", rdi, ebx)
        .else
            printf("This pointer, %p, is not aligned on %u\n", rdi, ebx)
        .endif
        xor eax,eax
    .else
        printf("Error allocation aligned memory.")
        mov eax,1
    .endif
    ret

main endp

    end
