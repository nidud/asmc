; _SCMOVER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

    .code

_scmover proc uses rsi rdi rbx r12 rc:TRECT, p:PCHAR_INFO

  local x,y,l
  local ci: CONSOLE_SCREEN_BUFFER_INFO

    mov edi,80
    .if GetConsoleScreenBufferInfo(hStdOutput, &ci)

        movzx edi,ci.dwSize.x
    .endif

    movzx   ecx,rc.x
    movzx   edx,rc.col
    mov     esi,ecx
    add     ecx,edx
    mov     eax,rc
    .return .if edi <= ecx

    mov     edi,ecx
    mov     x,esi
    mov     cl,rc.y
    mov     y,ecx
    mov     cl,rc.row
    mov     eax,ecx
    not     ecx
    mov     l,ecx
    mul     rc.col
    shl     eax,2

    .if malloc(eax)

        mov rbx,rax
        _scread(rc, rax)
        mov r12,_screadl(edi, y, l)
        inc rc.x
        _scwrite(rc, rbx)
        free(rbx)

        movzx   ebx,rc.col
        dec     ebx
        movzx   edx,rc.row
        mov     rsi,p
        mov     rdi,r12

        .repeat
            mov eax,[rsi]
            mov r8d,[rdi]
            mov [rdi],eax
            mov ecx,ebx
            mov r9,rdi
            mov rdi,rsi
            add rsi,4
            rep movsd
            mov rdi,r9
            mov [rsi-4],r8d
            add rdi,4
            dec edx
        .until !edx
        _scwritel(x, y, l, r12)
    .endif
    mov eax,rc
    ret

_scmover endp

    end
