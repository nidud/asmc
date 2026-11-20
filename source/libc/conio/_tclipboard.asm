; _TCLIPBOARD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include winuser.inc
include conio.inc

ifdef _UNICODE
define CLFLAGS CF_UNICODETEXT
else
define CLFLAGS CF_TEXT
endif

.code

_clipset proc uses rbx string:tstring_t, len:uint_t

    ldr rbx,string
    inc len
    .if OpenClipboard(0)
        EmptyClipboard()
ifdef _UNICODE
        shl len,1
endif
        .if GlobalAlloc(GMEM_MOVEABLE or GMEM_DDESHARE, len)
            mov string,rax
            mov rbx,memcpy(GlobalLock(rax), rbx, len)
            GlobalUnlock(string)
            SetClipboardData(CLFLAGS, rbx)
        .endif
        CloseClipboard()
    .endif
    ret
    endp


_clipget proc uses rbx
    .if OpenClipboard(0)
        mov rbx,GetClipboardData(CLFLAGS)
        CloseClipboard()
        mov rax,rbx
    .endif
    ret
    endp

    end
