; FTELLI64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include stdio.inc

    .code

    assume rbx:ptr _iobuf

_ftelli64 proc uses rbx fp:LPFILE

  local filepos:size_t
  local offs:size_t
  local rdcnt:uint_t
  local osfile:BYTE

    ldr rbx,fp
    .if ( [rbx]._cnt < 0 )
        mov [rbx]._cnt,0
    .endif

    mov osfile,_osfile([rbx]._file)
    mov filepos,_lseeki64( [rbx]._file, 0, SEEK_CUR )
    .ifs ( rax < 0 )
        .return( -1 )
    .endif
    mov ecx,[rbx]._flag
    .if ( !( ecx & _IOMYBUF or _IOYOURBUF ) )

        mov ecx,[rbx]._cnt
        sub rax,rcx
       .return
    .endif

    mov rdx,[rbx]._ptr
    sub rdx,[rbx]._base

    .if ( ecx & _IOWRT or _IOREAD )

        .if ( osfile & FTEXT )

            mov rax,[rbx]._base
            .while ( rax < [rbx]._ptr )
                .if ( byte ptr [rax] == 10 )
                    inc rdx
                .endif
                inc rax
            .endw
        .endif

    .elseif ( !( ecx & _IORW ) )

       .return( _set_errno( EINVAL ) )
    .endif

    mov rax,rdx
    .return .if !rax

    .if ( ecx & _IOREAD )

        mov eax,[rbx]._cnt
        .if ( !eax )

            mov rdx,rax
        .else

            add rax,[rbx]._ptr
            sub rax,[rbx]._base
            mov rdcnt,eax
            mov offs,rdx

            .if ( osfile & FTEXT )

                .if ( _lseeki64( [rbx]._file, 0, SEEK_END ) == filepos )

                    mov eax,rdcnt
                    mov rcx,[rbx]._base
                    add rax,rcx

                    .while ( rcx < rax )

                        .if ( byte ptr [rcx] == 10 )

                            inc rdcnt
                        .endif
                        inc rcx
                    .endw
                    .if ( [rbx]._flag & _IOCTRLZ )

                        inc rdcnt
                    .endif
                .else

                    _lseeki64( [rbx]._file, filepos, SEEK_SET )
                    mov eax,[rbx]._flag

                    .if ( rdcnt <= 512 && (eax & _IOMYBUF) && !( eax & _IOSETVBUF ) )

                        mov rdcnt,512
                    .else
                        mov eax,[rbx]._bufsiz
                        mov rdcnt,eax
                    .endif

                    .if ( osfile & FCRLF )

                        inc rdcnt
                    .endif
                .endif
            .endif
            mov rdx,offs
            mov eax,rdcnt
            sub filepos,rax
        .endif
    .endif
     add rdx,filepos
    .return( rdx )

_ftelli64 endp

    end
