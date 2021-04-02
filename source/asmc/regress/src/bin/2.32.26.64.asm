
    ; inline 64-bit

    .x64
    .model flat, fastcall

    option casemap:none
    option win64:auto

.template ft

    atom byte ?

    .static a a:byte {
        mov this.atom,a ; cl
        }
    .static b a:byte, b:byte, c:byte, d:byte {
        mov this.atom,a ; cl
        mov this.atom,b ; dl
        mov this.atom,c ; r8b
        mov this.atom,d ; r9b
        }
    .static c a:byte, b:byte, c:byte, d:byte, e:byte, f:byte {
        mov this.atom,a ; cl
        mov this.atom,b ; dl
        mov this.atom,c ; r8b
        mov this.atom,d ; r9b
        mov this.atom,e ; [rsp+4*8]
        mov this.atom,f ; [rsp+5*8]
        }
    .ends

.inline f1 a:ptr {
    add rax,a
    }

.inline f4 a1:dword, a2:dword, a3:dword, a4:dword {
    mov edi,a1
    mov edi,a2
    mov edi,a3
    mov edi,a4
    }

.inline f6 a1:dword, a2:dword, a3:dword, a4:dword, a5:dword, a6:dword {
    mov edi,a1 ; ecx
    mov edi,a2 ; edx
    mov edi,a3 ; r8d
    mov edi,a4 ; r9d
    mov edi,a5 ; [rsp+4*8]
    mov edi,a6 ; [rsp+5*8]
    }

.inline s6 syscall a1:dword, a2:dword, a3:dword, a4:dword, a5:dword, a6:dword {
    mov edi,a1 ; ecx
    mov edi,a2 ; edx
    mov edi,a3 ; r8d
    mov edi,a4 ; r9d
    mov edi,a5 ; [rsp+4*8]
    mov edi,a6 ; [rsp+5*8]
    }

    .code

main proc

  local f:ft


    f1(0)
    f4(0,1,2,3)
    f6(0,1,2,3,4,5)
    s6(0,1,2,3,4,5)

    f.a(0)
    f.b(0,1,2,3)
    f.c(0,1,2,3,4,5)
    ret

main endp

    end
