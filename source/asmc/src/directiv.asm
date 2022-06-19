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

            imul edx,i,asm_tok
            add  rdx,tokenarray

            tprintf( "%s\n", [rdx+asm_tok].asm_tok.tokpos )
        .endif
    .endif
    mov eax,NOT_ERROR
    ret

EchoDirective endp


; INCLUDE directive.
; If a full path is specified, the directory where the included file
; is located becomes the "source" directory, that is, it is searched
; FIRST if further INCLUDE directives are found inside the included file.

IncludeDirective proc __ccall i:int_t, tokenarray:token_t

    .if ( CurrFile[LST*string_t] )
        LstWriteSrcLine()
    .endif

    inc  i ; skip directive
    imul eax,i,asm_tok
    add  rax,tokenarray

    ; v2.03: allow plain numbers as file name argument

    .return asmerr(1017) .if ( [rax].asm_tok.token == T_FINAL )

    ; if the filename is enclosed in <>, just use this literal

    .if ( [rax].asm_tok.token == T_STRING && [rax].asm_tok.string_delim == '<' )
        .if ( [rax+asm_tok].asm_tok.token != T_FINAL )
            .return( asmerr(2008, [rax+asm_tok].asm_tok.tokpos ) )
        .endif
        mov rcx,[rax].asm_tok.string_ptr
    .else
        ;
        ; if the filename isn't enclosed in <>, use anything that comes
        ; after INCLUDE - and remove trailing white spaces.
        ;
        mov  rcx,[rax].asm_tok.tokpos
        imul eax,Token_Count,asm_tok
        add  rax,tokenarray

        .for ( rdx = [rax].asm_tok.tokpos, rdx--: rdx > rcx: rdx-- )
            .break .if !islspace( [rdx] )
            mov [rdx],ah
        .endf
    .endif
    .if SearchFile( rcx, TRUE )
        ProcessFile( tokenarray ) ; v2.11: process the file synchronously
    .endif
    .return( NOT_ERROR )

IncludeDirective endp


IncludeLibrary proc __ccall uses rbx name:string_t

    ;struct qitem *q;

    ; old approach, <= 1.91: add lib name to global namespace
    ; new approach, >= 1.92: check lib table, if entry is missing, add it
    ; Masm doesn't map cases for the paths. So if there is
    ; includelib <kernel32.lib>
    ; includelib <KERNEL32.LIB>
    ; then 2 defaultlib entries are added. If this is to be changed for
    ; JWasm, activate the _stricmp() below.

    .for ( rbx = ModuleInfo.LibQueue.head: rbx: rbx = [rbx].qitem.next )

        .if ( tstrcmp( &[rbx].qitem.value, name ) == 0 )
            .return( &[rbx].qitem.value )
        .endif
    .endf

    mov rbx,LclAlloc( &[tstrlen( name ) + sizeof( qitem )] )
    tstrcpy( &[rbx].qitem.value, name )
    QEnqueue( &ModuleInfo.LibQueue, rbx )
    lea rax,[rbx].qitem.value
    ret

IncludeLibrary endp


; directive INCLUDELIB

    assume rbx:token_t

IncludeLibDirective proc __ccall uses rbx i:int_t, tokenarray:token_t

    mov eax,NOT_ERROR

    .return .if ( Options.nolib ) ; slip directive
    .return .if ( Parse_Pass != PASS_1 ) ; do all work in pass 1

    inc  i ; skip the directive
    imul ebx,i,asm_tok
    add  rbx,tokenarray

    ; v2.03: library name may be just a "number"

    .if ( [rbx].token == T_FINAL )

        ; v2.05: Masm doesn't complain if there's no name, so emit a warning only!

        asmerr( 8012 )
    .endif

    .if ( [rbx].token == T_STRING && [rbx].string_delim == '<' )

        .if ( [rbx+asm_tok].token != T_FINAL )
            .return asmerr( 2008, [rbx+asm_tok].tokpos )
        .endif
        mov rcx,[rbx].string_ptr
    .else
        ; regard "everything" behind INCLUDELIB as the library name
        mov rcx,[rbx].tokpos
        ; remove trailing white spaces
        imul ebx,Token_Count,asm_tok
        add rbx,tokenarray
        .for ( rdx = [rbx].tokpos, rdx--: rdx > rcx: rdx-- )
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

    inc i ; skip the directive
    imul ebx,i,asm_tok
    add rbx,tokenarray

    .return asmerr(1017) .if ( [rbx].token == T_FINAL )

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
        .return( asmerr( 3015 ) );
    .endif

    xor esi,esi    ; fileoffset -- fixme: should be uint_64
    mov edi,-1     ; sizemax

    inc i
    add rbx,asm_tok
    .if ( [rbx].token == T_COMMA )

        inc i
        .return .ifd EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR

        .if ( opndx.kind == EXPR_CONST )
            mov esi,opndx.value
        .elseif ( opndx.kind != EXPR_EMPTY )
            .return( asmerr( 2026 ) )
        .endif
        imul ebx,i,asm_tok
        add rbx,tokenarray
        .if ( [rbx].token == T_COMMA )
            inc i
            .return .ifd EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR
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
    .if ( ModuleInfo.CommentDataInCode )
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

    inc  i ; go past ALIAS
    imul ebx,i,asm_tok
    add  rbx,tokenarray

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
                       ( [rdi].state != SYM_INTERNAL || !( [rdi].flags & S_ISPUBLIC ) ) )
                .return( asmerr(2217, subst) )
            .endif
        .endif
    .endif
    .return( NOT_ERROR )

AliasDirective endp


; the NAME directive is ignored in Masm v6

    assume rdx:token_t

NameDirective proc __ccall i:int_t, tokenarray:token_t

    .if ( Parse_Pass != PASS_1 )
        .return( NOT_ERROR )
    .endif

    inc  i ; skip directive
    imul edx,i,asm_tok
    add  rdx,tokenarray

    ; improper use of NAME is difficult to see since it is a nop
    ; therefore some syntax checks are implemented:
    ; - no 'name' structs, unions, records, typedefs!
    ; - no 'name' struct fields!
    ; - no 'name' segments!
    ; - no 'name:' label!

    .if ( CurrStruct != NULL ||
        ( [rdx].token == T_DIRECTIVE &&
        ( [rdx].tokval == T_SEGMENT ||
          [rdx].tokval == T_STRUCT  ||
          [rdx].tokval == T_STRUC   ||
          [rdx].tokval == T_UNION   ||
          [rdx].tokval == T_TYPEDEF ||
          [rdx].tokval == T_RECORD ) ) || [rdx].token == T_COLON )

        .return( asmerr( 2008, [rdx-asm_tok].tokpos ) )
    .endif

    ; don't touch Option fields! if anything at all, ModuleInfo.name may be modified.
    ; However, since the directive is ignored by Masm, nothing is done.

    .return( NOT_ERROR )

NameDirective endp


; .RADIX directive, value must be between 2 .. 16

RadixDirective proc __ccall uses rbx i:int_t, tokenarray:token_t

  local opndx:expr

    ; to get the .radix parameter, enforce radix 10 and retokenize!

    mov  bl,ModuleInfo.radix
    mov  ModuleInfo.radix,10

    inc  i ; skip directive token
    imul ecx,i,asm_tok
    add  rcx,tokenarray

    Tokenize( [rcx].asm_tok.tokpos, i, tokenarray, TOK_RESCAN )
    mov ModuleInfo.radix,bl

    ; v2.11: flag NOUNDEF added - no forward ref possible

    .ifd EvalOperand(&i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF) == ERROR
        .return
    .endif
    .if ( opndx.kind != EXPR_CONST )
        .return asmerr( 2026 )
    .endif

    imul edx,i,asm_tok
    add rdx,tokenarray

    .if ( [rdx].token != T_FINAL )

        asmerr( 2008, [rdx].tokpos )

    .elseif ( opndx.value > 16 || opndx.value < 2 || opndx.hvalue != 0 )

        asmerr( 2113 )
    .else
        mov ModuleInfo.radix,opndx.value
        mov eax,NOT_ERROR
    .endif
    ret

RadixDirective endp


; DOSSEG, .DOSSEG, .ALPHA, .SEQ directives

SegOrderDirective proc __ccall i:int_t, tokenarray:token_t

    imul eax,i,asm_tok
    add rax,tokenarray

    .if ( [rax+asm_tok].asm_tok.token != T_FINAL )
        .return( asmerr(2008, [rax+asm_tok].asm_tok.tokpos ) )
    .endif
    .if ( Options.output_format == OFORMAT_COFF || Options.output_format == OFORMAT_ELF ||
         ( Options.output_format == OFORMAT_BIN && ModuleInfo.sub_format == SFORMAT_PE ) )
        .if ( Parse_Pass == PASS_1 )
            asmerr( 3006, tstrupr( [rax].asm_tok.string_ptr ) )
        .endif
    .else
        mov ModuleInfo.segorder,GetSflagsSp( [rax].asm_tok.tokval )
    .endif
    .return( NOT_ERROR )

SegOrderDirective endp

    end
