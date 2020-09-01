; TWINPUTSTRING.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include twindow.inc

    .code

    assume rcx:window_t

TWindow::PutString proc x:int_t, y:int_t, at:ushort_t, max:int_t, format:string_t, argptr:vararg

  local w:ptr_t
  local highat:byte
  local attrib:byte
  local buffer[4096]:char_t
  local retval:int_t

    mov eax,r9d
    mov attrib,al
    mov highat,ah

    .if ( eax == 0 && r8d && [rcx].Flags & W_TRANSPARENT )

        mov r9,[rcx].Color
        mov al,[r9+BG_DIALOG]
        or  al,[r9+FG_DIALOG]
        mov attrib,al
        mov al,[r9+BG_DIALOG]
        or  al,[r9+FG_DIALOGKEY]
        mov highat,al
    .endif

    movzx   eax,[rcx].rc.col
    imul    eax,r8d
    add     eax,edx
    lea     rax,[rax*4]
    add     rax,[rcx].Window
    mov     w,rax
    mov     retval,vsprintf(&buffer, format, &argptr)
    mov     rcx,this
    mov     r11d,max

    .if !r11d

        mov r11b,[rcx].rc.col
        sub r11d,x
    .endif

    .for ( rdx = w,
           r8  = &buffer,
           r9d = 0,
           r9b = [rcx].rc.col,
           r9d <<= 2,
           r10 = rdx,
           ah  = attrib,
           al  = [r8] : al, r11d : r8++, al = [r8], r11d-- )

        .if al == 10

            add r10,r9
            mov rdx,r10
            mov r11b,[rcx].rc.col
            sub r11d,x

        .elseif al == 9

            add rdx,4*4
        .elseif al == '&' && highat

            inc r8
            mov al,highat
            mov [rdx+2],al
            mov al,[r8]
            mov [rdx],al
            add rdx,4
        .else
            mov [rdx],al
            .if ah
                mov [rdx+2],ah
            .endif
            add rdx,4
        .endif
    .endf
    mov eax,retval
    ret

TWindow::PutString endp

    end
