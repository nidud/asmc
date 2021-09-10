Asmc Macro Assembler Reference

## Directives Reference

### Code Labels

|||
|:---|:---|
| **ALIGN** [[_number_]] | Aligns the next variable or instruction on a byte that is a multiple of _number_.
| **EVEN**  | Aligns the next variable or instruction on an even byte. |
| _name_ **LABEL** _type_<br>_name_ **LABEL** [[NEAR\|FAR\|PROC]] PTR [[_type_]] | Creates a new label by assigning the current location-counter value and the given _type_ to _name_. |
| **ORG** _expression_ | Sets the location counter to _expression_. |
|xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx| |


### Conditional Assembly

|||
|:---|:---|
| **DEFINE** _name_ _expression_ | Assigns value of _expression_ to _name_. |
| [[ELSE]IF] [...] **DEFINED**(_name_) [...] | Grants assembly if _name_ is a previously defined label, variable, or symbol. |
| **ELSE** | Marks the beginning of an alternate block within a conditional block. |
| **ELSEIF** | Combines ELSE and IF into one statement. |
| **ELSEIF2** | ELSEIF block evaluated on every assembly pass if OPTION:SETIF2 is TRUE. |
| **IF** _expression1_<br>_if\_statements_<br>[[ELSEIF _expression2_<br>_elseif\_statements_]]<br>[[ELSE<br>_else_statements_]]<br>ENDIF | Grants assembly of _if\_statements_ if _expression1_ is true (nonzero) or _elseif\_statements_ if _expression1_ is false (0) and _expression2_ is true. The following directives may be substituted for ELSEIF: ELSEIFB, ELSEIFDEF, ELSEIFDIF, ELSEIFDIFI, ELSEIFE, ELSEIFIDN, ELSEIFIDNI, ELSEIFNB, and ELSEIFNDEF. Optionally, assembles elsestatements if the previous expression is false. Note that the expressions are evaluated at assembly time. |
| **IF2** _expression_ | IF block is evaluated on every assembly pass if OPTION:SETIF2 is TRUE. |
| **IF[N]B** _textitem_ | Grants assembly if _textitem_ is blank. |
| **IFDIF[[I]]** _textitem1_, _textitem2_ | Grants assembly if the text items are different. If I is given, the comparison is case insensitive. |
| **IFE** _expression_ | Grants assembly if _expression_ is false (0). |
| **IFIDN[[I]]** _textitem1_, _textitem2_ | Grants assembly if the text items are identical. If I is given, the comparison is case insensitive. |
| **IF[N]DEF** _name_ | Grants assembly if _name_ is a previously defined label, variable, or symbol. |
| **UNDEF** _identifier_ | Removes (undefines) a previously defined label, variable, or symbol. |
|xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx| |


### Conditional Control Flow

- [.ASSERT](dot_assert.md)
- [.BREAK](dot_break.md)
- [.CASE](dot_case.md)
- [.CLASS](dot_class.md)
- [.CONTINUE](dot_continue.md)
- [.COMDEF](dot_comdef.md)
- [.DEFAULT](dot_default.md)
- [.ENUM](dot_enum.md)
- [.ENUMT](dot_enumt.md)
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
- [.REPEAT](dot_repeat.md)
- [.RETURN](dot_return.md)
- [.STATIC](dot_static.md)
- [.SWITCH](dot_switch.md)
- [.TEMPLATE](dot_template.md)
- [.UNTIL](dot_until.md)
- [.UNTILCXZ](dot_untilcxz.md)
- [.WHILE](dot_while.md)


### Conditional Error

|||
|:---|:---|
| **.ERR** [[_message_]] | Generates an error. |
| **.ERR2** [[_message_]] | .ERR block evaluated on every assembly pass if OPTION:SETIF2 is TRUE. |
| **.ERRB** _textitem_ [[,_message_]] | Generates an error if textitem is blank. |
| **.ERRDEF** _name_ [[,_message_]] | Generates an error if _name_ is a previously defined label, variable, or symbol. |
| **.ERRDIF[[I]]** _textitem1_, _textitem2_ [[,_message_]] | Generates an error if the text items are different. If I is given, the comparison is case insensitive. |
| **.ERRE** _expression_ [[, _message_]] | Generates an error if expression is false (0). |
| **.ERRIDN[[I]]** _textitem1_, _textitem2_ [[,_message_]] | Generates an error if the text items are identical. If I is given, the comparison is case insensitive. |
| **.ERRNB** _textitem_ [[,_message_]] | Generates an error if textitem is not blank. |
| **.ERRNDEF** _name_ [[,_message_]] | Generates an error if _name_ has not been defined. |
| **.ERRNZ** _expression_ [[, _message_]] | Generates an error if expression is true (nonzero). |
|xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx| |


### Data Allocation

[[_name_]] _type_ _initializer_ [[, _initializer_]] ...

Allocates and optionally initializes _count_ byte(s) of storage.
Can also be used as a type specifier anywhere a type is legal.

| _type_ | _size_ | |
|:---         |:---:|:---|
| **BYTE**    | 1  | unsigned |
| **SBYTE**   | 1  | signed |
| **WORD**    | 2  | unsigned |
| **SWORD**   | 2  | signed |
| **DWORD**   | 4  | unsigned |
| **SDWORD**  | 4  | signed |
| **FWORD**   | 6  | unsigned |
| **QWORD**   | 8  | unsigned |
| **SQWORD**  | 8  | signed |
| **TBYTE**   | 10 | unsigned |
| **OWORD**   | 16 | unsigned |
| **XMMWORD** | 16 | vector |
| **YWORD**   | 32 | vector |
| **ZWORD**   | 64 | vector |
| **REAL2**   | 2  | float |
| **REAL4**   | 4  | float |
| **REAL8**   | 8  | float |
| **REAL10**  | 10 | float |
| **REAL16**  | 16 | float |


### Equates

|||
| --- |:--- |
| _name_ **=** _expression_ | Assigns the numeric value of expression to name. The symbol can be redefined later. |
| _name_ **EQU** _expression_ | Assigns numeric value of _expression_ to _name_. The _name_ cannot be redefined later. |
| _name_ **EQU** _\<text\>_ | Assigns specified _text_ to _name_. The _name_ can be assigned a different text later. |
| _name_ **TEXTEQU** [[_textitem_]] | Assigns _textitem_ to _name_. The textitem can be a literal string, a constant preceded by a , or the string returned by a macro function. |
|xxxxxxxxxxxxxxxxxxxxxxxxxxxx| |


### Listing Control

|||
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
| **.PAGE** [[[[_length_]], _width_]] | Sets line length and character width of the program listing. If no arguments are given, generates a page break. |
| **.PAGE** + | Increments the section number and resets the page number to 1. |
| **.SUBTITLE** | Defines the listing subtitle. Same as .SUBTTL. |
| **.TFCOND** | Toggles listing of false conditional blocks. |
| **.TITLE** _text_ | Defines the program listing title. |
|xxxxxxxxxxxxxxxxxxxxxxxxxxxx| |

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
