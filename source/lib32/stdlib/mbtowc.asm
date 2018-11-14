; MBTOWC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include ctype.inc
include winnls.inc
include errno.inc
include locale.inc
include setlocal.inc
include crtl.inc

extern __invalid_mb_chars:SINT

    .code

mbtowc proc pwc:LPWSTR, s:LPSTR, n:SIZE_T

    .assert MB_CUR_MAX == 1 || MB_CUR_MAX == 2

    .repeat
        mov eax,s
        .if !eax || n == 0
            ;
            ; indicate do not have state-dependent encodings,
            ; handle zero length string
            ;
            xor eax,eax
            .break
        .endif

        mov ecx,pwc
        .if !(byte ptr [eax])
            ;
            ; handle NULL char
            ;
            xor eax,eax
            .if ecx

                mov [ecx],ax
            .endif
            .break
        .endif

        .if __lc_handle[LC_CTYPE*4] == _CLOCALEHANDLE

            .if ecx

                movzx eax,BYTE PTR [eax]
                mov   [ecx],ax
            .endif
            mov eax,1
            .break
        .endif

        movzx eax,BYTE PTR [eax]
        .if isleadbyte(eax)

            ; multi-byte char

            mov eax,MB_PRECOMPOSED
            or  eax,__invalid_mb_chars
            xor ecx,ecx
            .if ecx != pwc
                inc ecx
            .endif
            MultiByteToWideChar(__lc_codepage, eax, s, MB_CUR_MAX, pwc, ecx)

            mov ecx,MB_CUR_MAX
            .if ecx <= 1 || n < ecx || !eax

                mov errno,EILSEQ
                mov eax,-1
                .break
            .endif
            mov eax,MB_CUR_MAX

        .else
            ; single byte char
            mov eax,MB_PRECOMPOSED
            or  eax,__invalid_mb_chars
            xor ecx,ecx
            .if ecx != pwc
                inc ecx
            .endif

            .if !MultiByteToWideChar(__lc_codepage, eax, s, 1, pwc, ecx)

                mov errno,EILSEQ
                mov eax,-1
                .break
            .endif
        .endif
        mov eax,1
    .until 1
    ret

mbtowc endp

    end
