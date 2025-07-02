; _TSPLITPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc
include tchar.inc

.code

_tsplitpath proc uses rsi rdi rbx path:tstring_t, drive:tstring_t, dir:tstring_t, fname:tstring_t, ext:tstring_t

    ldr rbx,path

    ldr rcx,drive
    .if ( tchar_t ptr [rbx+tchar_t] == ':' )

        .if ( rcx )

            mov [rcx],tchar_t ptr [rbx]
            mov tchar_t ptr [rcx+tchar_t],':'
            add rcx,tchar_t*2
        .endif
        add rbx,tchar_t*2
    .endif
    .if ( rcx )
        mov tchar_t ptr [rcx],0
    .endif

    .for ( edx=0, edi=0, esi=0, rcx=rbx :: rcx+=tchar_t )

        movzx eax,tchar_t ptr [rcx]

        .break .if eax == 0
        .if ( eax == '\' || eax == '/' )

            .if ( rdi == 0 )

                mov rdi,rcx
            .endif
            mov rsi,rcx
        .elseif ( eax == '.' )
            mov rdx,rcx
        .endif
    .endf

    mov rcx,dir
    .if ( rcx )

        .while ( rdi < rsi )

            mov [rcx],tchar_t ptr [rdi]
            add rdi,tchar_t
            add rcx,tchar_t
        .endw
        .if ( rsi )
            mov [rcx],tchar_t ptr [rsi]
            add rcx,tchar_t
        .endif
        mov tchar_t ptr [rcx],0
    .endif

    mov rcx,ext
    .if ( rcx )

        .if ( rdx )

            .for ( rdi = rdx :: rdi+=tchar_t, rcx+=tchar_t )

                mov [rcx],tchar_t ptr [rdi]
               .break .if ( eax == 0 )
            .endf
        .endif
        mov tchar_t ptr [rcx],0
    .endif

    mov rcx,fname
    .if ( rcx )

        .if ( rdx == 0 )
            dec rdx
        .endif
        .if ( rsi >= rbx )
            lea rbx,[rsi+tchar_t]
        .endif
        .while ( rbx < rdx )

            mov [rcx],tchar_t ptr [rbx]
           .break .if ( eax == 0 )
            add rcx,tchar_t
            add rbx,tchar_t
        .endw
        mov tchar_t ptr [rcx],0
    .endif
    ret

_tsplitpath endp

    end
