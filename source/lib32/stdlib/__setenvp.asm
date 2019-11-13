; __SETENVP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc
include malloc.inc
include winbase.inc

    .code

__setenvp proc uses esi edi ebx envp:LPSTR

  local base

    ; size up the environment

    .for ( edi = GetEnvironmentStringsA(),
           esi = eax, ; save start of block in ESI
           eax = 0,
           ebx = 0,
           ecx = -1 : al != [edi] : )

        .if ( byte ptr [edi] != '=' )

            mov  edx,edi    ; save offset of string
            sub  edx,esi
            push edx
            inc  ebx        ; increase count
        .endif
        repnz scasb         ; next string..
    .endf


    inc ebx                 ; count strings plus NULL
    sub edi,esi             ; EDI to size
    malloc(&[edi+ebx*4])    ; pointers plus size of environment

    mov ecx,envp            ; return result
    mov [ecx],eax
    .return .if !eax
                            ; new adderss of block
    memcpy(&[eax+ebx*4], esi, edi)
    xchg eax,esi            ; ESI to block
    FreeEnvironmentStrings(eax)

    lea edi,[esi-4]         ; EDI to end of pointers array
    xor eax,eax             ; set last pointer to NULL
    std                     ; move backwards
    stosd
    dec ebx
    .whilenz
        pop eax             ; pop offset in reverse
        add eax,esi         ; add address of block
        stosd
        dec ebx
    .endw
    cld
    mov eax,envp            ; return address of new _environ
    mov eax,[eax]
    ret

__setenvp endp

    END
