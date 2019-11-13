; __WSETENVP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc
include malloc.inc
include winbase.inc

    .code

__wsetenvp proc uses esi edi ebx envp:LPSTR

  local base

    ; size up the environment

    .for ( edi = GetEnvironmentStringsW(),
           esi = eax, ; save start of block in ESI
           eax = 0,
           ebx = 0,
           ecx = -1 : ax != [edi] : )

        .if ( word ptr [edi] != '=' )

            mov  edx,edi    ; save offset of string
            sub  edx,esi
            push edx
            inc  ebx        ; increase count
        .endif
        repnz scasw         ; next string..
    .endf

    inc ebx                 ; count strings plus NULL
    sub edi,esi             ; EDI to size
                            ; pointers plus size of environment
    malloc(&[edi+ebx*4])

    mov ecx,envp            ; return result
    mov [ecx],eax
    .return .if !eax
                            ; new adderss of block
    memcpy(&[eax+ebx*4], esi, edi)
    xchg eax,esi            ; ESI to block
    FreeEnvironmentStrings(eax)

    lea edi,[esi-4]     ; EDI to end of pointers array
    std                 ; move backwards
    xor eax,eax         ; set last pointer to NULL
    stosd
    dec ebx
    .whilenz
        pop eax         ; pop offset in reverse
        add eax,esi     ; add address of block
        stosd
        dec ebx
    .endw
    cld
    mov eax,envp        ; return address of new _environ
    mov eax,[eax]
    ret

__wsetenvp endp

    END
