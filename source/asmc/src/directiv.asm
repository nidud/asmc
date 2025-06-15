; DIRECTIV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description:
;
; function               directive
;--------------------------------------------------
; EchoDirective()        ECHO
; IncludeDirective()     INCLUDE
; IncludeLibDirective()          INCLUDELIB
; IncBinDirective()      INCBIN
; AliasDirective()       ALIAS
; NameDirective()        NAME
; RadixDirective()       .RADIX
; SegOrderDirective()    .DOSSEG, .SEQ, .ALPHA
;

include asmc.inc
include memalloc.inc
include parser.inc
include segment.inc
include input.inc
include tokenize.inc
include expreval.inc
include types.inc
include fastpass.inc
include listing.inc
include omf.inc
include macro.inc

public directive_tab

res macro token, function
exitm<function proto __ccall :int_t, :token_t>
endm
include dirtype.inc
undef res

CCALLBACK(fpDirective, :int_t, :token_t)

.data

; table of function addresses for directives
res macro token, function
exitm<fpDirective function>
endm
directive_tab label fpDirective
include dirtype.inc
undef res

.code

    option proc:private

; should never be called

StubDir proc __ccall i:int_t, tokenarray:token_t

    mov eax,ERROR
    ret

StubDir endp


; handle ECHO directive.
; displays text on the console

EchoDirective proc __ccall i:int_t, tokenarray:token_t

    .if ( Parse_Pass == PASS_1 ) ; display in pass 1 only

        .if ( Options.preprocessor_stdout == FALSE ) ; don't print to stdout if -EP is on!

            ldr  ecx,i
            ldr  rdx,tokenarray
            imul ecx,ecx,asm_tok

            tprintf( "%s\n", [rdx+rcx+asm_tok].asm_tok.tokpos )
        .endif
    .endif
    mov eax,NOT_ERROR
    ret

EchoDirective endp


IncludeLibrary proc __ccall uses rsi rbx name:string_t

    ldr rsi,name

    ; old approach, <= 1.91: add lib name to global namespace
    ; new approach, >= 1.92: check lib table, if entry is missing, add it
    ; Masm doesn't map cases for the paths. So if there is
    ; includelib <kernel32.lib>
    ; includelib <KERNEL32.LIB>
    ; then 2 defaultlib entries are added. If this is to be changed for
    ; JWasm, activate the _stricmp() below.

    .for ( rbx = MODULE.LibQueue.head : rbx : rbx = [rbx].qitem.next )

        .if ( tstrcmp( &[rbx].qitem.value, rsi ) == 0 )

            .return( &[rbx].qitem.value )
        .endif
    .endf

    mov rbx,LclAlloc( &[tstrlen( rsi ) + sizeof( qitem )] )
    tstrcpy( &[rbx].qitem.value, rsi )
    QEnqueue( &MODULE.LibQueue, rbx )
    lea rax,[rbx].qitem.value
    ret

IncludeLibrary endp


    assume rbx:token_t

; INCLUDE directive.

; If a full path is specified, the directory where the included file
; is located becomes the "source" directory, that is, it is searched
; FIRST if further INCLUDE directives are found inside the included file.

IncludeDirective proc __ccall uses rbx i:int_t, tokenarray:token_t

    ldr rbx,tokenarray

    .if ( CurrFile[LST*string_t] )
        LstWriteSrcLine()
    .endif

    inc  i ; skip directive
    imul edx,i,asm_tok
    add  rdx,rbx

    ; v2.03: allow plain numbers as file name argument

    .if ( [rdx].asm_tok.token == T_FINAL )

        .return asmerr( 1017 )
    .endif

    ; if the filename is enclosed in <>, just use this literal

    .if ( [rdx].asm_tok.token == T_STRING && [rdx].asm_tok.string_delim == '<' )

        .if ( [rdx+asm_tok].asm_tok.token != T_FINAL )

            .return( asmerr(2008, [rdx+asm_tok].asm_tok.tokpos ) )
        .endif
        mov rcx,[rdx].asm_tok.string_ptr
    .else

        ; if the filename isn't enclosed in <>, use anything that comes
        ; after INCLUDE - and remove trailing white spaces.

        mov  rcx,[rdx].asm_tok.tokpos
        imul eax,TokenCount,asm_tok

        .for ( rdx = [rbx+rax].tokpos, rdx-- : rdx > rcx : rdx-- )

            .break .if !islspace( [rdx] )
            mov [rdx],ah
        .endf
    .endif
    .if SearchFile( rcx, TRUE )
        ProcessFile( rbx ) ; v2.11: process the file synchronously
    .endif
    .return( NOT_ERROR )

IncludeDirective endp


; INCLUDELIB directive.

IncludeLibDirective proc __ccall uses rbx i:int_t, tokenarray:token_t

    .if ( Parse_Pass != PASS_1 || Options.nolib )

        ; skip directive
        ; do all work in pass 1

        .return( NOT_ERROR )
    .endif

    ldr ecx,i
    ldr rbx,tokenarray

    inc  ecx ; skip the directive
    imul ecx,ecx,asm_tok

    ; v2.03: library name may be just a "number"

    .if ( [rbx+rcx].token == T_FINAL )

        ; v2.05: Masm doesn't complain if there's no name, so emit a warning only!

        asmerr( 8012 )
    .endif

    .if ( [rbx+rcx].token == T_STRING && [rbx+rcx].string_delim == '<' )

        .if ( [rbx+rcx+asm_tok].token != T_FINAL )
            .return asmerr( 2008, [rbx+rcx+asm_tok].tokpos )
        .endif
        mov rcx,[rbx+rcx].string_ptr

    .else

        ; regard "everything" behind INCLUDELIB as the library name

        mov rcx,[rbx+rcx].tokpos

        ; remove trailing white spaces

        imul eax,TokenCount,asm_tok

        .for ( rdx = [rbx+rax].tokpos, rdx-- : rdx > rcx : rdx-- )

            .break .if !islspace( [rdx] )
            mov [rdx],ah
        .endf
    .endif

    IncludeLibrary(rcx)
   .return( NOT_ERROR )

IncludeLibDirective endp


; INCBIN directive

IncBinDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

  local opndx:expr

    ldr rbx,tokenarray

    inc  i ; skip the directive
    imul eax,i,asm_tok
    add  rbx,rax

    .if ( [rbx].token == T_FINAL )

        .return asmerr( 1017 )
    .endif

    .if ( [rbx].token == T_STRING )

        ; v2.08: use string buffer to avoid buffer overflow if string is > FILENAME_MAX

        mov rdi,StringBufferEnd
        .if ( [rbx].string_delim == '"' || [rbx].string_delim == "'" )

            mov ecx,[rbx].stringlen
            mov rsi,[rbx].string_ptr
            inc rsi
            rep movsb
            mov byte ptr [rdi],0

        .elseif ( [rbx].string_delim == '<' )

            mov ecx,[rbx].stringlen
            mov rsi,[rbx].string_ptr
            inc ecx
            rep movsb
        .else
            .return( asmerr( 3015 ) )
        .endif
    .else
        .return( asmerr( 3015 ) )
    .endif

    xor esi,esi    ; fileoffset -- fixme: should be uint_64
    mov edi,-1     ; sizemax

    inc i
    add rbx,asm_tok
    .if ( [rbx].token == T_COMMA )

        inc i
        .return .ifd EvalOperand( &i, tokenarray, TokenCount, &opndx, 0 ) == ERROR

        .if ( opndx.kind == EXPR_CONST )
            mov esi,opndx.value
        .elseif ( opndx.kind != EXPR_EMPTY )
            .return( asmerr( 2026 ) )
        .endif
        imul ebx,i,asm_tok
        add rbx,tokenarray
        .if ( [rbx].token == T_COMMA )

            inc i
            .ifd ( EvalOperand( &i, tokenarray, TokenCount, &opndx, 0 ) == ERROR )
                .return
            .endif
            .if ( opndx.kind == EXPR_CONST )
                mov edi,opndx.value
            .elseif ( opndx.kind != EXPR_EMPTY )
                .return( asmerr( 2026 ) )
            .endif
        .endif
    .endif

    imul ebx,i,asm_tok
    add rbx,tokenarray

    .if ( [rbx].token != T_FINAL )
        .return asmerr( 2008, [rbx].tokpos )
    .endif
    .if ( CurrSeg == NULL )
        .return asmerr( 2034 )
    .endif

    ; v2.04: tell assembler that data is emitted

    .if ( MODULE.CommentDataInCode )
        omf_OutSelect( TRUE )
    .endif

    ; try to open the file

    .if SearchFile( StringBufferEnd, FALSE )

        ; transfer file content to the current segment.

        .new fp:ptr FILE = rax
        .new sizemax:int_t = edi

        .if rsi
            fseek( fp, rsi, SEEK_SET ) ; fixme: use fseek64()
        .endif

        .for ( : sizemax : sizemax-- )

            mov ebx,fgetc(fp)
            .if ebx == -1   ; EOF
                .break .if feof(fp)
            .endif
            OutputByte(bl)
        .endf
        fclose(fp)
    .endif
    .return( NOT_ERROR )

IncBinDirective endp


; Alias directive.
; Masm syntax is:
;   'ALIAS <alias_name> = <substitute_name>'
; which looks somewhat strange if compared to other Masm directives.
; (OW Wasm syntax is 'alias_name ALIAS substitute_name', which is
; what one might have expected for Masm as well).
;
; <alias_name> is a global name and must be unique (that is, NOT be
; defined elsewhere in the source!
; <substitute_name> is the name which is defined in the source.
; For COFF and ELF, this name MUST be defined somewhere as
; external or public!

    assume rsi:asym_t
    assume rdi:asym_t

AliasDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

  local subst:string_t

    ldr ecx,i
    ldr rbx,tokenarray

    inc  ecx ; go past ALIAS
    imul eax,ecx,asm_tok
    add  rbx,rax

    .if ( [rbx].token != T_STRING || [rbx].string_delim != '<' )
        .return asmerr( 2051 )
    .endif

    ; check syntax. note that '=' is T_DIRECTIVE && DRT_EQUALSGN

    .if ( [rbx+asm_tok].token != T_DIRECTIVE || [rbx+asm_tok].dirtype != DRT_EQUALSGN )
        .return( asmerr( 2008, [rbx+asm_tok].string_ptr ) )
    .endif
    .if ( [rbx+asm_tok*2].token != T_STRING || [rbx+asm_tok*2].string_delim != '<' )
        .return asmerr( 2051 )
    .endif
    mov subst,[rbx+asm_tok*2].string_ptr
    .if ( [rbx+asm_tok*3].token != T_FINAL )
        .return asmerr( 2008, [rbx+asm_tok*3].string_ptr )
    .endif

    ; make sure <alias_name> isn't defined elsewhere
    mov rsi,SymSearch([rbx].string_ptr)
    .if ( rsi == NULL || [rsi].state == SYM_UNDEFINED )

        ; v2.04b: adjusted to new field <substitute>
        mov rdi,SymSearch(subst)
        .if ( rdi == NULL )
            mov rdi,SymCreate(subst)
            mov [rdi].state,SYM_UNDEFINED
            sym_add_table(&SymTables[TAB_UNDEF*symbol_queue], rdi)
        .elseif ( [rdi].state != SYM_UNDEFINED && [rdi].state != SYM_INTERNAL &&
                  [rdi].state != SYM_EXTERNAL )
            .return( asmerr( 2217, subst ) )
        .endif
        .if ( rsi == NULL )
            mov rsi,SymCreate([rbx].string_ptr)
        .else
            sym_remove_table(&SymTables[TAB_UNDEF*symbol_queue], rsi)
        .endif

        mov [rsi].state,SYM_ALIAS
        mov [rsi].substitute,rdi
        ; v2.10: copy language type of alias
        mov [rsi].langtype,[rdi].langtype
        sym_add_table(&SymTables[TAB_ALIAS*symbol_queue], rsi) ; add ALIAS
       .return( NOT_ERROR )
    .endif
    xor eax,eax
    .if ( [rsi].state != SYM_ALIAS )
        inc eax
    .else
        mov rdi,[rsi].substitute
        tstrcmp( [rdi].name, subst )
    .endif
    .if eax
        .return( asmerr( 2005, [rsi].name) )
    .endif

    ; for COFF+ELF, make sure <actual_name> is "global" (EXTERNAL or
    ; public INTERNAL). For OMF, there's no check at all. */

    .if ( Parse_Pass != PASS_1 )
        .if ( Options.output_format == OFORMAT_COFF || Options.output_format == OFORMAT_ELF )
            mov rdi,[rsi].substitute
            .if ( [rdi].state == SYM_UNDEFINED )
                .return( asmerr(2006, subst) )
            .elseif ( [rdi].state != SYM_EXTERNAL &&
                       ( [rdi].state != SYM_INTERNAL || !( [rdi].ispublic ) ) )
                .return( asmerr(2217, subst) )
            .endif
        .endif
    .endif
    .return( NOT_ERROR )

AliasDirective endp


; the NAME directive is ignored in Masm v6

    assume rdx:token_t

NameDirective proc __ccall i:int_t, tokenarray:token_t

    .if ( Parse_Pass > PASS_1 )

        ldr ecx,i
        ldr rdx,tokenarray

        imul ecx,ecx,asm_tok
        lea rdx,[rdx+rcx+asm_tok]
        mov ecx,[rdx].tokval
        mov al,[rdx].token

        ; improper use of NAME is difficult to see since it is a nop
        ; therefore some syntax checks are implemented:
        ; - no 'name' structs, unions, records, typedefs!
        ; - no 'name' struct fields!
        ; - no 'name' segments!
        ; - no 'name:' label!

        .if ( CurrStruct != NULL || al == T_COLON || ( al == T_DIRECTIVE &&
              ( ecx == T_SEGMENT || ecx == T_STRUCT  || ecx == T_STRUC ||
                ecx == T_UNION   || ecx == T_TYPEDEF || ecx == T_RECORD ) ) )

            .return( asmerr( 2008, [rdx-asm_tok].tokpos ) )
        .endif

        ; don't touch Option fields! if anything at all, ModuleInfo.name may be modified.
        ; However, since the directive is ignored by Masm, nothing is done.
    .endif
    .return( NOT_ERROR )

NameDirective endp


; .RADIX directive, value must be between 2 .. 16

RadixDirective proc __ccall uses rbx i:int_t, tokenarray:token_t

   .new opndx:expr
   .new radix:byte

    ldr rbx,tokenarray

    ; to get the .radix parameter, enforce radix 10 and retokenize!

    mov radix,MODULE.radix
    mov MODULE.radix,10

    inc  i ; skip directive token
    imul ecx,i,asm_tok

    Tokenize( [rbx+rcx].tokpos, i, rbx, TOK_RESCAN )
    mov MODULE.radix,radix

    ; v2.11: flag NOUNDEF added - no forward ref possible

    .ifd EvalOperand(&i, rbx, TokenCount, &opndx, EXPF_NOUNDEF) == ERROR
        .return
    .endif
    .if ( opndx.kind != EXPR_CONST )
        .return asmerr( 2026 )
    .endif

    imul edx,i,asm_tok
    .if ( [rbx+rdx].token != T_FINAL )

        asmerr( 2008, [rbx+rdx].tokpos )

    .elseif ( opndx.value > 16 || opndx.value < 2 || opndx.hvalue != 0 )

        asmerr( 2113 )
    .else
        mov MODULE.radix,opndx.value
        mov eax,NOT_ERROR
    .endif
    ret

RadixDirective endp


; DOSSEG, .DOSSEG, .ALPHA, .SEQ directives

SegOrderDirective proc __ccall i:int_t, tokenarray:token_t

    ldr ecx,i
    ldr rdx,tokenarray

    imul ecx,ecx,asm_tok
    add rcx,rdx

    .if ( [rcx+asm_tok].asm_tok.token != T_FINAL )
        .return( asmerr(2008, [rcx+asm_tok].asm_tok.tokpos ) )
    .endif
    .if ( Options.output_format == OFORMAT_COFF || Options.output_format == OFORMAT_ELF ||
         ( Options.output_format == OFORMAT_BIN && MODULE.sub_format == SFORMAT_PE ) )
        .if ( Parse_Pass == PASS_1 )
            asmerr( 3006, tstrupr( [rcx].asm_tok.string_ptr ) )
        .endif
    .else
        mov MODULE.segorder,GetSflagsSp( [rcx].asm_tok.tokval )
    .endif
    .return( NOT_ERROR )

SegOrderDirective endp

    end
