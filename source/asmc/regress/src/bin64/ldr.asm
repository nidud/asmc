;
; v2.34.33: LDR Directive
;
ifndef __ASMC64__
    .x64
    .model flat
endif
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

f1  endp

f2  proc fastcall a1:ptr, a2:dword, a3:word, a4:byte

  local l1:ptr, l2:dword, l3:word, l4:byte

    ldr l1,a1
    ldr l2,a2
    ldr l3,a3
    ldr l4,a4
    ret

f2  endp

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

v1  endp

v2  proc vectorcall a1:ptr, a2:dword, a3:word, a4:byte

  local l1:ptr, l2:dword, l3:word, l4:byte

    ldr l1,a1
    ldr l2,a2
    ldr l3,a3
    ldr l4,a4
    ret

v2  endp


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

s1  endp

s2  proc syscall a1:ptr, a2:dword, a3:word, a4:byte

  local l1:ptr, l2:dword, l3:word, l4:byte

    ldr l1,a1
    ldr l2,a2
    ldr l3,a3
    ldr l4,a4
    ret

s2  endp

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

w1  endp

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

f3  endp

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

v3  endp

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

s3  endp

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

w2  endp

    end
