; CONDASM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description: ASMC conditional processing routines
;

include asmc.inc
include parser.inc
include condasm.inc
include reswords.inc
include expreval.inc
include listing.inc
include input.inc
include macro.inc
include types.inc
include fastpass.inc

;
; the current if-block can be in one of 3 states:
;  state              assembly     possible state change to
; ---------------------------------------------------------
;  inactive           off          active
;  active             on           done
;  done               off          -
;  --------------------------------------------------------
;  up to v2.04, there was a fourth state:
;  condition check    on           active, inactive
;  it was necessary because lines may have been tokenized multiple times.
;
.data
CurrIfState if_state 0
blocknestlevel int_t 0
falseblocknestlevel int_t 0
elseoccured uint_32 0   ; 2.06: bit field, magnitude must be >= MAX_IF_NESTING

.code

;
; this code runs after the first token has been scanned,
; if it is a IFx, ELSEx or ENDIF.
; updates variables <blocknestlevel> and <falseblocknestlevel>.
;

CondPrepare proc __ccall directive:int_t

    option switch:REGAX
    mov eax,directive
    .switch eax

    .case T_IF
    .case T_IF1
    .case T_IF2
    .case T_IFB
    .case T_IFDEF
    .case T_IFDIF
    .case T_IFDIFI
    .case T_IFE
    .case T_IFIDN
    .case T_IFIDNI
    .case T_IFNB
    .case T_IFNDEF
        .if ( CurrIfState != BLOCK_ACTIVE )
            inc falseblocknestlevel
            .endc
        .endif
        .if ( blocknestlevel == MAX_IF_NESTING )
            asmerr( 1007 )
            .endc
        .endif
        mov ecx,blocknestlevel
        mov eax,1
        shl eax,cl
        not eax
        and elseoccured,eax ; v2.06: added
        inc blocknestlevel
        .endc

    .case T_ELSE
    .case T_ELSEIF
    .case T_ELSEIF1
    .case T_ELSEIF2
    .case T_ELSEIFB
    .case T_ELSEIFDEF
    .case T_ELSEIFDIF
    .case T_ELSEIFDIFI
    .case T_ELSEIFE
    .case T_ELSEIFIDN
    .case T_ELSEIFIDNI
    .case T_ELSEIFNB
    .case T_ELSEIFNDEF

        .if ( blocknestlevel ) ; v2.04: do nothing if there was no IFx
            .endc .if ( falseblocknestlevel > 0 )

            ; v2.06: check added to detect multiple ELSE branches

            mov ecx,blocknestlevel
            dec ecx
            mov eax,1
            shl eax,cl
            .if ( elseoccured & eax )
                asmerr( 2142 )
                .endc
            .endif

            ; status may change:
            ; inactive -> active
            ; active   -> done

            mov eax,BLOCK_DONE
            .if ( CurrIfState == BLOCK_INACTIVE )
                mov eax,BLOCK_ACTIVE
            .endif
            mov CurrIfState,eax

            ; v2.06: no further ELSEx once ELSE was detected

            .if ( directive == T_ELSE )

                mov ecx,blocknestlevel
                dec ecx
                mov eax,1
                shl eax,cl
                or elseoccured,eax
            .endif
        .else
            asmerr( 1007 )
        .endif
        .endc
    .case T_ENDIF
        .if ( blocknestlevel )
            .if ( falseblocknestlevel > 0 )
                dec falseblocknestlevel
                .endc
            .endif
            dec blocknestlevel
            mov CurrIfState,BLOCK_ACTIVE ; v2.04: added
        .else
            asmerr( 1007 )
        .endif
        .endc
    .endsw
    ret
CondPrepare endp


; handle [ELSE]IF[N]DEF
; <string> is
; - the value of a T_ID item!
; - "" (item is T_FINAL)

check_defd proc fastcall private name:string_t

    xor eax,eax
    .if ( byte ptr [rcx] )

        .if SymSearch( rcx )
            mov eax,[rax].asym.flags
            and eax,S_ISDEFINED
        .endif
    .endif
    ret

check_defd endp


; handle [ELSE]IF[N]B

check_blank proc fastcall private string:string_t

    .for ( : byte ptr [rcx] : rcx++ )
        .return FALSE .if ( !islspace( [rcx] ) )
    .endf
    .return( TRUE )

check_blank endp


; Are two strings different?
; Used by [ELSE]IFDIF[I] and [ELSE]IFIDN[I]

check_dif proc __ccall private string1:string_t, string2:string_t, sensitive:int_t

    .if ( sensitive )
        tstrcmp( string1, string2 )
    .else
        tstricmp( string1, string2 )
    .endif
    ret

check_dif endp


    assume rbx:ptr asm_tok

CondAsmDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

  local opndx:expr
  local directive:int_t

    .if ( CurrIfState != BLOCK_ACTIVE )
        .if ( i || ModuleInfo.listif )
            LstWriteSrcLine()
        .endif
        .return( NOT_ERROR )
    .endif

    .if ( ModuleInfo.list == TRUE )
        .if ( MacroLevel == 0 ||
              ModuleInfo.list_macro == LM_LISTMACROALL ||
              ModuleInfo.listif )
            LstWriteSrcLine()
        .endif
    .endif

    imul ebx,i,asm_tok
    add rbx,tokenarray
    mov eax,[rbx].tokval

    inc i ; go past IFx, ELSEx, ENDIF
    add rbx,asm_tok

    ; check params and call appropriate test routine
    mov directive,eax
    mov eax,GetSflagsSp(eax)

    .switch( eax )

    .case CC_NUMARG ; [ELSE]IF[E]

        ; no forward reference allowed, symbol must be defined

        .ifd ( ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) == ERROR ) )

            mov opndx.kind,EXPR_CONST
            mov opndx.value,0
            mov i,Token_Count
        .endif

        imul ebx,i,asm_tok
        add rbx,tokenarray

        .if ( opndx.kind == EXPR_CONST )
            ;
        .elseif ( opndx.kind == EXPR_ADDR && !( opndx.flags & E_INDIRECT ) )
            mov rdx,opndx.sym
            add opndx.value,[rdx].asym.offs

            ; v2.07: Masm doesn't accept a relocatable item,
            ; so emit at least a warning!

            asmerr( 8020 )
        .else
            .return( asmerr( 2026 ) )
        .endif
        mov esi,BLOCK_INACTIVE
        .if ( directive == T_IF || directive == T_ELSEIF )
            .if ( opndx.value )
                mov esi,BLOCK_ACTIVE
            .endif
        .else
            .if ( !opndx.value )
                mov esi,BLOCK_ACTIVE
            .endif
        .endif
        .endc
    .case CC_LITARG ;  [ELSE]IFDIF[I], [ELSE]IFIDN[I]
        mov rsi,[rbx].string_ptr
        .if ( [rbx].token != T_STRING || [rbx].string_delim != '<' )
            SymSearch( rsi )
            .if ( !eax && [rbx].token == T_ID )
                asmerr( 2006, rsi )
            .else
                asmerr( 2051 )
            .endif
            .return( ERROR )
        .endif
        add rbx,asm_tok
        .if ( [rbx].token != T_COMMA )
            .return( asmerr( 2008, [rbx].tokpos ) )
        .endif
        add rbx,asm_tok
        mov rdi,[rbx].string_ptr
        .if ( [rbx].token != T_STRING || [rbx].string_delim != '<' )
            SymSearch( rdi )
            .if ( [rbx].token == T_ID && eax == NULL )
                asmerr( 2006, rdi )
            .else
                asmerr( 2051 )
            .endif
            .return( ERROR )
        .endif
        add rbx,asm_tok
        mov eax,directive

        .switch ( eax )
        .case T_IFDIF
        .case T_ELSEIFDIF
            .if check_dif( rsi, rdi, TRUE )
                mov esi,BLOCK_ACTIVE
            .else
                mov esi,BLOCK_INACTIVE
            .endif
            .endc
        .case T_IFDIFI
        .case T_ELSEIFDIFI
            .if check_dif( rsi, rdi, FALSE )
                mov esi,BLOCK_ACTIVE
            .else
                mov esi,BLOCK_INACTIVE
            .endif
            .endc
        .case T_IFIDN
        .case T_ELSEIFIDN
            .if !check_dif( rsi, rdi, TRUE )
                mov esi,BLOCK_ACTIVE
            .else
                mov esi,BLOCK_INACTIVE
            .endif
            .endc
        .default
            .if !check_dif( rsi, rdi, FALSE )
                mov esi,BLOCK_ACTIVE
            .else
                mov esi,BLOCK_INACTIVE
            .endif
        .endsw
        .endc
    .case CC_BLKARG ; [ELSE]IF[N]B
        mov rsi,[rbx].string_ptr
        .if ( [rbx].token != T_STRING || [rbx].string_delim != '<' )
            SymSearch( rsi )
            .if ( [rbx].token == T_ID && rax == NULL )
                asmerr( 2006, rsi )
            .else
                asmerr( 2051 )
            .endif
            .return( ERROR )
        .endif
        add rbx,asm_tok
        .if ( directive == T_IFB || directive == T_ELSEIFB )
            .if check_blank( rsi )
                mov esi,BLOCK_ACTIVE
            .else
                mov esi,BLOCK_INACTIVE
            .endif
        .else
            .if !check_blank( rsi )
                mov esi,BLOCK_ACTIVE
            .else
                mov esi,BLOCK_INACTIVE
            .endif
        .endif
        .endc

    .case CC_PASS1 ; [ELSE]IF1
        mov esi,BLOCK_ACTIVE
        .endc

    .case CC_PASS2 ; [ELSE]IF2
        .if ( ModuleInfo.setif2 == FALSE )
            asmerr( 2061 )
            .endc
        .endif
        ; v2.04: changed
        mov esi,BLOCK_ACTIVE
        .endc

    .case CC_SYMARG ; [ELSE]IF[N]DEF

        mov esi,BLOCK_INACTIVE

        ; Masm's implementation works with IDs as arguments only. The rest
        ; will return FALSE. However, it's nice to be able to check whether
        ; a reserved word is defined or not.
        ;
        ; v2.0: [ELSE]IF[N]DEF is valid *without* an argument!

        mov al,[rbx].token

        .if ( al == T_FINAL )
        .elseif ( al == T_ID  )

            ; v2.07: handle structs + members (if -Zne is NOT set)

            SymSearch( [rbx].string_ptr )
            .if ( ModuleInfo.strict_masm_compat == FALSE &&
                  [rbx+asm_tok].token == T_DOT && eax &&
                  ( ( [rax].asym.state == SYM_TYPE ) || [rax].asym.type ) )

                .repeat
                    add rbx,asm_tok
                    ; if it's a structured variable, use its type!
                    .if ( [rax].asym.state != SYM_TYPE )
                        mov rax,[rax].asym.type
                    .endif
                    mov rcx,rax
                    SearchNameInStruct( rcx, [rbx].string_ptr, 0, 0 )
                .until ( !( rax && [rbx+asm_tok].token == T_DOT ) )
                .if ( rax )
                    mov esi,BLOCK_ACTIVE
                .else
                    mov esi,BLOCK_INACTIVE
                .endif
            .else
                .if ( check_defd( [rbx].string_ptr ) )
                    mov esi,BLOCK_ACTIVE
                .else
                    mov esi,BLOCK_INACTIVE
                .endif
            .endif
            add rbx,asm_tok
        .elseif ( al == T_RES_ID && [rbx].tokval == T_FLAT )
            ; v2.09: special treatment of FLAT added
            mov rax,ModuleInfo.flat_grp
            .if ( rax && [rax].asym.flags & S_ISDEFINED )
                mov esi,BLOCK_ACTIVE
            .else
                mov esi,BLOCK_INACTIVE
            .endif
            add rbx,asm_tok
        .endif

        .if ( [rbx].token != T_FINAL )
            asmerr( 8005, [rbx-asm_tok].tokpos )
            .while ( [rbx].token != T_FINAL )
                add rbx,asm_tok
            .endw
        .endif
        .if ( directive == T_IFNDEF || directive == T_ELSEIFNDEF )
            .if ( esi == BLOCK_ACTIVE )
                mov esi,BLOCK_INACTIVE
            .else
                mov esi,BLOCK_ACTIVE
            .endif
        .endif
        .endc
    .default ; ELSE and ENDIF
        mov esi,BLOCK_ACTIVE
        .endc
    .endsw

    .if ( [rbx].token != T_FINAL )
        .return( asmerr(2008, [rbx].string_ptr ) )
    .endif

    mov CurrIfState,esi
    .return( NOT_ERROR )

CondAsmDirective endp


GetErrText proc __ccall private uses rbx i:int_t, tokenarray:ptr asm_tok

    imul ebx,i,asm_tok
    add rbx,tokenarray

    mov rcx,StringBufferEnd
    mov byte ptr [rcx],0
    .if ( i )
        .if ( [rbx].token != T_STRING || [rbx].string_delim != '<' )
            TextItemError( rbx )
        .else
            tstrcpy( rcx, [rbx].string_ptr )
        .endif
    .endif
    .return( StringBufferEnd )

GetErrText endp


; v2.05: the error directives are no longer handled in the
; preprocessor, because the errors are displayed in pass 2 only
; - .err        [<text>]
; - .err<1|2>   [<text>]
; - .err<e|nz>  expression [, <text>]
; - .errdif[i]  literal1, literal2 [, <text>]
; - .erridn[i]  literal1, literal2 [, <text>]
; - .err[n]b    text_literal [, <text>]
; - .err[n]def  symbol [, <text>]

ErrorDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

  local opndx:expr
  local direct:dword
  local errmsg:string_t
  local erridx:int_t
  local sym:ptr asym

    imul ebx,i,asm_tok
    add rbx,tokenarray
    mov edi,[rbx].tokval

    inc i ; go past directive
    add rbx,asm_tok

    ; get an expression if necessary

    mov eax,GetSflagsSp(edi)
    .switch( eax )

    .case CC_NUMARG ; .ERR[E|NZ]

        .return .ifd ( ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR ) )

        mov rdx,opndx.sym
        .if ( opndx.kind == EXPR_CONST )
        .elseif ( opndx.kind == EXPR_ADDR && !( opndx.flags & E_INDIRECT ) && \
            rdx && [rdx].asym.state == SYM_UNDEFINED )
        .else
            .return( asmerr( 2026 ) )
        .endif

        imul ebx,i,asm_tok
        add rbx,tokenarray
        xor ecx,ecx
        .if ( [rbx].token == T_COMMA && [rbx+asm_tok].token != T_FINAL )
            mov ecx,i
            inc ecx
            add rbx,asm_tok*2
        .endif
        .endc .if ( Parse_Pass == PASS_1 )

        xor esi,esi
        .if ( edi == T_DOT_ERRNZ && opndx.value )
            mov esi,2054
        .elseif ( edi == T_DOT_ERRE && !opndx.value )
            mov esi,2053
        .endif
        .if ( esi )
            asmerr( esi, opndx.value, GetErrText( ecx, tokenarray ) )
        .endif
        .endc

    .case CC_SYMARG ; .ERR[N]DEF

        ; there's a special handling of these directives in ExpandLine()!

        .if ( [rbx].token != T_ID )
            .return( asmerr(2008, [rbx].string_ptr ) )
        .endif

        ; skip the next param

        .repeat
            add rbx,asm_tok
        .until !( [rbx].token == T_DOT || [rbx].token == T_ID )
        .if ( [rbx].token == T_COMMA && [rbx+asm_tok].token != T_FINAL )
            add rbx,asm_tok*2
        .endif

        ; should run on pass 2 only!

        .endc .if ( Parse_Pass == PASS_1 )

        ; don't use check_defd()!
        ; v2.07: check for structured variables

        mov direct,edi
        imul edi,i,asm_tok
        add rdi,tokenarray
        mov sym,SymSearch( [rdi].asm_tok.string_ptr )

        .if ( ModuleInfo.strict_masm_compat == FALSE && \
              [rdi+asm_tok].asm_tok.token == T_DOT && \
              rax && ( ( [rax].asym.state == SYM_TYPE ) || [rax].asym.type ) )

            mov rsi,rdi
            .repeat

                add rsi,asm_tok*2

                ; if it's a structured variable, use its type!

                .if ( [rax].asym.state != SYM_TYPE )
                    mov rax,[rax].asym.type
                .endif
                mov rcx,rax
                SearchNameInStruct( rcx, [rsi].asm_tok.string_ptr, 0, 0 )
            .until !( rax && [rsi+asm_tok].asm_tok.token == T_DOT )

            .if ( [rsi].asm_tok.token == T_ID )
                add rsi,asm_tok
            .elseif ( [rsi].asm_tok.token != T_FINAL && [rsi].asm_tok.token != T_COMMA )
                .return( asmerr(2008, [rsi].asm_tok.string_ptr ) )
            .endif
            mov rcx,[rsi].asm_tok.tokpos
            mov rsi,[rdi].asm_tok.tokpos
            sub rcx,rsi
        .else
            mov rsi,[rdi].asm_tok.string_ptr
            mov rcx,[rdi+asm_tok].asm_tok.tokpos
            sub rcx,[rdi].asm_tok.tokpos
        .endif
        mov rdi,StringBufferEnd
        rep movsb
        mov byte ptr [rdi],0
        mov rax,sym
        .if ( rax && [rax].asym.state == SYM_UNDEFINED )
            xor eax,eax
        .endif

        ; Masm "usually" ignores the optional errtxt!

        .if ( direct == T_DOT_ERRDEF && rax != NULL )
            asmerr( 2056, StringBufferEnd )
        .elseif( direct == T_DOT_ERRNDEF && rax == NULL )
            asmerr( 2055, StringBufferEnd )
        .endif
        .endc

    .case CC_BLKARG ; .ERR[N]B
        mov rsi,[rbx].string_ptr
        .if ( [rbx].token != T_STRING || [rbx].string_delim != '<' )
            .return( TextItemError( rbx ) )
        .endif
        inc i
        add rbx,asm_tok
        xor ecx,ecx
        .if ( [rbx].token == T_COMMA && [rbx+asm_tok].token != T_FINAL )
            mov ecx,i
            inc ecx
            add rbx,asm_tok*2
        .endif
        .endc .if ( Parse_Pass == PASS_1 )
        mov erridx,ecx
        xor edx,edx
        .if ( edi == T_DOT_ERRB && check_blank( rsi ) )
            mov edx,2057
        .elseif ( edi == T_DOT_ERRNB && !check_blank( rsi ) )
            mov edx,2058
        .endif
        .if ( edx )
            mov edi,edx
            asmerr( edi, rsi, GetErrText( erridx, tokenarray ) )
        .endif
        .endc

    .case CC_LITARG ; .ERRDIF[I], .ERRIDN[I]

        mov rsi,[rbx].string_ptr
        .if ( [rbx].token != T_STRING || [rbx].string_delim != '<' )
            .return( TextItemError( rbx ) )
        .endif
        inc i
        add rbx,asm_tok
        .if ( [rbx].token != T_COMMA )
            .return( asmerr( 2008, [rbx].tokpos ) )
        .endif
        inc i
        add rbx,asm_tok
        mov rdx,[rbx].string_ptr
        .if ( [rbx].token != T_STRING || [rbx].string_delim != '<' )
            .return( TextItemError( rbx ) )
        .endif
        inc i
        add rbx,asm_tok
        xor ecx,ecx
        .if ( [rbx].token == T_COMMA && [rbx+asm_tok].token != T_FINAL )
            mov ecx,i
            inc ecx
            add rbx,asm_tok*2
        .endif
        .endc .if ( Parse_Pass == PASS_1 )

        mov erridx,ecx
        mov eax,edi
        xor edi,edi
        mov errmsg,rdx
        .switch ( eax )
        .case T_DOT_ERRDIF
            .if ( check_dif( rsi, rdx, TRUE ) )
                mov edi,2060
            .endif
            .endc
        .case T_DOT_ERRDIFI
            .if ( check_dif( rsi, rdx, FALSE ) )
                mov edi,2060
            .endif
            .endc
        .case T_DOT_ERRIDN
            .if ( !check_dif( rsi, rdx, TRUE ) )
                mov edi,2059
            .endif
            .endc
        .default
            .if ( !check_dif( rsi, rdx, FALSE ) )
                mov edi,2059
            .endif
        .endsw
        .if ( edi )
            asmerr( edi, rsi, errmsg, GetErrText( erridx, tokenarray ) )
        .endif
        .endc
    .case CC_PASS2  ; .ERR2
        .if ( ModuleInfo.setif2 == FALSE )
            .return( asmerr( 2061 ) )
        .endif
    .case CC_PASS1  ; .ERR1
    .default        ; .ERR
        xor ecx,ecx
        .if ( [rbx].token != T_FINAL )
            mov ecx,i
            add rbx,asm_tok
        .endif
        .endc .if ( Parse_Pass == PASS_1 )
        asmerr( 2052, GetErrText( ecx, tokenarray ) )
        .endc
    .endsw
    .if ( [rbx].token != T_FINAL )
        .return( asmerr(2008, [rbx].tokpos ) )
    .endif
    .return( NOT_ERROR )

ErrorDirective endp


CondCheckOpen proc __ccall

    .if ( blocknestlevel > 0 )
        asmerr( 1010, "if-else" )
    .endif
    ret
CondCheckOpen endp


GetIfNestLevel proc __ccall

    .return( blocknestlevel )

GetIfNestLevel endp

SetIfNestLevel proc __ccall newlevel:int_t

    mov blocknestlevel,newlevel
    ret

SetIfNestLevel endp


; init (called once per module)

CondInit proc __ccall

    xor eax,eax
    mov CurrIfState,eax
    mov blocknestlevel,eax
    mov falseblocknestlevel,eax
    ret

CondInit endp

    end
