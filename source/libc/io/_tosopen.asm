; _TOSOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include string.inc
include errno.inc
ifndef __UNIX__
include winbase.inc
include winnls.inc
include malloc.inc
include stdlib.inc
endif
include tchar.inc

.code

_tosopen proc uses rsi rbx file:tstring_t, attrib:uint_t, mode:uint_t, action:uint_t

ifdef __UNIX__
    mov eax,-1
else

   .new fd:int_t
   .new share:int_t = 0
    ldr rbx,file

    .if ( mode == M_RDONLY )
        mov share,FILE_SHARE_READ
    .endif
    .ifd ( _alloc_osfhnd() == -1 )

        .return( _set_errno( EMFILE ) )
    .endif
    mov fd,eax
    mov rsi,rcx
ifndef _UNICODE
    mov rbx,_utftows(rbx)
endif

    .ifd ( CreateFileW(rbx, mode, share, 0, action, attrib, 0) == -1 )

        .ifd ( GetLastError() != ERROR_FILENAME_EXCED_RANGE )

            .return( _dosmaperr( eax ) )
        .endif

ifndef _UNICODE
        sub rbx,8
else
        lea rcx,[wcslen(rbx)*2+10]
        lea rcx,[alloca(ecx)+8]
        lea rbx,[wcscpy(rcx,rbx)-8]
endif
        mov eax,(('\' shl 16) or '\')
        mov [rbx],eax
        mov eax,(('?' shl 16) or '\')
        mov [rbx+4],eax

        .ifd ( CreateFileW(rbx, mode, share, 0, action, attrib, 0) == -1 )

            .return( _dosmaperr( GetLastError() ) )
        .endif
    .endif

    mov [rsi].ioinfo.osfhnd,rax
    or  [rsi].ioinfo.osfile,FOPEN
    mov eax,fd
endif
    ret

_tosopen endp

    end
