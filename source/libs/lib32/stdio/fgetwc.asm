; FGETWC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include ctype.inc
include stdlib.inc
include io.inc
include errno.inc

    .code

    assume esi:ptr _iobuf

fgetwc proc uses esi edi fp:LPFILE

  local mbc[4]:byte, wch:word

    mov esi,fp
    mov eax,[esi]._flag
    mov ecx,[esi]._file

    .repeat
        .if eax & _IOSTRG && _osfile[ecx] & FH_TEXT

            mov edi,1
            ;
            ; text (multi-byte) mode
            ;
            .break .if fgetc(esi) == -1

            mov mbc,al

            .if isleadbyte(eax)

                .if fgetc(esi) == -1

                    movzx eax,mbc
                    ungetc(eax, esi)
                    mov eax,-1
                    .break
                .endif

                mov mbc[1],al
                mov edi,2
            .endif

            movzx ecx,mbc
            .if mbtowc(addr wch, ecx, edi) == -1
                ;
                ; Conversion failed! Set errno and return
                ; failure.
                ;

                mov errno,EILSEQ
                mov eax,-1
                .break
            .endif
            movzx eax,wch
            .break
        .endif

        ;
        ; binary (Unicode) mode
        ;
        sub [esi]._cnt,2
        .ifs [esi]._cnt >= 0

            add [esi]._ptr,2
            mov eax,[esi]._ptr
            movzx eax,word ptr [eax-2]
        .else
            _filwbuf(esi)
        .endif
    .until 1
    ret

fgetwc endp

    END
