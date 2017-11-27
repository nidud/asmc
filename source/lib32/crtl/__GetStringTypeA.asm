include ctype.inc
include stdlib.inc
include setlocal.inc
include malloc.inc
include winnls.inc

    .code

USE_W equ 1
USE_A equ 2

__GetStringTypeA proc dwInfoType:dword, lpSrcStr:LPTSTR, cchSrc:SINT, lpCharType:LPWORD,
    code_page:SINT, lcid:SINT, bError:UINT

  local dummy, retval, buff_size, wbuffer

    .data

    f_use   db 0
    .code

    .repeat
        ;
        ; Look for unstubbed 'preferred' flavor. Otherwise use available
        ; flavor. Must actually call the function to ensure it's not a stub.
        ; (Always try wide version first so WinNT can process codepage correctly.)
        ;
        .if f_use == 0

            .if GetStringTypeW(CT_CTYPE1, "\0", 1, &dummy)

                mov f_use,USE_W

            .elseif GetStringTypeA(0, CT_CTYPE1, "\0", 1, &dummy)

                mov f_use,USE_A

            .else
                xor eax,eax
                .break
            .endif
        .endif
        ;
        ; Use "A" version
        ;
        .if f_use == USE_A

            .if lcid == 0

                mov eax,__lc_handle[LC_CTYPE*4]
                mov lcid,eax
            .endif

            GetStringTypeA(lcid, dwInfoType, lpSrcStr, cchSrc, lpCharType)
            .break

        .endif
        ;
        ; Use "W" version
        ;
        .if f_use == USE_W
            ;
            ; Convert string and return the requested information. Note that
            ; we are converting to a wide character string so there is not a
            ; one-to-one correspondence between number of multibyte chars in the
            ; input string and the number of wide chars in the buffer. However,
            ; there had *better be* a one-to-one correspondence between the
            ; number of multibyte characters and the number of WORDs in the
            ; return buffer.
            ;
            ; Use __lc_codepage for conversion if code_page not specified
            ;
            .if !code_page

                mov eax,__lc_codepage
                mov code_page,eax
            .endif
            ;
            ; find out how big a buffer we need
            ;
            mov ecx,MB_PRECOMPOSED
            .if bError

                mov ecx,MB_PRECOMPOSED or MB_ERR_INVALID_CHARS
            .endif

            .break .if !MultiByteToWideChar(code_page, ecx, lpSrcStr, cchSrc, NULL, 0)
            mov buff_size,eax
            ;
            ; allocate enough space for wide chars
            ;
            add eax,eax
            mov wbuffer,alloca(eax)
            mov ecx,buff_size
            add ecx,ecx
            memset(eax,  0, ecx)
            ;
            ; do the conversion
            ;
            .break .if !MultiByteToWideChar(
                            code_page,
                            MB_PRECOMPOSED,
                            lpSrcStr,
                            cchSrc,
                            wbuffer,
                            buff_size)
            ;
            ; obtain result
            ;
            GetStringTypeW(dwInfoType, wbuffer, eax, lpCharType)
        .else
            ;
            ; f_use is neither USE_A nor USE_W
            ;
            xor eax,eax
        .endif
    .until 1
    ret

__GetStringTypeA endp

    END
