; BSEARCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include errno.inc

    .code

bsearch proc uses rbx key:ptr, base:ptr, num:size_t, width:size_t, compare:_PtFuncCompare

   .new mid:size_t
   .new lo:string_t
   .new hi:string_t

    ldr rbx,base
    ldr rax,num
    ldr rcx,width

    ; validation section

    mov rdx,compare
    .if ( rdx == NULL || ( rbx == NULL && rax != 0 ) || rcx == 0 )

        _set_errno(EINVAL)
        .return( 0 )
    .endif

    ; We allow a NULL key here because it breaks some older code and
    ; because we do not dereference this ourselves so we can't be sure that
    ; it's a problem for the comparison function

    dec rax
    mul rcx
    lea rdx,[rax+rbx]
    mov lo,rbx
    mov hi,rdx

    .while ( lo <= hi )

        mov rbx,num
        shr rbx,1

        .if rbx

            mov mid,lo
            mov rax,rbx
            .if !( byte ptr num & 1 )
                dec rax
            .endif

            mul width
            add mid,rax

            .ifd !compare(key, mid)

                .return( mid )

            .elseifs ( eax < 0 )

                mov hi,mid
                sub hi,width
                mov rax,num

                .if ( al & 1 )
                    mov rax,rbx
                .else
                    lea rax,[rbx-1]
                .endif
                mov num,rax

            .else

                mov lo,mid
                add lo,width
                mov num,rbx
            .endif

        .elseif num

            .break .ifd compare(key, lo)
            .return( lo )
        .else
            .break
        .endif
    .endw
    .return( 0 )

bsearch endp

    end
