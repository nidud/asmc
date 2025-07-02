; _TUNGETC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
ifdef _UNICODE
include io.inc
include winnls.inc
include limits.inc
endif
include tchar.inc

    .code

    assume rbx:LPFILE

_ungettc proc uses rbx c:int_t, fp:LPFILE

    ldr rbx,fp
    .if ( c == EOF ||
         !( [rbx]._flag & _IOREAD || ( [rbx]._flag & _IORW && !( [rbx]._flag & _IOWRT ) ) ) )

        .return( -1 )
    .endif

    .if ( [rbx]._base == NULL )

        _getbuf(rbx)
    .endif

ifdef _UNICODE

    .if ( !( [rbx]._flag & _IOSTRG ) && _osfile([rbx]._file) & FTEXT )

        .new size:int_t
        .new mbc[MB_LEN_MAX]:char_t

        .if ( _textmode( [rbx]._file ) == __IOINFO_TM_ANSI )

            .ifd ( WideCharToMultiByte(CP_ACP, 0, &c, 1, &mbc, MB_LEN_MAX, 0, 0) == 0 )

                dec rax
               .return
            .endif
            mov size,eax

        .else

            mov eax,c
            mov mbc[0],al
            mov mbc[1],ah
            mov size,2
        .endif

        mov eax,size
        add rax,[rbx]._base

        .if ( [rbx]._ptr < rax )

            .if ( [rbx]._cnt || [rbx]._bufsiz < 2 )
                .return( -1 )
            .endif
            mov [rbx]._ptr,rax
        .endif

        .for ( ecx = 0 : ecx < size : ecx++ )

            dec [rbx]._ptr
            mov rdx,[rbx]._ptr
            mov al,mbc[rcx]
            mov [rdx],al
        .endf
        add [rbx]._cnt,size
        jmp done

    .endif

    mov eax,2
    add rax,[rbx]._base

    .if ( [rbx]._ptr < rax )

        .if ( [rbx]._cnt || [rbx]._bufsiz < 2 )
            .return( -1 )
        .endif
        mov [rbx]._ptr,rax
    .endif

else

    .if ( [rbx]._ptr == [rbx]._base )

        .if ( [rbx]._cnt )

            .return( -1 )
        .endif
        add [rbx]._ptr,tchar_t
    .endif

endif

    mov eax,c
    .if ( [rbx]._flag & _IOSTRG )

        sub [rbx]._ptr,tchar_t
        mov rcx,[rbx]._ptr
        .if ( _tal != [rcx] )

            add [rbx]._ptr,tchar_t
           .return( -1 )
        .endif
    .else

        sub [rbx]._ptr,tchar_t
        mov rcx,[rbx]._ptr
        mov [rcx],_tal
    .endif
    add [rbx]._cnt,tchar_t

done:

    and [rbx]._flag,not _IOEOF
    or  [rbx]._flag,_IOREAD
    movzx eax,tchar_t ptr c
    ret

_ungettc endp

    end
