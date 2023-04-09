; EXPREVAL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; expression evaluator.
;

include stddef.inc

include asmc.inc
include expreval.inc
include parser.inc
include reswords.inc
include segment.inc
include proc.inc
include assume.inc
include tokenize.inc
include types.inc
include label.inc
include qfloat.inc
include operator.inc
include unaryop.inc

define LS_SHORT 0xFF01
define LS_FAR16 0xFF05
define LS_FAR32 0xFF06

define OPATTR_CODELABEL 0x01
define OPATTR_DATALABEL 0x02
define OPATTR_IMMEDIATE 0x04
define OPATTR_DIRECTMEM 0x08
define OPATTR_REGISTER  0x10
define OPATTR_DEFINED   0x20
define OPATTR_SSREL     0x40
define OPATTR_EXTRNREF  0x80
define OPATTR_LANG_MASK 0x700

externdef StackAdj:uint_t

CCALLBACK(lpfnasmerr, :int_t, :vararg)

FindDotSymbol proto fastcall :ptr asm_tok

    .data

     thissym    asym_t 0
     nullstruct asym_t 0
     nullmbr    asym_t 0
     fnasmerr   lpfnasmerr 0
     floaterr   int_t 0

    .code

    option proc:private

    assume rcx:expr_t
    assume rdx:expr_t
    assume rsi:expr_t
    assume rdi:expr_t


noasmerr proc __ccall msg:int_t, args:vararg

    .return( ERROR )

noasmerr endp


ConstError proc fastcall opnd1:expr_t, opnd2:expr_t

    .if ( [rcx].flags & E_IS_OPEATTR )
        .return( NOT_ERROR )
    .endif
    .if ( [rcx].kind == EXPR_FLOAT || [rdx].kind == EXPR_FLOAT )
        fnasmerr( 2050 )
    .else
        fnasmerr( 2026 )
    .endif
    ret

ConstError endp


TokenAssign proc fastcall uses rsi rdi opnd1:expr_t, opnd2:expr_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    ; note that offsetof() is used. This means, don't change position
    ; of field <type> in expr!

    mov rsi,rdx
    mov rdi,rcx
    mov rax,rcx
    mov ecx,offsetof( expr, type ) / 4
    rep movsd
    mov rcx,rax
    ret

TokenAssign endp


invalid_operand proc fastcall uses rbx opnd:expr_t, oprtr:string_t, operand:string_t

    UNREFERENCED_PARAMETER(opnd)

    mov rbx,operand

    .if ( !( [rcx].flags & E_IS_OPEATTR ) )
        fnasmerr( 3018, tstrupr( rdx ), rbx )
    .endif
    .return ERROR

invalid_operand endp


    assume rcx:dsym_t

GetSizeValue proc fastcall sym:asym_t

    UNREFERENCED_PARAMETER(sym)

    movzx eax,[rcx].mem_type
    .if ( eax == MT_PTR )
        mov eax,MT_NEAR
        .if ( [rcx].is_far )
            mov eax,MT_FAR
        .endif
    .endif
    movzx edx,[rcx].Ofssize
    SizeFromMemtype( al, edx, [rcx].type )
    ret

GetSizeValue endp


GetRecordMask proc fastcall uses rsi rdi rbx rec:dsym_t

    xor eax,eax
    xor edx,edx
    mov rbx,[rcx].structinfo
    mov rbx,[rbx].struct_info.head

    .for ( : rbx : rbx = [rbx].sfield.next )

        mov ecx,[rbx].sfield.offs
        mov edi,[rbx].sfield.total_size
        add edi,ecx

        .for ( : ecx < edi : ecx++ )

            mov esi,1
            .if ecx < 32
                shl esi,cl
                or  eax,esi
            .else
                sub ecx,32
                shl esi,cl
                or  edx,esi
                add ecx,32
            .endif
        .endf
    .endf
    ret

GetRecordMask endp


    assume rcx:expr_t

IsOffset proc fastcall opnd:expr_t

    UNREFERENCED_PARAMETER(opnd)

    .if ( [rcx].mem_type == MT_EMPTY )
        mov eax,[rcx].inst
        .if ( eax == T_OFFSET ||
              eax == T_IMAGEREL ||
              eax == T_SECTIONREL ||
              eax == T_LROFFSET )
            .return( true )
        .endif
    .endif
    .return( false )

IsOffset endp


;--------------------------------------------------------------------------------
; unaryop.inc
;--------------------------------------------------------------------------------

tofloat proc fastcall opnd1:expr_t, opnd2:expr_t, size:int_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    .if ( ModuleInfo.strict_masm_compat )

        ConstError( rcx, rdx )
        mov ecx,eax
       .return 1
    .endif
    mov [rdx].kind,EXPR_CONST
    mov [rdx].float_tok,NULL
    .if ( size != 16 )
        mov rcx,rdx
        quad_resize( rcx, size )
    .endif
    .return( NOT_ERROR )

tofloat endp


    assume rdx:nothing
    assume rcx:nothing
    assume rbx:dsym_t

unaryop proc __ccall private uses rsi rdi rbx uot:unary_operand_types,
        opnd1:expr_t, opnd2:expr_t, sym:asym_t, oper:int_t, name:string_t

    mov rsi,opnd1
    mov rdi,opnd2
    mov eax,uot

    .switch eax
    .case UOT_DOT_LOW
        TokenAssign( rsi, rdi )
        .if ( [rdi].kind == EXPR_ADDR && [rdi].inst != T_SEG )
            mov [rsi].inst,T_DOT_LOW
            mov [rsi].mem_type,MT_EMPTY
        .endif
        mov eax,[rsi].value
        and eax,0xff
        mov [rsi].value,eax
        mov [rsi].hvalue,0
       .return NOT_ERROR
    .case UOT_DOT_HIGH
        TokenAssign( rsi, rdi )
        .if ( [rdi].kind == EXPR_ADDR && [rdi].inst != T_SEG )
            mov [rsi].inst,T_DOT_HIGH
            mov [rsi].mem_type,MT_EMPTY
        .endif
        mov eax,[rsi].value
        shr eax,8
        and eax,0xff
        mov [rsi].value,eax
        mov [rsi].hvalue,0
       .return NOT_ERROR
    .case UOT_LOWWORD
        TokenAssign( rsi, rdi )
        .if ( [rdi].kind == EXPR_ADDR && [rdi].inst != T_SEG )
            mov [rsi].inst,T_LOWWORD
            mov [rsi].mem_type,MT_EMPTY
        .endif
        mov eax,[rsi].value
        and eax,0xffff
        mov [rsi].value,eax
        mov [rsi].hvalue,0
       .return NOT_ERROR
    .case UOT_HIGHWORD
        TokenAssign( rsi, rdi )
        .if ( [rdi].kind == EXPR_ADDR && [rdi].inst != T_SEG )
            mov [rsi].inst,T_HIGHWORD
            mov [rsi].mem_type,MT_EMPTY
        .endif
        mov eax,[rsi].value
        shr eax,16
        and eax,0xffff
        mov [rsi].value,eax
        mov [rsi].hvalue,0
       .return NOT_ERROR
    .case UOT_LOW32
        .if ( [rdi].kind == EXPR_FLOAT )
            .return ecx .if tofloat( rsi, rdi, 8 )
        .endif
        TokenAssign( rsi, rdi )
        mov [rsi].mem_type,MT_DWORD
        .if ( [rdi].kind == EXPR_ADDR && [rdi].inst != T_SEG )
            mov [rsi].inst,T_LOW32
            mov [rsi].mem_type,MT_EMPTY
        .endif
        mov [rsi].hvalue,0
       .return NOT_ERROR
    .case UOT_HIGH32
        .if ( [rdi].kind == EXPR_FLOAT )
            .return ecx .if tofloat( rsi, rdi, 8 )
        .endif
        TokenAssign( rsi, rdi )
        mov [rsi].mem_type,MT_DWORD
        .if ( [rdi].kind == EXPR_ADDR && [rdi].inst != T_SEG )
            mov [rsi].inst,T_HIGH32
            mov [rsi].mem_type,MT_EMPTY
        .endif
        mov [rsi].value,[rsi].hvalue
        mov [rsi].hvalue,0
       .return NOT_ERROR
    .case UOT_OFFSET
    .case UOT_LROFFSET
    .case UOT_IMAGEREL
    .case UOT_SECTIONREL
        .if ( oper == T_OFFSET )
            .if ( [rdi].kind == EXPR_CONST )
                TokenAssign( rsi, rdi )
               .return NOT_ERROR
            .endif
        .endif
        mov rbx,sym
        .if ( ( rbx && [rbx].state == SYM_GRP ) || [rdi].inst == T_SEG )
            .return invalid_operand( rdi, GetResWName( oper, NULL ), name )
        .endif
        .if ( [rdi].flags & E_IS_TYPE )
            mov [rdi].value,0
        .endif
        TokenAssign( rsi, rdi )
        mov [rsi].inst,oper
        .if ( [rdi].flags & E_INDIRECT )
            .return invalid_operand( rdi, GetResWName( oper, NULL ), name )
        .endif
        mov [rsi].mem_type,MT_EMPTY
       .return NOT_ERROR
    .case UOT_SEG
        mov rbx,[rdi].sym
        .if ( rbx == NULL || [rbx].state == SYM_STACK || [rdi].flags & E_IS_ABS )
            .return fnasmerr( 2094 )
        .endif
        TokenAssign( rsi, rdi )
        mov [rsi].inst,oper
        .if ( [rsi].mbr )
            mov [rsi].value,0
        .endif
        mov [rsi].mem_type,MT_EMPTY
       .return NOT_ERROR
    .case UOT_OPATTR
    .case UOT_DOT_TYPE
        xor eax,eax
        mov [rsi].kind,EXPR_CONST
        mov [rsi].sym,rax
        mov [rsi].value,eax
        mov [rsi].mem_type,MT_EMPTY
        and [rsi].flags,not E_IS_OPEATTR
        .if ( [rdi].kind == EXPR_EMPTY )
            .return
        .endif
        mov rbx,[rdi].sym
        .if ( [rdi].kind == EXPR_ADDR )
            mov al,[rdi].mem_type
            and al,MT_SPECIAL_MASK
            .if ( rbx && [rbx].state != SYM_STACK && eax == MT_ADDRESS )
                or [rsi].value,OPATTR_CODELABEL
            .endif
            IsOffset(rdi)
            .if ( eax && rbx )
                mov al,[rbx].mem_type
                and eax,MT_SPECIAL_MASK
                .if ( eax == MT_ADDRESS )
                    or [rsi].value,OPATTR_CODELABEL
                .endif
            .endif
            .if ( rbx && ( ( [rbx].mem_type == MT_TYPE || !( [rdi].mem_type & MT_SPECIAL ) ) ||
                 ( [rdi].mem_type == MT_EMPTY && !( [rbx].mem_type & MT_SPECIAL ) ) ) )
                or [rsi].value,OPATTR_DATALABEL
            .endif
        .endif
        .if ( [rdi].kind != EXPR_ERROR && [rdi].flags & E_INDIRECT )
            or [rsi].value,OPATTR_DATALABEL
        .endif
        IsOffset(rdi)
        mov cl,[rdi].mem_type
        and ecx,MT_SPECIAL_MASK
        .if ( [rdi].kind == EXPR_CONST || ( [rdi].kind == EXPR_ADDR && !( [rdi].flags & E_INDIRECT ) &&
              ( ( [rdi].mem_type == MT_EMPTY && eax ) || [rdi].mem_type == MT_EMPTY || ecx == MT_ADDRESS ) &&
              ( [rbx].state == SYM_INTERNAL || [rbx].state == SYM_EXTERNAL ) ) )
            or [rsi].value,OPATTR_IMMEDIATE
        .endif
        .if ( [rdi].kind == EXPR_ADDR && !( [rdi].flags & E_INDIRECT ) &&
              ( ( [rdi].mem_type == MT_EMPTY && [rdi].inst == EMPTY ) || [rdi].mem_type == MT_TYPE ||
              !( [rdi].mem_type & MT_SPECIAL ) || [rdi].mem_type == MT_PTR ) &&
              ( rbx == NULL || [rbx].state == SYM_INTERNAL || [rbx].state == SYM_EXTERNAL ) )
            or [rsi].value,OPATTR_DIRECTMEM
        .endif
        .if ( [rdi].kind == EXPR_REG && !( [rdi].flags & E_INDIRECT ) )
            or [rsi].value,OPATTR_REGISTER
        .endif
        .if ( [rdi].kind != EXPR_ERROR && [rdi].kind != EXPR_FLOAT && ( ebx == NULL || [rbx].flags & S_ISDEFINED ) )
            or [rsi].value,OPATTR_DEFINED
        .endif
        mov rax,[rdi].idx_reg
        .if ( rax == 0 )
            mov rax,[rdi].base_reg
        .endif
        .if ( rax )
            imul eax,[rax].asm_tok.tokval,special_item
        .endif
        lea rcx,SpecialTable
        .if ( ( rbx && [rbx].state == SYM_STACK ) ||
              ( [rdi].flags & E_INDIRECT && eax && ( [rcx+rax].special_item.sflags & SFR_SSBASED ) ) )
            or [rsi].value,OPATTR_SSREL
        .endif
        .if ( rbx && [rbx].state == SYM_EXTERNAL )
            or [rsi].value,OPATTR_EXTRNREF
        .endif
        .if ( oper == T_OPATTR )
            .if ( rbx && [rdi].kind != EXPR_ERROR )
                movzx eax,[rbx].langtype
                shl eax,8
                or [rsi].value,eax
            .endif
        .endif
        .return( NOT_ERROR )
    .case UOT_DOT_SIZE
    .case UOT_SIZEOF
    .case UOT_DOT_LENGTH
    .case UOT_LENGTHOF
        mov rbx,sym
        mov [rsi].kind,EXPR_CONST
        .if ( rbx )
            .switch pascal
            .case ( [rbx].state == SYM_STRUCT_FIELD || [rbx].state == SYM_STACK )
            .case ( [rbx].state == SYM_UNDEFINED )
                mov [rsi].kind,EXPR_ADDR
                mov [rsi].sym,rbx
            .case ( ( [rbx].state == SYM_EXTERNAL || [rbx].state == SYM_INTERNAL ) &&
                    [rbx].mem_type != MT_EMPTY && [rbx].mem_type != MT_FAR &&
                    [rbx].mem_type != MT_NEAR )
            .case ( [rbx].state == SYM_GRP || [rbx].state == SYM_SEG )
                .return fnasmerr( 2143 )
            .case ( oper == T_DOT_SIZE || oper == T_DOT_LENGTH )
            .default
                .return fnasmerr( 2143 )
            .endsw
        .endif
        .switch oper
        .case T_DOT_LENGTH
            .if ( [rbx].flags & S_ISDATA )
                mov [rsi].value,[rbx].first_length
            .else
                mov [rsi].value,1
            .endif
            .endc
        .case T_LENGTHOF
            .if ( [rdi].kind == EXPR_CONST )
                mov rbx,[rdi].mbr
                mov [rsi].value,[rbx].total_length
            .elseif ( [rbx].state == SYM_EXTERNAL && !( [rbx].sflags & S_ISCOM ) )
                mov [rsi].value,1
            .else
                mov [rsi].value,[rbx].total_length
            .endif
            .endc
        .case T_DOT_SIZE
            .switch pascal
            .case ( rbx == NULL )
                mov al,[rdi].mem_type
                and eax,MT_SPECIAL_MASK
                .if ( eax == MT_ADDRESS )
                    mov eax,[rdi].value
                    or  eax,0xFF00
                    mov [rsi].value,eax
                .else
                    mov [rsi].value,[rdi].value
                .endif
            .case ( [rbx].flags & S_ISDATA )
                mov [rsi].value,[rbx].first_size
            .case ( [rbx].state == SYM_STACK )
                GetSizeValue(rbx)
                mov [rsi].value,eax
            .case ( [rbx].mem_type == MT_NEAR )
                mov ecx,GetSymOfssize(rbx)
                mov eax,2
                shl eax,cl
                or  eax,0xFF00
                mov [rsi].value,eax
            .case ( [rbx].mem_type == MT_FAR )
                .if GetSymOfssize(rbx)
                    mov eax,LS_FAR32
                .else
                    mov eax,LS_FAR16
                .endif
                mov [rsi].value,eax
            .default
                GetSizeValue(rbx)
                mov [rsi].value,eax
            .endsw
            .endc
        .case T_SIZEOF
            .if ( rbx == NULL )
                mov rbx,[rdi].type
                .if ( [rdi].flags & E_IS_TYPE && rbx && [rbx].typekind == TYPE_RECORD )
                    mov [rsi].value,[rbx].total_size
                .else
                    mov [rsi].value,[rdi].value
                .endif
            .elseif ( [rbx].state == SYM_EXTERNAL && !( [rbx].sflags & S_ISCOM ) )
                GetSizeValue(rbx)
                mov [rsi].value,eax
            .else
                mov [rsi].value,[rbx].total_size
            .endif
            .endc
        .endsw
        .return( NOT_ERROR )
    .case UOT_SHORT
        .if ( [rdi].kind != EXPR_ADDR || ( [rdi].mem_type != MT_EMPTY &&
              [rdi].mem_type != MT_NEAR && [rdi].mem_type != MT_FAR ) )
            .return fnasmerr( 2028 )
        .endif
        TokenAssign( rsi, rdi )
        mov [rsi].inst,oper
       .return NOT_ERROR
    .case UOT_DOT_THIS
        .if !( [rdi].flags & E_IS_TYPE )
            .return fnasmerr( 2010 )
        .endif
        .if CurrStruct
            .return fnasmerr( 2034 )
        .endif
        .if ModuleInfo.currseg == NULL
            .return asmerr( 2034 )
        .endif
        mov rbx,thissym
        .if ( rbx == NULL )
            mov thissym,SymAlloc("")
            mov rbx,rax
            mov [rbx].state,SYM_INTERNAL
            or  [rbx].flags,S_ISDEFINED
        .endif
        mov [rsi].kind,EXPR_ADDR
        mov [rsi].sym,rbx
        mov rcx,[rdi].type
        mov [rbx].type,rcx
        .if ( rcx )
            mov [rbx].mem_type,MT_TYPE
        .else
            mov cl,[rdi].mem_type
            mov [rbx].mem_type,cl
        .endif
        SetSymSegOfs(rbx)
        mov rbx,thissym
        mov al,[rbx].mem_type
        mov [rsi].mem_type,al
       .return( NOT_ERROR )
    .case UOT_TYPEOF
        mov rbx,sym
        mov [rsi].kind,EXPR_CONST
        .if ( [rdi].inst != EMPTY && [rdi].mem_type != MT_EMPTY )
            mov [rdi].inst,EMPTY
            xor ebx,ebx
        .endif
        .switch pascal
        .case ( [rdi].inst != EMPTY )
            .if ( [rdi].sym )
                .switch [rdi].inst
                .case T_DOT_LOW
                .case T_DOT_HIGH
                    mov [rsi].value,1
                   .endc
                .case T_LOWWORD
                .case T_HIGHWORD
                    mov [rsi].value,2
                   .endc
                .case T_LOW32
                .case T_HIGH32
                    mov [rsi].value,4
                   .endc
                .case T_LOW64
                .case T_HIGH64
                    mov [rsi].value,8
                   .endc
                .case T_OFFSET
                .case T_LROFFSET
                .case T_SECTIONREL
                .case T_IMAGEREL
                    mov ecx,GetSymOfssize([rdi].sym)
                    mov eax,2
                    shl eax,cl
                    mov [rsi].value,eax
                    or  [rsi].flags,E_IS_TYPE
                   .endc
                .endsw
            .endif
        .case ( rbx == NULL )
            mov rbx,[rdi].type
            .switch pascal
            .case ( [rdi].flags & E_IS_TYPE )
                .if ( rbx && [rbx].typekind == TYPE_RECORD )
                    mov [rdi].value,[rbx].total_size
                .endif
                TokenAssign(rsi, rdi)
                mov [rsi].type,[rdi].type
            .case ( [rdi].kind == EXPR_REG && !( [rdi].flags & E_INDIRECT ) )
                mov rax,[rdi].base_reg
                SizeFromRegister([rax].asm_tok.tokval)
                mov [rsi].value,eax
                or  [rsi].flags,E_IS_TYPE
                mov rax,[rdi].base_reg
                imul eax,[rax].asm_tok.tokval,special_item
                lea rcx,SpecialTable
                .if ( ( [rcx+rax].special_item.value & OP_RGT8 ) && [rsi].mem_type == MT_EMPTY &&
                      byte ptr [rsi].value == ModuleInfo.wordsize )
                    mov rax,[rdi].base_reg
                    mov rbx,GetStdAssumeEx([rax].asm_tok.bytval)
                .else
                    xor ebx,ebx
                .endif
                .if ( rbx )
                    mov [rsi].type,rbx
                    mov [rsi].mem_type,[rbx].mem_type
                    mov [rsi].value,[rbx].total_size
                .else
                    mov [rsi].mem_type,[rdi].mem_type
                    mov [rsi].type,[rdi].type
                    .if ( [rsi].mem_type == MT_EMPTY )
                        MemtypeFromSize([rsi].value, &[rsi].mem_type)
                    .endif
                .endif
            .case ( [rdi].mem_type != MT_EMPTY || [rdi].flags & E_EXPLICIT )
                .if ( [rdi].mem_type != MT_EMPTY )
                    ; added v2.31.46
                    .if ( [rdi].kind == EXPR_FLOAT && [rdi].mem_type == MT_REAL16 )
                        xor eax,eax
                    .else
                        mov [rsi].mem_type,[rdi].mem_type
                        SizeFromMemtype([rdi].mem_type, [rdi].Ofssize, [rdi].type)
                    .endif
                    mov [rsi].value,eax
                .else
                    mov rbx,[rdi].type
                    .if rbx
                        mov [rsi].value,[rbx].total_size
                        mov [rsi].mem_type,[rbx].mem_type
                    .endif
                .endif
                or  [rsi].flags,E_IS_TYPE
                mov [rsi].type,[rdi].type
            .default
                mov [rsi].value,0
            .endsw
        .case ( [rbx].state == SYM_UNDEFINED )
            mov [rsi].kind,EXPR_ADDR
            mov [rsi].sym,rbx
            or  [rsi].flags,E_IS_TYPE
        .case ( [rbx].mem_type == MT_TYPE && !( [rdi].flags & E_EXPLICIT ) )
            or  [rsi].flags,E_IS_TYPE
            mov rbx,[rbx].type
            mov [rsi].type,rbx
            mov [rsi].value,[rbx].total_size
            mov [rsi].mem_type,[rbx].mem_type
        .default
            or  [rsi].flags,E_IS_TYPE
            .if [rsi].mem_type == MT_EMPTY
                mov [rsi].mem_type,[rdi].mem_type
            .endif
            mov rbx,sym
            .switch pascal
            .case ( [rdi].type && [rdi].mbr == NULL )
                mov [rsi].type_tok,[rdi].type_tok
                mov [rsi].type,[rdi].type
                mov [rsi].value,[rbx].total_size
            .case ( [rbx].mem_type == MT_PTR )
                mov [rsi].type_tok,[rdi].type_tok
                mov ecx,MT_NEAR
                .if ( [rbx].is_far )
                    mov ecx,MT_FAR
                .endif
                SizeFromMemtype( cl, [rbx].Ofssize, NULL )
                mov [rsi].value,eax
            .case ( [rbx].mem_type == MT_NEAR )
                mov ecx,GetSymOfssize( rbx )
                mov eax,2
                shl eax,cl
                or  eax,0xFF00
                mov [rsi].value,eax
            .case ( [rbx].mem_type == MT_FAR )
                .if GetSymOfssize( rbx )
                    mov eax,LS_FAR32
                .else
                    mov eax,LS_FAR16
                .endif
                mov [rsi].value,eax
            .default
                mov edx,GetSymOfssize( rbx )
                SizeFromMemtype( [rdi].mem_type, edx, [rbx].type )
                mov [rsi].value,eax
            .endsw
        .endsw
        .return( NOT_ERROR )
    .case UOT_DOT_MASK
    .case UOT_DOT_WIDTH
        .switch pascal
        .case ( [rdi].flags & E_IS_TYPE )
            mov rbx,[rdi].type
            .if ( [rbx].typekind != TYPE_RECORD )
                .return fnasmerr( 2019 )
            .endif
        .case ( [rdi].kind == EXPR_CONST )
            mov rbx,[rdi].mbr
        .default
            mov rbx,[rdi].sym
        .endsw
        .if ( oper == T_DOT_MASK )
            mov [rsi].value,0
            .if ( [rdi].flags & E_IS_TYPE )
                GetRecordMask(rbx)
            .else
                xor eax,eax
                xor edx,edx
                mov ecx,[rbx].offs
                mov edi,[rbx].total_size
                add edi,ecx
                .for ( : ecx < edi : ecx++ )
                    mov ebx,1
                    .if ecx < 32
                        shl ebx,cl
                        or  eax,ebx
                    .else
                        sub ecx,32
                        shl ebx,cl
                        or  edx,ebx
                        add ecx,32
                    .endif
                .endf
            .endif
            mov [rsi].value,eax
            mov [rsi].hvalue,edx
        .else
            .if ( [rdi].flags & E_IS_TYPE )
                mov rax,[rbx].structinfo
                mov rcx,[rax].struct_info.head
                .for ( : rcx : rcx = [rcx].sfield.next )
                    add [rsi].value,[rcx].sfield.total_size
                .endf
            .else
                mov [rsi].value,[rbx].total_size
            .endif
        .endif
        mov [rsi].kind,EXPR_CONST
       .return( NOT_ERROR )
    .case UOT_LOW64
        .if ( [rdi].kind == EXPR_FLOAT )
            .return ecx .if tofloat( rsi, rdi, 16 )
        .endif
        TokenAssign( rsi, rdi )
        mov [rsi].mem_type,MT_QWORD
        .if ( [rdi].kind == EXPR_ADDR && [rdi].inst != T_SEG )
            mov [rsi].inst,T_LOW64
            mov [rsi].mem_type,MT_EMPTY
        .endif
        mov [rsi].h64_l,0
        mov [rsi].h64_h,0
       .return NOT_ERROR
    .case UOT_HIGH64
        xor eax,eax
        .if ( [rdi].kind == EXPR_FLOAT )
            .return ecx .if tofloat( rsi, rdi, 16 )
        .elseif ( [rdi].flags & E_NEGATIVE && [rdi].h64_l == eax && [rdi].h64_h == eax  )
            dec eax
            mov [rdi].h64_l,eax
            mov [rdi].h64_h,eax
        .endif
        TokenAssign( rsi, rdi )
        mov [rsi].mem_type,MT_QWORD
        .if ( [rdi].kind == EXPR_ADDR && [rdi].inst != T_SEG )
            mov [rsi].inst,T_HIGH64
            mov [rsi].mem_type,MT_EMPTY
        .endif
        mov [rsi].llvalue,[rsi].hlvalue
        mov [rsi].h64_l,0
        mov [rsi].h64_h,0
       .return( NOT_ERROR )
    .case UOT_SQRT
        .if ( [rdi].kind != EXPR_FLOAT )
            .return( fnasmerr( 2176 ) )
        .endif
        TokenAssign( rsi, rdi )
        __sqrtq( rsi )
        .endc
    .endsw
    .return( NOT_ERROR )

unaryop endp


;--------------------------------------------------------------------------------
;
;--------------------------------------------------------------------------------

    assume rcx:expr_t

init_expr proc fastcall opnd:expr_t

    UNREFERENCED_PARAMETER(opnd)

    mov rcx,tmemset( rcx, 0, sizeof(expr) )
    mov [rcx].inst,EMPTY
    mov [rcx].kind,EXPR_EMPTY
    mov [rcx].mem_type,MT_EMPTY
    mov [rcx].Ofssize,USE_EMPTY
    ret

init_expr endp


    assume rcx:token_t

get_precedence proc fastcall item:token_t

    UNREFERENCED_PARAMETER(item)

    ;
    ; The following table is taken verbatim from MASM 6.1 Programmer's Guide,
    ; page 14, Table 1.3.
    ;
    ; 1            (), []
    ; 2            LENGTH, SIZE, WIDTH, MASK, LENGTHOF, SIZEOF
    ; 3            . (structure-field-name operator)
    ; 4            : (segment override operator), PTR
    ; 5            LROFFSET, OFFSET, SEG, THIS, TYPE
    ; 6            HIGH, HIGHWORD, LOW, LOWWORD
    ; 7            +, - (unary)
    ; 8            *, /, MOD, SHL, SHR
    ; 9            +, - (binary)
    ; 10           EQ, NE, LT, LE, GT, GE
    ; 11           NOT
    ; 12           AND
    ; 13           OR, XOR
    ; 14           OPATTR, SHORT, .TYPE
    ;
    ; The following table appears in QuickHelp online documentation for
    ; both MASM 6.0 and 6.1. It's slightly different!
    ;
    ; 1            LENGTH, SIZE, WIDTH, MASK
    ; 2            (), []
    ; 3            . (structure-field-name operator)
    ; 4            : (segment override operator), PTR
    ; 5            THIS, OFFSET, SEG, TYPE
    ; 6            HIGH, LOW
    ; 7            +, - (unary)
    ; 8            *, /, MOD, SHL, SHR
    ; 9            +, - (binary)
    ; 10           EQ, NE, LT, LE, GT, GE
    ; 11           NOT
    ; 12           AND
    ; 13           OR, XOR
    ; 14           SHORT, OPATTR, .TYPE, ADDR
    ;
    ; japheth: the first table is the prefered one. Reasons:
    ; - () and [] must be first.
    ; - it contains operators SIZEOF, LENGTHOF, HIGHWORD, LOWWORD, LROFFSET
    ; - ADDR is no operator for expressions. It's exclusively used inside
    ;   INVOKE directive.
    ;
    ; However, what's wrong in both tables is the precedence of
    ; the dot operator: Actually for both JWasm and Wasm the dot precedence
    ; is 2 and LENGTH, SIZE, ... have precedence 3 instead.
    ;
    ; Precedence of operator TYPE was 5 in original Wasm source. It has
    ; been changed to 4, as described in the Masm docs. This allows syntax
    ; "TYPE DWORD ptr xxx"
    ;
    ; v2.02: another case which is problematic:
    ;     mov al,BYTE PTR CS:[]
    ; Since PTR and ':' have the very same priority, the evaluator will
    ; first calculate 'BYTE PTR CS'. This is invalid, but didn't matter
    ; prior to v2.02 because register coercion was never checked for
    ; plausibility. Solution: priority of ':' is changed from 4 to 3.
    ;

    mov al,[rcx].token
    .switch al
    .case T_UNARY_OPERATOR
    .case T_BINARY_OPERATOR
        .return [rcx].precedence
    .case T_OP_BRACKET
    .case T_OP_SQ_BRACKET

        ; v2.08: with -Zm, the priority of [] and (), if
        ; used as binary operator, is 9 (like binary +/-).
        ; test cases: mov ax,+5[bx]
        ;             mov ax,-5[bx]

        mov eax,1
        .if ( ModuleInfo.m510 )
            mov eax,9
        .endif
        .return
    .case T_DOT
        .return 2
    .case T_COLON
        .return 3
    .case '*'
    .case '/'
        .return 8
    .case '+'
    .case '-'
        mov eax,7
        .if ( [rcx].specval )
            mov eax,9
        .endif
        .return
    .endsw
    fnasmerr( 2008, [rcx].string_ptr )
   .return ERROR

get_precedence endp


GetTypeSize proc fastcall mem_type:byte, ofssize:int_t

    UNREFERENCED_PARAMETER(mem_type)
    UNREFERENCED_PARAMETER(ofssize)

    .if ( cl == MT_ZWORD )
        .return 64
    .endif
    .if !( cl & MT_SPECIAL )
        and ecx,MT_SIZE_MASK
        inc ecx
        .return ecx
    .endif
    .if ( edx == USE_EMPTY )
        movzx edx,ModuleInfo.Ofssize
    .endif
    .if ( cl == MT_NEAR )
        mov eax,2
        mov ecx,edx
        shl eax,cl
        or  eax,0xFF00
    .elseif ( cl == MT_FAR )
        mov eax,LS_FAR16
        .if ( dl != USE16 )
            mov eax,2
            mov ecx,edx
            shl eax,cl
            add eax,2
            or  eax,0xFF00
        .endif
    .else
        xor eax,eax
    .endif
    ret

GetTypeSize endp

    assume rdx:nothing


; added v2.31.32

SetEvexOpt proc fastcall tok:token_t

    UNREFERENCED_PARAMETER(tok)

    .if ( [rcx-1*asm_tok].token == T_COMMA &&
          [rcx-2*asm_tok].token == T_REG &&
          [rcx-3*asm_tok].token == T_INSTRUCTION )

        mov eax,GetValueSp( [rcx-2*asm_tok].tokval )
        .if ( eax & OP_XMM )
            .if ( [rcx-3*asm_tok].tokval < VEX_START &&
                  [rcx-3*asm_tok].tokval >= T_ADDPD )
                .return( false )
            .endif
        .endif
    .endif
    or  [rcx].asm_tok.flags,T_EVEX_OPT
   .return( true )

SetEvexOpt endp


    assume rcx:nothing
    assume rbx:token_t

get_operand proc __ccall uses rsi rdi rbx opnd:expr_t, idx:ptr int_t, tokenarray:token_t, flags:byte

    local tmp:string_t
    local sym:asym_t
    local j:int_t
    local i:int_t
    local labelbuff[16]:char_t

    UNREFERENCED_PARAMETER(opnd)

    mov  rdx,idx
    mov  eax,[rdx]
    mov  i,eax
    mov  rdi,opnd
    mov  rbx,tokenarray
    imul eax,eax,asm_tok
    add  rbx,rax
    mov  al,[rbx].token

    .switch al
    .case '&'
        ;
        ; v2.30.24 -- mov mem,&mem
        ;
        .if ( Options.strict_masm_compat == FALSE && i > 2 &&
              [rbx-asm_tok].token == T_COMMA && [rbx-asm_tok*2].token != T_REG )

            inc i
            inc dword ptr [rdx]
            add rbx,asm_tok
            mov al,[rbx].token

            .if ( al == T_OP_SQ_BRACKET )
                .return( NOT_ERROR )
            .endif
            .gotosw
        .endif
        .return fnasmerr( 2008, [rbx].tokpos )
    .case T_NUM
        mov [rdi].kind,EXPR_CONST
        _atoow( rdi, [rbx].string_ptr, [rbx].numbase, [rbx].itemlen )
        .endc
    .case T_STRING
        .if ( [rbx].string_delim != '"' && [rbx].string_delim != "'" )
            .endc .if ( [rdi].flags & E_IS_OPEATTR )

            mov rcx,[rbx].string_ptr
            mov al,[rcx]
            .if ( [rbx].string_delim == 0 && ( al == '"' || al == "'" ) )
                fnasmerr( 2046 )
            .elseif [rbx].string_delim == '{'
                mov [rdi].kind,EXPR_EMPTY
                .if SetEvexOpt(rbx) == 0
                    mov [rdi].kind,EXPR_CONST
                    mov [rdi].quoted_string,rbx
                .endif
                .endc
            .else
                fnasmerr( 2167, [rbx].tokpos )
            .endif
            .return ERROR
        .endif
        mov [rdi].kind,EXPR_CONST
        mov [rdi].quoted_string,rbx
        mov rdx,[rbx].string_ptr
        inc rdx
        mov ecx,[rbx].stringlen
        .if ecx > 16
            mov ecx,16
        .endif
        .for ( : ecx: ecx-- )
            mov al,[rdx]
            inc rdx
            mov [rdi].chararray[rcx-1],al
        .endf
        .endc
    .case T_REG
        mov [rdi].kind,EXPR_REG
        mov [rdi].base_reg,rbx
        imul eax,[rbx].tokval,special_item
        lea rcx,SpecialTable
        movzx eax,[rcx+rax].special_item.cpu
        mov ecx,ModuleInfo.curr_cpu
        mov edx,ecx
        and ecx,P_EXT_MASK
        and edx,P_CPU_MASK
        mov esi,eax
        and esi,P_CPU_MASK

        .if ( ( eax & P_EXT_MASK ) && !( eax & ecx ) || edx < esi )

            .if flags & EXPF_IN_SQBR
                mov [rdi].kind,EXPR_ERROR
                fnasmerr( 2085 )
            .else
                .return fnasmerr( 2085 )
            .endif
        .endif

        .if ( ( i > 0 && [rbx-asm_tok].tokval == T_TYPEOF ) ||
              ( i > 1 && [rbx-asm_tok].token == T_OP_BRACKET &&
                [rbx-asm_tok*2].tokval == T_TYPEOF ) )

             ; v2.24 [reg + type reg] | [reg + type(reg)]

        .elseif ( flags & EXPF_IN_SQBR )

            lea rcx,SpecialTable
            imul eax,[rbx].tokval,special_item
            add rax,rcx

            .if ( [rax].special_item.sflags & SFR_IREG )

                or [rdi].flags,E_INDIRECT or E_ASSUMECHECK

            .elseif ( [rax].special_item.value & OP_SR )

                .if ( [rbx+asm_tok].token != T_COLON ||
                      ( ModuleInfo.strict_masm_compat && [rbx+asm_tok*2].token == T_REG ) )
                    .return fnasmerr( 2032 )
                .endif
            .else
                .if ( [rdi].flags & E_IS_OPEATTR )
                    mov [rdi].kind,EXPR_ERROR
                .else
                    .return fnasmerr( 2031 )
                .endif
            .endif
        .endif
        .endc

    .case T_BINARY_OPERATOR

        .if ( i && [rbx].tokval == T_DEFINED && [rbx+asm_tok].token == T_OP_BRACKET )

            add i,2
            add rbx,asm_tok*2
            mov [rdi].kind,EXPR_CONST
            mov [rdi].value,0
            mov [rdi].hvalue,0

            ; added v2.28.17: defined(...) returns -1

            mov rcx,idx
            mov eax,i

            .if ( [rbx].token == T_CL_BRACKET )

                mov [rcx],eax
                dec [rdi].value ; <> -- defined()
                dec [rdi].hvalue
               .endc
            .endif

            .if ( [rbx].token == T_NUM && [rbx+asm_tok].token == T_CL_BRACKET )

                dec [rdi].value ; <> -- defined()
                dec [rdi].hvalue
                inc eax
                mov [rcx],eax
               .endc
            .endif

            .if ( [rbx].token == T_ID && [rbx+asm_tok].token == T_CL_BRACKET )

                inc eax
                mov [rcx],eax
                .if ( SymFind([rbx].string_ptr) )
                    .if ( [rax].asym.state != SYM_UNDEFINED )

                        dec [rdi].value ; symbol defined
                        dec [rdi].hvalue
                       .endc
                    .endif
                .endif

                ; -- symbol not defined --

                .endc .if ( [rbx+asm_tok*2].token == T_FINAL ||
                            [rbx+asm_tok*2].tokval != T_AND  ||
                            [rbx-asm_tok*3].tokval == T_NOT )

                ; [not defined(symbol)] - return 0


                ; [defined(symbol) and]
                ; - return 0 and skip rest of line...

                add rbx,asm_tok*3
                mov edx,i
                add edx,3

                .for ( ecx = 0: edx < Token_Count: edx++, rbx += asm_tok )

                    .if ( [rbx].token == T_CL_BRACKET )

                        .break .if ( ecx == 0 )
                        dec ecx
                    .elseif ( [rbx].token == T_OP_BRACKET )
                        inc ecx
                    .endif
                .endf

                dec edx
                mov rcx,idx
                mov [rcx],edx
               .endc
            .endif
        .endif

    .case T_ID
        mov rsi,[rbx].string_ptr
        .if ( [rdi].flags & E_IS_DOT )

            mov rcx,[rdi].type
            xor eax,eax
            mov [rdi].value,eax

            .if ( rcx )
                SearchNameInStruct( rcx, rsi, rdi, 0 )
            .endif

            .if ( rax == NULL )

                .if SymFind(rsi)

                    .if ( [rax].asym.state == SYM_TYPE )

                        mov rcx,[rdi].type
                        .if !( rax == rcx || ( rcx && !( [rcx].asym.flags & S_ISDEFINED ) ) || ModuleInfo.oldstructs )
                            xor eax,eax
                        .endif

                    .elseif !( ModuleInfo.oldstructs && ( [rax].asym.state == SYM_STRUCT_FIELD ||
                              [rax].asym.state == SYM_EXTERNAL || [rax].asym.state == SYM_INTERNAL ) )
                        xor eax,eax
                    .endif
                .endif
            .endif
        .else

            mov edx,[rsi]
            or  dh,0x20
            .if ( dl == '@' && !( edx & 0x00FF0000 ) )
                .if ( dh == 'b' )
                    mov rsi,GetAnonymousLabel( &labelbuff, 0 )
                .elseif ( dh == 'f' )
                    mov rsi,GetAnonymousLabel( &labelbuff, 1 )
                .endif
            .endif
            SymFind( rsi )
        .endif

        .if ( rax == NULL || [rax].asym.state == SYM_UNDEFINED ||
              ( [rax].asym.state == SYM_TYPE && [rax].asym.typekind == TYPE_NONE ) ||
              [rax].asym.state == SYM_MACRO || [rax].asym.state == SYM_TMACRO )

            .if ( [rdi].flags & E_IS_OPEATTR )

                mov [rdi].kind,EXPR_ERROR
               .endc
            .endif
            .if ( rax && ( [rax].asym.state == SYM_MACRO || [rax].asym.state == SYM_TMACRO ) )
                .return fnasmerr( 2148, [rax].asym.name )
            .endif
            .if ( rax == NULL && ( [rbx-asm_tok].token == T_DOT &&
                 ( [rbx-asm_tok*2].token == T_ID || [rbx-asm_tok*2].token == T_CL_SQ_BRACKET ) ) )

                mov rdx,tokenarray
                .if ( [rdx].asm_tok.tokval == T_INVOKE )
                    .if ( FindDotSymbol( rbx ) )
                        jmp method_ptr
                    .endif
                .endif
            .endif

            .if ( Parse_Pass == PASS_1 && !( flags & EXPF_NOUNDEF ) )

                .if ( rax == NULL )

                    mov rcx,[rdi].type
                    .if ( rcx == NULL )

                        SymLookup(rsi)
                        mov sym,rax
                        mov [rax].asym.state,SYM_UNDEFINED
                        sym_add_table( &SymTables[TAB_UNDEF*symbol_queue], rax )
                        mov rax,sym

                    .elseif ( [rcx].asym.typekind != TYPE_NONE )

                        .return fnasmerr(2006, rsi)
                    .else

                        mov rax,nullmbr
                        .if ( !rax )
                            SymAlloc("")
                        .endif
                        mov [rdi].mbr,rax
                        mov [rdi].kind,EXPR_CONST
                       .endc
                    .endif
                .endif

            .else
                .if ( byte ptr [rsi+1] == '&' )
                    lea rsi,@CStr("@@")
                .endif
                .return fnasmerr( 2006, rsi )
            .endif
        .elseif ( [rax].asym.state == SYM_ALIAS )
            mov rax,[rax].asym.substitute
        .endif

method_ptr:

        or [rax].asym.flags,S_USED
        .switch [rax].asym.state

        .case SYM_TYPE
            mov rcx,[rax].dsym.structinfo
            .if ( [rax].asym.typekind != TYPE_TYPEDEF && [rcx].struct_info.flags & SI_ISOPEN )

                mov [rdi].kind,EXPR_ERROR
               .endc
            .endif
            .for ( : [rax].asym.type : rax = [rax].asym.type )
                .break .if rax == [rax].asym.type
            .endf

            mov cl,[rax].asym.mem_type
            mov [rdi].kind,EXPR_CONST
            mov [rdi].mem_type,cl
            or  [rdi].flags,E_IS_TYPE
            mov [rdi].type,rax
            and ecx,MT_SPECIAL_MASK

            .if ( [rax].asym.typekind == TYPE_RECORD )

                GetRecordMask(rax)
                mov [rdi].value,eax
                mov [rdi].hvalue,edx

            .elseif ( ecx == MT_ADDRESS )

                .if ( [rax].asym.mem_type == MT_PROC )

                    mov ecx,[rax].asym.total_size
                    mov [rdi].value,ecx
                    mov cl,[rax].asym.Ofssize
                    mov [rdi].Ofssize,cl
                .else

                    movzx edx,[rax].asym.Ofssize
                    GetTypeSize([rax].asym.mem_type, edx)
                    mov [rdi].value,eax
                .endif
            .else
                mov [rdi].value,[rax].asym.total_size
            .endif
            .endc

        .case SYM_STRUCT_FIELD
            mov [rdi].mbr,rax
            mov [rdi].kind,EXPR_CONST
            mov ecx,[rax].asym.offs
            add [rdi].value,ecx

            .for ( : [rax].asym.type : rax = [rax].asym.type )
            .endf

            mov cl,[rax].asym.mem_type
            mov [rdi].mem_type,cl
            mov [rdi].type,NULL

            .if ( [rax].asym.state == SYM_TYPE && [rax].asym.typekind != TYPE_TYPEDEF )

                mov [rdi].type,rax
ifdef USE_INDIRECTION
            .elseif ( cl == MT_PTR && [rax].asym.is_ptr && [rax].asym.ptr_memtype != MT_PROC )

                mov [rdi].type,[rax].asym.target_type
                mov [rdi].scale,0x80
endif
            .endif
            .endc

        .default

            mov rsi,rax
            assume rsi:asym_t

            mov [rdi].kind,EXPR_ADDR
            .if ( [rsi].flags & S_PREDEFINED && [rsi].sfunc_ptr )
                [rsi].sfunc_ptr(rsi, NULL)
            .endif
            .if ( [rsi].state == SYM_INTERNAL && [rsi].segm == NULL )

                mov [rdi].kind,EXPR_CONST
                mov [rdi].uvalue,[rsi].uvalue
                mov [rdi].hvalue,[rsi].value3264
                mov [rdi].mem_type,[rsi].mem_type

                .if ( al == MT_REAL16 && !ModuleInfo.strict_masm_compat )

                    mov [rdi].kind,EXPR_FLOAT
                    mov [rdi].float_tok,NULL
                    mov dword ptr [rdi].hlvalue,[rsi].total_length
                    mov dword ptr [rdi].hlvalue[4],[rsi].ext_idx
                .endif

            .elseif ( [rsi].state == SYM_EXTERNAL && [rsi].mem_type == MT_EMPTY &&
                     !( [rsi].sflags & S_ISCOM ) )

                or  [rdi].flags,E_IS_ABS
                mov [rdi].sym,rsi

            .else

                mov [rdi].label_tok,rbx
                mov rcx,[rsi].type

                .if ( rcx && [rcx].asym.mem_type != MT_EMPTY )
                    mov [rdi].mem_type,[rcx].asym.mem_type
                .else
                    mov [rdi].mem_type,[rsi].mem_type
                .endif

                .if ( [rsi].state == SYM_STACK )

                    mov eax,[rsi].offs
                    add eax,StackAdj
                    cdq
                    mov [rdi].value,eax
                    mov [rdi].hvalue,edx
                    or  [rdi].flags,E_INDIRECT
                    mov [rdi].base_reg,rbx
                    mov rcx,CurrProc
                    mov rcx,[rcx].dsym.procinfo
                    movzx eax,[rcx].proc_info.basereg
                    mov [rbx].tokval,eax
                    imul eax,eax,special_item
                    lea rcx,SpecialTable
                    mov al,[rcx+rax].special_item.bytval
                    mov [rbx].bytval,al
                .endif

                mov [rdi].sym,rsi

                .for ( : [rsi].type : rsi = [rsi].type )
                .endf
                .if ( [rsi].state == SYM_TYPE && [rsi].typekind != TYPE_TYPEDEF )
                    mov [rdi].type,rsi
                .else
                    mov [rdi].type,NULL
                .endif
            .endif
            .endc
        .endsw
        .endc

    .case T_STYPE
        mov [rdi].kind,EXPR_CONST
        imul ecx,[rbx].tokval,special_item
        lea rax,SpecialTable
        add rcx,rax
        mov [rdi].mem_type,[rcx].special_item.bytval
        mov eax,[rcx].special_item.sflags
        mov [rdi].Ofssize,al
        GetTypeSize([rdi].mem_type, eax)
        mov [rdi].value,eax
        or  [rdi].flags,E_IS_TYPE
        mov [rdi].type,NULL
       .endc

    .case T_RES_ID
        .if ( [rbx].tokval == T_FLAT )
            .if !( flags & EXPF_NOUNDEF )

                mov eax,ModuleInfo.curr_cpu
                and eax,P_CPU_MASK
                .return fnasmerr(2085) .if eax < P_386
                DefineFlatGroup()
            .endif
            mov [rdi].sym,ModuleInfo.flat_grp
            .return(ERROR) .if !eax
            mov [rdi].label_tok,rbx
            mov [rdi].kind,EXPR_ADDR

            ; added v2.31.32: typeof(addr ...)

        .elseif ( [rbx].tokval == T_ADDR && i > 2 &&
                  ( [rbx-asm_tok].tokval == T_TYPEOF || [rbx-asm_tok*2].tokval == T_TYPEOF ) &&
                  ( [rbx+asm_tok].token == T_ID || [rbx+asm_tok].token == T_OP_SQ_BRACKET ) )

            inc dword ptr [rdx]
            mov [rdi].kind,EXPR_ADDR
            mov [rdi].mem_type,MT_PTR
           .endc
        .else
            .return fnasmerr( 2008, [rbx].string_ptr )
        .endif
        .endc

    .case T_FLOAT
        mov [rdi].kind,EXPR_FLOAT
        mov [rdi].mem_type,MT_REAL16
        mov [rdi].float_tok,rbx
        atofloat( rdi, [rbx].string_ptr, 16, 0, [rbx].floattype )
       .endc

    .default
        .if ( [rdi].flags & E_IS_OPEATTR )
            .if ( [rbx].token == T_FINAL ||
                  [rbx].token == T_CL_BRACKET ||
                  [rbx].token == T_CL_SQ_BRACKET )
                .return( NOT_ERROR )
            .endif
            .endc
        .endif
        mov rcx,[rbx].string_ptr
        .if ( [rbx].token == T_BAD_NUM )
            fnasmerr( 2048, rcx )
        .elseif ( [rbx].token == T_COLON )
            fnasmerr( 2009 )
        .elseif ( islalpha( [rcx] ) )
            fnasmerr( 2016, [rbx].tokpos )
        .else
            fnasmerr( 2008, [rbx].tokpos )
        .endif
        .return
    .endsw

    mov rcx,idx
    inc dword ptr [rcx]
    .return( NOT_ERROR )

get_operand endp


    assume rcx:expr_t
    assume rdx:expr_t

check_both proc fastcall opnd1:expr_t, opnd2:expr_t, type1:int_t, type2:int_t

    .if ( [rcx].kind == type1 && [rdx].kind == type2 )
        .return 1
    .endif
    .if ( [rcx].kind == type2 && [rdx].kind == type1 )
        .return 1
    .endif
    .return 0

check_both endp


index_connect proc fastcall opnd1:expr_t, opnd2:expr_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    mov rax,[rdx].base_reg
    .if ( rax != NULL )
        .if ( [rcx].base_reg == NULL )
            mov [rcx].base_reg,rax
        .elseif ( [rcx].idx_reg == NULL )
            .if ( [rax].asm_tok.bytval == 4 )
                mov [rcx].idx_reg,[rcx].base_reg
                mov [rcx].base_reg,[rdx].base_reg
            .else
                mov [rcx].idx_reg,rax
            .endif
ifdef USE_INDIRECTION
        .elseif ( [rax-asm_tok*1].asm_tok.token == T_OP_SQ_BRACKET &&
                  [rax-asm_tok*2].asm_tok.token == T_ID &&
                  [rax-asm_tok*3].asm_tok.token == T_DOT )

            mov rax,[rcx].sym
            .if ( !( rax && [rax].asym.mem_type == MT_PTR && [rax].asym.is_ptr ) )
                .return fnasmerr( 2030 )
            .endif
endif
        .else
            .return fnasmerr( 2030 )
        .endif
        or [rcx].flags,E_INDIRECT
    .endif

    mov rax,[rdx].idx_reg
    .if ( rax != NULL )
        .if ( [rcx].idx_reg == NULL )
            mov [rcx].idx_reg,rax
            mov [rcx].scale,[rdx].scale
ifdef USE_INDIRECTION
        .elseif ( [rax-asm_tok*1].asm_tok.token == T_OP_SQ_BRACKET &&
                  [rax-asm_tok*2].asm_tok.token == T_ID &&
                  [rax-asm_tok*3].asm_tok.token == T_DOT )

            mov rax,[rcx].sym
            .if ( !( rax && [rax].asym.mem_type == MT_PTR && [rax].asym.is_ptr ) )
                .return fnasmerr( 2030 )
            .endif
endif
        .else
            .return fnasmerr( 2030 )
        .endif
        or [rcx].flags,E_INDIRECT
    .endif
    .return( NOT_ERROR )

index_connect endp


MakeConst proc fastcall opnd:expr_t

    UNREFERENCED_PARAMETER(opnd)

    .if ( ( [rcx].kind != EXPR_ADDR ) || [rcx].flags & E_INDIRECT )
        .return
    .endif

    .if ( [rcx].sym )

        .if ( Parse_Pass > PASS_1 )
            .return
        .endif

        mov rax,[rcx].sym
        .if ( !( ( [rax].asym.state == SYM_UNDEFINED && [rcx].inst == EMPTY ) ||
                 ( [rax].asym.state == SYM_EXTERNAL && [rax].asym.sflags & S_WEAK &&
                 [rcx].flags & E_IS_ABS ) ) )
            .return
        .endif
        mov [rcx].value,1
    .endif

    mov [rcx].label_tok,NULL
    mov rax,[rcx].mbr
    .if ( rax && [rax].asym.state != SYM_STRUCT_FIELD )
        .return
    .endif

    .if ( [rcx].override != NULL )
        .return
    .endif
    mov [rcx].inst,EMPTY
    mov [rcx].kind,EXPR_CONST
    and [rcx].flags,not E_EXPLICIT
    mov [rcx].mem_type,MT_EMPTY
    ret

MakeConst endp


    assume rax:asym_t
    assume rbx:asym_t

MakeConst2 proc fastcall uses rbx opnd1:expr_t, opnd2:expr_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    mov rax,[rcx].sym
    .if ( [rax].state == SYM_EXTERNAL )
        .return fnasmerr( 2018, [rax].name )
    .endif

    mov rbx,[rdx].sym
    .if ( ( [rax].state != SYM_UNDEFINED && [rbx].segm != [rax].segm &&
            [rbx].state != SYM_UNDEFINED ) || [rbx].state == SYM_EXTERNAL )
        .return fnasmerr( 2025 )
    .endif
    mov rax,[rcx].sym
    mov [rcx].kind,EXPR_CONST
    mov [rdx].kind,EXPR_CONST
    add [rcx].value,[rax].offs
    add [rdx].value,[rbx].offs
   .return NOT_ERROR

MakeConst2 endp


fix_struct_value proc fastcall opnd:expr_t

    UNREFERENCED_PARAMETER(opnd)

    mov rax,[rcx].mbr
    .if ( rax && [rax].state == SYM_TYPE )
        add [rcx].value,[rax].total_size
        mov [rcx].mbr,NULL
    .endif
    ret

fix_struct_value endp

    assume rax:nothing


check_direct_reg proc fastcall opnd1:expr_t, opnd2:expr_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    .if ( [rcx].kind == EXPR_REG && !( [rcx].flags & E_INDIRECT ) ||
          [rdx].kind == EXPR_REG && !( [rdx].flags & E_INDIRECT ) )
        .return ERROR
    .endif
    .return NOT_ERROR

check_direct_reg endp


    assume rsi:expr_t
    assume rdi:expr_t
    assume rbx:nothing

plus_op proc fastcall uses rsi rdi rbx opnd1:expr_t, opnd2:expr_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    mov rsi,rcx
    mov rdi,rdx

    .ifd ( check_direct_reg( rcx, rdx ) == ERROR )
        .return fnasmerr( 2032 )
    .endif

    .if ( [rsi].kind == EXPR_REG )
        mov [rsi].kind,EXPR_ADDR
    .endif
    .if ( [rdi].kind == EXPR_REG )
       mov [rdi].kind,EXPR_ADDR
    .endif

    .if ( [rdi].override )
        .if ( [rsi].override )

            mov rbx,[rsi].override
            mov rax,[rdi].override
            mov al,[rax].asm_tok.token
            .if ( al == [rbx].asm_tok.token )
                .return fnasmerr( 3013 )
            .endif
        .endif
        mov [rsi].override,[rdi].override
    .endif

    .if ( [rsi].kind == EXPR_CONST && [rdi].kind == EXPR_CONST )

        add [rsi].llvalue,[rdi].llvalue

    .elseif ( [rsi].kind == EXPR_FLOAT && [rdi].kind == EXPR_FLOAT )

        __addq( rsi, rdi )

    .elseif ( ( [rsi].kind == EXPR_ADDR && [rdi].kind == EXPR_ADDR ) )

        fix_struct_value(rsi)
        fix_struct_value(rdi)
        .ifd ( index_connect( rsi, rdi ) == ERROR )
            .return
        .endif

        .if ( [rdi].sym != NULL )

            mov rax,[rsi].sym
            .if ( rax && [rax].asym.state != SYM_UNDEFINED )
                mov rax,[rdi].sym
                .if ( [rax].asym.state != SYM_UNDEFINED )
                    .return( fnasmerr( 2101 ) )
                .endif
            .endif

            mov [rsi].label_tok,[rdi].label_tok
            mov [rsi].sym,[rdi].sym
            .if ( [rsi].mem_type == MT_EMPTY )
                mov [rsi].mem_type,[rdi].mem_type
            .endif
            .if ( [rdi].inst != EMPTY )
                mov [rsi].inst,[rdi].inst
            .endif
        .endif

        add [rsi].llvalue,[rdi].llvalue
        .if ( [rdi].type )
            mov [rsi].type,[rdi].type
        .endif

    .elseif check_both( rsi, rdi, EXPR_CONST, EXPR_ADDR )

        .if ( [rsi].kind == EXPR_CONST )

            add [rdi].llvalue,[rsi].llvalue

            .if ( [rsi].flags & E_INDIRECT )
                or [rdi].flags,E_INDIRECT
            .endif

            .if ( [rsi].flags & E_EXPLICIT )

                or  [rdi].flags,E_EXPLICIT
                mov [rdi].mem_type,[rsi].mem_type

            .elseif ( [rdi].mem_type == MT_EMPTY )

                mov [rdi].mem_type,[rsi].mem_type
            .endif

            .if ( [rdi].mbr == NULL )
                mov [rdi].mbr,[rsi].mbr
            .endif
            .if ( [rdi].type )
                mov [rsi].type,[rdi].type
            .endif
            TokenAssign( rsi, rdi )

        .else

            add [rsi].llvalue,[rdi].llvalue
            .if ( [rdi].mbr )
                mov [rsi].mbr,[rdi].mbr
                mov [rsi].mem_type,[rdi].mem_type
            .elseif ( [rsi].mem_type == MT_EMPTY && !( [rdi].flags & E_IS_TYPE ) )
                mov [rsi].mem_type,[rdi].mem_type
            .endif
        .endif
        fix_struct_value( rsi )

    .else
        .return ConstError( rsi, rdi )
    .endif
    .return( NOT_ERROR )

plus_op endp


minus_op proc fastcall uses rsi rdi rbx opnd1:expr_t, opnd2:expr_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    mov rsi,rcx
    mov rdi,rdx

    .ifd ( check_direct_reg( rsi, rdi ) == ERROR )
        .return fnasmerr( 2032 )
    .endif

    mov rax,[rdi].sym
    .if ( !( [rsi].kind == EXPR_ADDR && [rdi].kind == EXPR_ADDR &&
           rax && [rax].asym.state == SYM_UNDEFINED ) )
        MakeConst(rdi)
    .endif

    .switch pascal
    .case ( [rsi].kind == EXPR_CONST && [rdi].kind == EXPR_CONST )
        sub [rsi].llvalue,[rdi].llvalue
    .case ( [rsi].kind == EXPR_FLOAT && [rdi].kind == EXPR_FLOAT )
        __subq( rsi, rdi )
    .case ( [rsi].kind == EXPR_ADDR && [rdi].kind == EXPR_CONST )
        sub [rsi].llvalue,[rdi].llvalue
        fix_struct_value(rsi)
    .case ( [rsi].kind == EXPR_ADDR && [rdi].kind == EXPR_ADDR )
        fix_struct_value(rsi)
        fix_struct_value(rdi)
        .if( [rdi].flags & E_INDIRECT )
            .return fnasmerr( 2032 )
        .endif
        .if( [rdi].label_tok == NULL )
            sub [rsi].llvalue,[rdi].llvalue
            .if( [rdi].flags & E_INDIRECT )
                or [rsi].flags,E_INDIRECT
            .endif
        .else
            .if ( [rsi].label_tok == NULL || [rsi].sym == NULL || [rdi].sym == NULL )
                .return fnasmerr( 2094 )
            .endif
            mov rbx,[rsi].sym
            add [rsi].value,[rbx].asym.offs
            mov rax,[rdi].sym
            .if ( Parse_Pass > PASS_1 )
                .if ( ( [rax].asym.state == SYM_EXTERNAL || [rbx].asym.state == SYM_EXTERNAL ) &&
                    rax != [rsi].sym )
                    .return( fnasmerr( 2018, [rbx].asym.name ) )
                .endif
                .if ( [rbx].asym.segm != [rax].asym.segm )
                    .return( fnasmerr( 2025 ) )
                .endif
                mov rax,[rdi].sym
            .endif
            mov [rsi].kind,EXPR_CONST
            .if ( [rbx].asym.state == SYM_UNDEFINED || [rax].asym.state == SYM_UNDEFINED )
                mov [rsi].value,1
                .if ( [rbx].asym.state != SYM_UNDEFINED )
                    mov [rsi].sym,rax
                    mov [rsi].label_tok,[rdi].label_tok
                .endif
                mov [rsi].kind,EXPR_ADDR
            .else
                sub [rsi].value,[rax].asym.offs
                sbb [rsi].hvalue,0
                sub [rsi].llvalue,[rdi].llvalue
                mov [rsi].label_tok,NULL
                mov [rsi].sym,NULL
            .endif
            .if !( [rsi].flags & E_INDIRECT )
                .if [rsi].inst == T_OFFSET && [rdi].inst == T_OFFSET
                    mov [rsi].inst,EMPTY
                .endif
            .else
                mov [rsi].kind,EXPR_ADDR
            .endif
            and [rsi].flags,not E_EXPLICIT
            mov [rsi].mem_type,MT_EMPTY
        .endif
    .case ( [rsi].kind == EXPR_REG && [rdi].kind == EXPR_CONST )
        .if ( [rdi].flags & E_INDIRECT )
            or [rsi].flags,E_INDIRECT
        .endif
        mov [rsi].kind,EXPR_ADDR
        __mul64( -1, [rdi].llvalue )
        .s8 [rsi].expr.llvalue
    .default
        .return ConstError( rsi, rdi )
    .endsw
    .return( NOT_ERROR )

minus_op endp


    assume rcx:expr_t
    assume rdx:expr_t

struct_field_error proc fastcall opnd:expr_t

    .if ( [rcx].flags & E_IS_OPEATTR )

        mov [rcx].kind,EXPR_ERROR
       .return NOT_ERROR
    .endif
    .return( fnasmerr( 2166 ) )

struct_field_error endp


dot_op proc fastcall uses rsi rdi rbx opnd1:expr_t, opnd2:expr_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    mov rsi,rcx
    mov rdi,rdx

    .ifd ( check_direct_reg( rsi, rdi ) == ERROR )
        .return( fnasmerr( 2032 ) )
    .endif

    .if ( [rsi].kind == EXPR_REG )
        mov [rsi].kind,EXPR_ADDR
    .endif
    .if ( [rdi].kind == EXPR_REG )
        mov [rdi].kind,EXPR_ADDR
    .endif

    mov rax,[rdi].sym
    .if ( rax && [rax].asym.state == SYM_UNDEFINED && Parse_Pass == PASS_1 )

        mov rax,nullstruct
        .if ( !rax )
            mov nullstruct,CreateTypeSymbol( NULL, "", 0 )
        .endif
        mov [rdi].type,rax
        or  [rdi].flags,E_IS_TYPE
        mov [rdi].sym,NULL
        mov [rdi].kind,EXPR_CONST
    .endif

    .if ( [rsi].kind == EXPR_ADDR && [rdi].kind == EXPR_ADDR )

        .if ( [rdi].mbr == NULL && !ModuleInfo.oldstructs )
            .return( struct_field_error( rsi ) )
        .endif
        .ifd ( index_connect( rsi, rdi ) == ERROR )
            .return
        .endif

        mov rax,[rdi].sym
        .if ( rax )

            mov rbx,[rsi].sym
            .if ( rbx && [rbx].asym.state != SYM_UNDEFINED && [rax].asym.state != SYM_UNDEFINED )
                .return( fnasmerr( 2101 ) )
            .endif
            mov [rsi].label_tok,[rdi].label_tok
            mov [rsi].sym,[rdi].sym
        .endif

        mov rax,[rdi].mbr
        .if ( rax )
            mov [rsi].mbr,rax
        .endif
        add [rsi].value,[rdi].value

        .if ( !( [rsi].flags & E_EXPLICIT ) )
            mov [rsi].mem_type,[rdi].mem_type
        .endif
        mov rax,[rdi].type
        .if ( rax )
            mov [rsi].type,rax
        .endif

    .elseif ( [rsi].kind == EXPR_CONST && [rdi].kind == EXPR_ADDR )

        .if ( [rsi].flags & E_IS_TYPE && [rsi].type )

            and [rdi].flags,not E_ASSUMECHECK
            mov [rsi].value,0
            mov [rsi].hvalue,0
        .endif

        .if ( ( !ModuleInfo.oldstructs ) && ( !( [rsi].flags & E_IS_TYPE ) && [rsi].mbr == NULL ) )
            .return( struct_field_error( rsi ) )
        .endif

        mov rax,[rsi].mbr
        .if ( rax && [rax].asym.state == SYM_TYPE )
            mov [rsi].value,[rax].asym.offs
            mov [rsi].hvalue,0
        .endif

        .if ( [rsi].flags & E_INDIRECT )
            or [rdi].flags,E_INDIRECT
        .endif
        add [rdi].llvalue,[rsi].llvalue
        .if ( [rdi].mbr )
            mov [rsi].type,[rdi].type
        .endif
        TokenAssign( rsi, rdi )

    .elseif ( [rsi].kind == EXPR_ADDR && [rdi].kind == EXPR_CONST )

        .if ( !ModuleInfo.oldstructs && ( [rdi].type == NULL || !( [rdi].flags & E_IS_TYPE ) ) &&
              [rdi].mbr == NULL )
            .return( struct_field_error( rsi ) )
        .endif

        .if ( [rdi].flags & E_IS_TYPE && [rdi].type )

            and [rsi].flags,not E_ASSUMECHECK

            ; v2.37: adjust for type's size only (japheth)

            mov rbx,[rdi].type
            sub [rdi].value,[rbx].asym.total_size
            sbb [rdi].hvalue,0
        .endif

        mov rbx,[rdi].mbr
        .if ( rbx && [rbx].asym.state == SYM_TYPE )

            mov [rsi].value,[rbx].asym.offs
            mov [rsi].hvalue,0
        .endif

        add [rsi].value64,[rdi].value64
        mov [rsi].mem_type,[rdi].mem_type
        mov [rsi].type,[rdi].type

        .if ( rbx )

            mov [rsi].mbr,rbx

ifdef USE_INDIRECTION

            .if ( rax && [rdi].flags & E_IS_DOT )
                .if ( [rsi].flags & E_EXPLICIT && [rdi].scale == 0x80 )
                    mov [rsi].type,NULL
                .else
                    or [rsi].flags,E_IS_DOT
                .endif
            .endif
endif
        .endif

    .elseif ( [rsi].kind == EXPR_CONST && [rdi].kind == EXPR_CONST )

        .if ( [rdi].mbr == NULL && !ModuleInfo.oldstructs )
            .return( struct_field_error( rsi ) )
        .endif

        .if ( [rsi].type != NULL )

            .if ( [rsi].mbr != NULL )
                add [rsi].llvalue,[rdi].llvalue
            .else
                mov [rsi].llvalue,[rdi].llvalue
            .endif

            mov [rsi].mbr,[rdi].mbr
            mov [rsi].mem_type,[rdi].mem_type
            and [rsi].flags,not E_IS_TYPE

            .if ( [rdi].flags & E_IS_TYPE )
                or [rsi].flags,E_IS_TYPE
            .endif
            .if ( [rsi].type != [rdi].type )
                mov [rsi].type,[rdi].type
            .else
                mov [rsi].type,NULL
            .endif

        .else

            add [rsi].llvalue,[rdi].llvalue
            mov [rsi].mbr,[rdi].mbr
            mov [rsi].mem_type,[rdi].mem_type
        .endif
    .else
        .return( struct_field_error( rsi ) )
    .endif
    .return( NOT_ERROR )

dot_op endp


colon_op proc fastcall uses rsi rdi rbx opnd1:expr_t, opnd2:expr_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    mov rsi,rcx
    mov rdi,rdx

    mov rax,[rdi].override
    .if ( rax )
        .if ( ( [rsi].kind == EXPR_REG && [rax].asm_tok.token == T_REG ) ||
              ( [rsi].kind == EXPR_ADDR && [rax].asm_tok.token == T_ID ) )
            .return( fnasmerr( 3013 ) )
        .endif
    .endif

    .switch [rdi].kind
    .case EXPR_REG
        .if ( !( [rdi].flags & E_INDIRECT ) )
            .return fnasmerr( 2032 )
        .endif
        .endc
    .case EXPR_FLOAT
        .return fnasmerr( 2050 )
    .endsw

    .if ( [rsi].kind == EXPR_REG )

        .if ( [rsi].idx_reg != NULL )
            .return( fnasmerr( 2032 ) )
        .endif

        mov rax,[rsi].base_reg
        imul eax,[rax].asm_tok.tokval,special_item
        lea rbx,SpecialTable

        .if !( [rbx+rax].special_item.value & OP_SR )
            .return( fnasmerr( 2096 ) )
        .endif

        mov [rdi].override,[rsi].base_reg
        .if ( [rsi].flags & E_INDIRECT )
            or [rdi].flags,E_INDIRECT
        .endif
        .if ( [rdi].kind == EXPR_CONST )
            mov [rdi].kind,EXPR_ADDR
        .endif

        .if ( [rsi].flags & E_EXPLICIT )

            or  [rdi].flags,E_EXPLICIT
            mov [rdi].mem_type,[rsi].mem_type
            mov [rdi].Ofssize,[rsi].Ofssize
        .endif

        TokenAssign( rsi, rdi )

        .if ( [rdi].type )
            mov [rsi].type,[rdi].type
        .endif

    .elseif ( [rsi].kind == EXPR_ADDR && [rsi].override == NULL && [rsi].inst == EMPTY &&
              [rsi].value == 0 && [rsi].sym && [rsi].base_reg == NULL && [rsi].idx_reg == NULL )

        mov rax,[rsi].sym
        .if ( [rax].asym.state == SYM_GRP || [rax].asym.state == SYM_SEG )

            mov [rdi].kind,EXPR_ADDR
            mov [rdi].override,[rsi].label_tok
            .if ( [rsi].flags & E_INDIRECT )
                or [rdi].flags,E_INDIRECT
            .endif

            .if ( [rsi].flags & E_EXPLICIT )

                or  [rdi].flags,E_EXPLICIT
                mov [rdi].mem_type,[rsi].mem_type
                mov [rdi].Ofssize,[rsi].Ofssize
            .endif

            TokenAssign( rsi, rdi )
            mov [rsi].type,[rdi].type

        .elseif ( Parse_Pass > PASS_1 || [rax].asym.state != SYM_UNDEFINED )
            .return fnasmerr( 2096 )
        .endif
    .else
        .return fnasmerr( 2096 )
    .endif
    .return( NOT_ERROR )

colon_op endp


positive_op proc fastcall uses rsi rdi opnd1:expr_t, opnd2:expr_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    mov rsi,rcx
    mov rdi,rdx

    MakeConst(rdi)
    .if ( [rdi].kind == EXPR_CONST )

        mov [rsi].kind,EXPR_CONST
        mov [rsi].llvalue,[rdi].llvalue
        mov [rsi].hlvalue,[rdi].hlvalue

    .elseif ( [rdi].kind == EXPR_FLOAT )

        mov [rsi].kind,EXPR_FLOAT
        mov [rsi].mem_type,[rdi].mem_type
        mov [rsi].llvalue,[rdi].llvalue
        mov [rsi].hlvalue,[rdi].hlvalue
        and [rsi].chararray[15],not 0x80
        mov [rsi].flags,[rdi].flags

    .else
        .return( fnasmerr( 2026 ) )
    .endif
    .return( NOT_ERROR )

positive_op endp


negative_op proc fastcall uses rsi rdi rbx opnd1:expr_t, opnd2:expr_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    mov rsi,rcx
    mov rdi,rdx

    MakeConst( rdi )

    .if ( [rdi].kind == EXPR_CONST )

        mov [rsi].flags,[rdi].flags
        xor [rsi].flags,E_NEGATIVE
        mov [rsi].kind,EXPR_CONST
ifdef _WIN64
        mov rax,[rdi].llvalue
        mov rdx,[rdi].hlvalue
        neg rax
        mov [rsi].llvalue,rax
        sbb eax,eax
        .if ( rdx )
            bt  eax,0
            adc rdx,0
            neg rdx
            mov [rsi].hlvalue,rdx
        .endif
else
        mov eax,[edi].value
        mov ebx,[edi].hvalue
        neg eax
        adc ebx,0
        neg ebx
        mov [esi].value,eax
        mov [esi].hvalue,ebx
        sbb eax,eax
        mov ebx,[edi].h64_h

        .if ( [edi].h64_l || ebx )

            bt  eax,0
            mov eax,[edi].h64_l
            adc eax,0
            neg eax
            adc ebx,0
            neg ebx
            mov [esi].h64_l,eax
            mov [esi].h64_h,ebx
        .endif
endif
    .elseif ( [rdi].kind == EXPR_FLOAT )

        mov [rsi].kind,EXPR_FLOAT
        mov [rsi].mem_type,[rdi].mem_type
        mov [rsi].llvalue,[rdi].llvalue
        mov [rsi].hlvalue,[rdi].hlvalue
        xor [rsi].chararray[15],0x80
        mov [rsi].flags,[rdi].flags
        xor [rsi].flags,E_NEGATIVE
    .else
        .return fnasmerr( 2026 )
    .endif
    .return( NOT_ERROR )

negative_op endp


    assume rdi:nothing
    assume rbx:asym_t
    assume rsi:expr_t

CheckAssume proc fastcall uses rsi rbx opnd:expr_t

    UNREFERENCED_PARAMETER(opnd)

    mov rsi,rcx
    .if ( [rsi].flags & E_EXPLICIT )
        mov rbx,[rsi].type
        .if ( rbx && [rbx].mem_type == MT_PTR )
            .if ( [rbx].is_ptr == 1 )
                mov [rsi].mem_type,[rbx].ptr_memtype
                mov [rsi].type,[rbx].target_type
               .return
            .endif
        .endif
    .endif

    xor ebx,ebx
    .if ( [rsi].idx_reg )

        mov rax,[rsi].idx_reg
        mov rbx,GetStdAssumeEx( [rax].asm_tok.bytval )
    .endif
    .if ( !rbx && [rsi].base_reg )
        mov rax,[rsi].base_reg
        mov rbx,GetStdAssumeEx( [rax].asm_tok.bytval )
    .endif

    .if ( rbx )
        .if ( [rbx].mem_type == MT_TYPE )
            mov [rsi].type,[rbx].type
        .elseif ( [rbx].is_ptr == 1 )
            mov [rsi].type,[rbx].target_type
            .if ( [rbx].target_type )
                mov rbx,[rbx].target_type
                mov [rsi].mem_type,[rbx].mem_type
            .else
                mov [rsi].mem_type,[rbx].ptr_memtype
            .endif
        .endif
    .endif
    ret

CheckAssume endp

    assume rbx:nothing


check_streg proc fastcall opnd1:expr_t, opnd2:expr_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    .if ( [rcx].scale > 0 )
        .return( fnasmerr( 2032 ) )
    .endif
    inc [rcx].scale
    .if ( [rdx].kind != EXPR_CONST )
        .return( fnasmerr( 2032 ) )
    .endif
    mov [rcx].st_idx,[rdx].value
   .return( NOT_ERROR )

check_streg endp


    assume rsi:asym_t
    assume rdi:asym_t

cmp_types proc fastcall uses rsi rdi rbx opnd1:expr_t, opnd2:expr_t, trueval:int_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)
    UNREFERENCED_PARAMETER(trueval)

    mov rsi,[rcx].type
    mov rdi,[rdx].type

    .if ( [rcx].mem_type == MT_PTR && [rdx].mem_type == MT_PTR )

        mov rbx,rcx
        .if !rsi
            mov rax,[rcx].type_tok
            mov rsi,SymFind( [rax].asm_tok.string_ptr )
            mov rdx,opnd2
        .endif
        .if !rdi
            mov rax,[rdx].type_tok
            mov rdi,SymFind( [rax].asm_tok.string_ptr )
        .endif
        .if ( [rsi].is_ptr == [rdi].is_ptr &&
              [rsi].ptr_memtype == [rdi].ptr_memtype &&
              [rsi].target_type == [rdi].target_type )
            mov eax,trueval
        .else
            mov eax,trueval
            not eax
        .endif
        cdq
        mov rcx,rbx
        mov [rcx].value,eax
        mov [rcx].hvalue,edx

    .else

        .if ( rsi && [rsi].typekind == TYPE_TYPEDEF && [rsi].is_ptr == 0 )
            mov [rcx].type,NULL
        .endif
        .if ( rdi && [rdi].typekind == TYPE_TYPEDEF && [rdi].is_ptr == 0 )
            mov [rdx].type,NULL
        .endif
        .if ( [rcx].mem_type == [rdx].mem_type && [rcx].type == [rdx].type )
            mov eax,trueval
        .else
            mov eax,trueval
            not eax
        .endif
        cdq
        mov [rcx].value,eax
        mov [rcx].hvalue,edx
    .endif
    ret

cmp_types endp


    assume rcx:nothing
    assume rdx:nothing

    assume rsi:expr_t
    assume rdi:expr_t
    assume rbx:token_t

calculate proc __ccall uses rsi rdi rbx opnd1:expr_t, opnd2:expr_t, oper:token_t

  local sym:asym_t
  local opnd:expr

    mov rsi,opnd1
    mov rdi,opnd2
    mov rbx,oper

    mov [rsi].quoted_string,NULL

    .if ( ( [rdi].h64_l || [rdi].h64_h ) && [rdi].mem_type != MT_REAL16 )

        .if ( !( [rbx].token == T_UNARY_OPERATOR && [rdi].kind == EXPR_CONST &&
              ModuleInfo.Ofssize == USE64 ) )

            .if ( !( [rdi].flags & E_IS_OPEATTR || ( ( [rbx].token == '+' ||
                  [rbx].token == '-' ) && [rbx].specval == 0 ) ) )

                .return( fnasmerr( 2084, [rdi].hlvalue, [rdi].value64 ) )
            .endif
        .endif
    .endif

    movzx eax,[rbx].token

    .switch eax

    .case T_OP_SQ_BRACKET

        .if ( [rdi].flags & E_ASSUMECHECK )

            and [rdi].flags,not E_ASSUMECHECK

            .if ( [rsi].sym == NULL )
                CheckAssume(rdi)
            .endif
        .endif
        .if ( [rsi].kind == EXPR_EMPTY )

            TokenAssign(rsi, rdi)
            mov [rsi].type,[rdi].type

            .if ( [rsi].flags & E_IS_TYPE && [rsi].kind == EXPR_CONST )

                and [rsi].flags,not E_IS_TYPE
            .endif
            .endc
        .endif
        .if ( [rsi].flags & E_IS_TYPE && [rsi].type == NULL &&
              ( [rdi].kind == EXPR_ADDR || [rdi].kind == EXPR_REG ) )
            .return( fnasmerr( 2009 ) )
        .endif
        mov rax,[rsi].base_reg
        .if ( rax && [rax].asm_tok.tokval == T_ST )
            .return( check_streg( rsi, rdi ) )
        .endif
        .return( plus_op( rsi, rdi ) )

    .case T_OP_BRACKET
        .if ( [rsi].kind == EXPR_EMPTY )
            TokenAssign( rsi, rdi )
            mov [rsi].type,[rdi].type
           .endc
        .endif
        .if ( [rsi].flags & E_IS_TYPE && [rdi].kind == EXPR_ADDR )
            .return( fnasmerr( 2009 ) )
        .endif
        mov rax,[rsi].base_reg
        .if ( [rsi].base_reg && [rax].asm_tok.tokval == T_ST )
            .return( check_streg( rsi, rdi ) )
        .endif
        .return( plus_op( rsi, rdi ) )

    .case '+'
        .if ( [rbx].specval == 0 )
            .return( positive_op( rsi, rdi ) )
        .endif
        .ifd ( EvalOperator( rsi, rdi, rbx ) == ERROR )
            .return( plus_op( rsi, rdi ) )
        .endif
        .endc

    .case '-'
        .if ( [rbx].specval == 0 )
            .return( negative_op( rsi, rdi ) )
        .endif
        .ifd ( EvalOperator( rsi, rdi, rbx ) == ERROR )
            .return(minus_op( rsi, rdi ) )
        .endif
        .endc

    .case T_DOT
        .return( dot_op( rsi, rdi ) )

    .case T_COLON
        .return(colon_op( rsi, rdi ) )

    .case '*'
        MakeConst(rsi)
        MakeConst(rdi)
        .if ( [rsi].kind == EXPR_CONST && [rdi].kind == EXPR_CONST )

            __mul64( [rdi].llvalue, [rsi].llvalue )
            .s8 [rsi].llvalue

        .elseif check_both( rsi, rdi, EXPR_REG, EXPR_CONST )

            .ifd ( check_direct_reg( rsi, rdi ) == ERROR )
                .return fnasmerr( 2032 )
            .endif
            .if ( [rdi].kind == EXPR_REG )

                mov [rsi].idx_reg,[rdi].base_reg
                mov [rsi].scale,[rsi].value
                mov [rsi].value,0
            .else
                mov [rsi].idx_reg,[rsi].base_reg
                mov [rsi].scale,[rdi].value
            .endif
            .if ( [rsi].scale == 0 )
                .return( fnasmerr( 2083 ) )
            .endif
            mov [rsi].base_reg,NULL
            or  [rsi].flags,E_INDIRECT
            mov [rsi].kind,EXPR_ADDR

        .elseif ( [rsi].kind == EXPR_FLOAT && [rdi].kind == EXPR_FLOAT )

            __mulq( rsi, rdi )

        .elseifd ( EvalOperator( rsi, rdi, rbx ) == ERROR )

            .return( ConstError( rsi, rdi ) )
        .endif
        .endc

    .case '/'
        .if ( ( [rsi].kind == EXPR_FLOAT && [rdi].kind == EXPR_FLOAT ) )
            __divq( rsi, rdi )
            .endc
        .endif
        .endc .ifd ( EvalOperator( rsi, rdi, rbx ) != ERROR )
        MakeConst(rsi)
        MakeConst(rdi)
        .if ( !( [rsi].kind == EXPR_CONST && [rdi].kind == EXPR_CONST ) )
            .return( ConstError( rsi, rdi ) )
        .endif
        .if ( [rdi].l64_l == 0 && [rdi].l64_h == 0 )
            .return( fnasmerr( 2169 ) )
        .endif
        __div64( [rsi].llvalue, [rdi].llvalue )
        .s8 [rsi].llvalue
        .endc

    .case T_BINARY_OPERATOR
        .if ( [rbx].tokval == T_PTR )
            .if ( !( [rsi].flags & E_IS_TYPE ) )
                mov rax,[rsi].sym
                .if ( rax && [rax].asym.state == SYM_UNDEFINED )
                    CreateTypeSymbol( rax, NULL, 1 )
                    mov [rsi].type,[rsi].sym
                    mov [rsi].sym,NULL
                    or  [rsi].flags,E_IS_TYPE
                .else
                    .return( fnasmerr( 2010 ) )
                .endif
            .endif

            or [rdi].flags,E_EXPLICIT

            .if ( [rdi].kind == EXPR_REG && ( !( [rdi].flags & E_INDIRECT ) || [rdi].flags & E_ASSUMECHECK ) )

                mov  rax,[rdi].base_reg
                mov  ecx,[rax].asm_tok.tokval
                imul eax,ecx,special_item
                lea  rdx,SpecialTable

                .if ( [rdx+rax].special_item.value & OP_SR )
                    .if ( [rsi].value != 2 && [rsi].value != 4 )
                        .return( fnasmerr( 2032 ) )
                    .endif
                .else
                    SizeFromRegister( ecx )
                    .if ( [rsi].value != eax )
                        .return( fnasmerr( 2032 ) )
                    .endif
                .endif
            .elseif ( [rdi].kind == EXPR_FLOAT )
                .if !( [rsi].mem_type & MT_FLOAT )
                    .return( fnasmerr( 2050 ) )
                .endif
            .endif
            mov [rdi].mem_type,[rsi].mem_type
            mov [rdi].Ofssize,[rsi].Ofssize
            .if [rdi].flags & E_IS_TYPE
                mov [rdi].value,[rsi].value
            .endif
            .if ( [rsi].override != NULL )
                .if ( [rdi].override == NULL )
                    mov [rdi].override,[rsi].override
                .endif
                mov [rdi].kind,EXPR_ADDR
            .endif
            TokenAssign( rsi, rdi )
            .endc
        .endif

        MakeConst(rsi)
        MakeConst(rdi)

        .if ( ( [rsi].kind == EXPR_CONST && [rdi].kind == EXPR_CONST ) ||
              ( [rsi].kind == EXPR_FLOAT && [rdi].kind == EXPR_FLOAT ) ||
              ( [rsi].kind == EXPR_FLOAT && [rdi].kind == EXPR_CONST ) )

            ; const XX const
            ; float XX const -- shr/shl/...
            ; float XX float

        .elseif ( [rbx].precedence == 10 && [rsi].kind != EXPR_CONST )

            .if ( [rsi].kind == EXPR_ADDR && !( [rsi].flags & E_INDIRECT ) && [rsi].sym )

                .if ( [rdi].kind == EXPR_ADDR && !( [rdi].flags & E_INDIRECT ) && [rdi].sym )
                    .return .ifd MakeConst2(rsi, rdi) == ERROR
                .else
                    .return( fnasmerr( 2094 ) )
                .endif
            .else
                .return( fnasmerr( 2095 ) )
            .endif
        .else
            .return( ConstError( rsi, rdi ) )
        .endif

        mov eax,[rbx].tokval
        .switch rax

        .case T_EQ
            .if ( [rsi].flags & E_IS_TYPE && [rdi].flags & E_IS_TYPE )

                cmp_types( rsi, rdi, -1 )

            .else

                xor eax,eax
                xor edx,edx
                .if ( [rsi].kind == EXPR_FLOAT )

                    mov [rsi].kind,EXPR_CONST
                    mov [rsi].mem_type,MT_EMPTY
ifdef _WIN64
                    add rdx,[rsi].hlvalue
                    sub rdx,[rdi].hlvalue
                    mov [rsi].hlvalue,rax
                .endif

                add rdx,[rsi].llvalue
                sub rdx,[rdi].llvalue
                .ifz
                    dec rax
                .endif
                mov [rsi].llvalue,rax
else
                    add edx,[esi].h64_l
                    sub edx,[edi].h64_l
                    add edx,[esi].h64_h
                    sub edx,[edi].h64_h
                    mov [esi].h64_l,eax
                    mov [esi].h64_h,eax
                .endif
                add edx,[esi].l64_l
                sub edx,[edi].l64_l
                add edx,[esi].l64_h
                sub edx,[edi].l64_h
                .ifz
                    dec eax
                .endif
                mov [esi].l64_l,eax
                mov [esi].l64_h,eax
endif
            .endif
            .endc

        .case T_NE
            .if ( [rsi].flags & E_IS_TYPE && [rdi].flags & E_IS_TYPE )

                cmp_types(rsi, rdi, 0)

            .else

                xor eax,eax
                xor edx,edx
                .if ( [rsi].kind == EXPR_FLOAT )
ifdef _WIN64
                    add rdx,[rsi].hlvalue
                    sub rdx,[rdi].hlvalue
                    mov [rsi].hlvalue,rax
                    mov [rsi].kind,EXPR_CONST
                    mov [rsi].mem_type,MT_EMPTY
                .endif
                add rdx,[rsi].llvalue
                sub rdx,[rdi].llvalue
                .ifnz
                    dec rax
                .endif
                mov [rsi].llvalue,rax
else
                    add edx,[esi].h64_l
                    sub edx,[edi].h64_l
                    add edx,[esi].h64_h
                    sub edx,[edi].h64_h
                    mov [esi].h64_l,eax
                    mov [esi].h64_h,eax
                    mov [esi].kind,EXPR_CONST
                    mov [esi].mem_type,MT_EMPTY
                .endif
                add edx,[esi].l64_l
                sub edx,[edi].l64_l
                add edx,[esi].l64_h
                sub edx,[edi].l64_h
                .ifnz
                    dec eax
                .endif
                mov [esi].l64_l,eax
                mov [esi].l64_h,eax
endif
            .endif
            .endc

        .case T_LT
            .if ( [rsi].kind == EXPR_FLOAT )

                __cmpq( rsi, rdi )

                xor ecx,ecx
                mov [rsi].kind,EXPR_CONST
                mov [rsi].mem_type,MT_EMPTY
                .z8 [rsi].hlvalue,rcx
                .if ( eax == -1 )
                    dec rcx
                .endif

            .else

                xor ecx,ecx
                .if ( [rsi].value64 < [rdi].value64 )
                    dec rcx
                .endif
            .endif
            .z8 [rsi].llvalue,rcx
            .endc

        .case T_LE
            .if ( [rsi].kind == EXPR_FLOAT )

                __cmpq( rsi, rdi )
                xor ecx,ecx
                .z8 [rsi].hlvalue,rcx
                mov [rsi].kind,EXPR_CONST
                mov [rsi].mem_type,MT_EMPTY
                .if ( eax != 1 )
                    dec rcx
                .endif
            .else
                xor ecx,ecx
                .if ( [rsi].value64 <= [rdi].value64 )
                    dec rcx
                .endif
            .endif
            .z8 [rsi].llvalue,rcx
            .endc

        .case T_GT
            .if [rsi].kind == EXPR_FLOAT

                __cmpq(rsi, rdi)
                xor ecx,ecx
                .z8 [rsi].hlvalue,rcx
                mov [rsi].kind,EXPR_CONST
                mov [rsi].mem_type,MT_EMPTY
                .if ( eax == 1 )
                    dec rcx
                .endif
            .else
                xor ecx,ecx
                .if ( [rsi].value64 > [rdi].value64 )
                    dec rcx
                .endif
            .endif
            .z8 [rsi].llvalue,rcx
            .endc

        .case T_GE
            .if ( [rsi].kind == EXPR_FLOAT )

                __cmpq(rsi, rdi)
                xor ecx,ecx
                .z8 [rsi].hlvalue,rcx
                mov [rsi].kind,EXPR_CONST
                mov [rsi].mem_type,MT_EMPTY
                .if ( eax != -1 )
                    dec rcx
                .endif
            .else
                xor ecx,ecx
                .if ( [rsi].value64 >= [rdi].value64 )
                    dec rcx
                .endif
            .endif
            .z8 [rsi].llvalue,rcx
            .endc

        .case T_MOD
            .if ( [rdi].l64_l == 0 && [rdi].l64_h == 0 )
                .return( fnasmerr( 2169 ) )
            .endif
            .if ( [rsi].kind == EXPR_FLOAT )

                __divo( rsi, rdi, &opnd )
                mov [rsi].llvalue,opnd.llvalue
                mov [rsi].hlvalue,opnd.hlvalue
               .endc
            .endif
            __rem64( [rsi].llvalue, [rdi].llvalue )
            .s8 [rsi].llvalue
            .endc

        .case T_SAL
        .case T_SHL
            .if ( [rdi].value < 0 )

                fnasmerr( 2092 )
               .endc
            .endif
            mov eax,64
            .if ( [rsi].kind == EXPR_FLOAT )
                mov eax,128
            .elseif ( ModuleInfo.Ofssize == USE32 )
                mov eax,32
            .endif
            __shlo( rsi, [rdi].value, eax )
            .if ( ModuleInfo.m510 )
                xor eax,eax
                mov [rsi].hvalue,eax
                .z8 [rsi].hlvalue,rax
            .endif
            .endc

        .case T_SHR
            .if ( [rdi].value < 0 )

                fnasmerr( 2092 )
               .endc
            .endif
            mov eax,64
            .if ( [rsi].kind == EXPR_FLOAT )
                mov eax,128
            .elseif ( ModuleInfo.Ofssize == USE32 )
                mov eax,32
            .endif
            __shro( rsi, [rdi].value, eax )
            .endc

        .case T_SAR
            .if ( [rdi].value < 0 )

                fnasmerr( 2092 )
               .endc
            .endif
            mov eax,64
            .if ( [rsi].kind == EXPR_FLOAT )
                mov eax,128
            .elseif ( ModuleInfo.Ofssize == USE32 )
                mov eax,32
            .endif
            __saro( rsi, [rdi].value, eax )
            .endc

        .case T_ADD
            .if ( [rsi].kind != EXPR_FLOAT )
                fnasmerr( 2187 )
            .endif
            add [rsi].llvalue,[rdi].llvalue
            adc [rsi].hlvalue,[rdi].hlvalue
           .endc

        .case T_SUB
            .if ( [rsi].kind != EXPR_FLOAT )
                fnasmerr( 2187 )
            .endif
            sub [rsi].hlvalue,[rdi].hlvalue
            sbb [rsi].llvalue,[rdi].llvalue
           .endc

        .case T_MUL
            .if ( [rsi].kind != EXPR_FLOAT )
                fnasmerr( 2187 )
            .endif
            __mulo( rsi, rdi, NULL )
            .endc

        .case T_DIV
            .if ( [rsi].kind != EXPR_FLOAT )
                fnasmerr( 2187 )
            .endif
            __divo( rsi, rdi, &opnd )
            .endc

        .case T_AND
            .if ( [rsi].kind == EXPR_FLOAT )
                and [rsi].hlvalue,[rdi].hlvalue
            .endif
            and [rsi].llvalue,[rdi].llvalue
           .endc

        .case T_OR
            .if ( [rsi].kind == EXPR_FLOAT )
                or [rsi].hlvalue,[rdi].hlvalue
            .endif
            or [rsi].llvalue,[rdi].llvalue
           .endc

        .case T_XOR
            .if ( [rsi].kind == EXPR_FLOAT )
                xor [rsi].hlvalue,[rdi].hlvalue
            .endif
            xor [rsi].llvalue,[rdi].llvalue
           .endc
        .endsw
        .endc

    .case T_UNARY_OPERATOR
        .if ( [rbx].tokval == T_NOT )
            MakeConst( rdi )
            .if ( [rdi].kind != EXPR_CONST && [rdi].kind != EXPR_FLOAT )
                .return fnasmerr( 2026 )
            .endif
            TokenAssign( rsi, rdi )
ifdef _WIN64
            not [rsi].llvalue
            .if ( [rsi].kind == EXPR_FLOAT )
                not [rsi].hlvalue
else
            not [esi].l64_l
            not [esi].l64_h
            .if ( [esi].kind == EXPR_FLOAT )
                not [esi].h64_l
                not [esi].h64_h
endif
            .endif
            .endc
        .endif

        imul eax,[rbx].tokval,special_item
        lea rcx,SpecialTable
        mov ecx,[rcx+rax].special_item.value
        mov rax,[rdi].sym

        .if ( [rdi].mbr != NULL )
            mov rax,[rdi].mbr
        .endif

        mov sym,rax
        mov esi,ecx
        .if ( [rdi].inst != EMPTY )

            tstrlen( [rbx].string_ptr )
            inc eax
            add rax,[rbx].tokpos

        .elseif ( rax )

            mov rax,[rax].asym.name

        .elseif ( [rdi].base_reg != NULL && !( [rdi].flags & E_INDIRECT ) )

            mov rax,[rdi].base_reg
            mov rax,[rax].asm_tok.string_ptr

        .else

            tstrlen( [rbx].string_ptr )
            inc eax
            add rax,[rbx].tokpos
        .endif

        mov rdx,rax
        mov ecx,esi
        mov rsi,opnd1

        .switch [rdi].kind

        .case EXPR_CONST
            mov rax,[rdi].mbr
            .if ( rax && [rax].asym.state != SYM_TYPE )

                .if ( [rax].asym.mem_type == MT_BITS )
                    .if !( ecx & AT_BF )
                        .return( invalid_operand( rdi, [rbx].string_ptr, rdx ) )
                    .endif
                .else
                    .if !( ecx & AT_FIELD )
                        .return( invalid_operand( rdi, [rbx].string_ptr, rdx ) )
                    .endif
                .endif

            .elseif ( [rdi].flags & E_IS_TYPE )

                .if !( ecx & AT_TYPE )
                    .return invalid_operand( rdi, [rbx].string_ptr, rdx )
                .endif

            .elseif !( ecx & AT_NUM )

                .if ( [rdi].flags & E_IS_OPEATTR )
                    .return ERROR
                .endif
                .if ( ecx == 2 )
                    .return fnasmerr( 2094 )
                .endif
                .return fnasmerr( 2009 )
            .endif
            .endc

        .case EXPR_ADDR
            .if ( [rdi].flags & E_INDIRECT && [rdi].sym == NULL )
                .if !( ecx & AT_IND )
                    .return invalid_operand( rdi, [rbx].string_ptr, rdx )
                .endif
            .else
                .if !( ecx & AT_LABEL )
                    .return ERROR .if ( [rdi].flags & E_IS_OPEATTR )
                    .if ( [rbx].tokval == T_HIGHWORD && [rdi].flags != 4 )
                        .return fnasmerr( 2105 )
                    .endif
                    .if [rdi].flags == 4
                        .return fnasmerr( 2026 )
                    .else
                        .return fnasmerr( 2009 )
                    .endif
                .endif
            .endif
            .endc

        .case EXPR_REG
            .if !( ecx & AT_REG )
                .if !( [rdi].flags & E_IS_OPEATTR )
                    .if ecx == 2
                        .return fnasmerr( 2094 )
                    .endif
                    .if ecx == 0x33
                        .if [rdi].flags & E_INDIRECT
                           .return fnasmerr( 2098 )
                        .else
                           .return fnasmerr( 2032 )
                        .endif
                    .endif
                    .if ecx & 0x20
                        .return fnasmerr( 2105 )
                    .endif
                    .if [rdi].flags & E_INDIRECT
                        .return fnasmerr( 2081 )
                    .else
                        .return fnasmerr( 2009 )
                    .endif
                .else
                    .return ERROR
                .endif
            .endif
            .endc
        .case EXPR_FLOAT
            .if !( ecx & AT_FLOAT )
                .return fnasmerr( 2050 )
            .endif
            .endc
        .endsw

        imul eax,[rbx].tokval,special_item
        lea  rcx,SpecialTable
        mov  ecx,[rcx+rax].special_item.sflags
       .return( unaryop( ecx, rsi, rdi, sym, [rbx].tokval, rdx ) )
    .default
        .return fnasmerr( 2008, [rbx].string_ptr )
    .endsw
    .return( NOT_ERROR )

calculate endp

    assume rcx:expr_t
    assume rdx:expr_t

PrepareOp proc fastcall opnd:expr_t, old:expr_t, oper:token_t

    UNREFERENCED_PARAMETER(opnd)
    UNREFERENCED_PARAMETER(old)

    and [rcx].flags,not E_IS_OPEATTR
    .if [rdx].flags & E_IS_OPEATTR
        or [rcx].flags,E_IS_OPEATTR
    .endif
    mov rax,oper
    .switch [rax].asm_tok.token
    .case T_DOT
        mov rax,[rdx].sym
        .if ( [rdx].type )
            mov [rcx].type,[rdx].type
            or  [rcx].flags,E_IS_DOT
        .elseif ( !ModuleInfo.oldstructs && rax && [rax].asym.state == SYM_UNDEFINED )
            mov [rcx].type,NULL
            or  [rcx].flags,E_IS_DOT
ifdef USE_INDIRECTION
        .elseif ( rax && [rax].asym.mem_type == MT_PTR && [rax].asym.is_ptr )
            mov [rcx].type,[rax].asym.target_type
            or  [rcx].flags,E_IS_DOT
endif
        .endif
        .endc
    .case T_UNARY_OPERATOR
        .switch [rax].asm_tok.tokval
        .case T_OPATTR
        .case T_DOT_TYPE
            or [rcx].flags,E_IS_OPEATTR
           .endc
        .endsw
        .endc
    .endsw
    ret

PrepareOp endp


    assume rcx:nothing
    assume rdx:nothing

OperErr proc fastcall i:int_t, tokenarray:token_t

    UNREFERENCED_PARAMETER(i)
    UNREFERENCED_PARAMETER(tokenarray)

    imul eax,ecx,asm_tok
    .if ( [rdx+rax].asm_tok.token <= T_BAD_NUM )
        fnasmerr( 2206 )
    .else
        fnasmerr( 2008, [rdx+rax].asm_tok.string_ptr )
    .endif
    ret

OperErr endp


    assume rsi:token_t

evaluate proc __ccall uses rsi rdi rbx opnd1:expr_t, i:ptr int_t,
        tokenarray:token_t, _end:int_t, flags:byte

   .new rc          : int_t = NOT_ERROR
   .new opnd2       : expr
   .new exp_token   : int_t
   .new last        : ptr asm_tok

    mov  rdi,opnd1
    mov  rdx,i
    imul ebx,[rdx],asm_tok
    add  rbx,tokenarray
    imul eax,_end,asm_tok
    add  rax,tokenarray
    mov  last,rax

    mov al,[rbx].token
    .if ( [rdi].kind == EXPR_EMPTY &&
          al != T_OP_BRACKET &&
          al != T_OP_SQ_BRACKET &&
          al != '+' &&
          al != '-' &&
          al != T_UNARY_OPERATOR
        )
        mov rc,get_operand( rdi, rdx, tokenarray, flags )
        mov rax,i
        imul ebx,[rax],asm_tok
        add rbx,tokenarray
    .endif

    .while ( rc == NOT_ERROR && rbx < last &&
             [rbx].token != T_CL_BRACKET && [rbx].token != T_CL_SQ_BRACKET )

        mov rsi,rbx

        .if ( [rdi].kind != EXPR_EMPTY )

            mov dl,[rsi].token
            .if ( dl == '+' || dl == '-' )

                mov [rsi].specval,1

            .elseif ( !( dl >= T_OP_BRACKET ||
                         dl == T_UNARY_OPERATOR ||
                         dl == T_BINARY_OPERATOR ) ||
                         dl == T_UNARY_OPERATOR )

                ; v2.26 - added for {k1}{z}..

                .if ( dl == T_STRING && [rsi].string_delim == '{' )

                    SetEvexOpt( rsi )
                    mov rdx,i
                    inc dword ptr [rdx]
                    add rbx,asm_tok
                   .continue

                .else

                    mov rc,ERROR
                    .if !( [rdi].flags & E_IS_OPEATTR )

                        sub rsi,tokenarray
                        mov ecx,asm_tok
                        xor edx,edx
                        mov eax,esi
                        div ecx
                        OperErr( eax, tokenarray )
                    .endif
                    .break
                .endif
            .endif
        .endif

        mov rdx,i
        inc dword ptr [rdx]
        add rbx,asm_tok
        init_expr( &opnd2 )
        PrepareOp( &opnd2, rdi, rsi )

        .if ( [rsi].token == T_OP_BRACKET || [rsi].token == T_OP_SQ_BRACKET )

            xor ecx,ecx
            mov exp_token,T_CL_BRACKET
            .if ( [rsi].token == T_OP_SQ_BRACKET )
                mov exp_token,T_CL_SQ_BRACKET
                mov ecx,EXPF_IN_SQBR
            .elseif ( [rdi].flags & E_IS_DOT )
                mov opnd2.type,[rdi].type
                or  opnd2.flags,E_IS_DOT
            .endif

            or  cl,flags
            and ecx,not EXPF_ONEOPND
            mov rc,evaluate( &opnd2, i, tokenarray, _end, cl )

            mov  rax,i
            imul ebx,[rax],asm_tok
            add  rbx,tokenarray
            mov  eax,exp_token

            .if ( al != [rbx].token )

                .if ( rc != ERROR )
                    fnasmerr( 2157 )
                    mov rax,[rdi].sym
                    .if ( ( [rbx].token == T_COMMA ) && rax && [rax].asym.state == SYM_UNDEFINED )

                        fnasmerr( 2006, [rax].asym.name )
                    .endif
                .endif
                mov rc,ERROR
            .else
                mov rdx,i
                inc dword ptr [rdx]
                add rbx,asm_tok
            .endif

        .elseif ( ( [rbx].token == T_OP_BRACKET || [rbx].token == T_OP_SQ_BRACKET ||
                    [rbx].token == '+' || [rbx].token == '-' || [rbx].token == T_UNARY_OPERATOR ) )
            movzx ecx,flags
            or ecx,EXPF_ONEOPND
            mov rc,evaluate( &opnd2, i, tokenarray, _end, cl )
        .else
            mov rc,get_operand( &opnd2, i, tokenarray, flags )
        .endif

        mov   rcx,i
        imul  ebx,[rcx],asm_tok
        add   rbx,tokenarray
        movzx eax,[rbx].token

        .while ( rc != ERROR && rbx < last && eax != T_CL_BRACKET && eax != T_CL_SQ_BRACKET )

            .if ( eax == '+' || eax == '-' )

                mov [rbx].specval,1

            .elseif ( !( eax >= T_OP_BRACKET || eax == T_UNARY_OPERATOR ||
                        eax == T_BINARY_OPERATOR ) || eax == T_UNARY_OPERATOR )

                ; v2.26 - added for {k1}{z}..

                .if ( eax == T_STRING && [rbx].string_delim == '{' )

                    SetEvexOpt(rbx)
                    mov rdx,i
                    inc dword ptr [rdx]
                    add rbx,asm_tok

                .else

                    mov rc,ERROR
                    .if !( [rdi].flags & E_IS_OPEATTR )
                        mov rcx,i
                        OperErr( [rcx], tokenarray )
                    .endif
                .endif
                .break
            .endif

           .new precedence:int_t = get_precedence( rbx )
            get_precedence( rsi )
            .break .if ( precedence >= eax )

            mov   cl,flags
            or    cl,EXPF_ONEOPND
            mov   rc,evaluate( &opnd2, i, tokenarray, _end, cl )
            mov   rax,i
            imul  ebx,[rax],asm_tok
            add   rbx,tokenarray
            movzx eax,[rbx].token
        .endw

        .if ( rc == ERROR && opnd2.flags & E_IS_OPEATTR )

            .while ( rbx < last && [rbx].token != T_CL_BRACKET &&
                    [rbx].token != T_CL_SQ_BRACKET )

                mov rcx,i
                inc dword ptr [rcx]
                add rbx,asm_tok
            .endw
            mov opnd2.kind,EXPR_EMPTY
            mov rc,NOT_ERROR
        .endif
        .if ( rc != ERROR )
            mov rc,calculate( rdi, &opnd2, rsi )
        .endif
        .break .if ( flags & EXPF_ONEOPND )
    .endw
    .return( rc )

evaluate endp


    option proc:public

EvalOperand proc __ccall uses rsi rbx start_tok:ptr int_t, tokenarray:token_t, end_tok:int_t,
        result:expr_t, flags:byte

    mov  rcx,start_tok
    mov  ebx,[rcx]
    mov  esi,ebx
    imul ebx,ebx,asm_tok
    add  rbx,tokenarray

    init_expr(result)
    .for ( : esi < end_tok : esi++, rbx += asm_tok )
        ;
        ; Check if a token is a valid part of an expression.
        ; chars + - * / . : [] and () are operators.
        ; also done here:
        ; T_INSTRUCTION  SHL, SHR, AND, OR, XOR changed to T_BINARY_OPERATOR
        ; T_INSTRUCTION  NOT                    changed to T_UNARY_OPERATOR
        ; T_DIRECTIVE    PROC                   changed to T_STYPE
        ; for the new operators the precedence is set.
        ; DUP, comma or other instructions or directives terminate the expression.
        ;
        movzx eax,[rbx].token
        .switch eax
        .case T_INSTRUCTION
            mov eax,[rbx].tokval
            .switch eax
            .case T_MUL
            .case T_DIV
                mov [rbx].token,T_BINARY_OPERATOR
                mov [rbx].precedence,8
                .continue
            .case T_SUB
            .case T_ADD
                mov [rbx].token,T_BINARY_OPERATOR
                mov [rbx].precedence,7
                .continue
            .case T_SAL
            .case T_SAR
            .case T_SHL
            .case T_SHR
                mov [rbx].token,T_BINARY_OPERATOR
                mov [rbx].precedence,8
                .continue
            .case T_NOT
                mov [rbx].token,T_UNARY_OPERATOR
                mov [rbx].precedence,11
                .continue
            .case T_AND
                mov [rbx].token,T_BINARY_OPERATOR
                mov [rbx].precedence,12
                .continue
            .case T_OR
            .case T_XOR
                mov [rbx].token,T_BINARY_OPERATOR
                mov [rbx].precedence,13
                .continue
            .endsw
            .break
        .case T_RES_ID
            .break .if [rbx].tokval == T_DUP ; DUP must terminate the expression
            .continue
        .case T_DIRECTIVE

            ; PROC is converted to a type

            .if ( [rbx].tokval == T_PROC )

                mov [rbx].token,T_STYPE

                ; v2.06: avoid to use ST_PROC
                ; item->bytval = ST_PROC;

                mov  dl,ModuleInfo._model
                mov  eax,1
                xchg ecx,edx
                shl  eax,cl
                mov  ecx,edx
                and  eax,SIZE_CODEPTR
                mov  eax,T_NEAR
                .ifnz
                    mov eax,T_FAR
                .endif
                mov [rbx].tokval,eax
               .continue
            .endif

            ; fall through. Other directives will end the expression

        .case T_COMMA
            .break
        .endsw
    .endf

    mov rdx,start_tok
    .return NOT_ERROR .if ( esi == [rdx] )

    lea rax,asmerr
    .if ( flags & EXPF_NOERRMSG )
        lea rax,noasmerr
    .endif
    mov fnasmerr,rax
    evaluate( result, rdx, tokenarray, esi, flags )
    ret

EvalOperand endp


EmitConstError proc __ccall opnd:expr_t

    UNREFERENCED_PARAMETER(opnd)

    asmerr( 2084 )
    ret

EmitConstError endp


ExprEvalInit proc __ccall

    xor eax,eax
    mov thissym,rax
    mov nullstruct,rax
    mov nullmbr,rax
    ret

ExprEvalInit endp

    end
