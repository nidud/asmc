    ;
    ; v2.27 - REAL const parameters
    ;
    .x64
    .model flat
    .code

XM_PI equ 3.141592654

XMConvertToRadians macro fDegrees
    retm<fDegrees * (XM_PI / 180.0)>
    endm

    XMConvertToRadians(2.0) ; ignored
    mov rax,XMConvertToRadians(2.0) ; REAL8
    mov eax,XMConvertToRadians(2.0) ; REAL4
    add eax,XMConvertToRadians(2.0) ; REAL4
    add rax,XMConvertToRadians(2.0) ; REAL4

    end
