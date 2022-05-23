; PARSER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Parser
;

include limits.inc
include malloc.inc

include asmc.inc
include memalloc.inc
include parser.inc
include preproc.inc
include reswords.inc
include codegen.inc
include expreval.inc
include fixup.inc
include types.inc
include label.inc
include segment.inc
include assume.inc
include proc.inc
include input.inc
include tokenize.inc
include listing.inc
include data.inc
include fastpass.inc
include omf.inc
include omfspec.inc
include condasm.inc
include extern.inc
include qfloat.inc
include reswords.inc
include Indirection.inc
include operator.inc

public SegOverride

externdef ProcStatus:int_t
externdef opnd_clstab:opnd_class
externdef vex_flags:byte
externdef Frame_Type:byte  ; Frame of current fixup
externdef Frame_Datum:word ; Frame datum of current fixup

ADDRSIZE macro s, x
  ifdif <x>,<eax>
    if sizeof(x) eq 4
      mov eax,x
    else
      mov al,x
    endif
  endif
    cmp s,al
    setne al
    exitm<al>
    endm

IS_ADDR32 macro s
    xor eax,eax
    cmp [s].Ofssize,al
    setz al
    exitm<[s].adrsiz == al>
    endm

OPSIZE32 macro s
    xor eax,eax
    cmp [s].Ofssize,al
    setz al
    exitm<al>
    endm

OPSIZE16 macro s
    xor eax,eax
    cmp [s].Ofssize,al
    setnz al
    exitm<al>
    endm

InWordRange macro val
    exitm<!!(val !> 65535 || val !< -65535)>
    endm

CCALLBACK(fpDirective, :int_t, :token_t)

extern ResWordTable:ReservedWord
extern directive_tab:fpDirective

;; parsing of branch instructions with imm operand is found in branch.asm
process_branch proto :ptr code_info, :uint_t, :expr_t
ExpandLine proto :string_t, :token_t
ExpandHllProcEx proto :string_t, :int_t, :token_t

    .data
    SegOverride asym_t 0
    LastRegOverride int_t 0 ; needed for CMPS

    .data?
    align 4

    ;; linked lists of:     index
    ;;--------------------------------
    ;; - undefined symbols  TAB_UNDEF
    ;; - externals          TAB_EXT
    ;; - segments           TAB_SEG
    ;; - groups             TAB_GRP
    ;; - procedures         TAB_PROC
    ;; - aliases            TAB_ALIAS
    SymTables symbol_queue TAB_LAST dup(<>)

    .code

;; add item to linked list of symbols

    assume edx:dsym_t
    assume ecx:ptr symbol_queue

sym_add_table proc queue:ptr symbol_queue, item:dsym_t

    mov ecx,queue
    mov edx,item
    xor eax,eax

    .if [ecx].head == eax
        mov [ecx].head,edx
        mov [ecx].tail,edx
        mov [edx].next,eax
        mov [edx].prev,eax
    .else
        mov [edx].prev,[ecx].tail
        mov [eax].dsym.next,edx
        mov [ecx].tail,edx
        mov [edx].next,NULL
    .endif
    ret

sym_add_table endp

;; remove an item from a symbol queue.
;; this is called only for TAB_UNDEF and TAB_EXT,
;; segments, groups, procs or aliases never change their state.

sym_remove_table proc queue:ptr symbol_queue, item:dsym_t

    ;; unlink the node

    mov ecx,queue
    mov edx,item

    .if [edx].prev
        mov eax,[edx].next
        mov edx,[edx].prev
        mov [edx].next,eax
        mov edx,item
    .endif
    .if [edx].next
        mov eax,[edx].prev
        mov edx,[edx].next
        mov [edx].prev,eax
        mov edx,item
    .endif
    .if [ecx].head == edx
        mov [ecx].head,[edx].next
    .endif
    .if [ecx].tail == edx
        mov [ecx].tail,[edx].prev
    .endif
    mov [edx].next,NULL
    mov [edx].prev,NULL
    ret

sym_remove_table endp

    assume ecx:asym_t

sym_ext2int proc sym:asym_t

;; Change symbol state from SYM_EXTERNAL to SYM_INTERNAL.
;; called by:
;; - CreateConstant()             EXTERNDEF name:ABS           -> constant
;; - CreateAssemblyTimeVariable() EXTERNDEF name:ABS           -> assembly-time variable
;; - CreateLabel()                EXTERNDEF name:NEAR|FAR|PROC -> code label
;; - data_dir()                   EXTERNDEF name:typed memref  -> data label
;; - ProcDir()           PROTO or EXTERNDEF name:NEAR|FAR|PROC -> PROC

    ;; v2.07: GlobalQueue has been removed

    mov ecx,sym
    .if ( !( [ecx].flag1 & S_ISPROC ) && !( [ecx].flags & S_ISPUBLIC ) )
        or [ecx].flags,S_ISPUBLIC
        AddPublicData( sym )
    .endif
    sym_remove_table( &SymTables[TAB_EXT*symbol_queue], sym )
    mov ecx,sym
    .if !( [ecx].flag1 & S_ISPROC ) ;; v2.01: don't clear flags for PROTO
        mov [ecx].first_size,0
    .endif
    mov [ecx].state,SYM_INTERNAL
    ret

sym_ext2int endp

GetLangType proc i:ptr int_t, tokenarray:token_t, plang:ptr byte

    mov ecx,i
    mov edx,[ecx]
    shl edx,4
    add edx,tokenarray
    assume edx:token_t

    mov eax,[edx].string_ptr
    mov eax,[eax]
    or  al,0x20

    .if ( [edx].token == T_ID && ax == 'c' )
        ;; proto c :word or proc c:word
        .if ( !( [edx-16].tokval == T_PROC && [edx+16].token == T_COLON ) )
            mov [edx].token,T_RES_ID
            mov [edx].tokval,T_CCALL
            mov [edx].bytval,1
        .endif
    .endif
    .if( [edx].token == T_RES_ID )
        .if ( [edx].tokval >= T_CCALL && [edx].tokval <= T_WATCALL )
            mov al,[edx].bytval
            mov edx,plang
            mov [edx],al
            inc dword ptr [ecx]
            .return( NOT_ERROR )
        .endif
    .endif
    mov eax,ERROR
    ret

GetLangType endp

;; get size of a register
;; v2.06: rewritten, since the sflags field
;; does now contain size for GPR, STx, MMX, XMM regs.

SizeFromRegister proc registertoken:int_t

    mov eax,GetSflagsSp(registertoken)
    and eax,SFR_SIZMSK
    .return .if eax

    .if ( GetValueSp(registertoken) & OP_SR )

        movzx eax,CurrWordSize
        .return
    .endif

    ;; CRx, DRx, TRx remaining
    mov eax,4
    .if ModuleInfo.Ofssize == USE64
        mov eax,8
    .endif
    ret

SizeFromRegister endp

;; get size from memory type

;; MT_PROC memtype is set ONLY in typedefs ( state=SYM_TYPE, typekind=TYPE_TYPEDEF)
;; and makes the type a PROTOTYPE. Due to technical (obsolete?) restrictions the
;; prototype data is stored in another symbol and is referenced in the typedef's
;; target_type member.

SizeFromMemtype proc mem_type:uchar_t, Ofssize:int_t, type:asym_t

    movzx eax,mem_type
    .if al == MT_ZWORD
        .return 64
    .endif
    mov ecx,eax
    and ecx,MT_SPECIAL
    .ifz
        and eax,MT_SIZE_MASK
        inc eax
        .return
    .endif

    mov ecx,Ofssize
    .if ( ecx == USE_EMPTY )
        movzx ecx,ModuleInfo.Ofssize
    .endif
    mov edx,2
    shl edx,cl
    .switch eax
    .case MT_NEAR
        mov eax,edx
        .endc
    .case MT_FAR
        lea eax,[edx+2]
        .endc
    .case MT_PROC
        mov eax,edx
        mov ecx,type
        .if [ecx].is_far
            add eax,2
        .endif
        .endc
    .case MT_PTR
        mov eax,edx
        movzx ecx,ModuleInfo._model
        mov edx,1
        shl edx,cl
        and edx,SIZE_DATAPTR
        .ifnz
            add eax,2
        .endif
        .endc
    .case MT_TYPE
        mov ecx,type
        .if ecx
            mov eax,[ecx].total_size
            .endc
        .endif
    .default
        xor eax,eax
    .endsw
    ret

SizeFromMemtype endp

;; get memory type from size

    assume ecx:ptr special_item

MemtypeFromSize proc size:int_t, ptype:ptr byte

    .for ( ecx = T_BYTE * special_item :,
           SpecialTable[ecx].type == RWT_STYPE: ecx += special_item )

        mov al,SpecialTable[ecx].bytval
        and eax,MT_SPECIAL
        .if eax == 0

            ;; the size is encoded 0-based in field mem_type
            mov al,SpecialTable[ecx].bytval
            .if al != MT_ZWORD
                and eax,MT_SIZE_MASK
            .endif
            inc eax
            .if eax == size
                mov edx,ptype
                mov al,SpecialTable[ecx].bytval
                mov [edx],al
                .return NOT_ERROR
            .endif
        .endif
    .endf
    mov eax,ERROR
    ret

MemtypeFromSize endp

    assume edx:ptr code_info

OperandSize proc opnd:int_t, CodeInfo:ptr code_info

    ;; v2.0: OP_M8_R8 and OP_M16_R16 have the DFT bit set!
    mov eax,opnd
    .switch
    .case eax == OP_NONE
        .return 0
    .case eax == OP_M
        mov edx,CodeInfo
        .return SizeFromMemtype( [edx].mem_type, [edx].Ofssize, NULL )
    .case eax & ( OP_R8 or OP_M08 or OP_I8 )
        .return 1
    .case eax & ( OP_R16 or OP_M16 or OP_I16 or OP_SR )
        .return 2
    .case eax & ( OP_R32 or OP_M32 or OP_I32 )
        .return 4
    .case eax & ( OP_K or OP_R64 or OP_M64 or OP_MMX or OP_I64 )
        .return 8
    .case eax & ( OP_I48 or OP_M48 )
        .return 6
    .case eax & ( OP_STI or OP_M80 )
        .return 10
    .case eax & ( OP_XMM or OP_M128 )
        .return 16
    .case eax & ( OP_YMM or OP_M256 )
        .return 32
    .case eax & ( OP_ZMM or OP_M512 )
        .return 64
    .case eax & OP_RSPEC
        mov eax,4
        mov edx,CodeInfo
        .if [edx].Ofssize == USE64
            mov eax,8
        .endif
        .return
    .endsw
    xor eax,eax
    ret
OperandSize endp

comp_mem16 proc fastcall private reg1:int_t, reg2:int_t

;; compare and return the r/m field encoding of 16-bit address mode;
;; call by set_rm_sib() only;

    .if ecx == T_BX
        .return(RM_BX_SI) .if edx == T_SI ;; 00
        .return(RM_BX_DI) .if edx == T_DI ;; 01
    .elseif ecx == T_BP
        .return(RM_BP_SI) .if edx == T_SI ;; 02
        .return(RM_BP_DI) .if edx == T_DI ;; 03
    .else
        .return asmerr(2030)
    .endif
    asmerr(2029)
    ret

comp_mem16 endp

    assume ecx:asym_t

check_assume proc private CodeInfo:ptr code_info, sym:asym_t, default_reg:int_t

;; Check if an assumed segment register is found, and
;; set CodeInfo->RegOverride if necessary.
;; called by seg_override().
;; at least either sym or SegOverride is != NULL.

    local reg:int_t
    local assum:asym_t

    mov ecx,sym
    .return .if ecx && [ecx].state == SYM_UNDEFINED


    mov reg,GetAssume( SegOverride, ecx, default_reg, &assum )
    ;; set global vars Frame and Frame_Datum
    SetFixupFrame( assum, FALSE )

    mov ecx,sym
    .if reg == ASSUME_NOTHING
        .if ecx
            .if [ecx].segm != NULL
                asmerr(2074, [ecx].name)
            .else
                mov eax,CodeInfo
                mov ecx,default_reg
                mov [eax].code_info.RegOverride,ecx
            .endif
        .else
            mov ecx,SegOverride
            asmerr(2074, [ecx].name)
        .endif
    .elseif default_reg != EMPTY
        mov eax,CodeInfo
        mov ecx,reg
        mov [eax].code_info.RegOverride,ecx
    .endif
    ret

check_assume endp

seg_override proc private CodeInfo:ptr code_info, seg_reg:int_t, sym:asym_t, direct:int_t

;; called by set_rm_sib(). determine if segment override is necessary
;; with the current address mode;
;; - seg_reg: register index (T_DS, T_BP, T_EBP, T_BX, ... )


    local default_seg:int_t
    local assum:asym_t

    mov edx,CodeInfo
    mov eax,[edx].pinstr
    movzx eax,[eax].instr_item.flags
    and eax,II_ALLOWED_PREFIX

    ;; don't touch segment overrides for string instructions
    .return .if eax == AP_REP || eax == AP_REPxx

    .if [edx].token == T_LEA
        mov [edx].RegOverride,ASSUME_NOTHING ;; skip segment override
        .return SetFixupFrame(sym, FALSE)
    .endif

    .switch seg_reg
    .case T_BP
    .case T_EBP
    .case T_ESP
        ;; todo: check why cases T_RBP/T_RSP aren't needed!
        mov default_seg,ASSUME_SS
        .endc
    .default
        mov default_seg,ASSUME_DS
    .endsw

    .if [edx].RegOverride != EMPTY

        mov assum,GetOverrideAssume( [edx].RegOverride )
        ;; assume now holds assumed SEG/GRP symbol

        .if sym
            mov eax,assum
            .if eax == NULL
                mov eax,sym
            .endif
            SetFixupFrame(eax, FALSE)
        .elseif direct
            ;; no label attached (DS:[0]). No fixup is to be created!

            .if assum
                GetSymOfssize( assum )
                mov edx,CodeInfo
                mov [edx].adrsiz,ADDRSIZE( [edx].Ofssize, eax )
            .else
                ;; v2.01: if -Zm, then use current CS offset size.
                ;; This isn't how Masm v6 does it, but it matches Masm v5.
                mov edx,CodeInfo
                .if ModuleInfo.m510
                    mov [edx].adrsiz,ADDRSIZE( [edx].Ofssize, ModuleInfo.Ofssize )
                .else
                    mov [edx].adrsiz,ADDRSIZE( [edx].Ofssize, ModuleInfo.defOfssize )
                .endif
            .endif
        .endif
    .else
        .if sym || SegOverride
            check_assume( CodeInfo, sym, default_seg )
        .endif
        .if sym == NULL && SegOverride
            GetSymOfssize( SegOverride )
            mov edx,CodeInfo
            mov [edx].adrsiz,ADDRSIZE( [edx].Ofssize, eax )
        .endif
    .endif
    mov edx,CodeInfo
    .if [edx].RegOverride == default_seg
        mov [edx].RegOverride,ASSUME_NOTHING
    .endif
    ret

seg_override endp

;; prepare fixup creation
;; called by:
;; - idata_fixup()
;; - process_branch() in branch.c
;; - data_item() in data.c

set_frame proc sym:asym_t

    mov eax,SegOverride
    .if !eax
        mov eax,sym
    .endif
    SetFixupFrame(eax, FALSE)
    ret

set_frame endp

;; set fixup frame if OPTION OFFSET:SEGMENT is set and
;; OFFSET or SEG operator was used.
;; called by:
;; - idata_fixup()
;; - data_item()

set_frame2 proc sym:asym_t

    mov eax,SegOverride
    .if !eax
        mov eax,sym
    .endif
    SetFixupFrame(eax, TRUE)
    ret

set_frame2 endp

    assume edx:nothing
    assume ecx:nothing
    assume esi:ptr code_info

set_rm_sib proc private uses esi edi ebx CodeInfo:ptr code_info,
    CurrOpnd:uint_t, s:char_t, index:int_t, base:int_t, sym:asym_t

;; encode ModRM and SIB byte for memory addressing.
;; called by memory_operand().
;; in:  ss = scale factor (00=1,40=2,80=4,C0=8)
;;   index = index register (T_DI, T_ESI, ...)
;;    base = base register (T_EBP, ... )
;;     sym = symbol (direct addressing, displacement)
;; out: CodeInfo->rm_byte, CodeInfo->sib, CodeInfo->rex


    local temp      :int_t
    local mod_field :uchar_t
    local rm_field  :uchar_t
    local base_reg  :uchar_t
    local idx_reg   :uchar_t
    local bit3_base :uchar_t
    local bit3_idx  :uchar_t
    local rex       :uchar_t

    ;; clear mod
    mov rm_field,0
    mov bit3_base,0
    mov bit3_idx,0
    mov rex,0
    mov esi,CodeInfo
    mov ebx,CurrOpnd
    shl ebx,4

    .if base == T_RIP
        or [esi].flags,CI_BASE_RIP
    .endif
    .if [esi].opnd[ebx].InsFixup ;; symbolic displacement given?
        mov mod_field,MOD_10
    .elseif [esi].opnd[ebx].data32l == 0 || base == T_RIP ;; no displacement (or 0)
        mov mod_field,MOD_00
    .elseif [esi].opnd[ebx].data32l > SCHAR_MAX || [esi].opnd[ebx].data32l < SCHAR_MIN
        mov mod_field,MOD_10 ;; full size displacement
    .else
        mov mod_field,MOD_01 ;; byte size displacement
    .endif

    .if index == EMPTY && base == EMPTY

        ;; direct memory.
        ;; clear the rightmost 3 bits

        or [esi].flags,CI_ISDIRECT
        mov mod_field,MOD_00

        ;; default is DS:[], DS: segment override is not needed
        seg_override( esi, T_DS, sym, TRUE )

ifndef ASMC64
        .if ( [esi].Ofssize == USE16 && [esi].adrsiz == 0 ) || \
            ( [esi].Ofssize == USE32 && [esi].adrsiz == 1 )
            .return asmerr(2011) .if !InWordRange([esi].opnd[ebx].data32l)
            mov rm_field,RM_D16 ;; D16=110b
        .else
endif
            mov rm_field,RM_D32 ;; D32=101b
ifndef ASMC64
            .if ( [esi].Ofssize == USE64 )
endif
                mov eax,[esi].opnd[ebx].InsFixup
                .if eax == NULL
                    mov rm_field,RM_SIB   ;; 64-bit non-RIP direct addressing
                    mov [esi].sib,0x25    ;; IIIBBB, base=101b, index=100b
                .elseif [eax].fixup.type == FIX_OFF32
                    ;; added v2.26
                    mov [eax].fixup.type,FIX_RELOFF32
                .endif
ifndef ASMC64
            .endif
        .endif
endif
    .elseif index == EMPTY && base != EMPTY

        ;; for SI, DI and BX: default is DS:[],
        ;; DS: segment override is not needed
        ;; for BP: default is SS:[], SS: segment override is not needed

        .switch base
        .case T_SI
            mov rm_field,RM_SI ;; 4
            .endc
        .case T_DI
            mov rm_field,RM_DI ;; 5
            .endc
        .case T_BP
            mov rm_field,RM_BP ;; 6
            .if mod_field == MOD_00 && base != T_RIP
                mov mod_field,MOD_01
            .endif
            .endc
        .case T_BX
            mov rm_field,RM_BX ;; 7
            .endc
        .default ;; for 386 and up
            mov base_reg,5
            .if base != T_RIP
                mov base_reg,GetRegNo(base)
            .endif
            mov al,base_reg
            shr al,3
            mov bit3_base,al
            and base_reg,BIT_012
            mov rm_field,base_reg
            .if base_reg == 4
                ;; 4 is RSP/ESP or R12/R12D, which must use SIB encoding.
                ;; SSIIIBBB, ss = 00, index = 100b ( no index ), base = 100b ( ESP )
                mov [esi].sib,0x24
            .elseif base_reg == 5 && mod_field == MOD_00 && base != T_RIP
                ;; 5 is [E|R]BP or R13[D]. Needs displacement
                mov mod_field,MOD_01
            .endif
            mov rex,bit3_base ;; set REX_R
        .endsw
        seg_override(esi, base, sym, FALSE)
    .elseif index != EMPTY && base == EMPTY
        mov idx_reg,GetRegNo(index)
        mov al,idx_reg
        shr al,3
        mov bit3_idx,al
        and idx_reg,BIT_012
        ;; mod field is 00
        mov mod_field,MOD_00
        ;; s-i-b is present ( r/m = 100b )
        mov rm_field,RM_SIB
        ;; scale factor, index, base ( 0x05 => no base reg )

        mov al,idx_reg
        shl al,3
        or  al,s
        or  al,0x05
        mov [esi].sib,al
        mov al,bit3_idx
        shl al,1
        mov rex,al ;; set REX_X
        ;; default is DS:[], DS: segment override is not needed
        seg_override(esi, T_DS, sym, FALSE)
        mov eax,[esi].pinstr
        .if [eax].instr_item.evex & VX_XMMI
            mov [esi].opc_or,GetRegNo(index)
            .if GetValueSp(index) > 16
                or [esi].opc_or,0x40 ;; YMM/ZMM
            .endif
        .endif

    .else ;; base != EMPTY && index != EMPTY

        mov base_reg,5
        .if base != T_RIP
            mov base_reg,GetRegNo(base)
        .endif
        mov idx_reg,GetRegNo(index)
        mov al,base_reg
        shr al,3
        mov bit3_base,al
        mov al,idx_reg
        shr al,3
        mov bit3_idx,al
        and base_reg,BIT_012
        mov ecx,GetSflagsSp(base)
        and ecx,GetSflagsSp(index)
        and ecx,SFR_SIZMSK

        .if ecx == 0
            mov ecx,[esi].pinstr
            .if GetValueSp(index) > 8 && [ecx].instr_item.evex & VX_XMMI
                mov [esi].opc_or,idx_reg
                .if GetValueSp(index) > 16
                    or [esi].opc_or,0x40 ;; YMM/ZMM
                .endif
            .else
                .return( asmerr( 2082 ) )
            .endif
        .endif
        and idx_reg,BIT_012

        .switch index
        .case T_BX
        .case T_BP
            .return .if comp_mem16( index, base ) == ERROR
            mov rm_field,al
            seg_override( esi, index, sym, FALSE )
            .endc
        .case T_SI
        .case T_DI
            .return .if comp_mem16( base, index ) == ERROR
            mov rm_field,al
            seg_override( esi, base, sym, FALSE )
            .endc
        .case T_RSP
        .case T_RIP
        .case T_ESP
            .return( asmerr( 2032 ) )
        .default
            .if base_reg == 5 && base != T_RIP ;; v2.03: EBP/RBP/R13/R13D?
                .if mod_field == MOD_00
                    mov mod_field,MOD_01
                .endif
            .endif
            ;; s-i-b is present ( r/m = 100b )
            or  rm_field,RM_SIB
            mov al,idx_reg
            shl al,3
            or  al,s
            or  al,base_reg
            mov [esi].sib,al
            mov al,bit3_idx
            shl al,1
            add al,bit3_base
            mov rex,al ;; set REX_X + REX_B
            seg_override( esi, base, sym, FALSE )
        .endsw ;; end switch(index)
    .endif

    .if base == T_RIP
        and mod_field,BIT_012
    .endif
    .if CurrOpnd == OPND2
        ;; shift the register field to left by 3 bit
        mov al,rm_field
        shl al,3
        mov cl,[esi].rm_byte
        and cl,BIT_012
        or  al,mod_field
        or  al,cl
        mov [esi].rm_byte,al
        mov al,rex
        mov cl,al
        mov dl,al
        shr al,2
        and cl,REX_X
        and dl,1
        shl dl,2
        or al,cl
        or al,dl
        or [esi].rex,al
    .elseif CurrOpnd == OPND1
        mov al,mod_field
        or  al,rm_field
        mov [esi].rm_byte,al
        or [esi].rex,rex
    .endif
    mov eax,NOT_ERROR
    ret

set_rm_sib endp

;; override handling
;; called by
;; - process_branch()
;; - idata_fixup()
;; - memory_operand() (CodeInfo != NULL)
;; - data_item()
;; 1. If it's a segment register, set CodeInfo->RegOverride.
;; 2. Set global variable SegOverride if it's a SEG/GRP symbol
;;    (or whatever is assumed for the segment register)

    assume edi:token_t

segm_override proc uses esi edi ebx opndx:expr_t, CodeInfo:ptr code_info

    mov esi,CodeInfo
    mov edx,opndx
    mov edi,[edx].expr.override
    .if edi
        .if [edi].token == T_REG

            movzx ebx,GetRegNo([edi].tokval)
            .return asmerr(2108) .if SegAssumeTable[ebx*8].error

            ;; ES,CS,SS and DS overrides are invalid in 64-bit
            .return asmerr(2202) .if esi && [esi].Ofssize == USE64 && ebx < ASSUME_FS

            GetOverrideAssume(ebx)
            .if esi
                ;; hack: save the previous reg override value (needed for CMPS)
                mov ecx,[esi].RegOverride
                mov LastRegOverride,ecx
                mov [esi].RegOverride,ebx
            .endif
        .else
            SymSearch([edi].string_ptr)
        .endif
        .if eax && ( [eax].asym.state == SYM_GRP || [eax].asym.state == SYM_SEG )
            mov SegOverride,eax
        .endif
    .endif
    mov eax,NOT_ERROR
    ret

segm_override endp

;; get an immediate operand without a fixup.
;; output:
;; - ERROR: error
;; - NOT_ERROR: ok,
;;   CodeInfo->opnd_type[CurrOpnd] = OP_Ix
;;   CodeInfo->data[CurrOpnd]      = value
;;   CodeInfo->opsiz
;;   CodeInfo->iswide

    assume edi:expr_t

idata_nofixup proc private uses esi edi ebx CodeInfo:ptr code_info, CurrOpnd:uint_t, opndx:expr_t

    local op_type:int_t
    local value:int_t
    local size:int_t

    mov esi,CodeInfo
    mov edi,opndx
    mov ebx,CurrOpnd
    shl ebx,4
    mov size,0

    ;; jmp/call/jxx/loop/jcxz/jecxz?
    .if IS_ANY_BRANCH( [esi].token )
        .return( process_branch( esi, CurrOpnd, opndx ) )
    .endif

    .if [edi].mem_type == MT_REAL16

        mov eax,4
        movzx ecx,[esi].token
        .switch ecx
        .case T_ADDSD
        .case T_SUBSD
        .case T_MULSD
        .case T_DIVSD
        .case T_MOVSD
        .case T_MOVQ
        .case T_COMISD
        .case T_UCOMISD
            mov eax,8
            mov size,8
            .endc
        .case T_MOV
            .if CurrOpnd == OPND2
                .if [esi].Ofssize == USE64 && ( [esi].opnd[OPND1].type & OP_R64 )
                    mov eax,8
                .elseif [esi].opnd[OPND1].type & OP_R16
                    mov eax,2
                .endif
            .endif
        .endsw
        quad_resize(edi, eax)
    .endif

    mov value,[edi].value
    mov [esi].opnd[ebx].data32l,eax

    ;; 64bit immediates are restricted to MOV <reg>,<imm64>
    .if dword ptr [edi].hlvalue || dword ptr [edi].hlvalue[4] ;; magnitude > 64 bits?
        .return EmitConstError(edi)
    .endif
    ;; v2.03: handle QWORD type coercion here as well!
    ;; This change also reveals an old problem in the expression evaluator:
    ;; the mem_type field is set whenever a (simple) type token is found.
    ;; It should be set ONLY when the type is used in conjuction with the
    ;; PTR operator!
    ;; current workaround: query the 'explicit' flag.

    ;; use long format of MOV for 64-bit if value won't fit in a signed DWORD

    xor ecx,ecx
    mov edx,[edi].hvalue
    cmp edx,ecx
    setg cl
    .ifz
        cmp eax,LONG_MAX
        seta cl
    .endif
    cmp edx,-1
    setl ch
    .ifz
        cmp eax,LONG_MIN
        setb ch
    .endif

    .if ( size || [esi].Ofssize == USE64 && [esi].token == T_MOV && CurrOpnd == OPND2 && \
          [esi].opnd[OPND1].type & OP_R64 && ( ecx || \
          ( [edi].flags & E_EXPLICIT && ( [edi].mem_type == MT_QWORD || [edi].mem_type == MT_SQWORD ) ) ) )

        ;; CodeInfo->iswide = 1; ;; has been set by first operand already

        mov [esi].opnd[ebx].type,OP_I64
        mov [esi].opnd[ebx].data32h,edx
        .return NOT_ERROR
    .endif
    xor  ecx,ecx
    cmp  edx,-1
    setl cl
    .ifz
        test eax,eax
        setz cl
    .endif
    test edx,edx
    setg ch
    .if ( ecx )
        ; compare mem_float,imm_float64
        .if ( [esi].Ofssize >= USE32 && [esi].token == T_COMISD &&
              CurrOpnd == OPND2 && [esi].opnd[OPND1].type == OP_M64 )
            mov [esi].opnd[ebx].type,OP_I64
            mov [esi].opnd[ebx].data32h,edx
            .return NOT_ERROR
        .else
            .return EmitConstError(edi)
        .endif
    .endif

    ;; v2.06: code simplified.
    ;; to be fixed: the "wide" bit should not be set here!
    ;; Problem: the "wide" bit isn't set in memory_operand(),
    ;; probably because of the instructions which accept both
    ;; signed and unsigned arguments (ADD, CMP, ... ).


    .if [edi].flags & E_EXPLICIT
        ;; size coercion for immediate value
        or [esi].flags,CI_CONST_SIZE_FIXED
        ;; don't check if size and value are compatible.
        .switch SizeFromMemtype( [edi].mem_type, [edi].Ofssize, [edi].type )
        .case 1 : mov op_type,OP_I8  : .endc
        .case 2 : mov op_type,OP_I16 : .endc
        .case 4 : mov op_type,OP_I32 : .endc
        .case 8 ;; v2.27: handle asin(0.0) in 64-bit
            .if [esi].Ofssize == USE64 && [edi].mem_type == MT_REAL8 && value == 0 && [edi].hvalue == 0
                mov op_type,OP_I64
                mov [esi].opnd[ebx].data32h,0
                .endc
            .endif
        .default
            .return asmerr(2070)
        .endsw
    .else
        ;; use true signed values for BYTE only!
        movsx eax,byte ptr value
        .if eax == value
            mov op_type,OP_I8
        .elseif value <= USHRT_MAX && value >= 0 - USHRT_MAX
            mov op_type,OP_I16
        .else
            mov op_type,OP_I32
        .endif
    .endif

    .switch [esi].token
    .case T_PUSH
        .if !( [edi].flags & E_EXPLICIT )
            .if [esi].Ofssize > USE16 && op_type == OP_I16
                mov op_type,OP_I32
            .endif
        .endif
        .if op_type == OP_I16
            mov [esi].opsiz,OPSIZE16(esi)
        .elseif op_type == OP_I32
            mov [esi].opsiz,OPSIZE32(esi)
        .endif
        .endc
    .case T_PUSHW
        .if op_type != OP_I32
            mov op_type,OP_I16
            movsx eax,byte ptr value
            movsx ecx,word ptr value
            .if eax == ecx
                mov op_type,OP_I8
            .endif
        .endif
        .endc
    .case T_PUSHD
        .if op_type == OP_I16
            mov op_type,OP_I32
        .endif
        .endc
    .endsw

    ;; v2.11: set the wide-bit if a mem_type size of > BYTE is set???
    ;; actually, it should only be set if immediate is second operand
    ;; ( and first operand is a memory ref with a size > 1 )

    .if ( CurrOpnd == OPND2 )
        .if ( !([esi].mem_type & MT_SPECIAL) && ( [esi].mem_type & MT_SIZE_MASK ) )
            or [esi].flags,CI_ISWIDE
        .endif
    .endif
    mov [esi].opnd[ebx].type,op_type
    mov eax,NOT_ERROR
    ret

idata_nofixup endp

;; get an immediate operand with a fixup.
;; output:
;; - ERROR: error
;; - NOT_ERROR: ok,
;;   CodeInfo->opnd_type[CurrOpnd] = OP_Ix
;;   CodeInfo->data[CurrOpnd]      = value
;;   CodeInfo->InsFixup[CurrOpnd]  = fixup
;;   CodeInfo->mem_type
;;   CodeInfo->opsiz
;; to be fixed: don't modify CodeInfo->mem_type here!

idata_fixup proc uses esi edi ebx CodeInfo:ptr code_info, CurrOpnd:uint_t, opndx:expr_t

    local fixup_type:int_t
    local fixup_option:int_t
    local size:int_t
    local Ofssize:byte ; 1=32bit, 0=16bit offset for fixup

    mov fixup_option,OPTJ_NONE

    mov esi,CodeInfo
    mov edi,opndx
    mov ebx,CurrOpnd
    shl ebx,4

    ;; jmp/call/jcc/loopcc/jxcxz?
    .if IS_ANY_BRANCH( [esi].token )
        .return process_branch( esi, CurrOpnd, edi )
    .endif
    mov [esi].opnd[ebx].data32l,[edi].value
    mov ecx,[edi].sym

    .if [edi].Ofssize != USE_EMPTY
        mov Ofssize,[edi].Ofssize
    .elseif [ecx].asym.state == SYM_SEG || [ecx].asym.state == SYM_GRP || [edi].inst == T_SEG
        mov Ofssize,USE16
    .elseif [edi].flags & E_IS_ABS ;; an (external) absolute symbol?
        mov Ofssize,USE16
    .else
        mov Ofssize,GetSymOfssize(ecx)
    .endif
    ;; short works for branch instructions only
    .return asmerr(2070) .if [edi].inst == T_SHORT

    ;; the code below should be rewritten.
    ;; - an address operator ( OFFSET, LROFFSET, IMAGEREL, SECTIONREL,
    ;;   LOW, HIGH, LOWWORD, HIGHWORD, LOW32, HIGH32, SEG ) should not
    ;;   force a magnitude, but may set a minimal magnitude - and the
    ;;   fixup type, of course.
    ;; - check if Codeinfo->mem_type really has to be set here!

    .if ( [edi].flags & E_EXPLICIT ) && !( [edi].flags & E_IS_ABS )
        or [esi].flags,CI_CONST_SIZE_FIXED
        .if [esi].mem_type == MT_EMPTY
            mov [esi].mem_type,[edi].mem_type
        .endif
    .endif
    .if [esi].mem_type == MT_EMPTY && CurrOpnd > OPND1 && [edi].Ofssize == USE_EMPTY
        OperandSize( [esi].opnd[OPND1].type, esi )
        ;; may be a forward reference, so wait till pass 2
        .if Parse_Pass > PASS_1 && [edi].inst != EMPTY

            mov ecx,[edi].inst
            .switch ecx
            .case T_SEG ;; v2.04a: added
                .return asmerr(2022, eax, 2) .if eax && eax < 2
                .endc
            .case T_OFFSET
            .case T_LROFFSET
            .case T_IMAGEREL
            .case T_SECTIONREL
                .if eax && (eax < 2 || ( Ofssize && eax < 4 ))
                    movzx ecx,Ofssize
                    mov edx,2
                    shl edx,cl
                    .return asmerr(2022, eax, edx)
                .endif
            .endsw
        .endif
        .switch eax
        .case 1
            .if [edi].flags & E_IS_ABS || [edi].inst == T_DOT_LOW || [edi].inst == T_DOT_HIGH
                mov [esi].mem_type,MT_BYTE
            .endif
            .endc
        .case 2
            .if [edi].flags & E_IS_ABS || [esi].Ofssize == USE16 ||\
                [edi].inst == T_LOWWORD || [edi].inst == T_HIGHWORD
                mov [esi].mem_type,MT_WORD
            .endif
            .endc
        .case 4
            mov [esi].mem_type,MT_DWORD
            .endc
        .case 8
            .if Ofssize == USE64
                .if [edi].inst == T_LOW64 || [edi].inst == T_HIGH64 || \
                    ( [esi].token == T_MOV && ( [esi].opnd[OPND1].type & OP_R64 ) )
                    mov [esi].mem_type,MT_QWORD
                .elseif [edi].inst == T_LOW32 || [edi].inst == T_HIGH32
                    ;; v2.10:added; LOW32/HIGH32 in expreval.c won't set mem_type anymore.
                    mov [esi].mem_type,MT_DWORD
                .endif
            .endif
            .endc
        .endsw
    .endif
    .if [esi].mem_type == MT_EMPTY
        .if [edi].flags & E_IS_ABS
            .if [edi].mem_type != MT_EMPTY
                mov [esi].mem_type,[edi].mem_type
            .elseif [esi].token == T_PUSHW  ;; v2.10: special handling PUSHW
                mov [esi].mem_type,MT_WORD
            .else
                mov ecx,MT_WORD
                .if IS_OPER_32(esi)
                    mov ecx,MT_DWORD
                .endif
                mov [esi].mem_type,cl
            .endif
        .else
            movzx eax,[esi].token
            .switch eax
            .case T_PUSHW
            .case T_PUSHD
            .case T_PUSH
                .if [edi].mem_type == MT_EMPTY
                    mov eax,[edi].inst
                    .switch eax
                    .case EMPTY
                    .case T_DOT_LOW
                    .case T_DOT_HIGH
                        mov [edi].mem_type,MT_BYTE
                        .endc
                    .case T_LOW32 ;; v2.10: added - low32_op() doesn't set mem_type anymore.
                    .case T_IMAGEREL
                    .case T_SECTIONREL
                        mov [edi].mem_type,MT_DWORD
                        .endc
                    .endsw
                .endif
                ;; default: push offset only
                ;; for PUSH + undefined symbol, assume BYTE
                .if [edi].mem_type == MT_FAR && !( [edi].flags & E_EXPLICIT )
                    mov [edi].mem_type,MT_NEAR
                .endif
                ;; v2.04: curly brackets added
                .if [esi].token == T_PUSHW
                    .if SizeFromMemtype( [edi].mem_type, Ofssize, [edi].type ) < 2
                        mov [edi].mem_type,MT_WORD
                    .endif
                .elseif [esi].token == T_PUSHD
                    .if SizeFromMemtype( [edi].mem_type, Ofssize, [edi].type ) < 4
                        mov [edi].mem_type,MT_DWORD
                    .endif
                .endif
                .endc
            .endsw
            ;; if a WORD size is given, don't override it with
            ;; anything what might look better at first glance
            mov ecx,[edi].sym
            .if [edi].mem_type != MT_EMPTY
                mov [esi].mem_type,[edi].mem_type
            ;; v2.04: assume BYTE size if symbol is undefined
            .elseif [ecx].asym.state == SYM_UNDEFINED
                mov [esi].mem_type,MT_BYTE
                mov fixup_option,OPTJ_PUSH
            .else
                ;; v2.06d: changed
                mov eax,MT_WORD
                .if Ofssize == USE64
                    mov eax,MT_QWORD
                .elseif Ofssize == USE32
                    mov eax,MT_DWORD
                .endif
                mov [esi].mem_type,al
            .endif
        .endif
    .endif

    mov size,SizeFromMemtype( [esi].mem_type, Ofssize, NULL )
    .switch eax
    .case 1
        mov [esi].opnd[ebx].type,OP_I8
        mov [esi].opsiz,FALSE ;; v2.10: reset opsize is not really a good idea - might have been set by previous operand
        .endc
    .case 2: mov [esi].opnd[ebx].type,OP_I16 : mov [esi].opsiz,OPSIZE16(esi) : .endc
    .case 4: mov [esi].opnd[ebx].type,OP_I32 : mov [esi].opsiz,OPSIZE32(esi) : .endc
    .case 8
        ;; v2.05: do only assume size 8 if the constant won't fit in 4 bytes.
        mov al,[edi].mem_type
        and eax,MT_SIZE_MASK
        xor ecx,ecx
        mov edx,[edi].hvalue
        .if edx == ecx
            cmp [edi].value,LONG_MAX
        .endif
        setg cl
        .if edx == -1
            cmp [edi].value,LONG_MIN
        .endif
        setl ch
        .if ecx || ( [edi].flags & E_EXPLICIT && eax == 7 )

            mov [esi].opnd[ebx].type,OP_I64
            mov [esi].opnd[ebx].data32h,[edi].hvalue
        .elseif Ofssize == USE64 && ( [edi].inst == T_OFFSET || ( [esi].token == T_MOV && ( [esi].opnd[OPND1].type & OP_R64 ) ) )
            ;; v2.06d: in 64-bit, ALWAYS set OP_I64, so "mov m64, ofs" will fail,
            ;; This was accepted in v2.05-v2.06c)

            mov [esi].opnd[ebx].type,OP_I64
            mov [esi].opnd[ebx].data32h,[edi].hvalue
        .else
            mov [esi].opnd[ebx].type,OP_I32
        .endif
        mov [esi].opsiz,OPSIZE32(esi)
        .endc
    .endsw

    ;; set fixup_type

    .if [edi].inst == T_SEG
        mov fixup_type,FIX_SEG
    .elseif [esi].mem_type == MT_BYTE
        .if [edi].inst == T_DOT_HIGH
            mov fixup_type,FIX_HIBYTE
        .else
            mov fixup_type,FIX_OFF8
        .endif
    .elseif IS_OPER_32(esi)
        .if [esi].opnd[ebx].type == OP_I64 && ( [edi].inst == EMPTY || [edi].inst == T_OFFSET )
            mov fixup_type,FIX_OFF64
        .else
            .if size >= 4 && [edi].inst != T_LOWWORD

                ;; v2.06: added branch for PTR16 fixup.
                ;; it's only done if type coercion is FAR (Masm-compat)

                .if [edi].flags & E_EXPLICIT && Ofssize == USE16 && [edi].mem_type == MT_FAR
                    mov fixup_type,FIX_PTR16
                .else
                    mov fixup_type,FIX_OFF32
                .endif
            .else
                mov fixup_type,FIX_OFF16
            .endif
        .endif
    .else
        mov fixup_type,FIX_OFF16
    .endif
    ;; v2.04: 'if' added, don't set W bit if size == 1
    ;; code example:
    ;;   extern x:byte
    ;;   or al,x
    ;; v2.11: set wide bit only if immediate is second operand.
    ;; and first operand is a memory reference with size > 1

    .if CurrOpnd == OPND2 && size != 1
        or [esi].flags,CI_ISWIDE
    .endif
    segm_override(edi, NULL) ;; set SegOverride global var

    ;; set frame type in variables Frame_Type and Frame_Datum for fixup creation
    .if ModuleInfo.offsettype == OT_SEGMENT && ( [edi].inst == T_OFFSET || [edi].inst == T_SEG )
        set_frame2([edi].sym)
    .else
        set_frame([edi].sym)
    .endif
    mov [esi].opnd[ebx].InsFixup,CreateFixup( [edi].sym, fixup_type, fixup_option )
    .if [edi].inst == T_LROFFSET
        or [eax].fixup.fx_flag,FX_LOADER_RESOLVED
    .endif
    .if [edi].inst == T_IMAGEREL && fixup_type == FIX_OFF32
        mov [eax].fixup.type,FIX_OFF32_IMGREL
    .endif
    .if [edi].inst == T_SECTIONREL && fixup_type == FIX_OFF32
        mov [eax].fixup.type,FIX_OFF32_SECREL
    .endif
    mov eax,NOT_ERROR
    ret

idata_fixup endp

;; convert MT_PTR to MT_WORD, MT_DWORD, MT_FWORD, MT_QWORD.
;; MT_PTR cannot be set explicitely (by the PTR operator),
;; so this value must come from a label or a structure field.
;; (above comment is most likely plain wrong, see 'PF16 ptr [reg]'!
;; This code needs cleanup!

SetPtrMemtype proc private uses esi edi CodeInfo:ptr code_info, opndx:expr_t

  local sym:asym_t
  local size:int_t

    mov esi,CodeInfo
    mov edi,opndx
    mov size,0
    mov sym,[edi].sym

    .if [edi].mbr  ;; the mbr field has higher priority
        mov sym,[edi].mbr
    .endif

    .if [edi].flags & E_EXPLICIT && [edi].type
        mov ecx,[edi].type
        mov size,[ecx].asym.total_size
        .if [ecx].asym.is_far
            or [esi].flags,CI_ISFAR
        .else
            and [esi].flags,not CI_ISFAR
        .endif
    .elseif eax

        .if [eax].asym.type

            mov ecx,[eax].asym.type
            mov size,[ecx].asym.total_size
            .if [ecx].asym.is_far
                or [esi].flags,CI_ISFAR
            .else
                and [esi].flags,not CI_ISFAR
            .endif
            ;; there's an ambiguity with pointers of size DWORD,
            ;; since they can be either NEAR32 or FAR16
            mov al,[ecx].asym.Ofssize
            .if size == 4 && al != [esi].Ofssize
                mov [edi].Ofssize,al
            .endif
        .elseif [eax].asym.mem_type == MT_PTR

            mov ecx,MT_NEAR
            .if [eax].asym.is_far
                mov ecx,MT_FAR
            .endif
            mov size,SizeFromMemtype( cl, [eax].asym.Ofssize, NULL )
            mov ecx,sym
            and [esi].flags,not CI_ISFAR
            .if [ecx].asym.is_far
                or [esi].flags,CI_ISFAR
            .endif
        .else
            .if [eax].asym.flag1 & S_ISARRAY
                mov ecx,[eax].asym.total_length
                mov eax,[eax].asym.total_size
                xor edx,edx
                div ecx
                mov size,eax
            .else
                mov size,[eax].asym.total_size
            .endif
        .endif
    .else
        mov cl,ModuleInfo._model
        mov eax,1
        shl eax,cl
        .if cl & SIZE_DATAPTR
            mov size,2
        .endif
        mov cl,ModuleInfo.defOfssize
        mov eax,2
        shl eax,cl
        add size,eax
    .endif
    .if size
        MemtypeFromSize( size, &[edi].mem_type )
    .endif
    ret

SetPtrMemtype endp


;; set fields in CodeInfo:
;; - mem_type
;; - prefix.opsiz
;; - prefix.rex REX_W
;; called by memory_operand()

    assume ebx:ptr instr_item

Set_Memtype proc private uses esi edi ebx CodeInfo:ptr code_info, mem_type:uchar_t

    mov esi,CodeInfo
    .return .if [esi].token == T_LEA

    ;; v2.05: changed. Set "data" types only.

    movzx eax,mem_type
    .return .if al == MT_EMPTY || al == MT_TYPE || al == MT_NEAR || al == MT_FAR

    mov [esi].mem_type,al
    mov ebx,[esi].pinstr

    .if [esi].Ofssize > USE16

        ;; if we are in use32 mode, we have to add OPSIZ prefix for
        ;; most of the 386 instructions when operand has type WORD.
        ;; Exceptions ( MOVSX and MOVZX ) are handled in check_size().

        .if IS_MEM_TYPE( al, WORD )
            mov [esi].opsiz,TRUE

        ;; set rex Wide bit if a QWORD operand is found (not for FPU/MMX/SSE instr).
        ;; This looks pretty hackish now and is to be cleaned!
        ;; v2.01: also had issues with SSE2 MOVSD/CMPSD, now fixed!

        ;; v2.06: with AVX, SSE tokens may exist twice, one
        ;; for "legacy", the other for VEX encoding!

        .elseif IS_MEMTYPE_SIZ( al, QWORD )

            movzx eax,[esi].token
            .switch eax
            .case T_PUSH ;; for PUSH/POP, REX_W isn't needed (no 32-bit variants in 64-bit mode)
            .case T_POP
            .case T_CMPXCHG8B
            .case T_VMPTRLD
            .case T_VMPTRST
            .case T_VMCLEAR
            .case T_VMXON
                .endc
            .default
                ;; don't set REX for opcodes that accept memory operands
                ;; of any size.
                movzx eax,[ebx].opclsidx
                imul  eax,eax,opnd_class

                .endc .if opnd_clstab[eax].opnd_type[OPND1] == OP_M_ANY
                ;; don't set REX for FPU opcodes
                .endc .if ( [ebx].cpu & P_FPU_MASK )
                ;; don't set REX for - most - MMX/SSE opcodes
                .if [ebx].cpu & P_EXT_MASK
                    movzx eax,[esi].token
                    .switch eax

                        ;; [V]CMPSD and [V]MOVSD are also candidates,
                        ;; but currently they are handled in HandleStringInstructions()

                    .case T_CVTSI2SD ;; v2.06: added
                    .case T_CVTSI2SS ;; v2.06: added
                    .case T_PEXTRQ   ;; v2.06: added
                    .case T_PINSRQ   ;; v2.06: added
                    .case T_MOVD
                    .case T_VCVTSI2SD
                    .case T_VCVTSI2SS
                    .case T_VPEXTRQ
                    .case T_VPINSRQ
                    .case T_VMOVD
                        or [esi].rex,REX_W
                        .endc
                    .endsw
                .else
                    or [esi].rex,REX_W
                .endif
            .endsw
        .endif
    .else
        .if IS_MEMTYPE_SIZ( al, DWORD )

            ;; in 16bit mode, a DWORD memory access usually requires an OPSIZ
            ;; prefix. A few instructions, which access m16:16 operands,
            ;; are exceptions.

            movzx eax,[esi].token
            .switch eax
            .case T_LDS
            .case T_LES
            .case T_LFS
            .case T_LGS
            .case T_LSS
            .case T_CALL ;; v2.0: added
            .case T_JMP  ;; v2.0: added
                ;; in these cases, opsize does NOT need to be changed
                .endc
            .default
                mov [esi].opsiz,TRUE
                .endc
            .endsw

        ;; v2.06: added because in v2.05, 64-bit memory operands were
        ;; accepted in 16-bit code

        .elseif IS_MEMTYPE_SIZ( mem_type, QWORD )

            movzx eax,[ebx].opclsidx
            imul  eax,eax,opnd_class

            .if opnd_clstab[eax].opnd_type[OPND1] == OP_M_ANY

            .elseif [ebx].cpu & ( P_FPU_MASK or P_EXT_MASK )

            .elseif [esi].token != T_CMPXCHG8B
                ;; setting REX.W will cause an error in codegen
                or [esi].rex,REX_W
            .endif
        .endif
    .endif
    ret

Set_Memtype endp


;; process direct or indirect memory operand
;; in: opndx=operand to process
;; in: CurrOpnd=no of operand (0=first operand,1=second operand)
;; out: CodeInfo->data[]
;; out: CodeInfo->opnd_type[]

    assume ebx:nothing

memory_operand proc private uses esi edi ebx CodeInfo:ptr code_info,
    CurrOpnd:uint_t, opndx:expr_t, with_fixup:int_t

    local sym:asym_t
    local index:int_t
    local base:int_t
    local fixup_type:int_t
    local j:int_t
    local mem_type:byte
    local Ofssize:byte
    local s:char_t

    mov s,SCALE_FACTOR_1

    mov esi,CodeInfo
    mov edi,opndx
    mov ebx,CurrOpnd
    shl ebx,4

    ;; v211: use full 64-bit value
    mov [esi].opnd[ebx].data32l,[edi].value
    mov [esi].opnd[ebx].data32h,[edi].hvalue
    mov [esi].opnd[ebx].type,OP_M
    mov sym,[edi].sym

    segm_override(edi, esi)

    mov al,[edi].mem_type
    mov ah,al
    and ah,MT_SPECIAL_MASK
    .if al == MT_PTR
        SetPtrMemtype(esi, edi)
    .elseif ah == MT_ADDRESS
        .if [edi].Ofssize == USE_EMPTY && sym
            mov [edi].Ofssize,GetSymOfssize(sym)
        .endif
        mov ecx,SizeFromMemtype([edi].mem_type, [edi].Ofssize, [edi].type)
        MemtypeFromSize(ecx, &[edi].mem_type)
    .endif

    Set_Memtype(esi, [edi].mem_type)
    mov ecx,[edi].mbr
    .if ecx != NULL
        .if [ecx].asym.mem_type == MT_TYPE && [edi].mem_type == MT_EMPTY
            .if MemtypeFromSize([ecx].asym.total_size, &mem_type) == NOT_ERROR
                Set_Memtype(esi, mem_type)
            .endif
        .endif
        mov ecx,[edi].mbr
        .if [ecx].asym.state == SYM_UNDEFINED
            or [esi].flags,CI_UNDEF_SYM
        .endif
    .endif

    ;; instruction-specific handling
    .switch [esi].token
    .case T_JMP
    .case T_CALL
        ;; the 2 branch instructions are peculiar because they
        ;; will work with an unsized label.

        ;; v1.95: convert MT_NEAR/MT_FAR and display error if no type.
        ;; For memory operands, expressions of type MT_NEAR/MT_FAR are
        ;; call [bx+<code_label>]

        .if [esi].mem_type == MT_EMPTY
            ;; with -Zm, no size needed for indirect CALL/JMP
            .if ModuleInfo.m510 == FALSE && \
                Parse_Pass > PASS_1 && [edi].sym == NULL
                .return asmerr(2023)
            .endif
            mov eax,MT_WORD
            .if [esi].Ofssize == USE64
                mov eax,MT_QWORD
            .elseif[esi].Ofssize == USE32
                mov eax,MT_DWORD
            .endif
            mov [edi].mem_type,al
            Set_Memtype(esi, al)
        .endif

        SizeFromMemtype([esi].mem_type, [esi].Ofssize, NULL)
        .return asmerr(2024) \
        .if ( ( eax == 1 || eax > 6 ) && ( [esi].Ofssize != USE64 ) )
            ;; CALL/JMP possible for WORD/DWORD/FWORD memory operands only

        .if( [edi].mem_type == MT_FAR || [esi].mem_type == MT_FWORD || \
           ( [esi].mem_type == MT_TBYTE && [esi].Ofssize == USE64 ) || \
            ( [esi].mem_type == MT_DWORD && \
              (( [esi].Ofssize == USE16 && [edi].Ofssize != USE32 ) || \
               ( [esi].Ofssize == USE32 && [edi].Ofssize == USE16 ))))
            or [esi].flags,CI_ISFAR
        .endif
        .endc
    .endsw

    mov al,[esi].mem_type
    and eax,MT_SPECIAL
    .if eax == 0
        mov al,[esi].mem_type
        and eax,0x3F
        .if eax == MT_ZMMWORD
            mov [esi].opnd[ebx].type,OP_M512
        .else
            mov al,[esi].mem_type
            and eax,MT_SIZE_MASK
            mov ecx,[esi].opnd[ebx].type
            .switch eax ;; size is encoded 0-based
            .case  0: mov ecx,OP_M08 : .endc
            .case  1: mov ecx,OP_M16 : .endc
            .case  3: mov ecx,OP_M32 : .endc
            .case  5: mov ecx,OP_M48 : .endc
            .case  7: mov ecx,OP_M64 : .endc
            .case  9: mov ecx,OP_M80 : .endc
            .case 15: mov ecx,OP_M128: .endc
            .case 31: mov ecx,OP_M256: .endc
            .endsw
            mov [esi].opnd[ebx].type,ecx
        .endif
    .elseif [esi].mem_type == MT_EMPTY
        ;; v2.05: added
        movzx eax,[esi].token
        .switch eax
        .case T_INC
        .case T_DEC
            ;; jwasm v1.94-v2.04 accepted unsized operand for INC/DEC
            .return asmerr(2023) .if [edi].sym == NULL
            .endc
        .case T_PUSH
        .case T_POP
            .return asmerr(2070) .if [edi].mem_type == MT_TYPE
            .endc
        .endsw
    .endif

    mov eax,[edi].base_reg
    mov ecx,EMPTY
    .if eax
        mov ecx,[eax].asm_tok.tokval
    .endif
    mov base,ecx

    mov eax,[edi].idx_reg
    mov edx,EMPTY
    .if eax
        mov edx,[eax].asm_tok.tokval
    .endif
    mov index,edx

    ;; check for base registers

    .if ( ecx != EMPTY )

        mov eax,GetValueSp(ecx)
        mov cl,[esi].Ofssize

        .if ( ( ( eax & OP_R32 ) && cl == USE32 ) || \
              ( ( eax & OP_R64 ) && cl == USE64 ) || \
              ( ( eax & OP_R16 ) && cl == USE16 ) )
            mov [esi].adrsiz,FALSE
        .else
            mov [esi].adrsiz,TRUE
            ;; 16bit addressing modes don't exist in long mode
            .if ( ( eax & OP_R16 ) && cl == USE64 )
                .return( asmerr( 2085 ) )
            .endif
        .endif
    .endif

    ;; check for index registers

    .if ( index != EMPTY )

        mov eax,GetValueSp(index)
        mov cl,[esi].Ofssize

        .if ( ( ( eax & OP_R32) && cl == USE32 ) || \
              ( ( eax & OP_R64) && cl == USE64 ) || \
              ( ( eax & OP_R16) && cl == USE16 ) )
            mov [esi].adrsiz,FALSE
        .else
            mov [esi].adrsiz,TRUE
        .endif

        ;; v2.10: register swapping has been moved to expreval.asm, index_connect().
        ;; what has remained here is the check if R/ESP is used as index reg.

        mov eax,[esi].pinstr
        mov cl,[eax].instr_item.evex
        .if ( GetRegNo(index) == 4 && !( cl & VX_XMMI ))
            ;; [E|R]SP
            .if [edi].scale ;; no scale must be set
                asmerr(2031, GetResWName(index, NULL))
            .else
                asmerr(2029)
            .endif
            .return
        .endif

        ;; 32/64 bit indirect addressing?

        mov cl,[esi].Ofssize
        .if ( ( cl == USE16 && [esi].adrsiz == 1 ) || cl == USE64  || \
              ( cl == USE32 && [esi].adrsiz == 0 ) )

            mov eax,ModuleInfo.curr_cpu
            and eax,P_CPU_MASK
            .if eax >= P_386
                ;; scale, 0 or 1->00, 2->40, 4->80, 8->C0
                movzx eax,[edi].scale
                .switch eax
                .case 0
                .case 1: .endc                          ;; s = 00
                .case 2: mov s,SCALE_FACTOR_2: .endc   ;; s = 01
                .case 4: mov s,SCALE_FACTOR_4: .endc   ;; s = 10
                .case 8: mov s,SCALE_FACTOR_8: .endc   ;; s = 11
                .default ;; must be * 1, 2, 4 or 8
                    .return( asmerr( 2083 ) )
                .endsw
            .else
                ;; 286 and down cannot use this memory mode
                .return( asmerr( 2085 ) )
            .endif
        .else
            ;; v2.01: 16-bit addressing mode. No scale possible
            .return asmerr(2032) .if [edi].scale
        .endif
    .endif

    .if with_fixup

        .if [edi].flags & E_IS_ABS
            mov Ofssize,0
            .if IS_ADDR32(esi)
                inc Ofssize
            .endif
        .elseif sym
            mov Ofssize,GetSymOfssize(sym)
        .elseif SegOverride
            mov Ofssize,GetSymOfssize(SegOverride)
        .else
            mov Ofssize,[esi].Ofssize
        .endif

        ;; now set fixup_type.
        ;; for direct addressing, the fixup type can easily be set by
        ;; the symbol's offset size.

        .if base == EMPTY && index == EMPTY

            mov [esi].adrsiz,ADDRSIZE( [esi].Ofssize, Ofssize )
            .if Ofssize == USE64
                ;; v2.03: override with a segment assumed != FLAT?
                .if [edi].override && SegOverride != ModuleInfo.flat_grp
                    mov fixup_type,FIX_OFF32
                .else
                    mov fixup_type,FIX_RELOFF32
                .endif
            .else
                .if Ofssize
                    mov fixup_type,FIX_OFF32
                .else
                    mov fixup_type,FIX_OFF16
                .endif
            .endif
        .else

            xor eax,eax
            cmp [esi].Ofssize,al
            setz al

            .if Ofssize == USE64
                mov fixup_type,FIX_OFF32
            .else
                .if IS_ADDR32(esi) ;; address prefix needed?

                    ;; changed for v1.95. Probably more tests needed!
                    ;; test case:
                    ;;   mov eax,[ebx*2-10+offset var] ;code and var are 16bit!
                    ;; the old code usually works fine because HiWord of the
                    ;; symbol's offset is zero. However, if there's an additional
                    ;; displacement which makes the value stored at the location
                    ;; < 0, then the target's HiWord becomes <> 0.

                    mov fixup_type,FIX_OFF32
                .else
                    mov fixup_type,FIX_OFF16
                    .if Ofssize && Parse_Pass == PASS_2
                        ;; address size is 16bit but label is 32-bit.
                        ;; example: use a 16bit register as base in FLAT model:
                        ;;   test buff[di],cl
                        mov eax,sym
                        asmerr(8007, [eax].asym.name)
                    .endif
                .endif
            .endif
        .endif

        .if fixup_type == FIX_OFF32
            .if [edi].inst == T_IMAGEREL
                mov fixup_type,FIX_OFF32_IMGREL
            .elseif [edi].inst == T_SECTIONREL
                mov fixup_type,FIX_OFF32_SECREL
            .endif
        .endif
        ;; no fixups are needed for memory operands of string instructions and XLAT/XLATB.
        ;; However, CMPSD and MOVSD are also SSE2 opcodes, so the fixups must be generated
        ;; anyways.

        .if [esi].token != T_XLAT && [esi].token != T_XLATB
            CreateFixup(sym, fixup_type, OPTJ_NONE)
            mov [esi].opnd[ebx].InsFixup,eax
        .endif

    .endif
    .return .if set_rm_sib(esi, CurrOpnd, s, index, base, sym) == ERROR
    ;; set frame type/data in fixup if one was created
    mov ecx,[esi].opnd[ebx].InsFixup
    .if ecx
        mov [ecx].fixup.frame_type,Frame_Type
        mov [ecx].fixup.frame_datum,Frame_Datum
    .endif

    mov eax,NOT_ERROR
    ret

memory_operand endp

process_address proc private uses esi edi ebx CodeInfo:ptr code_info,
        CurrOpnd:uint_t, opndx:expr_t

;; parse the memory reference operand
;; CurrOpnd is 0 for first operand, 1 for second, ...
;; valid return values: NOT_ERROR, ERROR

    mov esi,CodeInfo
    mov edi,opndx
    mov ebx,CurrOpnd

    mov ecx,[edi].sym
    .if [edi].flags & E_INDIRECT ;; indirect register operand or stack var

        ;; if displacement doesn't fit in 32-bits:
        ;; Masm (both ML and ML64) just truncates.
        ;; JWasm throws an error in 64bit mode and
        ;; warns (level 3) in the other modes.
        ;; todo: this check should also be done for direct addressing!

        .if [edi].hvalue && ( [edi].hvalue != -1 || [edi].value >= 0 )
            .return EmitConstError(edi) .if ModuleInfo.Ofssize == USE64
            asmerr(8008, [edi].value64)
        .endif
        mov ecx,[edi].sym
        .if ecx == NULL || [ecx].asym.state == SYM_STACK
            .return memory_operand(esi, ebx, edi, FALSE)
        .endif
        ;; do default processing

    .elseif [edi].inst != EMPTY
        ;; instr is OFFSET | LROFFSET | SEG | LOW | LOWWORD, ...
        .if [edi].sym == NULL ;; better to check opndx->type?
            .return idata_nofixup(esi, ebx, edi)
        .else
            ;; allow "lea <reg>, [offset <sym>]"
            .if [esi].token == T_LEA && [edi].inst == T_OFFSET
                .return memory_operand(esi, ebx, edi, TRUE)
            .endif
            .return idata_fixup(esi, ebx, edi)
        .endif
    .elseif [edi].sym == NULL ;; direct operand without symbol
        .if [edi].override != NULL
            ;; direct absolute memory without symbol.
            ;; DS:[0] won't create a fixup, but
            ;; DGROUP:[0] will create one! */
            ;; for 64bit, always create a fixup, since RIP-relative addressing is used
            ;; v2.11: don't create fixup in 64-bit.
            mov ecx,[edi].override
            .if [ecx].asm_tok.token == T_REG || [esi].Ofssize == USE64
                .return memory_operand(esi, ebx, edi, FALSE)
            .else
                .return memory_operand(esi, ebx, edi, TRUE)
            .endif
        .else
            .return idata_nofixup(esi, ebx, edi)
        .endif
    .elseif [ecx].asym.state == SYM_UNDEFINED && !( [edi].flags & E_EXPLICIT )

        ;; undefined symbol, it's not possible to determine
        ;; operand type and size currently. However, for backpatching
        ;; a fixup should be created.

        ;; assume a code label for branch instructions!
        .if IS_ANY_BRANCH([esi].token)
            .return process_branch(esi, ebx, edi)
        .endif

        .switch [esi].token
        .case T_PUSH
        .case T_PUSHW
        .case T_PUSHD
            ;; v2.0: don't assume immediate operand if cpu is 8086
            mov eax,ModuleInfo.curr_cpu
            and eax,P_CPU_MASK
            .if eax > P_86
                .return idata_fixup(esi, ebx, edi)
            .endif
            .endc
        .default

            ;; v2.04: if operand is the second argument (and the first is NOT
            ;; a segment register!), scan the
            ;; instruction table if the instruction allows an immediate!
            ;; If so, assume the undefined symbol is a constant.
            mov eax,[esi].opnd[OPND1].type
            and eax,OP_SR
            .if ebx == OPND2 && eax == 0
                mov ecx,[esi].pinstr
                .repeat
                    movzx eax,[ecx].instr_item.opclsidx
                    imul eax,eax,opnd_class
                    .if opnd_clstab[eax].opnd_type[4] & OP_I
                        .return idata_fixup(esi, ebx, edi)
                    .endif
                    add ecx,instr_item
                .until [ecx].instr_item.flags & II_FIRST
            .endif
            ;; v2.10: if current operand is the third argument, always assume an immediate
            .if ebx == OPND3
                .return idata_fixup(esi, ebx, edi)
            .endif
        .endsw
        ;; do default processing

    .elseif [ecx].asym.state == SYM_SEG || [ecx].asym.state == SYM_GRP
        ;; SEGMENT and GROUP symbol is converted to SEG symbol
        ;; for next processing
        mov [edi].inst,T_SEG
        .return idata_fixup(esi, ebx, edi)
    .else
        ;; symbol external, but absolute?
        .if [edi].flags & E_IS_ABS
            .return idata_fixup(esi, ebx, edi)
        .endif

        ;; CODE location is converted to OFFSET symbol
        .if [edi].mem_type == MT_NEAR || [edi].mem_type == MT_FAR

            xor eax,eax ; v2.30 - mov mem,&proc
            mov ecx,[edi].type_tok
            .if ecx && [esi].Ofssize == USE64
                .if [ecx-16].asm_tok.token == '&'
                    inc eax
                .endif
            .endif
            .if eax || [esi].token == T_LEA || [edi].mbr != NULL ;; structure field?
                .return memory_operand(esi, ebx, edi, TRUE)
            .endif
            .return idata_fixup(esi, ebx, edi)
        .endif
    .endif
    ;; default processing: memory with fixup
    memory_operand(esi, ebx, edi, TRUE)
    ret

process_address endp

;; Handle constant operands.
;; These never need a fixup. Externals - even "absolute" ones -
;; are always labeled as EXPR_ADDR by the expression evaluator.

process_const proc private CodeInfo:ptr code_info, CurrOpnd:uint_t, opndx:expr_t

    ;; v2.11: don't accept an empty string

    mov edx,opndx
    .if [edx].expr.mem_type & MT_FLOAT
        mov [edx].expr.float_tok,NULL
    .endif
    mov eax,[edx].expr.quoted_string
    .return asmerr(2047) .if eax && [eax].asm_tok.stringlen == 0

    ;; optimization: skip <value> if it is 0 and instruction
    ;; is RET[W|D|N|F].
    ;; v2.06: moved here and checked the opcode directly, so
    ;; RETD and RETW are also handled.

    mov ecx,CodeInfo
    mov ecx,[ecx].code_info.pinstr
    mov al,[ecx].instr_item.opcode
    and eax,0xf7
    .return(NOT_ERROR) .if eax == 0xc2 && CurrOpnd == OPND1 && [edx].expr.value == 0
    idata_nofixup(CodeInfo, CurrOpnd, opndx)
    ret
process_const endp

process_register proc private uses esi edi ebx CodeInfo:ptr code_info, CurrOpnd:uint_t,
        opndx:expr_t, index:uint_t

;; parse and encode direct register operands. Modifies:
;; - CodeInfo->opnd_type
;; - CodeInfo->rm_byte (depending on CurrOpnd)
;; - CodeInfo->iswide
;; - CodeInfo->x86hi_used/x64lo_used
;; - CodeInfo->rex

    local regtok:int_t
    local regno:int_t
    local flags:uint_t

    mov esi,CodeInfo
    mov edi,opndx
    mov ebx,CurrOpnd
    shl ebx,4

    imul eax,CurrOpnd,expr
    mov eax,[edi+eax].base_reg
    mov regtok,[eax].asm_tok.tokval
    movzx eax,GetRegNo(eax)
    mov regno,eax
    ;; the register's "OP-flags" are stored in the 'value' field
    mov flags,GetValueSp(regtok)
    mov [esi].opnd[ebx].type,eax

    .if ( ( ( eax == OP_XMM || eax == OP_YMM ) && regno > 15 ) || eax & OP_ZMM )
        mov [esi].evex,1
        .if eax == OP_ZMM
            or [esi].vflags,VX_ZMM
        .endif
        .if regno > 15
            mov ecx,index
            mov edx,1
            shl edx,cl
            .if eax == OP_ZMM && regno > 23
                or edx,VX_ZMM24
            .endif
            or [esi].vflags,dl
        .elseif eax == OP_ZMM && regno > 7
            or [esi].vflags,VX_ZMM8
        .endif
    .endif

    .if eax & OP_R8
        ;; it's probably better to not reset the wide bit at all
        .if eax != OP_CL ;; problem: SHL AX|AL, CL
            and [esi].flags,not CI_ISWIDE
        .endif
        .if [esi].Ofssize == USE64 && regno >=4 && regno <= 7
            mov eax,regtok
            imul eax,eax,special_item
            .if SpecialTable[eax].cpu == P_86
                or [esi].flags,CI_X86HI_USED ;; it's AH,BH,CH,DH
            .else
                or [esi].flags,CI_x64LO_USED ;; it's SPL,BPL,SIL,DIL
            .endif
        .endif
        imul eax,regno,assume_info
        mov ecx,RL_ERROR
        .if regtok >= T_AH && regtok <= T_BH
            mov ecx,RH_ERROR
        .endif
        .return asmerr(2108) .if StdAssumeTable[eax].error & cl

    .elseif eax & OP_R ;; 16-, 32- or 64-bit GPR?
        or   [esi].flags,CI_ISWIDE
        imul ecx,regno,assume_info
        and  al,OP_R
        .return asmerr(2108) .if StdAssumeTable[ecx].error & al

        .if flags & OP_R16
            .if [esi].Ofssize > USE16
                mov [esi].opsiz,TRUE
            .endif
        .else
            .if [esi].Ofssize == USE16
                mov [esi].opsiz,TRUE
            .endif
        .endif
    .elseif eax & OP_SR
        .if regno == 1 ;; 1 is CS
            ;; POP CS is not allowed
            .return asmerr(2008, "POP CS") .if [esi].token == T_POP
        .endif
    .elseif eax & OP_ST

        imul eax,CurrOpnd,expr
        mov regno,[edi+eax].st_idx
        .return asmerr(2032) .if eax > 7 ;; v1.96: index check added
        or [esi].rm_byte,al
        .if eax != 0
            mov [esi].opnd[ebx].type,OP_ST_REG
        .endif
        ;; v2.06: exit, rm_byte is already set.
        .return NOT_ERROR

    .elseif eax & OP_RSPEC ;; CRx, DRx, TRx
        .if [esi].token != T_MOV
            .return asmerr(2151) .if [esi].token == T_PUSH
            .return asmerr(2070)
        .endif
        ;; v2.04: previously there were 3 flags, OP_CR, OP_DR and OP_TR.
        ;; this was summoned to one flag OP_RSPEC to free 2 flags, which
        ;; are needed if AVC ( new YMM registers ) is to be supported.
        ;; To distinguish between CR, DR and TR, the register number is
        ;; used now: CRx are numbers 0-F, DRx are numbers 0x10-0x1F and
        ;; TRx are 0x20-0x2F.

        .if regno >= 0x20 ;; TRx?
            or [esi].opc_or,0x04
            ;; TR3-TR5 are available on 486-586
            ;; TR6+TR7 are available on 386-586
            ;; v2.11: simplified.

            mov eax,ModuleInfo.curr_cpu
            and eax,P_CPU_MASK
            .if eax >= P_686
                mov eax,3
                .if regno > 0x25
                    mov eax,6
                .endif
                mov ecx,5
                .if regno > 0x25
                    mov ecx,7
                .endif
                .return asmerr(3004, eax, ecx)
            .endif
        .elseif regno >= 0x10 ;; DRx?
            or [esi].opc_or,0x01
        .endif
        and regno,0x0F
    .endif

    ;; if it's a x86-64 register (SIL, R8W, R8D, RSI, ...
    imul eax,regtok,special_item
    movzx eax,SpecialTable[eax].cpu
    and eax,P_CPU_MASK
    .if eax == P_64
        or [esi].rex,0x40
        .if flags & OP_R64
            or [esi].rex,REX_W
        .endif
    .endif

    .if CurrOpnd == OPND1
        ;; the first operand
        ;; r/m is treated as a 'reg' field
        mov eax,regno
        mov ecx,eax
        and eax,8
        shr eax,3
        or [esi].rex,al ;; set REX_B
        and ecx,BIT_012
        or  ecx,MOD_11
        ;; fill the r/m field
        or [esi].rm_byte,cl
    .else
        ;; the second operand
        ;; XCHG can use short form if op1 is AX/EAX/RAX
        .if( ( [esi].token == T_XCHG ) && ( [esi].opnd[OPND1].type & OP_A ) && \
             ( !([esi].opnd[OPND1].type & OP_R8 ) ) )
            mov eax,regno
            mov ecx,eax
            and eax,8
            shr eax,3
            or  [esi].rex,al ;; set REX_B
            and ecx,BIT_012
            and [esi].rm_byte,BIT_67
            or  [esi].rm_byte,cl
        .else
            ;; fill reg field with reg
            mov eax,regno
            mov ecx,eax
            and eax,8
            shr eax,1
            or  [esi].rex,al ;; set REX_R
            and ecx,BIT_012
            and [esi].rm_byte,not BIT_345
            shl ecx,3
            or  [esi].rm_byte,cl
        .endif
    .endif
    mov eax,NOT_ERROR
    ret
process_register endp


;; special handling for string instructions
;; CMPS[B|W|D|Q]
;;  INS[B|W|D]
;; LODS[B|W|D|Q]
;; MOVS[B|W|D|Q]
;; OUTS[B|W|D]
;; SCAS[B|W|D|Q]
;; STOS[B|W|D|Q]
;; the peculiarity is that these instructions ( optionally )
;; have memory operands, which aren't used for code generation
;; <opndx> contains the last operand.


HandleStringInstructions proc private uses esi edi ebx CodeInfo:ptr code_info, opndx:expr_t

  local opndidx:int_t
  local op_size:int_t

    mov opndidx,OPND1
    mov esi,CodeInfo
    mov edi,opndx

    movzx eax,[esi].token
    .switch eax
    .case T_VCMPSD
    .case T_CMPSD
        ;; filter SSE2 opcode CMPSD
        .if [esi].opnd[OPND1].type & (OP_XMM or OP_MMX)
            ;; v2.01: QWORD operand for CMPSD/MOVSD may have set REX_W!
            and [esi].rex,not REX_W
            .return
        .endif
        ;; fall through
    .case T_CMPS
    .case T_CMPSB
    .case T_CMPSW
    .case T_CMPSQ
         ;; cmps allows prefix for the first operand (=source) only
        .if [esi].RegOverride != EMPTY
            .if [edi+expr].override != NULL
                .if [esi].RegOverride == ASSUME_ES

                    ;; content of LastRegOverride is valid if
                    ;; CodeInfo->RegOverride is != EMPTY.

                    .if LastRegOverride == ASSUME_DS
                        mov [esi].RegOverride,EMPTY
                    .else
                        mov [esi].RegOverride,LastRegOverride
                    .endif
                .else
                    asmerr(2070)
                .endif
            .elseif [esi].RegOverride == ASSUME_DS
                ;; prefix for first operand?
                mov [esi].RegOverride,EMPTY
            .endif
        .endif
        .endc

    .case T_MOVSD
    .case T_VMOVSD
        ;; filter SSE2 opcode MOVSD
        .if [esi].opnd[OPND1].type & (OP_XMM or OP_MMX) || \
            [esi].opnd[OPNI2].type & (OP_XMM or OP_MMX)
            ;; v2.01: QWORD operand for CMPSD/MOVSD may have set REX_W!
            and [esi].rex,not REX_W
            .return
        .endif
        ;; fall through
    .case T_MOVS
    .case T_MOVSB
    .case T_MOVSW
    .case T_MOVSQ
        ;; movs allows prefix for the second operand (=source) only
        .if [esi].RegOverride != EMPTY
            .if [edi+expr].override == NULL
                asmerr(2070)
            .elseif [esi].RegOverride == ASSUME_DS
                mov [esi].RegOverride,EMPTY
            .endif
        .endif
        .endc
    .case T_OUTS
    .case T_OUTSB
    .case T_OUTSW
    .case T_OUTSD
        ;; v2.01: remove default DS prefix
        .if [esi].RegOverride == ASSUME_DS
            mov [esi].RegOverride,EMPTY
        .endif
        mov opndidx,OPND2
        .endc
    .case T_LODS
    .case T_LODSB
    .case T_LODSW
    .case T_LODSD
    .case T_LODSQ
        ;; v2.10: remove unnecessary DS prefix ( Masm-compatible )
        .if [esi].RegOverride == ASSUME_DS
            mov [esi].RegOverride,EMPTY
        .endif
        .endc
    .default ;; INS[B|W|D], SCAS[B|W|D|Q], STOS[B|W|D|Q]
             ;; INSx, SCASx and STOSx don't allow any segment prefix != ES
             ;; for the memory operand.

        .if [esi].RegOverride != EMPTY
            .if [esi].RegOverride == ASSUME_ES
                mov [esi].RegOverride,EMPTY
            .else
                asmerr(2070)
            .endif
        .endif
    .endsw

    mov   ecx,opndidx
    shl   ecx,2
    mov   eax,[esi].pinstr
    movzx eax,[eax].instr_item.opclsidx
    imul  eax,eax,opnd_class

    .if opnd_clstab[eax].opnd_type[ecx] == OP_NONE
        and [esi].flags,not CI_ISWIDE
        mov [esi].opsiz,FALSE
    .endif

    ;; if the instruction is the variant without suffix (MOVS, LODS, ..),
    ;; then use the operand's size to get further info.
    mov ebx,opndidx
    shl ebx,4
    .if opnd_clstab[eax].opnd_type[ecx] != OP_NONE && [esi].opnd[ebx].type != OP_NONE

        mov op_size,OperandSize([esi].opnd[ebx].type, esi)
        ;; v2.06: added. if memory operand has no size
        .if op_size == 0
            mov edx,[esi].opnd[ebx].InsFixup
            xor eax,eax
            .if edx
                mov ecx,[edx].fixup.sym
                .if [ecx].asym.state != SYM_UNDEFINED
                    inc eax
                .endif
            .endif
            .if edx == NULL || eax
                asmerr(2023)
            .endif
            mov op_size,1 ;; assume shortest format
        .endif
        .switch op_size
        .case 1
            and [esi].flags,not CI_ISWIDE
            mov [esi].opsiz,FALSE
            .endc
        .case 2
            or  [esi].flags,CI_ISWIDE
            xor eax,eax
            .if [esi].Ofssize
                inc eax
            .endif
            mov [esi].opsiz,al
            .endc
        .case 4
            or  [esi].flags,CI_ISWIDE
            xor eax,eax
            .if ![esi].Ofssize
                inc eax
            .endif
            mov [esi].opsiz,al
            .endc
        .case 8
            .if [esi].Ofssize == USE64
                or  [esi].flags,CI_ISWIDE
                mov [esi].opsiz,FALSE
                mov [esi].rex,REX_W
            .endif
            .endc
        .endsw
    .endif
    ret

HandleStringInstructions endp

check_size proc private uses esi edi ebx CodeInfo:ptr code_info, opndx:expr_t

;; - use to make sure the size of first operand match the size of second operand;
;; - optimize MOV instruction;
;; - opndx contains last operand
;; todo: BOUND second operand check ( may be WORD/DWORD or DWORD/QWORD ).
;; tofix: add a flag in instr_table[] if there's NO check to be done.

  local op1:int_t
  local op2:int_t
  local rc:int_t
  local op1_size:int_t
  local op2_size:int_t

    mov esi,CodeInfo
    mov edi,opndx

    mov ecx,[esi].opnd[OPND1].type
    mov edx,[esi].opnd[OPNI2].type
    mov rc,NOT_ERROR

    mov op1,ecx
    mov op2,edx

    movzx eax,[esi].token
    .switch eax
    .case T_IN
        .if op2 == OP_DX
            ;; wide and size is NOT determined by DX, but
            ;; by the first operand, AL|AX|EAX

            .switch ecx
            .case OP_AX
                .endc
            .case OP_AL
                and [esi].flags,not CI_ISWIDE ;; clear w-bit
            .case OP_EAX
                .if [esi].Ofssize
                    mov [esi].opsiz,FALSE
                .endif
                .endc
            .endsw
        .endif
        .endc
    .case T_OUT
        .if ecx == OP_DX
            .switch edx
            .case OP_AX
                .endc
            .case OP_AL
                and [esi].flags,not CI_ISWIDE ;; clear w-bit
            .case OP_EAX
                .if [esi].Ofssize
                    mov [esi].opsiz,FALSE
                .endif
            .endsw
        .endif
        .endc
    .case T_LEA
        .endc
    .case T_RCL
    .case T_RCR
    .case T_ROL
    .case T_ROR
    .case T_SAL
    .case T_SAR
    .case T_SHL
    .case T_SHR
        ;; v2.11: added

        mov ecx,[edi].sym
        .if ( [esi].opnd[OPND1].type == OP_M && !( [esi].flags & CI_UNDEF_SYM ) && \
            ( ecx == NULL || [ecx].asym.state != SYM_UNDEFINED ) )

            asmerr(2023)
            mov rc,eax
            .endc
        .endif
        ;; v2.0: if second argument is a forward reference,
        ;; change type to "immediate 1"
        mov ecx,[edi+expr].sym
        .if [edi+expr].kind == EXPR_ADDR && Parse_Pass == PASS_1 && \
            !( [edi+expr].flags & E_INDIRECT ) && \
            ecx && [ecx].asym.state == SYM_UNDEFINED

            mov [esi].opnd[OPNI2].type,OP_I8
            mov [esi].opnd[OPNI2].data32l,1
        .endif
        ;; v2.06: added (because if first operand is memory, wide bit
        ;; isn't set!)

        .if OperandSize(op1, esi) > 1
            or [esi].flags,CI_ISWIDE
        .endif
        ;; v2.06: makes the OP_CL_ONLY case in codegen.c obsolete
        .if op2 == OP_CL
            ;; CL is encoded in bit 345 of rm_byte, but we don't need it
            ;; so clear it here
            and [esi].rm_byte,NOT_BIT_345
        .endif
        .endc
    .case T_LDS
    .case T_LES
    .case T_LFS
    .case T_LGS
    .case T_LSS
        OperandSize(ecx, esi)
        add eax,2           ;; add 2 for the impl. segment register
        mov op1_size,eax
        mov op2_size,OperandSize(op2, esi)
        .if op2_size != 0 && op1_size != op2_size
            .return asmerr(2024)
        .endif
        .endc
    .case T_ENTER
        .endc
    .case T_MOVSX
    .case T_MOVZX
        and [esi].flags,not CI_ISWIDE
        mov op1_size,OperandSize(op1, esi)
        mov op2_size,OperandSize(op2, esi)
        .if op2_size == 0 && Parse_Pass == PASS_2
            .if op1_size == 2
                asmerr( 8019, "BYTE" )
            .else
                asmerr( 2023 )
            .endif
        .endif
        .switch op1_size
        .case 8
        .case 4
            .if op2_size < 2
                ;
            .elseif op2_size == 2
                or [esi].flags,CI_ISWIDE
            .else
                mov rc,asmerr(2024)
            .endif
            xor eax,eax
            cmp [esi].Ofssize,al
            sete al
            mov [esi].opsiz,al
            .endc
        .case 2
            .if op2_size >= 2
                mov rc,asmerr(2024)
            .endif
            xor eax,eax
            cmp [esi].Ofssize,al
            setne al
            mov [esi].opsiz,al
            .endc
        .default
            ;; op1 must be r16/r32/r64
            mov rc,asmerr(2024)
        .endsw
        .endc
    .case T_MOVSXD
        .endc
    .case T_ARPL ;; v2.06: new, avoids the OP_R16 hack in codegen.c
        mov [esi].opsiz,0
        jmp def_check
        .endc
    .case T_LAR ;; v2.04: added
    .case T_LSL ;; 19-sep-93
        and edx,OP_M
        .if ( ModuleInfo.Ofssize != USE64 || ( edx == 0 ) )
            jmp def_check
        .endif
        ;; in 64-bit, if second argument is memory operand,
        ;; ensure it has size WORD ( or 0 if a forward ref )

        mov op2_size,OperandSize(op2, esi)
        .return asmerr(2024) .if eax != 2 && eax != 0
        ;; the opsize prefix depends on the FIRST operand only!
        mov op1_size,OperandSize(op1, esi)
        .if eax != 2
            mov [esi].opsiz,FALSE
        .endif
        .endc
    .case T_IMUL ;; v2.06: check for 3rd operand must be done here
        .if [esi].opnd[OPNI3].type != OP_NONE

            mov op1_size,OperandSize(op1, esi)
            OperandSize([esi].opnd[OPNI3].type, esi)
            ;; the only case which must be checked here
            ;; is a WORD register as op1 and a DWORD immediate as op3
            .if op1_size == 2 && eax > 2
                mov rc,asmerr(2022, op1_size, eax)
                .endc
            .endif
            .if [esi].opnd[OPNI3].type & ( OP_I16 or OP_I32 )
                mov eax,OP_I32
                .if op1_size == 2
                    mov eax,OP_I16
                .endif
                mov [esi].opnd[OPNI3].type,eax
            .endif
        .endif
        jmp def_check
        .endc
    .case T_CVTSD2SI
    .case T_CVTTSD2SI
    .case T_CVTSS2SI
    .case T_CVTTSS2SI
    .case T_VBROADCASTSD
    .case T_VBROADCASTF128
    .case T_VEXTRACTF128
    .case T_VINSERTF128
    .case T_VCVTSD2SI
    .case T_VCVTTSD2SI
    .case T_VCVTSS2SI
    .case T_VCVTTSS2SI
    .case T_INVEPT
    .case T_INVVPID
        .endc
    .case T_VCVTPD2DQ
    .case T_VCVTTPD2DQ
    .case T_VCVTPD2PS
        .return asmerr(2023) .if edx == OP_M && ( [edi+expr].flags & E_INDIRECT )
        .endc
    .case T_VMOVDDUP
        .endc .if !( ecx & OP_YMM )
        ;; fall through
    .case T_VPERM2F128 ;; has just one memory variant, and VX_L isnt set
        .if edx == OP_M
            or [esi].opnd[OPNI2].type,OP_M256
        .endif
        .endc
    .case T_CRC32

        ;; v2.02: for CRC32, the second operand determines whether an
        ;; OPSIZE prefix byte is to be written.

        mov op2_size,OperandSize(op2, esi)
        .if eax < 2
            mov [esi].opsiz,FALSE
        .elseif eax == 2
            xor eax,eax
            cmp [esi].Ofssize,al
            setne al
            mov [esi].opsiz,al
        .else
            xor eax,eax
            cmp [esi].Ofssize,al
            sete al
            mov [esi].opsiz,al
        .endif
        .endc
    .case T_MOVD
        .endc
    .case T_MOV
        .if op1 & OP_SR ;; segment register as op1?
            mov op2_size,OperandSize(op2, esi)
            .if eax == 2 || eax == 4 || ( eax == 8 && ModuleInfo.Ofssize == USE64 )
                .return NOT_ERROR
            .endif
        .elseif op2 & OP_SR
            mov op1_size,OperandSize(op1, esi)
            .if eax == 2 || eax == 4 || ( eax == 8 && ModuleInfo.Ofssize == USE64 )
                .return NOT_ERROR
            .endif
        .elseif ( op1 & OP_M ) && ( op2 & OP_A ) ;; 1. operand memory reference, 2. AL|AX|EAX|RAX?

            .if !( [esi].flags & CI_ISDIRECT )

                ;; address mode is indirect.
                ;; don't use the short format (opcodes A0-A3) - it exists for direct
                ;; addressing only. Reset OP_A flag!

                and [esi].opnd[OPNI2].type,not OP_A
            .elseif [esi].Ofssize == USE64

                xor eax,eax
                mov ecx,[esi].opnd[OPND1].data32l
                mov edx,[esi].opnd[OPND1].data32h
                cmp edx,eax
                setl al
                .ifz
                    cmp ecx,0x80000000
                    setb al
                .endif
                cmp edx,-1
                .ifz
                    cmp ecx,0x80000000
                    setae ah
                .endif
                .if eax

                    ;; for 64bit, opcodes A0-A3 ( direct memory addressing with AL/AX/EAX/RAX )
                    ;; are followed by a full 64-bit moffs. This is only used if the offset won't fit
                    ;; in a 32-bit signed value.

                    and [esi].opnd[OPNI2].type,not OP_A
                .endif
            .endif

        .elseif ( op1 & OP_A ) && ( op2 & OP_M ) ;; 2. operand memory reference, 1. AL|AX|EAX|RAX?

            .if !( [esi].flags & CI_ISDIRECT )
                and [esi].opnd[OPND1].type,not OP_A
            .elseif [esi].Ofssize == USE64
                xor eax,eax
                mov ecx,[esi].opnd[OPNI2].data32l
                mov edx,[esi].opnd[OPNI2].data32h
                cmp edx,eax
                setl al
                .ifz
                    cmp ecx,0x80000000
                    setb al
                .endif
                cmp edx,-1
                .ifz
                    cmp ecx,0x80000000
                    setae ah
                .endif
                .if eax
                    and [esi].opnd[OPND1].type,not OP_A
                .endif
            .endif
        .endif
        ;; fall through
    .default
    def_check:
        ;; make sure the 2 opnds are of the same type
        mov op1_size,OperandSize(op1, esi)
        mov op2_size,OperandSize(op2, esi)
        .if op1_size > eax
            .if op2 >= OP_I8 && op2 <= OP_I32 ;; immediate
                mov op2_size,op1_size ;; promote to larger size
            .endif
        .endif

        ;; v2.04: check in idata_nofixup was signed,
        ;; so now add -256 - -129 and 128-255 to acceptable byte range.
        ;; Since Masm v8, the check is more restrictive, -255 - -129
        ;; is no longer accepted.

        .if op1_size == 1 && op2 == OP_I16 && [esi].opnd[OPNI2].data32l <= UCHAR_MAX && \
            [esi].opnd[OPNI2].data32l >= -255
            .return rc ;; OK cause no sign extension
        .endif
        .if op1_size != op2_size
            ;; if one or more are !defined, set them appropriately
            mov eax,op1
            or  eax,op2
            .if eax & ( OP_MMX or OP_XMM or OP_YMM or OP_ZMM or OP_K ) || [esi].token >= VEX_START

            .elseif op1_size != 0 && op2_size != 0

                mov eax,1
                .if ( [esi].Ofssize > USE16 && ( op1 & OP_M_ANY ) && ( op2 & OP_M_ANY ) )
                    ;; v2.30 - Memory to memory operands.
                    movzx ecx,[esi].token
                    .switch ecx
                    .case T_MOV
                    .case T_CMP
                    .case T_TEST
                    .case T_ADC
                    .case T_ADD
                    .case T_SBB
                    .case T_SUB
                    .case T_AND
                    .case T_OR
                    .case T_XOR
                        xor eax,eax
                        .endc
                    .endsw
                .endif
                .if eax
                    mov rc,asmerr(2022, op1_size, op2_size)
                .endif
            .endif
            ;; size == 0 is assumed to mean "undefined", but there
            ;; is also the case of an "empty" struct or union. The
            ;; latter case isn't handled correctly.

            .if ( op1_size == 0 )

                mov eax,op1
                or  eax,op2

                .if ( op1 & OP_M_ANY && op2 & OP_I )

                    ; changed in v2.33.56
                    mov eax,[esi].opnd[OPNI2].data32l
                    .ifs ( op2_size == 1 || ( op1 == OP_M && !( [edi+expr].flags & E_EXPLICIT ) &&
                        !( ( eax < 0 && eax < CHAR_MIN ) || eax > UCHAR_MAX ) ) )

                        mov [esi].mem_type,MT_BYTE
                        mov [esi].opnd[OPNI2].type,OP_I8
                        lea ecx,@CStr("BYTE")
                        .if ( op1 == OP_M && !( [edi+expr].flags & E_EXPLICIT ) )
                            mov [esi].opnd[OPND1].type,OP_M08
                        .endif

                    .elseifs ( op2_size == 2 && !( ( eax < 0 && eax < SHRT_MIN ) || eax > USHRT_MAX ) )

                        mov [esi].mem_type,MT_WORD
                        or  [esi].flags,CI_ISWIDE
                        mov [esi].opnd[OPNI2].type,OP_I16
                        lea ecx,@CStr("WORD")

                    .else
                        or [esi].flags,CI_ISWIDE
                        .if ModuleInfo.Ofssize == USE16 && op2_size > 2 && InWordRange([esi].opnd[OPNI2].data32l)
                            mov op2_size,2
                        .endif
                        .ifs op2_size <= 2 && eax > SHRT_MIN && ModuleInfo.Ofssize == USE16
                            mov [esi].mem_type,MT_WORD
                            mov [esi].opnd[OPNI2].type,OP_I16
                        .else
                            mov [esi].mem_type,MT_DWORD
                            mov [esi].opnd[OPNI2].type,OP_I32
                            lea ecx,@CStr("DWORD")
                        .endif
                    .endif

                    .if !( [edi+expr].flags & E_EXPLICIT )
                        ;; v2.06: emit warning at pass one if mem op isn't a forward ref
                        ;; v2.06b: added "undefined" check
                        mov eax,[esi].opnd[OPND1].InsFixup
                        .if ( ( eax  == NULL && Parse_Pass == PASS_1 && !( [esi].flags & CI_UNDEF_SYM ) ) || \
                            ( eax && Parse_Pass == PASS_2 ) )
                            asmerr( 8019, ecx )
                        .endif
                    .endif
                .elseif( ( op1 & OP_M_ANY ) && ( op2 & ( OP_R or OP_SR ) ) )
                .elseif( ( op1 & ( OP_MMX or OP_XMM ) ) && ( op2 & OP_I ) )
                    mov eax,[esi].opnd[OPNI2].data32l
                    .if eax > USHRT_MAX
                        mov [esi].opnd[OPNI2].type,OP_I32
                    .elseif eax > UCHAR_MAX
                        mov [esi].opnd[OPNI2].type,OP_I16
                    .else
                        mov [esi].opnd[OPNI2].type,OP_I8
                    .endif
                .elseif eax & ( OP_MMX or OP_XMM )
                .else
                    .switch op2_size
                    .case 1
                        mov [esi].mem_type,MT_BYTE
                        .if Parse_Pass == PASS_1 && ( op2 & OP_I )
                            asmerr( 8019, "BYTE" )
                        .endif
                        .endc
                    .case 2
                        mov [esi].mem_type,MT_WORD
                        or [esi].flags,CI_ISWIDE
                        .if Parse_Pass == PASS_1 && ( op2 & OP_I )
                            asmerr( 8019, "WORD" )
                        .endif
                        .if [esi].Ofssize
                            mov [esi].opsiz,TRUE
                        .endif
                        .endc
                    .case 4
                        mov [esi].mem_type,MT_DWORD
                        or [esi].flags,CI_ISWIDE
                        .if Parse_Pass == PASS_1 && ( op2 & OP_I )
                            asmerr( 8019, "DWORD" )
                        .endif
                        .endc
                    .endsw
                .endif
            .endif
        .endif
    .endsw
    mov eax,rc
    ret

check_size endp

IsType proc private name:string_t

    SymSearch(name)
    .return .if eax && [eax].asym.state == SYM_TYPE
    xor eax,eax
    ret

IsType endp

;
; Handles {modifiers}
;
; Rounding
;  to nearest or even        {rn-sae} - _MM_FROUND_TO_NEAREST_INT
;  toward negative infinity  {rd-sae} - _MM_FROUND_TO_NEG_INF
;  toward positive infinity  {ru-sae} - _MM_FROUND_TO_POS_INF
;  toward zero               {rz-sae} - _MM_FROUND_TO_ZERO
;
; Suppress All Exceptions    {sae}    - __MM_FROUND_NO_EXC
; Merge Mask                 {k1}
; Zero Mask                  {k1}{z}
;
parsevex proc private string:string_t, result:ptr uchar_t

    mov edx,string
    mov ecx,result
    mov eax,[edx]

    .switch ( al )

      .case 9
      .case ' '
        inc edx
        mov eax,[edx]
        .gotosw

      .case 'k' ; {k1}
        .endc .if ah < '1'
        .endc .if ah > '7'
        .endc .if eax & 0xFF0000
        sub ah,'0'
        or  [ecx],ah
        .return 1

      .case '1' ; {1to2} {1to4} {1to8} {1to16}
        .endc .if ah != 't'
        shr eax,24
        .switch ( al )
          .case '1'
            .endc .if byte ptr [edx+4] != '6'
          .case '2'
          .case '4'
          .case '8'
            or  byte ptr [ecx],0x10
            .return 1
        .endsw
        .endc

      .case 'z' ; {z}
        .endc .if ah
        or byte ptr [ecx],0x80
        .return 1

      .case 'r' ; {rn-sae} {ru-sae} {rd-sae} {rz-sae}
        .endc .if byte ptr [edx+2] != '-'
        .endc .if byte ptr [edx+3] != 's'
        mov edx,0x2000
        .switch ( ah )
          .case 'u'
            or dl,0x50  ; B|L1
            .endc
          .case 'z'
            or dl,0x70  ; B|L0|L1
          .case 'd'
            or dl,0x30  ; B|L0
          .case 'n'
            or dl,0x10  ; B
        .endsw
        .if dl
            or [ecx],dx
            .return 1
        .endif
        .endc

      .case 's' ; {sae}
        .endc .if eax != 'eas'
        mov edx,0x2010  ; B
        or [ecx],dx
        .return 1
    .endsw
    xor eax,eax
    ret

parsevex endp


;; ParseLine() is the main parser function.
;; It scans the tokens in tokenarray[] and does:
;; - for code labels: call CreateLabel()
;; - for data items and data directives: call data_dir()
;; - for other directives: call directive[]()
;; - for instructions: fill CodeInfo and call codegen()

;; callback PROC(...) [?]

ProcType        proto :int_t, :token_t
PublicDirective proto :int_t, :token_t
mem2mem         proto :uint_t, :uint_t, :token_t, :ptr expr
imm2xmm         proto :token_t, :expr_t
NewDirective    proto :int_t, :token_t

externdef       CurrEnum:asym_t
EnumDirective   proto :int_t, :token_t
SizeFromExpression proto :ptr expr

    assume ebx:token_t
    assume esi:token_t
    assume edi:nothing

ParseLine proc uses esi edi ebx tokenarray:token_t

    local i:int_t
    local j:int_t
    local q:int_t
    local dirflags:uint_t
    local sym:asym_t
    local oldofs:uint_t
    local CodeInfo:code_info
    local opndx[MAX_OPND+1]:expr
    local buffer:ptr char_t

    mov ebx,tokenarray
    .return EnumDirective(0, ebx) .if ( CurrEnum && [ebx].token == T_ID )

    mov buffer,NULL ; v2.32 - may not be used..

continue:

    mov i,0

    .if ( Token_Count > 2 && [ebx].token == T_ID &&
          ( [ebx+16].token == T_COLON ||
            [ebx+16].token == T_DBL_COLON ) )

        .if ( buffer == NULL )

            mov buffer,alloca(ModuleInfo.max_line_len)
            mov edi,eax
        .endif

        ; break label: macro/hll lines

        strcpy( edi, [ebx+32].tokpos )
        strcpy( CurrSource, [ebx].string_ptr )
        strcat( CurrSource, [ebx+16].string_ptr )

        mov Token_Count,Tokenize( CurrSource, 0, ebx, TOK_DEFAULT )

        .return .if ParseLine( ebx ) == ERROR

        .if ModuleInfo.list ; v2.26 -- missing line from list file (wiesl)
            and ModuleInfo.line_flags,not LOF_LISTED
        .endif

        ; parse macro or hll function

        strcpy(CurrSource, edi)
        mov Token_Count,Tokenize(CurrSource, 0, ebx, TOK_DEFAULT)

        ExpandLine(CurrSource, ebx)

        .return .if eax == EMPTY
        .return .if eax == ERROR

        mov i,0

        ; label:

    .elseif ( [ebx].token == T_ID && ( [ebx+16].token == T_COLON || [ebx+16].token == T_DBL_COLON ) )

        mov i,2

        .if ProcStatus & PRST_PROLOGUE_NOT_DONE

            write_prologue(ebx)
        .endif
        ;
        ; create a global or local code label
        ;
        xor eax,eax
        .if ( ModuleInfo.scoped && CurrProc && [ebx+16].token != T_DBL_COLON )
            inc eax
        .endif
        .if CreateLabel( [ebx].string_ptr, MT_NEAR, NULL, eax ) == NULL
            .return ERROR
        .endif
        ;
        ; v2.26: make label:: public
        ;
        .if ( [ebx+16].token == T_DBL_COLON && ModuleInfo.scoped && !CurrProc )

            mov [ebx+16].token,T_FINAL
            mov Token_Count,1
            PublicDirective( -1, tokenarray )
        .endif

        lea esi,[ebx+32]

        .if [esi].token == T_FINAL
            ;
            ; v2.06: this is a bit too late. Should be done BEFORE
            ; CreateLabel, because of '@@'. There's a flag supposed to
            ; be used for this handling, LOF_STORED in line_flags.
            ; It's only a problem if a '@@:' is the first line
            ; in the code section.
            ; v2.10: is no longer an issue because the label counter has
            ; been moved to module_vars (see global.h).
            ;
            FStoreLine(0)
            .if CurrFile[LST*4]
                LstWrite( LSTTYPE_LABEL, 0, NULL )
            .endif
            .return NOT_ERROR
        .endif
    .endif

    ; handle directives and (anonymous) data items

    mov esi,i
    shl esi,4
    add esi,ebx

    mov j,0
    .if ModuleInfo.ComStack
        .if ( [ebx].token == T_STYPE &&
              [ebx+16].token == T_DIRECTIVE &&
              [ebx+16].tokval == T_PROC )
            inc j
        .endif
    .elseif ( [ebx].token == T_DIRECTIVE && [ebx].tokval == T_DOT_INLINE )

        mov [ebx].token,T_ID
        mov [ebx].string_ptr,[ebx+16].string_ptr
        mov [ebx+16].token,T_DIRECTIVE
        mov [ebx+16].tokval,T_PROTO
        mov [ebx+16].dirtype,DRT_PROTO
        ;mov [ebx+16].string_ptr,&@CStr( "proto" )
    .endif

    .if j || [esi].token != T_INSTRUCTION
        ;
        ; a code label before a data item is only accepted in Masm5 compat mode
        ;
        mov Frame_Type,FRAME_NONE
        mov SegOverride,NULL
        .if ( i == 0 && ( j || [ebx].token == T_ID ) )
            ;
            ; token at pos 0 may be a label.
            ; it IS a label if:
            ; 1. token at pos 1 is a directive (lbl dd ...)
            ; 2. token at pos 0 is NOT a userdef type ( lbl DWORD ...)
            ; 3. inside a struct and token at pos 1 is a userdef type
            ;    or a predefined type. (usertype DWORD|usertype ... )
            ;    the separate namespace allows this syntax here.
            ;
            .if [ebx+16].token == T_DIRECTIVE
                inc i
                add esi,16
            .else
                mov sym,IsType( [ebx].string_ptr )
                .if eax == NULL
                    inc i
                    add esi,16
                .elseif ( CurrStruct )
                    xor eax,eax
                    .if ( [ebx+16].token == T_STYPE )
                        inc eax
                    .elseif ( [ebx+16].token == T_ID )
                        IsType( [ebx+16].string_ptr )
                    .endif
                    .if ( eax )
                        inc i
                        add esi,16
                    .endif
                .endif
            .endif
        .endif
        movzx eax,[esi].token
        .switch eax
        .case T_DIRECTIVE
            .if [esi].dirtype == DRT_DATADIR
                .return( data_dir( i, tokenarray, NULL ) )
            .endif
            mov dirflags,GetValueSp( [esi].tokval )
            .if j || ( CurrStruct && ( dirflags & DF_NOSTRUC ) )

                .if [esi].tokval != T_PROC
                    .return( asmerr( 2037 ) )
                .endif
                .if StoreState
                    .if ( ( dirflags & DF_CGEN ) && ModuleInfo.CurrComment && ModuleInfo.list_generated_code )
                        FStoreLine(1)
                    .else
                        FStoreLine(0)
                    .endif
                .endif
                mov edi,ProcType( i, tokenarray )
                .if ( ModuleInfo.list && ( Parse_Pass == PASS_1 || ModuleInfo.GeneratedCode || UseSavedState == FALSE ) )
                    LstWriteSrcLine()
                .endif
                .return( edi )
            .endif
            ;; label allowed for directive?
            .if ( dirflags & DF_LABEL )
                .if ( i && [ebx].token != T_ID )
                    .return( asmerr(2008, [ebx].string_ptr ) )
                .endif
            .elseif ( i && [esi-16].token != T_COLON && [esi-16].token != T_DBL_COLON )
                .return( asmerr(2008, [esi-16].string_ptr ) )
            .endif
            ;; must be done BEFORE FStoreLine()!
            .if( ( ProcStatus & PRST_PROLOGUE_NOT_DONE ) && ( dirflags & DF_PROC ) )
                write_prologue( tokenarray )
            .endif
            .if ( StoreState || ( dirflags & DF_STORE ) )

                ;; v2.07: the comment must be stored as well
                ;; if a listing (with -Sg) is to be written and
                ;; the directive will generate lines

                .if ( ( dirflags & DF_CGEN ) && ModuleInfo.CurrComment && ModuleInfo.list_generated_code )
                    FStoreLine(1)
                .else
                    FStoreLine(0)
                .endif
            .endif
            .if ( [esi].dirtype > DRT_DATADIR )
                movzx eax,[esi].dirtype
                mov eax,directive_tab[eax*4]
                assume eax:fpDirective
                eax( i, ebx )
                assume eax:nothing
                mov edi,eax
            .else
                mov edi,ERROR
                ;; ENDM, EXITM and GOTO directives should never be seen here
                mov eax,[esi].tokval
                .switch eax
                .case T_ENDM
                    asmerr( 1008 )
                    .endc
                .case T_RETM
                .case T_EXITM
                .case T_GOTO
                    asmerr( 2170 )
                    .endc
                .default
                    ;
                    ; this error may happen if
                    ; CATSTR, SUBSTR, MACRO, ...
                    ; aren't at pos 1
                    ;
                    asmerr(2008, [esi].string_ptr )
                    .endc
                .endsw
            .endif
            ;; v2.0: for generated code it's important that list file is
            ;; written in ALL passes, to update file position!
            ;; v2.08: UseSavedState == FALSE added
            .if ( ModuleInfo.list && ( Parse_Pass == PASS_1 || \
                  ModuleInfo.GeneratedCode || UseSavedState == FALSE ) )
                LstWriteSrcLine()
            .endif
            .return( edi )
        .case T_BINARY_OPERATOR
            .endc .if [esi].tokval != T_PTR
        .case T_STYPE
            .return data_dir( i, ebx, NULL )
        .case T_ID
            .if IsType( [esi].string_ptr )
                ;; v2.31.25: Type() -- constructor
                .endc .if [esi].hll_flags & T_HLL_PROC
                .return data_dir( i, ebx, eax )
            .endif
            .endc
        .default
            .if ( [esi].token == T_COLON )
                .return asmerr( 2065, ":")
            .endif
            .endc
        .endsw ;; end switch (tokenarray[i].token)

        .if ( i && [esi-16].token == T_ID )
            dec i
            sub esi,16
        .endif

        .if ( i == 0 && ( ModuleInfo.strict_masm_compat == 0 ) && ( [ebx].hll_flags & T_HLL_PROC ) )

            .if ( buffer == NULL )

                mov buffer,alloca(ModuleInfo.max_line_len)
                mov edi,eax
            .endif
            ;
            ; invoke handle import, call do not..
            ;
            lea esi,@CStr( ".new " )
            .if !IsType( [ebx].string_ptr ) ; added 2.31.44
                lea esi,@CStr( "invoke " )
            .endif

            strcat( strcpy( edi, esi ), [ebx].tokpos )
            mov Token_Count,Tokenize( strcpy( CurrSource, edi ), 0, ebx, TOK_DEFAULT )
            jmp continue

        .elseif ( i != 0 || [ebx].dirtype != '{' )

            .return EnumDirective(0, ebx) .if ( CurrEnum && [ebx].token == T_STRING )
            .if ( i == 0 && Token_Count > 1 )
                .if ( GetOperator( &[ebx+16] ) )
                    .return ProcessOperator( tokenarray )
                .endif
            .endif
            .return asmerr(2008, [esi].string_ptr )
        .endif
    .endif

    .return asmerr( 2037 ) .if CurrStruct
    .if ProcStatus & PRST_PROLOGUE_NOT_DONE
        write_prologue( ebx )
    .endif
    .if CurrFile[LST*4]
        mov oldofs,GetCurrOffset()
    .endif

    ;; init CodeInfo
    xor eax,eax
    mov ecx,sizeof(CodeInfo) / 4
    lea edi,CodeInfo
    rep stosd
    mov CodeInfo.inst,EMPTY
    mov CodeInfo.RegOverride,EMPTY
    mov CodeInfo.mem_type,MT_EMPTY
    mov CodeInfo.Ofssize,ModuleInfo.Ofssize

    ;; instruction prefix?

    .if ( i == 0 && [ebx].dirtype == '{' )
        .if ( !tstricmp( [ebx].string_ptr, "evex" ) )
            mov CodeInfo.evex,1
            inc i
            add esi,16
        .else
            .return asmerr(2008, [esi].string_ptr )
        .endif
    .endif

    ;; T_LOCK, T_REP, T_REPE, T_REPNE, T_REPNZ, T_REPZ
    .if ( [esi].tokval >= T_LOCK && [esi].tokval <= T_REPZ )
        mov CodeInfo.inst,[esi].tokval
        inc i
        add esi,16
        ;; prefix has to be followed by an instruction
        .return asmerr(2068) .if [esi].token != T_INSTRUCTION
    .endif

    .if CurrProc
        .switch [esi].tokval
        .case T_RET
        .case T_IRET  ;; IRET is always 16-bit; OTOH, IRETW doesn't exist
        .case T_IRETD
        .case T_IRETQ
            .if ( !( ProcStatus & PRST_INSIDE_EPILOGUE ) && ModuleInfo.epiloguemode != PEM_NONE )

                ;; v2.07: special handling for RET/IRET
                xor eax,eax
                .if ( ModuleInfo.CurrComment && ModuleInfo.list_generated_code )
                    inc eax
                .endif
                FStoreLine( eax )
                or ProcStatus,PRST_INSIDE_EPILOGUE
                RetInstr( i, tokenarray, Token_Count )
                and ProcStatus,not PRST_INSIDE_EPILOGUE
                .return
            .endif
            ;; default translation: just RET to RETF if proc is far
            ;; v2.08: this code must run even if PRST_INSIDE_EPILOGUE is set
            .if [esi].tokval == T_RET
                mov eax,CurrProc
                .if [eax].asym.mem_type == MT_FAR
                    mov [esi].tokval,T_RETF
                .endif
            .endif
        .endsw
    .endif

    .if ModuleInfo.strict_masm_compat == 0

        lea esi,[ebx+16]
        .for ( j = 1 : [esi].token != T_FINAL : j++, esi += 16 )

            .if ( [esi].hll_flags & T_HLL_PROC )

                .if ( buffer == NULL )

                    mov buffer,alloca(ModuleInfo.max_line_len)
                    mov edi,eax
                .endif
                ;
                ; v2.21 - mov reg,proc(...)
                ; v2.27 - mov reg,class.proc(...)
                ;
                .return .if ExpandHllProcEx( buffer, j, ebx ) == ERROR
                .if eax == STRING_EXPANDED
                    FStoreLine(0)
                    .return NOT_ERROR
                .endif
                .break
            .endif
        .endf
    .endif

    FStoreLine(0) ;; must be placed AFTER write_prologue()

    mov esi,i
    shl esi,4
    add esi,ebx
    mov eax,[esi].tokval
    mov CodeInfo.token,ax

    ;; get the instruction's start position in InstrTable[]
    movzx eax,IndexFromToken(eax)
    lea eax,InstrTable[eax*8]
    mov CodeInfo.pinstr,eax

    inc i
    add esi,16

    mov eax,CurrSeg
    .return asmerr(2034) .if eax == NULL

    mov eax,[eax].dsym.seginfo

    .if [eax].seg_info.segtype == SEGTYPE_UNDEF
        mov [eax].seg_info.segtype,SEGTYPE_CODE
    .endif
    .if ModuleInfo.CommentDataInCode
        omf_OutSelect( FALSE )
    .endif

    ; get the instruction's arguments.
    ; This loop accepts up to 4 arguments if AVXSUPP is on

    .for ( j = 0: j < lengthof(opndx) && [esi].token != T_FINAL: j++ )
        .if j
            .break .if [esi].token != T_COMMA
            inc i
        .endif
        imul edi,j,expr
        lea ecx,opndx[edi]
        .return .if EvalOperand( &i, tokenarray, Token_Count, ecx, 0 ) == ERROR

        mov esi,i
        shl esi,4
        add esi,tokenarray

        .if [esi-16].hll_flags & T_EVEX_OPT
            mov CodeInfo.evex,1
            lea ebx,[esi-16] ; get transform modifiers
            .repeat
                .if !parsevex( [ebx].string_ptr, &CodeInfo.evexP3 )
                    .return asmerr(2008, [ebx].string_ptr )
                .endif
                sub ebx,16
            .until !( [ebx].hll_flags & T_EVEX_OPT )

            .if opndx[edi].kind == EXPR_EMPTY
                dec j
                .continue
            .endif
        .endif

        .switch opndx[edi].kind
        .case EXPR_FLOAT
            ;
            ; v2.06: accept float constants for PUSH
            ;
            .if ( j == OPND2 || CodeInfo.token == T_PUSH || CodeInfo.token == T_PUSHD )
                .if ( ModuleInfo.strict_masm_compat == FALSE )

                    ; v2.27: convert to REAL

                    .if ( opndx[edi].mem_type != MT_EMPTY )
                        movzx eax,CurrWordSize ; added v2.31.31
                        .if j
                            .if opndx[edi-expr].kind == EXPR_REG && !( opndx[edi-expr].flags & E_INDIRECT )
                                mov eax,opndx[edi-expr].base_reg
                                SizeFromRegister( [eax].asm_tok.tokval )
                            .elseif opndx[edi-expr].kind == EXPR_ADDR || opndx[edi-expr].kind == EXPR_REG
                                ; added v2.31.27
                                SizeFromMemtype(opndx[edi-expr].mem_type, opndx[edi-expr].Ofssize, opndx[edi-expr].type)
                            .endif
                        .endif
                        xor ecx,ecx
                        .switch eax
                        .case 2:  mov ecx,MT_REAL2  : .endc
                        .case 4:  mov ecx,MT_REAL4  : .endc
                        .case 8:  mov ecx,MT_REAL8  : .endc
                        .case 16: mov ecx,MT_REAL16 : .endc
                        .endsw
                        .if ecx
                            lea edx,opndx[edi]
                            mov opndx[edi].kind,EXPR_CONST
                            mov opndx[edi].expr.mem_type,cl
                            .if eax != 16
                                quad_resize(edx, eax)
                            .endif
                            .endc
                        .endif
                    .endif
                .endif
                ;
                ; Masm message is: real or BCD number not allowed
                ;
                .return asmerr( 2050 )
            .endif
            ;
            ; fall through
            ;
        .case EXPR_EMPTY
            ;
            ; added v2.30.11 - allow mov reg,.new Class()
            ;
            .if ( i > 1 && [esi].token == T_DIRECTIVE && [esi].tokval == T_DOT_NEW )

                .if ( buffer == NULL )

                    mov buffer,alloca(ModuleInfo.max_line_len)
                .endif

                mov  eax,tokenarray
                mov  eax,[eax].asm_tok.tokpos
                mov  ecx,[esi].tokpos
                sub  ecx,eax
                mov  edx,edi
                mov  edi,buffer
                xchg esi,eax
                rep  movsb
                mov  esi,eax
                .if ModuleInfo.Ofssize == USE64
                    mov eax,"xar"
                .else
                    mov eax,"xae"
                .endif
                stosd
                mov edi,edx
                NewDirective(i, tokenarray)
                .if Parse_Pass > PASS_1
                    mov Token_Count,Tokenize(strcpy(CurrSource, buffer), 0, tokenarray, TOK_DEFAULT)
                    .return ParseLine(tokenarray)
                .endif
                .return NOT_ERROR
            .endif
            .if i == Token_Count
                sub esi,16 ;; v2.08: if there was a terminating comma, display it
            .endif
            ;
            ; fall through
            ;
        .case EXPR_ERROR
            .return asmerr(2008, [esi].string_ptr )
        .endsw
    .endf

    .return asmerr(2008, [esi].tokpos) .if [esi].token != T_FINAL
    .if j >= 3
        or CodeInfo.vflags,VX_OP3
    .endif

    .for ( q = 0, ebx = 0: ebx < j && ebx < MAX_OPND: ebx++, q++ )

        mov Frame_Type,FRAME_NONE
        mov SegOverride,0 ; segreg prefix is stored in RegOverride
        imul edx,ebx,expr

        ; if encoding is VEX and destination op is XMM, YMM or memory,
        ; the second argument may be stored in the vexregop field.

        movzx eax,CodeInfo.token
        mov ecx,CodeInfo.opnd[OPND1].type

        .if ( eax >= VEX_START && ebx == OPND2 && \
            ( ecx & ( OP_XMM or OP_YMM or OP_ZMM or OP_M or OP_K or OP_M256 or OP_M512 or OP_R32 or OP_R64 ) ) )

            movzx edi,vex_flags[eax-VEX_START]
            .if ( ( eax < T_ANDN || eax > T_PEXT ) && ( ecx & ( OP_R32 or OP_R64 ) ) )
            .elseif edi & VX_NND
            .elseif ( ( edi & VX_IMM ) && ( opndx[expr*2].kind == EXPR_CONST ) && ( j > 2 ) )
            .elseif ( ( edi & VX_HALF ) && ( ( ecx & ( OP_XMM or OP_YMM or OP_ZMM ) ) && \
                      ( opndx[edx].flags & E_INDIRECT ) ) )
                mov CodeInfo.rm_byte,0
            .elseif ( ( edi & VX_NMEM ) && ( ( ecx & OP_M ) || \
                     ( ( eax == T_VMOVSD || eax == T_VMOVSS ) && \
                     ( opndx[expr].kind != EXPR_REG || opndx[expr].flags & E_INDIRECT ) ) ) )

                ; v2.11: VMOVSD and VMOVSS always have 2 ops if a memory op is involved

            .else
                .return asmerr(2070) .if opndx[expr].kind != EXPR_REG
                mov eax,opndx[edx].base_reg
                mov eax,[eax].asm_tok.tokval
                .return asmerr(2070) .if !( GetValueSp(eax) & \
                    ( OP_R32 or OP_R64 or OP_XMM or OP_YMM or OP_ZMM or OP_K ) )

                ; fixme: check if there's an operand behind OPND2 at all!
                ; if no, there's no point to continue with switch (opndx[].kind).
                ; v2.11: additional check for j <= 2 added

                .if ( j <= 2 )

                    ; v2.11: next line should be activated - currently the
                    ; error is emitted below as syntax error

                    movzx eax,CodeInfo.token
                    .if ResWordTable[eax*8].flags & RWF_EVEX
                        inc j
                    .endif

                    ; flag VX_DST is set if an immediate is expected as operand 3

                .elseif ( ( edi & VX_DST ) && ( opndx[expr*2].kind == EXPR_CONST ) )

                    .if opndx[OPND1].base_reg

                        ; first operand register is moved to vexregop
                        ; handle VEX.NDD

                        mov ecx,opndx[edx].base_reg
                        mov eax,[ecx].asm_tok.tokval
                        mov eax,GetValueSp(eax)

                        mov ecx,opndx[OPND1].base_reg
                        mov cl,[ecx].asm_tok.bytval
                        inc cl
                        mov CodeInfo.vexregop,cl
                        .if eax & OP_ZMM
                            or CodeInfo.vexregop,0x80
                        .elseif eax & OP_YMM
                            or CodeInfo.vexregop,0x40
                        .endif

                        lea  edi,opndx[0]
                        lea  eax,opndx[edx]
                        xchg eax,esi
                        mov  ecx,expr * 3
                        rep  movsb
                        mov  esi,eax

                        mov CodeInfo.rm_byte,0
                        .return .if process_register( &CodeInfo, OPND1, &opndx, q ) == ERROR
                        inc q
                    .endif
                .else
                    mov ecx,opndx[edx].base_reg
                    mov eax,[ecx].asm_tok.tokval
                    mov eax,GetValueSp(eax)

                    ; v2.08: no error here if first op is an untyped memory reference
                    ; note that OP_M includes OP_M128, but not OP_M256 (to be fixed?)

                    .if ( CodeInfo.opnd[OPND1].type == OP_M )

                    .elseif ( ( eax & ( OP_XMM or OP_M128 ) ) && \
                        ( CodeInfo.opnd[OPND1].type & (OP_YMM or OP_M256 ) ) || \
                        ( eax & ( OP_YMM or OP_M256 ) ) && \
                        ( CodeInfo.opnd[OPND1].type & (OP_XMM or OP_M128 ) ) )
                        .return asmerr(2070)
                    .endif

                    ; second operand register is moved to vexregop
                    ; to be fixed: CurrOpnd is always OPND2, so use this const here

                    mov edi,eax
                    mov al,[ecx].asm_tok.bytval
                    inc al
                    mov CodeInfo.vexregop,al
                    .if CodeInfo.vexregop > 16 || edi & OP_ZMM

                        mov CodeInfo.evex,1
                        .if CodeInfo.vexregop > 16
                            or CodeInfo.vflags,VX_OP2V
                        .endif
                        .if edi & OP_ZMM
                            or CodeInfo.vexregop,0x80
                            or CodeInfo.vflags,VX_ZMM
                        .endif
                    .elseif edi & OP_YMM
                        or CodeInfo.vexregop,0x40
                    .endif
                    inc  q
                    lea  edi,opndx[edx]
                    lea  eax,opndx[edx+expr]
                    xchg eax,esi
                    mov  ecx,expr * 2
                    rep  movsb
                    mov  esi,eax
                .endif
                dec j
            .endif
        .endif
        imul edx,ebx,expr
        .switch opndx[edx].kind
        .case EXPR_ADDR
            .return .if process_address( &CodeInfo, ebx, &opndx[edx] ) == ERROR
            .endc
        .case EXPR_CONST
            .return .if process_const( &CodeInfo, ebx, &opndx[edx] ) == ERROR
            .endc
        .case EXPR_REG
            .if opndx[edx].flags & E_INDIRECT ; indirect operand ( "[EBX+...]" )?
                .return .if process_address( &CodeInfo, ebx, &opndx[edx] ) == ERROR
            .else

                ; process_register() can't handle 3rd operand

                .if ebx == OPND3

                    mov ecx,opndx[edx].base_reg
                    mov eax,[ecx].asm_tok.tokval
                    mov eax,GetValueSp(eax)
                    mov CodeInfo.opnd[OPNI3].type,eax
                    movzx eax,[ecx].asm_tok.bytval
                    mov CodeInfo.opnd[OPNI3].data32l,eax
                    mov ecx,CodeInfo.pinstr
                    .if [ecx].instr_item.evex & VX_XMMI
                        mov cl,CodeInfo.opc_or
                        and cl,0xF0
                        or  al,cl
                        mov CodeInfo.opc_or,al
                    .endif
                .elseif process_register( &CodeInfo, ebx, &opndx, q ) == ERROR
                    .return
                .endif
            .endif
            .endc
        .endsw
    .endf

ifdef USE_INDIRECTION

    assume edi:ptr expr

    .if ( ebx == 2 && \
          ( ( opndx.kind == EXPR_REG && opndx[expr].kind == EXPR_ADDR ) || \
            ( opndx.kind == EXPR_ADDR && opndx[expr].kind != EXPR_ADDR ) ) )

        mov ecx,1
        lea edi,opndx
        .if ( [edi].kind == EXPR_REG )
            add edi,expr
            dec ecx
        .endif
        mov ebx,[edi].base_reg
        mov eax,[edi].sym
        mov edx,[edi].mbr

        .if ( ebx && eax && edx && [edi].flags & E_IS_DOT )

            mov edx,[eax].asym.target_type
            .if ( [eax].asym.mem_type == MT_PTR && \
                  [eax].asym.is_ptr && \
                  [edx].asym.state == SYM_TYPE && \
                  [ebx].token == T_ID && \
                  ( [ebx+16].token == T_DOT || [ebx+16].token == T_OP_SQ_BRACKET ) )

                .if ( ( !ecx && \
                        [ebx-3*16].token == T_INSTRUCTION && \
                        [ebx-32].token == T_REG && \
                        [ebx-16].token == T_COMMA \
                      ) || ( ecx && [ebx-16].token == T_INSTRUCTION )
                    )
                    .return HandleIndirection(eax, ebx, ecx)
                .endif
            .endif
        .endif
        mov ebx,2
    .endif

endif
    ;
    ; 4 arguments are valid vor AVX only
    ;
    .if ebx != j
        .for ( : [esi].token != T_COMMA: i--, esi -= 16 )
        .endf
        .return asmerr(2008, [esi].tokpos)
    .endif
    ;
    ; for FAR calls/jmps some special handling is required:
    ; in the instruction tables, the "far" entries are located BEHIND
    ; the "near" entries, that's why it's needed to skip all items
    ; until the next "first" item is found.
    ;
    .if CodeInfo.flags & CI_ISFAR
        .if CodeInfo.token == T_CALL || CodeInfo.token == T_JMP
            .repeat
                add CodeInfo.pinstr,instr_item
                mov edx,CodeInfo.pinstr
            .until [edx].instr_item.flags & II_FIRST
        .endif
    .endif

    ;; special handling for string instructions
    mov edx,CodeInfo.pinstr
    mov al,[edx].instr_item.flags
    and eax,II_ALLOWED_PREFIX

    .if eax == AP_REP || eax == AP_REPxx
        ;
        ; v2.31.24: immediate operand to XMM
        ;
        .if ( ModuleInfo.strict_masm_compat == 0 && CodeInfo.token == T_MOVSD )
            .if ( CodeInfo.opnd[OPND1].type == OP_XMM && \
                ( CodeInfo.opnd[OPNI2].type & OP_I_ANY ) )
                .return imm2xmm( tokenarray, &opndx[expr] )
            .endif
        .endif

        HandleStringInstructions( &CodeInfo, &opndx )

    .else
        .if ebx > 1

            ; v1.96: check if a third argument is ok

            .if ebx > 2

                mov edx,CodeInfo.pinstr
                .while 1

                    movzx eax,[edx].instr_item.opclsidx
                    imul  eax,eax,opnd_class

                    .break .if opnd_clstab[eax].opnd_type_3rd != OP3_NONE

                    add edx,instr_item
                    .if [edx].instr_item.flags & II_FIRST
                        .for ( : [esi].token != T_COMMA: esi -= 16 )
                        .endf
                        .return asmerr(2008, [esi].tokpos )
                    .endif
                .endw
                mov CodeInfo.pinstr,edx
            .endif
            ;
            ; v2.06: moved here from process_const()
            ;
            .if ( CodeInfo.token == T_IMUL )
                ;
                ; the 2-operand form with an immediate as second op
                ; is actually a 3-operand form. That's why the rm byte
                ; has to be adjusted.
                ;
                mov eax,CodeInfo.opnd[OPNI2].InsFixup
                .if eax
                    mov eax,[eax].fixup.sym
                .endif
                .if CodeInfo.opnd[OPNI3].type == OP_NONE && ( CodeInfo.opnd[OPNI2].type & OP_I )

                    .if CodeInfo.rex & REX_B
                        or CodeInfo.rex,REX_R
                    .endif
                    mov al,CodeInfo.rm_byte
                    mov dl,al
                    and al,not BIT_345
                    and dl,BIT_012
                    shl dl,3
                    or  al,dl
                    mov CodeInfo.rm_byte,al

                .elseif ( ( CodeInfo.opnd[OPNI3].type != OP_NONE ) && ( CodeInfo.opnd[OPNI2].type & OP_I ) && \
                          eax && [eax].asym.state == SYM_UNDEFINED )
                    mov CodeInfo.opnd[OPNI2].type,OP_M
                .endif
            .endif
            .return .if check_size( &CodeInfo, &opndx ) == ERROR
        .endif
        .if CodeInfo.Ofssize == USE64
            .if ( CodeInfo.flags & CI_X86HI_USED && CodeInfo.rex )
                asmerr( 3012 )
            .endif

            ;; for some instructions, the "wide" flag has to be removed selectively.
            ;; this is to be improved - by a new flag in struct instr_item.

            ;; added v2.31.32
            movzx eax,CodeInfo.token

            .if eax < VEX_START && eax >= T_ADDPD && j > 1 && opndx[expr].kind == EXPR_CONST
                mov edx,opndx[expr].quoted_string
                .if edx
                    .if [edx].asm_tok.token == T_STRING && \
                        [edx].asm_tok.dirtype == '{'

                        mov eax,T_MOVAPS
                    .endif
                .endif
            .endif

            .switch eax
            .case T_PUSH
            .case T_POP
                ;; v2.06: REX.W prefix is always 0, because size is either 2 or 8
                and CodeInfo.rex,0x7
                .endc
            .case T_CALL
            .case T_JMP
            .case T_VMREAD
            .case T_VMWRITE
                ;; v2.02: previously rex-prefix was cleared entirely,
                ;; but bits 0-2 are needed to make "call rax" and "call r8"
                ;; distinguishable!

                and CodeInfo.rex,0x7
                .endc
                ;; v2.31.32: immediate operand to XMM { 1.0, 2.0 }
            .case T_MOVAPS
                ;; v2.31.24: immediate operand to XMM
            .case T_MOVQ
            .case T_MOVSD
            .case T_ADDSD
            .case T_SUBSD
            .case T_MULSD
            .case T_DIVSD
            .case T_COMISD
            .case T_UCOMISD
            .case T_ADDSS
            .case T_SUBSS
            .case T_MULSS
            .case T_DIVSS
            .case T_COMISS
            .case T_UCOMISS
            .case T_MOVD
            .case T_MOVSS
                .endc .if ( ModuleInfo.strict_masm_compat != 0 )
                .endc .if ( CodeInfo.opnd[OPND1].type != OP_XMM )
                .endc .if !( CodeInfo.opnd[OPNI2].type & OP_I_ANY )
                .return imm2xmm( tokenarray, &opndx[expr] )
            .case T_MOV:
                ;; don't use the Wide bit for moves to/from special regs
                .if ( CodeInfo.opnd[OPND1].type & OP_RSPEC || CodeInfo.opnd[OPNI2].type & OP_RSPEC )
                    and CodeInfo.rex,0x7
                .endif
                .endc
            .endsw
        .endif

        .if ( CodeInfo.Ofssize > USE16 && !ModuleInfo.strict_masm_compat )

            movzx eax,CodeInfo.token
            mov ecx,CodeInfo.opnd[OPND1].type
            mov edx,CodeInfo.opnd[OPNI2].type

            .if ( ( ecx & OP_M_ANY ) && ( edx & OP_M_ANY ) )

                ;; v2.30 - Memory to memory operands.

                .switch eax
                .case T_MOV
                .case T_CMP
                .case T_TEST
                .case T_ADC
                .case T_ADD
                .case T_SBB
                .case T_SUB
                .case T_AND
                .case T_OR
                .case T_XOR
                .case T_COMISS
                .case T_COMISD
                    .return mem2mem( ecx, edx, tokenarray, &opndx )
                .endsw
            .endif
            xor ebx,ebx
            .if ( eax == T_COMISS && ecx == OP_M32 && ( edx & OP_I_ANY ) )
                inc ebx
            .elseif ( eax == T_COMISD && ecx == OP_M64 && ( edx & OP_I_ANY ) )
                inc ebx
            .elseif ( ( ecx == OP_XMM ) && ( edx & OP_I_ANY ) )

                .switch eax

                    ;; v2.31.32: immediate operand to XMM { 1.0, 2.0 }

                .case T_MOVAPS

                    ;; v2.31.24: immediate operand to XMM

                .case T_MOVQ
                .case T_MOVSD
                .case T_ADDSD
                .case T_SUBSD
                .case T_MULSD
                .case T_DIVSD
                .case T_COMISD
                .case T_UCOMISD
                .case T_ADDSS
                .case T_SUBSS
                .case T_MULSS
                .case T_DIVSS
                .case T_COMISS
                .case T_UCOMISS
                .case T_MOVD
                .case T_MOVSS
                    inc ebx
                .endsw
            .endif
            .if ( ebx )
                .return imm2xmm( tokenarray, &opndx[expr] )
            .endif
        .endif
    .endif

    ; now call the code generator
    codegen(&CodeInfo, oldofs)
    ret

ParseLine endp


;; process a file. introduced in v2.11

ProcessFile proc tokenarray:ptr asm_tok

    .if ( ModuleInfo.EndDirFound == FALSE && GetTextLine( CurrSource ) )

        mov edx,CurrSource ;; v2.23 - BOM UFT-8 test
        mov eax,[edx]
        and eax,0x00FFFFFF
        .if eax == 0xBFBBEF
            lea eax,[edx+3]
            strcpy(edx, eax)
        .endif
        .repeat
            .if PreprocessLine( ModuleInfo.tokenarray )
                ParseLine( ModuleInfo.tokenarray )
                .if ( Options.preprocessor_stdout == TRUE && Parse_Pass == PASS_1 )
                    WritePreprocessedLine( CurrSource )
                .endif
            .endif
        .until !( ModuleInfo.EndDirFound == FALSE && GetTextLine( CurrSource ) )
    .endif
    ret

ProcessFile endp

    end

