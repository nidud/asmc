Asmc Macro Assembler Reference

## .SWITCH

**.SWITCH** [JMP] [C | PASCAL] [_expression_]

The switch comes in three main variants: a structured switch, as in Pascal, which takes exactly one branch, an unstructured switch, as in C, which functions as a type of goto, and a control table switch with the added possibility of testing for combinations of input values, using boolean style AND/OR conditions, and potentially calling subroutines instead of just a single set of values.

The control table switch is declared with no arguments and each .CASE directive does all the testing.
```
    .switch
      .case strchr( esi, '(' )
      .case strchr( esi, ')' )
	    jmp around
      ...
    .endsw
```
The unstructured switch works as a regular C switch (default) where each .CASE directive is just a label.
```
    .switch eax
      .case 0: .repeat : movsb
      .case 7: movsb
      .case 6: movsb
      .case 5: movsb
      .case 4: movsb
      .case 3: movsb
      .case 2: movsb
      .case 1: movsb : .untilcxz
    .endsw
```
The structured switch works as a regular Pascal switch where each .CASE directive is a closed branch.
```
    .switch eax
      .case 1: printf("Gold medal")
      .case 2: printf("Silver medal")
      .case 3: printf("Bronze medal")
      .default
	  printf("Better luck next time")
    .endsw
```
The **JMP** option skips the range-test in the jump code.
```
    .switch jmp pascal eax
      .case 0
      .case 1
      .case 2
    .endsw
```
A start label is added for [.gotosw](dot-gotosw.md).
```
    * @C0003:
```
In 32-bit a direct jump is used.
```
    * jmp [eax*4+@C0001-(MIN@C0001*4)]
```
In 64-bit the jump-address is calculated from the exit-label.
```
    * lea r11,@C0002
    * sub r11,[rax*8+r11-(MIN@C0001*8)+(@C0001-@C0002)]
    * jmp r11
```
Pascal entries auto exits.

```
    * @C0004: ; .case 0
    * jmp @C0002
    * @C0005: ; .case 1
    * jmp @C0002
    * @C0006: ; .case 2
    * jmp @C0002
```
Jump table entries in 64-bit are distance from case to exit.

```
    * ALIGN 8
    * @C0001:
    * MIN@C0001 equ 0
    * dq @C0002-@C0004
    * dq @C0002-@C0005
    * dq @C0002-@C0006
    * @C0002:
```
In 32-bit the table entry is an address. If not Pascal is used (no auto exit) the table is created in the data segment.

```
    .switch jmp eax
    * @C0003:
    * jmp [eax*4+DT@C0001-(MIN@C0001*4)]
    * @C0004: ; .case 0
    * @C0005: ; .case 1
    * @C0006: ; .case 2
    * @C0001:
    * @C0002:
```
#### See Also

[Directives Reference](readme.md) | [OPTION SWITCH](opt-switch.md) | [.CASE](dot-case.md) | [.ENDC](dot-endc.md) | [.ENDSW](dot-endsw.md)
