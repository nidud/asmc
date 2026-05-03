Asmc Macro Assembler Reference

## @ComAlloc

**@ComAlloc(_Class_[[,_expression1_[[,_expression2_]]]])**

Macro function that allocates a CLASS object. Returns a pointer to the new object.

If _expression1_ is added and evaluates to a label or register, a _vtable_ is assumed. In that case, if _expression2_ is added and evaluates to a CONST value or register, additional size is assumed. Else, if _expression1_ evaluates to a CONST value, additional size is assumed.

### Example

```
.class MyClass

    m_next          ptr MyClass ?
    m_string        sbyte 1 dup(?)

    MyClass         proc
    Release         proc
    AddString       proc :ptr sbyte
   .ends

   .code

MyClass::MyClass proc

    @ComAlloc(MyClass)
    ret

MyClass::MyClass endp
...
        push    rbp
        mov     rbp, rsp
        sub     rsp, 32
        mov     ecx, 40         ; MyClass + MyClassVtbl
        call    malloc
        mov     rdx, rdi        ; Save rdi
        lea     rdi, [rax+8H]   ; Clear MyClass ( - lpVtbl )
        mov     ecx, 16         ; m_next + m_string + alignment
        xor     eax, eax
        rep     stosb
        lea     rax, [rdi-18H]  ; Init Vtbl
        xchg    rdx, rdi        ; rdi = end of MyClass ( = start of MyClassVtbl )
        mov     [rax], rdx
        lea     rcx, [MyClass_Release]
        mov     [rdx], rcx
        lea     rcx, [MyClass_AddString]
        mov     [rdx+8H], rcx
        leave
        ret
```
Note that the _vtable_ argument has to be a nonvolatile-register but the size argument not.

```
    assume class:rbx

MyClass::AddString proc uses rsi rdi string:ptr sbyte

    ldr rdi,string

    strlen(rdi)
    mov rsi,lpVtbl

    .if @ComAlloc(MyClass, rsi, rax)

        mov m_next,rax
        mov rbx,rax
        strcpy( &m_string, rdi)
    .endif
    ret

MyClass::AddString endp
...
        push    rsi
        push    rdi
        push    rbx
        push    rbp
        mov     rbp, rsp
        sub     rsp, 40
        mov     rbx, rcx        ; this
        mov     rdi, rdx        ; string
        mov     rcx, rdi
        call    strlen
        mov     rsi, [rbx]      ; Use *this vtable
        lea     ecx, [rax+18H]  ; MyClass + rax
        call    malloc
        mov     rdx, rdi
        lea     rdi, [rax+8H]   ; Clear
        mov     ecx, 16
        xor     eax, eax
        rep     stosb
        lea     rax, [rdi-18H]
        mov     rdi, rdx
        mov     rdx, rsi
        mov     [rax], rdx
        test    rax, rax
        jz      ?_001
        mov     [rbx+8H], rax   ; link to *this.m_next
        mov     rbx, rax        ; new class
        mov     rdx, rdi
        lea     rcx, [rbx+10H]  ; &m_string
        call    strcpy
?_001:  leave
        pop     rbx
        pop     rdi
        pop     rsi
        ret
```

#### See Also

[Macro Functions](macro-functions.md) | [Symbols Reference](readme.md)
