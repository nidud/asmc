; FTELL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc
include errno.inc
include winbase.inc

    .code

    assume rbx:ptr _iobuf

ftell proc uses rdi rbx fp:LPFILE

  local filepos:SINT
  local fd:HANDLE
  local rdcnt:UINT
  local osfile:BYTE

    mov rbx,rcx
    .if [rbx]._cnt < 0
        mov [rbx]._cnt,0
    .endif

    mov edx,[rbx]._file
    lea rcx,_osfile
    mov al,[rcx+rdx]
    lea rcx,_osfhnd
    mov rcx,[rcx+rdx*8]
    mov fd,rcx
    mov osfile,al

    .ifsd SetFilePointer(rcx, 0, 0, SEEK_CUR) < 0

        .return _dosmaperr(GetLastError())
    .endif

    mov ecx,[rbx]._flag
    .if !( ecx & _IOMYBUF or _IOYOURBUF )

        sub eax,[rbx]._cnt
        .return
    .endif

    mov filepos,eax
    mov rdi,[rbx]._ptr
    sub rdi,[rbx]._base

    .if ecx & _IOWRT or _IOREAD

        .if osfile & FH_TEXT

            mov rax,[rbx]._base
            .while rax < [rbx]._ptr

                .if byte ptr [rax] == 10

                    inc rdi
                .endif
                inc rax
            .endw
        .endif

    .elseif !( ecx & _IORW )

        _set_errno(EINVAL)
        .return -1
    .endif

    mov rax,rdi
    .return .if !rax

    .if ecx & _IOREAD

        mov eax,[rbx]._cnt
        .if !eax

            mov rdi,rax
        .else

            add rax,[rbx]._ptr
            sub rax,[rbx]._base
            mov rdcnt,eax

            .if osfile & FH_TEXT

                .ifd SetFilePointer(fd, 0, 0, SEEK_END) == filepos

                    mov eax,rdcnt
                    mov rcx,[rbx]._base
                    add rax,rcx

                    .while rcx < rax

                        .if byte ptr [rcx] == 10

                            inc rdcnt
                        .endif
                        inc rcx
                    .endw
                    .if [rbx]._flag & _IOCTRLZ

                        inc rdcnt
                    .endif
                .else

                    SetFilePointer(fd, filepos, 0, SEEK_SET)
                    mov eax,[rbx]._flag

                    .if rdcnt <= 512 && (eax & _IOMYBUF) && !(eax & _IOSETVBUF)

                        mov rdcnt,512
                    .else
                        mov eax,[rbx]._bufsiz
                        mov rdcnt,eax
                    .endif

                    .if osfile & FH_CRLF

                        inc rdcnt
                    .endif
                .endif
            .endif
            mov eax,rdcnt
            sub filepos,eax
        .endif
    .endif
    add edi,filepos
    mov eax,edi
    ret

ftell endp

    END
