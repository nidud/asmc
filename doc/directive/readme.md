Asmc Macro Assembler Reference

## Directives Reference

### Code Labels

| | | |
|:---|:--- |:--- |
| **ALIGN** | `**ALIGN** [[_number_]]` | Aligns the next variable or instruction on a byte that is a multiple of _number_.
| **EVEN**  | `**EVEN**` | Aligns the next variable or instruction on an even byte. |
| **LABEL** | `_name_ **LABEL** _type_`<br>`_name_ **LABEL** [[NEAR \| FAR \| PROC]] PTR [[_type_]]` | Creates a new label by assigning the current location-counter value and the given _type_ to _name_. |
| **ORG** | `**ORG** _expression_` | Sets the location counter to _expression_. |

### Conditional Assembly

- [DEFINE](define.md)
- [DEFINED](defined.md)
- [ELSE](else.md)
- [ELSEIF](elseif.md)
- [ELSEIF2](elseif2.md)
- [IF](if.md)
- [IF2](if2.md)
- [IF[N]B](ifb.md)
- [IF[N]DEF](ifndef.md)
- [IFDIF[[I]]](ifdif.md)
- [IFE](ife.md)
- [IFIDN[[I]]](ifidn.md)
- [UNDEF](undef.md)

### Conditional Control Flow

- [.ASSERT](dot_assert.md)
- [.BREAK](dot_break.md)
- [.CASE](dot_case.md)
- [.CLASS](dot_class.md)
- [.CONTINUE](dot_continue.md)
- [.COMDEF](dot_comdef.md)
- [.DEFAULT](dot_default.md)
- [.ENUM](dot_enum.md)
- [.ELSE](dot_else.md)
- [.ELSEIF](dot_if.md)
- [.ENDIF](dot_endif.md)
- [.ENDW](dot_endw.md)
- [.ENDC](dot_endc.md)
- [.ENDSW](dot_endsw.md)
- [.ENDS](dot_ends.md)
- [.FOR](dot_for.md)
- [.GOTOSW](dot_gotosw.md)
- [.IF](dot_if.md)
- [.INLINE](dot_inline.md)
- [.NEW](dot_new.md)
- [.OPERATOR](dot_operator.md)
- [.REPEAT](dot_repeat.md)
- [.RETURN](dot_return.md)
- [.STATIC](dot_static.md)
- [.SWITCH](dot_switch.md)
- [.TEMPLATE](dot_template.md)
- [.UNTIL](dot_until.md)
- [.UNTILCXZ](dot_untilcxz.md)
- [.WHILE](dot_while.md)

### Conditional Error

- [.ERR](dot_err.md)
- [.ERR2](dot_err2.md)
- [.ERRB](dot_errb.md)
- [.ERRDEF](dot_errdef.md)
- [.ERRDIF[[I]]](dot_errdif.md)
- [.ERRE](dot_erre.md)
- [.ERRIDN[[I]]](dot_erridn.md)
- [.ERRNB](dot_errnb.md)
- [.ERRNDEF](dot_errndef.md)
- [.ERRNZ](dot_errnz.md)

### Data Allocation

[[_name_]] _type_ _initializer_ [[, _initializer_]] ...

Can also be used as a type specifier anywhere a type is legal.

| | |
| --- |:--- |
| **BYTE** | Allocates and optionally initializes 1 byte of storage. |
| **DWORD** | Allocates and optionally initializes 4 bytes of storage. |
| **FWORD** | Allocates and optionally initializes 6 bytes of storage. |
| **OWORD** | Allocates and optionally initializes 16 bytes of storage. |
| **QWORD** | Allocates and optionally initializes 8 bytes of storage. |
| **REAL2** | Allocates and optionally initializes 2 bytes of storage. |
| **REAL4** | Allocates and optionally initializes 4 bytes of storage. |
| **REAL8** | Allocates and optionally initializes 8 bytes of storage. |
| **REAL10** | Allocates and optionally initializes 10 bytes of storage. |
| **REAL16** | Allocates and optionally initializes 16 bytes of storage. |
| **SBYTE** | Allocates and optionally initializes 1 byte of storage. |
| **SDWORD** | Allocates and optionally initializes 4 bytes of storage. |
| **SWORD** | Allocates and optionally initializes 2 bytes of storage. |
| **TBYTE** | Allocates and optionally initializes 10 bytes of storage. |
| **XMMWORD** | Allocates and optionally initializes 16 bytes of storage. |
| **YWORD** | Allocates and optionally initializes 32 bytes of storage. |
| **ZWORD** | Allocates and optionally initializes 64 bytes of storage. |


### Equates

- [=](e.md)
- [EQU](equ.md)
- [TEXTEQU](textequ.md)

### Listing Control

| | |
| --- |:--- |
| **.CREF** | Enables listing of symbols in the symbol portion of the symbol table and browser file. |
| **.LIST** | Starts listing of statements. This is the default. |
| **.LISTALL** | Starts listing of all statements. Equivalent to the combination of .LIST, .LISTIF, and .LISTMACROALL. |
| **.LISTIF** | Starts listing of statements in false conditional blocks. Same as .LFCOND. |
| **.LISTMACRO** | Starts listing of macro expansion statements that generate code or data. This is the default. Same as .XALL. |
| **.LISTMACROALL** | Starts listing of all statements in macros. Same as .LALL. |
| **.NOCREF** [[_name_ [[, _name_]]...]] | Suppresses listing of symbols in the symbol table and browser file. If names are specified, then only the given names are suppressed. Same as .XCREF. |
| **.NOLIST** | Suppresses program listing. Same as .XLIST. |
| **.NOLISTIF** | Suppresses listing of conditional blocks whose condition evaluates to false (0). This is the default. Same as .SFCOND. |
| **.NOLISTMACRO** | Suppresses listing of macro expansions. Same as .SALL. |
| **.PAGE** [[[[length]], width]] | Sets line length and character width of the program listing. If no arguments are given, generates a page break. |
| **.PAGE** + | Increments the section number and resets the page number to 1. |
| **.SUBTITLE** | Defines the listing subtitle. Same as .SUBTTL. |
| **.TFCOND** | Toggles listing of false conditional blocks. |
| **.TITLE** _text_ | Defines the program listing title. |

### Macros

- [ENDM](endm.md)
- [EXITM](exitm.md)
- [GOTO](goto.md)
- [LOCAL](local.md)
- [MACRO](macro.md)
- [PURGE](purge.md)
- [RETM](retm.md)

### Miscellaneous

- [ASSUME](assume.md)
- [COMMENT](comment.md)
- [ECHO](echo.md)
- [END](end.md)
- [INCLUDE](include.md)
- [INCLUDELIB](includelib.md)
- [OPTION](option.md)
- [POPCONTEXT](popcontext.md)
- [PUSHCONTEXT](pushcontext.md)
- [.RADIX](dot_radix.md)
- [.SAFESEH](dot_safeseh.md)
- [.ALLOCSTACK](dot_allocstack.md)
- [.ENDPROLOG](dot_endprolog.md)
- [.PUSHFRAME](dot_pushframe.md)
- [.PUSHREG](dot_pushreg.md)
- [.SAVEREG](dot_savereg.md)
- [.SAVEXMM128](dot_savexmm128.md)
- [.SETFRAME](dot_setframe.md)
- [.PRAGMA](dot_pragma.md)

### Procedures

- [ENDP](endp.md)
- [INVOKE](invoke.md)
- [PROC](proc.md)
- [PROTO](proto.md)

### Processor

| | |
| -------- |:------- |
| **.186** | Enables assembly of instructions for the 80186 processor; disables assembly of instructions introduced with later processors. Also enables 8087 instructions. |
| **.286** | Enables assembly of nonprivileged instructions for the 80286 processor; disables assembly of instructions introduced with later processors. Also enables 80287 instructions. |
| **.286P** | Enables assembly of all instructions (including privileged) for the 80286 processor; disables assembly of instructions introduced with later processors. Also enables 80287 instructions. |
| **.287** | Enables assembly of instructions for the 80287 coprocessor; disables assembly of instructions introduced with later coprocessors. |
| **.386** | Enables assembly of nonprivileged instructions for the 80386 processor; disables assembly of instructions introduced with later processors. Also enables 80387 instructions. |
| **.386P** | Enables assembly of all instructions (including privileged) for the 80386 processor; disables assembly of instructions introduced with later processors. Also enables 80387 instructions. |
| **.387** | Enables assembly of instructions for the 80387 coprocessor. |
| **.486** | Enables assembly of nonprivileged instructions for the 80486 processor. |
| **.486P** | Enables assembly of all instructions (including privileged) for the 80486 processor. |
| **.586** | Enables assembly of nonprivileged instructions for the Pentium processor. |
| **.586P** | Enables assembly of all instructions (including privileged) for the Pentium processor. |
| **.686** | Enables assembly of nonprivileged instructions for the Pentium Pro processor. |
| **.686P** | Enables assembly of all instructions (including privileged) for the Pentium Pro processor. |
| **.K3D** | Enables assembly of K3D instructions. |
| **.MMX** | Enables assembly of MMX or single-instruction, multiple data (SIMD) instructions. |
| **.XMM** | Enables assembly of Internet Streaming SIMD Extension instructions. |
| **.X64** | Enables assembly of nonprivileged instructions for the x86-64 processor. |
| **.X64P** | Enables assembly of privileged instructions for the x86-64 processor. |
| **.8086** | Enables assembly of 8086 instructions (and the identical 8088 instructions); disables assembly of instructions introduced with later processors. Also enables 8087 instructions. This is the default mode for processors. |
| **.8087** | Enables assembly of 8087 instructions; disables assembly of instructions introduced with later coprocessors. This is the default mode for coprocessors. |
| **.NO87** | Disallows assembly of all floating-point instructions. |

### Repeat Blocks

- [ENDM](endm.md)
- [FOR](for.md)
- [FORC](forc.md)
- [GOTO](goto.md)
- [REPEAT](repeat.md)
- [WHILE](while.md)

### Scope

- [COMM](comm.md)
- [EXTERN](extern.md)
- [EXTERNDEF](externdef.md)
- [INCLUDELIB](includelib.md)
- [PUBLIC](public.md)

### Segment

- [.ALPHA](dot_alpha.md)
- [ASSUME](assume.md)
- [.DOSSEG](dot_dosseg.md)
- [END](end.md)
- [ENDS](ends.md)
- [GROUP](group.md)
- [SEGMENT](segment.md)
- [.SEQ](dot_seq.md)

### Simplified Segment

- [.CODE](dot_code.md)
- [.CONST](dot_const.md)
- [.DATA](dot_data.md)
- [.DATA?](dot_dataq.md)
- [.DOSSEG](dot_dosseg.md)
- [.EXIT](dot_exit.md)
- [.FARDATA](dot_fardata.md)
- [.FARDATA?](dot_fardataq.md)
- [.MODEL](dot_model.md)
- [.STACK](dot_stack.md)
- [.STARTUP](dot_startup.md)

### String

- [CATSTR](catstr.md)
- [INSTR](instr.md)
- [SIZESTR](sizestr.md)
- [SUBSTR](substr.md)

### Structure and Record

- [ENDS](ends.md)
- [RECORD](record.md)
- [STRUCT](struct.md)
- [TYPEDEF](typedef.md)
- [UNION](union.md)

### See Also

[Symbols Reference](../symbol/readme.md)
