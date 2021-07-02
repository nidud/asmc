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
exitm<function proto :int_t, :token_t>
endm
include dirtype.inc
undef res

CALLBACKC(fpDirective, :int_t, :token_t)

.data

;; table of function addresses for directives
res macro token, function
exitm<fpDirective function>
endm
directive_tab label fpDirective
include dirtype.inc
undef res

.code

    option proc:private

;; should never be called
StubDir proc i:int_t, tokenarray:token_t

    mov eax,ERROR
    ret

StubDir endp

;; handle ECHO directive.
;; displays text on the console

EchoDirective proc i:int_t, tokenarray:token_t

    .if ( Parse_Pass == PASS_1 ) ;; display in pass 1 only
        .if ( Options.preprocessor_stdout == FALSE ) ;; don't print to stdout if -EP is on!

            imul eax,i,asm_tok
            add eax,tokenarray
            printf( "%s\n", [eax+16].asm_tok.tokpos )
        .endif
    .endif
    mov eax,NOT_ERROR
    ret

EchoDirective endp

;; INCLUDE directive.
;; If a full path is specified, the directory where the included file
;; is located becomes the "source" directory, that is, it is searched
;; FIRST if further INCLUDE directives are found inside the included file.

IncludeDirective proc i:int_t, tokenarray:token_t

    .if ( CurrFile[LST*4] )
        LstWriteSrcLine()
    .endif

    inc i ;; skip directive
    imul eax,i,asm_tok
    add eax,tokenarray
    ;; v2.03: allow plain numbers as file name argument
    .return asmerr(1017) .if ( [eax].asm_tok.token == T_FINAL )

    ;; if the filename is enclosed in <>, just use this literal

    .if ( [eax].asm_tok.token == T_STRING && [eax].asm_tok.string_delim == '<' )
        .if ( [eax+16].asm_tok.token != T_FINAL )
            .return( asmerr(2008, [eax+16].asm_tok.tokpos ) )
        .endif
        mov ecx,[eax].asm_tok.string_ptr
    .else
        ;
        ; if the filename isn't enclosed in <>, use anything that comes
        ; after INCLUDE - and remove trailing white spaces.
        ;
        mov  ecx,[eax].asm_tok.tokpos
        imul eax,Token_Count,asm_tok
        add  eax,tokenarray

        .for ( edx = [eax].asm_tok.tokpos, edx--: edx > ecx: edx-- )
            .break .if !islspace( [edx] )
            mov [edx],ah
        .endf
    .endif
    .if SearchFile( ecx, TRUE )
        ProcessFile( tokenarray ) ;; v2.11: process the file synchronously
    .endif
    mov eax,NOT_ERROR
    ret

IncludeDirective endp

IncludeLibrary proc uses ebx name:string_t

    ;struct qitem *q;

    ;; old approach, <= 1.91: add lib name to global namespace
    ;; new approach, >= 1.92: check lib table, if entry is missing, add it
    ;; Masm doesn't map cases for the paths. So if there is
    ;; includelib <kernel32.lib>
    ;; includelib <KERNEL32.LIB>
    ;; then 2 defaultlib entries are added. If this is to be changed for
    ;; JWasm, activate the _stricmp() below.

    .for ( ebx = ModuleInfo.LibQueue.head: ebx: ebx = [ebx].qitem.next )

        .return(&[ebx].qitem.value) .if ( strcmp(&[ebx].qitem.value, name) == 0 )
    .endf

    mov ebx,LclAlloc( &[strlen( name ) + sizeof( qitem )] )
    strcpy( &[ebx].qitem.value, name )
    QEnqueue( &ModuleInfo.LibQueue, ebx )
    lea eax,[ebx].qitem.value
    ret

IncludeLibrary endp

;; directive INCLUDELIB

    assume ebx:token_t

IncludeLibDirective proc uses ebx i:int_t, tokenarray:token_t

    mov eax,NOT_ERROR
    .return .if ( Options.nolib ) ;; slip directive
    .return .if ( Parse_Pass != PASS_1 ) ;; do all work in pass 1

    inc i ;; skip the directive
    imul ebx,i,asm_tok
    add ebx,tokenarray
    ;; v2.03: library name may be just a "number"
    .if ( [ebx].token == T_FINAL )
        ;; v2.05: Masm doesn't complain if there's no name, so emit a warning only!
        asmerr( 8012 )
    .endif

    .if ( [ebx].token == T_STRING && [ebx].string_delim == '<' )
        .return asmerr(2008, [ebx+16].tokpos) .if ( [ebx+16].token != T_FINAL )
        mov ecx,[ebx].string_ptr
    .else
        ;; regard "everything" behind INCLUDELIB as the library name
        mov ecx,[ebx].tokpos
        ;; remove trailing white spaces
        imul ebx,Token_Count,asm_tok
        add ebx,tokenarray
        .for ( edx = [ebx].tokpos, edx--: edx > ecx: edx-- )
            .break .if !islspace( [edx] )
            mov [edx],ah
        .endf
    .endif

    IncludeLibrary(ecx)
    mov eax,NOT_ERROR
    ret

IncludeLibDirective endp

;; INCBIN directive

IncBinDirective proc uses esi edi ebx i:int_t, tokenarray:token_t

  local opndx:expr

    inc i ;; skip the directive
    imul ebx,i,asm_tok
    add ebx,tokenarray

    .return asmerr(1017) .if ( [ebx].token == T_FINAL )

    .if ( [ebx].token == T_STRING )

        ;; v2.08: use string buffer to avoid buffer overflow if string is > FILENAME_MAX
        mov edi,StringBufferEnd
        .if ( [ebx].string_delim == '"' || [ebx].string_delim == "'" )

            mov ecx,[ebx].stringlen
            mov esi,[ebx].string_ptr
            inc esi
            rep movsb
            mov byte ptr [edi],0

        .elseif ( [ebx].string_delim == '<' )

            mov ecx,[ebx].stringlen
            mov esi,[ebx].string_ptr
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
    add ebx,16
    .if ( [ebx].token == T_COMMA )

        inc i
        .return .if EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR

        .if ( opndx.kind == EXPR_CONST )
            mov esi,opndx.value
        .elseif ( opndx.kind != EXPR_EMPTY )
            .return( asmerr( 2026 ) )
        .endif
        imul ebx,i,asm_tok
        add ebx,tokenarray
        .if ( [ebx].token == T_COMMA )
            inc i
            .return .if EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR
            .if ( opndx.kind == EXPR_CONST )
                mov edi,opndx.value
            .elseif ( opndx.kind != EXPR_EMPTY )
                .return( asmerr( 2026 ) )
            .endif
        .endif
    .endif
    imul ebx,i,asm_tok
    add ebx,tokenarray
    .return asmerr(2008, [ebx].tokpos) .if ( [ebx].token != T_FINAL )
    .return asmerr(2034) .if ( CurrSeg == NULL )

    ;; v2.04: tell assembler that data is emitted
    .if ( ModuleInfo.CommentDataInCode )
        omf_OutSelect( TRUE )
    .endif

    ;; try to open the file

    .if SearchFile( StringBufferEnd, FALSE )

        ;; transfer file content to the current segment.

        xchg eax,esi
        .if eax

            fseek( esi, eax, SEEK_SET ) ;; fixme: use fseek64()
        .endif

        .for ( : edi : edi-- )

            mov ebx,fgetc(esi)
            .if ebx == -1   ; EOF
                .break .if feof(esi)
            .endif
            OutputByte(bl)
        .endf
        fclose(esi)
    .endif
    mov eax,NOT_ERROR
    ret

IncBinDirective endp

;; Alias directive.
;; Masm syntax is:
;;   'ALIAS <alias_name> = <substitute_name>'
;; which looks somewhat strange if compared to other Masm directives.
;; (OW Wasm syntax is 'alias_name ALIAS substitute_name', which is
;; what one might have expected for Masm as well).
;;
;; <alias_name> is a global name and must be unique (that is, NOT be
;; defined elsewhere in the source!
;; <substitute_name> is the name which is defined in the source.
;; For COFF and ELF, this name MUST be defined somewhere as
;; external or public!

    assume esi:asym_t
    assume edi:asym_t

AliasDirective proc uses esi edi ebx i:int_t, tokenarray:token_t

    local subst:string_t

    inc i ;; go past ALIAS
    imul ebx,i,asm_tok
    add ebx,tokenarray

    .return asmerr(2051) .if ( [ebx].token != T_STRING || [ebx].string_delim != '<' )

    ;; check syntax. note that '=' is T_DIRECTIVE && DRT_EQUALSGN
    .return( asmerr(2008, [ebx+16].string_ptr) ) \
        .if ( [ebx+16].token != T_DIRECTIVE || [ebx+16].dirtype != DRT_EQUALSGN )
    .return asmerr(2051) .if ( [ebx+32].token != T_STRING || [ebx+32].string_delim != '<' )
    mov subst,[ebx+32].string_ptr
    .return asmerr(2008, [ebx+48].string_ptr) .if ( [ebx+48].token != T_FINAL )

    ;; make sure <alias_name> isn't defined elsewhere
    mov esi,SymSearch([ebx].string_ptr)
    .if ( esi == NULL || [esi].state == SYM_UNDEFINED )

        ;; v2.04b: adjusted to new field <substitute>
        mov edi,SymSearch(subst)
        .if ( edi == NULL )
            mov edi,SymCreate(subst)
            mov [edi].state,SYM_UNDEFINED
            sym_add_table(&SymTables[TAB_UNDEF*symbol_queue], edi)
        .elseif ( [edi].state != SYM_UNDEFINED && [edi].state != SYM_INTERNAL && \
                  [edi].state != SYM_EXTERNAL )
            .return( asmerr(2217, subst) )
        .endif
        .if ( esi == NULL )
            mov esi,SymCreate([ebx].string_ptr)
        .else
            sym_remove_table(&SymTables[TAB_UNDEF*symbol_queue], esi)
        .endif

        mov [esi].state,SYM_ALIAS
        mov [esi].substitute,edi
        ;; v2.10: copy language type of alias
        mov [esi].langtype,[edi].langtype
        sym_add_table(&SymTables[TAB_ALIAS*symbol_queue], esi) ;; add ALIAS
        .return(NOT_ERROR)
    .endif
    xor eax,eax
    .if ( [esi].state != SYM_ALIAS )
        inc eax
    .else
        mov edi,[esi].substitute
        strcmp( [edi].name, subst )
    .endif
    .return( asmerr(2005, [esi].name) ) .if eax
    ;; for COFF+ELF, make sure <actual_name> is "global" (EXTERNAL or
    ;; public INTERNAL). For OMF, there's no check at all. */
    .if ( Parse_Pass != PASS_1 )
        .if ( Options.output_format == OFORMAT_COFF || Options.output_format == OFORMAT_ELF )
            mov edi,[esi].substitute
            .if ( [edi].state == SYM_UNDEFINED )
                .return( asmerr(2006, subst) )
            .elseif ( [edi].state != SYM_EXTERNAL && \
                       ( [edi].state != SYM_INTERNAL || !( [edi].flags & S_ISPUBLIC ) ) )
                .return( asmerr(2217, subst) )
            .endif
        .endif
    .endif
    mov eax,NOT_ERROR
    ret

AliasDirective endp

;; the NAME directive is ignored in Masm v6

    assume edx:token_t

NameDirective proc i:int_t, tokenarray:token_t

    .return(NOT_ERROR) .if ( Parse_Pass != PASS_1 )

    inc i ;; skip directive
    imul edx,i,asm_tok
    add edx,tokenarray

    ;; improper use of NAME is difficult to see since it is a nop
    ;; therefore some syntax checks are implemented:
    ;; - no 'name' structs, unions, records, typedefs!
    ;; - no 'name' struct fields!
    ;; - no 'name' segments!
    ;; - no 'name:' label!

    .if ( CurrStruct != NULL || \
        ( [edx].token == T_DIRECTIVE && \
        ( [edx].tokval == T_SEGMENT || \
          [edx].tokval == T_STRUCT  || \
          [edx].tokval == T_STRUC   || \
          [edx].tokval == T_UNION   || \
          [edx].tokval == T_TYPEDEF || \
          [edx].tokval == T_RECORD ) ) || [edx].token == T_COLON )
        .return( asmerr(2008, [edx-16].tokpos) )
    .endif

    ;; don't touch Option fields! if anything at all, ModuleInfo.name may be modified.
    ;; However, since the directive is ignored by Masm, nothing is done.

    mov eax,NOT_ERROR
    ret

NameDirective endp

;; .RADIX directive, value must be between 2 .. 16

RadixDirective proc uses ebx i:int_t, tokenarray:token_t

  local opndx:expr

    ;; to get the .radix parameter, enforce radix 10 and retokenize!
    mov bl,ModuleInfo.radix
    mov ModuleInfo.radix,10
    inc i ;; skip directive token
    imul edx,i,asm_tok
    add edx,tokenarray

    Tokenize([edx].tokpos, i, tokenarray, TOK_RESCAN)
    mov ModuleInfo.radix,bl

    ;; v2.11: flag NOUNDEF added - no forward ref possible
    .return .if EvalOperand(&i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF) == ERROR
    .return asmerr(2026) .if ( opndx.kind != EXPR_CONST )

    imul edx,i,asm_tok
    add edx,tokenarray

    .if ( [edx].token != T_FINAL )

        asmerr(2008, [edx].tokpos)

    .elseif ( opndx.value > 16 || opndx.value < 2 || opndx.hvalue != 0 )

        asmerr(2113)

    .else

        mov ModuleInfo.radix,opndx.value
        mov eax,NOT_ERROR
    .endif
    ret

RadixDirective endp

;; DOSSEG, .DOSSEG, .ALPHA, .SEQ directives

SegOrderDirective proc i:int_t, tokenarray:token_t

    imul eax,i,asm_tok
    add eax,tokenarray

    .if ( [eax+16].asm_tok.token != T_FINAL )
        .return( asmerr(2008, [eax+16].asm_tok.tokpos ) )
    .endif
    .if ( Options.output_format == OFORMAT_COFF || Options.output_format == OFORMAT_ELF || \
        ( Options.output_format == OFORMAT_BIN && ModuleInfo.sub_format == SFORMAT_PE ) )
        .if ( Parse_Pass == PASS_1 )
            asmerr( 3006, _strupr( [eax].asm_tok.string_ptr ) )
        .endif
    .else
        mov ModuleInfo.segorder,GetSflagsSp( [eax].asm_tok.tokval )
    .endif

    mov eax,NOT_ERROR
    ret

SegOrderDirective endp

    end
