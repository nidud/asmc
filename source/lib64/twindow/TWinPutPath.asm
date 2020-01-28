; TWINPUTPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include twindow.inc

    .code

    assume rcx:window_t

TWindow::PutPath proc uses rsi rdi rbx x:int_t, y:int_t, max:int_t, path:string_t

  local pre[16]:char_t

    mov rsi,path
    mov ebx,r9d

    .ifd strlen(rsi) > ebx
        lea rcx,pre
        mov edx,[rsi]
        add rsi,rax
        sub rsi,rbx
        mov eax,4
        .if dh == ':'
            mov [rcx],dx
            shr edx,8
            mov dl,'.'
            add rcx,2
            add eax,2
        .else
            mov dx,'/.'
        .endif
        add rsi,rax
        sub ebx,eax
        mov [rcx],dh
        mov [rcx+1],dl
        mov [rcx+2],dx
        mov byte ptr [rcx+4],0
        mov rcx,this
        mov edx,x
        add x,eax
        [rcx].PutString(x, y, 0, 6, &pre)
    .endif
    mov rcx,this
    [rcx].PutString(x, y, 0, ebx, rsi)
    ret

TWindow::PutPath endp

    end
