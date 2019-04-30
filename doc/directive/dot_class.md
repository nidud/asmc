Asmc Macro Assembler Reference

## .CLASS

**.CLASS** _name_ [args]

Declares a structure type for a [COM interface](dot_comdef.md).

.CLASS adds the following types:

    .class Class
        foo proc local  ; Class.foo()
        bar proc :ptr   ; ClassVtbl.bar(:ptr Class, :ptr)
    .ends

- **Class::Class** proto
- **LPCLASS** typedef ptr Class
- **LPCLASSVtbl** typedef ptr ClassVtbl
- **Class** struct
    lpVtbl LPCLASSVtbl ?
    foo    typedef() ?
- **Class** ends
- **ClassVtbl** struct
    bar    typedef(:ptr Class, :ptr) ?
- **ClassVtbl** ends

LOCAL means a pointer in the base class.

- assume rcx:LPCLASS
- [rcx].foo()
        call [rcx+0x10]
- [rcx].bar(rdx)
        mov  rax,[rcx]
        call [rax]

#### See Also

[.ENDS](dot_ends.md) | [.COMDEF](dot_comdef.md) | [.NEW](dot_new.md)
