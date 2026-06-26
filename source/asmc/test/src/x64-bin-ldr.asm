;
; v2.34.33: LDR Directive
;
    .code

f1  proc fastcall a1:ptr, a2:dword, a3:word, a4:byte

    ldr rcx,a1
    ldr edx,a2
    ldr r8w,a3
    ldr r9b,a4

    ldr rax,a1
    ldr eax,a2
    ldr ax,a3
    ldr al,a4
    ret
    endp

f2  proc fastcall a1:ptr, a2:dword, a3:word, a4:byte

  local l1:ptr, l2:dword, l3:word, l4:byte

    ldr l1,a1
    ldr l2,a2
    ldr l3,a3
    ldr l4,a4
    ret
    endp

v1  proc vectorcall a1:ptr, a2:dword, a3:word, a4:byte

    ldr rcx,a1
    ldr edx,a2
    ldr r8w,a3
    ldr r9b,a4

    ldr rax,a1
    ldr eax,a2
    ldr ax,a3
    ldr al,a4
    ret
    endp

v2  proc vectorcall a1:ptr, a2:dword, a3:word, a4:byte

  local l1:ptr, l2:dword, l3:word, l4:byte

    ldr l1,a1
    ldr l2,a2
    ldr l3,a3
    ldr l4,a4
    ret
    endp


s1  proc syscall a1:ptr, a2:dword, a3:word, a4:byte

    ldr rdi,a1
    ldr esi,a2
    ldr dx,a3
    ldr cl,a4

    ldr rax,a1
    ldr eax,a2
    ldr ax,a3
    ldr al,a4
    ret
    endp

s2  proc syscall a1:ptr, a2:dword, a3:word, a4:byte

  local l1:ptr, l2:dword, l3:word, l4:byte

    ldr l1,a1
    ldr l2,a2
    ldr l3,a3
    ldr l4,a4
    ret
    endp

w1  proc watcall a1:ptr, a2:dword, a3:word, a4:byte

    ldr rax,a1
    ldr edx,a2
    ldr bx,a3
    ldr cl,a4

    ldr rax,a1
    ldr eax,a2
    ldr ax,a3
    ldr al,a4
    ret
    endp

    option win64:auto

f3  proc fastcall a1:ptr, a2:dword, a3:word, a4:byte

    ldr rcx,a1
    ldr edx,a2
    ldr r8w,a3
    ldr r9b,a4

    ldr rax,a1
    ldr eax,a2
    ldr ax,a3
    ldr al,a4
    ret
    endp

v3  proc vectorcall a1:ptr, a2:dword, a3:word, a4:byte

    ldr rcx,a1
    ldr edx,a2
    ldr r8w,a3
    ldr r9b,a4

    ldr rax,a1
    ldr eax,a2
    ldr ax,a3
    ldr al,a4
    ret
    endp

s3  proc syscall a1:ptr, a2:dword, a3:word, a4:byte

    ldr rdi,a1
    ldr esi,a2
    ldr dx,a3
    ldr cl,a4

    ldr rax,a1
    ldr eax,a2
    ldr ax,a3
    ldr al,a4
    ret
    endp

w2  proc watcall a1:ptr, a2:dword, a3:word, a4:byte

    ldr rax,a1
    ldr edx,a2
    ldr bx,a3
    ldr cl,a4

    ldr rax,a1
    ldr eax,a2
    ldr ax,a3
    ldr al,a4
    ret
    endp

    end
