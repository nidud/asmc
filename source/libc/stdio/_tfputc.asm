; FPUTWC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc
include io.inc
ifdef _UNICODE
include winnls.inc
endif
include tchar.inc

    .code

ifdef _UNICODE

_fputtc proc uses rbx c:int_t, fp:LPFILE

else

_fputtc proc c:int_t, fp: LPFILE

endif

    ldr rdx,fp
    ldr ecx,c

ifdef _UNICODE

    .if ( !( [rdx]._iobuf._flag & _IOSTRG ) )

        .if ( _textmode([rdx]._iobuf._file) == __IOINFO_TM_ANSI )

            .if ( [rax].ioinfo.osfile & FTEXT )

                .new size:int_t
                .new mbc[16]:char_t

                ; text (multi-byte) mode

                .ifd WideCharToMultiByte(CP_ACP, 0, &c, 1, &mbc, sizeof(mbc), NULL, NULL)

                    .for ( size = eax, ebx = 0: ebx < size: ebx++ )

                        movzx ecx,mbc[rbx]
                        .ifsd ( fputc(ecx, fp) < 0 )

                            .return
                        .endif
                    .endf
                    movzx eax,word ptr c
                   .return
                .endif
                dec rax
               .return
            .endif
        .endif
    .endif
    movzx ecx,cx
endif

    sub [rdx]._iobuf._cnt,tchar_t
    .ifl
        _tflsbuf( ecx, rdx )
    .else
        mov eax,ecx
        mov rcx,[rdx]._iobuf._ptr
        add [rdx]._iobuf._ptr,tchar_t
        mov [rcx],_tal
    .endif
    ret

_fputtc endp

    end
