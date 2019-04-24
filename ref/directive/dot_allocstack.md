Asmc Macro Assembler Reference

## .ALLOCSTACK

Generates a UWOP_ALLOC_SMALL or a UWOP_ALLOC_LARGE with the specified size for the current offset in the prologue.

**.ALLOCSTACK** size

.ALLOCSTACK allows users to specify how a frame function unwinds and is only allowed within the prologue, which extends from the PROC FRAME declaration to the [.ENDPROLOG](dot_endprolog.md) directive. These directives do not generate code; they only generate .xdata and .pdata. .ALLOCSTACK should be preceded by instructions that actually implement the actions to be unwound. It is a good practice to wrap both the unwind directives and the code they are meant to unwind in a macro to ensure agreement.

The size operand must be a multiple of 8.

**Sample**

The following sample shows how to specify an unwind/exception handler:

    ; asmc -win64 test.asm`
    ; link /entry:main /subsystem:console test.obj`

    .code

    unwind proc

    ; exception/unwind handler body

    ret

    unwind endp

    main proc frame : unwind

    sub rsp,16
    .allocstack 16
    .endprolog

    ; function body
    add rsp,16
    ret

    main endp

    end

#### See Also

[Directives Reference](readme.md)
