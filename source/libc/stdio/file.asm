; FILE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include malloc.inc
include rterr.inc

public _stdbuf

.data
 stdin      LPFILE NULL
 stdout     LPFILE NULL
 stderr     LPFILE NULL
 _stdbuf    string_t 2 dup(0) ; buffer for stdout and stderr

.code

__initstdio proc uses rbx

    .if ( _nstream ==  0 )
        mov _nstream,_NSTREAM_
    .elseif ( _nstream < _IOB_ENTRIES )
        mov _nstream,_IOB_ENTRIES
    .endif

    imul ebx,_nstream,_iobuf
    .if ( malloc( &[rbx+_INTIOBUF*3] ) == NULL )

        .return( _RT_STDIOINIT )
    .endif

    mov rdx,rdi
    mov rdi,rax
    lea ecx,[rbx+_INTIOBUF]
    mov rbx,rax
    xor eax,eax
    rep stosb
    mov rdi,rdx

    assume rbx:ptr _iobuf

    imul eax,_nstream,_iobuf
    add rax,rbx
    lea rdx,_stdbuf

    mov [rbx]._ptr,rax
    mov [rbx]._base,rax
    mov [rbx]._flag,_IOREAD or _IOYOURBUF
    mov [rbx]._bufsiz,_INTIOBUF
    mov stdin,rbx

    add rbx,_iobuf
    mov [rbx]._flag,_IOWRT
    mov [rbx]._file,1
    mov stdout,rbx
    add rax,_INTIOBUF
    mov [rdx],rax

    add rbx,_iobuf
    mov [rbx]._flag,_IOWRT
    mov [rbx]._file,2
    mov stderr,rbx
    add rax,_INTIOBUF
    mov [rdx+string_t],rax

    add rbx,_iobuf
    .for ( ecx = 3 : ecx < _nstream : ecx++, rbx+=_iobuf )
        mov [rbx]._file,-1
    .endf
    xor eax,eax
    ret

__initstdio endp


__endstdio proc uses rbx

    .if ( stdin != NULL )

        .for ( ebx = 3 : ebx < _nstream : ebx++ )

            imul ecx,ebx,_iobuf
            add rcx,stdin

            .if ( [rcx]._iobuf._file != -1 )
                fclose(rcx)
            .endif
        .endf
        free(stdin)
        mov stdin,NULL
    .endif
    ret

__endstdio endp

.pragma init(__initstdio, 4)
.pragma exit(__endstdio, 98)

    end
