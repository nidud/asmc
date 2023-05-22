; _CLIPBOARDW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_clipsetW proc uses rsi rdi rbx string:LPWSTR, len:UINT

ifndef __UNIX__

    ldr rbx,string
    ldr edx,len
    lea edi,[rdx*wchar_t]

    .if OpenClipboard(0)

        EmptyClipboard()
        add edi,wchar_t

        .if GlobalAlloc(GMEM_MOVEABLE or GMEM_DDESHARE, edi)

            mov rsi,rax
            mov rbx,memcpy(GlobalLock(rax), rbx, edi)
            GlobalUnlock(rsi)
            SetClipboardData(CF_UNICODETEXT, rbx)
        .endif
        CloseClipboard()
    .endif
endif
    ret

_clipsetW endp


_clipgetW proc uses rbx
ifndef __UNIX__
    .if OpenClipboard(0)

        mov rbx,GetClipboardData(CF_UNICODETEXT)
        CloseClipboard()
        mov rax,rbx
    .endif
endif
    ret

_clipgetW endp

    end
