; _TFGETC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
ifdef _UNICODE
include io.inc
include winnls.inc
include ctype.inc
include errno.inc
endif
include tchar.inc

    .code

_fgettc proc fp:LPFILE

ifdef _UNICODE
   .new wc:int_t
   .new mbc[4]:char_t
endif

    ldr rcx,fp

ifdef _UNICODE

    .if ( !( [rcx]._iobuf._flag & _IOSTRG ) )

        .if ( _textmode( [rcx]._iobuf._file ) != __IOINFO_TM_ANSI )

            .ifsd ( fgetc(rcx) < 0 )
                .return
            .endif
            mov mbc,al
            .ifsd ( fgetc(fp) < 0 )
                .return
            .endif
            shl eax,8
            mov al,mbc
           .return

        .elseif ( [rax].ioinfo.osfile & FTEXT )

            ; text (multi-byte) mode

            .ifsd ( fgetc(rcx) < 0 )
                .return
            .endif
            mov mbc,al
            mov wc,1

            .if ( isleadbyte(eax) )

                .ifsd ( fgetc(fp) < 0 )

                    movzx ecx,mbc
                    ungetc(ecx, fp)
                   .return(-1)
                .endif
                mov mbc[1],al
                inc wc
            .endif

            mov ecx,wc
            mov wc,0
            .ifd MultiByteToWideChar(CP_ACP, 0, &mbc, ecx, &wc, 1)

                .return(wc)
            .endif
            .return( _set_errno( EILSEQ ) )
        .endif
    .endif
endif

    .if ( [rcx]._iobuf._cnt >= tchar_t )

        sub [rcx]._iobuf._cnt,tchar_t
        mov rdx,[rcx]._iobuf._ptr
        add [rcx]._iobuf._ptr,tchar_t
        movzx eax,tchar_t ptr [rdx]
    .else
        _tfilbuf(rcx)
    .endif
    ret

_fgettc endp

    end
