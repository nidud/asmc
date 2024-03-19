; _TDSORT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include stdlib.inc
include direct.inc
include tchar.inc

    .data
     sortflag dd 0

    .code

    option dotname

compare proc private uses rsi rdi rbx a:PFBLK, b:PFBLK

   .new name_a:LPTSTR
   .new name_b:LPTSTR

    ldr rax,b
    mov rsi,[rax]
    mov edx,[rsi].FBLK.attrib
    mov rbx,[rsi].FBLK.name
    mov name_b,rbx

    ldr rax,a
    mov rdi,[rax]
    mov ecx,[rdi].FBLK.attrib
    mov rbx,[rdi].FBLK.name
    mov name_a,rbx
    test ecx,_F_SUBDIR
    jz  .0
    mov eax,'.'
    cmp [rbx],_tal
    jne .0
    cmp [rbx+TCHAR],_tal
    jne .0
    xor eax,eax
    cmp [rbx+TCHAR*2],_tal
    je  .9
.0:
    mov eax,ecx
    and edx,_F_SUBDIR
    and eax,_F_SUBDIR
    mov ecx,sortflag
    jz  .1
    test edx,edx
    jz  .1
    test ecx,_D_SORTSUB
    jnz .2
    mov ecx,_D_SORTNAME
    jmp .3
.1:
    or  eax,edx
    jz  .2
    mov ecx,_D_SORTSUB
    jmp .3
.2:
    and ecx,_D_SORTSIZE or _D_SORTTYPE or _D_SORTDATE
.3:
    cmp ecx,_D_SORTTYPE
    je  .4
    cmp ecx,_D_SORTDATE
    je  .6
    cmp ecx,_D_SORTSIZE
    je  .7
    cmp ecx,_D_SORTSUB
    je  .8
    jmp .N
.4:
    mov rbx,_tstrext(name_b)
    and rax,_tstrext(name_a)
    jz  .5
    and rbx,rbx
    jz  .A
ifdef __UNIX__
    and eax,_tcscmp(rax, rbx)
else
    and eax,_tcsicmp(rax, rbx)
endif
    jz  .N
    jmp .C
.5:
    and rbx,rbx
    jnz .9
    jmp .N
.6:
    mov ecx,[rdi].FBLK.time
    cmp ecx,[rsi].FBLK.time
    jb  .A
    ja  .9
    jmp .N
.7:
ifdef _WIN64
    mov rcx,[rdi].FBLK.size
    cmp rcx,[rsi].FBLK.size
else
    mov ecx,dword ptr [rdi].FBLK.size[4]
    cmp ecx,dword ptr [rsi].FBLK.size[4]
    jb  .A
    ja  .9
    mov ecx,dword ptr [rdi].FBLK.size
    cmp ecx,dword ptr [rsi].FBLK.size
endif
    jb  .A
    ja  .9
    jmp .N
.8:
    test [rsi].FBLK.attrib,_F_SUBDIR
    jnz .A
.9:
    mov eax,-1
    jmp .C
.A:
    mov eax,1
    jmp .C
.N:
ifdef __UNIX__
    _tcscmp(name_a, name_b)
else
    _tcsicmp(name_a, name_b)
endif
.C:
    ret

compare endp

_dsort proc uses rbx d:PDIRENT

    ldr rbx,d

    mov sortflag,[rbx].DIRENT.flags
    qsort([rbx].DIRENT.fcb, [rbx].DIRENT.count, size_t, &compare)
    ret

_dsort endp

    end
