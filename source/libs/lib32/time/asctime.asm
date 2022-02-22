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

    mov ecx,10
    mov eax,val
    xor edx,edx
    div ecx
    mov ah,dl
    add ax,'00'
    mov ecx,p
    mov [ecx],ax
    lea eax,[ecx+2]
    ret

store_dt endp

    assume esi:ptr tm

asctime proc uses esi edi ebx tb:ptr tm

    ; copy day and month names into the buffer

    lea edi,buf
    mov esi,tb

    imul eax,[esi].tm_wday,3    ; index to correct day string
    imul edx,[esi].tm_mon,3     ; index to correct month string

    lea ebx,__dnames
    lea esi,__mnames

    add ebx,eax
    add esi,edx

    .for ( ecx = 0: ecx < 3 : ecx++ )

        mov al,[ebx+ecx]
        stosb
        mov al,[esi+ecx]
        mov [edi+3],al
    .endf
    mov al,' '
    stosb                       ; blank between day and month
    add edi,3
    stosb

    mov esi,tb
    mov edi,store_dt(edi, [esi].tm_mday)    ; day of the month (1-31)
    mov al,' '
    stosb
    mov edi,store_dt(edi, [esi].tm_hour);   ; hours (0-23)
    mov al,':'
    stosb
    mov edi,store_dt(edi, [esi].tm_min);    ; minutes (0-59)
    mov al,':'
    stosb
    mov edi,store_dt(edi, [esi].tm_sec);    ; seconds (0-59)
    mov al,' '
    stosb
    mov ecx,100
    xor edx,edx
    mov eax,[esi].tm_year
    div ecx
    add eax,19
    mov esi,edx
    mov edi,store_dt(edi, eax)  ;  year (after 1900)
    mov edi,store_dt(edi, esi)
    mov eax,0x0A0D
    stosd
    lea eax,buf
    ret

asctime endp

    end
