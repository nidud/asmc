; _CLIPBOARDW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_clipsetW proc uses rsi rdi rbx string:LPWSTR, len:UINT

ifndef _WIN64
    mov ecx,string
    mov edx,len
endif
    mov rbx,rcx
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
    ret

_clipsetW endp


_clipgetW proc uses rsi

    .if OpenClipboard(0)

        mov rsi,GetClipboardData(CF_UNICODETEXT)
        CloseClipboard()
        mov rax,rsi
    .endif
    ret

_clipgetW endp

    end
