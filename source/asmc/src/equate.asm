; EQUATE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; handles EQU and '=' directives.
;

include asmc.inc
include memalloc.inc
include parser.inc
include expreval.inc
include equate.inc
include tokenize.inc
include macro.inc
include fastpass.inc
include listing.inc
include input.inc
include fixup.inc
include qfloat.inc
include operator.inc

;public maxintvalues
;public minintvalues

    .data
     maxintvalues int64_t 0x00000000ffffffff, 0x00000000ffffffff, 0x7fffffffffffffff
     minintvalues int64_t 0xffffffff00000000, 0xffffffff00000000, 0x8000000000000000

    .code

; set the value of a constant (EQU) or an assembly time variable (=)

    assume rdx:expr_t
    assume rcx:asym_t
    assume rdi:asym_t
    assume rbx:token_t

SetValue proc fastcall private uses rdi _sym:asym_t, opndx:expr_t

    mov [rcx].state,SYM_INTERNAL
    or  [rcx].flags,S_ISEQUATE or S_ISDEFINED
    and [rcx].flags,not S_ISPROC

    .if ( [rdx].kind == EXPR_CONST ||
         ( [rdx].kind == EXPR_FLOAT && [rdx].float_tok == NULL ) )

        mov [rcx].uvalue,[rdx].uvalue
        mov [rcx].value3264,[rdx].hvalue
        mov [rcx].mem_type,[rdx].mem_type
        .if al == MT_REAL16 && !Options.strict_masm_compat
            mov [rcx].total_length,dword ptr [rdx].hlvalue
            mov [rcx].ext_idx,dword ptr [rdx].hlvalue[4]
        .endif
        mov [rcx].segm,NULL
       .return
    .endif

    ; for a PROC alias, copy the procinfo extension!

    mov rdi,[rdx].sym
    .if [rdi].flags & S_ISPROC

        or  [rcx].flags,S_ISPROC
        ; v2.12: must be copied as well, or INVOKE won't work correctly
        mov [rcx].langtype,[rdi].langtype
        assume rcx:dsym_t
        assume rdi:dsym_t
        mov [rcx].procinfo,[rdi].procinfo
        assume rcx:asym_t
        assume rdi:asym_t
    .endif

    mov [rcx].mem_type,[rdx].mem_type

    ; v2.01: allow equates of variables with arbitrary type.
    ; Currently the expression evaluator sets opndx.mem_type
    ; to the mem_type of the type (i.e. QWORD for a struct with size 8),
    ; which is a bad idea in this case. So the original mem_type of the
    ; label is used instead.

    .if ( [rdi].mem_type == MT_TYPE && !( [rdx].flags & E_EXPLICIT ) )

        mov [rcx].mem_type,[rdi].mem_type
        mov [rcx].type,[rdi].type
    .endif
    mov [rcx].value3264,0 ;; v2.09: added
    mov [rcx].segm,[rdi].segm

    ; labels are supposed to be added to the current segment's label_list chain.
    ; this isn't done for alias equates, for various reasons.
    ; consequently, if the alias was forward referenced, ensure that a third pass
    ; will be done! regression test forward5.asm.

    mov eax,[rdi].offs
    add eax,[rdx].value
    .if [rcx].flags & S_VARIABLE
        mov [rcx].offs,eax
        .if Parse_Pass == PASS_2 && ( [rcx].flags & S_FWDREF )
            mov ModuleInfo.PhaseError,TRUE
        .endif
    .else
        .if Parse_Pass != PASS_1 && [rcx].offs != eax
            mov ModuleInfo.PhaseError,TRUE
        .endif
        mov [rcx].offs,eax
        BackPatch(rcx)
    .endif
    ret

SetValue endp

; the '=' directive defines an assembly time variable.
; this can only be a number (constant or relocatable).

CreateAssemblyTimeVariable proc __ccall private uses rsi rdi rbx tokenarray:token_t

    local sym:asym_t
    local name:string_t
    local i:int_t
    local opnd:expr
    local opn2:expr

    mov i,2
    ldr rbx,tokenarray
    mov name,[rbx].string_ptr
    add rbx,2*asm_tok

    ; v2.08: for plain numbers ALWAYS avoid to call evaluator

    .if ( [rbx].token == T_NUM && [rbx+asm_tok].token == T_FINAL )

        _atoow( &opnd, [rbx].string_ptr, [rbx].numbase, [rbx].itemlen )

check_number:

        mov opnd.kind,EXPR_CONST
        mov opnd.mem_type,MT_EMPTY ;; v2.07: added
        .l8 opnd.hlvalue
ifndef _WIN64
        or eax,edx
endif
        ; v2.08: check added. the number must be 32-bit

        .if ( !rax )

            movzx   ecx,ModuleInfo.Ofssize
            lea     rsi,minintvalues
            lea     rdi,maxintvalues
          ifdef _WIN64
            mov     rdx,opnd.llvalue
            cmp     rdx,[rsi+rcx*int64_t]
            setl    al
            cmp     rdx,[rdi+rcx*int64_t]
            setg    ah
          else
            mov edx,opnd.hvalue
            mov ebx,opnd.value
            .if ( ( sdword ptr edx < [esi+ecx*int64_t][4] || ( ZERO? && ebx < [esi+ecx*int64_t] ) ) ||
                  ( sdword ptr edx > [edi+ecx*int64_t][4] || ( ZERO? && ebx > [edi+ecx*int64_t] ) ) )
                inc al
            .endif
          endif
        .endif
        .if rax
            EmitConstError(&opnd)
           .return NULL
        .endif
    .else

        ; v2.09: don't create not-(yet)-defined symbols. Example:
        ; E1 = E1 or 1
        ; must NOT create E1.

        .return .ifd EvalOperand( &i, tokenarray, TokenCount, &opnd, 0 ) == ERROR

        imul ebx,i,asm_tok
        add rbx,tokenarray
        .if ( [rbx].token != T_FINAL )

            asmerr( 2008, [rbx].string_ptr )
           .return NULL
        .endif

        ; expression may be a constant or a relocatable item.
        ; v2.09: kind may be EXPR_CONST and still include an undefined symbol.
        ; This is caused by MakeConst() in expreval.c. Brackets changed so
        ; opnd.sym is also checked for opnd.kind == EXPR_CONST.

        mov rcx,opnd.sym
        .if ( opnd.kind != EXPR_CONST &&
             ( opnd.kind != EXPR_ADDR || ( opnd.flags & E_INDIRECT ) ) ||
             ( rcx != NULL && [rcx].state != SYM_INTERNAL ) )

            ; v2.09: no error if argument is a forward reference,
            ; but don't create the variable either. Will enforce an
            ; error if referenced symbol is still undefined in pass 2.

            .if ( rcx && [rcx].state == SYM_UNDEFINED && !( opnd.flags & E_INDIRECT ) )
                .if StoreState == FALSE
                    FStoreLine(0) ;; make sure this line is evaluated in pass two
                .endif

            .elseif ( !rcx && opnd.kind == EXPR_FLOAT && !Options.strict_masm_compat )

                mov opnd.mem_type,MT_REAL16
                mov opnd.kind,EXPR_CONST
                mov opnd.float_tok,NULL
                jmp check_float
            .else
                mov i,0
                .ifd ( EvalOperand( &i, tokenarray, 1, &opn2, 0 ) != ERROR )
                    mov rcx,tokenarray
                    add rcx,asm_tok
                    .ifd ( EvalOperator( &opn2, &opnd, rcx ) != ERROR )
                        .ifd ( ParseOperator( tokenarray, opn2.op ) != ERROR )
                            mov rax,opn2.sym
                            .return ;opn2.sym
                        .endif
                    .endif
                .endif
                asmerr(2026)
            .endif
            .return NULL
        .endif

        ; v2.08: accept any result that fits in 64-bits from expression evaluator
        .if ( dword ptr opnd.hlvalue || dword ptr opnd.hlvalue[4] )
            EmitConstError(&opnd)
           .return NULL
        .endif
        ; for quoted strings, the same restrictions as for plain numbers apply
        .if ( opnd.quoted_string )
            jmp check_number
        .endif
    .endif

check_float:

    mov rdi,SymSearch(name)

    .if ( rdi == NULL || [rdi].state == SYM_UNDEFINED )
        .if rdi == NULL
            mov rdi,SymCreate(name)
        .else
            sym_remove_table(&SymTables[TAB_UNDEF*symbol_queue], rdi)
            or [rdi].flags,S_FWDREF
        .endif
        and [rdi].flags,not S_ISSAVED
        .if StoreState
            or [rdi].flags,S_ISSAVED
        .endif
    .elseif ( [rdi].state == SYM_EXTERNAL && [rdi].sflags & S_WEAK && [rdi].mem_type == MT_EMPTY )
        sym_ext2int(rdi)
        and [rdi].flags,not S_ISSAVED
        .if StoreState
            or [rdi].flags,S_ISSAVED
        .endif
    .else
        .if ( [rdi].state != SYM_INTERNAL || ( !( [rdi].flags & S_VARIABLE ) &&
             ( opnd.uvalue != [rdi].uvalue || opnd.hvalue != [rdi].value3264 ) ) )
            asmerr( 2005, [rdi].name )
           .return NULL
        .endif

        ; v2.04a regression in v2.04. Do not save the variable when it
        ; is defined the first time
        ; v2.10: store state only when variable is changed and has been
        ; defined BEFORE SaveState() has been called.

        .if ( StoreState && !( [rdi].flags & S_ISSAVED ) )
            SaveVariableState(rdi)
        .endif
    .endif
    or byte ptr [rdi].flags,S_VARIABLE
    ; v2.09: allow internal variables to be set
    .if ( ( byte ptr [rdi].flags & S_PREDEFINED ) && [rdi].sfunc_ptr )
        [rdi].sfunc_ptr( rdi, &opnd )
    .else
        SetValue( rdi, &opnd )
    .endif
    .return( rdi )

CreateAssemblyTimeVariable endp


; '=' directive.

    assume rdx:token_t

EqualSgnDirective proc __ccall i:int_t, tokenarray:token_t

    ldr rdx,tokenarray
    .if [rdx].token != T_ID
        .return asmerr( 2008, [rdx].string_ptr )
    .endif
    .if CreateAssemblyTimeVariable(rdx)
        .if ( ModuleInfo.list == TRUE )
            LstWrite(LSTTYPE_EQUATE, 0, rax)
        .endif
        .return NOT_ERROR
    .endif
    .return( ERROR )

EqualSgnDirective endp


; CreateVariable().
; define an assembly time variable directly without using the token buffer.
; this is used for some internally generated variables (SIZESTR, INSTR, @Cpu)
; NO listing is written! The value is ensured to be max 16-bit wide.

CreateVariable proc __ccall uses rdi name:string_t, value:int_t

    mov rdi,SymSearch(name)
    .if rdi == NULL
        mov rdi,SymCreate(name)
        and [rdi].flags,not S_ISSAVED
        .if StoreState
            or [rdi].flags,S_ISSAVED
        .endif
    .elseif [rdi].state == SYM_UNDEFINED
        sym_remove_table( &SymTables[TAB_UNDEF*symbol_queue], rdi)
        or  [rdi].flags,S_FWDREF
        and [rdi].flags,not S_ISSAVED
        .if StoreState
            or [rdi].flags,S_ISSAVED
        .endif
    .else
        .if !( [rdi].flags & S_ISEQUATE )
            asmerr(2005, name)
            .return NULL
        .endif
        mov [rdi].value3264,0

        ; v2.09: don't save variable when it is defined the first time
        ; v2.10: store state only when variable is changed and has been
        ; defined BEFORE SaveState() has been called.

        .if StoreState && !( [rdi].flags & S_ISSAVED )
            SaveVariableState(rdi)
        .endif
    .endif
    or  [rdi].flags,S_ISDEFINED or S_VARIABLE or S_ISEQUATE
    mov [rdi].state,SYM_INTERNAL
    mov [rdi].value,value
   .return(rdi)

CreateVariable endp


; CreateConstant()
; this is the worker behind EQU.
; EQU may define 3 different types of equates:
; - numeric constants (with or without "type")
; - relocatable items ( aliases )
; - text macros
; the argument may be
; - an expression which can be evaluated to a number or address
; - a text literal (enclosed in <>)
; - anything. This will also become a text literal.

    assume rsi:token_t

CreateConstant proc __ccall uses rsi rdi rbx tokenarray:token_t

    local name:         string_t
    local i:            int_t
    local rc:           int_t
    local p:            string_t
    local cmpvalue:     int_t
    local opnd:         expr
    local argbuffer[MAX_LINE_LEN]:char_t

    ldr rbx,tokenarray
    .if ( [rbx].token == T_DIRECTIVE && [rbx].tokval == T_DEFINE )
        mov rax,[rbx+asm_tok].string_ptr
    .else
        NameSpace([rbx].string_ptr, [rbx].string_ptr)
    .endif
    mov name,rax
    mov i,2
    mov cmpvalue,FALSE
    mov rdi,SymSearch(name)
    lea rsi,[rbx+asm_tok*2]

    .switch
    .case ( [rbx].tokval == T_DEFINE && [rsi].token == T_FINAL )
        ;
        ; define name
        ;
        xor eax,eax
ifndef _WIN64
        cdq
endif
        .s8 opnd.llvalue
        .s8 opnd.hlvalue
        mov opnd.sym,rax
        dec i
        jmp check_single_number

    .case ( [rsi].token == T_STRING && [rsi].string_delim == '<' )
        ;
        ; if a literal follows, the equate MUST be(come) a text macro
        ;
        .return SetTextMacro(rbx, rdi, name, NULL)

    .case ( rdi == NULL )
        .endc
    .case ( [rdi].state == SYM_UNDEFINED )
    .case ( [rdi].state == SYM_EXTERNAL &&
           ( [rdi].sflags & S_WEAK ) && !( [rdi].flags & S_ISPROC ) )
        ;
        ; It's a "new" equate.
        ; wait with definition until type of equate is clear
        ;
        .endc
    .case [rdi].state == SYM_TMACRO
        .return SetTextMacro(rbx, rdi, name, [rsi].tokpos)
    .case !( byte ptr [rdi].flags & S_ISEQUATE )
        asmerr( 2005, name )
        .return NULL
    .default
        mov eax,Parse_Pass
        .if ( [rdi].asmpass == al )
            mov cmpvalue,TRUE
        .endif
        mov [rdi].asmpass,al
    .endsw

    ; try to evaluate the expression

    .if ( [rsi].token == T_NUM && TokenCount == 3 )

        mov p,[rsi].string_ptr

    do_single_number:

        ; value is a plain number. it will be accepted only if it fits into 32-bits.
        ; Else a text macro is created.

        _atoow( &opnd, [rsi].string_ptr, [rsi].numbase, [rsi].itemlen )

    check_single_number:

        mov opnd.inst,EMPTY
        mov opnd.kind,EXPR_CONST
        mov opnd.mem_type,MT_EMPTY ;; v2.07: added
        mov opnd.flags,0

        .l8 opnd.hlvalue
ifndef _WIN64
        or eax,edx
endif
        mov rc,NOT_ERROR
        inc i

        ; v2.08: does it fit in 32-bits

        .if ( !rax )

            movzx   ecx,ModuleInfo.Ofssize
          ifdef _WIN64
            mov     rdx,opnd.llvalue
            lea     r8,minintvalues
            cmp     rdx,[r8+rcx*int64_t]
            setl    al
            lea     r8,maxintvalues
            cmp     rdx,[r8+rcx*int64_t]
            setg    ah
          else
            push    edi
            push    ebx
            lea     esi,minintvalues
            lea     edi,maxintvalues
            mov     edx,opnd.hvalue
            mov     ebx,opnd.value
            .if ( ( sdword ptr edx < [esi+ecx*int64_t][4] || ( ZERO? && ebx < [esi+ecx*int64_t] ) ) ||
                  ( sdword ptr edx > [edi+ecx*int64_t][4] || ( ZERO? && ebx > [edi+ecx*int64_t] ) ) )
                inc al
            .endif
            pop     ebx
            pop     edi
          endif

        .endif
        .if rax
            .return SetTextMacro( rbx, rdi, name, p )
        .endif

    .else

        mov p,[rsi].tokpos
        .if Parse_Pass == PASS_1
            ;
            ; if the expression cannot be evaluated to a numeric value,
            ; it's to become a text macro. The value of this macro will be
            ; the original (unexpanded!) line - that's why it has to be
            ; saved here to argbuffer[].
            ;
            ; v2.32.39 - added error 'missing right parenthesis'
            ; -- '(' triggers multiple lines..
            ;
            mov     rdx,rdi
            mov     rdi,rax
            xor     eax,eax
            mov     ecx,-1
            repnz   scasb
            not     ecx

            .if ( ecx >= MAX_LINE_LEN )

                asmerr( 2008, [rbx].string_ptr )
               .return( NULL )
            .endif

            mov     rax,rsi
            lea     rdi,argbuffer
            mov     rsi,p
            rep     movsb
            mov     rsi,rax
            mov     rdi,rdx

            ; expand EQU argument (macro functions won't be expanded!)

            .if ExpandLineItems( p, 2, rbx, FALSE, TRUE )

                ; v2.08: if expansion result is a plain number, handle is specifically.
                ; this is necessary because values of expressions may be 64-bit now.

                lea rax,argbuffer
                mov p,rax ;; ensure that p points to unexpanded source
            .endif
            .if [rsi].token == T_NUM && TokenCount == 3
                jmp do_single_number
            .endif
        .endif
        mov rc,EvalOperand( &i, rbx, TokenCount, &opnd, EXPF_NOERRMSG or EXPF_NOUNDEF )

        ; v2.08: if it's a quoted string, handle it like a plain number
        ; v2.10: quoted_string field is != 0 if kind == EXPR_FLOAT,
        ; so this is a regression in v2.08-2.09.

        .if opnd.quoted_string && opnd.kind == EXPR_CONST
            dec i ; v2.09: added; regression in v2.08 and v2.08a
            jmp check_single_number
        .endif

        ; check here if last token has been reached?
    .endif

    ; what is an acceptable 'number' for EQU?
    ; 1. a numeric value - if magnitude is <= 64 (or 32, if it's a plain number)
    ;    This includes struct fields.
    ; 2. an address - if it is direct, has a label and is of type SYM_INTERNAL -
    ;    that is, no forward references, no seg, groups, externals;
    ;    Anything else will be stored as a text macro.
    ; v2.04: large parts rewritten.

    imul eax,i,asm_tok
    mov rcx,opnd.sym
ifdef _WIN64
    mov rdx,opnd.hlvalue ; magnitude <= 64 bits?
else
    mov edx,dword ptr opnd.hlvalue
    or  edx,dword ptr opnd.hlvalue[4]
endif

    .if ( rc != ERROR && [rbx+rax].token == T_FINAL && opnd.inst == EMPTY &&
          ( ( opnd.kind == EXPR_CONST && rdx == 0 ) ||
            ( opnd.kind == EXPR_ADDR && !( opnd.flags & E_INDIRECT ) &&
              rcx != NULL && [rcx].state == SYM_INTERNAL ) ) )

        .switch
        .case !rdi
            mov rdi,SymCreate(name)
            mov eax,Parse_Pass
            mov [rdi].asmpass,al
            .endc
        .case [rdi].state == SYM_UNDEFINED
            sym_remove_table(&SymTables[TAB_UNDEF*symbol_queue], rdi)
            or [rdi].flags,S_FWDREF
            .endc
        .case [rdi].state == SYM_EXTERNAL
            sym_ext2int(rdi)
            .endc
        .case cmpvalue
            .if opnd.kind == EXPR_CONST
                ; for 64bit, it may be necessary to check 64bit value!
                ; v2.08: always compare 64-bit values
                .if [rdi].value != opnd.value || [rdi].value3264 != opnd.hvalue
                    asmerr(2005, name)
                    .return(NULL)
                .endif
            .elseif opnd.kind == EXPR_ADDR
                mov rcx,opnd.sym
                mov edx,[rcx].offs
                add edx,opnd.value
                .if [rdi].offs != edx || [rdi].segm != [rcx].segm
                    asmerr(2005, name)
                    .return(NULL)
                .endif
            .endif
        .endsw

        and byte ptr [rdi].flags,not S_VARIABLE
        SetValue(rdi, &opnd)
        .return rdi
    .endif
    SetTextMacro(rbx, rdi, name, &argbuffer)
    ret

CreateConstant endp

    assume rsi:nothing


; EQU directive.
; This function is called rarely, since EQU
; is a preprocessor directive handled directly inside PreprocessLine().
; However, if fastpass is on, the preprocessor step is skipped in
; pass 2 and later, and then this function may be called.

    assume rcx:token_t

EquDirective proc __ccall i:int_t, tokenarray:token_t

    ldr rcx,tokenarray
    mov al,[rcx].token
    .if ( [rcx].token == T_DIRECTIVE && [rcx].tokval == T_DEFINE )
        mov al,[rcx+asm_tok].token
    .endif
    .if ( al != T_ID )
        .return asmerr( 2008, [rcx].string_ptr )
    .endif
    .if CreateConstant( rcx )
        .if ( ModuleInfo.list == TRUE )
            LstWrite( LSTTYPE_EQUATE, 0, rax )
        .endif
        .return NOT_ERROR
    .endif
    .return( ERROR )

EquDirective endp

    end
