; _CLIPBOARDA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
ifdef __UNIX__
include malloc.inc

.data
 clipboard string_t NULL
 clipbsize uint_t 0
endif

.code

_clipsetA proc uses rbx string:LPSTR, len:UINT

    ldr rbx,string
    inc len

ifdef __UNIX__

    free(clipboard)

    mov clipbsize,0
    mov clipboard,malloc(len)

    .if ( rax )

        dec len
        memcpy(rax, rbx, len)
        mov ecx,len
        mov byte ptr [rax+rcx],0
        mov clipbsize,ecx
    .endif

else

    .if OpenClipboard(0)

        EmptyClipboard()
        .if GlobalAlloc(GMEM_MOVEABLE or GMEM_DDESHARE, len)

            mov string,rax
            mov rbx,memcpy(GlobalLock(rax), rbx, len)
            GlobalUnlock(string)
            SetClipboardData(CF_TEXT, rbx)
        .endif
        CloseClipboard()
    .endif
endif
    ret

_clipsetA endp


_clipgetA proc uses rbx

ifdef __UNIX__

    xor eax,eax
    .if ( eax != clipbsize )
        mov rax,clipboard
    .endif

else

    .if OpenClipboard(0)

        mov rbx,GetClipboardData(CF_TEXT)
        CloseClipboard()
        mov rax,rbx
    .endif
endif
    ret

_clipgetA endp

    end
