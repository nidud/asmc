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
CCALLBACK(unaryop_t, :expr_t, :expr_t, :asym_t, :int_t, :string_t)


low_op          proto __ccall :expr_t, :expr_t, :asym_t, :int_t, :string_t
lowword_op      proto __ccall :expr_t, :expr_t, :asym_t, :int_t, :string_t
low32_op        proto __ccall :expr_t, :expr_t, :asym_t, :int_t, :string_t
low64_op        proto __ccall :expr_t, :expr_t, :asym_t, :int_t, :string_t
high_op         proto __ccall :expr_t, :expr_t, :asym_t, :int_t, :string_t
highword_op     proto __ccall :expr_t, :expr_t, :asym_t, :int_t, :string_t
high32_op       proto __ccall :expr_t, :expr_t, :asym_t, :int_t, :string_t
high64_op       proto __ccall :expr_t, :expr_t, :asym_t, :int_t, :string_t
offset_op       proto __ccall :expr_t, :expr_t, :asym_t, :int_t, :string_t
seg_op          proto __ccall :expr_t, :expr_t, :asym_t, :int_t, :string_t
opattr_op       proto __ccall :expr_t, :expr_t, :asym_t, :int_t, :string_t
sizlen_op       proto __ccall :expr_t, :expr_t, :asym_t, :int_t, :string_t
short_op        proto __ccall :expr_t, :expr_t, :asym_t, :int_t, :string_t
this_op         proto __ccall :expr_t, :expr_t, :asym_t, :int_t, :string_t
type_op         proto __ccall :expr_t, :expr_t, :asym_t, :int_t, :string_t
wimask_op       proto __ccall :expr_t, :expr_t, :asym_t, :int_t, :string_t


FindDotSymbol   proto __ccall :ptr asm_tok

res macro token, function
    unaryop_t function
    endm

    .data

     thissym    asym_t 0
     nullstruct asym_t 0
     nullmbr    asym_t 0
     fnasmerr   lpfnasmerr 0
     unaryop    label unaryop_t
     include unaryop.inc
     undef res

    .code

    option proc:private

    assume rcx:expr_t
    assume rdx:expr_t
    assume rsi:expr_t
    assume rdi:expr_t

noasmerr proc __ccall msg:int_t, args:vararg

    UNREFERENCED_PARAMETER(msg)

    .return( ERROR )

noasmerr endp

ConstError proc __ccall opnd1:expr_t, opnd2:expr_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    .return( NOT_ERROR ) .if ( [rcx].flags & E_IS_OPEATTR )
    .if [rcx].kind == EXPR_FLOAT || [rdx].kind == EXPR_FLOAT
        fnasmerr(2050)
    .else
        fnasmerr(2026)
    .endif
    ret

ConstError endp

TokenAssign proc __ccall uses rsi rdi opnd1:expr_t, opnd2:expr_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    ; note that offsetof() is used. This means, don't change position
    ; of field <type> in expr!

    mov rsi,rdx
    mov rdi,rcx
    mov rax,rcx
    mov ecx,offsetof( expr, type ) / 8
    rep movsq
    mov rcx,rax
    ret

TokenAssign endp

tofloat proc __ccall uses rcx rdx opnd1:expr_t, opnd2:expr_t, size:int_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)
    UNREFERENCED_PARAMETER(size)

    .if ModuleInfo.strict_masm_compat
        ConstError(rcx, rdx)
        mov r8,rax
       .return 1
    .endif
    mov [rdx].kind,EXPR_CONST
    mov [rdx].float_tok,NULL
    .if r8d != 16
        mov rcx,rdx
        quad_resize(rcx, r8d)
    .endif
   .return NOT_ERROR

tofloat endp

invalid_operand proc __ccall opnd:expr_t, oprtr:string_t, operand:string_t

    UNREFERENCED_PARAMETER(opnd)
    UNREFERENCED_PARAMETER(oprtr)
    UNREFERENCED_PARAMETER(operand)

    .if !( [rcx].flags & E_IS_OPEATTR )
        fnasmerr(3018, tstrupr(rdx), r8)
    .endif
    .return ERROR

invalid_operand endp

    assume rcx:dsym_t

GetSizeValue proc __ccall sym:asym_t

    UNREFERENCED_PARAMETER(sym)

    movzx eax,[rcx].mem_type
    .if eax == MT_PTR
        mov eax,MT_NEAR
        .if [rcx].is_far
            mov eax,MT_FAR
        .endif
    .endif
    SizeFromMemtype(al, [rcx].Ofssize, [rcx].type)
    ret

GetSizeValue endp

GetRecordMask proc __ccall uses rsi rdi rbx rec:dsym_t

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

IsOffset proc __ccall opnd:expr_t

    UNREFERENCED_PARAMETER(opnd)

    .if ( [rcx].mem_type == MT_EMPTY )
        mov eax,[rcx].inst
        .if ( eax == T_OFFSET ||
              eax == T_IMAGEREL ||
              eax == T_SECTIONREL ||
              eax == T_LROFFSET )
            .return true
        .endif
    .endif
    .return false

IsOffset endp

;--------------------------------------------------------------------------------
; unaryop.inc
;--------------------------------------------------------------------------------

UNARY_PARAMETER macro
    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)
    UNREFERENCED_PARAMETER(sym)
    UNREFERENCED_PARAMETER(oper)
    UNREFERENCED_PARAMETER(name)
    endm

low_op proc __ccall opnd1:expr_t, opnd2:expr_t, sym:asym_t, oper:int_t, name:string_t

    UNARY_PARAMETER

    TokenAssign(rcx, rdx)

    .if [rdx].kind == EXPR_ADDR && [rdx].inst != T_SEG
        mov [rcx].inst,T_DOT_LOW
        mov [rcx].mem_type,MT_EMPTY
    .endif
    mov eax,[rcx].value
    and eax,0xff
    mov [rcx].llvalue,rax
   .return NOT_ERROR

low_op endp

lowword_op proc __ccall opnd1:expr_t, opnd2:expr_t, sym:asym_t, oper:int_t, name:string_t

    UNARY_PARAMETER

    TokenAssign(rcx, rdx)

    .if [rdx].kind == EXPR_ADDR && [rdx].inst != T_SEG
        mov [rcx].inst,T_LOWWORD
        mov [rcx].mem_type,MT_EMPTY
    .endif
    mov eax,[rcx].value
    and eax,0xffff
    mov [rcx].llvalue,rax
   .return NOT_ERROR

lowword_op endp

low32_op proc __ccall opnd1:expr_t, opnd2:expr_t, sym:asym_t, oper:int_t, name:string_t

    UNARY_PARAMETER

    .if [rdx].kind == EXPR_FLOAT
        .return r8d .if tofloat(rcx, rdx, 8)
    .endif

    TokenAssign(rcx, rdx)

    mov [rcx].mem_type,MT_DWORD
    .if [rdx].kind == EXPR_ADDR && [rdx].inst != T_SEG
        mov [rcx].inst,T_LOW32
        mov [rcx].mem_type,MT_EMPTY
    .endif
    xor eax,eax
    mov [rcx].hvalue,eax
    ret

low32_op endp

low64_op proc __ccall opnd1:expr_t, opnd2:expr_t, sym:asym_t, oper:int_t, name:string_t

    UNARY_PARAMETER

    .if [rdx].kind == EXPR_FLOAT
        .return r8d .if tofloat(rcx, rdx, 16)
    .endif

    TokenAssign(rcx, rdx)

    mov [rcx].mem_type,MT_QWORD
    .if [rdx].kind == EXPR_ADDR && [rdx].inst != T_SEG
        mov [rcx].inst,T_LOW64
        mov [rcx].mem_type,MT_EMPTY
    .endif
    xor eax,eax
    mov [rcx].hlvalue,rax
    ret

low64_op endp

high_op proc __ccall opnd1:expr_t, opnd2:expr_t, sym:asym_t, oper:int_t, name:string_t

    UNARY_PARAMETER

    TokenAssign(rcx, rdx)
    .if [rdx].kind == EXPR_ADDR && [rdx].inst != T_SEG
        mov [rcx].inst,T_DOT_HIGH
        mov [rcx].mem_type,MT_EMPTY
    .endif
    mov eax,[rcx].value
    shr eax,8
    and eax,0xff
    mov [rcx].llvalue,rax
   .return NOT_ERROR

high_op endp

highword_op proc __ccall opnd1:expr_t, opnd2:expr_t, sym:asym_t, oper:int_t, name:string_t

    UNARY_PARAMETER

    TokenAssign(rcx, rdx)

    .if [rdx].kind == EXPR_ADDR && [rdx].inst != T_SEG
        mov [rcx].inst,T_HIGHWORD
        mov [rcx].mem_type,MT_EMPTY
    .endif
    mov eax,[rcx].value
    shr eax,16
    and eax,0xffff
    mov [rcx].llvalue,rax
   .return NOT_ERROR

highword_op endp

high32_op proc fastcall opnd1:expr_t, opnd2:expr_t, sym:asym_t, oper:int_t, name:string_t

    UNARY_PARAMETER

    .if [rdx].kind == EXPR_FLOAT
        .return r8d .if tofloat(rcx, rdx, 8)
    .endif

    TokenAssign(rcx, rdx)

    mov [rcx].mem_type,MT_DWORD
    .if [rdx].kind == EXPR_ADDR && [rdx].inst != T_SEG
        mov [rcx].inst,T_HIGH32
        mov [rcx].mem_type,MT_EMPTY
    .endif
    mov eax,[rcx].hvalue
    mov [rcx].llvalue,rax
   .return NOT_ERROR

high32_op endp

high64_op proc fastcall opnd1:expr_t, opnd2:expr_t, sym:asym_t, oper:int_t, name:string_t

    UNARY_PARAMETER

    xor eax,eax
    .if [rdx].kind == EXPR_FLOAT
        .return r8d .if tofloat(rcx, rdx, 16)
    .elseif [rdx].flags & E_NEGATIVE && [rdx].hlvalue == rax
        dec rax
        mov [rdx].hlvalue,rax
    .endif

    TokenAssign(rcx, rdx)

    mov [rcx].mem_type,MT_QWORD
    .if [rdx].kind == EXPR_ADDR && [rdx].inst != T_SEG
        mov [rcx].inst,T_HIGH64
        mov [rcx].mem_type,MT_EMPTY
    .endif
    mov rax,[rcx].hlvalue
    mov [rcx].llvalue,rax
    xor eax,eax
    mov [rcx].hlvalue,rax
    ret

high64_op endp

offset_op proc __ccall opnd1:expr_t, opnd2:expr_t, sym:asym_t, oper:int_t, name:string_t

    UNARY_PARAMETER

    .if r9d == T_OFFSET
        .if [rdx].kind == EXPR_CONST
            TokenAssign(rcx, rdx)
            .return NOT_ERROR
        .endif
    .endif
    .if ( ( r8 && [r8].asym.state == SYM_GRP ) || [rdx].inst == T_SEG )
        .return invalid_operand(opnd2, GetResWName(r9d, NULL), name)
    .endif
    .if ( [rdx].flags & E_IS_TYPE )
        mov [rdx].value,0
    .endif
    TokenAssign(rcx, rdx)
    mov [rcx].inst,r9d
    .if [rdx].flags & E_INDIRECT
        .return invalid_operand(opnd2, GetResWName(r9d, NULL), name)
    .endif
    mov [rcx].mem_type,MT_EMPTY
   .return NOT_ERROR

offset_op endp

seg_op proc __ccall opnd1:expr_t, opnd2:expr_t, sym:asym_t, oper:int_t, name:string_t

    UNARY_PARAMETER

    mov rax,[rdx].sym
    .if rax == NULL || [rax].asym.state == SYM_STACK || [rdx].flags & E_IS_ABS
        .return fnasmerr(2094)
    .endif
    TokenAssign(rcx, rdx)
    mov [rcx].inst,oper
    .if [rcx].mbr
        mov [rcx].value,0
    .endif
    mov [rcx].mem_type,MT_EMPTY
   .return NOT_ERROR

seg_op endp

    assume rbx:asym_t

opattr_op proc __ccall uses rsi rdi rbx opnd1:expr_t, opnd2:expr_t, sym:asym_t, oper:int_t, name:string_t

    UNARY_PARAMETER

    xor eax,eax

    mov [rcx].kind,EXPR_CONST
    mov [rcx].sym,NULL
    mov [rcx].value,0
    mov [rcx].mem_type,MT_EMPTY
    and [rcx].flags,not E_IS_OPEATTR
   .return .if [rdx].kind == EXPR_EMPTY

    mov rsi,rcx
    mov rdi,rdx
    mov rbx,[rdi].sym
    .if [rdi].kind == EXPR_ADDR
        mov al,[rdi].mem_type
        and al,MT_SPECIAL_MASK
        .if rbx && [rbx].state != SYM_STACK && eax == MT_ADDRESS
            or [rsi].value,OPATTR_CODELABEL
        .endif
        IsOffset(rdi)
        .if eax && rbx
            mov al,[rbx].mem_type
            and eax,MT_SPECIAL_MASK
            .if eax == MT_ADDRESS
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
    .if rax == 0
        mov rax,[rdi].base_reg
    .endif
    .if rax
        imul eax,[rax].asm_tok.tokval,special_item
    .endif
    lea r8,SpecialTable
    .if ( ( rbx && [rbx].state == SYM_STACK ) || \
          ( [rdi].flags & E_INDIRECT && eax && ( [r8+rax].special_item.sflags & SFR_SSBASED ) ) )
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
    .return NOT_ERROR

opattr_op endp

    assume rbx:nothing
    assume rax:asym_t

sizlen_op proc __ccall uses rsi opnd1:expr_t, opnd2:expr_t, sym:asym_t, oper:int_t, name:string_t

    UNARY_PARAMETER

    mov rsi,rcx
    mov rax,r8
    mov [rcx].kind,EXPR_CONST
    .if rax
        .if [rax].state == SYM_STRUCT_FIELD || [rax].state == SYM_STACK
        .elseif [rax].state == SYM_UNDEFINED
            mov [rcx].kind,EXPR_ADDR
            mov [rcx].sym,rax
        .elseif ( ( [rax].state == SYM_EXTERNAL || [rax].state == SYM_INTERNAL) &&
                    [rax].mem_type != MT_EMPTY && [rax].mem_type != MT_FAR &&
                    [rax].mem_type != MT_NEAR )
        .elseif [rax].state == SYM_GRP || [rax].state == SYM_SEG
            .return fnasmerr(2143)
        .elseif r9d == T_DOT_SIZE || r9d == T_DOT_LENGTH
        .else
            .return fnasmerr(2143)
        .endif
    .endif
    .switch r9d
    .case T_DOT_LENGTH
        .if [rax].flag1 & S_ISDATA
            mov [rcx].value,[rax].first_length
        .else
            mov [rcx].value,1
        .endif
        .endc
    .case T_LENGTHOF
        .if [rdx].kind == EXPR_CONST
            mov rax,[rdx].mbr
            mov [rcx].value,[rax].total_length
        .elseif [rax].state == SYM_EXTERNAL && !( [rax].sflags & S_ISCOM )
            mov [rcx].value,1
        .else
            mov [rcx].value,[rax].total_length
        .endif
        .endc
    .case T_DOT_SIZE
        .if r8 == NULL
            mov al,[rdx].mem_type
            and eax,MT_SPECIAL_MASK
            .if eax == MT_ADDRESS
                mov eax,[rdx].value
                or  eax,0xFF00
                mov [rcx].value,eax
            .else
                mov [rcx].value,[rdx].value
            .endif
        .elseif [rax].flag1 & S_ISDATA
            mov [rcx].value,[rax].first_size
        .elseif [rax].state == SYM_STACK
            GetSizeValue(rax)
            mov [rsi].value,eax
        .elseif [rax].mem_type == MT_NEAR
            mov ecx,GetSymOfssize(rax)
            mov eax,2
            shl eax,cl
            or  eax,0xFF00
            mov [rsi].value,eax
        .elseif [rax].mem_type == MT_FAR
            .if GetSymOfssize(rax)
                mov eax,LS_FAR32
            .else
                mov eax,LS_FAR16
            .endif
            mov [rsi].value,eax
        .else
            GetSizeValue(rax)
            mov [rsi].value,eax
        .endif
        .endc
    .case T_SIZEOF
        .if rax == NULL
            mov rax,[rdx].type
            .if [rdx].flags & E_IS_TYPE && eax && [rax].typekind == TYPE_RECORD
                mov [rcx].value,[rax].total_size
            .else
                mov [rcx].value,[rdx].value
            .endif
        .elseif [rax].state == SYM_EXTERNAL && !( [rax].sflags & S_ISCOM )
            GetSizeValue(rax)
            mov [rsi].value,eax
        .else
            mov [rcx].value,[rax].total_size
        .endif
        .endc
    .endsw
    .return NOT_ERROR

sizlen_op endp

short_op proc __ccall opnd1:expr_t, opnd2:expr_t, sym:asym_t, oper:int_t, name:string_t

    UNARY_PARAMETER

    .if ( [rdx].kind != EXPR_ADDR || ( [rdx].mem_type != MT_EMPTY &&
          [rdx].mem_type != MT_NEAR && [rdx].mem_type != MT_FAR ) )
        .return fnasmerr(2028)
    .endif

    TokenAssign(rcx, rdx)

    mov [rcx].inst,r9d
   .return NOT_ERROR

short_op endp

this_op proc __ccall uses rsi rdi opnd1:expr_t, opnd2:expr_t, sym:asym_t, oper:int_t, name:string_t

    UNARY_PARAMETER

    .if !( [rdx].flags & E_IS_TYPE )
        .return fnasmerr(2010)
    .endif
    .if CurrStruct
        .return fnasmerr(2034)
    .endif
    .if ModuleInfo.currseg == NULL
        .return asmerr(2034)
    .endif

    mov rsi,rcx
    mov rdi,rdx

    mov rax,thissym
    .if rax == NULL
        mov thissym,SymAlloc("")
        mov [rax].state,SYM_INTERNAL
        or  [rax].flags,S_ISDEFINED
    .endif

    mov [rsi].kind,EXPR_ADDR
    mov [rsi].sym,rax
    mov rcx,[rdi].type
    mov [rax].type,rcx
    .if rcx
        mov [rax].mem_type,MT_TYPE
    .else
        mov cl,[rdi].mem_type
        mov [rax].mem_type,cl
    .endif
    SetSymSegOfs(rax)
    mov rax,thissym
    mov al,[rax].mem_type
    mov [rsi].mem_type,al
   .return( NOT_ERROR )

this_op endp

type_op proc __ccall uses rsi rdi opnd1:expr_t, opnd2:expr_t, sym:asym_t, oper:int_t, name:string_t

    UNARY_PARAMETER

    mov rsi,rcx
    mov rdi,rdx
    mov rax,r8

    mov [rsi].kind,EXPR_CONST
    .if [rdi].inst != EMPTY && [rdi].mem_type != MT_EMPTY

        mov [rdi].inst,EMPTY
        xor eax,eax
    .endif

    .if [rdi].inst != EMPTY
        .if [rdi].sym
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
    .elseif rax == NULL
        mov rax,[rdi].type
        .if ( [rdi].flags & E_IS_TYPE )
            .if rax && [rax].typekind == TYPE_RECORD
                mov [rdi].value,[rax].total_size
            .endif
            TokenAssign(rsi, rdi)
            mov [rsi].type,[rdi].type
        .elseif ( [rdi].kind == EXPR_REG && !( [rdi].flags & E_INDIRECT ) )

            mov rax,[rdi].base_reg
            assume rax:nothing
            SizeFromRegister([rax].asm_tok.tokval)
            mov [rsi].value,eax
            or  [rsi].flags,E_IS_TYPE
            mov rax,[rdi].base_reg
            imul eax,[rax].asm_tok.tokval,special_item
            lea r8,SpecialTable
            .if ( ( [r8+rax].special_item.value & OP_RGT8 ) &&
                  [rsi].mem_type == MT_EMPTY &&
                  byte ptr [rsi].value == ModuleInfo.wordsize )
                mov rax,[rdi].base_reg
                GetStdAssumeEx([rax].asm_tok.bytval)
            .else
                xor eax,eax
            .endif
            assume rax:asym_t
            .if rax
                mov [rsi].type,rax
                mov dl,[rax].mem_type
                mov [rsi].mem_type,dl
                mov [rsi].value,[rax].total_size
            .else
                mov [rsi].mem_type,[rdi].mem_type
                mov [rsi].type,[rdi].type
                .if [rsi].mem_type == MT_EMPTY
                    MemtypeFromSize([rsi].value, &[rsi].mem_type)
                .endif
            .endif
        .elseif [rdi].mem_type != MT_EMPTY || [rdi].flags & E_EXPLICIT
            .if [rdi].mem_type != MT_EMPTY
                ; added v2.31.46
                .if ( [rdi].kind == EXPR_FLOAT && [rdi].mem_type == MT_REAL16 )
                    xor eax,eax
                .else
                    mov [rsi].mem_type,[rdi].mem_type
                    SizeFromMemtype([rdi].mem_type, [rdi].Ofssize, [rdi].type)
                .endif
                mov [rsi].value,eax
            .else
                mov rax,[rdi].type
                .if rax
                    mov ecx,[rax].total_size
                    mov [rsi].value,ecx
                    mov [rsi].mem_type,[rax].mem_type
                .endif
            .endif
            or  [rsi].flags,E_IS_TYPE
            mov [rsi].type,[rdi].type
        .else
            mov [rsi].value,0
        .endif
    .elseif [rax].state == SYM_UNDEFINED
        mov [rsi].kind,EXPR_ADDR
        mov [rsi].sym,rax
        or  [rsi].flags,E_IS_TYPE
    .elseif [rax].mem_type == MT_TYPE && !( [rdi].flags & E_EXPLICIT )
        or  [rsi].flags,E_IS_TYPE
        mov rax,[rax].type
        mov [rsi].type,rax
        mov edx,[rax].total_size
        mov [rsi].value,edx
        mov [rsi].mem_type,[rax].mem_type
    .else
        or  [rsi].flags,E_IS_TYPE
        .if [rsi].mem_type == MT_EMPTY
            mov [rsi].mem_type,[rdi].mem_type
        .endif
        mov rax,sym
        .if [rdi].type && [rdi].mbr == NULL
            mov [rsi].type_tok,[rdi].type_tok
            mov [rsi].type,[rdi].type
            mov [rsi].value,[rax].total_size
        .elseif [rax].mem_type == MT_PTR
            mov [rsi].type_tok,[rdi].type_tok
            mov rax,sym
            mov ecx,MT_NEAR
            .if [rax].is_far
                mov ecx,MT_FAR
            .endif
            SizeFromMemtype(cl, [rax].Ofssize, NULL)
            mov [rsi].value,eax
        .elseif [rax].mem_type == MT_NEAR
            mov ecx,GetSymOfssize(rax)
            mov eax,2
            shl eax,cl
            or  eax,0xFF00
            mov [rsi].value,eax
        .elseif [rax].mem_type == MT_FAR
            .if GetSymOfssize(rax)
                mov eax,LS_FAR32
            .else
                mov eax,LS_FAR16
            .endif
            mov [rsi].value,eax
        .else
            mov edx,GetSymOfssize(rax)
            mov rax,sym
            SizeFromMemtype([rdi].mem_type, edx, [rax].type)
            mov [rsi].value,eax
        .endif
    .endif
    .return NOT_ERROR

type_op endp

    assume rax:nothing
    assume rsi:nothing

wimask_op proc __ccall uses rsi rdi rbx opnd1:expr_t, opnd2:expr_t, sym:asym_t, oper:int_t, name:string_t

    UNARY_PARAMETER

    .if [rdx].flags & E_IS_TYPE
        mov rax,[rdx].type
        .if [rax].asym.typekind != TYPE_RECORD
            .return fnasmerr(2019)
        .endif
    .elseif [rdx].kind == EXPR_CONST
        mov rax,[rdx].mbr
    .else
        mov rax,[rdx].sym
    .endif
    .if r9d == T_DOT_MASK
        mov [rcx].value,0
        .if [rdx].flags & E_IS_TYPE
            GetRecordMask(rax)
        .else
            mov rbx,rax
            xor eax,eax
            xor edx,edx
            mov ecx,[rbx].asym.offs
            mov edi,[rbx].asym.total_size
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
        .endif
        mov rcx,opnd1
        mov [rcx].value,eax
        mov [rcx].hvalue,edx
    .else
        .if [rdx].flags & E_IS_TYPE
            mov rax,[rax].dsym.structinfo
            mov rsi,[rax].struct_info.head
            .for ( : esi : rsi = [rsi].sfield.next )
                add [rcx].value,[rsi].sfield.total_size
            .endf
        .else
            mov [rcx].value,[rax].asym.total_size
        .endif
    .endif
    mov [rcx].kind,EXPR_CONST
   .return( NOT_ERROR )

wimask_op endp

;--------------------------------------------------------------------------------
;
;--------------------------------------------------------------------------------

init_expr proc __ccall opnd:expr_t

    UNREFERENCED_PARAMETER(opnd)

    xor eax,eax
    mov [rcx].llvalue,rax
    mov [rcx].hlvalue,rax
    mov [rcx].quoted_string,rax
    mov [rcx].base_reg,rax
    mov [rcx].idx_reg,rax
    mov [rcx].label_tok,rax
    mov [rcx].override,rax
    mov [rcx].inst,EMPTY
    mov [rcx].kind,EXPR_EMPTY
    mov [rcx].mem_type,MT_EMPTY
    mov [rcx].scale,al
    mov [rcx].Ofssize,USE_EMPTY
    mov [rcx].flags,al
    mov [rcx].op,rax
    mov [rcx].sym,rax
    mov [rcx].mbr,rax
    mov [rcx].type,rax
    ret

init_expr endp

    assume rcx:token_t

get_precedence proc __ccall item:token_t

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
        .if ModuleInfo.m510
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
        .if [rcx].specval
            mov eax,9
        .endif
        .return
    .endsw
    fnasmerr( 2008, [rcx].string_ptr )
   .return ERROR

get_precedence endp

GetTypeSize proc __ccall mem_type:byte, ofssize:int_t

    UNREFERENCED_PARAMETER(mem_type)
    UNREFERENCED_PARAMETER(ofssize)

    .if cl == MT_ZWORD
        .return 64
    .endif
    .if !( cl & MT_SPECIAL )
        and ecx,MT_SIZE_MASK
        inc ecx
        .return ecx
    .endif
    .if edx == USE_EMPTY
        movzx edx,ModuleInfo.Ofssize
    .endif
    .if cl == MT_NEAR
        mov eax,2
        mov ecx,edx
        shl eax,cl
        or  eax,0xFF00
    .elseif cl == MT_FAR
        mov eax,LS_FAR16
        .if dl != USE16
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

SetEvexOpt proc __ccall tok:token_t

    UNREFERENCED_PARAMETER(tok)

    .if ( [rcx-1*asm_tok].token == T_COMMA &&
          [rcx-2*asm_tok].token == T_REG &&
          [rcx-3*asm_tok].token == T_INSTRUCTION )

        mov eax,GetValueSp([rcx-2*asm_tok].tokval)
        .if eax & OP_XMM
            .if ( [rcx-3*asm_tok].tokval < VEX_START &&
                  [rcx-3*asm_tok].tokval >= T_ADDPD )
                .return false
            .endif
        .endif
    .endif
    or  [rcx].asm_tok.hll_flags,T_EVEX_OPT
   .return true

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

    mov  eax,[rdx]
    mov  i,eax
    mov  rdi,rcx
    mov  rbx,r8
    imul eax,eax,asm_tok
    add  rbx,rax
    mov  al,[rbx].token

    .switch al
    .case '&' ; v2.30.24 -- mov mem,&mem
        .if ( Options.strict_masm_compat == FALSE && i > 2 && \
              [rbx-asm_tok].token == T_COMMA && [rbx-asm_tok*2].token != T_REG )
            inc i
            inc dword ptr [rdx]
            add rbx,asm_tok
            mov al,[rbx].token
            .return NOT_ERROR .if al == T_OP_SQ_BRACKET
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
        lea r8,SpecialTable
        movzx eax,[r8+rax].special_item.cpu
        mov ecx,ModuleInfo.curr_cpu
        mov edx,ecx
        and ecx,P_EXT_MASK
        and edx,P_CPU_MASK
        mov esi,eax
        and esi,P_CPU_MASK

        .if ( ( eax & P_EXT_MASK ) && !( eax & ecx ) || edx < esi )

            .if flags & EXPF_IN_SQBR
                mov [rdi].kind,EXPR_ERROR
                fnasmerr(2085)
            .else
                .return fnasmerr(2085)
            .endif
        .endif

        .if ( ( i > 0 && [rbx-asm_tok].tokval == T_TYPEOF ) ||
              ( i > 1 && [rbx-asm_tok].token == T_OP_BRACKET &&
                [rbx-asm_tok*2].tokval == T_TYPEOF ) )

             ; v2.24 [reg + type reg] | [reg + type(reg)]

        .elseif flags & EXPF_IN_SQBR

            lea r8,SpecialTable
            imul eax,[rbx].tokval,special_item
            add rax,r8
            .if ( [rax].special_item.sflags & SFR_IREG )
                or [rdi].flags,E_INDIRECT or E_ASSUMECHECK
            .elseif ( [rax].special_item.value & OP_SR )
                .if ( [rbx+asm_tok].token != T_COLON ||
                      ( ModuleInfo.strict_masm_compat && [rbx+asm_tok*2].token == T_REG ) )
                    .return fnasmerr(2032)
                .endif
            .else
                .if ( [rdi].flags & E_IS_OPEATTR )
                    mov [rdi].kind,EXPR_ERROR
                .else
                    .return fnasmerr(2031)
                .endif
            .endif
        .endif
        .endc
    .case T_ID
        mov rsi,[rbx].string_ptr
        .if ( [rdi].flags & E_IS_DOT )
            mov rcx,[rdi].type
            xor eax,eax
            mov [rdi].value,eax
            .if rcx
                SearchNameInStruct( rcx, rsi, rdi, 0 )
            .endif
            .if rax == NULL
                .if SymFind(rsi)
                    .if [rax].asym.state == SYM_TYPE
                        mov rcx,[rdi].type
                        .if !( rax == rcx || ( rcx && !( [rcx].asym.flags & S_ISDEFINED ) ) || ModuleInfo.oldstructs )
                            xor eax,eax
                        .endif

                    .elseif !( ModuleInfo.oldstructs && ( [rax].asym.state == SYM_STRUCT_FIELD || \
                              [rax].asym.state == SYM_EXTERNAL || [rax].asym.state == SYM_INTERNAL ) )
                        xor eax,eax
                    .endif
                .endif
            .endif
        .else

            mov edx,[rsi]
            or  dh,0x20
            .if ( dl == '@' && !( edx & 0x00FF0000 ) )
                .if dh == 'b'
                    mov rsi,GetAnonymousLabel( &labelbuff, 0 )
                .elseif dh == 'f'
                    mov rsi,GetAnonymousLabel( &labelbuff, 1 )
                .endif
            .endif
            SymFind(rsi)
        .endif

        .if ( rax == NULL || [rax].asym.state == SYM_UNDEFINED ||
              ( [rax].asym.state == SYM_TYPE && [rax].asym.typekind == TYPE_NONE ) ||
              [rax].asym.state == SYM_MACRO || [rax].asym.state == SYM_TMACRO )

            .if ( [rdi].flags & E_IS_OPEATTR )

                mov [rdi].kind,EXPR_ERROR
               .endc
            .endif
            .if ( rax &&
                 ( [rax].asym.state == SYM_MACRO || [rax].asym.state == SYM_TMACRO ) )
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

                .if ( Options.strict_masm_compat == FALSE && rax == NULL )

                    mov rax,[rsi]
                    mov rdx,0x20202020202020
                    or  rax,rdx
                    mov rdx,'denifed'
                    .if ( rax == rdx )

                        .if ( i && [rbx+asm_tok].token == T_OP_BRACKET )

                            add i,2
                            add rbx,asm_tok*2
                            mov [rdi].kind,EXPR_CONST
                            mov [rdi].llvalue,0

                            ; added v2.28.17: defined(...) returns -1

                            mov rcx,idx
                            mov eax,i

                            .if ( [rbx].token == T_CL_BRACKET )
                                mov [rcx],eax
                                dec [rdi].llvalue ; <> -- defined()
                               .endc
                            .endif

                            .if ( [rbx].token == T_NUM &&
                                  [rbx+asm_tok].token == T_CL_BRACKET )

                                dec [rdi].llvalue ; <> -- defined()
                                inc eax
                                mov [rcx],eax
                               .endc
                            .endif

                            .if ( [rbx].token == T_ID &&
                                  [rbx+asm_tok].token == T_CL_BRACKET )

                                inc eax
                                mov [rcx],eax
                                .if ( SymFind([rbx].string_ptr) )
                                    .if ( [rax].asym.state != SYM_UNDEFINED )

                                        dec [rdi].llvalue ; symbol defined
                                       .endc
                                    .endif
                                .endif

                                ;; -- symbol not defined --

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
                    .endif
                .endif
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
                    mov [rdi].value,GetTypeSize([rax].asym.mem_type, edx)
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
                .if al == MT_REAL16 && !ModuleInfo.strict_masm_compat
                    mov [rdi].kind,EXPR_FLOAT
                    mov [rdi].float_tok,NULL
                    mov dword ptr [rdi].hlvalue,[rsi].total_length
                    mov dword ptr [rdi].hlvalue[4],[rsi].ext_idx
                .endif
            .elseif ( [rsi].state == SYM_EXTERNAL &&
                      [rsi].mem_type == MT_EMPTY &&
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
                    lea r8,SpecialTable
                    mov al,[r8+rax].special_item.bytval
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
        lea r8,SpecialTable
        add rcx,r8
        mov [rdi].mem_type,[rcx].special_item.bytval
        mov eax,[rcx].special_item.sflags
        mov [rdi].Ofssize,al
        mov [rdi].value,GetTypeSize([rdi].mem_type, eax)
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
                  ( [rbx-asm_tok].tokval == T_TYPEOF ||
                    [rbx-asm_tok*2].tokval == T_TYPEOF ) &&
                  ( [rbx+asm_tok].token == T_ID ||
                    [rbx+asm_tok].token == T_OP_SQ_BRACKET ) )

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
    mov eax,NOT_ERROR
    ret

get_operand endp

    assume rcx:expr_t
    assume rdx:expr_t

check_both proc __ccall opnd1:expr_t, opnd2:expr_t, type1:int_t, type2:int_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)
    UNREFERENCED_PARAMETER(type1)
    UNREFERENCED_PARAMETER(type2)

    mov eax,1
   .return .if [rcx].kind == r8d && [rdx].kind == r9d
   .return .if [rcx].kind == r9d && [rdx].kind == r8d
   .return 0

check_both endp

index_connect proc __ccall opnd1:expr_t, opnd2:expr_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    mov rax,[rdx].base_reg
    .if rax != NULL
        .if [rcx].base_reg == NULL
            mov [rcx].base_reg,rax
        .elseif [rcx].idx_reg == NULL
            .if [rax].asm_tok.bytval == 4
                mov [rcx].idx_reg,[rcx].base_reg
                mov [rcx].base_reg,[rdx].base_reg
            .else
                mov [rcx].idx_reg,rax
            .endif
ifdef USE_INDIRECTION
        .elseif ( [rax-asm_tok*1].asm_tok.token == T_OP_SQ_BRACKET && \
                  [rax-asm_tok*2].asm_tok.token == T_ID && \
                  [rax-asm_tok*3].asm_tok.token == T_DOT )
            mov rax,[rcx].sym
            .if ( !( rax && [rax].asym.mem_type == MT_PTR && [rax].asym.is_ptr ) )
                .return fnasmerr(2030)
            .endif
endif
        .else
            .return fnasmerr(2030)
        .endif
        or [rcx].flags,E_INDIRECT
    .endif
    mov rax,[rdx].idx_reg
    .if rax != NULL
        .if [rcx].idx_reg == NULL
            mov [rcx].idx_reg,rax
            mov [rcx].scale,[rdx].scale
ifdef USE_INDIRECTION
        .elseif ( [rax-asm_tok*1].asm_tok.token == T_OP_SQ_BRACKET && \
                  [rax-asm_tok*2].asm_tok.token == T_ID && \
                  [rax-asm_tok*3].asm_tok.token == T_DOT )
            mov rax,[rcx].sym
            .if ( !( rax && [rax].asym.mem_type == MT_PTR && [rax].asym.is_ptr ) )
                .return fnasmerr(2030)
            .endif
endif
        .else
            .return fnasmerr(2030)
        .endif
        or [rcx].flags,E_INDIRECT
    .endif
    .return( NOT_ERROR )

index_connect endp

MakeConst proc __ccall opnd:expr_t

    UNREFERENCED_PARAMETER(opnd)

    .return .if ( ( [rcx].kind != EXPR_ADDR ) || [rcx].flags & E_INDIRECT )
    .if [rcx].sym
        .return .if Parse_Pass > PASS_1
        mov rax,[rcx].sym
        .return .if !( ( [rax].asym.state == SYM_UNDEFINED && [rcx].inst == EMPTY ) || \
            ( [rax].asym.state == SYM_EXTERNAL && [rax].asym.sflags & S_WEAK && \
              [rcx].flags & E_IS_ABS ) )
        mov [rcx].value,1
    .endif
    mov [rcx].label_tok,NULL
    mov rax,[rcx].mbr
    .if rax
        .return .if [rax].asym.state != SYM_STRUCT_FIELD
    .endif
    .return .if [rcx].override != NULL
    mov [rcx].inst,EMPTY
    mov [rcx].kind,EXPR_CONST
    and [rcx].flags,not E_EXPLICIT
    mov [rcx].mem_type,MT_EMPTY
    ret

MakeConst endp

    assume r10:asym_t
    assume rax:asym_t

MakeConst2 proc __ccall opnd1:expr_t, opnd2:expr_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    mov rax,[rcx].sym
    .if [rax].state == SYM_EXTERNAL
        .return fnasmerr(2018, [rax].name)
    .endif
    mov r10,[rdx].sym
    .if ( ( [rax].state != SYM_UNDEFINED && [r10].segm != [rax].segm &&
            [r10].state != SYM_UNDEFINED ) || [r10].state == SYM_EXTERNAL )
        .return fnasmerr(2025)
    .endif
    mov rax,[rcx].sym
    mov [rcx].kind,EXPR_CONST
    mov [rdx].kind,EXPR_CONST
    add [rcx].value,[rax].offs
    add [rdx].value,[r10].offs
   .return NOT_ERROR

MakeConst2 endp

fix_struct_value proc __ccall opnd:expr_t

    UNREFERENCED_PARAMETER(opnd)

    mov rax,[rcx].mbr
    .if rax && [rax].state == SYM_TYPE
        add [rcx].value,[rax].total_size
        mov [rcx].mbr,NULL
    .endif
    ret

fix_struct_value endp

    assume rax:nothing

check_direct_reg proc __ccall opnd1:expr_t, opnd2:expr_t

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

plus_op proc __ccall opnd1:expr_t, opnd2:expr_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    .ifd check_direct_reg( rcx, rdx ) == ERROR
        .return fnasmerr( 2032 )
    .endif
    .if [rcx].kind == EXPR_REG
        mov [rcx].kind,EXPR_ADDR
    .endif
    .if [rdx].kind == EXPR_REG
       mov [rdx].kind,EXPR_ADDR
    .endif
    .if [rdx].override
        .if [rcx].override
            mov r8,[rcx].override
            mov r9,[rdx].override
            .if [r8].asm_tok.token == [r9].asm_tok.token
                .return fnasmerr( 3013 )
            .endif
        .endif
        mov [rcx].override,[rdx].override
    .endif
    .if [rcx].kind == EXPR_CONST && [rdx].kind == EXPR_CONST
        add [rcx].llvalue,[rdx].llvalue
    .elseif [rcx].kind == EXPR_FLOAT && [rdx].kind == EXPR_FLOAT
        __addq( rcx, rdx )
    .elseif( ( [rcx].kind == EXPR_ADDR && [rdx].kind == EXPR_ADDR ) )
        fix_struct_value(rcx)
        xchg rcx,rdx
        fix_struct_value(rcx)
        xchg rcx,rdx
        .return .ifd index_connect(rcx, rdx) == ERROR
        .if [rdx].sym != NULL
            mov r8,[rcx].sym
            mov r9,[rdx].sym
            .if r8 && [r8].asym.state != SYM_UNDEFINED && [r9].asym.state != SYM_UNDEFINED
                .return( fnasmerr( 2101 ) )
            .endif
            mov [rcx].label_tok,[rdx].label_tok
            mov [rcx].sym,[rdx].sym
            .if [rcx].mem_type == MT_EMPTY
                mov [rcx].mem_type,[rdx].mem_type
            .endif
            .if [rdx].inst != EMPTY
                mov [rcx].inst,[rdx].inst
            .endif
        .endif
        add [rcx].llvalue,[rdx].llvalue
        .if [rdx].type
            mov [rcx].type,[rdx].type
        .endif
    .elseif check_both(rcx, rdx, EXPR_CONST, EXPR_ADDR)
        .if [rcx].kind == EXPR_CONST
            add [rdx].llvalue,[rcx].llvalue
            .if [rcx].flags & E_INDIRECT
                or [rdx].flags,E_INDIRECT
            .endif
            .if [rcx].flags & E_EXPLICIT
                or  [rdx].flags,E_EXPLICIT
                mov [rdx].mem_type,[rcx].mem_type
            .elseif [rdx].mem_type == MT_EMPTY
                mov [rdx].mem_type,[rcx].mem_type
            .endif
            .if [rdx].mbr == NULL
                mov [rdx].mbr,[rcx].mbr
            .endif
            .if [rdx].type
                mov [rcx].type,[rdx].type
            .endif
            TokenAssign(rcx, rdx)
        .else
            add [rcx].llvalue,[rdx].llvalue
            .if [rdx].mbr
                mov [rcx].mbr,[rdx].mbr
                mov [rcx].mem_type,[rdx].mem_type
            .elseif [rcx].mem_type == MT_EMPTY && !( [rdx].flags & E_IS_TYPE )
                mov [rcx].mem_type,[rdx].mem_type
            .endif
        .endif
        fix_struct_value(rcx)
    .else
        .return ConstError(rcx, rdx)
    .endif
    .return( NOT_ERROR )

plus_op endp

    assume rcx:expr_t
    assume rdx:expr_t

minus_op proc __ccall opnd1:expr_t, opnd2:expr_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    .ifd check_direct_reg(rcx, rdx) == ERROR
        .return fnasmerr(2032)
    .endif
    mov rax,[rdx].sym
    .if !( [rcx].kind == EXPR_ADDR && [rdx].kind == EXPR_ADDR && \
           rax && [rax].asym.state == SYM_UNDEFINED )
        xchg rdx,rcx
        MakeConst(rcx)
        xchg rdx,rcx
    .endif
    .if [rcx].kind == EXPR_CONST && [rdx].kind == EXPR_CONST
        sub [rcx].llvalue,[rdx].llvalue
    .elseif [rcx].kind == EXPR_FLOAT && [rdx].kind == EXPR_FLOAT
        __subq(rcx, rdx)
    .elseif [rcx].kind == EXPR_ADDR && [rdx].kind == EXPR_CONST
        sub [rcx].llvalue,[rdx].llvalue
        fix_struct_value(rcx)
    .elseif [rcx].kind == EXPR_ADDR && [rdx].kind == EXPR_ADDR
        fix_struct_value(rcx)
        xchg rdx,rcx
        fix_struct_value(rcx)
        xchg rdx,rcx
        .if( [rdx].flags & E_INDIRECT )
            .return fnasmerr( 2032 )
        .endif
        .if( [rdx].label_tok == NULL )
            sub [rcx].llvalue,[rdx].llvalue
            .if( [rdx].flags & E_INDIRECT )
                or [rcx].flags,E_INDIRECT
            .endif
        .else
            .if [rcx].label_tok == NULL || [rcx].sym == NULL || [rdx].sym == NULL
                .return fnasmerr(2094)
            .endif
            mov r8,[rcx].sym
            add [rcx].value,[r8].asym.offs
            mov rax,[rdx].sym
            .if Parse_Pass > PASS_1
                .if ( ( [rax].asym.state == SYM_EXTERNAL || [r8].asym.state == SYM_EXTERNAL ) && rax != [rcx].sym )
                    .return( fnasmerr(2018, [r8].asym.name ) )
                .endif
                .if ( [r8].asym.segm != [rax].asym.segm )
                    .return( fnasmerr( 2025 ) )
                .endif
                mov rax,[rdx].sym
            .endif
            mov [rcx].kind,EXPR_CONST
            .if ( [r8].asym.state == SYM_UNDEFINED || [rax].asym.state == SYM_UNDEFINED )
                mov [rcx].value,1
                .if ( [r8].asym.state != SYM_UNDEFINED )
                    mov [rcx].sym,rax
                    mov [rcx].label_tok,[rdx].label_tok
                .endif
                mov [rcx].kind,EXPR_ADDR
            .else
                mov eax,[rax].asym.offs
                sub [rcx].llvalue,rax
                sub [rcx].llvalue,[rdx].llvalue
                mov [rcx].label_tok,NULL
                mov [rcx].sym,NULL
            .endif
            .if !( [rcx].flags & E_INDIRECT )
                .if [rcx].inst == T_OFFSET && [rdx].inst == T_OFFSET
                    mov [rcx].inst,EMPTY
                .endif
            .else
                mov [rcx].kind,EXPR_ADDR
            .endif
            and [rcx].flags,not E_EXPLICIT
            mov [rcx].mem_type,MT_EMPTY
        .endif
    .elseif [rcx].kind == EXPR_REG && [rdx].kind == EXPR_CONST
        .if [rdx].flags & E_INDIRECT
            or [rcx].flags,E_INDIRECT
        .endif
        mov [rcx].kind,EXPR_ADDR
        mov rax,-1
        mul [rdx].llvalue
        mov [rcx].llvalue,rax
    .else
        .return ConstError(rcx, rdx)
    .endif
    .return( NOT_ERROR )

minus_op endp

struct_field_error proc fastcall opnd:expr_t

    .if [rcx].flags & E_IS_OPEATTR
        mov [rcx].kind,EXPR_ERROR
        .return NOT_ERROR
    .endif
    fnasmerr(2166)
    ret

struct_field_error endp

dot_op proc __ccall uses rsi rdi opnd1:expr_t, opnd2:expr_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    .ifd check_direct_reg(rcx, rdx) == ERROR
        .return fnasmerr(2032)
    .endif
    .if [rcx].kind == EXPR_REG
        mov [rcx].kind,EXPR_ADDR
    .endif
    .if [rdx].kind == EXPR_REG
        mov [rdx].kind,EXPR_ADDR
    .endif
    mov rax,[rdx].sym
    .if rax && [rax].asym.state == SYM_UNDEFINED && Parse_Pass == PASS_1
        mov rax,nullstruct
        .if !rax
            mov rsi,rcx
            mov rdi,rdx
            mov nullstruct,CreateTypeSymbol( NULL, "", 0 )
            mov rdx,rdi
            mov rcx,rsi
        .endif
        mov [rdx].type,rax
        or  [rdx].flags,E_IS_TYPE
        mov [rdx].sym,NULL
        mov [rdx].kind,EXPR_CONST
    .endif
    .if [rcx].kind == EXPR_ADDR && [rdx].kind == EXPR_ADDR
        .if [rdx].mbr == NULL && !ModuleInfo.oldstructs
            .return struct_field_error(rcx)
        .endif
        .return .ifd index_connect(rcx, rdx) == ERROR
        mov rax,[rdx].sym
        .if rax
            mov r8,[rcx].sym
            .if r8 && [r8].asym.state != SYM_UNDEFINED && [rax].asym.state != SYM_UNDEFINED
                .return( fnasmerr( 2101 ) )
            .endif
            mov [rcx].label_tok,[rdx].label_tok
            mov [rcx].sym,[rdx].sym
        .endif
        mov rax,[rdx].mbr
        .if rax
            mov [rcx].mbr,rax
        .endif
        add [rcx].value,[rdx].value
        .if !( [rcx].flags & E_EXPLICIT )
            mov [rcx].mem_type,[rdx].mem_type
        .endif
        mov rax,[rdx].type
        .if rax
            mov [rcx].type,rax
        .endif
    .elseif [rcx].kind == EXPR_CONST && [rdx].kind == EXPR_ADDR
        .if [rcx].flags & E_IS_TYPE && [rcx].type
            and [rdx].flags,not E_ASSUMECHECK
            mov [rcx].llvalue,0
        .endif
        .if ( ( !ModuleInfo.oldstructs ) && ( !( [rcx].flags & E_IS_TYPE ) && [rcx].mbr == NULL ) )
            .return struct_field_error(rcx)
        .endif
        mov r8,[rcx].mbr
        .if r8 && [r8].asym.state == SYM_TYPE
            mov eax,[r8].asym.offs
            mov [rcx].llvalue,rax
        .endif
        .if [rcx].flags & E_INDIRECT
            or [rdx].flags,E_INDIRECT
        .endif
        add [rdx].llvalue,[rcx].llvalue
        .if [rdx].mbr
            mov [rcx].type,[rdx].type
        .endif
        TokenAssign(rcx, rdx)
    .elseif( [rcx].kind == EXPR_ADDR && [rdx].kind == EXPR_CONST )
        .if ( !ModuleInfo.oldstructs && ( [rdx].type == NULL || \
            !( [rdx].flags & E_IS_TYPE ) ) && [rdx].mbr == NULL )
            .return struct_field_error(rcx)
        .endif
        .if ( [rdx].flags & E_IS_TYPE && [rdx].type )
            and [rcx].flags,not E_ASSUMECHECK
            ;; v2.37: adjust for type's size only (japheth)
            mov r8,[rdx].type
            mov eax,[r8].asym.total_size
            sub [rdx].llvalue,rax
        .endif
        mov r8,[rdx].mbr
        .if r8 && [r8].asym.state == SYM_TYPE
            mov eax,[r8].asym.offs
            mov [rdx].llvalue,rax
        .endif
        add [rcx].value64,[rdx].value64
        mov [rcx].mem_type,[rdx].mem_type
        mov [rcx].type,[rdx].type
        .if r8
            mov [rcx].mbr,r8
ifdef USE_INDIRECTION
            .if ( rax && [rdx].flags & E_IS_DOT )
                .if ( [rcx].flags & E_EXPLICIT &&
                      [rdx].scale == 0x80 )
                    mov [rcx].type,NULL
                .else
                    or [rcx].flags,E_IS_DOT
                .endif
            .endif
endif
        .endif

    .elseif [rcx].kind == EXPR_CONST && [rdx].kind == EXPR_CONST
        .if [rdx].mbr == NULL && !ModuleInfo.oldstructs
            .return struct_field_error(rcx)
        .endif
        mov rax,[rdx].llvalue
        .if [rcx].type != NULL
            .if [rcx].mbr != NULL
                add [rcx].llvalue,rax
            .else
                mov [rcx].llvalue,rax
            .endif
            mov [rcx].mbr,[rdx].mbr
            mov [rcx].mem_type,[rdx].mem_type
            and [rcx].flags,not E_IS_TYPE
            .if [rdx].flags & E_IS_TYPE
                or [rcx].flags,E_IS_TYPE
            .endif
            .if [rcx].type != [rdx].type
                mov [rcx].type,[rdx].type
            .else
                mov [rcx].type,NULL
            .endif
        .else
            add [rcx].llvalue,rax
            mov [rcx].mbr,[rdx].mbr
            mov [rcx].mem_type,[rdx].mem_type
        .endif
    .else
        .return struct_field_error(rcx)
    .endif
    .return( NOT_ERROR )

dot_op endp

colon_op proc __ccall opnd1:expr_t, opnd2:expr_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    mov rax,[rdx].override
    .if rax
        .if ( ( [rcx].kind == EXPR_REG && [rax].asm_tok.token == T_REG ) || \
            ( [rcx].kind == EXPR_ADDR && [rax].asm_tok.token == T_ID ) )
            .return( fnasmerr( 3013 ) )
        .endif
    .endif
    .switch [rdx].kind
    .case EXPR_REG
        .if !( [rdx].flags & E_INDIRECT )
            .return fnasmerr( 2032 )
        .endif
        .endc
    .case EXPR_FLOAT
        .return fnasmerr( 2050 )
    .endsw
    .if ( [rcx].kind == EXPR_REG )
        .if ( [rcx].idx_reg != NULL )
            .return( fnasmerr( 2032 ) )
        .endif
        mov rax,[rcx].base_reg
        imul eax,[rax].asm_tok.tokval,special_item
        lea r8,SpecialTable
        .if !( [r8+rax].special_item.value & OP_SR )
            .return( fnasmerr( 2096 ) )
        .endif
        mov [rdx].override,[rcx].base_reg
        .if [rcx].flags & E_INDIRECT
            or [rdx].flags,E_INDIRECT
        .endif
        .if [rdx].kind == EXPR_CONST
            mov [rdx].kind,EXPR_ADDR
        .endif
        .if [rcx].flags & E_EXPLICIT
            or  [rdx].flags,E_EXPLICIT
            mov [rdx].mem_type,[rcx].mem_type
            mov [rdx].Ofssize,[rcx].Ofssize
        .endif
        TokenAssign(rcx, rdx)
        .if [rdx].type
            mov [rcx].type,[rdx].type
        .endif
    .elseif ( [rcx].kind == EXPR_ADDR && [rcx].override == NULL && [rcx].inst == EMPTY && \
              [rcx].value == 0 && [rcx].sym && [rcx].base_reg == NULL && [rcx].idx_reg == NULL )

        mov rax,[rcx].sym
        .if [rax].asym.state == SYM_GRP || [rax].asym.state == SYM_SEG
            mov [rdx].kind,EXPR_ADDR
            mov [rdx].override,[rcx].label_tok
            .if [rcx].flags & E_INDIRECT
                or [rdx].flags,E_INDIRECT
            .endif
            .if [rcx].flags & E_EXPLICIT
                or  [rdx].flags,E_EXPLICIT
                mov [rdx].mem_type,[rcx].mem_type
                mov [rdx].Ofssize,[rcx].Ofssize
            .endif
            TokenAssign(rcx, rdx)
            mov [rcx].type,[rdx].type
        .elseif Parse_Pass > PASS_1 || [rax].asym.state != SYM_UNDEFINED
            .return fnasmerr( 2096 )
        .endif
    .else
        .return fnasmerr( 2096 )
    .endif
    .return( NOT_ERROR )

colon_op endp

positive_op proc __ccall opnd1:expr_t, opnd2:expr_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    xchg rdx,rcx
    MakeConst(rcx)
    xchg rdx,rcx
    .if [rdx].kind == EXPR_CONST
        mov [rcx].kind,EXPR_CONST
        mov [rcx].llvalue,[rdx].llvalue
        mov [rcx].hlvalue,[rdx].hlvalue
    .elseif [rdx].kind == EXPR_FLOAT
        mov [rcx].kind,EXPR_FLOAT
        mov [rcx].mem_type,[rdx].mem_type
        mov [rcx].llvalue,[rdx].llvalue
        mov [rcx].hlvalue,[rdx].hlvalue
        and [rcx].chararray[15],not 0x80
        mov [rcx].flags,[rdx].flags
    .else
        .return( fnasmerr( 2026 ) )
    .endif
    .return( NOT_ERROR )

positive_op endp

negative_op proc __ccall opnd1:expr_t, opnd2:expr_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    xchg rdx,rcx
    MakeConst(rcx)
    xchg rdx,rcx
    .if [rdx].kind == EXPR_CONST
        mov [rcx].flags,[rdx].flags
        xor [rcx].flags,E_NEGATIVE
        mov [rcx].kind,EXPR_CONST
        mov rax,[rdx].llvalue
        mov rdx,[rdx].hlvalue
        neg rax
        mov [rcx].llvalue,rax
        sbb eax,eax
        .if rdx
            bt  eax,0
            adc rdx,0
            neg rdx
            mov [rcx].hlvalue,rdx
        .endif
    .elseif [rdx].kind == EXPR_FLOAT
        mov [rcx].kind,EXPR_FLOAT
        mov [rcx].mem_type,[rdx].mem_type
        mov [rcx].llvalue,[rdx].llvalue
        mov [rcx].hlvalue,[rdx].hlvalue
        xor [rcx].chararray[15],0x80
        mov [rcx].flags,[rdx].flags
        xor [rcx].flags,E_NEGATIVE
    .else
        .return fnasmerr( 2026 )
    .endif
    .return( NOT_ERROR )

negative_op endp

    assume rbx:asym_t

CheckAssume proc __ccall uses rsi rbx opnd:expr_t

    UNREFERENCED_PARAMETER(opnd)

    mov rsi,rcx
    .if [rsi].flags & E_EXPLICIT
        mov rbx,[rsi].type
        .if rbx && [rbx].mem_type == MT_PTR
            .if [rbx].is_ptr == 1
                mov [rsi].mem_type,[rbx].ptr_memtype
                mov [rsi].type,[rbx].target_type
                .return
            .endif
        .endif
    .endif

    xor ebx,ebx
    .if [rsi].idx_reg
        mov rax,[rsi].idx_reg
        mov rbx,GetStdAssumeEx( [rax].asm_tok.bytval )
    .endif
    .if !rbx && [rsi].base_reg
        mov rax,[rsi].base_reg
        mov rbx,GetStdAssumeEx( [rax].asm_tok.bytval )
    .endif

    .if rbx
        .if [rbx].mem_type == MT_TYPE
            mov [rsi].type,[rbx].type
        .elseif [rbx].is_ptr == 1
            mov [rsi].type,[rbx].target_type
            .if [rbx].target_type
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

check_streg proc __ccall opnd1:expr_t, opnd2:expr_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)

    .if [rcx].scale > 0
        .return( fnasmerr( 2032 ) )
    .endif
    inc [rcx].scale
    .if [rdx].kind != EXPR_CONST
        .return( fnasmerr( 2032 ) )
    .endif
    mov [rcx].st_idx,[rdx].value
   .return( NOT_ERROR )

check_streg endp

    assume rsi:asym_t
    assume rdi:asym_t

cmp_types proc __ccall uses rsi rdi rbx opnd1:expr_t, opnd2:expr_t, trueval:int_t

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)
    UNREFERENCED_PARAMETER(trueval)

    mov rsi,[rcx].type
    mov rdi,[rdx].type

    .if ( [rcx].mem_type == MT_PTR && [rdx].mem_type == MT_PTR )

        .if !rsi
            mov rax,[rcx].type_tok
            mov rsi,SymFind([rax].asm_tok.string_ptr)
            mov rdx,opnd2
        .endif
        .if !rdi
            mov rax,[rdx].type_tok
            mov rdi,SymFind([rax].asm_tok.string_ptr)
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
        mov rcx,opnd1
        mov [rcx].value,eax
        mov [rcx].hvalue,edx
    .else
        .if rsi && [rsi].typekind == TYPE_TYPEDEF && [rsi].is_ptr == 0
            mov [rcx].type,NULL
        .endif
        .if rdi && [rdi].typekind == TYPE_TYPEDEF && [rdi].is_ptr == 0
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

    assume rsi:expr_t
    assume rdi:expr_t
    assume rbx:token_t

calculate proc __ccall uses rsi rdi rbx opnd1:expr_t, opnd2:expr_t, oper:token_t

  local sym:asym_t
  local opnd:expr

    UNREFERENCED_PARAMETER(opnd1)
    UNREFERENCED_PARAMETER(opnd2)
    UNREFERENCED_PARAMETER(oper)

    mov rsi,rcx
    mov rdi,rdx
    mov rbx,r8

    mov [rsi].quoted_string,NULL
    .if ( [rdi].hlvalue && [rdi].mem_type != MT_REAL16 )
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
        .if [rdi].flags & E_ASSUMECHECK
            and [rdi].flags,not E_ASSUMECHECK
            .if [rsi].sym == NULL
                CheckAssume(rdi)
            .endif
        .endif
        .if [rsi].kind == EXPR_EMPTY
            TokenAssign(rsi, rdi)
            mov [rsi].type,[rdi].type
            .if [rsi].flags & E_IS_TYPE && [rsi].kind == EXPR_CONST
                and [rsi].flags,not E_IS_TYPE
            .endif
            .endc
        .endif
        .if ( [rsi].flags & E_IS_TYPE && [rsi].type == NULL && \
            ( [rdi].kind == EXPR_ADDR || [rdi].kind == EXPR_REG ) )
            .return( fnasmerr( 2009 ) )
        .endif
        mov rax,[rsi].base_reg
        .if rax && [rax].asm_tok.tokval == T_ST
            .return(check_streg(rsi, rdi))
        .endif
        .return(plus_op(rsi, rdi))
    .case T_OP_BRACKET
        .if [rsi].kind == EXPR_EMPTY
            TokenAssign(rsi, rdi)
            mov [rsi].type,[rdi].type
            .endc
        .endif
        .if [rsi].flags & E_IS_TYPE && [rdi].kind == EXPR_ADDR
            .return( fnasmerr( 2009 ) )
        .endif
        mov rax,[rsi].base_reg
        .if [rsi].base_reg && [rax].asm_tok.tokval == T_ST
            .return(check_streg(rsi, rdi))
        .endif
        .return(plus_op(rsi, rdi))
    .case '+'
        .if [rbx].specval == 0
            .return( positive_op(rsi, rdi))
        .endif
        .ifd ( EvalOperator(rsi, rdi, rbx) == ERROR )
            .return( plus_op(rsi, rdi))
        .endif
        .endc
    .case '-'
        .if [rbx].specval == 0
            .return( negative_op(rsi, rdi))
        .endif
        .ifd ( EvalOperator(rsi, rdi, rbx) == ERROR )
            .return(minus_op(rsi, rdi))
        .endif
        .endc
    .case T_DOT
        .return(dot_op(rsi, rdi))
    .case T_COLON
        .return(colon_op(rsi, rdi))
    .case '*'
        MakeConst(rsi)
        MakeConst(rdi)
        .if [rsi].kind == EXPR_CONST && [rdi].kind == EXPR_CONST
            __mul64([rdi].llvalue, [rsi].llvalue)
            mov [rsi].llvalue,rax
        .elseif check_both(rsi, rdi, EXPR_REG, EXPR_CONST)
            .ifd check_direct_reg(rsi, rdi) == ERROR
                .return fnasmerr(2032)
            .endif
            .if [rdi].kind == EXPR_REG
                mov [rsi].idx_reg,[rdi].base_reg
                mov [rsi].scale,[rsi].value
                mov [rsi].value,0
            .else
                mov [rsi].idx_reg,[rsi].base_reg
                mov [rsi].scale,[rdi].value
            .endif
            .if [rsi].scale == 0
                .return( fnasmerr( 2083 ) )
            .endif
            mov [rsi].base_reg,NULL
            or  [rsi].flags,E_INDIRECT
            mov [rsi].kind,EXPR_ADDR
        .elseif [rsi].kind == EXPR_FLOAT && [rdi].kind == EXPR_FLOAT
            __mulq(rsi, rdi)
        .elseifd ( EvalOperator(rsi, rdi, rbx) == ERROR )
            .return( ConstError(rsi, rdi))
        .endif
        .endc
    .case '/'
        .if ( ( [rsi].kind == EXPR_FLOAT && [rdi].kind == EXPR_FLOAT ) )
            __divq(rsi, rdi)
            .endc
        .endif
        .endc .ifd ( EvalOperator(rsi, rdi, rbx) != ERROR )
        MakeConst(rsi)
        MakeConst(rdi)
        .if( !( [rsi].kind == EXPR_CONST && [rdi].kind == EXPR_CONST ) )
            .return(ConstError(rsi, rdi))
        .endif
        .if [rdi].llvalue == 0
            .return(fnasmerr(2169))
        .endif
        __div64([rsi].llvalue, [rdi].llvalue)
        mov [rsi].llvalue,rax
        .endc
    .case T_BINARY_OPERATOR
        .if [rbx].tokval == T_PTR
            .if !( [rsi].flags & E_IS_TYPE )
                mov rax,[rsi].sym
                .if rax && [rax].asym.state == SYM_UNDEFINED
                    CreateTypeSymbol(rax, NULL, 1)
                    mov [rsi].type,[rsi].sym
                    mov [rsi].sym,NULL
                    or  [rsi].flags,E_IS_TYPE
                .else
                    .return( fnasmerr( 2010 ) )
                .endif
            .endif
            or [rdi].flags,E_EXPLICIT
            .if ( [rdi].kind == EXPR_REG && ( !( [rdi].flags & E_INDIRECT ) || [rdi].flags & E_ASSUMECHECK ) )
                mov rax,[rdi].base_reg
                mov ecx,[rax].asm_tok.tokval
                imul eax,ecx,special_item
                lea r8,SpecialTable
                .if ( [r8+rax].special_item.value & OP_SR )
                    .if [rsi].value != 2 && [rsi].value != 4
                        .return( fnasmerr( 2032 ) )
                    .endif
                .else
                    SizeFromRegister(ecx)
                    .if ( [rsi].value != eax )
                        .return(fnasmerr(2032))
                    .endif
                .endif
            .elseif [rdi].kind == EXPR_FLOAT
                .if !( [rsi].mem_type & MT_FLOAT )
                    .return( fnasmerr( 2050 ) )
                .endif
            .endif
            mov [rdi].mem_type,[rsi].mem_type
            mov [rdi].Ofssize,[rsi].Ofssize
            .if [rdi].flags & E_IS_TYPE
                mov [rdi].value,[rsi].value
            .endif
            .if [rsi].override != NULL
                .if [rdi].override == NULL
                    mov [rdi].override,[rsi].override
                .endif
                mov [rdi].kind,EXPR_ADDR
            .endif
            TokenAssign(rsi, rdi)
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
                    .return(fnasmerr(2094))
                .endif
            .else
                .return(fnasmerr(2095))
            .endif
        .else
            .return(ConstError(rsi, rdi))
        .endif
        .switch [rbx].tokval
        .case T_EQ
            .if ( [rsi].flags & E_IS_TYPE && [rdi].flags & E_IS_TYPE )
                cmp_types(rsi, rdi, -1)
            .else
                xor eax,eax
                xor edx,edx
                .if [rsi].kind == EXPR_FLOAT
                    add rdx,[rsi].hlvalue
                    sub rdx,[rdi].hlvalue
                    mov [rsi].hlvalue,rax
                    mov [rsi].kind,EXPR_CONST
                    mov [rsi].mem_type,MT_EMPTY
                .endif
                add rdx,[rsi].llvalue
                sub rdx,[rdi].llvalue
                .ifz
                    dec rax
                .endif
                mov [rsi].llvalue,rax
            .endif
            .endc
        .case T_NE
            .if ( [rsi].flags & E_IS_TYPE && [rdi].flags & E_IS_TYPE )
                cmp_types(rsi, rdi, 0)
            .else
                xor eax,eax
                xor edx,edx
                .if [rsi].kind == EXPR_FLOAT
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
            .endif
            .endc
        .case T_LT
            .if [rsi].kind == EXPR_FLOAT
                __cmpq(rsi, rdi)
                xor edx,edx
                mov [rsi].hlvalue,rdx
                mov [rsi].kind,EXPR_CONST
                mov [rsi].mem_type,MT_EMPTY
                .if eax == -1
                    dec rdx
                .endif
            .else
                xor edx,edx
                .if [rsi].value64 < [rdi].value64
                    dec rdx
                .endif
            .endif
            mov [rsi].llvalue,rdx
            .endc
        .case T_LE
            .if [rsi].kind == EXPR_FLOAT
                __cmpq(rsi, rdi)
                xor edx,edx
                mov [rsi].hlvalue,rdx
                mov [rsi].kind,EXPR_CONST
                mov [rsi].mem_type,MT_EMPTY
                .if eax != 1
                    dec rdx
                .endif
            .else
                xor edx,edx
                .if [rsi].value64 <= [rdi].value64
                    dec rdx
                .endif
            .endif
            mov [rsi].llvalue,rdx
           .endc
        .case T_GT
            .if [rsi].kind == EXPR_FLOAT
                __cmpq(rsi, rdi)
                xor edx,edx
                mov [rsi].hlvalue,rdx
                mov [rsi].kind,EXPR_CONST
                mov [rsi].mem_type,MT_EMPTY
                .if eax == 1
                    dec rdx
                .endif
            .else
                xor edx,edx
                .if [rsi].value64 > [rdi].value64
                    dec rdx
                .endif
            .endif
            mov [rsi].llvalue,rdx
           .endc
        .case T_GE
            .if [rsi].kind == EXPR_FLOAT
                __cmpq(rsi, rdi)
                xor edx,edx
                mov [rsi].hlvalue,rdx
                mov [rsi].kind,EXPR_CONST
                mov [rsi].mem_type,MT_EMPTY
                .if eax != -1
                    dec rdx
                .endif
            .else
                xor edx,edx
                .if [rsi].value64 >= [rdi].value64
                    dec rdx
                .endif
            .endif
            mov [rsi].llvalue,rdx
           .endc

        .case T_MOD
            .if [rdi].llvalue == 0
                .return(fnasmerr(2169))
            .endif
            .if [rsi].kind == EXPR_FLOAT
                __divo(rsi, rdi, &opnd)
                mov [rsi].llvalue,opnd.llvalue
                mov [rsi].hlvalue,opnd.hlvalue
               .endc
            .endif
            xor edx,edx
            mov rax,[rsi].llvalue
            div [rdi].llvalue
            mov [rsi].llvalue,rdx
           .endc

        .case T_SAL
        .case T_SHL
            .if [rdi].value < 0
                fnasmerr( 2092 )
                .endc
            .endif
            mov r8d,64
            .if [rsi].kind == EXPR_FLOAT
                mov r8d,128
            .elseif ModuleInfo.Ofssize == USE32
                mov r8d,32
            .endif
            __shlo(rsi, [rdi].value, r8d)
            .if ModuleInfo.m510
                xor eax,eax
                mov [rsi].hvalue,eax
                mov [rsi].hlvalue,rax
            .endif
            .endc

        .case T_SHR
            .if [rdi].value < 0
                fnasmerr( 2092 )
                .endc
            .endif
            mov eax,64
            .if [rsi].kind == EXPR_FLOAT
                mov eax,128
            .elseif ModuleInfo.Ofssize == USE32
                mov eax,32
            .endif
            __shro(rsi, [rdi].value, eax)
            .endc

        .case T_SAR
            .if [rdi].value < 0
                fnasmerr( 2092 )
                .endc
            .endif
            mov eax,64
            .if [rsi].kind == EXPR_FLOAT
                mov eax,128
            .elseif ModuleInfo.Ofssize == USE32
                mov eax,32
            .endif
            __saro(rsi, [rdi].value, eax)
            .endc

        .case T_ADD
            .if [rsi].kind != EXPR_FLOAT
                fnasmerr( 2187 )
            .endif
            add [rsi].llvalue,[rdi].llvalue
            adc [rsi].hlvalue,[rdi].hlvalue
           .endc

        .case T_SUB
            .if [rsi].kind != EXPR_FLOAT
                fnasmerr( 2187 )
            .endif
            sub [rsi].hlvalue,[rdi].hlvalue
            sbb [rsi].llvalue,[rdi].llvalue
           .endc

        .case T_MUL
            .if [rsi].kind != EXPR_FLOAT
                fnasmerr( 2187 )
            .endif
            __mulo(rsi, rdi, NULL)
            .endc

        .case T_DIV
            .if [rsi].kind != EXPR_FLOAT
                fnasmerr( 2187 )
            .endif
            __divo(rsi, rdi, &opnd)
            .endc

        .case T_AND
            .if [rsi].kind == EXPR_FLOAT
                and [rsi].hlvalue,[rdi].hlvalue
            .endif
            and [rsi].llvalue,[rdi].llvalue
           .endc

        .case T_OR
            .if [rsi].kind == EXPR_FLOAT
                or [rsi].hlvalue,[rdi].hlvalue
            .endif
            or [rsi].llvalue,[rdi].llvalue
           .endc

        .case T_XOR
            .if [rsi].kind == EXPR_FLOAT
                xor [rsi].hlvalue,[rdi].hlvalue
            .endif
            xor [rsi].llvalue,[rdi].llvalue
           .endc
        .endsw
        .endc
    .case T_UNARY_OPERATOR
        .if [rbx].tokval == T_NOT
            MakeConst(rdi)
            .if [rdi].kind != EXPR_CONST && [rdi].kind != EXPR_FLOAT
                .return fnasmerr(2026)
            .endif
            TokenAssign(rsi, rdi)
            not [rsi].llvalue
            .if [rsi].kind == EXPR_FLOAT
                not [rsi].hlvalue
            .endif
            .endc
        .endif
        imul eax,[rbx].tokval,special_item
        lea r8,SpecialTable
        mov ecx,[r8+rax].special_item.value
        mov rax,[rdi].sym
        .if [rdi].mbr != NULL
            mov rax,[rdi].mbr
        .endif
        mov sym,rax
        mov esi,ecx
        .if [rdi].inst != EMPTY
            tstrlen([rbx].string_ptr)
            inc eax
            add rax,[rbx].tokpos
        .elseif rax
            mov rax,[rax].asym.name
        .elseif [rdi].base_reg != NULL && !( [rdi].flags & E_INDIRECT )
            mov rax,[rdi].base_reg
            mov rax,[rax].asm_tok.string_ptr
        .else
            tstrlen([rbx].string_ptr)
            inc eax
            add rax,[rbx].tokpos
        .endif
        mov rdx,rax
        mov ecx,esi
        mov rsi,opnd1

        .switch [rdi].kind

        .case EXPR_CONST
            mov rax,[rdi].mbr
            .if rax && [rax].asym.state != SYM_TYPE
                .if [rax].asym.mem_type == MT_BITS
                    .if !( ecx & AT_BF )
                        .return( invalid_operand( rdi, [rbx].string_ptr, rdx ) )
                    .endif
                .else
                    .if !( ecx & AT_FIELD )
                        .return( invalid_operand( rdi, [rbx].string_ptr, rdx ) )
                    .endif
                .endif
            .elseif [rdi].flags & E_IS_TYPE
                .if !( ecx & AT_TYPE )
                    .return invalid_operand( rdi, [rbx].string_ptr, rdx )
                .endif
            .else
                .if !( ecx & AT_NUM )
                    .if [rdi].flags & E_IS_OPEATTR
                        .return ERROR
                    .endif
                    .if ecx == 2
                        .return fnasmerr( 2094 )
                    .endif
                    .return fnasmerr( 2009 )
                .endif
            .endif
            .endc

        .case EXPR_ADDR
            .if ( [rdi].flags & E_INDIRECT && [rdi].sym == NULL )
                .if !( ecx & AT_IND )
                    .return invalid_operand(rdi, [rbx].string_ptr, rdx)
                .endif
            .else
                .if !( ecx & AT_LABEL )
                    .return ERROR .if [rdi].flags & E_IS_OPEATTR
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
        lea r8,SpecialTable
        mov eax,[r8+rax].special_item.sflags
        lea rcx,unaryop
        mov rax,[rcx+rax*8]
        assume rax:ptr unaryop_t
        rax( rsi, rdi, sym, [rbx].tokval, rdx )
        assume rax:nothing
        .return
    .default
        .return fnasmerr( 2008, [rbx].string_ptr )
    .endsw
    .return( NOT_ERROR )

calculate endp

PrepareOp proc __ccall opnd:expr_t, old:expr_t, oper:token_t

    UNREFERENCED_PARAMETER(opnd)
    UNREFERENCED_PARAMETER(old)
    UNREFERENCED_PARAMETER(oper)

    and [rcx].flags,not E_IS_OPEATTR
    .if [rdx].flags & E_IS_OPEATTR
        or [rcx].flags,E_IS_OPEATTR
    .endif
    .switch [r8].asm_tok.token
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
        .switch [r8].asm_tok.tokval
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

OperErr proc __ccall i:int_t, tokenarray:token_t

    UNREFERENCED_PARAMETER(i)
    UNREFERENCED_PARAMETER(tokenarray)

    imul eax,ecx,asm_tok
    add rax,rdx
    .if [rax].asm_tok.token <= T_BAD_NUM
        fnasmerr(2206)
    .else
        fnasmerr(2008, [rax].asm_tok.string_ptr)
    .endif
    ret

OperErr endp

    assume rsi:token_t

evaluate proc __ccall uses rsi rdi rbx r12  opnd1:expr_t, i:ptr int_t,
        tokenarray:token_t, _end:int_t, flags:byte

   .new rc:int_t = NOT_ERROR
   .new opnd2:expr
   .new exp_token:int_t
   .new last:ptr asm_tok

    mov  rdi,rcx
    imul ebx,[rdx],asm_tok
    add  rbx,r8
    imul eax,r9d,asm_tok
    add  rax,r8
    mov  last,rax

    mov al,[rbx].token
    .if ( [rdi].kind == EXPR_EMPTY &&
          al != T_OP_BRACKET &&
          al != T_OP_SQ_BRACKET &&
          al != '+' &&
          al != '-' &&
          al != T_UNARY_OPERATOR
        )
        mov rc,get_operand(rdi, rdx, r8, flags)
        mov rax,i
        imul ebx,[rax],asm_tok
        add rbx,tokenarray
    .endif

    .while ( rc == NOT_ERROR && rbx < last &&
             [rbx].token != T_CL_BRACKET &&
             [rbx].token != T_CL_SQ_BRACKET )

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

                    SetEvexOpt(rsi)
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
                        OperErr(eax, tokenarray)
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

            mov rax,i
            imul ebx,[rax],asm_tok
            add rbx,tokenarray
            mov eax,exp_token

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

        .elseif ( ( [rbx].token == T_OP_BRACKET || [rbx].token == T_OP_SQ_BRACKET || \
                    [rbx].token == '+' || [rbx].token == '-' || [rbx].token == T_UNARY_OPERATOR ) )
            movzx ecx,flags
            or ecx,EXPF_ONEOPND
            mov rc,evaluate( &opnd2, i, tokenarray, _end, cl )
        .else
            mov rc,get_operand( &opnd2, i, tokenarray, flags )
        .endif

        mov rcx,i
        imul ebx,[rcx],asm_tok
        add rbx,tokenarray

        movzx eax,[rbx].token
        .while ( rc != ERROR && rbx < last && eax != T_CL_BRACKET && eax != T_CL_SQ_BRACKET )

            .if ( eax == '+' || eax == '-' )
                mov [rbx].specval,1
            .elseif( !( eax >= T_OP_BRACKET || eax == T_UNARY_OPERATOR || \
                        eax == T_BINARY_OPERATOR ) || eax == T_UNARY_OPERATOR )

                ;; v2.26 - added for {k1}{z}..

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
            mov r12d,get_precedence(rbx)
            get_precedence(rsi)
            .break .if r12d >= eax
            mov cl,flags
            or  cl,EXPF_ONEOPND
            mov rc,evaluate( &opnd2, i, tokenarray, _end, cl )
            mov rax,i
            imul ebx,[rax],asm_tok
            add rbx,tokenarray
            movzx eax,[rbx].token
        .endw

        .if ( rc == ERROR && opnd2.flags & E_IS_OPEATTR )

            .while ( rbx < last &&
                    [rbx].token != T_CL_BRACKET &&
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
    mov eax,rc
    ret

evaluate endp

    option proc:public

EvalOperand proc __ccall uses rsi rbx start_tok:ptr int_t, tokenarray:token_t, end_tok:int_t,
        result:expr_t, flags:byte

    mov  ebx,[rcx]
    mov  esi,ebx
    imul ebx,ebx,asm_tok
    add  rbx,rdx

    init_expr(r9)
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
            .if [rbx].tokval == T_PROC
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
    .if flags & EXPF_NOERRMSG
        lea rax,noasmerr
    .endif
    mov fnasmerr,rax
    evaluate( result, rdx, tokenarray, esi, flags )
    ret

EvalOperand endp

EmitConstError proc __ccall opnd:expr_t

    UNREFERENCED_PARAMETER(opnd)

    asmerr(2084)
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
