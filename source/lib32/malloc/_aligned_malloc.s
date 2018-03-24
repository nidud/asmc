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
    mov edi,_aligned_malloc(100, ebx)
    mov eax,1

    .if edi
        mov ecx,ebx
        dec ecx

        .if !( edi & ecx )
            xor eax,eax
        .endif
    .endif
    ret

main endp

    end
