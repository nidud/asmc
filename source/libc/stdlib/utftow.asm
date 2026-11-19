; _UTFTOW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Convert UTF8 to Wide char
;
; Input:  utf (string_t)    = pointer to UTF-8 sequence
;         cbMultiByte (int) = remaining bytes in buffer, or -1 if NUL-terminated
; Output: eax = 16-bit wchar_t (upper 16 bits 0), OR
;               32-bit packed (LowSurrogate << 16) | HighSurrogate (for U+10000..U+10FFFF)
;         ecx = UTF-8 bytes consumed (1..4)
;

include stdlib.inc

.code

_utftow proc uses rbx utf:string_t, cbMultiByte:int_t

    ldr rdx,utf
    ldr ebx,cbMultiByte
    movzx eax,byte ptr [rdx]

    .if ( eax > 0xBF && eax < 0xF5 )
        .if ( eax < 0xE0 )
            ;
            ; 2-byte UTF-8 sequence (requires 2 bytes)
            ;
            .if ( ebx == -1 || ebx >= 2 )
                movzx ecx,byte ptr [rdx+1]
                .if ( cl != 0 )
                    and eax,0x1F
                    shl eax,6
                    and ecx,0x3F
                    or  eax,ecx
                    mov ecx,2
                   .return
                .endif
            .endif
        .elseif ( eax < 0xF0 )
            ;
            ; 3-byte UTF-8 sequence (requires 3 bytes)
            ;
            .if ( ebx == -1 || ebx >= 3 )
                movzx ecx,byte ptr [rdx+1]
                movzx edx,byte ptr [rdx+2]
                .if ( cl != 0 && dl != 0 )
                    and eax,0x0F
                    shl eax,12
                    and ecx,0x3F
                    shl ecx,6
                    or  eax,ecx
                    and edx,0x3F
                    or  eax,edx
                    mov ecx,3
                   .return
                .endif
            .endif
        .else
            ;
            ; 4-byte UTF-8 sequence (0xF0..0xF4, requires 4 bytes)
            ;
            .if ( ebx == -1 || ebx >= 4 )
                movzx ecx,byte ptr [rdx+1]
                .if ( cl != 0 && byte ptr [rdx+2] != 0 && byte ptr [rdx+3] != 0 )
                    and eax,0x07
                    shl eax,18
                    and ecx,0x3F
                    shl ecx,12
                    or  eax,ecx
                    movzx ecx,byte ptr [rdx+2]
                    and ecx,0x3F
                    shl ecx,6
                    or  eax,ecx
                    movzx ecx,byte ptr [rdx+3]
                    and ecx,0x3F
                    or  eax,ecx
                    .if ( eax >= 0x10000 )
                        sub eax,0x10000
                        mov ecx,eax
                        shr ecx,10
                        add ecx,0xD800      ; High surrogate (low word)
                        and eax,0x3FF
                        add eax,0xDC00      ; Low surrogate (high word)
                        shl eax,16
                        or  eax,ecx
                    .endif
                    mov ecx,4
                   .return
                .endif
            .endif
        .endif
    .endif
    ;
    ; Fallback for ASCII (< 0x80) or truncated/invalid lead byte
    ;
    and eax,0x7F
    mov ecx,1
    ret
    endp

    end
