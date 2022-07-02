; __ARGV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include crtl.inc
include winbase.inc

.data
 __argv  array_t 0
 _pgmptr string_t 0

.code

Install proc private

  local pgname[260]:char_t

    mov __argv,setargv(&__argc, GetCommandLineA())

    mov rax,[rax]

    .if ( byte ptr [rax+1] != ':' )

        free(rax)

        ; Get the program name pointer from Win32 Base

        mov rcx,malloc( &[GetModuleFileNameA(0, &pgname, 260)+1] )
        strcpy( rcx, &pgname )

        mov rcx,__argv
        mov [rcx],rax

        .if ( byte ptr [rax] == '"' )

            .for ( rdx = rax : byte ptr [rdx] : rdx++ )

                mov al,[rdx+1]
                mov [rdx],al
            .endf
            .if ( byte ptr [rdx-2] == '"' )
                mov byte ptr [rdx-2],0
            .endif
            mov rax,[rcx]
        .endif
    .endif
    mov _pgmptr,rax
    ret

Install endp


__p___argv proc

    lea rax,__argv
    ret

__p___argv endp


_get_pgmptr proc array:array_t

    mov rax,_pgmptr
    mov [rcx],rax
    ret

_get_pgmptr endp

.pragma(init(Install, 4))

    end
