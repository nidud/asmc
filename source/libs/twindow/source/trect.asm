; TRECT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include twindow.inc

    .code

    assume rcx:trect_t

TRect::Read proc uses rsi rdi rbx h:HANDLE, pc:PCHAR_INFO

  local co:COORD, rc:SMALL_RECT

    mov rsi,r8
    mov rdi,rdx

    mov co,[rcx].Coord()
    mov rc,[rcx].SmallRect()

    .return .ifd ReadConsoleOutput(rdi, rsi, co, 0, &rc)

    movzx ebx,co.y
    mov   rc.Bottom,rc.Top
    mov   co.y,1

    .for ( : ebx : ebx--, rc.Bottom++, rc.Top++ )

        .break .ifd !ReadConsoleOutput(rdi, rsi, co, 0, &rc)

        movzx ecx,co.x
        shl   ecx,2
        add   rsi,rcx
    .endf
    ret

TRect::Read endp

TRect::Write proc uses rsi rdi rbx h:HANDLE, pc:PCHAR_INFO

  local co:COORD, rc:SMALL_RECT

    mov rsi,r8
    mov rdi,rdx

    mov co,[rcx].TRect.Coord()
    mov rc,[rcx].TRect.SmallRect()

    .return .ifd WriteConsoleOutput(rdi, rsi, co, 0, &rc)

    movzx ebx,co.y
    mov   rc.Bottom,rc.Top
    mov   co.y,1

    .for ( : ebx : ebx--, rc.Bottom++, rc.Top++ )

        .break .ifd !WriteConsoleOutput(rdi, rsi, co, 0, &rc)

        movzx ecx,co.x
        shl   ecx,2
        add   rsi,rcx
    .endf
    ret

TRect::Write endp

TRect::Exchange proc uses rsi rdi rbx h:HANDLE, pc:PCHAR_INFO

    mov     rdi,r8
    movzx   eax,[rcx].row
    movzx   ecx,[rcx].col
    mul     ecx
    mov     ebx,eax
    shl     eax,2
    mov     rsi,alloca(eax)

    .if TRect::Read(this, h, rsi)
        TRect::Write(this, h, rdi)
        mov ecx,ebx
        rep movsd
    .endif
    ret

TRect::Exchange endp

    end
