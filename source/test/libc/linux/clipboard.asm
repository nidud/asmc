;
; A few things which should work now:
; - string converion from Unicode + surrugate pairs
; - Windows memory and clipboard wrappers
;
; What to expect:
; - signal SIGPIPE (Broken pipe) if [WAYLAND_]DISPLAY defined
;   and clipboard binaries missing (xclip/wl-copy/wl-paste)
; - echo "DISPLAY=$DISPLAY WAYLAND_DISPLAY=$WAYLAND_DISPLAY"
; - in WSL WAYLAND_DISPLAY is defined without binaries
;   the copied text is avilable in Windows and right-click
;   in the Linux terminal, but no luck using the keyboard
;
; Build and debug:
;   asmc64 -MT -Zd clipboard.asm
;   gdb -x layout.gdb clipboard
;

include winuser.inc

.code

 main proc

    .new string:LPWSTR = L"Hello \U1F600 from Linux"
    .new string_size:int_t = sizeof(@CStr(0)) - 2
    .new hMem:HANDLE
    .if OpenClipboard(0)
        EmptyClipboard()
        .if GlobalAlloc(GMEM_MOVEABLE or GMEM_DDESHARE, string_size)
            mov hMem,rax
            mov rbx,memcpy(GlobalLock(rax), string, string_size)
            GlobalUnlock(hMem)
            SetClipboardData(CF_UNICODETEXT, rbx)
        .endif
        CloseClipboard()
    .endif
    .return( 0 )
    endp

    end
