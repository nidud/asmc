
    ; inline 32-bit

    .486
    .model flat, c

.template wt watcall

    atom byte ?

    .static a a:byte {
        mov this.atom,a ; al
        }
    .static b a:byte, b:byte, c:byte, d:byte {
        mov this.atom,a ; al
        mov this.atom,b ; dl
        mov this.atom,c ; bl
        mov this.atom,d ; cl
        }
    .ends

.template ft fastcall

    atom byte ?

    .static a a:byte {
        mov this.atom,a ; cl
        }
    .static b a:byte, b:byte, c:byte, d:byte {
        mov this.atom,a ; cl
        mov this.atom,b ; dl
        mov this.atom,c ; [esp+0*4]
        mov this.atom,d ; [esp+1*4]
        ;   add esp, 8
        }
    .ends

.inline w1 watcall a:ptr {
    add eax,a
    }

.inline w4 watcall a1:dword, a2:dword, a3:dword, a4:dword {
    mov edi,a1
    mov edi,a2
    mov edi,a3
    mov edi,a4
    }

.inline w6 watcall a1:dword, a2:dword, a3:dword, a4:dword, a5:dword, a6:dword {
    mov edi,a1 ; eax
    mov edi,a2 ; edx
    mov edi,a3 ; ebx
    mov edi,a4 ; ecx
    mov edi,a5 ; [esp+0*4]
    mov edi,a6 ; [esp+1*4]
;   add esp, 8
    }

.inline wa watcall a1:abs, a2:abs, a3:abs, a4:abs, a5:abs, a6:abs {
    mov edi,a1 ; 0
    mov edi,a2 ; 1
    mov edi,a3 ; 2
    mov edi,a4 ; 3
    mov edi,a5 ; 4
    mov edi,a6 ; 5
    }

.inline fa watcall a1:abs, a2:abs, a3:abs, a4:abs, a5:abs, a6:abs {
    mov edi,a1 ; 0
    mov edi,a2 ; 1
    mov edi,a3 ; 2
    mov edi,a4 ; 3
    mov edi,a5 ; 4
    mov edi,a6 ; 5
    }

.inline f1 fastcall a:ptr {
    add eax,a
    }

.inline f4 fastcall a1:dword, a2:dword, a3:dword, a4:dword {
    mov edi,a1 ; ecx
    mov edi,a2 ; edx
    mov edi,a3 ; [esp+0*4]
    mov edi,a4 ; [esp+1*4]
;   add esp, 8
    }

    .code

main proc

  local w:wt
  local f:ft

    w1(0)
    w4(0,1,2,3)
    w6(0,1,2,3,4,5)
    wa(0,1,2,3,4,5)

    f1(0)
    f4(0,1,2,3)
    fa(0,1,2,3,4,5)

    w.a(0)
    w.b(0,1,2,3)
    f.a(0)
    f.b(0,1,2,3)
    ret

main endp

    end
