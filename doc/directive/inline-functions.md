Asmc Macro Assembler Reference

# Inline functions

In theory, using inline functions can make your program faster because they eliminate the overhead associated with function calls. Calling a function requires pushing the return address on the stack, pushing arguments onto the stack, jumping to the function body, and then executing a return instruction when the function finishes. This process is eliminated by inlining the function. There are also more opportunities to optimize functions expanded inline versus those that aren't. A tradeoff of inline functions is that the overall size of your program can increase.

Inline functions are supported by the register calling conventions [asmcall](asmcall.md), [fastcall](fastcall.md), [syscall](syscall.md), [vectorcall](vectorcall.md) and [watcall](watcall.md). Argument evaluation use the normal function-call protocol with an additional :ABS argument type.

### Example

```
define __inline <syscall>

multi2 proto asmcall a:dword, b:dword, p:ptr {
    mul     edx
    mov     [rcx],eax
    }
multi3 proto __inline a:dword, b:abs, p:ptr {
    imul    eax,a,b
    mov     [p],eax
    }
multi4 proto __inline :dword, :abs, :ptr {
    imul    eax,_1,_2
    mov     [_3],eax
    }
```

#### See Also

[Directives Reference](readme.md) | [Procedures](procedures.md) | [PROTO](proto.md)
