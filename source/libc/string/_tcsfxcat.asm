; _TCSFXCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *strfxcat(char *, char *);
; wchar_t *_wstrfxcat(wchar_t *, wchar_t *);
;
include string.inc
include tchar.inc

.code

_tcsfxcat proc path:tstring_t, ext:tstring_t

    .if _tcsext(path)

        mov tchar_t ptr [rax],0
    .endif
    _tcscat(path, ext)
    ret

_tcsfxcat endp

    end
