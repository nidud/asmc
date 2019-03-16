; PRINTCONTEXT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include signal.inc

    .data

format label byte
    db 10
    db "CONTEXT:",10
    db 9, "Exception Code: %08X", 10
    db 9, "Exception Flags %08X", 10
    db 10, 9
    db 9,   'EAX: %08X EDX: %08X',10
    db 9,9, 'EBX: %08X ECX: %08X',10
    db 9,9, 'EIP: %08X ESI: %08X',10
    db 9,9, 'EBP: %08X EDI: %08X',10
    db 9,9, 'ESP: %08X',10
    db 10
    db 9,'Flags:  '
bits label byte
    db '0000000000000000',10
    db 9,'        r n oditsz a p c',10
    db 10,0

    .code

PrintContext proc ExcContext:PCONTEXT, ExcRecord:ptr EXCEPTION_RECORD

    mov eax,30303030h
    lea edx,bits
    mov [edx],eax
    mov [edx+4],eax
    mov [edx+8],eax
    mov [edx+12],eax

    mov eax,ExcContext
    assume eax:PCONTEXT

    mov eax,[eax].EFlags
    mov ecx,16
    .repeat
        shr eax,1
        adc byte ptr [edx+ecx-1],0
    .untilcxz

    mov eax,ExcContext
    mov ecx,ExcRecord
    printf(
        &format,
        [ecx].EXCEPTION_RECORD.ExceptionCode,
        [ecx].EXCEPTION_RECORD.ExceptionFlags,
        [eax]._Eax,
        [eax]._Edx,
        [eax]._Ebx,
        [eax]._Ecx,
        [eax]._Eip,
        [eax]._Esi,
        [eax]._Ebp,
        [eax]._Edi,
        [eax]._Esp)
    ret

PrintContext endp

    END
