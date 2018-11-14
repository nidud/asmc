; FGETS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

    assume ebx:ptr _iobuf

fgets proc uses edi ebx buf:LPSTR, count:SINT, fp:LPFILE

    mov edi,buf
    mov ecx,count
    mov ebx,fp
    xor eax,eax

    .repeat
        .break .ifs ecx <= eax
        dec ecx
        .for : ecx : ecx--

            dec [ebx]._cnt
            .ifl
                push    ecx
                _filbuf(ebx)
                pop ecx
                .if eax == -1

                    .break .if edi != buf

                    xor eax,eax
                    .break(1)
                .endif
            .else
                mov eax,[ebx]._ptr
                add [ebx]._ptr,1
                mov al,[eax]
            .endif
            stosb
            .break .if al == 10
        .endf
        xor eax,eax
        stosb
        or eax,buf
    .until 1
    ret

fgets endp

    END
