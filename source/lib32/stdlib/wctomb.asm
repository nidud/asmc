include stdlib.inc
include winnls.inc
include errno.inc
include setlocal.inc

    .code

wctomb proc s:LPSTR, wchar:wchar_t

local defused

    mov ecx,s
    movzx edx,wchar
    xor eax,eax

    .repeat

        .break .if !ecx ; indicate do not have state-dependent encodings

        .if __lc_handle[LC_CTYPE*4] == _CLOCALEHANDLE

            .if edx > 255 ; validate high byte

                mov errno,EILSEQ
                dec eax
                .break
            .endif
            mov [ecx],dl
            inc eax
            .break
        .endif

        mov defused,0
        .if !WideCharToMultiByte(
                __lc_codepage,
                WC_COMPOSITECHECK or WC_SEPCHARS,
                &wchar,
                1,
                s,
                MB_CUR_MAX,
                NULL,
                &defused) || defused

            mov errno,EILSEQ
            mov eax,-1
        .endif
    .until 1
    ret

wctomb endp

    end

