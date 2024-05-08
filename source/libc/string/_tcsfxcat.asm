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

_tcsfxcat proc path:LPTSTR, ext:LPTSTR

    .if _tcsext(path)

        mov TCHAR ptr [rax],0
    .endif
    _tcscat(path, ext)
    ret

_tcsfxcat endp

    end
