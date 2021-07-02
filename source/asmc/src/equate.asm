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
include atofloat.inc

    .data
    maxintvalues int_t -1,0, -1,0,-1,0x7fffffff
    minintvalues int_t 0,-1, 0,-1, 0,0x80000000

    .code

;; set the value of a constant (EQU) or an assembly time variable (=)

    assume edx:expr_t
    assume ecx:asym_t
    assume edi:asym_t
    assume ebx:token_t

SetValue proc private uses edi sym:asym_t, opndx:expr_t

    mov ecx,sym
    mov edx,opndx

    mov [ecx].state,SYM_INTERNAL
    or  [ecx].flags,S_ISEQUATE or S_ISDEFINED
    and [ecx].flag1,not S_ISPROC

    .if ( [edx].kind == EXPR_CONST || \
        ( [edx].kind == EXPR_FLOAT && [edx].float_tok == NULL ) )

        mov [ecx].uvalue,    [edx].uvalue
        mov [ecx].value3264, [edx].hvalue
        mov [ecx].mem_type,  [edx].mem_type
        .if al == MT_REAL16 && !ModuleInfo.strict_masm_compat
            mov [ecx].total_length,dword ptr [edx].hlvalue
            mov [ecx].ext_idx,dword ptr [edx].hlvalue[4]
        .endif
        mov [ecx].segm,  NULL
        .return
    .endif

    ;; for a PROC alias, copy the procinfo extension!

    mov edi,[edx].sym
    .if [edi].flag1 & S_ISPROC

        or  [ecx].flag1,S_ISPROC
        ;; v2.12: must be copied as well, or INVOKE won't work correctly
        mov [ecx].langtype,[edi].langtype
        assume ecx:dsym_t
        assume edi:dsym_t
        mov [ecx].procinfo,[edi].procinfo
        assume ecx:asym_t
        assume edi:asym_t
    .endif

    mov [ecx].mem_type,[edx].mem_type

    ;; v2.01: allow equates of variables with arbitrary type.
    ;; Currently the expression evaluator sets opndx.mem_type
    ;; to the mem_type of the type (i.e. QWORD for a struct with size 8),
    ;; which is a bad idea in this case. So the original mem_type of the
    ;; label is used instead.

    .if ( [edi].mem_type == MT_TYPE && !( [edx].flags & E_EXPLICIT ) )

        mov [ecx].mem_type,[edi].mem_type
        mov [ecx].type,[edi].type
    .endif
    mov [ecx].value3264,0 ;; v2.09: added
    mov [ecx].segm,[edi].segm

    ;; labels are supposed to be added to the current segment's label_list chain.
    ;; this isn't done for alias equates, for various reasons.
    ;; consequently, if the alias was forward referenced, ensure that a third pass
    ;; will be done! regression test forward5.asm.

    mov eax,[edi].offs
    add eax,[edx].value
    .if [ecx].flags & S_VARIABLE
        mov [ecx].offs,eax
        .if Parse_Pass == PASS_2 && ( [ecx].flag1 & S_FWDREF )
            mov ModuleInfo.PhaseError,TRUE
        .endif
    .else
        .if Parse_Pass != PASS_1 && [ecx].offs != eax
            mov ModuleInfo.PhaseError,TRUE
        .endif
        mov [ecx].offs,eax
        BackPatch(ecx)
    .endif
    ret

SetValue endp

;; the '=' directive defines an assembly time variable.
;; this can only be a number (constant or relocatable).

CreateAssemblyTimeVariable proc private uses esi edi ebx tokenarray:token_t

    local sym:asym_t
    local name:string_t
    local i:int_t
    local opnd:expr

    mov i,2
    mov ebx,tokenarray
    mov name,[ebx].string_ptr
    add ebx,2*16

    ;; v2.08: for plain numbers ALWAYS avoid to call evaluator

    .if ( [ebx].token == T_NUM && [ebx+16].token == T_FINAL )

        _atoow( &opnd, [ebx].string_ptr, [ebx].numbase, [ebx].itemlen )

check_number:

        mov opnd.kind,EXPR_CONST
        mov opnd.mem_type,MT_EMPTY ;; v2.07: added

        ;; v2.08: check added. the number must be 32-bit

        .if dword ptr opnd.hlvalue || dword ptr opnd.hlvalue[4]
            mov eax,1
        .else
            xor eax,eax

            movzx ecx,ModuleInfo.Ofssize
            mov ebx,opnd.value
            mov edx,opnd.hvalue

            cmp edx,minintvalues[ecx*8+4]
            setl al
            .ifnl
                .ifz
                    cmp ebx,minintvalues[ecx*8]
                    setb al
                .endif
            .endif
            cmp edx,maxintvalues[ecx*8+4]
            setg ah
            .ifng
                .ifz
                    cmp ebx,maxintvalues[ecx*8]
                    seta ah
                .endif
            .endif
        .endif
        .if eax
            EmitConstError(&opnd)
            .return NULL
        .endif
    .else

        ;; v2.09: don't create not-(yet)-defined symbols. Example:
        ;; E1 = E1 or 1
        ;; must NOT create E1.

        .return .if EvalOperand( &i, tokenarray, Token_Count, &opnd, 0 ) == ERROR

        mov ebx,i
        shl ebx,4
        add ebx,tokenarray
        .if [ebx].token != T_FINAL

            asmerr( 2008, [ebx].string_ptr )
            .return NULL
        .endif

        ;; expression may be a constant or a relocatable item.
        ;; v2.09: kind may be EXPR_CONST and still include an undefined symbol.
        ;; This is caused by MakeConst() in expreval.c. Brackets changed so
        ;; opnd.sym is also checked for opnd.kind == EXPR_CONST.

        mov ecx,opnd.sym
        .if ( opnd.kind != EXPR_CONST && \
            ( opnd.kind != EXPR_ADDR || ( opnd.flags & E_INDIRECT ) ) || \
            ( ecx != NULL && [ecx].state != SYM_INTERNAL ) )

            ;; v2.09: no error if argument is a forward reference,
            ;; but don't create the variable either. Will enforce an
            ;; error if referenced symbol is still undefined in pass 2.

            .if ecx && [ecx].state == SYM_UNDEFINED && !( opnd.flags & E_INDIRECT )
                .if StoreState == FALSE
                    FStoreLine(0) ;; make sure this line is evaluated in pass two
                .endif

            .elseif !ecx && opnd.kind == EXPR_FLOAT && !ModuleInfo.strict_masm_compat

                mov opnd.mem_type,MT_REAL16
                mov opnd.kind,EXPR_CONST
                mov opnd.float_tok,NULL
                jmp check_float
            .else
                asmerr(2026)
            .endif
            .return NULL
        .endif

        ;; v2.08: accept any result that fits in 64-bits from expression evaluator
        .if ( dword ptr opnd.hlvalue || dword ptr opnd.hlvalue[4] )
            EmitConstError(&opnd)
            .return NULL
        .endif
        ;; for quoted strings, the same restrictions as for plain numbers apply
        .if ( opnd.quoted_string )
            jmp check_number
        .endif
    .endif

check_float:

    mov edi,SymSearch(name)

    .if ( edi == NULL || [edi].state == SYM_UNDEFINED )
        .if edi == NULL
            mov edi,SymCreate(name)
        .else
            sym_remove_table(&SymTables[TAB_UNDEF*symbol_queue], edi)
            or [edi].flag1,S_FWDREF
        .endif
        and [edi].flag1,not S_ISSAVED
        .if StoreState
            or [edi].flag1,S_ISSAVED
        .endif
    .elseif ( [edi].state == SYM_EXTERNAL && [edi].sflags & S_WEAK && [edi].mem_type == MT_EMPTY )
        sym_ext2int(edi)
        and [edi].flag1,not S_ISSAVED
        .if StoreState
            or [edi].flag1,S_ISSAVED
        .endif
    .else
        .if ( [edi].state != SYM_INTERNAL || ( !( [edi].flags & S_VARIABLE ) && \
            ( opnd.uvalue != [edi].uvalue || opnd.hvalue != [edi].value3264 ) ) )
            asmerr(2005, [edi].name)
            .return NULL
        .endif

        ;; v2.04a regression in v2.04. Do not save the variable when it
        ;; is defined the first time
        ;; v2.10: store state only when variable is changed and has been
        ;; defined BEFORE SaveState() has been called.

        .if StoreState && !( [edi].flag1 & S_ISSAVED )
            SaveVariableState(edi)
        .endif
    .endif
    or byte ptr [edi].flags,S_VARIABLE
    ;; v2.09: allow internal variables to be set
    .if ( byte ptr [edi].flags & S_PREDEFINED ) && [edi].sfunc_ptr
        [edi].sfunc_ptr(edi, &opnd)
    .else
        SetValue(edi, &opnd)
    .endif
    mov eax,edi
    ret

CreateAssemblyTimeVariable endp

;; '=' directive.

    assume edx:token_t

EqualSgnDirective proc i:int_t, tokenarray:token_t

    mov edx,tokenarray
    .return asmerr(2008, [edx].string_ptr) .if [edx].token != T_ID
    .if CreateAssemblyTimeVariable(edx)
        .if ModuleInfo.list == TRUE
            LstWrite(LSTTYPE_EQUATE, 0, eax)
        .endif
        .return NOT_ERROR
    .endif
    mov eax,ERROR
    ret

EqualSgnDirective endp

;; CreateVariable().
;; define an assembly time variable directly without using the token buffer.
;; this is used for some internally generated variables (SIZESTR, INSTR, @Cpu)
;; NO listing is written! The value is ensured to be max 16-bit wide.

CreateVariable proc uses edi name:string_t, value:int_t

    mov edi,SymSearch(name)
    .if edi == NULL
        mov edi,SymCreate(name)
        and [edi].flag1,not S_ISSAVED
        .if StoreState
            or [edi].flag1,S_ISSAVED
        .endif
    .elseif [edi].state == SYM_UNDEFINED
        sym_remove_table( &SymTables[TAB_UNDEF*symbol_queue], edi)
        or  [edi].flag1,S_FWDREF
        and [edi].flag1,not S_ISSAVED
        .if StoreState
            or [edi].flag1,S_ISSAVED
        .endif
    .else
        .if !( [edi].flags & S_ISEQUATE )
            asmerr(2005, name)
            .return NULL
        .endif
        mov [edi].value3264,0

        ;; v2.09: don't save variable when it is defined the first time
        ;; v2.10: store state only when variable is changed and has been
        ;; defined BEFORE SaveState() has been called.

        .if StoreState && !( [edi].flag1 & S_ISSAVED )
            SaveVariableState(edi)
        .endif
    .endif
    or  [edi].flags,S_ISDEFINED or S_VARIABLE or S_ISEQUATE
    mov [edi].state,SYM_INTERNAL
    mov eax,value
    mov [edi].value,eax
    mov eax,edi
    ret

CreateVariable endp


;; CreateConstant()
;; this is the worker behind EQU.
;; EQU may define 3 different types of equates:
;; - numeric constants (with or without "type")
;; - relocatable items ( aliases )
;; - text macros
;; the argument may be
;; - an expression which can be evaluated to a number or address
;; - a text literal (enclosed in <>)
;; - anything. This will also become a text literal.

    assume esi:token_t

CreateConstant proc uses esi edi ebx tokenarray:token_t

    local name:         string_t
    local i:            int_t
    local rc:           int_t
    local p:            string_t
    local cmpvalue:     int_t
    local opnd:         expr
    local argbuffer[MAX_LINE_LEN]:char_t

    mov ebx,tokenarray
    mov name,[ebx].string_ptr
    mov i,2
    mov cmpvalue,FALSE
    mov edi,SymSearch(name)
    lea esi,[ebx+32]

    .switch
        ;; if a literal follows, the equate MUST be(come) a text macro
      .case [esi].token == T_STRING && [esi].string_delim == '<'
        .return SetTextMacro(ebx, edi, name, NULL)
      .case edi == NULL
      .case [edi].state == SYM_UNDEFINED
      .case [edi].state == SYM_EXTERNAL && \
          ( [edi].sflags & S_WEAK ) && !( [edi].flag1 & S_ISPROC )
        ;; It's a "new" equate.
        ;; wait with definition until type of equate is clear
        .endc
      .case [edi].state == SYM_TMACRO
        .return SetTextMacro(ebx, edi, name, [esi].tokpos)
      .case !( byte ptr [edi].flags & S_ISEQUATE )
        asmerr( 2005, name )
        .return NULL
      .default
        mov eax,Parse_Pass
        .if ( [edi].asmpass == al )
            mov cmpvalue,TRUE
        .endif
        mov [edi].asmpass,al
    .endsw

    ;; try to evaluate the expression

    .if [esi].token == T_NUM && Token_Count == 3

        mov p,[esi].string_ptr

    do_single_number:

        ;; value is a plain number. it will be accepted only if it fits into 32-bits.
        ;; Else a text macro is created.

        _atoow( &opnd, [esi].string_ptr, [esi].numbase, [esi].itemlen )

    check_single_number:

        mov opnd.inst,EMPTY
        mov opnd.kind,EXPR_CONST
        mov opnd.mem_type,MT_EMPTY ;; v2.07: added
        mov opnd.flags,0

        ;; v2.08: does it fit in 32-bits

        .if dword ptr opnd.hlvalue || dword ptr opnd.hlvalue[4]

            mov eax,1
        .else
            xor eax,eax
            movzx ecx,ModuleInfo.Ofssize
            mov esi,opnd.value
            mov edx,opnd.hvalue
            cmp edx,minintvalues[ecx*8+4]
            .ifng
                setnz al
                .ifz
                    cmp esi,minintvalues[ecx*8]
                    setb al
                .endif
            .endif
            cmp edx,maxintvalues[ecx*8+4]
            .ifnl
                setnz al
                .ifz
                    cmp esi,maxintvalues[ecx*8]
                    seta al
                .endif
            .endif
        .endif
        .if eax == 0
            mov rc,NOT_ERROR
            inc i
        .else
            .return SetTextMacro( ebx, edi, name, p )
        .endif

    .else
        mov p,[esi].tokpos
        .if Parse_Pass == PASS_1

            ;; if the expression cannot be evaluated to a numeric value,
            ;; it's to become a text macro. The value of this macro will be
            ;; the original (unexpanded!) line - that's why it has to be
            ;; saved here to argbuffer[].

            ; v2.32.39 - added error 'missing right parenthesis'
            ; -- '(' triggers multiple lines..

            mov edx,edi
            mov edi,eax
            xor eax,eax
            mov ecx,-1
            repnz scasb
            not ecx
            .if ecx >= MAX_LINE_LEN
                asmerr( 2008, [ebx].string_ptr )
                .return( NULL )
            .endif
            mov eax,esi
            lea edi,argbuffer
            mov esi,p
            rep movsb
            mov esi,eax
            mov edi,edx

            ;; expand EQU argument (macro functions won't be expanded!)

            .if ExpandLineItems( p, 2, ebx, FALSE, TRUE )

                ;; v2.08: if expansion result is a plain number, handle is specifically.
                ;; this is necessary because values of expressions may be 64-bit now.

                lea eax,argbuffer
                mov p,eax ;; ensure that p points to unexpanded source
            .endif
            .if [esi].token == T_NUM && Token_Count == 3
                jmp do_single_number
            .endif
        .endif
        mov rc,EvalOperand( &i, ebx, Token_Count, &opnd, EXPF_NOERRMSG or EXPF_NOUNDEF )

        ;; v2.08: if it's a quoted string, handle it like a plain number
        ;; v2.10: quoted_string field is != 0 if kind == EXPR_FLOAT,
        ;; so this is a regression in v2.08-2.09.

        .if opnd.quoted_string && opnd.kind == EXPR_CONST
            dec i ;; v2.09: added; regression in v2.08 and v2.08a
            jmp check_single_number
        .endif

        ;; check here if last token has been reached?
    .endif

    ;; what is an acceptable 'number' for EQU?
    ;; 1. a numeric value - if magnitude is <= 64 (or 32, if it's a plain number)
    ;;    This includes struct fields.
    ;; 2. an address - if it is direct, has a label and is of type SYM_INTERNAL -
    ;;    that is, no forward references, no seg, groups, externals;
    ;;    Anything else will be stored as a text macro.
    ;; v2.04: large parts rewritten.

    mov eax,i
    shl eax,4
    mov edx,dword ptr opnd.hlvalue
    or  edx,dword ptr opnd.hlvalue[4] ;; magnitude <= 64 bits?
    mov ecx,opnd.sym

    .if ( rc != ERROR && [ebx+eax].token == T_FINAL && ( ( opnd.kind == EXPR_CONST \
        && edx == 0 ) || ( opnd.kind == EXPR_ADDR && !( opnd.flags & E_INDIRECT ) \
        && ecx != NULL && [ecx].state == SYM_INTERNAL ) ) && ( opnd.inst == EMPTY ) )

        .switch
        .case !edi
            mov edi,SymCreate(name)
            mov eax,Parse_Pass
            mov [edi].asmpass,al
            .endc
        .case [edi].state == SYM_UNDEFINED
            sym_remove_table(&SymTables[TAB_UNDEF*symbol_queue], edi)
            or [edi].flag1,S_FWDREF
            .endc
        .case [edi].state == SYM_EXTERNAL
            sym_ext2int(edi)
            .endc
        .case cmpvalue
            .if opnd.kind == EXPR_CONST
                ;; for 64bit, it may be necessary to check 64bit value!
                ;; v2.08: always compare 64-bit values
                .if [edi].value != opnd.value || [edi].value3264 != opnd.hvalue
                    asmerr(2005, name)
                    .return(NULL)
                .endif
            .elseif opnd.kind == EXPR_ADDR
                mov ecx,opnd.sym
                mov edx,[ecx].offs
                add edx,opnd.value
                .if [edi].offs != edx || [edi].segm != [ecx].segm
                    asmerr(2005, name)
                    .return(NULL)
                .endif
            .endif
        .endsw

        and byte ptr [edi].flags,not S_VARIABLE
        SetValue(edi, &opnd)
        .return edi
    .endif
    SetTextMacro(ebx, edi, name, &argbuffer)
    ret

CreateConstant endp

    assume esi:nothing

;; EQU directive.
;; This function is called rarely, since EQU
;; is a preprocessor directive handled directly inside PreprocessLine().
;; However, if fastpass is on, the preprocessor step is skipped in
;; pass 2 and later, and then this function may be called.

    assume ecx:token_t

EquDirective proc i:int_t, tokenarray:token_t

    mov ecx,tokenarray
    .return asmerr(2008, [ecx].string_ptr) .if [ecx].token != T_ID

    .if CreateConstant(ecx)
        .if ModuleInfo.list == TRUE
            LstWrite(LSTTYPE_EQUATE, 0, eax)
        .endif
        .return NOT_ERROR
    .endif
    mov eax,ERROR
    ret

EquDirective endp

    end
