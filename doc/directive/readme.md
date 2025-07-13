Asmc Macro Assembler Reference

# Directives Reference

### In this article

- [x64](x64.md)
- [Code Labels](code-labels.md)
- [Conditional Assembly](conditional-assembly.md)
- [Conditional Control Flow](conditional-control-flow.md)
- [Conditional Error](conditional-error.md)
- [Data Allocation](data-allocation.md)
- [Equates](equates.md)
- [Inline Functions](inline-functions.md)
- [Instruction Format](instruction-format.md)
- [Listing Control](listing-control.md)
- [Macros](macros.md)
- [Miscellaneous](miscellaneous.md)
- [Procedures](procedures.md)
- [Processor](processor.md)
- [Repeat Blocks](repeat-blocks.md)
- [Scope](scope.md)
- [Segment](segments.md)
- [Simplified Segment](simplified-segment.md)
- [String](string.md)
- [Structure and Record](structure-and-record.md)

## x64

<table>
<tr><td><a href="dot-allocstack.md">.ALLOCSTACK</a></td><td><a href="dot-endprolog.md">.ENDPROLOG</a></td></tr>
<tr><td><a href="proc.md">PROC</a></td><td><a href="dot-pushframe.md">.PUSHFRAME</a></td></tr>
<tr><td><a href="dot-pushreg.md">.PUSHREG</a></td><td><a href="dot-savereg.md">.SAVEREG</a></td></tr>
<tr><td><a href="dot-savexmm128.md">.SAVEXMM128</a></td><td><a href="dot-setframe.md">.SETFRAME</a></td></tr>
</table>

## Code Labels

<table>
<tr><td><a href="align.md">ALIGN</a></td><td><a href="even.md">EVEN</a></td><td><a href="label.md">LABEL</a></td><td><a href="org.md">ORG</a></td></tr>
</table>

## Conditional Assembly

<table>
<tr><td><a href="defined.md">DEFINED</a></td><td><a href="else.md">ELSE</a></td><td><a href="elseif.md">ELSEIF</a></td></tr>
<tr><td><a href="elseif2.md">ELSEIF2</a></td><td><a href="if.md">IF</a></td><td><a href="if2.md">IF2</a></td></tr>
<tr><td><a href="ifb.md">IFB</a></td><td><a href="ifdef.md">IFDEF</a></td><td><a href="ifdif.md">IFDIF</a></td></tr>
<tr><td><a href="ifdif.md">IFDIFI</a></td><td><a href="ife.md">IFE</a></td><td><a href="ifidn.md">IFIDN</a></td></tr>
<tr><td><a href="ifidn.md">IFIDNI</a></td><td><a href="ifnb.md">IFNB</a></td><td><a href="ifndef.md">IFNDEF</a></td></tr>
</table>

## Conditional Control Flow

<table>
<tr><td><a href="dot-assert.md">.ASSERT</a></td><td><a href="dot-break.md">.BREAK</a></td><td><a href="dot-case.md">.CASE</a></td></tr>
<tr><td><a href="dot-class.md">.CLASS</a></td><td><a href="dot-continue.md">.CONTINUE</a></td><td><a href="dot-comdef.md">.COMDEF</a></td></tr>
<tr><td><a href="dot-default.md">.DEFAULT</a></td><td><a href="dot-else.md">.ELSE</a></td><td><a href="dot-if.md">.ELSEIF</a></td></tr>
<tr><td><a href="dot-endc.md">.ENDC</a></td><td><a href="dot-endf.md">.ENDF</a></td><td><a href="dot-endif.md">.ENDIF</a></td></tr>
<tr><td><a href="dot-endn.md">.ENDN</a></td><td><a href="dot-ends.md">.ENDS</a></td><td><a href="dot-endsw.md">.ENDSW</a></td></tr>
<tr><td><a href="dot-endw.md">.ENDW</a></td><td><a href="dot-enum.md">.ENUM</a></td><td><a href="dot-enumt.md">.ENUMT</a></td></tr>
<tr><td><a href="dot-for.md">.FOR</a></td><td><a href="dot-gotosw.md">.GOTOSW</a></td><td><a href="dot-if.md">.IF</a></td></tr>
<tr><td><a href="dot-inline.md">.INLINE</a></td><td><a href="dot-namespace.md">.NAMESPACE</a></td><td><a href="dot-new.md">.NEW</a></td></tr>
<tr><td><a href="dot-operator.md">.OPERATOR</a></td><td><a href="dot-repeat.md">.REPEAT</a></td><td><a href="dot-return.md">.RETURN</a></td></tr>
<tr><td><a href="dot-static.md">.STATIC</a></td><td><a href="dot-switch.md">.SWITCH</a></td><td><a href="dot-template.md">.TEMPLATE</a></td></tr>
<tr><td><a href="dot-until.md">.UNTIL</a></td><td><a href="dot-untilcxz.md">.UNTILCXZ</a></td><td><a href="dot-while.md">.WHILE</a></td></tr>
</table>

## Conditional Error

<table>
<tr><td><a href="dot-err.md">.ERR</a></td><td><a href="dot-err2.md">.ERR2</a></td><td><a href="dot-errb.md">.ERRB</a></td></tr>
<tr><td><a href="dot-errdef.md">.ERRDEF</a></td><td><a href="dot-errdif.md">.ERRDIF</a></td><td><a href="dot-errdif.md">.ERRDIFI</a></td></tr>
<tr><td><a href="dot-erre.md">.ERRE</a></td><td><a href="dot-erridn.md">.ERRIDN</a></td><td><a href="dot-erridn.md">.ERRIDNI</a></td></tr>
<tr><td><a href="dot-errnb.md">.ERRNB</a></td><td><a href="dot-errndef.md">.ERRNDEF</a></td><td><a href="dot-errnz.md">.ERRNZ</a></td></tr>
</table>

## Data Allocation

<table>
<tr><td><a href="byte.md">BYTE</a></td><td><a href="sbyte.md">SBYTE</a></td><td><a href="word.md">WORD</a></td></tr>
<tr><td><a href="sword.md">SWORD</a></td><td><a href="dword.md">DWORD</a></td><td><a href="sdword.md">SDWORD</a></td></tr>
<tr><td><a href="fword.md">FWORD</a></td><td><a href="qword.md">QWORD</a></td><td><a href="sqword.md">SQWORD</a></td></tr>
<tr><td><a href="tbyte.md">TBYTE</a></td><td><a href="oword.md">OWORD</a></td><td><a href="soword.md">SOWORD</a></td></tr>
<tr><td><a href="real2.md">REAL2</a></td><td><a href="real4.md">REAL4</a></td><td><a href="real8.md">REAL8</a></td></tr>
<tr><td><a href="real10.md">REAL10</a></td><td><a href="real16.md">REAL16</a></td><td><a href="mmword.md">MMWORD</a></td></tr>
<tr><td><a href="xmmword.md">XMMWORD</a></td><td><a href="ymmword.md">YMMWORD</a></td><td><a href="zmmword.md">ZMMWORD</a></td></tr>
</table>

## Equates

<table>
<tr><td><a href="equal.md">=</a></td><td><a href="define.md">DEFINE</a></td><td><a href="equ.md">EQU</a></td><td><a href="textequ.md">TEXTEQU</a></td><td><a href="undef.md">UNDEF</a></td>
</table>

## Inline Functions

<table>
<tr><td><a href="proto.md">PROTO</a></td><td><a href="dot-inline.md">.INLINE</a></td><td><a href="dot-static.md">.STATIC</a></td></tr>
</table>

## Instruction Format

<table>
<tr><td><a href="instruction-format.md">REP</a></td><td><a href="instruction-format.md">REPE</a></td><td><a href="instruction-format.md">REPZ</a></td></tr>
<tr><td><a href="instruction-format.md">REPNE</a></td><td><a href="instruction-format.md">REPNZ</a></td><td><a href="instruction-format.md">LOCK</a></td></tr>
<tr><td><a href="instruction-format.md">XACQUIRE</a></td><td><a href="instruction-format.md">XRELEASE</a></td><td><a href="instruction-format.md">VEX</a></td></tr>
<tr><td><a href="instruction-format.md">VEX2</a></td><td><a href="instruction-format.md">VEX3</a></td><td><a href="instruction-format.md">EVEX</a></td></tr>
</table>

## Listing Control

<table>
<tr><td><a href="dot-cref.md">.CREF</a></td><td><a href="dot-list.md">.LIST</a></td><td><a href="dot-listall.md">.LISTALL</a></td></tr>
<tr><td><a href="dot-listif.md">.LISTIF</a></td><td><a href="dot-listmacro.md">.LISTMACRO</a></td><td><a href="dot-listmacroall.md">.LISTMACROALL</a></td></tr>
<tr><td><a href="dot-nocref.md">.NOCREF</a></td><td><a href="dot-nolist.md">.NOLIST</a></td><td><a href="dot-nolistif.md">.NOLISTIF</a></td></tr>
<tr><td><a href="dot-nolistmacro.md">.NOLISTMACRO</a></td><td><a href="page.md">PAGE</a></td><td><a href="subtitle.md">SUBTITLE</a></td></tr>
<tr><td><a href="dot-tfcond.md">.TFCOND</a></td><td><a href="title.md">TITLE</a></td></tr>
</table>

## Macros

<table>
<tr><td><a href="endm.md">ENDM</a></td><td><a href="exitm.md">EXITM</a></td><td><a href="goto.md">GOTO</a></td><td><a href="local.md">LOCAL</a></td></tr>
<tr><td><a href="macro.md">MACRO</a></td><td><a href="purge.md">PURGE</a></td><td><a href="retm.md">RETM</a></td></tr>
</table>

## Miscellaneous

<table>
<tr><td><a href="alias.md">ALIAS</a></td><td><a href="assume.md">ASSUME</a></td><td><a href="comment.md">COMMENT</a></td></tr>
<tr><td><a href="echo.md">ECHO</a></td><td><a href="end.md">END</a></td><td><a href="include.md">INCLUDE</a></td></tr>
<tr><td><a href="includelib.md">INCLUDELIB</a></td><td><a href="option.md">OPTION</a></td><td><a href="popcontext.md">POPCONTEXT</a></td></tr>
<tr><td><a href="pushcontext.md">PUSHCONTEXT</a></td><td><a href="dot-radix.md">.RADIX</a></td><td><a href="dot-safeseh.md">.SAFESEH</a></td></tr>
<tr><td><a href="dot-pragma.md">.PRAGMA</a></td></tr>
</table>

## Procedures

<table>
<tr><td><a href="endp.md">ENDP</a></td><td><a href="invoke.md">INVOKE</a></td><td><a href="ldr.md">LDR</a></td><td><a href="proc.md">PROC</a></td><td><a href="proto.md">PROTO</a></td></tr>
</table>

## Processor

<table>
<tr><td><a href="processor.md">.8086</a></td><td><a href="processor.md">.8087</a></td><td><a href="processor.md">.NO87</a></td><td><a href="processor.md">.186</a></td><td><a href="processor.md">.286[p]</a></td></tr>
<tr><td><a href="processor.md">.287</a></td><td><a href="processor.md">.386[p]</a></td><td><a href="processor.md">.387</a></td><td><a href="processor.md">.486[p]</a></td><td><a href="processor.md">.586[p]</a></td></tr>
<tr><td><a href="processor.md">.686[p]</a></td><td><a href="processor.md">.K3D</a></td><td><a href="processor.md">.MMX</a></td><td><a href="processor.md">.XMM</a></td><td><a href="processor.md">.X64[p]</a></td></tr>
</table>

## Repeat Blocks

<table>
<tr><td><a href="endm.md">ENDM</a></td><td><a href="for.md">FOR</a></td><td><a href="forc.md">FORC</a></td><td><a href="goto.md">GOTO</a></td><td><a href="repeat.md">REPEAT</a></td><td><a href="while.md">WHILE</a></td></tr>
</table>

## Scope

<table>
<tr><td><a href="comm.md">COMM</a></td><td><a href="extern.md">EXTERN</a></td><td><a href="externdef.md">EXTERNDEF</a></td><td><a href="includelib.md">INCLUDELIB</a></td><td><a href="public.md">PUBLIC</a></td></tr>
</table>

## Segment

<table>
<tr><td><a href="dot-alpha.md">.ALPHA</a></td><td><a href="assume.md">ASSUME</a></td><td><a href="dot-dosseg.md">.DOSSEG</a></td></tr>
<tr><td><a href="end.md">END</a></td><td><a href="ends.md">ENDS</a></td><td><a href="group.md">GROUP</a></td></tr>
<tr><td><a href="dot-seq.md">.SEQ</a></td><td><a href="segment.md">SEGMENT</a></td></tr>
</table>

## Simplified Segment

<table>
<tr><td><a href="dot-code.md">.CODE</a></td><td><a href="dot-const.md">.CONST</a></td><td><a href="dot-data.md">.DATA</a></td></tr>
<tr><td><a href="dot-dataq.md">.DATA?</a></td><td><a href="dot-dosseg.md">.DOSSEG</a></td><td><a href="dot-exit.md">.EXIT</a></td></tr>
<tr><td><a href="dot-fardata.md">.FARDATA</a></td><td><a href="dot-fardataq.md">.FARDATA?</a></td><td><a href="dot-model.md">.MODEL</a></td></tr>
<tr><td><a href="dot-stack.md">.STACK</a></td><td><a href="dot-startup.md">.STARTUP</a></td></tr>
</table>

## String

<table>
<tr><td><a href="catstr.md">CATSTR</a></td><td><a href="instr.md">INSTR</a></td><td><a href="sizestr.md">SIZESTR</a></td><td><a href="substr.md">SUBSTR</a></td></tr>
</table>

## Structure and Record

<table>
<tr><td><a href="ends.md">ENDS</a></td><td><a href="record.md">RECORD</a></td><td><a href="struct.md">STRUCT</a></td><td><a href="typedef.md">TYPEDEF</a></td><td><a href="union.md">UNION</a></td></tr>
</table>

### See Also

[Asmc Reference](../readme.md) | [Symbols Reference](../symbol/readme.md)
