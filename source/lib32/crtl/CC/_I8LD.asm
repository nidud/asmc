; _I8LD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

.code
    ;
    ; SQWORD [eax] to long double[edx]
    ;
_I8LD proc

    push ecx
    xor ecx,ecx
    jmp L8TOLD

_I8LD endp
    ;
    ; QWORD [eax] to long double[edx]
    ;
_U8LD proc

    push ecx
    or ecx,1

_U8LD endp

L8TOLD:

    push ebx
    mov  ebx,edx
    mov  edx,[eax+4]
    mov  eax,[eax]
    test ecx,ecx

    mov ecx,0x403E ; 16446
    .ifz
        test edx,edx
        .ifs
            neg edx
            neg eax
            sbb edx,0
            or  ecx,0xFFFF8000
        .endif
    .endif

    .repeat
        .if !edx
            sub ecx,32
            or  edx,eax
            mov eax,0
            .ifz
                mov ecx,eax
                .break
            .endif
        .endif
        .break .ifs
        .repeat
            dec  ecx
            shld edx,eax,1
            shl  eax,1
        .untils
    .until 1

    mov [ebx],eax
    mov [ebx+4],edx
    mov [ebx+8],cx
    pop ebx
    pop ecx
    ret

    END
