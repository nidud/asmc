; _TMKTEMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include io.inc
include string.inc
include errno.inc
ifdef __UNIX__
include stdlib.inc
else
include winbase.inc
endif
include tchar.inc

    .code

    assume rbx:tstring_t, rsi:tstring_t

_tmktemp_s proc uses rsi rdi rbx template:tstring_t, sizeInChars:size_t

   .new string:tstring_t
   .new letter:int_t = 'a'
   .new xcount:size_t
   .new save_errno:errno_t

    ldr rbx,template
    ldr rdx,sizeInChars

    .if ( rbx == NULL || rdx == 0 )

        .return( EINVAL )
    .endif

    mov xcount,_tcsnlen(rbx, rdx)
ifdef __UNIX__
    rand()
else
    GetCurrentThreadId()
endif
    mov rcx,xcount
    .if ( rcx >= sizeInChars || rcx < 6 )

        mov [rbx],0
       .return( EINVAL )
    .endif
ifdef _UNICODE
    add rcx,rcx
endif
    lea rsi,[rbx+rcx-tchar_t]

    .for ( ecx = 10, edi = 0 : rsi > rbx && [rsi] == 'X' && edi < 5 : rsi-=tchar_t, edi++ )

        xor edx,edx
        div ecx
        add dl,'0'
        mov [rsi],_tdl
    .endf
    .if ( [rsi] != 'X' || edi < 5 )

        mov [rbx],0
       .return( EINVAL )
    .endif
    mov eax,letter
    inc letter
    mov [rsi],_tal
    mov string,rsi

    mov eax,errno
    mov save_errno,eax
    _set_errno( 0 )

    .while 1

        .ifd _taccess(rbx, 0)
            .break .ifd ( errno != EACCES )
        .endif
        .if ( letter == 'z' + 1 )

            _set_errno( EEXIST )
            mov [rbx],0
           .return( EEXIST )
        .endif
        mov rcx,string
        mov eax,letter
        inc letter
        mov [rcx],_tal
        _set_errno( 0 )
    .endw
    _set_errno( save_errno )
    xor eax,eax
    ret

_tmktemp_s endp


_tmktemp proc uses rbx template:tstring_t

    ldr rbx,template

    .if ( rbx == NULL )
        _set_errno( EINVAL )
        .return( 0 )
    .endif
    .ifd _tmktemp_s(rbx, &[_tcslen(rbx)+1])
        .return( 0 )
    .endif
    mov rax,rbx
    ret

_tmktemp endp

    end
