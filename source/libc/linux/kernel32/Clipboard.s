; CLIPBOARD.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include winuser.inc
include winbase.inc
include winnls.inc
include stdio.inc
include stdlib.inc
include string.inc

define MAX_CLIP_FORMATS 16

CLIP_ENTRY  struct
uFormat     UINT ?
hMem        HANDLE ?
CLIP_ENTRY  ends

.data
 clip_opened   BOOL FALSE
 clip_dirty    BOOL FALSE
 clip_owner    HWND NULL
 clip_entries  CLIP_ENTRY MAX_CLIP_FORMATS dup(<0, NULL>)

.code

__GetClipWriteCmd proc private
    .if ( getenv("WAYLAND_DISPLAY") )
        .return( "wl-copy 2>/dev/null" )
    .endif
    .if ( getenv("DISPLAY") )
        .return( "xclip -selection clipboard 2>/dev/null" )
    .endif
if 0
    .if ( getenv("WSL_DISTRO_NAME") )
        .return( "clip.exe 2>/dev/null" )
    .endif
endif
    .return( NULL )
    endp

__GetClipReadCmd proc private
    .if ( getenv("WAYLAND_DISPLAY") )
        .return( "wl-paste -n 2>/dev/null" )
    .endif
    .if ( getenv("DISPLAY") )
        .return( "xclip -o -selection clipboard 2>/dev/null" )
    .endif
if 0
    .if ( getenv("WSL_DISTRO_NAME") )
        .return( "powershell.exe -NoProfile -Command Get-Clipboard 2>/dev/null" )
    .endif
endif
    .return( NULL )
    endp

OpenClipboard proc WINAPI hWndNewOwner:HWND
    .if ( clip_opened )
        .return( FALSE )
    .endif
    ldr rcx,hWndNewOwner
    mov clip_owner,rcx
    mov clip_opened,TRUE
    mov clip_dirty,FALSE
    .return( TRUE )
    endp

EmptyClipboard proc WINAPI uses rbx
    .new i:int_t
    .if ( !clip_opened )
        .return( FALSE )
    .endif
    .for ( i = 0, rbx = &clip_entries : i < MAX_CLIP_FORMATS : i++, rbx += CLIP_ENTRY )
        .if ( [rbx].CLIP_ENTRY.hMem )
            GlobalFree([rbx].CLIP_ENTRY.hMem)
            mov [rbx].CLIP_ENTRY.hMem,NULL
        .endif
        mov [rbx].CLIP_ENTRY.uFormat,0
    .endf
    mov eax,TRUE
    mov clip_dirty,eax
    ret
    endp


SetClipboardData proc WINAPI  uses rbx uFormat:UINT, hMem:HANDLE
    .new i:int_t
    .if ( !clip_opened || !ldr(hMem) )
        .return( NULL )
    .endif
    .for ( i = 0, rbx = &clip_entries : i < MAX_CLIP_FORMATS : i++, rbx += CLIP_ENTRY )
        mov eax,[rbx].CLIP_ENTRY.uFormat
        .if ( eax == uFormat || [rbx].CLIP_ENTRY.hMem == NULL )
            .if ( [rbx].CLIP_ENTRY.hMem && [rbx].CLIP_ENTRY.hMem != hMem )
                GlobalFree([rbx].CLIP_ENTRY.hMem)
            .endif
            mov [rbx].CLIP_ENTRY.uFormat,uFormat
            mov [rbx].CLIP_ENTRY.hMem,hMem
            mov clip_dirty,TRUE
           .return( rax )
        .endif
    .endf
    .return( NULL )
    endp


GetClipboardData proc WINAPI uses rsi rdi rbx uFormat:UINT
    .new i:int_t
    .new cmd:LPSTR
    .new fp:ptr FILE
    .new raw_buf:LPSTR
    .new raw_len:size_t
    .new cap:size_t
    .new hGlobal:HGLOBAL
    .if ( !clip_opened )
        .return( NULL )
    .endif
    .for ( i = 0, rbx = &clip_entries : i < MAX_CLIP_FORMATS : i++, rbx += CLIP_ENTRY )
        mov eax,[rbx].CLIP_ENTRY.uFormat
        .if ( eax == uFormat && [rbx].CLIP_ENTRY.hMem != NULL )
            .return( [rbx].CLIP_ENTRY.hMem )
        .endif
    .endf
    mov eax,uFormat
    .if ( eax != CF_TEXT && eax != CF_OEMTEXT && eax != CF_UNICODETEXT )
        .return( NULL )
    .endif
    mov cmd,__GetClipReadCmd()
    .if ( !rax )
        .return( NULL )
    .endif
    mov fp,popen(cmd, "r")
    .if ( !rax )
        .return( NULL )
    .endif
    mov cap,4096
    mov raw_len,0
    mov raw_buf,malloc(cap)
    .if ( !rax )
        pclose(fp)
       .return( NULL )
    .endif
    .while ( 1 )
        mov rdx,cap
        sub rdx,raw_len
        .if ( rdx <= 2 )
            shl cap,1
            mov raw_buf,realloc(raw_buf, cap)
            .if ( !rax )
                pclose(fp)
               .return( NULL )
            .endif
            mov rdx,cap
            sub rdx,raw_len
        .endif
        dec rdx
        mov rdi,raw_buf
        add rdi,raw_len
        fread(rdi, 1, rdx, fp)
        .break .if ( !rax )
        add raw_len,rax
    .endw
    pclose(fp)
    mov rdi,raw_buf
    mov rax,raw_len
    mov byte ptr [rdi+rax],0
    .if ( uFormat == CF_UNICODETEXT )
        mov ebx,MultiByteToWideChar(CP_UTF8, 0, raw_buf, -1, NULL, 0)
        .ifs ( ebx <= 0 )
            free(raw_buf)
            .return( NULL )
        .endif
        lea eax,[rbx*2]
        mov hGlobal,GlobalAlloc(GMEM_MOVEABLE or GMEM_ZEROINIT, rax)
        .if ( rax )
            mov rdi,GlobalLock(hGlobal)
            MultiByteToWideChar(CP_UTF8, 0, raw_buf, -1, rdi, ebx)
            GlobalUnlock(hGlobal)
        .endif
    .else
        mov rax,raw_len
        inc rax
        mov hGlobal,GlobalAlloc(GMEM_MOVEABLE or GMEM_ZEROINIT, rax)
        .if ( rax )
            mov rdi,GlobalLock(hGlobal)
            mov rcx,raw_len
            inc rcx
            memcpy(rdi, raw_buf, rcx)
            GlobalUnlock(hGlobal)
        .endif
    .endif
    free(raw_buf)
    .if ( hGlobal )
        SetClipboardData(uFormat, hGlobal)
        mov clip_dirty,FALSE
    .endif
    .return( hGlobal )
    endp


CloseClipboard proc WINAPI uses rsi rdi rbx
    .new i:int_t
    .new cmd:LPSTR
    .new fp:ptr FILE
    .new hUni:HANDLE
    .new hTxt:HANDLE
    .new utf8_buf:LPSTR
    .new utf8_len:int_t
    .if ( !clip_opened )
        .return( FALSE )
    .endif
    .if ( clip_dirty )
        mov cmd,__GetClipWriteCmd()
        .if ( rax )
            mov hUni,NULL
            mov hTxt,NULL
            .for ( i = 0, rbx = &clip_entries : i < MAX_CLIP_FORMATS : i++, rbx += CLIP_ENTRY )
                mov eax,[rbx].CLIP_ENTRY.uFormat
                .if ( eax == CF_UNICODETEXT )
                    mov hUni,[rbx].CLIP_ENTRY.hMem
                .elseif ( eax == CF_TEXT || eax == CF_OEMTEXT )
                    mov hTxt,[rbx].CLIP_ENTRY.hMem
                .endif
            .endf
            .if ( hUni )
                mov rbx,GlobalLock(hUni)
                .if ( rax )
                    mov utf8_len,WideCharToMultiByte(CP_UTF8, 0, rbx, -1, NULL, 0, NULL, NULL)
                    .if ( eax > 1 )
                        mov utf8_buf,malloc(utf8_len)
                        .if ( rax )
                            WideCharToMultiByte(CP_UTF8, 0, rbx, -1, utf8_buf, utf8_len, NULL, NULL)
                            mov fp,popen(cmd, "w")
                            .if ( rax )
                                mov eax,utf8_len
                                dec eax
                                fwrite(utf8_buf, 1, rax, fp)
                                pclose(fp)
                            .endif
                            free(utf8_buf)
                        .endif
                    .endif
                    GlobalUnlock(hUni)
                .endif
            .elseif ( hTxt )
                mov rbx,GlobalLock(hTxt)
                .if ( rax )
                    mov fp,popen(cmd, "w")
                    .if ( rax )
                        strlen(rbx)
                        fwrite(rbx, 1, rax, fp)
                        pclose(fp)
                    .endif
                    GlobalUnlock(hTxt)
                .endif
            .endif
        .endif
    .endif
    mov clip_opened,FALSE
    mov clip_dirty,FALSE
    .return( TRUE )
    endp

    end
