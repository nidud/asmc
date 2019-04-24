Asmc Macro Assembler Reference

### .SETFRAME

Fills in the frame register field and offset in the unwind information using the specified register (reg) and offset (offset). The offset must be a multiple of 16 and less than or equal to 240\. This directive also generates a UWOP_SET_FPREG unwind code entry for the specified register using the current prologue offset.

**.SETFRAME** reg, offset

.SETFRAME allows ml64.exe users to specify how a frame function unwinds, and is only allowed within the prologue, which extends from the PROC FRAME declaration to the .ENDPROLOG directive. These directives do not generate code; they only generate .xdata and .pdata. .SETFRAME should be preceded by instructions that actually implement the actions to be unwound. It is a good practice to wrap both the unwind directives and the code they are meant to unwind in a macro to ensure agreement.

#### Sample

The following sample shows how to use a frame pointer:

    ; asmc -win64 frmex2.asm
    ; link /entry:frmex2 /subsystem:console frmex2.obj

    .code

    frmex2 proc frame
    push rbp
    .pushreg rbp
    sub rsp,0x10
    .allocstack 0x10
    mov rbp, rsp
    .setframe rbp,0
    .endprolog

    ; modify the stack pointer outside of the prologue (similar to alloca)

    sub rsp,0x60

    ; we can unwind from the following AV because of the frame pointer
    mov rax,0
    mov rax,[rax] ; AV!

    add rsp,0x60
    add rsp,0x10
    pop rbp
    ret
    frmex2 endp

    end

#### See Also

[Directives Reference](readme.md)
