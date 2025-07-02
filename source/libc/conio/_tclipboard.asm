; _TCLIPBOARD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

ifdef __UNIX__
include malloc.inc
.data
 clipboard string_t NULL
 clipbsize uint_t 0
else
include winuser.inc
endif
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
endif
    ret

_clipset endp


_clipget proc uses rbx
ifdef __UNIX__
    xor eax,eax
    .if ( eax != clipbsize )
        mov rax,clipboard
    .endif
else
    .if OpenClipboard(0)

        mov rbx,GetClipboardData(CLFLAGS)
        CloseClipboard()
        mov rax,rbx
    .endif
endif
    ret

_clipget endp

    end
