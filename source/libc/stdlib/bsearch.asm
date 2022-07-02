; BSEARCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include errno.inc

    .code

bsearch proc uses rsi rdi rbx key:ptr, base:ptr, num:size_t, width:size_t, compare:_PtFuncCompare

   .new mid:size_t

    ; validation section

    mov rax,compare
    .if ( rax == NULL || ( base == NULL && num != 0 ) || width == 0 )

        _set_errno(EINVAL)
        .return( 0 )
    .endif

    ; We allow a NULL key here because it breaks some older code and
    ; because we do not dereference this ourselves so we can't be sure that
    ; it's a problem for the comparison function

    mov rsi,base
    mov rax,num
    dec rax
    mul width
    lea rdi,[rax+rsi]

    .while ( rsi <= rdi )

        mov rbx,num
        shr rbx,1

        .if rbx

            mov mid,rsi
            mov rax,rbx
            .if !( byte ptr num & 1 )
                dec rax
            .endif

            mul width
            add mid,rax

            .ifd !compare(key, mid)

                .return( mid )

            .elseifs ( eax < 0 )

                mov rdi,mid
                sub rdi,width
                mov rax,num

                .if ( al & 1 )
                    mov rax,rbx
                .else
                    lea rax,[rbx-1]
                .endif
                mov num,rax

            .else

                mov rsi,mid
                add rsi,width
                mov num,rbx
            .endif

        .elseif num

            .break .ifd compare(key, rsi)
            .return( rsi )

        .else

            .break
        .endif
    .endw
    .return( 0 )

bsearch endp

    end
