
    ; 2.37.31 - @ComAlloc( Class[, vtable | additional-size[, additional-size]] )

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    option win64:3

.class C0

    array       dd 100 dup(?)

    C0          proc
    Release     proc
    AddArray    proc
   .ends

.class C1

    m_next      ptr C1 ?
    m_string    sbyte 1 dup(?)

    C1          proc
    Release     proc
    AddString   proc :ptr sbyte
   .ends


   .code

malloc proc size:dword
    ret
    endp
free proc p:ptr
    ret
    endp
strlen proc string:ptr sbyte
    ret
    endp
strcpy proc s1:ptr sbyte, s2:ptr sbyte
    ret
    endp

    assume class:rbx

C0::C0 proc
    @ComAlloc(C0)
    ret
    endp

C0::Release proc
    free(rbx)
    ret
    endp

C0::AddArray proc
    @ComAlloc(C0, sizeof(C0.array))
    ret
    endp

C1::C1 proc
    @ComAlloc(C1)
    ret
    endp

C1::Release proc
    free(rbx)
    ret
    endp

C1::AddString proc uses rsi rdi string:ptr sbyte

    ldr rdi,string

    strlen(rdi)
    mov rsi,lpVtbl

    .if @ComAlloc(C1, rsi, rax)

        mov m_next,rax
        mov rbx,rax
        strcpy( &m_string, rdi)
    .endif
    ret
    endp
    end
