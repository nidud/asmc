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
include indirect.inc
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

ADDRSIZE16 proto watcall :byte, :byte {
    test    _1,_1
    setnz   _1
    test    _2,_2
    setnz   _2
    cmp     _1,_2
    setne   _1
    }

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

; parsing of branch instructions with imm operand is found in branch.asm

process_branch  proto __ccall :ptr code_info, :uint_t, :expr_t
ExpandLine      proto __ccall :string_t, :token_t
ExpandHllProcEx proto __ccall :string_t, :int_t, :token_t

    .data
    SegOverride asym_t 0
    LastRegOverride int_t 0 ; needed for CMPS

    .data?
    align 16

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

    ; add item to linked list of symbols

    assume rdx:dsym_t
    assume rcx:ptr symbol_queue

sym_add_table proc fastcall queue:ptr symbol_queue, item:dsym_t

    UNREFERENCED_PARAMETER(queue)
    UNREFERENCED_PARAMETER(item)

    xor eax,eax
    .if ( [rcx].head == rax )

        mov [rcx].head,rdx
        mov [rcx].tail,rdx
        mov [rdx].next,rax
        mov [rdx].prev,rax
    .else

        mov [rdx].prev,[rcx].tail
        mov [rax].dsym.next,rdx
        mov [rcx].tail,rdx
        mov [rdx].next,NULL
    .endif
    ret

sym_add_table endp


; remove an item from a symbol queue.
; this is called only for TAB_UNDEF and TAB_EXT,
; segments, groups, procs or aliases never change their state.

sym_remove_table proc fastcall uses rbx queue:ptr symbol_queue, item:dsym_t

    UNREFERENCED_PARAMETER(queue)
    UNREFERENCED_PARAMETER(item)

    ; unlink the node

    .if ( [rdx].prev )

        mov rax,[rdx].next
        mov rbx,[rdx].prev
        mov [rbx].dsym.next,rax
    .endif

    .if ( [rdx].next )

        mov rax,[rdx].prev
        mov rbx,[rdx].next
        mov [rbx].dsym.prev,rax
    .endif

    .if ( [rcx].head == rdx )
        mov [rcx].head,[rdx].next
    .endif
    .if ( [rcx].tail == rdx )
        mov [rcx].tail,[rdx].prev
    .endif
    mov [rdx].next,NULL
    mov [rdx].prev,NULL
    ret

sym_remove_table endp


    assume rcx:asym_t

; Change symbol state from SYM_EXTERNAL to SYM_INTERNAL.
; called by:
; - CreateConstant()             EXTERNDEF name:ABS           -> constant
; - CreateAssemblyTimeVariable() EXTERNDEF name:ABS           -> assembly-time variable
; - CreateLabel()                EXTERNDEF name:NEAR|FAR|PROC -> code label
; - data_dir()                   EXTERNDEF name:typed memref  -> data label
; - ProcDir()           PROTO or EXTERNDEF name:NEAR|FAR|PROC -> PROC

sym_ext2int proc __ccall sym:asym_t

    ; v2.07: GlobalQueue has been removed

    ldr rcx,sym
    .if ( !( [rcx].isproc ) && !( [rcx].ispublic ) )
        mov [rcx].ispublic,1
        AddPublicData( rcx )
    .endif
    sym_remove_table( &SymTables[TAB_EXT*symbol_queue], sym )
    mov rcx,sym
    .if !( [rcx].isproc ) ;; v2.01: don't clear flags for PROTO
        mov [rcx].first_size,0
    .endif
    mov [rcx].state,SYM_INTERNAL
    ret

sym_ext2int endp


    assume rdx:token_t

GetLangType proc __ccall i:ptr int_t, tokenarray:token_t, plang:ptr byte

    ldr  rdx,tokenarray
    ldr  rcx,i
    imul eax,[rcx],asm_tok
    add  rdx,rax
    mov  rax,[rdx].string_ptr
    mov  eax,[rax]
    or   al,0x20

    .if ( [rdx].token == T_ID && ax == 'c' )

        ; proto c :word or proc c:word

        .if ( !( [rdx-asm_tok].tokval == T_PROC && [rdx+asm_tok].token == T_COLON ) )

            mov [rdx].token,T_RES_ID
            mov [rdx].tokval,T_CCALL
            mov [rdx].bytval,1
        .endif
    .endif

    .if ( [rdx].token == T_RES_ID )

        .if ( [rdx].tokval >= T_CCALL && [rdx].tokval <= T_ASMCALL )

            inc dword ptr [rcx]
            mov al,[rdx].bytval
            mov rcx,plang
            mov [rcx],al

           .return( NOT_ERROR )
        .endif
    .endif
    .return( ERROR )

GetLangType endp

    assume rdx:nothing

; get size of a register
; v2.06: rewritten, since the sflags field
; does now contain size for GPR, STx, MMX, XMM regs.

SizeFromRegister proc fastcall registertoken:int_t

    UNREFERENCED_PARAMETER(registertoken)

    lea  rdx,SpecialTable
    imul eax,ecx,special_item
    add  rdx,rax
    mov  eax,[rdx].special_item.sflags
    and  eax,SFR_SIZMSK

    .ifz

        movzx eax,CurrWordSize
        .if !( [rdx].special_item.value & OP_SR )

            ; CRx, DRx, TRx remaining

            mov eax,4
            .if ( MODULE.Ofssize == USE64 )
                mov eax,8
            .endif
        .endif
    .endif
    ret

SizeFromRegister endp


; get size from memory type

; MT_PROC memtype is set ONLY in typedefs ( state=SYM_TYPE, typekind=TYPE_TYPEDEF)
; and makes the type a PROTOTYPE. Due to technical (obsolete?) restrictions the
; prototype data is stored in another symbol and is referenced in the typedef's
; target_type member.

SizeFromMemtype proc fastcall mem_type:uchar_t, _Ofssize:int_t, type:asym_t

    movzx eax,cl
    .if al == MT_ZWORD
        .return 64
    .endif
    and ecx,MT_SPECIAL
    .ifz
        and eax,MT_SIZE_MASK
        inc eax
       .return
    .endif

    mov ecx,edx
    .if ( ecx == USE_EMPTY )
        movzx ecx,MODULE.Ofssize
    .endif
    mov edx,2
    shl edx,cl
    .switch eax
    .case MT_NEAR
        mov eax,edx
        .endc
    .case MT_FAR
        lea eax,[rdx+2]
        .endc
    .case MT_PROC
        mov eax,edx
        mov rcx,type
        .if ( rcx && [rcx].is_far )
            add eax,2
        .endif
        .endc
    .case MT_PTR
if 0
        ; v2.16: check type; might be called so by idata_nofixup; see invoke52.asm

        mov rcx,type
        .if rcx
            xor edx,edx
            .if ( [rcx].is_far )
                add edx,2
            .endif
            mov cl,[rcx].Ofssize
            mov eax,2
            shl eax,cl
            add eax,edx
           .endc
        .endif
endif
        mov     eax,edx
        movzx   ecx,MODULE._model
        mov     edx,1
        shl     edx,cl
        and     edx,SIZE_DATAPTR
        .ifnz
            add eax,2
        .endif
        .endc
    .case MT_TYPE
        mov rcx,type
        .if rcx
            mov eax,[rcx].total_size
           .endc
        .endif
    .default
        xor eax,eax
    .endsw
    ret

SizeFromMemtype endp


; get memory type from size

    assume rcx:ptr special_item

MemtypeFromSize proc fastcall uses rbx size:int_t, ptype:ptr byte

    UNREFERENCED_PARAMETER(size)
    UNREFERENCED_PARAMETER(ptype)

    lea rbx,SpecialTable
    add rbx,T_BYTE * special_item
    .for ( : [rbx].special_item.type == RWT_STYPE : rbx += special_item )

        mov al,[rbx].special_item.bytval
        and eax,MT_SPECIAL
        .ifz
            ; the size is encoded 0-based in field mem_type

            mov al,[rbx].special_item.bytval
            .if al != MT_ZWORD
                and eax,MT_SIZE_MASK
            .endif
            inc eax
            .if eax == ecx
                mov al,[rbx].special_item.bytval
                mov [rdx],al
               .return( NOT_ERROR )
            .endif
        .endif
    .endf
    .return( ERROR )

MemtypeFromSize endp


    assume rdx:ptr code_info

OperandSize proc fastcall opnd:int_t, CodeInfo:ptr code_info

    UNREFERENCED_PARAMETER(opnd)
    UNREFERENCED_PARAMETER(CodeInfo)

    ; v2.0: OP_M8_R8 and OP_M16_R16 have the DFT bit set!

    .switch
    .case ecx == OP_NONE
        .return 0
    .case ecx == OP_M
        mov cl,[rdx].mem_type
        .return SizeFromMemtype( cl, [rdx].Ofssize, NULL )
    .case ecx & ( OP_R8 or OP_M08 or OP_I8 )
        .return 1
    .case ecx & ( OP_R16 or OP_M16 or OP_I16 or OP_SR )
        .return 2
    .case ecx & ( OP_R32 or OP_M32 or OP_I32 )
        .return 4
    .case ecx & ( OP_K or OP_R64 or OP_M64 or OP_MMX or OP_I64 )
        .return 8
    .case ecx & ( OP_I48 or OP_M48 )
        .return 6
    .case ecx & ( OP_STI or OP_M80 )
        .return 10
    .case ecx & ( OP_XMM or OP_M128 )
        .return 16
    .case ecx & ( OP_YMM or OP_M256 )
        .return 32
    .case ecx & ( OP_ZMM or OP_M512 )
        .return 64
    .case ecx & OP_RSPEC
        mov eax,4
        .if [rdx].Ofssize == USE64
            mov eax,8
        .endif
        .return
    .endsw
    .return( 0 )

OperandSize endp


    option proc:private

comp_mem16 proc fastcall reg1:int_t, reg2:int_t

    UNREFERENCED_PARAMETER(reg1)
    UNREFERENCED_PARAMETER(reg2)

    ; compare and return the r/m field encoding of 16-bit address mode;
    ; call by set_rm_sib() only;

    .if ecx == T_BX
        .return(RM_BX_SI) .if edx == T_SI ; 00
        .return(RM_BX_DI) .if edx == T_DI ; 01
    .elseif ecx == T_BP
        .return(RM_BP_SI) .if edx == T_SI ; 02
        .return(RM_BP_DI) .if edx == T_DI ; 03
    .else
        .return asmerr(2030)
    .endif
    asmerr(2029)
    ret

comp_mem16 endp


    assume rdx:asym_t

check_assume proc __ccall CodeInfo:ptr code_info, sym:asym_t, default_reg:int_t

    ; Check if an assumed segment register is found, and
    ; set CodeInfo->RegOverride if necessary.
    ; called by seg_override().
    ; at least either sym or SegOverride is != NULL.

  local reg:int_t
  local assum:asym_t

    ldr rdx,sym
    .if ( rdx && [rdx].state == SYM_UNDEFINED )
        .return
    .endif

    mov reg,GetAssume( SegOverride, rdx, default_reg, &assum )

    ; set global vars Frame and Frame_Datum

    SetFixupFrame( assum, FALSE )

    mov rdx,sym
    .if reg == ASSUME_NOTHING
        .if rdx
            .if [rdx].segm != NULL
                asmerr(2074, [rdx].name)
            .else
                mov rax,CodeInfo
                mov ecx,default_reg
                mov [rax].code_info.RegOverride,ecx
            .endif
        .else
            mov rdx,SegOverride
            asmerr(2074, [rdx].name)
        .endif
    .elseif default_reg != EMPTY
        mov rax,CodeInfo
        mov ecx,reg
        mov [rax].code_info.RegOverride,ecx
    .endif
    ret

check_assume endp


    assume rbx:ptr code_info

seg_override proc __ccall uses rbx CodeInfo:ptr code_info, seg_reg:int_t, sym:asym_t, direct:int_t

  local default_seg:int_t
  local assum:asym_t

    ; called by set_rm_sib(). determine if segment override is necessary
    ; with the current address mode;
    ; - seg_reg: register index (T_DS, T_BP, T_EBP, T_BX, ... )

    ldr     rbx,CodeInfo
    ldr     ecx,seg_reg

    mov     rax,[rbx].pinstr
    movzx   eax,[rax].instr_item.flags
    and     eax,II_ALLOWED_PREFIX

    ; don't touch segment overrides for string instructions

    .return .if ( eax == AP_REP || eax == AP_REPxx )

    .if ( [rbx].token == T_LEA )

        mov [rbx].RegOverride,ASSUME_NOTHING ;; skip segment override

        ; v2.15 use SegOverride if set. Without this modification the
        ; fixup created by LEA <reg>,addr is ignored if sym=NULL; see lea2.asm
        ; mz:  ok
        ; omf: ok (also see modification in omffixup.c)
        ; pe:  ok
        ; coff: ignores fixup ( coff relocations have to refer to a symbol )

        mov rcx,SegOverride
        .if ( rcx == NULL )
            mov rcx,sym
        .endif
        .return SetFixupFrame( rcx, FALSE )
    .endif

    .switch ecx
    .case T_BP
    .case T_EBP
    .case T_ESP

        ; todo: check why cases T_RBP/T_RSP aren't needed!

        mov default_seg,ASSUME_SS
        .endc
    .default
        mov default_seg,ASSUME_DS
    .endsw

    .if ( [rbx].RegOverride != EMPTY )

        GetOverrideAssume( [rbx].RegOverride )

        ; assume now holds assumed SEG/GRP symbol

        .if sym
            .if rax == NULL
                mov rax,sym
            .endif
            SetFixupFrame(rax, FALSE)

        .elseif direct

            ; no label attached (DS:[0]). No fixup is to be created!

            .if rax
                ; v2.12: args for ADDRSIZE must be USE16 and "> USE16". The old way
                ; caused error 'magnitude of offset exceeds 16 bit' to be displayed if
                ; module contained USE32 & USE64 segments. Todo: Most likely to be adjusted
                ; in the other ADDRSIZE() locations as well!
                mov [rbx].adrsiz,ADDRSIZE16( [rbx].Ofssize, GetSymOfssize( rax ) )
            .else

                ; v2.01: if -Zm, then use current CS offset size.
                ; This isn't how Masm v6 does it, but it matches Masm v5.

                .if MODULE.m510
                    mov [rbx].adrsiz,ADDRSIZE( [rbx].Ofssize, ModuleInfo.Ofssize )
                .else

                    ; v2.15: value of ModuleInfo.defOfssize shouldn't matter; see offset14.asm

                    mov [rbx].adrsiz,ADDRSIZE16( [rbx].Ofssize, ModuleInfo.defOfssize )
                .endif
            .endif
        .endif
    .else
        .if ( sym || SegOverride )

            check_assume( rbx, sym, default_seg )
        .endif

        ; v2.19: next if() removed, since definitely a bug; see pref67a.asm.
        ; i.e. ADDRSIZE() will clear prefix.adrsize if both arguments are > 0.
if 0
if 1
        ; v2.17: no address prefix in 64-bit or if segoverride is FLAT.
        ; todo: check if this isn't generally the wrong place to modify the adrsiz prefix.
        ; Also, the ADDRSIZE() macro should really be removed/replaced.

        .if ( sym == NULL && SegOverride && SegOverride != MODULE.flat_grp && [rbx].Ofssize != USE64 )
else
        .if ( sym == NULL && SegOverride )
endif
            GetSymOfssize( SegOverride )
            mov [rbx].adrsiz,ADDRSIZE( [rbx].Ofssize, eax )
        .endif
endif
    .endif
    .if [rbx].RegOverride == default_seg
        mov [rbx].RegOverride,ASSUME_NOTHING
    .endif
    ret

seg_override endp

    assume rbx:nothing

; prepare fixup creation
; called by:
; - idata_fixup()
; - process_branch() in branch.c
; - data_item() in data.c

set_frame proc fastcall public sym:asym_t

    UNREFERENCED_PARAMETER(sym)

    mov rax,SegOverride
    .if rax
        mov rcx,rax
    .endif
    SetFixupFrame( rcx, FALSE )
    ret

set_frame endp


; set fixup frame if OPTION OFFSET:SEGMENT is set and
; OFFSET or SEG operator was used.
; called by:
; - idata_fixup()
; - data_item()

set_frame2 proc fastcall public sym:asym_t

    UNREFERENCED_PARAMETER(sym)

    mov rax,SegOverride
    .if rax
        mov rcx,rax
    .endif
    SetFixupFrame( rcx, TRUE )
    ret

set_frame2 endp


    assume rdx:nothing
    assume rcx:nothing
    assume rsi:ptr code_info

set_rm_sib proc __ccall uses rsi rdi rbx CodeInfo:ptr code_info, CurrOpnd:uint_t,
        s:char_t, index:int_t, base:int_t, sym:asym_t

; encode ModRM and SIB byte for memory addressing.
; called by memory_operand().
; in:  ss = scale factor (00=1,40=2,80=4,C0=8)
;   index = index register (T_DI, T_ESI, ...)
;    base = base register (T_EBP, ... )
;     sym = symbol (direct addressing, displacement)
; out: CodeInfo->rm_byte, CodeInfo->sib, CodeInfo->rex

   .new temp      :int_t
   .new mod_field :uchar_t
   .new rm_field  :uchar_t = 0
   .new base_reg  :uchar_t
   .new idx_reg   :uchar_t
   .new bit3_base :uchar_t = 0
   .new bit3_idx  :uchar_t = 0
   .new rex       :uchar_t = 0

    mov rsi,CodeInfo
    imul ebx,CurrOpnd,opnd_item

    .if base == T_RIP
        mov [rsi].base_rip,1
    .endif
    .if [rsi].opnd[rbx].InsFixup ; symbolic displacement given?
        mov mod_field,MOD_10
    .elseif [rsi].opnd[rbx].data32l == 0 || base == T_RIP ; no displacement (or 0)
        mov mod_field,MOD_00
    .elseif [rsi].opnd[rbx].data32l > SCHAR_MAX || [rsi].opnd[rbx].data32l < SCHAR_MIN
        mov mod_field,MOD_10 ; full size displacement
    .else
        mov mod_field,MOD_01 ; byte size displacement
    .endif

    .if ( index == EMPTY && base == EMPTY )

        ; direct memory.
        ; clear the rightmost 3 bits

        mov [rsi].isdirect,1
        mov mod_field,MOD_00

        ; default is DS:[], DS: segment override is not needed
        seg_override( rsi, T_DS, sym, TRUE )

ifndef ASMC64
        .if ( ( [rsi].Ofssize == USE16 && [rsi].adrsiz == 0 ) ||
              ( [rsi].Ofssize == USE32 && [rsi].adrsiz == 1 ) )

            .if !InWordRange( [rsi].opnd[rbx].data32l )

                ; v2.16: accept 32-bit offset for 16-bit, i.e. "mov ax,es:[10000000h]", but
                ; generate a warning level 3 ( Masm just truncates to 16-bit ); see offset15.asm.
                ; for the case code=use32 + addr size prefix 67h + offset >= 0x10000 see offset16.asm.
                ; before v2.16, both cases were errors.

                mov rm_field,RM_D32
                xor [rsi].adrsiz,1
                .if ( Parse_Pass == PASS_1 )

                    asmerr( 7009 )
                .endif
            .else
                mov rm_field,RM_D16 ; D16=110b
            .endif
        .else
endif
            mov rm_field,RM_D32 ; D32=101b
ifndef ASMC64
            .if ( [rsi].Ofssize == USE64 )
endif
                mov rax,[rsi].opnd[rbx].InsFixup
                .if rax == NULL
                    mov rm_field,RM_SIB   ; 64-bit non-RIP direct addressing
                    mov [rsi].sib,0x25    ; IIIBBB, base=101b, index=100b
                .elseif [rax].fixup.type == FIX_OFF32
                    ; added v2.26
                    mov [rax].fixup.type,FIX_RELOFF32
                .endif
ifndef ASMC64
            .endif
        .endif
endif

    .elseif ( index == EMPTY && base != EMPTY )

        ; for SI, DI and BX: default is DS:[],
        ; DS: segment override is not needed
        ; for BP: default is SS:[], SS: segment override is not needed

        .switch base
        .case T_SI
            mov rm_field,RM_SI ; 4
            .endc
        .case T_DI
            mov rm_field,RM_DI ; 5
            .endc
        .case T_BP
            mov rm_field,RM_BP ; 6
            .if mod_field == MOD_00 && base != T_RIP
                mov mod_field,MOD_01
            .endif
            .endc
        .case T_BX
            mov rm_field,RM_BX ; 7
            .endc
        .default ; for 386 and up
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

                ; 4 is RSP/ESP or R12/R12D, which must use SIB encoding.
                ; SSIIIBBB, ss = 00, index = 100b ( no index ), base = 100b ( ESP )

                mov [rsi].sib,0x24
            .elseif base_reg == 5 && mod_field == MOD_00 && base != T_RIP

                ; 5 is [E|R]BP or R13[D]. Needs displacement

                mov mod_field,MOD_01
            .endif
            mov rex,bit3_base ; set REX_R
        .endsw
        seg_override(rsi, base, sym, FALSE)

    .elseif ( index != EMPTY && base == EMPTY )

        mov idx_reg,GetRegNo(index)
        mov al,idx_reg
        shr al,3
        mov bit3_idx,al
        and idx_reg,BIT_012

        ; mod field is 00

        mov mod_field,MOD_00

        ; s-i-b is present ( r/m = 100b )

        mov rm_field,RM_SIB

        ; scale factor, index, base ( 0x05 => no base reg )

        mov al,idx_reg
        shl al,3
        or  al,s
        or  al,0x05
        mov [rsi].sib,al
        mov al,bit3_idx
        shl al,1
        mov rex,al ; set REX_X

        ; default is DS:[], DS: segment override is not needed

        seg_override(rsi, T_DS, sym, FALSE)

        mov rax,[rsi].pinstr
        .if [rax].instr_item.evex & VX_XMMI
            mov [rsi].opc_or,GetRegNo(index)
            .if GetValueSp(index) > 16
                or [rsi].opc_or,0x40 ; YMM/ZMM
            .endif
        .endif

    .else ; base != EMPTY && index != EMPTY

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
            mov rcx,[rsi].pinstr
            .if GetValueSp(index) > 8 && [rcx].instr_item.evex & VX_XMMI
                mov [rsi].opc_or,idx_reg
                .if GetValueSp(index) > 16
                    or [rsi].opc_or,0x40 ;; YMM/ZMM
                .endif
            .else
                .return( asmerr( 2082 ) )
            .endif
        .endif
        and idx_reg,BIT_012

        .switch index
        .case T_BX
        .case T_BP
            .return .ifd comp_mem16( index, base ) == ERROR
            mov rm_field,al
            seg_override( rsi, index, sym, FALSE )
            .endc
        .case T_SI
        .case T_DI
            .return .ifd comp_mem16( base, index ) == ERROR
            mov rm_field,al
            seg_override( rsi, base, sym, FALSE )
            .endc
        .case T_RSP
        .case T_RIP
        .case T_ESP
            .return( asmerr( 2032 ) )
        .default
            .if base_reg == 5 && base != T_RIP ; v2.03: EBP/RBP/R13/R13D?
                .if mod_field == MOD_00
                    mov mod_field,MOD_01
                .endif
            .endif

            ; s-i-b is present ( r/m = 100b )

            or  rm_field,RM_SIB
            mov al,idx_reg
            shl al,3
            or  al,s
            or  al,base_reg
            mov [rsi].sib,al
            mov al,bit3_idx
            shl al,1
            add al,bit3_base
            mov rex,al ; set REX_X + REX_B
            seg_override( rsi, base, sym, FALSE )
        .endsw
    .endif

    .if base == T_RIP
        and mod_field,BIT_012
    .endif
    .if CurrOpnd == OPND2

        ; shift the register field to left by 3 bit

        mov al,rm_field
        shl al,3
        mov cl,[rsi].rm_byte
        and cl,BIT_012
        or  al,mod_field
        or  al,cl
        mov [rsi].rm_byte,al
        mov al,rex
        mov cl,al
        mov dl,al
        shr al,2
        and cl,REX_X
        and dl,1
        shl dl,2
        or al,cl
        or al,dl
        or [rsi].rex,al

    .elseif CurrOpnd == OPND1

        mov al,mod_field
        or  al,rm_field
        mov [rsi].rm_byte,al
        or [rsi].rex,rex
    .endif
    .return( NOT_ERROR )

set_rm_sib endp


; override handling
; called by
; - process_branch()
; - idata_fixup()
; - memory_operand() (CodeInfo != NULL)
; - data_item()
; 1. If it's a segment register, set CodeInfo->RegOverride.
; 2. Set global variable SegOverride if it's a SEG/GRP symbol
;    (or whatever is assumed for the segment register)

    assume rdi:token_t

segm_override proc __ccall public uses rsi rdi rbx opndx:expr_t, CodeInfo:ptr code_info

    UNREFERENCED_PARAMETER(opndx)
    UNREFERENCED_PARAMETER(CodeInfo)

    ldr rcx,opndx
    mov rsi,CodeInfo
    mov rdi,[rcx].expr.override

    .if rdi

        .if ( [rdi].token == T_REG )

            movzx ebx,GetRegNo([rdi].tokval)
            imul eax,ebx,assume_info
            lea rcx,SegAssumeTable

            .if ( [rcx+rax].assume_info.error )
                .return asmerr( 2108 )
            .endif

            ; ES,CS,SS and DS overrides are invalid in 64-bit

            .if ( rsi && [rsi].Ofssize == USE64 && ebx < ASSUME_FS )
                .return asmerr( 2202 )
            .endif

            GetOverrideAssume(ebx)

            .if ( rsi )

                ; hack: save the previous reg override value (needed for CMPS)

                mov ecx,[rsi].RegOverride
                mov LastRegOverride,ecx
                mov [rsi].RegOverride,ebx
            .endif
        .else
            SymSearch( [rdi].string_ptr )
        .endif
        .if ( rax && ( [rax].asym.state == SYM_GRP || [rax].asym.state == SYM_SEG ) )
            mov SegOverride,rax
        .endif
    .endif
    .return( NOT_ERROR )

segm_override endp


; get an immediate operand without a fixup.
; output:
; - ERROR: error
; - NOT_ERROR: ok,
;   CodeInfo->opnd_type[CurrOpnd] = OP_Ix
;   CodeInfo->data[CurrOpnd]      = value
;   CodeInfo->opsiz
;   CodeInfo->iswide

memory_operand proto __ccall private :ptr code_info, :uint_t, :expr_t, :int_t

    assume rdi:expr_t

idata_nofixup proc __ccall private uses rsi rdi rbx CodeInfo:ptr code_info, CurrOpnd:uint_t, opndx:expr_t

   .new op_type:int_t
   .new value:int_t
   .new size:int_t = 0

    UNREFERENCED_PARAMETER(opndx)
    UNREFERENCED_PARAMETER(CodeInfo)

    ldr rsi,CodeInfo
    ldr rdi,opndx
    imul ebx,CurrOpnd,opnd_item

    ; jmp/call/jxx/loop/jcxz/jecxz?

    .if IS_ANY_BRANCH( [rsi].token )
        .return( process_branch( CodeInfo, CurrOpnd, opndx ) )
    .endif

    .if ( [rdi].mem_type == MT_REAL16 )

        mov eax,4
        movzx ecx,[rsi].token

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
            .if edx == OPND2
                .if [rsi].Ofssize == USE64 && ( [rsi].opnd[OPND1].type & OP_R64 )
                    mov eax,8
                .elseif [rsi].opnd[OPND1].type & OP_R16
                    mov eax,2
                .endif
            .endif
        .endsw
        quad_resize(rdi, eax)
    .endif

    mov value,[rdi].value
    mov [rsi].opnd[rbx].data32l,eax

    ; 64bit immediates are restricted to MOV <reg>,<imm64>

    .if ( [rdi].h64_l || [rdi].h64_h ) ; magnitude > 64 bits?
        .return EmitConstError()
    .endif

    ; v2.03: handle QWORD type coercion here as well!
    ; This change also reveals an old problem in the expression evaluator:
    ; the mem_type field is set whenever a (simple) type token is found.
    ; It should be set ONLY when the type is used in conjuction with the
    ; PTR operator!
    ; current workaround: query the 'explicit' flag.

    ; use long format of MOV for 64-bit if value won't fit in a signed DWORD

    mov  edx,[rdi].hvalue
    xor  ecx,ecx
    add  eax,INT_MIN
    adc  edx,0
    test edx,edx
    seta cl

    .if ( size || [rsi].Ofssize == USE64 && [rsi].token == T_MOV &&
          CurrOpnd == OPND2 && [rsi].opnd[OPND1].type & OP_R64 &&
          ( ecx || ( [rdi].explicit &&
              ( [rdi].mem_type == MT_QWORD || [rdi].mem_type == MT_SQWORD ) ) ) )

        ; CodeInfo->iswide = 1 -- has been set by first operand already

        mov [rsi].opnd[rbx].type,OP_I64
        mov [rsi].opnd[rbx].data32h,[rdi].hvalue
       .return NOT_ERROR
    .endif

    .if ( [rdi].hvalue > 0 )

        ; COMISD mem_float,imm_float64
        ; MOV mem.field,imm64 - record7.asm

        .if ( [rsi].Ofssize >= USE32 && CurrOpnd == OPND2 && [rsi].opnd[OPND1].type == OP_M64 )

            .if ( [rsi].token == T_COMISD || ( [rsi].token == T_MOV && [rsi].mem_type == MT_BITS ) )

                mov [rsi].opnd[rbx].type,OP_I64
                mov [rsi].opnd[rbx].data32h,[rdi].hvalue
               .return( NOT_ERROR )
            .endif
        .endif
        .return EmitConstError()
    .endif

    ; v2.06: code simplified.
    ; to be fixed: the "wide" bit should not be set here!
    ; Problem: the "wide" bit isn't set in memory_operand(),
    ; probably because of the instructions which accept both
    ; signed and unsigned arguments (ADD, CMP, ... ).


    .if ( [rdi].explicit )

        ; size coercion for immediate value

        mov [rsi].constsizefixed,1

        ; don't check if size and value are compatible.

        .switch SizeFromMemtype( [rdi].mem_type, [rdi].Ofssize, [rdi].type )
        .case 1 : mov op_type,OP_I8  : .endc
        .case 2 : mov op_type,OP_I16 : .endc
        .case 4 : mov op_type,OP_I32 : .endc
        .case 8 ;; v2.27: handle asin(0.0) in 64-bit
            .if ( [rsi].Ofssize == USE64 && [rdi].mem_type == MT_REAL8 && value == 0 && [rdi].hvalue == 0 )
                mov op_type,OP_I64
                mov [rsi].opnd[rbx].data32h,0
               .endc
            .endif
        .default
            .return asmerr(2070)
        .endsw
    .else
        ; use true signed values for BYTE only!
        movsx eax,byte ptr value
        .if eax == value
            mov op_type,OP_I8
        .elseif value <= USHRT_MAX && value >= 0 - USHRT_MAX
            mov op_type,OP_I16
        .else
            mov op_type,OP_I32
        .endif
    .endif

    .switch [rsi].token
    .case T_OR
    .case T_TEST
       .endc .if ( [rdi].hvalue || MODULE.masm_compat_gencode )
        ;
        ; Optimization for mem,CONST
        ;
        ; mem16[2],0x100 --> mem8[3],0x01
        ;
        mov edx,[rsi].opnd.type
        .if ( !( [rdi].explicit ) && [rsi].Ofssize > USE16 &&
               ( edx == OP_M16 || edx == OP_M32  || edx == OP_M64 ) )

            sub rdi,expr
            mov [rsi].rex,0

            .if ( op_type == OP_I8 )

                mov [rdi].mem_type,MT_BYTE

            .else

                mov eax,[rdi+expr].value ; find a byte..
                xor ecx,ecx
                .switch
                .case ( edx != OP_M16 && !( eax & 0x00FFFFFF ) )
                    inc ecx
                    shr eax,8
                .case ( edx != OP_M16 && !( eax & 0xFF00FFFF ) )
                    inc ecx
                    shr eax,8
                .case ( edx != OP_M16 && !( eax & 0xFFFF00FF ) )
                .case ( edx == OP_M16 && !( eax & 0x00FF ) )
                    inc ecx
                    shr eax,8
                   .endc
                .endsw

                .if ( ecx )

                    mov op_type,OP_I8
                    mov [rdi].mem_type,MT_BYTE
                    add [rdi].value,ecx
                    adc [rdi].hvalue,0
                    mov [rsi].opnd[rbx].data32l,eax
                    mov [rdi+expr].value,eax
                .else
                    ;
                    ; mem64 --> mem32
                    ; mem16 --> mem32
                    ;
                    mov op_type,OP_I32
                    mov [rdi].mem_type,MT_DWORD
                .endif
            .endif
            memory_operand(rsi, 0, rdi, 0)
        .endif
        .endc
    .case T_PUSH
        .if !( [rdi].explicit )
            .if [rsi].Ofssize > USE16 && op_type == OP_I16
                mov op_type,OP_I32
            .endif
        .endif
        .if op_type == OP_I16
            mov [rsi].opsiz,OPSIZE16(rsi)
        .elseif op_type == OP_I32
            mov [rsi].opsiz,OPSIZE32(rsi)
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

    ; v2.11: set the wide-bit if a mem_type size of > BYTE is set???
    ; actually, it should only be set if immediate is second operand
    ; ( and first operand is a memory ref with a size > 1 )

    .if ( CurrOpnd == OPND2 )
        .if ( !([rsi].mem_type & MT_SPECIAL) && ( [rsi].mem_type & MT_SIZE_MASK ) )
            mov [rsi].iswide,1
        .endif
    .endif
    mov [rsi].opnd[rbx].type,op_type
   .return( NOT_ERROR )

idata_nofixup endp


; get an immediate operand with a fixup.
; output:
; - ERROR: error
; - NOT_ERROR: ok,
;   CodeInfo->opnd_type[CurrOpnd] = OP_Ix
;   CodeInfo->data[CurrOpnd]      = value
;   CodeInfo->InsFixup[CurrOpnd]  = fixup
;   CodeInfo->mem_type
;   CodeInfo->opsiz
; to be fixed: don't modify CodeInfo->mem_type here!

idata_fixup proc __ccall public uses rsi rdi rbx CodeInfo:ptr code_info, CurrOpnd:uint_t, opndx:expr_t

    local fixup_type:int_t
    local fixup_option:int_t
    local size:int_t
    local Ofssize:byte ; 1=32bit, 0=16bit offset for fixup

    mov fixup_option,OPTJ_NONE

    ldr rsi,CodeInfo
    ldr rdi,opndx
    imul ebx,CurrOpnd,opnd_item

    ; jmp/call/jcc/loopcc/jxcxz?

    .if IS_ANY_BRANCH( [rsi].token )
        .return process_branch( rsi, CurrOpnd, opndx )
    .endif

    mov [rsi].opnd[rbx].data32l,[rdi].value
    mov rcx,[rdi].sym

    .if ( [rdi].Ofssize != USE_EMPTY )
        mov Ofssize,[rdi].Ofssize
    .elseif( rcx == NULL ) ; v2.15: branch added
        segm_override( rdi, NULL )
        .if ( SegOverride )
            mov Ofssize,GetSymOfssize( SegOverride )
        .endif
    .elseif ( [rcx].asym.state == SYM_SEG || [rcx].asym.state == SYM_GRP || [rdi].inst == T_SEG )
        mov Ofssize,USE16
    .elseif ( [rdi].is_abs ) ; an (external) absolute symbol?
        mov Ofssize,USE16
    .else
        mov Ofssize,GetSymOfssize( rcx )
    .endif

    ; short works for branch instructions only

    .if ( [rdi].inst == T_SHORT )
        .return asmerr( 2070 )
    .endif

    ; the code below should be rewritten.
    ; - an address operator ( OFFSET, LROFFSET, IMAGEREL, SECTIONREL,
    ;   LOW, HIGH, LOWWORD, HIGHWORD, LOW32, HIGH32, SEG ) should not
    ;   force a magnitude, but may set a minimal magnitude - and the
    ;   fixup type, of course.
    ; - check if Codeinfo->mem_type really has to be set here!

    .if ( [rdi].explicit && !( [rdi].is_abs ) )
        mov [rsi].constsizefixed,1
        .if ( [rsi].mem_type == MT_EMPTY )
            mov [rsi].mem_type,[rdi].mem_type
        .endif
    .endif

    .if ( [rsi].mem_type == MT_EMPTY && CurrOpnd > OPND1 && [rdi].Ofssize == USE_EMPTY )

        OperandSize( [rsi].opnd[OPND1].type, rsi )

        ; may be a forward reference, so wait till pass 2

        mov ecx,[rdi].inst
        .if ( Parse_Pass > PASS_1 && [rdi].inst != EMPTY )

            .switch ecx
            .case T_SEG ; v2.04a: added
                .if ( eax && eax < 2 )
                    .return asmerr( 2022, eax, 2 )
                .endif
                .endc
            .case T_OFFSET
            .case T_LROFFSET
            .case T_IMAGEREL
            .case T_SECTIONREL
                .if ( eax && ( eax < 2 || ( Ofssize && eax < 4 ) ) )

                    movzx ecx,Ofssize
                    mov edx,2
                    shl edx,cl
                   .return asmerr( 2022, eax, edx )
                .endif
            .endsw
        .endif

        .switch eax
        .case 1
            .if ( [rdi].is_abs || ecx == T_LOW || ecx == T_HIGH || ecx == T_LOWBYTE || ecx == T_HIGHBYTE )
                mov [rsi].mem_type,MT_BYTE
            .endif
            .endc
        .case 2
            .if ( [rdi].is_abs || [rsi].Ofssize == USE16 || ecx == T_LOWWORD || ecx == T_HIGHWORD )
                mov [rsi].mem_type,MT_WORD
            .endif
            .endc
        .case 4
            mov [rsi].mem_type,MT_DWORD
            .endc
        .case 8
            .if ( Ofssize == USE64 )

                .if ( ecx == T_LOW64 || ecx == T_HIGH64 ||
                      ( [rsi].token == T_MOV && ( [rsi].opnd[OPND1].type & OP_R64 ) ) )

                    mov [rsi].mem_type,MT_QWORD

                .elseif ( ecx == T_LOW32 || ecx == T_HIGH32 )

                    ; v2.10:added; LOW32/HIGH32 in expreval.c won't set mem_type anymore.

                    mov [rsi].mem_type,MT_DWORD
                .endif
            .endif
            .endc
        .endsw
    .endif

    .if ( [rsi].mem_type == MT_EMPTY )

        .if ( [rdi].is_abs )

            .if ( [rdi].mem_type != MT_EMPTY )
                mov [rsi].mem_type,[rdi].mem_type
            .elseif ( [rsi].token == T_PUSHW ) ; v2.10: special handling PUSHW
                mov [rsi].mem_type,MT_WORD
            .else
                mov ecx,MT_WORD
                .if IS_OPER_32(rsi)
                    mov ecx,MT_DWORD
                .endif
                mov [rsi].mem_type,cl
            .endif

        .else

            movzx eax,[rsi].token

            .switch eax
            .case T_PUSHW
            .case T_PUSHD
            .case T_PUSH

                .if ( [rdi].mem_type == MT_EMPTY )
                    mov eax,[rdi].inst
                    .switch eax
                    .case EMPTY
                    .case T_LOW
                    .case T_HIGH
                    .case T_LOWBYTE
                    .case T_HIGHBYTE
                        mov [rdi].mem_type,MT_BYTE
                       .endc
                    .case T_LOWWORD  ; v2.12: added
                    .case T_HIGHWORD ; v2.12: added
                        mov [rdi].mem_type,MT_WORD
                       .endc
                    .case T_LOW32 ;; v2.10: added - low32_op() doesn't set mem_type anymore.
                    .case T_IMAGEREL
                    .case T_SECTIONREL
                        mov [rdi].mem_type,MT_DWORD
                       .endc
                    .endsw
                .endif

                ; default: push offset only
                ; for PUSH + undefined symbol, assume BYTE

                .if ( [rdi].mem_type == MT_FAR && !( [rdi].explicit ) )
                    mov [rdi].mem_type,MT_NEAR
                .endif

                ; v2.04: curly brackets added

                .if ( [rsi].token == T_PUSHW )
                    ; v2.19: calling SizeFromMemtype() for offsets isn't reliable
                    ; since mem_type is usually MT_EMPTY
                    .if ( [rdi].inst == T_OFFSET && Ofssize > USE16 && Parse_Pass == PASS_2 )
                        asmerr( 7009 )
                    .endif
                    .ifd ( SizeFromMemtype( [rdi].mem_type, Ofssize, [rdi].type ) < 2 )
                        mov [rdi].mem_type,MT_WORD
                    .endif
                .elseif ( [rsi].token == T_PUSHD )
                    .ifd ( SizeFromMemtype( [rdi].mem_type, Ofssize, [rdi].type ) < 4 )
                        mov [rdi].mem_type,MT_DWORD
                    .endif
                .endif
                .endc
            .endsw

            ; if a WORD size is given, don't override it with
            ; anything what might look better at first glance

            mov rcx,[rdi].sym

            .if ( [rdi].mem_type != MT_EMPTY )

                mov [rsi].mem_type,[rdi].mem_type
            ;
            ; v2.04: assume BYTE size if symbol is undefined
            ;
            .elseif ( [rcx].asym.state == SYM_UNDEFINED )

                mov [rsi].mem_type,MT_BYTE
                mov fixup_option,OPTJ_PUSH

            .else
                ;
                ; v2.06d: changed
                ;
                mov eax,MT_WORD
                .if Ofssize == USE64
                    mov eax,MT_QWORD
                .elseif Ofssize == USE32
                    mov eax,MT_DWORD
                .endif
                mov [rsi].mem_type,al
            .endif
        .endif
    .endif

    mov size,SizeFromMemtype( [rsi].mem_type, Ofssize, NULL )
    .switch eax
    .case 1
        mov [rsi].opnd[rbx].type,OP_I8
        mov [rsi].opsiz,FALSE ; v2.10: reset opsize is not really a good idea
       .endc                  ; - might have been set by previous operand
    .case 2: mov [rsi].opnd[rbx].type,OP_I16 : mov [rsi].opsiz,OPSIZE16(rsi) : .endc
    .case 4: mov [rsi].opnd[rbx].type,OP_I32 : mov [rsi].opsiz,OPSIZE32(rsi) : .endc
    .case 8

        ; v2.05: do only assume size 8 if the constant won't fit in 4 bytes.
        ; v2.14: don't use LONG_MAX/MIN, won't work in 64-bit unix

        mov al,[rdi].mem_type
        and eax,MT_SIZE_MASK
        xor ecx,ecx
        mov edx,[rdi].hvalue
        .if edx == ecx
            cmp [rdi].value,INT_MAX
        .endif
        setg cl
        .if edx == -1
            cmp [rdi].value,INT_MIN
        .endif
        setl ch

        .if ( ecx || ( [rdi].explicit && eax == 7 ) )

            mov [rsi].opnd[rbx].type,OP_I64
            mov [rsi].opnd[rbx].data32h,[rdi].hvalue

        .elseif Ofssize == USE64 && ( [rdi].inst == T_OFFSET || ( [rsi].token == T_MOV && ( [rsi].opnd[OPND1].type & OP_R64 ) ) )

            ; v2.06d: in 64-bit, ALWAYS set OP_I64, so "mov m64, ofs" will fail,
            ; This was accepted in v2.05-v2.06c)

            mov [rsi].opnd[rbx].type,OP_I64
            mov [rsi].opnd[rbx].data32h,[rdi].hvalue
        .else
            mov [rsi].opnd[rbx].type,OP_I32
        .endif
        mov [rsi].opsiz,OPSIZE32(rsi)
       .endc
    .endsw

    ; set fixup_type

    .if ( [rdi].inst == T_SEG )
        mov fixup_type,FIX_SEG
    .elseif ( [rsi].mem_type == MT_BYTE )
        .if ( [rdi].inst == T_HIGH || [rdi].inst == T_HIGHBYTE )
            mov fixup_type,FIX_HIBYTE
        .else
            mov fixup_type,FIX_OFF8
        .endif

    .elseif IS_OPER_32(rsi)

        .if ( [rsi].opnd[rbx].type == OP_I64 && ( [rdi].inst == EMPTY || [rdi].inst == T_OFFSET ) )

            mov fixup_type,FIX_OFF64

        .else

            .if ( size >= 4 && [rdi].inst != T_LOWWORD )

                ; v2.06: added branch for PTR16 fixup.
                ; it's only done if type coercion is FAR (Masm-compat)

                .if ( [rdi].explicit && Ofssize == USE16 && [rdi].mem_type == MT_FAR )
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

    ; v2.04: 'if' added, don't set W bit if size == 1
    ; code example:
    ;   extern x:byte
    ;   or al,x
    ; v2.11: set wide bit only if immediate is second operand.
    ; and first operand is a memory reference with size > 1

    .if ( CurrOpnd == OPND2 && size != 1 )
        mov [rsi].iswide,1
    .endif
    segm_override(rdi, NULL) ;; set SegOverride global var

    ; set frame type in variables Frame_Type and Frame_Datum for fixup creation

    .if ( MODULE.offsettype == OT_SEGMENT && ( [rdi].inst == T_OFFSET || [rdi].inst == T_SEG ) )
        set_frame2([rdi].sym)
    .else
        set_frame([rdi].sym)
    .endif

    mov [rsi].opnd[rbx].InsFixup,CreateFixup( [rdi].sym, fixup_type, fixup_option )

    .if ( [rdi].inst == T_LROFFSET )
        or [rax].fixup.fx_flag,FX_LOADER_RESOLVED
    .endif
    .if ( [rdi].inst == T_IMAGEREL && fixup_type == FIX_OFF32 )
        mov [rax].fixup.type,FIX_OFF32_IMGREL
    .endif
    .if ( [rdi].inst == T_SECTIONREL && fixup_type == FIX_OFF32 )
        mov [rax].fixup.type,FIX_OFF32_SECREL
    .endif
    .return( NOT_ERROR )

idata_fixup endp

; convert MT_PTR to MT_WORD, MT_DWORD, MT_FWORD, MT_QWORD.
; MT_PTR cannot be set explicitely (by the PTR operator),
; so this value must come from a label or a structure field.
; (above comment is most likely plain wrong, see 'PF16 ptr [reg]'!
; This code needs cleanup!

SetPtrMemtype proc __ccall uses rsi rdi rbx CodeInfo:ptr code_info, opndx:expr_t

   .new sym:asym_t

    ldr rsi,CodeInfo
    ldr rdi,opndx
    xor ebx,ebx
    mov rdx,[rdi].sym

    .if [rdi].mbr ; the mbr field has higher priority
        mov rdx,[rdi].mbr
    .endif

    .if ( [rdi].explicit && [rdi].type )

        mov rcx,[rdi].type
        mov ebx,[rcx].asym.total_size
        .if [rcx].asym.is_far
            mov [rsi].isfar,1
        .else
            mov [rsi].isfar,0
        .endif

    .elseif ( rdx )

        .if ( [rdx].asym.type )

            mov rcx,[rdx].asym.type
            mov ebx,[rcx].asym.total_size
            .if [rcx].asym.is_far
                mov [rsi].isfar,1
            .else
                mov [rsi].isfar,0
            .endif

            ; there's an ambiguity with pointers of size DWORD,
            ; since they can be either NEAR32 or FAR16

            mov al,[rcx].asym.Ofssize
            .if ( ebx == 4 && al != [rsi].Ofssize )
                mov [rdi].Ofssize,al
            .endif

        .elseif ( [rdx].asym.mem_type == MT_PTR )

            mov ecx,MT_NEAR
            .if ( [rdx].asym.is_far )
                mov ecx,MT_FAR
            .endif

            mov sym,rdx
            mov ebx,SizeFromMemtype( cl, [rdx].asym.Ofssize, NULL )
            mov [rsi].isfar,0
            mov rdx,sym
            .if [rdx].asym.is_far
                mov [rsi].isfar,1
            .endif
        .else
            .if ( [rdx].asym.isarray )

                mov ecx,[rdx].asym.total_length
                mov eax,[rdx].asym.total_size
                xor edx,edx
                div ecx
                mov ebx,eax
            .else
                mov ebx,[rdx].asym.total_size
            .endif
        .endif
    .else
        mov cl,MODULE._model
        mov eax,1
        shl eax,cl
        .if cl & SIZE_DATAPTR
            mov ebx,2
        .endif
        mov cl,MODULE.defOfssize
        mov eax,2
        shl eax,cl
        add ebx,eax
    .endif
    .if ebx
        MemtypeFromSize( ebx, &[rdi].mem_type )
    .endif
    ret

SetPtrMemtype endp


; set fields in CodeInfo:
; - mem_type
; - prefix.opsiz
; - prefix.rex REX_W
; called by memory_operand()

    assume rbx:ptr instr_item

Set_Memtype proc __ccall private uses rsi rdi rbx CodeInfo:ptr code_info, mem_type:uchar_t

    ldr rsi,CodeInfo

    .if ( [rsi].token == T_LEA )
        .return
    .endif

    ; v2.05: changed. Set "data" types only.

    movzx eax,mem_type
    .return .if ( al == MT_EMPTY || al == MT_TYPE || al == MT_NEAR || al == MT_FAR )

    mov [rsi].mem_type,al
    mov rbx,[rsi].pinstr

    .if ( [rsi].Ofssize > USE16 )

        ; if we are in use32 mode, we have to add OPSIZ prefix for
        ; most of the 386 instructions when operand has type WORD.
        ; Exceptions ( MOVSX and MOVZX ) are handled in check_size().

        .if IS_MEM_TYPE( al, WORD )

            mov [rsi].opsiz,TRUE

            ; set rex Wide bit if a QWORD operand is found (not for FPU/MMX/SSE instr).
            ; This looks pretty hackish now and is to be cleaned!
            ; v2.01: also had issues with SSE2 MOVSD/CMPSD, now fixed!

            ; v2.06: with AVX, SSE tokens may exist twice, one
            ; for "legacy", the other for VEX encoding!

        .elseif IS_MEMTYPE_SIZ( al, QWORD )

            movzx eax,[rsi].token
            .switch eax
            .case T_PUSH ; for PUSH/POP, REX_W isn't needed (no 32-bit variants in 64-bit mode)
            .case T_POP
            .case T_CMPXCHG8B
            .case T_VMPTRLD
            .case T_VMPTRST
            .case T_VMCLEAR
            .case T_VMXON
                .endc
            .default

                ; don't set REX for opcodes that accept memory operands
                ; of any size.

                movzx eax,[rbx].opclsidx
                imul  eax,eax,opnd_class
                lea   rcx,opnd_clstab

                .endc .if ( [rcx+rax].opnd_class.opnd_type[OPND1] == OP_M_ANY )

                ; don't set REX for FPU opcodes

                .endc .if ( [rbx].cpu & P_FPU_MASK )

                ; don't set REX for - most - MMX/SSE opcodes

                .if ( [rbx].cpu & P_EXT_MASK )

                    movzx eax,[rsi].token
                    .switch eax

                        ; [V]CMPSD and [V]MOVSD are also candidates,
                        ; but currently they are handled in HandleStringInstructions()

                    .case T_CVTSI2SD ; v2.06: added
                    .case T_CVTSI2SS ; v2.06: added
                    .case T_PEXTRQ   ; v2.06: added
                    .case T_PINSRQ   ; v2.06: added
                    .case T_MOVD
                    .case T_VCVTSI2SD
                    .case T_VCVTSI2SS
                    .case T_VPEXTRQ
                    .case T_VPINSRQ
                    .case T_VMOVD
                        or [rsi].rex,REX_W
                        .endc
                    .endsw
                .else
                    or [rsi].rex,REX_W
                .endif
            .endsw
        .endif
    .else
        .if IS_MEMTYPE_SIZ( al, DWORD )

            ; in 16bit mode, a DWORD memory access usually requires an OPSIZ
            ; prefix. A few instructions, which access m16:16 operands,
            ; are exceptions.

            movzx eax,[rsi].token
            .switch eax
            .case T_LDS
            .case T_LES
            .case T_LFS
            .case T_LGS
            .case T_LSS
            .case T_CALL ; v2.0: added
            .case T_JMP  ; v2.0: added
                ; in these cases, opsize does NOT need to be changed
                .endc
            .default
                mov [rsi].opsiz,TRUE
                .endc
            .endsw

            ; v2.06: added because in v2.05, 64-bit memory operands were
            ; accepted in 16-bit code

        .elseif IS_MEMTYPE_SIZ( mem_type, QWORD )

            movzx eax,[rbx].opclsidx
            imul  eax,eax,opnd_class
            lea   rcx,opnd_clstab

            .if ( [rcx+rax].opnd_class.opnd_type[OPND1] == OP_M_ANY )

            .elseif ( [rbx].cpu & ( P_FPU_MASK or P_EXT_MASK ) )

            .elseif ( [rsi].token != T_CMPXCHG8B )

                ; setting REX.W will cause an error in codegen

                or [rsi].rex,REX_W
            .endif
        .endif
    .endif
    ret

Set_Memtype endp


; process direct or indirect memory operand
; in: opndx=operand to process
; in: CurrOpnd=no of operand (0=first operand,1=second operand)
; out: CodeInfo->data[]
; out: CodeInfo->opnd_type[]

    assume rbx:nothing

memory_operand proc __ccall uses rsi rdi rbx CodeInfo:ptr code_info,
    CurrOpnd:uint_t, opndx:expr_t, with_fixup:int_t

   .new sym:asym_t
   .new index:int_t
   .new base:int_t
   .new j:int_t
   .new mem_type:byte
   .new scale_factor:uchar_t = SCALE_FACTOR_1

    UNREFERENCED_PARAMETER(opndx)
    UNREFERENCED_PARAMETER(CodeInfo)

    ldr rsi,CodeInfo
    ldr rdi,opndx
    imul ebx,CurrOpnd,opnd_item

    ; v211: use full 64-bit value

    mov [rsi].opnd[rbx].data64,[rdi].value64
    mov [rsi].opnd[rbx].type,OP_M
    mov sym,[rdi].sym

    segm_override(rdi, rsi)

    mov al,[rdi].mem_type
    mov ah,al
    and ah,MT_SPECIAL_MASK

    .if ( al == MT_PTR )

        SetPtrMemtype(rsi, rdi)

    .elseif ( ah == MT_ADDRESS )

        .if ( [rdi].Ofssize == USE_EMPTY && sym )

            mov [rdi].Ofssize,GetSymOfssize( sym )
        .endif
        mov ecx,SizeFromMemtype( [rdi].mem_type, [rdi].Ofssize, [rdi].type )
        MemtypeFromSize( ecx, &[rdi].mem_type )
    .endif

    Set_Memtype(rsi, [rdi].mem_type)
    mov rcx,[rdi].mbr

    .if ( rcx != NULL )

        .if ( [rcx].asym.mem_type == MT_TYPE && [rdi].mem_type == MT_EMPTY )

            .ifd ( MemtypeFromSize([rcx].asym.total_size, &mem_type) == NOT_ERROR )
                Set_Memtype(rsi, mem_type)
            .endif
        .endif
        mov rcx,[rdi].mbr
        .if ( [rcx].asym.state == SYM_UNDEFINED )
            mov [rsi].undef_sym,1
        .endif
    .endif

    ; instruction-specific handling

    .switch [rsi].token
    .case T_JMP
    .case T_CALL

        ; the 2 branch instructions are peculiar because they
        ; will work with an unsized label.

        ; v1.95: convert MT_NEAR/MT_FAR and display error if no type.
        ; For memory operands, expressions of type MT_NEAR/MT_FAR are
        ; call [bx+<code_label>]

        .if ( [rsi].mem_type == MT_EMPTY )

            ; with -Zm, no size needed for indirect CALL/JMP

            .if ( MODULE.m510 == FALSE && Parse_Pass > PASS_1 && [rdi].sym == NULL )
                .return asmerr( 2023 )
            .endif
            mov eax,MT_WORD
            .if ( [rsi].Ofssize == USE64 )
                mov eax,MT_QWORD
            .elseif ( [rsi].Ofssize == USE32 )
                mov eax,MT_DWORD
            .endif
            mov [rdi].mem_type,al
            Set_Memtype( rsi, al )
        .endif

        SizeFromMemtype( [rsi].mem_type, [rsi].Ofssize, NULL )

        .if ( ( eax == 1 || eax > 6 ) && ( [rsi].Ofssize != USE64 ) )
            .return asmerr( 2024 )
        .endif

            ; CALL/JMP possible for WORD/DWORD/FWORD memory operands only

        .if ( [rdi].mem_type == MT_FAR || [rsi].mem_type == MT_FWORD ||
             ( [rsi].mem_type == MT_TBYTE && [rsi].Ofssize == USE64 ) ||
             ( [rsi].mem_type == MT_DWORD &&
              ( ( [rsi].Ofssize == USE16 && [rdi].Ofssize != USE32 ) ||
                ( [rsi].Ofssize == USE32 && [rdi].Ofssize == USE16 ) ) ) )

            mov [rsi].isfar,1
        .endif
        .endc
    .endsw

    mov al,[rsi].mem_type
    and eax,MT_SPECIAL

    .ifz

        mov al,[rsi].mem_type
        and eax,0x3F

        .if ( eax == MT_ZMMWORD )

            mov [rsi].opnd[rbx].type,OP_M512

        .else

            mov al,[rsi].mem_type
            and eax,MT_SIZE_MASK
            mov ecx,[rsi].opnd[rbx].type

            .switch eax ; size is encoded 0-based
            .case  0: mov ecx,OP_M08 : .endc
            .case  1: mov ecx,OP_M16 : .endc
            .case  3: mov ecx,OP_M32 : .endc
            .case  5: mov ecx,OP_M48 : .endc
            .case  7: mov ecx,OP_M64 : .endc
            .case  9: mov ecx,OP_M80 : .endc
            .case 15: mov ecx,OP_M128: .endc
            .case 31: mov ecx,OP_M256: .endc
            .endsw
            mov [rsi].opnd[rbx].type,ecx
        .endif

    .elseif ( [rsi].mem_type == MT_BITS )

        mov rdx,[rdi].mbr
        .if ( rdx && [rdx].asym.crecord )

            mov eax,[rdx].asym.total_size
            mov ecx,[rsi].opnd[rbx].type
            .switch pascal eax
            .case  1: mov ecx,OP_M08
            .case  2: mov ecx,OP_M16
            .case  4: mov ecx,OP_M32
            .case  8: mov ecx,OP_M64
            .endsw
            mov [rsi].opnd[rbx].type,ecx
        .endif

    .elseif ( [rsi].mem_type == MT_EMPTY )

        ; v2.05: added

        movzx eax,[rsi].token

        .switch eax
        .case T_INC
        .case T_DEC

            ; jwasm v1.94-v2.04 accepted unsized operand for INC/DEC

            .if ( [rdi].sym == NULL )
                .return asmerr( 2023 )
            .endif
            .endc
        .case T_PUSH
        .case T_POP
            .return asmerr(2070) .if [rdi].mem_type == MT_TYPE
            .endc
        .case T_PUSHW ; v2.20 see pushwd.asm
            Set_Memtype( rsi, MT_WORD )
           .endc
        .case T_PUSHD ; v2.20 see pushwd.asm
            Set_Memtype( rsi, MT_DWORD )
        .endsw
    .endif

    mov rax,[rdi].base_reg
    mov ecx,EMPTY
    .if rax
        mov ecx,[rax].asm_tok.tokval
    .endif
    mov base,ecx

    mov rax,[rdi].idx_reg
    mov edx,EMPTY
    .if rax
        mov edx,[rax].asm_tok.tokval
    .endif
    mov index,edx

    ; check for base registers

    .if ( ecx != EMPTY )

        mov eax,GetValueSp(ecx)
        mov cl,[rsi].Ofssize

        .if ( ( ( eax & OP_R32 ) && cl == USE32 ) ||
              ( ( eax & OP_R64 ) && cl == USE64 ) ||
              ( ( eax & OP_R16 ) && cl == USE16 ) )
            mov [rsi].adrsiz,FALSE
        .else
            mov [rsi].adrsiz,TRUE

            ; 16bit addressing modes don't exist in long mode

            .if ( ( eax & OP_R16 ) && cl == USE64 )
                .return( asmerr( 2085 ) )
            .endif
        .endif
    .endif

    ; check for index registers

    .if ( index != EMPTY )

        mov eax,GetValueSp(index)
        mov cl,[rsi].Ofssize

        .if ( ( ( eax & OP_R32 ) && cl == USE32 ) ||
              ( ( eax & OP_R64 ) && cl == USE64 ) ||
              ( ( eax & OP_R16 ) && cl == USE16 ) )
            mov [rsi].adrsiz,FALSE
        .else
            mov [rsi].adrsiz,TRUE

            ; v2.13: check added. see expr6.asm
            ; 16bit addressing modes don't exist in 64-bit

            .if ( ( eax & OP_R16 ) && cl == USE64 )
                .return( asmerr( 2032 ) )
            .endif
        .endif

        ; v2.10: register swapping has been moved to expreval.asm, index_connect().
        ; what has remained here is the check if R/ESP is used as index reg.

        mov rax,[rsi].pinstr
        mov cl,[rax].instr_item.evex

        .if ( GetRegNo( index ) == 4 && !( cl & VX_XMMI ) )

            ; [E|R]SP

            .if ( [rdi].scale ) ; no scale must be set
                asmerr( 2031, GetResWName( index, NULL ) )
            .else
                asmerr( 2029 )
            .endif
            .return
        .endif

        ; 32/64 bit indirect addressing?

        mov cl,[rsi].Ofssize
        .if ( ( cl == USE16 && [rsi].adrsiz == 1 ) || cl == USE64  ||
              ( cl == USE32 && [rsi].adrsiz == 0 ) )

            mov eax,MODULE.curr_cpu
            and eax,P_CPU_MASK
            .if ( eax >= P_386 )

                ; scale, 0 or 1->00, 2->40, 4->80, 8->C0

                movzx eax,[rdi].scale
                .switch eax
                .case 0
                .case 1: .endc                          ; s = 00
                .case 2: mov scale_factor,SCALE_FACTOR_2: .endc ; s = 01
                .case 4: mov scale_factor,SCALE_FACTOR_4: .endc ; s = 10
                .case 8: mov scale_factor,SCALE_FACTOR_8: .endc ; s = 11
                .default ; must be * 1, 2, 4 or 8
                    .return( asmerr( 2083 ) )
                .endsw
            .else
                ; 286 and down cannot use this memory mode
                .return( asmerr( 2085 ) )
            .endif
        .else
            ; v2.01: 16-bit addressing mode. No scale possible
            .if ( [rdi].scale )
                .return asmerr( 2032 )
            .endif
        .endif
    .endif

    .if with_fixup

        .new Ofssize:byte = 0
        .new fixup_type:int_t = 0

        .if ( [rdi].is_abs )
            .if IS_ADDR32(rsi)
                inc Ofssize
            .endif
        .elseif sym
            mov Ofssize,GetSymOfssize(sym)
        .elseif SegOverride
            mov Ofssize,GetSymOfssize(SegOverride)
        .else
            mov Ofssize,[rsi].Ofssize
        .endif

        ; now set fixup_type.
        ; for direct addressing, the fixup type can easily be set by
        ; the symbol's offset size.

        .if ( base == EMPTY && index == EMPTY )

            ; v2.19: For Masm, offsets and fixups generated depend on the used segment register;
            ; if it's assumed to be flat/32-bit, offsets and fixups will also be 32-bit.

            .if ( !( [rdi].is_abs ) && sym )

               .new passume:ptr asym
                GetAssume( SegOverride, sym, ASSUME_DS, &passume )
                .if ( eax != ASSUME_NOTHING && passume )
                    mov Ofssize,GetSymOfssize( passume )
                .endif
            .endif

            mov [rsi].adrsiz,ADDRSIZE( [rsi].Ofssize, Ofssize )

            ; v2.13: also check CI->Ofssize. if current segm is 64-bit,
            ; use 32-bit rel fixups (mixed mode 64-bit mz binary) - ignore Ofssize

            .if ( Ofssize == USE64 || [rsi].Ofssize == USE64 )

                ; v2.03: override with a segment assumed != FLAT?

                .if ( [rdi].override && SegOverride != MODULE.flat_grp )
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

            .if ( Ofssize == USE64 )

                mov fixup_type,FIX_OFF32

            .elseif IS_ADDR32(rsi) ; address prefix needed?

                ; changed for v1.95. Probably more tests needed!
                ; test case:
                ;   mov eax,[rbx*2-10+offset var] ;code and var are 16bit!
                ; the old code usually works fine because HiWord of the
                ; symbol's offset is zero. However, if there's an additional
                ; displacement which makes the value stored at the location
                ; < 0, then the target's HiWord becomes <> 0.

                mov fixup_type,FIX_OFF32

            .else

                mov fixup_type,FIX_OFF16
                .if ( Ofssize && Parse_Pass == PASS_2 )

                    ; address size is 16bit but label is 32-bit.
                    ; example: use a 16bit register as base in FLAT model:
                    ;   test buff[di],cl

                    mov rax,sym
                    asmerr( 8007, [rax].asym.name )
                .endif
            .endif
        .endif

        .if ( fixup_type == FIX_OFF32 )
            .if ( [rdi].inst == T_IMAGEREL )
                mov fixup_type,FIX_OFF32_IMGREL
            .elseif ( [rdi].inst == T_SECTIONREL )
                mov fixup_type,FIX_OFF32_SECREL
            .endif
        .endif

        ; no fixups are needed for memory operands of string instructions and XLAT/XLATB.
        ; However, CMPSD and MOVSD are also SSE2 opcodes, so the fixups must be generated
        ; anyways.

        .if ( [rsi].token != T_XLAT && [rsi].token != T_XLATB )
            CreateFixup( sym, fixup_type, OPTJ_NONE )
            mov [rsi].opnd[rbx].InsFixup,rax
        .endif
    .endif

if 1
    ; v2.17: check if offset fits in 32-bit; this replaces check
    ; in process_address(), which was for indirect addressing only.

    .if ( [rdi].hvalue && ( [rdi].hvalue != -1 || [rdi].value >= 0 ) )

        .if ( [rsi].Ofssize != USE64 || [rdi].indirect )
            .return EmitConstError()
        .endif
    .endif
endif

    .ifd ( set_rm_sib( rsi, CurrOpnd, scale_factor, index, base, sym ) == ERROR )
        .return
    .endif

    ; v2.19: check if address register is 16-bit; if yes, check if the associated segment register is flat.
    ; If yes, emit error "cannot use 16-bit register with a 32-bit address". That's what Masm does, with the
    ; small difference that jwasm won't complain if the expression is behind a LEA!
    ; If the assumed segment register is 32-bit, but NOT flat, it's no error!?
    ; this check is behind set_rm_sib(), since the errors detected by that function have a higher priority.

    .if ( !with_fixup && [rsi].token != T_LEA )

        xor edi,edi
        .if ( base != EMPTY )
            .if ( GetValueSp( base ) & OP_R16 ) ; 16-bit register used for based addressing?

                lea rcx,SegAssumeTable
                mov eax,[rsi].RegOverride
                .if ( eax == EMPTY )
                    mov eax,ASSUME_DS
                    .if ( base == T_BP )
                        mov eax,ASSUME_SS
                    .endif
                .endif
                imul eax,eax,assume_info
                movzx edi,[rcx+rax].assume_info.is_flat
            .endif
        .endif
        .if ( edi == 0 && index != EMPTY )
            .if ( GetValueSp( index ) & OP_R16 ) ; 16-bit register used for based addressing?

                lea rcx,SegAssumeTable
                mov eax,[rsi].RegOverride
                .if ( eax == EMPTY )
                    mov eax,ASSUME_DS
                    .if ( index == T_BP )
                        mov eax,ASSUME_SS
                    .endif
                .endif
                imul eax,eax,assume_info
                movzx edi,[rcx+rax].assume_info.is_flat
            .endif
        .endif
        .if ( edi )
            asmerr( 2155 )
        .endif
    .endif

    ; set frame type/data in fixup if one was created

    mov rcx,[rsi].opnd[rbx].InsFixup
    .if rcx
        mov [rcx].fixup.frame_type,Frame_Type
        mov [rcx].fixup.frame_datum,Frame_Datum
    .endif
    .return( NOT_ERROR )

memory_operand endp


process_address proc __ccall uses rsi rdi rbx CodeInfo:ptr code_info,
        CurrOpnd:uint_t, opndx:expr_t

    UNREFERENCED_PARAMETER(CodeInfo)
    UNREFERENCED_PARAMETER(CurrOpnd)
    UNREFERENCED_PARAMETER(opndx)

    ; parse the memory reference operand
    ; CurrOpnd is 0 for first operand, 1 for second, ...
    ; valid return values: NOT_ERROR, ERROR

    ldr rsi,CodeInfo
    ldr rdi,opndx
    ldr ebx,CurrOpnd

    mov rcx,[rdi].sym
    .if ( [rdi].indirect ) ;; indirect register operand or stack var

        ; if displacement doesn't fit in 32-bits:
        ; Masm (both ML and ML64) just truncates.
        ; JWasm throws an error in 64bit mode and
        ; warns (level 3) in the other modes.
        ; todo: this check should also be done for direct addressing!
        ; v2.17: removed, more generic check now in memory_operand();
        ; it always emits error "constant value too large".
if 0
        .if ( [rdi].hvalue && ( [rdi].hvalue != -1 || [rdi].value >= 0 ) )
            .if ( MODULE.Ofssize == USE64 )
                .return EmitConstError()
            .endif
            asmerr( 8008, [rdi].value64 )
        .endif
endif
        mov rcx,[rdi].sym
        .if ( rcx == NULL || [rcx].asym.state == SYM_STACK )
            .return memory_operand( rsi, ebx, rdi, FALSE )
        .endif

        ; do default processing

    .elseif ( [rdi].inst != EMPTY )

        ; instr is OFFSET | LROFFSET | SEG | LOW | LOWWORD, ...
        ; v2.15 create fixup if override is given

        mov rcx,[rdi].override
        .if ( [rdi].sym == NULL && ( !rcx || [rcx].asm_tok.token == T_REG ) )
            .return idata_nofixup( rsi, ebx, rdi )
        .else

            ; allow "lea <reg>, [offset <sym>]"

            .if ( [rsi].token == T_LEA && [rdi].inst == T_OFFSET )
                .return memory_operand( rsi, ebx, rdi, TRUE )
            .endif
            .return idata_fixup( rsi, ebx, rdi )
        .endif

    .elseif ( [rdi].sym == NULL ) ; direct operand without symbol

        .if ( [rdi].override != NULL )

            ; direct absolute memory without symbol.
            ; DS:[0] won't create a fixup, but
            ; DGROUP:[0] will create one! */
            ; for 64bit, always create a fixup, since RIP-relative addressing is used
            ; v2.11: don't create fixup in 64-bit.

            mov rcx,[rdi].override
            .if ( [rcx].asm_tok.token == T_REG || [rsi].Ofssize == USE64 )
                .return memory_operand( rsi, ebx, rdi, FALSE )
            .else
                .return memory_operand( rsi, ebx, rdi, TRUE )
            .endif
        .else
            .return idata_nofixup( rsi, ebx, rdi )
        .endif

    .elseif ( [rcx].asym.state == SYM_UNDEFINED && !( [rdi].explicit ) )

        ; undefined symbol, it's not possible to determine
        ; operand type and size currently. However, for backpatching
        ; a fixup should be created.

        ; assume a code label for branch instructions!

        .if IS_ANY_BRANCH( [rsi].token )
            .return process_branch( rsi, ebx, rdi )
        .endif

        .switch [rsi].token
        .case T_PUSH
        .case T_PUSHW
        .case T_PUSHD

            ; v2.0: don't assume immediate operand if cpu is 8086

            mov eax,MODULE.curr_cpu
            and eax,P_CPU_MASK
            .if eax > P_86
                .return idata_fixup( rsi, ebx, rdi )
            .endif
            .endc
        .default

            ; v2.04: if operand is the second argument (and the first is NOT
            ; a segment register!), scan the
            ; instruction table if the instruction allows an immediate!
            ; If so, assume the undefined symbol is a constant.

            mov eax,[rsi].opnd[OPND1].type
            and eax,OP_SR

            .if ( ebx == OPND2 && eax == 0 )

                mov rcx,[rsi].pinstr
                .repeat
                    movzx eax,[rcx].instr_item.opclsidx
                    imul eax,eax,opnd_class
                    lea rdx,opnd_clstab
                    .if ( [rdx+rax].opnd_class.opnd_type[4] & OP_I )
                        .return idata_fixup( rsi, ebx, rdi )
                    .endif
                    add rcx,instr_item
                .until ( [rcx].instr_item.flags & II_FIRST )
            .endif

            ; v2.10: if current operand is the third argument, always assume an immediate

            .if ( ebx == OPND3 )
                .return idata_fixup(rsi, ebx, rdi)
            .endif
        .endsw

        ; do default processing

    .elseif ( [rcx].asym.state == SYM_SEG || [rcx].asym.state == SYM_GRP )

        ; SEGMENT and GROUP symbol is converted to SEG symbol
        ; for next processing

        mov [rdi].inst,T_SEG
        .return idata_fixup( rsi, ebx, rdi )

    .else

        ; symbol external, but absolute?

        .if ( [rdi].is_abs )
            .return idata_fixup( rsi, ebx, rdi )
        .endif

        ; CODE location is converted to OFFSET symbol

        .if ( [rdi].mem_type == MT_NEAR || [rdi].mem_type == MT_FAR )

            xor eax,eax ; v2.30 - mov mem,&proc
            mov rcx,[rdi].type_tok

            .if ( rcx && [rsi].Ofssize == USE64 )
                .if ( [rcx-asm_tok].asm_tok.token == '&' )
                    inc eax
                .endif
            .endif
            .if ( eax || [rsi].token == T_LEA || [rdi].mbr != NULL ) ; structure field?
                .return memory_operand( rsi, ebx, rdi, TRUE )
            .endif
            .return idata_fixup( rsi, ebx, rdi )
        .endif
    .endif

    ; default processing: memory with fixup

    memory_operand( rsi, ebx, rdi, TRUE )
    ret

process_address endp


; Handle constant operands.
; These never need a fixup. Externals - even "absolute" ones -
; are always labeled as EXPR_ADDR by the expression evaluator.

process_const proc fastcall uses rbx CodeInfo:ptr code_info, CurrOpnd:uint_t, opndx:expr_t

    UNREFERENCED_PARAMETER(CodeInfo)
    UNREFERENCED_PARAMETER(CurrOpnd)

    ; v2.11: don't accept an empty string

    ldr rbx,opndx
    .if ( [rbx].expr.mem_type & MT_FLOAT )
        mov [rbx].expr.float_tok,NULL
    .endif

    mov rax,[rbx].expr.quoted_string
    .if ( rax && [rax].asm_tok.stringlen == 0 )
        .return asmerr( 2047 )
    .endif

    ; optimization: skip <value> if it is 0 and instruction
    ; is RET[W|D|N|F].
    ; v2.06: moved here and checked the opcode directly, so
    ; RETD and RETW are also handled.

    mov rax,[rcx].code_info.pinstr
    mov al,[rax].instr_item.opcode
    and eax,0xf7

    .if ( eax == 0xc2 && edx == OPND1 && [rbx].expr.value == 0 )
        .return( NOT_ERROR )
    .endif
    .return idata_nofixup( rcx, edx, rbx )

process_const endp


process_register proc __ccall uses rsi rdi rbx CodeInfo:ptr code_info, CurrOpnd:uint_t,
        opndx:expr_t, index:uint_t

; parse and encode direct register operands. Modifies:
; - CodeInfo->opnd_type
; - CodeInfo->rm_byte (depending on CurrOpnd)
; - CodeInfo->iswide
; - CodeInfo->x86hi_used/x64lo_used
; - CodeInfo->rex

  local regtok:int_t
  local regno:int_t
  local flags:uint_t

    ldr rsi,CodeInfo
    ldr rdi,opndx

    imul ebx,CurrOpnd,opnd_item
    imul eax,CurrOpnd,expr

    mov rax,[rdi+rax].base_reg
    mov regtok,[rax].asm_tok.tokval
    movzx eax,GetRegNo(eax)
    mov regno,eax

    ; the register's "OP-flags" are stored in the 'value' field

    mov flags,GetValueSp(regtok)
    mov [rsi].opnd[rbx].type,eax

    .if ( ( ( eax == OP_XMM || eax == OP_YMM ) && regno > 15 ) || eax & OP_ZMM )
        or [rsi].prefix,PREFIX_EVEX
        .if eax == OP_ZMM
            or [rsi].vflags,VX_ZMM
        .endif
        .if regno > 15
            mov ecx,index
            mov edx,1
            shl edx,cl
            .if eax == OP_ZMM && regno > 23
                or edx,VX_ZMM24
            .endif
            or [rsi].vflags,dl
        .elseif eax == OP_ZMM && regno > 7
            or [rsi].vflags,VX_ZMM8
        .endif
    .endif

    .if ( eax & OP_R8 )
        ;
        ; it's probably better to not reset the wide bit at all
        ;
        .if ( eax != OP_CL ) ; problem: SHL AX|AL, CL
            mov [rsi].iswide,0
        .endif

        .if ( [rsi].Ofssize == USE64 && regno >=4 && regno <= 7 )

            mov eax,regtok
            imul eax,eax,special_item
            lea rcx,SpecialTable

            .if ( [rcx+rax].special_item.cpu == P_86 )
                mov [rsi].x86hi_used,1 ;; it's AH,BH,CH,DH
            .else
                mov [rsi].x64lo_used,1 ;; it's SPL,BPL,SIL,DIL
            .endif
        .endif

        imul eax,regno,assume_info
        mov ecx,RL_ERROR
        .if ( regtok >= T_AH && regtok <= T_BH )
            mov ecx,RH_ERROR
        .endif

        lea rdx,StdAssumeTable
        .if ( [rdx+rax].assume_info.error & cl )
            .return asmerr( 2108 )
        .endif

    .elseif ( eax & OP_R ) ; 16-, 32- or 64-bit GPR?

        mov [rsi].iswide,1
        imul ecx,regno,assume_info
        and al,OP_R

        lea rdx,StdAssumeTable
        .if ( [rdx+rcx].assume_info.error & al )
            .return asmerr( 2108 )
        .endif

        .if ( flags & OP_R16 )
            .if ( [rsi].Ofssize > USE16 )
                mov [rsi].opsiz,TRUE
            .endif
        .elseif ( [rsi].Ofssize == USE16 )
            mov [rsi].opsiz,TRUE
        .endif

    .elseif ( eax & OP_SR )

        .if ( regno == 1 ) ; 1 is CS
            ;
            ; POP CS is not allowed
            ;
            .if ( [rsi].token == T_POP )
                .return asmerr( 2008, "POP CS" )
            .endif
        .endif
if 1
        ; v2.15: emit warning if PUSHD/PUSHW are used and size doesn't match current mode.
        ; emitting a size prefix (0x66) silently would break masm compatibility.

        .if ( Parse_Pass == PASS_2 )
            .if ( [rsi].token == T_PUSHD && [rsi].Ofssize == USE16 ||
                  [rsi].token == T_PUSHW && [rsi].Ofssize > USE16 )
                asmerr( 8021 )
            .endif
        .endif
endif

    .elseif ( eax & OP_ST )

        imul eax,CurrOpnd,expr
        mov regno,[rdi+rax].st_idx

        .if ( eax > 7 ) ; v1.96: index check added
            .return asmerr( 2032 )
        .endif

        or [rsi].rm_byte,al
        .if ( eax != 0 )
            mov [rsi].opnd[rbx].type,OP_ST_REG
        .endif
        ;
        ; v2.06: exit, rm_byte is already set.
        ;
        .return NOT_ERROR

    .elseif ( eax & OP_RSPEC ) ; CRx, DRx, TRx

        .if ( [rsi].token != T_MOV )

            .if ( [rsi].token == T_PUSH )
                .return asmerr( 2151 )
            .endif
            .return asmerr( 2070 )
        .endif

        ; v2.04: previously there were 3 flags, OP_CR, OP_DR and OP_TR.
        ; this was summoned to one flag OP_RSPEC to free 2 flags, which
        ; are needed if AVC ( new YMM registers ) is to be supported.
        ; To distinguish between CR, DR and TR, the register number is
        ; used now: CRx are numbers 0-F, DRx are numbers 0x10-0x1F and
        ; TRx are 0x20-0x2F.

        .if ( regno >= 0x20 ) ; TRx?

            or [rsi].opc_or,0x04

            ; TR3-TR5 are available on 486-586
            ; TR6+TR7 are available on 386-586
            ; v2.11: simplified.

            mov eax,MODULE.curr_cpu
            and eax,P_CPU_MASK

            .if ( eax >= P_686 )

                mov eax,3
                .if ( regno > 0x25 )
                    mov eax,6
                .endif
                mov ecx,5
                .if ( regno > 0x25 )
                    mov ecx,7
                .endif
                .return asmerr( 3004, eax, ecx )
            .endif

        .elseif ( regno >= 0x10 ) ; DRx?

            or [rsi].opc_or,0x01
        .endif
        and regno,0x0F
    .endif

    ; if it's a x86-64 register (SIL, R8W, R8D, RSI, ...

    imul eax,regtok,special_item

    lea rcx,SpecialTable
    movzx eax,[rcx+rax].special_item.cpu
    and eax,P_CPU_MASK

    .if ( eax == P_64 )
        or [rsi].rex,0x40
        .if ( flags & OP_R64 )
            or [rsi].rex,REX_W
        .endif
    .endif

    .if ( CurrOpnd == OPND1 )

        ; the first operand
        ; r/m is treated as a 'reg' field

        mov eax,regno
        mov ecx,eax
        and eax,8
        shr eax,3
        or [rsi].rex,al ;; set REX_B
        and ecx,BIT_012
        or  ecx,MOD_11

        ; fill the r/m field

        or [rsi].rm_byte,cl

    .else

        ; the second operand
        ; XCHG can use short form if op1 is AX/EAX/RAX

        .if ( [rsi].token == T_XCHG && [rsi].opnd[OPND1].type & OP_A &&
              !( [rsi].opnd[OPND1].type & OP_R8 ) )

            mov eax,regno
            mov ecx,eax
            and eax,8
            shr eax,3
            or  [rsi].rex,al ; set REX_B
            and ecx,BIT_012
            and [rsi].rm_byte,BIT_67
            or  [rsi].rm_byte,cl

        .else

            ; fill reg field with reg

            mov eax,regno
            mov ecx,eax
            and eax,8
            shr eax,1
            or  [rsi].rex,al ;; set REX_R
            and ecx,BIT_012
            and [rsi].rm_byte,not BIT_345
            shl ecx,3
            or  [rsi].rm_byte,cl
        .endif
    .endif
    .return( NOT_ERROR )

process_register endp


; v2.14: check if variable is accessible thru ES

IsAccessible proc fastcall uses rbx sym:ptr asym, sr:int_t

    imul edx,edx,assume_info
    lea  rax,SegAssumeTable
    mov  rbx,[rdx+rax].assume_info.symbol

    .if ( [rcx].asym.segm && rbx )
        .if ( [rcx].asym.segm != rbx )
            .if ( GetGroup( rcx ) != rbx )
                .return( FALSE )
            .endif
        .endif
    .endif
    .return( TRUE )

IsAccessible endp

; special handling for string instructions
; CMPS[B|W|D|Q]
;  INS[B|W|D]
; LODS[B|W|D|Q]
; MOVS[B|W|D|Q]
; OUTS[B|W|D]
; SCAS[B|W|D|Q]
; STOS[B|W|D|Q]
; the peculiarity is that these instructions ( optionally )
; have memory operands, which aren't used for code generation
; <opndx> contains the last operand.


HandleStringInstructions proc __ccall uses rsi rdi rbx CodeInfo:ptr code_info, opndx:expr_t

  local opndidx:int_t
  local op_size:int_t

    mov opndidx,OPND1
    ldr rsi,CodeInfo
    ldr rdi,opndx

    movzx eax,[rsi].token
    .switch eax
    .case T_VCMPSD
    .case T_CMPSD

        ; filter SSE2 opcode CMPSD

        .if [rsi].opnd[OPND1].type & (OP_XMM or OP_MMX)
            ;
            ; v2.01: QWORD operand for CMPSD/MOVSD may have set REX_W!
            ;
            and [rsi].rex,not REX_W
           .return
        .endif

        ; fall through

    .case T_CMPS
    .case T_CMPSB
    .case T_CMPSW
    .case T_CMPSQ

        ; v2.14: reject segment != ES for second op if symbolic

        .if ( [rsi].opnd[OPNI2].type != OP_NONE && [rdi+expr].override == NULL && [rdi+expr].sym )
            .ifd ( !IsAccessible( [rdi+expr].sym, ASSUME_ES ) )

                asmerr( 2070 )
               .endc
            .endif
        .endif

        ; cmps allows prefix for the first operand (=source) only

        .if ( [rsi].RegOverride != EMPTY )

            .if ( [rdi+expr].override != NULL )

                .if ( [rsi].RegOverride == ASSUME_ES )

                    ; content of LastRegOverride is valid if
                    ; CodeInfo->RegOverride is != EMPTY.

                    .if ( LastRegOverride == ASSUME_DS )
                        mov [rsi].RegOverride,EMPTY
                    .else
                        mov [rsi].RegOverride,LastRegOverride
                    .endif
                .else
                    asmerr( 2070 )
                .endif
            .endif

        .elseif ( [rsi].opnd[OPND1].type != OP_NONE && ; v2.14
                  [rdi].override == NULL && [rdi].sym )

            check_assume( rsi, [rdi].sym, ASSUME_DS )
        .endif
        .if ( [rsi].RegOverride == ASSUME_DS )

            ; prefix for first operand?

            mov [rsi].RegOverride,EMPTY
        .endif
        .endc

    .case T_MOVSD
    .case T_VMOVSD

        ; filter SSE2 opcode MOVSD

        .if ( [rsi].opnd[OPND1].type & ( OP_XMM or OP_MMX ) ||
              [rsi].opnd[OPNI2].type & ( OP_XMM or OP_MMX ) )

            ; v2.01: QWORD operand for CMPSD/MOVSD may have set REX_W!

            and [rsi].rex,not REX_W
           .return
        .endif

        ; fall through

    .case T_MOVS
    .case T_MOVSB
    .case T_MOVSW
    .case T_MOVSQ

        ; v2.14: reject segment != ES for second op if symbolic

        .if ( [rsi].opnd[OPND1].type != OP_NONE && [rdi].override == NULL && [rdi].sym )
            .ifd ( !IsAccessible( [rdi].sym, ASSUME_ES ) )

                asmerr( 2070 )
               .endc
            .endif
        .endif

        ; MOVSx allows prefix for the second operand (=source) only.
        ; there's only one place to store the register override in CodeInfo,
        ; so it's a problem if both operands have an override; to be improved.

        .if ( [rsi].RegOverride != ASSUME_NOTHING )

            ; v2.14: destination must be ES:

            mov rcx,[rdi].override
            .if ( rcx && [rcx].asm_tok.token == T_REG && [rcx].asm_tok.tokval != T_ES )

                asmerr( 2070 )

            .elseif ( [rdi+expr].override == NULL )

                ; v2.14: "if block" added

                .if ( [rsi].RegOverride == ASSUME_ES )
                    mov [rsi].RegOverride,ASSUME_NOTHING
                .else
                    asmerr( 2070 )
                .endif
            .endif

        .elseif ( [rsi].opnd[OPNI2].type != OP_NONE && ; v2.14
                  [rdi+expr].override == NULL && [rdi+expr].sym )

            check_assume( rsi, [rdi+expr].sym, ASSUME_DS )
        .endif
        .if ( [rsi].RegOverride == ASSUME_DS )
            mov [rsi].RegOverride,ASSUME_NOTHING
        .endif
        .endc

    .case T_OUTS
    .case T_OUTSB
    .case T_OUTSW
    .case T_OUTSD

        ; v2.14

        .if ( [rsi].opnd[OPNI2].type != OP_NONE && [rdi+expr].override == NULL && [rdi+expr].sym )
            check_assume( rsi, [rdi+expr].sym, ASSUME_DS )
        .endif

        ; v2.01: remove default DS prefix

        .if ( [rsi].RegOverride == ASSUME_DS )
            mov [rsi].RegOverride,EMPTY
        .endif
        mov opndidx,OPND2
       .endc

    .case T_LODS
    .case T_LODSB
    .case T_LODSW
    .case T_LODSD
    .case T_LODSQ

        ; v2.14

        .if ( [rsi].opnd[OPND1].type != OP_NONE && [rdi].override == NULL && [rdi].sym )
            check_assume( rsi, [rdi].sym, ASSUME_DS )
        .endif

        ; v2.10: remove unnecessary DS prefix ( Masm-compatible )

        .if ( [rsi].RegOverride == ASSUME_DS )
            mov [rsi].RegOverride,EMPTY
        .endif
        .endc

    .default ; INS[B|W|D], SCAS[B|W|D|Q], STOS[B|W|D|Q]
             ; INSx, SCASx and STOSx don't allow any segment prefix != ES
             ; for the memory operand.

        ; v2.14: check added to reject invalid segment assumes

        .if ( [rsi].opnd[OPND1].type != OP_NONE && [rdi].override == NULL && [rdi].sym )
            .ifd ( !IsAccessible( [rdi].sym, ASSUME_ES ) )
                asmerr( 2070 )
               .endc
            .endif
        .endif

        .if ( [rsi].RegOverride != ASSUME_NOTHING )
            .if ( [rsi].RegOverride == ASSUME_ES )
                mov [rsi].RegOverride,EMPTY
            .else
                asmerr( 2070 )
            .endif
        .endif
    .endsw

    mov   ecx,opndidx
    shl   ecx,2
    mov   rax,[rsi].pinstr
    movzx eax,[rax].instr_item.opclsidx
    imul  eax,eax,opnd_class

    lea   rdx,opnd_clstab
    add   rdx,rax

    .if ( [rdx].opnd_class.opnd_type[rcx] == OP_NONE )

        mov [rsi].iswide,0
        mov [rsi].opsiz,FALSE
    .endif

    ; if the instruction is the variant without suffix (MOVS, LODS, ..),
    ; then use the operand's size to get further info.

    mov ebx,opndidx
    imul ebx,ebx,opnd_item

    .if ( [rdx].opnd_class.opnd_type[rcx] != OP_NONE && [rsi].opnd[rbx].type != OP_NONE )

        mov op_size,OperandSize( [rsi].opnd[rbx].type, rsi )

        ; v2.06: added. if memory operand has no size

        .if ( op_size == 0 )

            mov rdx,[rsi].opnd[rbx].InsFixup
            xor eax,eax

            .if ( rdx )
                mov rcx,[rdx].fixup.sym
                .if ( [rcx].asym.state != SYM_UNDEFINED )
                    inc eax
                .endif
            .endif
            .if ( rdx == NULL || eax )
                asmerr( 2023 )
            .endif
            mov op_size,1 ; assume shortest format
        .endif
        .switch op_size
        .case 1
            mov [rsi].iswide,0
            mov [rsi].opsiz,FALSE
           .endc
        .case 2
            mov [rsi].iswide,1
            xor eax,eax
            .if ( [rsi].Ofssize )
                inc eax
            .endif
            mov [rsi].opsiz,al
           .endc
        .case 4
            mov [rsi].iswide,1
            xor eax,eax
            .if ( ![rsi].Ofssize )
                inc eax
            .endif
            mov [rsi].opsiz,al
           .endc
        .case 8
            .if ( [rsi].Ofssize == USE64 )

                mov [rsi].iswide,1
                mov [rsi].opsiz,FALSE
                mov [rsi].rex,REX_W
            .endif
            .endc
        .endsw
    .endif
    ret

HandleStringInstructions endp


check_size proc __ccall uses rsi rdi rbx CodeInfo:ptr code_info, opndx:expr_t

; - use to make sure the size of first operand match the size of second operand;
; - optimize MOV instruction;
; - opndx contains last operand
; todo: BOUND second operand check ( may be WORD/DWORD or DWORD/QWORD ).
; tofix: add a flag in instr_table[] if there's NO check to be done.

  local op1:int_t
  local op2:int_t
  local rc:int_t
  local op1_size:int_t
  local op2_size:int_t

    UNREFERENCED_PARAMETER(CodeInfo)
    UNREFERENCED_PARAMETER(opndx)

    ldr rsi,CodeInfo
    ldr rdi,opndx

    mov ecx,[rsi].opnd[OPND1].type
    mov edx,[rsi].opnd[OPNI2].type
    mov rc,NOT_ERROR

    mov op1,ecx
    mov op2,edx

    movzx eax,[rsi].token
    .switch eax
    .case T_HRESET ; added v2.34.59
        .if ( ecx != OP_I8 && edx != OP_EAX )
            jmp def_check
        .endif
        .endc
    .case T_IN

        .if ( op2 == OP_DX )

            ; wide and size is NOT determined by DX, but
            ; by the first operand, AL|AX|EAX

            .switch ecx
            .case OP_AX
                .endc
            .case OP_AL
                mov [rsi].iswide,0 ; clear w-bit
            .case OP_EAX
                .if ( [rsi].Ofssize )
                    mov [rsi].opsiz,FALSE
                .endif
                .endc
            .endsw
        .endif
        .endc
    .case T_OUT
        .if ( ecx == OP_DX )
            .switch edx
            .case OP_AX
                .endc
            .case OP_AL
                mov [rsi].iswide,0 ; clear w-bit
            .case OP_EAX
                .if [rsi].Ofssize
                    mov [rsi].opsiz,FALSE
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

        ; v2.11: added

        mov rcx,[rdi].sym
        .if ( [rsi].opnd[OPND1].type == OP_M && !( [rsi].undef_sym ) &&
              ( rcx == NULL || [rcx].asym.state != SYM_UNDEFINED ) )

            asmerr( 2023 )
            mov rc,eax
           .endc
        .endif

        ; v2.0: if second argument is a forward reference,
        ; change type to "immediate 1"

        mov rcx,[rdi+expr].sym
        .if ( [rdi+expr].kind == EXPR_ADDR && Parse_Pass == PASS_1 &&
              !( [rdi+expr].indirect ) && rcx && [rcx].asym.state == SYM_UNDEFINED )

            mov [rsi].opnd[OPNI2].type,OP_I8
            mov [rsi].opnd[OPNI2].data32l,1
        .endif

        ; v2.06: added (because if first operand is memory, wide bit
        ; isn't set!)

        .if ( OperandSize( op1, rsi ) > 1 )
            mov [rsi].iswide,1
        .endif

        ; v2.06: makes the OP_CL_ONLY case in codegen.c obsolete

        .if ( op2 == OP_CL )

            ; CL is encoded in bit 345 of rm_byte, but we don't need it
            ; so clear it here

            and [rsi].rm_byte,NOT_BIT_345
        .endif
        .endc
    .case T_LDS
    .case T_LES
    .case T_LFS
    .case T_LGS
    .case T_LSS
        OperandSize( ecx, rsi )
        add eax,2           ; add 2 for the impl. segment register
        mov op1_size,eax
        mov op2_size,OperandSize( op2, rsi )
        .if ( op2_size != 0 && op1_size != op2_size )
            .return asmerr( 2024 )
        .endif
        .endc
    .case T_ENTER
        .endc
    .case T_MOVSX
    .case T_MOVZX
        mov [rsi].iswide,0
        mov op1_size,OperandSize(op1, rsi)
        mov op2_size,OperandSize(op2, rsi)
        .if ( op2_size == 0 && Parse_Pass == PASS_2 )
            .if ( op1_size == 2 )
                asmerr( 8019, "BYTE" )
            .else
                asmerr( 2023 )
            .endif
        .endif
        .switch op1_size
        .case 8
        .case 4
            .if ( op2_size < 2 )
                ;
            .elseif ( op2_size == 2 )
                mov [rsi].iswide,1
            .else
                mov rc,asmerr( 2024 )
            .endif
            xor eax,eax
            cmp [rsi].Ofssize,al
            sete al
            mov [rsi].opsiz,al
           .endc
        .case 2
            .if ( op2_size >= 2 )
                mov rc,asmerr( 2024 )
            .endif
            xor eax,eax
            cmp [rsi].Ofssize,al
            setne al
            mov [rsi].opsiz,al
           .endc
        .default

            ; op1 must be r16/r32/r64

            mov rc,asmerr( 2024 )
        .endsw
        .endc
    .case T_MOVSXD
        .endc
    .case T_ARPL ; v2.06: new, avoids the OP_R16 hack in codegen.c
        mov [rsi].opsiz,0
        jmp def_check
    .case T_LAR ; v2.04: added
    .case T_LSL ; 19-sep-93
        and edx,OP_M
        .if ( MODULE.Ofssize != USE64 || ( edx == 0 ) )
            jmp def_check
        .endif

        ; in 64-bit, if second argument is memory operand,
        ; ensure it has size WORD ( or 0 if a forward ref )

        mov op2_size,OperandSize(op2, rsi)
        .return asmerr(2024) .if eax != 2 && eax != 0

        ; the opsize prefix depends on the FIRST operand only!

        mov op1_size,OperandSize(op1, rsi)
        .if ( eax != 2 )
            mov [rsi].opsiz,FALSE
        .endif
        .endc
    .case T_IMUL ; v2.06: check for 3rd operand must be done here
        .if ( [rsi].opnd[OPNI3].type != OP_NONE )

            mov op1_size,OperandSize(op1, rsi)
            OperandSize([rsi].opnd[OPNI3].type, rsi)

            ; the only case which must be checked here
            ; is a WORD register as op1 and a DWORD immediate as op3

            .if ( op1_size == 2 && eax > 2 )
                mov rc,asmerr( 2022, op1_size, eax )
                .endc
            .endif
            .if ( [rsi].opnd[OPNI3].type & ( OP_I16 or OP_I32 ) )
                mov eax,OP_I32
                .if ( op1_size == 2 )
                    mov eax,OP_I16
                .endif
                mov [rsi].opnd[OPNI3].type,eax
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
        .if ( edx == OP_M && ( [rdi+expr].indirect ) )
            .return asmerr( 2023 )
        .endif
        .endc

    .case T_VMOVDDUP
        .endc .if !( ecx & OP_YMM )

        ; fall through

    .case T_VPERM2F128 ; has just one memory variant, and VX_L isnt set
        .if ( edx == OP_M )
            or [rsi].opnd[OPNI2].type,OP_M256
        .endif
        .endc

    .case T_CRC32

        ; v2.02: for CRC32, the second operand determines whether an
        ; OPSIZE prefix byte is to be written.

        mov op2_size,OperandSize(op2, rsi)
        .if ( eax < 2 )
            mov [rsi].opsiz,FALSE
        .elseif ( eax == 2 )
            xor eax,eax
            cmp [rsi].Ofssize,al
            setne al
            mov [rsi].opsiz,al
        .else
            xor eax,eax
            cmp [rsi].Ofssize,al
            sete al
            mov [rsi].opsiz,al
        .endif
        .endc
    .case T_MOVD
        .endc
    .case T_MOV
        .if ( op1 & OP_SR ) ; segment register as op1?
            mov op2_size,OperandSize(op2, rsi)
            .if ( eax == 2 || eax == 4 || ( eax == 8 && MODULE.Ofssize == USE64 ) )
                .return NOT_ERROR
            .endif
        .elseif ( op2 & OP_SR )
            mov op1_size,OperandSize(op1, rsi)
            .if ( eax == 2 || eax == 4 || ( eax == 8 && MODULE.Ofssize == USE64 ) )
                .return NOT_ERROR
            .endif
        .elseif ( ( op1 & OP_M ) && ( op2 & OP_A ) ) ; 1. operand memory reference, 2. AL|AX|EAX|RAX?

            .if !( [rsi].isdirect )

                ; address mode is indirect.
                ; don't use the short format (opcodes A0-A3) - it exists for direct
                ; addressing only. Reset OP_A flag!

                and [rsi].opnd[OPNI2].type,not OP_A

            .elseif ( [rsi].Ofssize == USE64 )
ifdef _WIN64
                mov rax,0x80000000
                mov rdx,0xffffffff80000000
                .if ( [rsi].opnd[OPND1].data64 < rax ||
                      [rsi].opnd[OPND1].data64 >= rdx )
else
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
endif

                    ; for 64bit, opcodes A0-A3 ( direct memory addressing with AL/AX/EAX/RAX )
                    ; are followed by a full 64-bit moffs. This is only used if the offset won't fit
                    ; in a 32-bit signed value.

                    and [rsi].opnd[OPNI2].type,not OP_A
                .endif
            .endif

        .elseif ( ( op1 & OP_A ) && ( op2 & OP_M ) ) ; 2. operand memory reference, 1. AL|AX|EAX|RAX?

            .if ( !( [rsi].isdirect ) )

                and [rsi].opnd[OPND1].type,not OP_A

            .elseif ( [rsi].Ofssize == USE64 )

ifdef _WIN64
                mov eax,0x80000000
                mov rdx,0xffffffff80000000
                .if ( [rsi].opnd[OPNI2].data64 < rax ||
                      [rsi].opnd[OPNI2].data64 >= rdx )
else
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
endif
                    and [rsi].opnd[OPND1].type,not OP_A
                .endif
            .endif
        .endif
        ; fall through
    .default
    def_check:

        ; make sure the 2 opnds are of the same type

        mov op1_size,OperandSize(op1, rsi)
        mov op2_size,OperandSize(op2, rsi)
        .if ( op1_size > eax )
            .if ( op2 >= OP_I8 && op2 <= OP_I32 ) ; immediate
                mov op2_size,op1_size ; promote to larger size
            .endif
        .endif

        ; v2.04: check in idata_nofixup was signed,
        ; so now add -256 - -129 and 128-255 to acceptable byte range.
        ; Since Masm v8, the check is more restrictive, -255 - -129
        ; is no longer accepted.

        .if ( op1_size == 1 && op2 == OP_I16 &&
             [rsi].opnd[OPNI2].data32l <= UCHAR_MAX && [rsi].opnd[OPNI2].data32l >= -255 )

            .return rc ; OK cause no sign extension
        .endif

        .if ( op1_size != op2_size )

            ; if one or more are !defined, set them appropriately

            mov eax,op1
            or  eax,op2
            .if ( eax & ( OP_MMX or OP_XMM or OP_YMM or OP_ZMM or OP_K ) || [rsi].token >= VEX_START )

            .elseif ( op1_size != 0 && op2_size != 0 )

                mov eax,1
                .if ( [rsi].Ofssize > USE16 && ( op1 & OP_M_ANY ) && ( op2 & OP_M_ANY ) )

                    ; v2.30 - Memory to memory operands.

                    movzx ecx,[rsi].token
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

                .elseif ( op1 & OP_MS || op2 & OP_MS )

                    ; mov reg,field | field,reg - record5.asm and record7.asm
                    ; the op-size should be correct here

                    xor ecx,ecx
                    .if ( op1 & OP_MS && op2 & OP_R )
                        mov rcx,[rdi].mbr
                    .elseif ( op2 & OP_MS && op1 & OP_R )
                        mov rcx,[rdi+expr].mbr
                    .endif
                    .if ( rcx && [rcx].asym.crecord )
                        xor eax,eax
                    .endif
                .endif
                .if eax
                    mov rc,asmerr( 2022, op1_size, op2_size )
                .endif
            .endif

            ; size == 0 is assumed to mean "undefined", but there
            ; is also the case of an "empty" struct or union. The
            ; latter case isn't handled correctly.

            .if ( op1_size == 0 )

                mov eax,op1
                or  eax,op2

                .if ( op1 & OP_M_ANY && op2 & OP_I )

                    ; changed in v2.33.56
                    mov eax,[rsi].opnd[OPNI2].data32l
                    .ifs ( op2_size == 1 || ( op1 == OP_M && !( [rdi+expr].explicit ) &&
                        !( ( eax < 0 && eax < CHAR_MIN ) || eax > UCHAR_MAX ) ) )

                        mov [rsi].mem_type,MT_BYTE
                        mov [rsi].opnd[OPNI2].type,OP_I8
                        lea rcx,@CStr("BYTE")
                        .if ( op1 == OP_M && !( [rdi+expr].explicit ) )
                            mov [rsi].opnd[OPND1].type,OP_M08
                        .endif

                    .elseifs ( op2_size == 2 && !( ( eax < 0 && eax < SHRT_MIN ) || eax > USHRT_MAX ) )

                        mov [rsi].mem_type,MT_WORD
                        mov [rsi].iswide,1
                        mov [rsi].opnd[OPNI2].type,OP_I16
                        lea rcx,@CStr("WORD")

                    .else

                        mov [rsi].iswide,1
                        .if MODULE.Ofssize == USE16 && op2_size > 2 && InWordRange([rsi].opnd[OPNI2].data32l)
                            mov op2_size,2
                        .endif
                        .ifs op2_size <= 2 && eax > SHRT_MIN && MODULE.Ofssize == USE16
                            mov [rsi].mem_type,MT_WORD
                            mov [rsi].opnd[OPNI2].type,OP_I16
                        .else
                            mov [rsi].mem_type,MT_DWORD
                            mov [rsi].opnd[OPNI2].type,OP_I32
                            lea rcx,@CStr("DWORD")
                        .endif
                    .endif

                    .if !( [rdi+expr].explicit )

                        ; v2.06: emit warning at pass one if mem op isn't a forward ref
                        ; v2.06b: added "undefined" check

                        mov rax,[rsi].opnd[OPND1].InsFixup
                        .if ( ( rax  == NULL && Parse_Pass == PASS_1 && !( [rsi].undef_sym ) ) ||
                            ( rax && Parse_Pass == PASS_2 ) )
                            asmerr( 8019, rcx )
                        .endif
                    .endif
                .elseif ( ( op1 & OP_M_ANY ) && ( op2 & ( OP_R or OP_SR ) ) )
                .elseif ( ( op1 & ( OP_MMX or OP_XMM ) ) && ( op2 & OP_I ) )
                    mov eax,[rsi].opnd[OPNI2].data32l
                    .if ( eax > USHRT_MAX )
                        mov [rsi].opnd[OPNI2].type,OP_I32
                    .elseif ( eax > UCHAR_MAX )
                        mov [rsi].opnd[OPNI2].type,OP_I16
                    .else
                        mov [rsi].opnd[OPNI2].type,OP_I8
                    .endif
                .elseif ( eax & ( OP_MMX or OP_XMM ) )
                .else
                    .switch op2_size
                    .case 1
                        mov [rsi].mem_type,MT_BYTE
                        .if ( Parse_Pass == PASS_1 && ( op2 & OP_I ) )
                            asmerr( 8019, "BYTE" )
                        .endif
                        .endc
                    .case 2
                        mov [rsi].mem_type,MT_WORD
                        mov [rsi].iswide,1
                        .if ( Parse_Pass == PASS_1 && ( op2 & OP_I ) )
                            asmerr( 8019, "WORD" )
                        .endif
                        .if ( [rsi].Ofssize )
                            mov [rsi].opsiz,TRUE
                        .endif
                        .endc
                    .case 4
                        mov [rsi].mem_type,MT_DWORD
                        mov [rsi].iswide,1
                        .if ( Parse_Pass == PASS_1 && ( op2 & OP_I ) )
                            asmerr( 8019, "DWORD" )
                        .endif
                        .endc
                    .endsw
                .endif
            .endif
        .endif
    .endsw
    .return( rc )

check_size endp


IsType proc fastcall name:string_t

    UNREFERENCED_PARAMETER(name)

    SymSearch( rcx )

    .if ( rax && [rax].asym.state == SYM_TYPE )
        .return
    .endif
    .return ( NULL )

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

parsevex proc fastcall string:string_t, result:ptr uchar_t

    UNREFERENCED_PARAMETER(string)
    UNREFERENCED_PARAMETER(result)

    mov eax,[rcx]

    .switch ( al )

      .case 9
      .case ' '
        inc rcx
        mov eax,[rcx]
        .gotosw

      .case 'k' ; {k1}
        .endc .if ah < '1'
        .endc .if ah > '7'
        .endc .if eax & 0xFF0000
        sub ah,'0'
        or  [rdx],ah
        .return 1

      .case '1' ; {1to2} {1to4} {1to8} {1to16}
        .endc .if ah != 't'
        shr eax,24
        .switch ( al )
          .case '1'
            .endc .if byte ptr [rcx+4] != '6'
          .case '2'
          .case '4'
          .case '8'
            or  byte ptr [rdx],0x10
            .return 1
        .endsw
        .endc

      .case 'z' ; {z}
        .endc .if ah
        or byte ptr [rdx],0x80
        .return 1

      .case 'r' ; {rn-sae} {ru-sae} {rd-sae} {rz-sae}
        .endc .if byte ptr [rcx+2] != '-'
        .endc .if byte ptr [rcx+3] != 's'
        mov ecx,0x2000
        .switch ( ah )
          .case 'u'
            or cl,0x50  ; B|L1
            .endc
          .case 'z'
            or cl,0x70  ; B|L0|L1
          .case 'd'
            or cl,0x30  ; B|L0
          .case 'n'
            or cl,0x10  ; B
        .endsw
        .if cl
            or [rdx],cx
            .return 1
        .endif
        .endc

      .case 's' ; {sae}
        .endc .if eax != 'eas'
        mov ecx,0x2010  ; B
        or [rdx],cx
        .return 1
    .endsw
    .return( 0 )

parsevex endp


    option proc:public

; ParseLine() is the main parser function.
; It scans the tokens in tokenarray[] and does:
; - for code labels: call CreateLabel()
; - for data items and data directives: call data_dir()
; - for other directives: call directive[]()
; - for instructions: fill CodeInfo and call codegen()

; callback PROC(...) [?]

ProcType        proto __ccall :int_t, :token_t
PublicDirective proto __ccall :int_t, :token_t
mem2mem         proto __ccall :uint_t, :uint_t, :token_t, :ptr expr
imm2xmm         proto __ccall :token_t, :expr_t, :uint_t
NewDirective    proto __ccall :int_t, :token_t
CRecordField    proto __ccall :int_t, :ptr expr, :ptr expr

externdef       CurrEnum:asym_t
EnumDirective   proto __ccall :int_t, :token_t
SizeFromExpression proto __ccall :ptr expr

    assume rdi:nothing
    assume rsi:token_t
    assume rbx:token_t

ParseLine proc __ccall uses rsi rdi rbx tokenarray:token_t

  local i:int_t
  local j:int_t
  local q:int_t
  local rc:int_t
  local dirflags:uint_t
  local sym:asym_t
  local oldofs:uint_t
  local CodeInfo:code_info
  local opndx[MAX_OPND+1]:expr

    ldr rbx,tokenarray
    .if ( CurrEnum && [rbx].token == T_ID )
        .return EnumDirective( 0, rbx )
    .endif
    mov i,0

    .if ( [rbx].token == T_ID && TokenCount > 2 &&
          ( [rbx+asm_tok].token == T_COLON || [rbx+asm_tok].token == T_DBL_COLON ) )

        mov rdi,MemAlloc(MaxLineLength)

        ; break label: macro/hll lines

        tstrcpy( rdi, [rbx+asm_tok*2].tokpos )
        tstrcpy( CurrSource, [rbx].string_ptr )
        tstrcat( CurrSource, [rbx+asm_tok].string_ptr )

        mov TokenCount,Tokenize( CurrSource, 0, rbx, TOK_DEFAULT )

        .ifd ( ParseLine( rbx ) == ERROR )

            MemFree(rdi)
           .return(ERROR)
        .endif

        .if MODULE.list ; v2.26 -- missing line from list file (wiesl)
            and MODULE.line_flags,not LOF_LISTED
        .endif

        ; parse macro or hll function

        tstrcpy(CurrSource, rdi)
        MemFree(rdi)
        mov TokenCount,Tokenize(CurrSource, 0, rbx, TOK_DEFAULT)
        ExpandLine(CurrSource, rbx)
        .if ( eax == EMPTY || eax == ERROR )

           .return
        .endif
        mov i,0

if 0 ; code labels before data items allowed..

        .if ( MODULE.m510 == FALSE && [rbx].token == T_DIRECTIVE && [rbx].dirtype == DRT_DATADIR )
            .return( asmerr( 2008, [rbx].string_ptr ) )
        .endif
endif
        ; label:

    .elseif ( [rbx].token == T_ID && ( [rbx+asm_tok].token == T_COLON || [rbx+asm_tok].token == T_DBL_COLON ) )

        mov i,2

        .if ( ProcStatus & PRST_PROLOGUE_NOT_DONE )

            write_prologue(rbx)
        .endif
        ;
        ; create a global or local code label
        ;
        xor eax,eax
        .if ( MODULE.scoped && CurrProc && [rbx+asm_tok].token != T_DBL_COLON )
            inc eax
        .endif
        .if CreateLabel( [rbx].string_ptr, MT_NEAR, NULL, eax ) == NULL

            .return ERROR
        .endif
        ;
        ; v2.26: make label:: public
        ;
        .if ( [rbx+asm_tok].token == T_DBL_COLON && MODULE.scoped && !CurrProc )

            mov [rbx+asm_tok].token,T_FINAL
            mov TokenCount,1
            PublicDirective( -1, tokenarray )
        .endif

        lea rsi,[rbx+asm_tok*2]

        .if ( [rsi].token == T_FINAL )
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
            .if CurrFile[LST*size_t]
                LstWrite( LSTTYPE_LABEL, 0, NULL )
            .endif
            .return NOT_ERROR
        .endif
    .endif

    ; handle directives and (anonymous) data items

    imul esi,i,asm_tok
    add rsi,rbx

    mov j,0
    mov CodeInfo.prefix,0

    .if ( MODULE.ComStack )

        .if ( [rbx].token == T_STYPE &&
              [rbx+asm_tok].token == T_DIRECTIVE &&
              [rbx+asm_tok].tokval == T_PROC )
            inc j
        .endif

    .elseif ( [rbx].token == T_DIRECTIVE && [rbx].tokval == T_DOT_INLINE )

        mov [rbx].token,T_ID
        mov [rbx].string_ptr,[rbx+asm_tok].string_ptr
        mov [rbx+asm_tok].token,T_DIRECTIVE
        mov [rbx+asm_tok].tokval,T_PROTO
        mov [rbx+asm_tok].dirtype,DRT_PROTO
        ;mov [rbx+asm_tok].string_ptr,&@CStr( "proto" )
    .endif

    .if ( j || [rsi].token != T_INSTRUCTION )
        ;
        ; a code label before a data item is only accepted in Masm5 compat mode
        ;
        mov Frame_Type,FRAME_NONE
        mov SegOverride,NULL

        .if ( i == 0 && ( j || [rbx].token == T_ID ) )
            ;
            ; token at pos 0 may be a label.
            ; it IS a label if:
            ; 1. token at pos 1 is a directive (lbl dd ...)
            ; 2. token at pos 0 is NOT a userdef type ( lbl DWORD ...)
            ; 3. inside a struct and token at pos 1 is a userdef type
            ;    or a predefined type. (usertype DWORD|usertype ... )
            ;    the separate namespace allows this syntax here.
            ;
            .if ( [rbx+asm_tok].token == T_DIRECTIVE )

                inc i
                add rsi,asm_tok

            .else

                mov sym,IsType( [rbx].string_ptr )
                .if ( rax == NULL )

                    inc i
                    add rsi,asm_tok

                .elseif ( CurrStruct )

                    xor eax,eax
                    .if ( [rbx+asm_tok].token == T_STYPE )
                        inc eax
                    .elseif ( [rbx+asm_tok].token == T_ID )
                        IsType( [rbx+asm_tok].string_ptr )
                    .endif
                    .if ( rax )
                        inc i
                        add rsi,asm_tok
                    .endif
                .endif
            .endif
        .endif

        movzx eax,[rsi].token
        .switch eax
        .case T_DIRECTIVE
            .if ( [rsi].dirtype == DRT_DATADIR )
                .return( data_dir( i, tokenarray, NULL ) )
            .endif
            mov dirflags,GetValueSp( [rsi].tokval )
            .if ( j || ( CurrStruct && ( dirflags & DF_NOSTRUC ) ) )

                .if ( [rsi].tokval != T_PROC )
                    .return( asmerr( 2037 ) )
                .endif
                .if StoreState
                    FStoreLine(0)
                .endif
                mov edi,ProcType( i, tokenarray )
                .if ( MODULE.list &&
                      ( Parse_Pass == PASS_1 || MODULE.GeneratedCode || UseSavedState == FALSE ) )
                    LstWriteSrcLine()
                .endif
                .return( edi )
            .endif

            ; label allowed for directive?

            .if ( dirflags & DF_LABEL )
                .if ( i && [rbx].token != T_ID )
                    .return( asmerr(2008, [rbx].string_ptr ) )
                .endif
            .elseif ( i && [rsi-asm_tok].token != T_COLON && [rsi-asm_tok].token != T_DBL_COLON )
                .return( asmerr(2008, [rsi-asm_tok].string_ptr ) )
            .endif

            ; must be done BEFORE FStoreLine()!

            .if( ( ProcStatus & PRST_PROLOGUE_NOT_DONE ) && ( dirflags & DF_PROC ) )
                write_prologue( tokenarray )
            .endif
            .if ( StoreState || ( dirflags & DF_STORE ) )

                ; v2.07: the comment must be stored as well
                ; if a listing (with -Sg) is to be written and
                ; the directive will generate lines
                ; v2.19: obsolete, comment is never stored.

                FStoreLine(0)
            .endif

            .if ( [rsi].dirtype > DRT_DATADIR )

                movzx eax,[rsi].dirtype
                lea rcx,directive_tab
                mov rax,[rcx+rax*size_t]
                assume rax:fpDirective
                rax( i, rbx )
                assume rax:nothing
                mov edi,eax

            .else

                mov edi,ERROR
                ;
                ; ENDM, EXITM and GOTO directives should never be seen here
                ;
                mov eax,[rsi].tokval
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
                    asmerr(2008, [rsi].string_ptr )
                    .endc
                .endsw
            .endif
            ;
            ; v2.0: for generated code it's important that list file is
            ; written in ALL passes, to update file position!
            ; v2.08: UseSavedState == FALSE added
            ;
            .if ( MODULE.list && ( Parse_Pass == PASS_1 ||
                  MODULE.GeneratedCode || UseSavedState == FALSE ) )
                LstWriteSrcLine()
            .endif
            .return( edi )

        .case T_BINARY_OPERATOR
            .endc .if [rsi].tokval != T_PTR
        .case T_STYPE
            .return data_dir( i, rbx, NULL )
        .case T_ID
            .if IsType( [rsi].string_ptr )
                ;
                ; v2.31.25: Type() -- constructor
                ;
                .endc .if [rsi].IsProc
                .return data_dir( i, rbx, rax )
            .endif
            .endc
        .default
            .if ( [rsi].token == T_COLON )
                .return asmerr( 2065, ":")
            .endif
            .endc
        .endsw

        .if ( i && [rsi-asm_tok].token == T_ID )
            dec i
            sub rsi,asm_tok
        .endif

        .if ( i || [rbx].dirtype != '{' )

            .if ( CurrEnum && [rbx].token == T_STRING )
                .return EnumDirective( 0, rbx )
            .endif

            .if ( i == 0 && TokenCount > 1 )

                .if ( [rbx].token == T_ID )

                    mov rcx,[rbx].string_ptr
                    mov eax,[rcx]
                    or  eax,0x20202020
                    mov cl,[rcx+4]

                    .if ( eax == 'xeve' && cl == 0 )
                        mov eax,PREFIX_EVEX
                        jmp init_prefix
                    .elseif ( eax == ' xev' )
                        mov eax,PREFIX_VEX
                        jmp init_prefix
                    .elseif ( eax == '2xev' && cl == 0 )
                        mov eax,PREFIX_VEX2
                        jmp init_prefix
                    .elseif ( eax == '3xev' && cl == 0 )
                        mov eax,PREFIX_VEX3
                        jmp init_prefix
                    .endif
                .endif

                .if ( GetOperator( &[rbx+asm_tok] ) )
                    .return ProcessOperator( tokenarray )
                .endif
                .if ( ( [rbx].token == T_BINARY_OPERATOR && [rbx].tokval == T_DEFINED ) ||
                      ( [rbx].token == T_UNARY_OPERATOR && [rbx].tokval == T_SQRT ) )

                    RemoveResWord( [rbx].tokval )
                    mov [rbx].token,T_ID
                    .if PreprocessLine( rbx )
                        ParseLine( rbx )
                    .endif
                    .return
                .endif
            .endif
            .return asmerr( 2008, [rsi].string_ptr )
init_prefix:
            mov CodeInfo.prefix,al
            inc i
            add rsi,asm_tok

        .elseif ( i == 0 && [rbx].dirtype == '{' && [rbx].stringlen == 4 )

            mov rcx,[rbx].string_ptr
            mov eax,[rcx]
            or  eax,0x20202020
            .if ( eax == 'xeve' )

                mov eax,PREFIX_EVEX
                jmp init_prefix
            .endif
        .endif
    .endif

    .if ( CurrStruct )
        .return asmerr( 2037 )
    .endif
    .if ( ProcStatus & PRST_PROLOGUE_NOT_DONE )
        write_prologue( rbx )
    .endif
    .if ( CurrFile[LST*size_t] )
        mov oldofs,GetCurrOffset()
    .endif

    ; init CodeInfo

    mov dl,CodeInfo.prefix
    xor eax,eax
    mov ecx,sizeof(CodeInfo) / 4
    lea rdi,CodeInfo
    rep stosd
    mov CodeInfo.inst,EMPTY
    mov CodeInfo.RegOverride,EMPTY
    mov CodeInfo.mem_type,MT_EMPTY
    mov CodeInfo.Ofssize,MODULE.Ofssize
    mov CodeInfo.prefix,dl

    ; instruction prefix?
    ;
    ; v2.36.36 - added VEX, VEX2, VEX3, EXEX, XACQUIRE, and XRELEASE
    ;
    mov eax,[rsi].tokval
    .if ( eax == T_XACQUIRE || eax == T_XRELEASE )

        mov edx,eax

        inc i
        add rsi,asm_tok
        mov eax,[rsi].tokval

        .if ( eax == T_LOCK && ( [rsi+asm_tok].tokval == T_MOV || [rsi+asm_tok].tokval == T_XCHG ) )

            ; Masm ignore the LOCK prefix here..

            inc i
            add rsi,asm_tok
            mov eax,[rsi].tokval
        .endif
        .if ( eax != T_LOCK )
            mov eax,edx
            mov CodeInfo.inst,edx
        .endif
    .endif

    ; T_LOCK, T_REP, T_REPE, T_REPNE, T_REPNZ, T_REPZ

    .if ( eax >= T_LOCK && eax <= T_REPZ )

        mov CodeInfo.inst,eax
        inc i
        add rsi,asm_tok
        ;
        ; prefix has to be followed by an instruction
        ;
        .if ( [rsi].token != T_INSTRUCTION )
            .return asmerr( 2068 )
        .endif
    .endif

    .if ( CurrProc )

        .switch [rsi].tokval
        .case T_RET
        .case T_IRET  ;; IRET is always 16-bit; OTOH, IRETW doesn't exist
        .case T_IRETD
        .case T_IRETQ

            .if ( !( ProcStatus & PRST_INSIDE_EPILOGUE ) && MODULE.epiloguemode != PEM_NONE )

                ; v2.07: special handling for RET/IRET
                ; v2.19: comment is never stored, so flags are obsolete
                FStoreLine(0)
                or ProcStatus,PRST_INSIDE_EPILOGUE
                RetInstr( i, tokenarray, TokenCount )
                and ProcStatus,not PRST_INSIDE_EPILOGUE
               .return
            .endif

            ; default translation: just RET to RETF if proc is far
            ; v2.08: this code must run even if PRST_INSIDE_EPILOGUE is set

            .if ( [rsi].tokval == T_RET )

                mov rax,CurrProc
                .if ( [rax].asym.mem_type == MT_FAR )
                    mov [rsi].tokval,T_RETF
                .endif
            .endif
        .endsw
    .endif

    .if ( [rbx].Expand )

        lea rsi,[rbx+asm_tok]
        .for ( j = 1 : [rsi].token != T_FINAL : j++, rsi += asm_tok )

            .if ( [rsi].IsProc )

                mov rdi,alloc_line()
                ;
                ; v2.21 - mov reg,proc(...)
                ; v2.27 - mov reg,class.proc(...)
                ;
                mov rc,ExpandHllProcEx( rdi, j, rbx )
                free_line(rdi)

                .if ( rc == ERROR )
                   .return(ERROR)
                .endif
                .if ( rc == STRING_EXPANDED )

                    FStoreLine(0)
                   .return( NOT_ERROR )
                .endif
                .break
            .endif
        .endf
    .endif

    FStoreLine(0) ; must be placed AFTER write_prologue()

    imul esi,i,asm_tok
    add rsi,rbx
    mov eax,[rsi].tokval
    mov CodeInfo.token,ax

    ; get the instruction's start position in InstrTable[]

    movzx eax,IndexFromToken(eax)
    lea rcx,InstrTable
    lea rax,[rcx+rax*8]
    mov CodeInfo.pinstr,rax

    inc i
    add rsi,asm_tok

    mov rax,CurrSeg
    .return asmerr(2034) .if rax == NULL

    mov rax,[rax].dsym.seginfo

    .if ( [rax].seg_info.segtype == SEGTYPE_UNDEF )
        mov [rax].seg_info.segtype,SEGTYPE_CODE
    .endif
    .if ( MODULE.CommentDataInCode )
        omf_OutSelect( FALSE )
    .endif

    ; get the instruction's arguments.
    ; This loop accepts up to 4 arguments if AVXSUPP is on

    .for ( j = 0: j < lengthof(opndx) && [rsi].token != T_FINAL: j++ )

        .if j
            .break .if [rsi].token != T_COMMA
            inc i
        .endif

        imul edi,j,expr
        lea rcx,opndx[rdi]

        .ifd ( EvalOperand( &i, tokenarray, TokenCount, rcx, 0 ) == ERROR )
            .return
        .endif

        imul esi,i,asm_tok
        add rsi,tokenarray

        .if ( [rsi-asm_tok].Modifier )

            or CodeInfo.prefix,PREFIX_EVEX
            lea rbx,[rsi-asm_tok] ; get transform modifiers

            .if ( [rbx].token == T_STRING )
                .repeat
                    .if ( !parsevex( [rbx].string_ptr, &CodeInfo.evexP3 ) )
                        .return asmerr( 2008, [rbx].string_ptr )
                    .endif
                    sub rbx,asm_tok
                .until !( [rbx].Modifier )

                .if ( opndx[rdi].kind == EXPR_EMPTY )

                    dec j
                   .continue
                .endif
            .else
                or CodeInfo.evexP3,0x10
            .endif
        .endif

        .switch opndx[rdi].kind
        .case EXPR_FLOAT
            ;
            ; v2.06: accept float constants for PUSH
            ;
            .if ( j == OPND2 || CodeInfo.token == T_PUSH || CodeInfo.token == T_PUSHD )

                .if ( Options.strict_masm_compat == FALSE )

                    ; v2.27: convert to REAL

                    .if ( opndx[rdi].mem_type != MT_EMPTY )

                        movzx eax,CurrWordSize ; added v2.31.31

                        .if ( j )

                            .if ( opndx[rdi-expr].kind == EXPR_REG && !( opndx[rdi-expr].indirect ) )

                                mov rax,opndx[rdi-expr].base_reg
                                SizeFromRegister( [rax].asm_tok.tokval )

                            .elseif ( opndx[rdi-expr].kind == EXPR_ADDR || opndx[rdi-expr].kind == EXPR_REG )

                                ; added v2.31.27
                                SizeFromMemtype(opndx[rdi-expr].mem_type, opndx[rdi-expr].Ofssize, opndx[rdi-expr].type)
                            .endif
                        .endif

                        xor ecx,ecx
                        .switch eax
                        .case 2:  mov ecx,MT_REAL2  : .endc
                        .case 4:  mov ecx,MT_REAL4  : .endc
                        .case 8:  mov ecx,MT_REAL8  : .endc
                        .case 16: mov ecx,MT_REAL16 : .endc
                        .endsw

                        .if ( ecx )

                            lea rdx,opndx[rdi]
                            mov opndx[rdi].kind,EXPR_CONST
                            mov opndx[rdi].expr.mem_type,cl

                            .if ( eax != 16 )
                                mov rcx,rdx
                                quad_resize(rcx, eax)
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
            .if ( i > 1 && [rsi].token == T_DIRECTIVE && [rsi].tokval == T_DOT_NEW )


                mov rbx,alloc_line()
                mov rax,tokenarray
                mov rax,[rax].asm_tok.tokpos
                mov rcx,[rsi].tokpos
                sub rcx,rax
                mov rsi,rax
                mov rdi,rbx
                rep movsb
                .if ( MODULE.Ofssize == USE64 )
                    mov eax,"xar"
                .else
                    mov eax,"xae"
                .endif
                stosd
                NewDirective(i, tokenarray)
                .if ( Parse_Pass > PASS_1 )
                    mov TokenCount,Tokenize( tstrcpy( CurrSource, rbx ), 0, tokenarray, TOK_DEFAULT )
                    MemFree(rbx)
                   .return ParseLine( tokenarray )
                .endif
                free_line(rbx)
               .return NOT_ERROR
            .endif
            .if ( i == TokenCount )
                sub rsi,asm_tok ; v2.08: if there was a terminating comma, display it
            .endif
            ;
            ; fall through
            ;
        .case EXPR_ERROR
            .return asmerr( 2008, [rsi].string_ptr )
        .endsw
    .endf

    .if ( [rsi].token != T_FINAL )
        .return asmerr( 2008, [rsi].tokpos )
    .endif
    .if ( j >= 3 )
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

        .if ( eax >= VEX_START && ebx == OPND2 &&
              ( ecx & ( OP_XMM or OP_YMM or OP_ZMM or OP_M or OP_K or OP_M256 or OP_M512 or OP_R32 or OP_R64 ) ) )

            lea rdi,vex_flags
            movzx edi,byte ptr [rdi+rax-VEX_START]

            .if ( ( eax < T_ANDN || eax > T_PEXT ) && ( ecx & ( OP_R32 or OP_R64 ) ) )
            .elseif ( edi & VX_NND )
            .elseif ( ( edi & VX_IMM ) && ( opndx[expr*2].kind == EXPR_CONST ) && ( j > 2 ) )
            .elseif ( ( edi & VX_HALF ) && ( ( ecx & ( OP_XMM or OP_YMM or OP_ZMM ) ) &&
                      ( opndx[rdx].indirect ) ) )

                mov CodeInfo.rm_byte,0

            .elseif ( ( edi & VX_NMEM ) && ( ( ecx & OP_M ) ||
                     ( ( eax == T_VMOVSD || eax == T_VMOVSS ) &&
                     ( opndx[expr].kind != EXPR_REG || opndx[expr].indirect ) ) ) )

                ; v2.11: VMOVSD and VMOVSS always have 2 ops if a memory op is involved

            .else

                .if opndx[expr].kind != EXPR_REG
                    .return asmerr( 2070 )
                .endif
                mov rax,opndx[rdx].base_reg
                mov eax,[rax].asm_tok.tokval

                .if ( !( GetValueSp(eax) & ( OP_R32 or OP_R64 or OP_XMM or OP_YMM or OP_ZMM or OP_K ) ) )
                    .return asmerr( 2070 )
                .endif

                ; fixme: check if there's an operand behind OPND2 at all!
                ; if no, there's no point to continue with switch (opndx[].kind).
                ; v2.11: additional check for j <= 2 added

                .if ( j <= 2 )

                    ; v2.11: next line should be activated - currently the
                    ; error is emitted below as syntax error

                    movzx eax,CodeInfo.token
                    lea   rcx,ResWordTable
                    imul  eax,eax,ReservedWord

                    .if [rcx+rax].ReservedWord.flags & RWF_EVEX
                        inc j
                    .endif

                    ; flag VX_DST is set if an immediate is expected as operand 3

                .elseif ( ( edi & VX_DST ) && ( opndx[expr*2].kind == EXPR_CONST ) )

                    .if ( opndx[OPND1].base_reg )

                        ; first operand register is moved to vexregop
                        ; handle VEX.NDD

                        mov rcx,opndx[rdx].base_reg
                        mov eax,[rcx].asm_tok.tokval
                        mov eax,GetValueSp(eax)

                        mov rcx,opndx[OPND1].base_reg
                        mov cl,[rcx].asm_tok.bytval
                        inc cl
                        mov CodeInfo.vexregop,cl

                        .if ( eax & OP_ZMM )
                            or CodeInfo.vexregop,0x80
                        .elseif ( eax & OP_YMM )
                            or CodeInfo.vexregop,0x40
                        .endif

                        lea  rdi,opndx[0]
                        lea  rax,opndx[rdx]
                        xchg rax,rsi
                        mov  ecx,expr * 3
                        rep  movsb
                        mov  rsi,rax

                        mov CodeInfo.rm_byte,0
                        .ifd ( process_register( &CodeInfo, OPND1, &opndx, q ) == ERROR )
                            .return
                        .endif
                        inc q
                    .endif

                .else

                    mov rcx,opndx[rdx].base_reg
                    mov eax,[rcx].asm_tok.tokval
                    mov eax,GetValueSp(eax)

                    ; v2.08: no error here if first op is an untyped memory reference
                    ; note that OP_M includes OP_M128, but not OP_M256 (to be fixed?)

                    .if ( CodeInfo.opnd[OPND1].type == OP_M )

                    .elseif ( ( eax & ( OP_XMM or OP_M128 ) ) &&
                        ( CodeInfo.opnd[OPND1].type & (OP_YMM or OP_M256 ) ) ||
                        ( eax & ( OP_YMM or OP_M256 ) ) &&
                        ( CodeInfo.opnd[OPND1].type & (OP_XMM or OP_M128 ) ) )

                        .return asmerr(2070)
                    .endif

                    ; second operand register is moved to vexregop
                    ; to be fixed: CurrOpnd is always OPND2, so use this const here

                    mov edi,eax
                    mov al,[rcx].asm_tok.bytval
                    inc al
                    mov CodeInfo.vexregop,al
                    .if ( CodeInfo.vexregop > 16 || edi & OP_ZMM )

                        or CodeInfo.prefix,PREFIX_EVEX
                        .if ( CodeInfo.vexregop > 16 )
                            or CodeInfo.vflags,VX_OP2V
                        .endif
                        .if ( edi & OP_ZMM )
                            or CodeInfo.vexregop,0x80
                            or CodeInfo.vflags,VX_ZMM
                        .endif
                    .elseif ( edi & OP_YMM )
                        or CodeInfo.vexregop,0x40
                    .endif
                    inc  q
                    lea  rdi,opndx[rdx]
                    lea  rax,opndx[rdx+expr]
                    xchg rax,rsi
                    mov  ecx,expr * 2
                    rep  movsb
                    mov  rsi,rax
                .endif
                dec j
            .endif
        .endif

        imul edx,ebx,expr
        .switch opndx[rdx].kind
        .case EXPR_ADDR
            .ifd ( process_address( &CodeInfo, ebx, &opndx[rdx] ) == ERROR )
                .return
            .endif
            .endc
        .case EXPR_CONST
            .ifd ( process_const( &CodeInfo, ebx, &opndx[rdx] ) == ERROR )
                .return
            .endif
            .endc
        .case EXPR_REG

            .if ( opndx[rdx].indirect ) ; indirect operand ( "[EBX+...]" )?

                .ifd ( process_address( &CodeInfo, ebx, &opndx[rdx] ) == ERROR )
                    .return
                .endif

            .else

                ; process_register() can't handle 3rd operand

                .if ( ebx == OPND3 )

                    mov rcx,opndx[rdx].base_reg
                    mov eax,[rcx].asm_tok.tokval
                    mov eax,GetValueSp(eax)
                    mov CodeInfo.opnd[OPNI3].type,eax
                    movzx eax,[rcx].asm_tok.bytval
                    mov CodeInfo.opnd[OPNI3].data32l,eax
                    mov rcx,CodeInfo.pinstr

                    .if ( [rcx].instr_item.evex & VX_XMMI )

                        mov cl,CodeInfo.opc_or
                        and cl,0xF0
                        or  al,cl
                        mov CodeInfo.opc_or,al
                    .endif

                .elseifd ( process_register( &CodeInfo, ebx, &opndx, q ) == ERROR )

                    .return
                .endif
            .endif
            .endc
        .endsw
    .endf

ifdef USE_INDIRECTION

    assume rdi:ptr expr

    .if ( ebx == 2 &&
          ( ( opndx.kind == EXPR_REG && opndx[expr].kind == EXPR_ADDR ) ||
            ( opndx.kind == EXPR_ADDR && opndx[expr].kind != EXPR_ADDR ) ) )

        mov ecx,1
        lea rdi,opndx
        .if ( [rdi].kind == EXPR_REG )
            add rdi,expr
            dec ecx
        .endif
        mov rbx,[rdi].base_reg
        mov rax,[rdi].sym
        mov rdx,[rdi].mbr

        .if ( rbx && rax && rdx && [rdi].is_dot )

            mov rdx,[rax].asym.target_type

            .if ( rdx &&
                  [rax].asym.mem_type == MT_PTR &&
                  [rax].asym.is_ptr &&
                  [rdx].asym.state == SYM_TYPE &&
                  [rbx].token == T_ID &&
                  ( [rbx+asm_tok].token == T_DOT || [rbx+asm_tok].token == T_OP_SQ_BRACKET ) )

                .if ( ( !ecx &&
                        [rbx-3*asm_tok].token == T_INSTRUCTION &&
                        [rbx-2*asm_tok].token == T_REG &&
                        [rbx-asm_tok].token == T_COMMA
                      ) || ( ecx && [rbx-asm_tok].token == T_INSTRUCTION )
                    )
                    .return HandleIndirection( rax, rbx, ecx )
                .endif
            .endif
        .endif
        mov ebx,2
    .endif

endif
    ;
    ; 4 arguments are valid vor AVX only
    ;
    .if ( ebx != j )

        .for ( : [rsi].token != T_COMMA: i--, rsi -= asm_tok )
        .endf
        .return asmerr( 2008, [rsi].tokpos )
    .endif
    ;
    ; for FAR calls/jmps some special handling is required:
    ; in the instruction tables, the "far" entries are located BEHIND
    ; the "near" entries, that's why it's needed to skip all items
    ; until the next "first" item is found.
    ;
    .if ( CodeInfo.isfar )
        .if ( CodeInfo.token == T_CALL || CodeInfo.token == T_JMP )

            .repeat
                add CodeInfo.pinstr,instr_item
                mov rdx,CodeInfo.pinstr
            .until [rdx].instr_item.flags & II_FIRST
        .endif
    .endif

    ;; special handling for string instructions
    mov rdx,CodeInfo.pinstr
    mov al,[rdx].instr_item.flags
    and eax,II_ALLOWED_PREFIX

    .if ( eax == AP_REP || eax == AP_REPxx )
        ;
        ; v2.31.24: immediate operand to XMM
        ;
        .if ( MODULE.masm_compat_gencode == 0 && CodeInfo.token == T_MOVSD )
            .if ( CodeInfo.opnd[OPND1].type == OP_XMM &&
                ( CodeInfo.opnd[OPNI2].type & OP_I_ANY ) )
                .return imm2xmm( tokenarray, &opndx[expr], 8 )
            .endif
        .endif

        HandleStringInstructions( &CodeInfo, &opndx )

    .else
        .if ( ebx > 1 )

            ; v1.96: check if a third argument is ok

            .if ( ebx > 2 )

                mov rdx,CodeInfo.pinstr
                .while 1

                    movzx eax,[rdx].instr_item.opclsidx
                    imul  eax,eax,opnd_class
                    lea   rcx,opnd_clstab

                    .break .if ( [rcx+rax].opnd_class.opnd_type_3rd != OP3_NONE )

                    add rdx,instr_item

                    .if ( [rdx].instr_item.flags & II_FIRST )

                        .for ( : [rsi].token != T_COMMA: rsi -= asm_tok )
                        .endf
                        .return asmerr( 2008, [rsi].tokpos )
                    .endif
                .endw
                mov CodeInfo.pinstr,rdx
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
                mov rax,CodeInfo.opnd[OPNI2].InsFixup
                .if rax
                    mov rax,[rax].fixup.sym
                .endif
                .if ( CodeInfo.opnd[OPNI3].type == OP_NONE && ( CodeInfo.opnd[OPNI2].type & OP_I ) )

                    .if ( CodeInfo.rex & REX_B )
                        or CodeInfo.rex,REX_R
                    .endif
                    mov al,CodeInfo.rm_byte
                    mov dl,al
                    and al,not BIT_345
                    and dl,BIT_012
                    shl dl,3
                    or  al,dl
                    mov CodeInfo.rm_byte,al

                .elseif ( ( CodeInfo.opnd[OPNI3].type != OP_NONE ) && ( CodeInfo.opnd[OPNI2].type & OP_I ) &&
                          rax && [rax].asym.state == SYM_UNDEFINED )
                    mov CodeInfo.opnd[OPNI2].type,OP_M
                .endif
            .endif

            .ifd ( check_size( &CodeInfo, &opndx ) == ERROR )
                .return
            .endif
        .endif

        .if ( CodeInfo.Ofssize == USE64 )

            .if ( CodeInfo.x86hi_used && CodeInfo.rex )
                asmerr( 3012 )
            .endif

            ; for some instructions, the "wide" flag has to be removed selectively.
            ; this is to be improved - by a new flag in struct instr_item.

            ; added v2.31.32

            movzx eax,CodeInfo.token
            .if ( eax < VEX_START && eax >= T_ADDPD && j > 1 && opndx[expr].kind == EXPR_CONST )
                mov rdx,opndx[expr].quoted_string
                .if rdx
                    .if ( [rdx].asm_tok.token == T_STRING && [rdx].asm_tok.dirtype == '{' )
                        mov eax,T_MOVAPS
                    .endif
                .endif
            .endif

            mov ecx,4
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
                add ecx,8
            .case T_MOVQ
            .case T_MOVSD
            .case T_ADDSD
            .case T_SUBSD
            .case T_MULSD
            .case T_DIVSD
            .case T_COMISD
            .case T_UCOMISD
                add ecx,4
            .case T_ADDSS
            .case T_SUBSS
            .case T_MULSS
            .case T_DIVSS
            .case T_COMISS
            .case T_UCOMISS
            .case T_MOVD
            .case T_MOVSS
                .endc .if ( MODULE.masm_compat_gencode != 0 )
                .endc .if ( CodeInfo.opnd[OPND1].type != OP_XMM )
                .endc .if !( CodeInfo.opnd[OPNI2].type & OP_I_ANY )
                .return imm2xmm( tokenarray, &opndx[expr], ecx )
            .case T_MOV:
                ;; don't use the Wide bit for moves to/from special regs
                .if ( CodeInfo.opnd[OPND1].type & OP_RSPEC || CodeInfo.opnd[OPNI2].type & OP_RSPEC )
                    and CodeInfo.rex,0x7
                .endif
                .endc
            .endsw
        .endif

        assume rbx:nothing
        assume rsi:nothing

        movzx eax,CodeInfo.token
        mov ecx,CodeInfo.opnd[OPND1].type
        mov edx,CodeInfo.opnd[OPNI2].type

        .if ( ( ecx & OP_M_ANY ) || ( edx & OP_M_ANY ) )

            mov rbx,opndx[expr].mbr
            .if ( ecx & OP_M_ANY )
                mov rbx,opndx.mbr
            .endif
            .if ( rbx && [rbx].asym.state == SYM_STRUCT_FIELD && [rbx].asym.mem_type == MT_BITS )

                ; v2.36.44 - Handle Masm RECORD fields errors

                .if ( !MODULE.masm_compat_gencode && [rbx].asym.crecord )

                    ; v2.36.39 - Handle C-type RECORD fields

                    .switch eax
                    .case T_OR
                    .case T_XOR
                    .case T_TEST
                    .case T_CMP
                        .if ( edx & OP_I )
                            xor ebx,ebx
                        .endif
                        .endc
                    .case T_MOV
                    .case T_MOVZX
                        .if ( ecx & OP_R )
                            xor ebx,ebx
                        .elseif ( edx & ( OP_IS or OP_R ) )
                            xor ebx,ebx
                        .endif
                    .endsw
                .endif
                .if ( rbx == 0 )
                    mov ecx,eax
                   .return( CRecordField(ecx, &opndx, &opndx[expr]) )
                .elseif !( ecx & OP_MS && edx & OP_MS )
                    .return( asmerr( 2166 ) )
                .endif
            .endif
        .endif

        .if ( CodeInfo.Ofssize > USE16 && !MODULE.masm_compat_gencode )

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
                mov ecx,4
            .elseif ( eax == T_COMISD && ecx == OP_M64 && ( edx & OP_I_ANY ) )
                inc ebx
                mov ecx,8
            .elseif ( ( ecx == OP_XMM ) && ( edx & OP_I_ANY ) )

                mov ecx,4
                .switch eax

                    ;; v2.31.24: immediate operand to XMM
                    ;; v2.31.32: immediate operand to XMM { 1.0, 2.0 }

                .case T_MOVAPS
                    add ecx,8
                .case T_MOVQ
                .case T_MOVSD
                .case T_ADDSD
                .case T_SUBSD
                .case T_MULSD
                .case T_DIVSD
                .case T_COMISD
                .case T_UCOMISD
                    add ecx,4
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
                .return imm2xmm( tokenarray, &opndx[expr], ecx )
            .endif
        .endif
    .endif

    ; now call the code generator
    codegen(&CodeInfo, oldofs)
    ret

ParseLine endp


;; process a file. introduced in v2.11

ProcessFile proc __ccall tokenarray:ptr asm_tok

    UNREFERENCED_PARAMETER(tokenarray)

    .if ( MODULE.EndDirFound == FALSE && GetTextLine( CurrSource ) )

        mov rcx,CurrSource ;; v2.23 - BOM UFT-8 test
        mov eax,[rcx]
        and eax,0x00FFFFFF
        .if eax == 0xBFBBEF
            lea rax,[rcx+3]
            tstrcpy(rcx, rax)
        .endif
        .repeat
            .if PreprocessLine( TokenArray )
                ParseLine( TokenArray )
                .if ( Options.preprocessor_stdout == TRUE && Parse_Pass == PASS_1 )
                    WritePreprocessedLine( CurrSource )
                .endif
            .endif
        .until !( MODULE.EndDirFound == FALSE && GetTextLine( CurrSource ) )
    .endif
    ret

ProcessFile endp

    end

