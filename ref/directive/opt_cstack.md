Asmc Macro Assembler Reference

## OPTION CSTACK

**OPTION CSTACK**:[ ON | OFF ]

The **CSTACK** option change the stack frame creation on a [PROC](proc.md) entry if the **USES** clause is used. If set the registers will be pushed before the stack frame is created and popped after the stack is restored. The default setting is OFF.

#### Sample

The following sample shows how to use the command line argument -**Cs** to create a re-sizable stack:

    ; asmc -pe -win64 -Cs foo.asm

    .code

    foo proc uses rsi rdi a1:byte

    mov al,a1
    ret

    foo endp

    end foo

#### See Also

[Directives Reference](readme.md)