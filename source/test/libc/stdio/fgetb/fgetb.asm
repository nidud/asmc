; FGETB.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc
include tchar.inc

.code

_tmain proc argc:int_t, argv:array_t

    .new fp:LPFILE = fopen(__FILE__, "rb")
    .new fo:LPFILE = _fopent()
    .new fb:LPFILE = fopen("out.txt", "wb")

    .whiled ( _fgetb(fp, 1) != -1 )

        _fputb(fo, eax, 1)
    .endw
    _fflushb(fo)
    fclose(fp)

    mov rcx,fo
    mov rax,[rcx].FILE._ptr
    mov rdx,[rcx].FILE._base
    sub rax,rdx
    mov [rcx].FILE._cnt,eax
    mov [rcx].FILE._ptr,rdx

    .whiled ( _fgetb(fo, 1) != -1 )

        _fputb(fb, eax, 1)
    .endw
    _fflushb(fb)
    fclose(fb)
    fclose(fo)

   .return( 0 )

_tmain endp

    end
