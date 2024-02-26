; _TSPLITPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc
include tchar.inc

.code

_tsplitpath proc uses rsi rdi rbx path:LPTSTR, drive:LPTSTR, dir:LPTSTR, fname:LPTSTR, ext:LPTSTR

    ldr rbx,path

    ldr rcx,drive
    .if ( TCHAR ptr [rbx+TCHAR] == ':' )

        .if ( rcx )

            mov [rcx],TCHAR ptr [rbx]
            mov TCHAR ptr [rcx+TCHAR],':'
            add rcx,TCHAR*2
        .endif
        add rbx,TCHAR*2
    .endif
    .if ( rcx )
        mov TCHAR ptr [rcx],0
    .endif

    .for ( edx=0, edi=0, esi=0, rcx=rbx :: rcx+=TCHAR )

        movzx eax,TCHAR ptr [rcx]

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

            mov [rcx],TCHAR ptr [rdi]
            add rdi,TCHAR
            add rcx,TCHAR
        .endw
        .if ( rsi )
            mov [rcx],TCHAR ptr [rsi]
            add rcx,TCHAR
        .endif
        mov TCHAR ptr [rcx],0
    .endif

    mov rcx,ext
    .if ( rcx )

        .if ( rdx )

            .for ( rdi = rdx :: rdi+=TCHAR, rcx+=TCHAR )

                mov [rcx],TCHAR ptr [rdi]
               .break .if ( eax == 0 )
            .endf
        .endif
        mov TCHAR ptr [rcx],0
    .endif

    mov rcx,fname
    .if ( rcx )

        .if ( rdx == 0 )
            dec rdx
        .endif
        .if ( rsi >= rbx )
            lea rbx,[rsi+TCHAR]
        .endif
        .while ( rbx < rdx )

            mov [rcx],TCHAR ptr [rbx]
           .break .if ( eax == 0 )
            add rcx,TCHAR
            add rbx,TCHAR
        .endw
        mov TCHAR ptr [rcx],0
    .endif
    ret

_tsplitpath endp

    end
