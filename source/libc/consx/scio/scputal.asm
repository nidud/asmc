include consx.inc
include string.inc

    .code

scputal proc uses esi edx ecx eax x, y, l, lpAttribute:PVOID

  local NumberOfAttrsWritten
  local Attribute[TIMAXSCRLINE]:word

    movzx ecx,byte ptr l
    xor eax,eax
    lea edx,Attribute
    mov esi,lpAttribute

    .repeat
        mov al,[esi]
        mov [edx],ax
        add edx,2
        inc esi
    .untilcxz

    movzx eax,byte ptr x
    movzx edx,byte ptr y

    .repeat

        .if edx <= _scrrow

            shl   edx,16
            add   edx,eax
            movzx ecx,byte ptr l
            add   eax,ecx

            .if eax > _scrcol
                sub eax,ecx
                mov ecx,_scrcol
                sub ecx,eax
                .break .ifng
            .endif

            WriteConsoleOutputAttribute(
                hStdOutput,
                &Attribute,
                ecx,
                edx,
                &NumberOfAttrsWritten)
        .endif
    .until 1
    ret

scputal endp

    END
