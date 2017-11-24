include io.inc
include errno.inc
include winbase.inc

.code
.win64:nosave

_close proc handle:SINT

    lea rax,_osfile
    .if ecx < 3 || ecx >= _nfile || !(byte ptr [rax+rcx] & FH_OPEN)

        mov errno,EBADF
        mov oserrno,0
        xor rax,rax
    .else

        mov BYTE PTR [rax+rcx],0
        lea rax,_osfhnd
        mov rcx,[rax+rcx*8]
        .if !CloseHandle(rcx)

            osmaperr()
        .else
            xor eax,eax
        .endif
    .endif
    ret

_close endp

    end
