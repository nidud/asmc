Asmc Macro Assembler Reference

## .CLASSDEF

**.CLASSDEF** _name_ [args]

Declares a structure type for a [COM interface](dot_comdef.md).

.CLASSDEF adds the following types:

    .classdef Class
    * LPCLASS typedef ptr Class
    * LPCLASSVtbl typedef ptr ClassVtbl
    * Class@Class proto :ptr Class
    * Class struct 8
    * lpVtbl LPCLASSVtbl ?

Release() is added as the first method:

    Method1 proc local  ; static
    Method2 proc :ptr   ; first virtual function
    * Class ends
    * ClassVtbl struct
    * T$000B typedef proto :ptr Class
    * P$000B typedef ptr T$000B
    * Release P$000B ?
    * T$000B typedef proto :ptr Class
    * P$000B typedef ptr T$000B
    * Method2 P$000B ?

To define a method locally in the base class the keyword LOCAL may be used. Locally defined functions are called directly without the _this argument omitted.

    assume rcx:LPCLASS

    foo proc

    local p:LPCLASS

    [rcx].Method1()
    [rcx].Method2(rdx)
    [rcx].Release()
    ret

    foo endp

Code produced:

     0: 55            push   rbp
     1: 48 8b ec      mov    rbp,rsp
     4: 48 83 ec 30   sub    rsp,0x30
     8: ff 51 10      call   QWORD PTR [rcx+0x10]
     b: 48 8b 01      mov    rax,QWORD PTR [rcx]
     e: ff 50 08      call   QWORD PTR [rax+0x8]
    11: 48 8b 01      mov    rax,QWORD PTR [rcx]
    14: ff 10         call   QWORD PTR [rax]
    16: c9            leave
    17: c3            ret

#### See Also

[.ENDS](dot_ends.md) | [.COMDEF](dot_comdef.md)
