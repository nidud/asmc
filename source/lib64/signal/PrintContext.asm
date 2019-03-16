; PRINTCONTEXT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Change history:
; 2018-12-17 - format + "I64"
; 2018-12-17 - assign value <[rdx+8]=rax> (Asmc v2.28.15)
;

include stdio.inc
include signal.inc

    .code

    option win64:nosave

    assume r11:PCONTEXT

PrintContext proc ExcContext:PCONTEXT, ExcRecord:ptr EXCEPTION_RECORD

  local flags[17]:sbyte

    .for ( r8d      = 0,
           r10      = rdx,
           r11      = rcx,
           rdx      = &flags,
           rax      = '00000000',
           [rdx]    = rax,
           [rdx+8]  = rax,
           [rdx+16] = r8b,
           eax      = [r11].EFlags,
           ecx      = 16 : ecx : ecx-- )

        shr eax,1
        adc [rdx+rcx-1],r8b
    .endf

    printf(
        "This message is created due to unrecoverable error\n"
        "and may contain data necessary to locate it.\n"
        "\n"
        "\tException Code: %08X\n"
        "\tException Flags %08X\n"
        "\n"
        "\t  regs: RAX: %016I64X R8:  %016I64X\n"
        "\t\tRBX: %016I64X R9:  %016I64X\n"
        "\t\tRCX: %016I64X R10: %016I64X\n"
        "\t\tRDX: %016I64X R11: %016I64X\n"
        "\t\tRSI: %016I64X R12: %016I64X\n"
        "\t\tRDI: %016I64X R13: %016I64X\n"
        "\t\tRBP: %016I64X R14: %016I64X\n"
        "\t\tRSP: %016I64X R15: %016I64X\n"
        "\t\tRIP: %016I64X\n\n"
        "\t     EFlags: %s\n"
        "\t\t     r n oditsz a p c\n\n",
        [r10].EXCEPTION_RECORD.ExceptionCode,
        [r10].EXCEPTION_RECORD.ExceptionFlags,
        [r11]._Rax, [r11]._R8,
        [r11]._Rbx, [r11]._R9,
        [r11]._Rcx, [r11]._R10,
        [r11]._Rdx, [r11]._R11,
        [r11]._Rsi, [r11]._R12,
        [r11]._Rdi, [r11]._R13,
        [r11]._Rbp, [r11]._R14,
        [r11]._Rsp, [r11]._R15,
        [r11]._Rip, &flags)
    ret

PrintContext endp

    END
