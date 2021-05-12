;
; VEX-Encoded GPR Instructions (v2.28)
;
ifndef __ASMC64__
    .x64
    .model flat
endif
    .code

    blsmsk  rax,r9
    blsmsk  rcx,r9
    blsmsk  rdx,r9
    blsmsk  r11,r9
    blsmsk  r11,[rcx]

    blsr    rax,rax
    blsr    rcx,rax
    blsr    rdx,rax
    blsr    r8,rax
    blsr    r9,rax
    blsr    r10,rax
    blsr    r11,rax

    blsr    rax,r8
    blsr    rcx,r8
    blsr    rdx,r8
    blsr    r8,r8
    blsr    r9,r8
    blsr    r10,r8
    blsr    r11,r8

    blsi    rax,rax
    blsi    rcx,rax
    blsi    rdx,rax
    blsi    r8,rax
    blsi    r9,rax
    blsi    r10,rax
    blsi    r11,rax

    blsi    rax,r8
    blsi    rcx,r8
    blsi    rdx,r8
    blsi    r8,r8
    blsi    r9,r8
    blsi    r10,r8
    blsi    r11,r8

    sarx  rax,rcx,rbx
    shlx  rax,rcx,rbx
    shrx  rax,rcx,rbx
    bzhi  rax,rcx,rbx

    sarx  rax,[rcx],rbx
    shlx  rax,[rcx],rbx
    shrx  rax,[rcx],rbx
    bzhi  rax,[rcx],rbx

    pext rax,rcx,rbx
    pext rax,rcx,[rbx]

    pdep rax,rcx,rbx
    pdep rax,rcx,[rbx]

    andn eax,edx,ecx
    andn eax,edx,[rcx]

    rorx rax,rdx,2

    mulx rax,rcx,[rcx]
    mulx edx,edx,edx
    mulx eax,eax,eax
    mulx rax,rdx,rcx
    mulx rbx,rdx,rcx
    mulx r10,rdx,rcx

    end
