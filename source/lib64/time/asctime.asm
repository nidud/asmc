; ASCTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc

_ASCBUFSIZE equ 26

    .data
    buf char_t _ASCBUFSIZE dup(0)

    .code

store_dt proc private p:string_t, val:int_t

    mov r8d,edx
    mov r9d,10
    mov eax,edx
    xor edx,edx
    div r9d
    mov ah,dl
    add ax,'00'
    mov [rcx],ax
    lea rax,[rcx+2]
    ret

store_dt endp

    assume rsi:ptr tm

asctime proc uses rsi rdi tb:ptr tm

    ; copy day and month names into the buffer

    lea rdi,buf
    mov rsi,rcx

    lea r8,__dnames
    lea r9,__mnames

    imul eax,[rsi].tm_wday,3    ; index to correct day string
    imul edx,[rsi].tm_mon,3     ; index to correct month string

    add r8,rax
    add r9,rdx

    .for ( ecx = 0: ecx < 3 : ecx++ )

        mov al,[r8+rcx]
        stosb
        mov al,[r9+rcx]
        mov [rdi+3],al
    .endf
    mov al,' '
    stosb                       ; blank between day and month
    add rdi,3
    stosb

    mov rdi,store_dt(rdi, [rsi].tm_mday)    ; day of the month (1-31)
    mov al,' '
    stosb
    mov rdi,store_dt(rdi, [rsi].tm_hour);   ; hours (0-23)
    mov al,':'
    stosb
    mov rdi,store_dt(rdi, [rsi].tm_min);    ; minutes (0-59)
    mov al,':'
    stosb
    mov rdi,store_dt(rdi, [rsi].tm_sec);    ; seconds (0-59)
    mov al,' '
    stosb
    mov ecx,100
    xor edx,edx
    mov eax,[rsi].tm_year
    div ecx
    add eax,19
    mov esi,edx
    mov rdi,store_dt(rdi, eax)  ;  year (after 1900)
    mov rdi,store_dt(rdi, esi)
    mov eax,0x0A0D
    stosd
    lea rax,buf
    ret

asctime endp

    end
