; FPUTWC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include io.inc
include stdio.inc
include winnls.inc

    .code

fputwc proc uses rbx wc:wint_t, fp:LPFILE

    ldr cx,wc
    ldr rdx,fp

    .if ( !([rdx]._iobuf._flag & _IOSTRG) )

        .if ( _textmode([rdx]._iobuf._file) == __IOINFO_TM_ANSI )

            .if ( [rax].ioinfo.osfile & FTEXT )

                .new size:int_t
                .new mbc[16]:char_t

                ; text (multi-byte) mode

                .ifd WideCharToMultiByte(CP_ACP, 0, &wc, 1, &mbc, sizeof(mbc), NULL, NULL)

                    .for ( size = eax, ebx = 0: ebx < size: ebx++ )

                        movzx ecx,mbc[rbx]
                        .ifsd ( fputc(ecx, fp) < 0 )

                            .return
                        .endif
                    .endf
                    movzx eax,wc
                   .return
                .endif
                dec rax
               .return
            .endif
        .endif
    .endif

binary_mode:

    movzx ecx,cx
    sub [rdx]._iobuf._cnt,2
    .ifl
        _flswbuf( ecx, rdx )
    .else
        mov eax,ecx
        mov rcx,[rdx]._iobuf._ptr
        add [rdx]._iobuf._ptr,2
        mov [rcx],ax
    .endif
    ret

fputwc endp

    end
