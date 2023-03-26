; _CLIPBOARDA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_clipsetA proc uses rsi rdi rbx string:LPSTR, len:UINT

    mov rbx,string
    mov edi,len

    .if OpenClipboard(0)

        EmptyClipboard()
        add edi,char_t

        .if GlobalAlloc(GMEM_MOVEABLE or GMEM_DDESHARE, edi)

            mov rsi,rax
            mov rbx,memcpy(GlobalLock(rax), rbx, edi)
            GlobalUnlock(rsi)
            SetClipboardData(CF_TEXT, rbx)
        .endif
        CloseClipboard()
    .endif
    ret

_clipsetA endp


_clipgetA proc uses rsi

    .if OpenClipboard(0)

        mov rsi,GetClipboardData(CF_TEXT)
        CloseClipboard()
        mov rax,rsi
    .endif
    ret

_clipgetA endp

    end
