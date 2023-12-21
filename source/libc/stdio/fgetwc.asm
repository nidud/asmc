; FGETWC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include io.inc
include stdio.inc
include winnls.inc
include ctype.inc
include errno.inc

    .code

fgetwc proc fp:LPFILE
ifdef __UNIX__
    mov rax,-1
else
   .new wc:int_t
   .new mbc[4]:char_t

    ldr rcx,fp

    .if ( !([rcx]._iobuf._flag & _IOSTRG) )

        .if ( _textmode([rcx]._iobuf._file) != __IOINFO_TM_ANSI )

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
                    ungetc(ecx, rsi)
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

            _set_errno(EILSEQ)
            .return(-1)
        .endif
    .endif

binary_mode:

    .if ( [rcx]._iobuf._cnt >= sizeof(wchar_t) )

        sub [rcx]._iobuf._cnt,sizeof(wchar_t)
        mov rcx,[rdx]._iobuf._ptr
        add [rdx]._iobuf._ptr,2
        movzx eax,wchar_t ptr [rcx]
    .else

        _filwbuf(rcx)
    .endif
endif
    ret

fgetwc endp

    end
