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

CHeap::Release      proto :ptr CHeap
CHeap::Alloc        proto :ptr CHeap, :UINT
CHeap::Free         proto :ptr CHeap, :PVOID
CHeap::Realloc      proto :ptr CHeap, :PVOID, :UINT
CHeap::Aligned      proto :ptr CHeap, :UINT, :UINT
CHeap::NewString    proto :ptr CHeap, :LPSTR
CHeap::Coreleft     proto :ptr CHeap

    .data
    virtual_table label qword
        dq CHeap@Release
        dq CHeap@Alloc
        dq CHeap@Free
        dq CHeap@Realloc
        dq CHeap@Aligned
        dq CHeap@NewString
        dq CHeap@Coreleft
    .code

    option win64:nosave
    assume rcx:LPCHEAP

CHeap::CHeap proc BufferSize:UINT

    .repeat

        .if !rcx

            add edx,sizeof(MBLOCK) + _GRANULARITY - 1
            and dl,-(_GRANULARITY)
            mov BufferSize,edx
            mov rcx,GetProcessHeap()
            mov r8d,BufferSize
            add r8d,sizeof(CHeap)+8+sizeof(MBLOCK)

            .break .if !HeapAlloc(rcx, 0, r8)

            mov rcx,rax
            add rax,sizeof(CHeap)+8
            mov [rcx].heap_base,rax
            mov [rcx].heap_free,rax
            mov edx,BufferSize
            mov [rax].MBLOCK.bsize,edx
            mov [rax].MBLOCK.flags,0
            mov [rax+rdx].MBLOCK.bsize,0
            mov [rax+rdx].MBLOCK.flags,_USED
            mov [rax+rdx].MBLOCK.prev,rax
        .endif
        lea rax,virtual_table
        mov [rcx].lpVtbl,rax
        mov rax,rcx
    .until 1
    ret

CHeap::CHeap endp

CHeap::Release proc

    mov _this,rcx

    HeapFree( GetProcessHeap(), 0, _this )
    ret

CHeap::Release endp

    end
