; _SPLITPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc

.code

_splitpath proc uses rsi rdi rbx path:string_t, drive:string_t, dir:string_t, fname:string_t, ext:string_t

    ldr rbx,path
    ldr rcx,drive
    mov ax,[rbx]
    .if ( ah == ':' )

        add rbx,2
        .if ( rcx )

            mov [rcx],ax
            add rcx,2
        .endif
    .endif
    .if ( rcx )
        mov byte ptr [rcx],0
    .endif

    .for ( edx=0, edi=0, esi=0, rcx=rbx :: rcx++ )

        mov al,[rcx]

        .break .if al == 0
        .if ( al == '\' || al == '/' )

            .if ( rdi == 0 )

                mov rdi,rcx
            .endif
            mov rsi,rcx
        .elseif ( al == '.' )
            mov rdx,rcx
        .endif
    .endf

    mov rcx,dir
    .if ( rcx )

        .while ( rdi < rsi )

            mov al,[rdi]
            mov [rcx],al
            inc rdi
            inc rcx
        .endw
        .if ( rsi )
            mov al,[rsi]
            mov [rcx],al
            inc rcx
        .endif
        mov byte ptr [rcx],0
    .endif

    mov rcx,ext
    .if ( rcx )

        .if ( rdx )

            .for ( rdi = rdx :: rdi++, rcx++ )

                mov al,[rdi]
                mov [rcx],al
               .break .if ( al == 0 )
            .endf
        .endif
        mov byte ptr [rcx],0
    .endif

    mov rcx,fname
    .if ( rcx )

        .if ( rdx == 0 )
            dec rdx
        .endif
        .if ( rsi >= rbx )
            lea rbx,[rsi+1]
        .endif
        .while ( rbx < rdx )

            mov al,[rbx]
            mov [rcx],al
           .break .if ( al == 0 )
            inc rcx
            inc rbx
        .endw
        mov byte ptr [rcx],0
    .endif
    ret

_splitpath endp

    end
