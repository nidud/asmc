include string.inc
include malloc.inc
include errno.inc
include CHeap.inc

_FREE   equ 0
_USED   equ 1
_ALIGN  equ 3

MBLOCK  STRUC
bsize   dd ?
flags   dd ?
prev    dq ?
MBLOCK  ENDS

CHeap::Alloc        proto :ptr CHeap, :UINT
CHeap::Free         proto :ptr CHeap, :PVOID
CHeap::Realloc      proto :ptr CHeap, :PVOID, :UINT
CHeap::Aligned      proto :ptr CHeap, :UINT, :UINT
CHeap::NewString    proto :ptr CHeap, :LPSTR
CHeap::Coreleft     proto :ptr CHeap

    .data
    virtual_table label qword
        dq CStack@Release
        dq CHeap@Alloc
        dq CHeap@Free
        dq CHeap@Realloc
        dq CHeap@Aligned
        dq CHeap@NewString
        dq CHeap@Coreleft
    .code

    option win64:rsp nosave noauto
    assume rcx:LPCSTACK

CStack::CStack proc BufferSize:UINT, ReservedStack:UINT

    .repeat

        .if !rcx

            add edx,sizeof(MBLOCK) + _GRANULARITY - 1
            and dl,-(_GRANULARITY)
            lea rcx,[rdx+sizeof(CStack)+sizeof(MBLOCK)]
            lea rax,[rsp+8]
            .while ecx > 0x1000

                sub  rax,0x1000
                test [rax],al
                sub  ecx,0x1000
            .endw
            sub rax,rcx
            add rax,8               ; rsp + 8 on return
            test [rax],al           ; probe..

            mov r9,rsp
            mov rsp,rax             ; new stack
            mov rcx,[r9]            ; return addr
            mov [rax],rcx

            lea rcx,[rax+r8+8]      ; + shadow space
            and cl,-16
            lea rax,[rcx+sizeof(CStack)]
            mov [rcx].heap_base,rax
            mov [rcx].heap_free,rax
            mov [rcx].stack_ptr,r9

            xor r8d,r8d
            mov [rax].MBLOCK.bsize,edx
            mov [rax].MBLOCK.flags,r8d
            mov [rax+rdx].MBLOCK.bsize,r8d
            mov [rax+rdx].MBLOCK.flags,_USED
            mov [rax+rdx].MBLOCK.prev,rax
        .endif
        lea rax,virtual_table
        mov [rcx].lpVtbl,rax
        mov rax,rcx
    .until 1
    ret

CStack::CStack endp

CStack::Release proc

    mov rax,[rsp]
    mov rsp,[rcx].stack_ptr
    mov [rsp],rax
    ret

CStack::Release endp

    end
