Asmc Macro Assembler Reference

## INVOKE

**INVOKE** expression [[, arguments]]

Calls the procedure at the address given by expression, passing the arguments on the stack or in registers according to the standard calling conventions of the language type. Each argument passed to the procedure may be an expression, a register pair, or an address expression (an expression preceded by ADDR).

In Asmc a macro is handled at the same level as a procedure. The header file may then control the expansion:

```
    ifdef __INLINE__
	strlen	macro string
		...
		endm
    else
	strlen	proto :ptr
    endif
```

This is achieved by simply excluding _invoke_ as appose to allow invocations of macros.

```
    strlen( esi )
```

Asmc sees the combination of a procedure followed by an open bracket as invoke. Empty brackets will be given special handling if the token in front is not a macro.

```
    call eax
    call label

    eax()
    label()
```

It is also possible to typedef a register to a proto type and call it directly using invoke:

```
    proto_r macro reg, args:vararg
    local t, p
    t typedef proto args
    p typedef ptr t
    exitm<assume reg:ptr p>
    endm

    proto_r(eax, :dword, :ptr, :ptr, :dword)
    GetProcAddress(GetModuleHandle("user32.dll"),"MessageBoxA")
    eax(0, "This is a test", "Hello!", 0)
```

So the register call returns a register:

```
    proto_r(eax, :ptr)
    eax(0)(1)(2)

	push	0
	call	eax
	push	1
	call	eax
	push	2
	call	eax
```

This simple solution avoids breaking any existing code with a few exceptions: Masm allows brackets to access memory.

```
    .if edx < foo( 1 )
    ; MASM: cmp edx,foo+1
    ; ASMC: invoke foo, 1 : cmp edx,eax
```

So square brackets should be used for accessing memory and round brackets to execute. However, an error must then be issued if Asmc extensions are turned off and labels are accessed using round brackets to ensure compatibility.

The inside of brackets may be recursive used at any length including [C-strings](../symbol/readme.md). However, the return code for a procedure is [R|E]AX so there is a limit with regards to OR/AND testing of nested functions.

```
    .if foo( bar( 1 ), 2 ) == TRUE
```

#### See Also

[Procedures](procedures.md) | [Directives Reference](readme.md)
