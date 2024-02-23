; _WSPLITPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc

.code

_wsplitpath proc uses rsi rdi rbx path:wstring_t, drive:wstring_t, dir:wstring_t, fname:wstring_t, ext:wstring_t

    ldr rbx,path
    ldr rcx,drive
    mov ax,[rbx]
    mov dx,[rbx+2]
    .if ( dx == ':' )

        add rbx,4
        .if ( rcx )

            mov [rcx],ax
            mov [rcx+2],dx
            add rcx,4
        .endif
    .endif
    .if ( rcx )
        mov word ptr [rcx],0
    .endif

    .for ( edx=0, edi=0, esi=0, rcx=rbx :: rcx+=2 )

        mov ax,[rcx]

        .break .if ax == 0
        .if ( ax == '\' || ax == '/' )

            .if ( rdi == 0 )

                mov rdi,rcx
            .endif
            mov rsi,rcx
        .elseif ( ax == '.' )
            mov rdx,rcx
        .endif
    .endf

    mov rcx,dir
    .if ( rcx )

        .while ( rdi < rsi )

            mov ax,[rdi]
            mov [rcx],ax
            add rdi,2
            add rcx,2
        .endw
        .if ( rsi )
            mov ax,[rsi]
            mov [rcx],ax
            add rcx,2
        .endif
        mov word ptr [rcx],0
    .endif

    mov rcx,ext
    .if ( rcx )

        .if ( rdx )

            .for ( rdi = rdx :: rdi+=2, rcx+=2 )

                mov ax,[rdi]
                mov [rcx],ax
               .break .if ( ax == 0 )
            .endf
        .endif
        mov word ptr [rcx],0
    .endif

    mov rcx,fname
    .if ( rcx )

        .if ( rdx == 0 )
            dec rdx
        .endif
        .if ( rsi >= rbx )
            lea rbx,[rsi+2]
        .endif
        .while ( rbx < rdx )

            mov ax,[rbx]
            mov [rcx],ax
           .break .if ( ax == 0 )
            add rcx,2
            add rbx,2
        .endw
        mov word ptr [rcx],0
    .endif
    ret

_wsplitpath endp

    end
