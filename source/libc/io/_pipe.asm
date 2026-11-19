; _PIPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
ifdef __UNIX__
include unistd.inc
include sys/syscall.inc

.code

pipe proc uses rbx pfd:ptr int_t
    ldr rbx,pfd
    .ifsd ( sys_pipe( rbx ) < 0 )
        neg eax
        _set_errno( eax )
    .endif
    mov ecx,[rbx]
    .ifs ( ecx >= 0 && ecx < _nfile )
        mov [_pioinfo(ecx)].ioinfo.osfile,FOPEN or FPIPE
    .endif
    mov ecx,[rbx+4]
    .ifs ( ecx >= 0 && ecx < _nfile )
        mov [_pioinfo(ecx)].ioinfo.osfile,FOPEN or FPIPE
    .endif
    xor eax,eax
    ret
    endp

else

include fcntl.inc
include stdlib.inc
include winbase.inc

.code

_pipe proc uses rsi rdi rbx phandles:ptr int_t, psize:uint_t, textmode:int_t

   .new dosretval:ULONG
   .new handle0:int_t = 0
   .new handle1:int_t = 0
   .new toomanyfiles:int_t = 0
   .new ReadHandle:HANDLE
   .new WriteHandle:HANDLE
   .new SecurityAttributes:SECURITY_ATTRIBUTES

    ldr rbx,phandles
    ldr esi,psize
    ldr edi,textmode

    mov eax,edi
    and eax,_O_BINARY or _O_TEXT
    .if ( rbx == NULL || ( edi & not ( _O_NOINHERIT or _O_BINARY or _O_TEXT ) ) || ( eax == _O_BINARY or _O_TEXT ) )
        .return( _set_errno( EINVAL ) )
    .endif
    mov eax,-1
    mov [rbx],eax
    mov [rbx+4],eax
    mov SecurityAttributes.nLength,sizeof(SecurityAttributes)
    mov SecurityAttributes.lpSecurityDescriptor,NULL
    .if ( edi & _O_NOINHERIT )
        mov SecurityAttributes.bInheritHandle,FALSE
    .else
        mov SecurityAttributes.bInheritHandle,TRUE
    .endif
    .if ( !CreatePipe(&ReadHandle, &WriteHandle, &SecurityAttributes, esi) )
        .return( _dosmaperr( GetLastError() ) )
    .endif

    ; now we must allocate C Runtime handles for Read and Write handles

    .ifd ( _alloc_osfhnd() != -1 )
        mov handle0,eax
        mov [rcx].ioinfo.osfile,FOPEN or FPIPE or FTEXT
        mov [rcx].ioinfo.textmode,0
        mov [rcx].ioinfo.unicode,0
        .ifd ( _alloc_osfhnd() != -1 )
            mov handle1,eax
            mov [rcx].ioinfo.osfile,FOPEN or FPIPE or FTEXT
            mov [rcx].ioinfo.textmode,0
            mov [rcx].ioinfo.unicode,0
            .new fmode:int_t = 0
            _get_fmode(&fmode)
            .if ( edi & _O_BINARY || ( !( edi & _O_TEXT ) && fmode == _O_BINARY ) )
                and _osfile(handle0),not FTEXT
                and _osfile(handle1),not FTEXT
            .endif
            .if ( edi & _O_NOINHERIT )
                or _osfile(handle0),FNOINHERIT
                or _osfile(handle1),FNOINHERIT
            .endif
            _set_osfhnd(handle0, ReadHandle)
            _set_osfhnd(handle1, WriteHandle)
        .else
            mov _osfile(handle0),0
            mov toomanyfiles,1
        .endif
    .else
        mov toomanyfiles,1
    .endif

    ; If error occurred, close Win32 handles and return -1

    .if ( toomanyfiles )
        CloseHandle(ReadHandle)
        CloseHandle(WriteHandle)
        mov _doserrno,0 ; not an o.s. error
        .return( _set_errno( EMFILE ) )
    .endif
    mov eax,handle0
    mov ecx,handle1
    mov [rbx],eax
    mov [rbx+4],ecx
    xor eax,eax
    ret
    endp
endif
    end
