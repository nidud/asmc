Asmc Macro Assembler Reference

## ALIGN

**ALIGN** [[_forward\_label_]] [[_number_]]

Aligns the next variable or instruction on a byte that is a multiple of _number_.

The _number_ must be a power of 2, and the assembler will insert between 0 and _number_-1 bytes of padding to ensure that the next variable or instruction starts at an address that is a multiple of _number_.

`ALIGN forward_label number` aligns a forward label's offset by inserting padding bytes so the resulting address is rounded up to the next multiple of _number_.

Example:
```asm
    jmp     start

    ALIGN   main_loop 16

; padding bytes here to ensure that the
; address of main_loop is a multiple of 16

check_blocks:
    mov     rdx,rcx
    shr     rdx,6
    jz      compare_u

main_loop:
    ...
```

#### See Also

[Code Labels](code-labels.md) | [Directives Reference](readme.md)
