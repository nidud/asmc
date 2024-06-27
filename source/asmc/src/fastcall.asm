; FASTCALL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include string.inc
include limits.inc
include malloc.inc
include stdio.inc

include asmc.inc
include proc.inc
include lqueue.inc
include parser.inc
include reswords.inc
include segment.inc
include operands.inc
include expreval.inc
include qfloat.inc
include memalloc.inc
include assume.inc

;
; tables for FASTCALL support
;
; v2.07: 16-bit MS FASTCALL registers are AX, DX, BX.
; And params on stack are in PASCAL order.
;
; v2.34.64 - new fastcall info
;
define FC_FIXED     0x01    ; registers is equal to param index
define FC_LOCAL     0x02    ; local stack cleanup
define FC_RESERVED  0x04    ; use reserved stack
define FC_TMACRO    0x08    ; add TMACRO register-param name

define R0_USED      0x01    ; register contents of AX/EAX/RAX is destroyed

.template fc_info

    gpr_db      db 8 dup(?) ; General purpose registers
    gpr_dw      db 8 dup(?)
    gpr_dd      db 8 dup(?) ; mask bits
    gpr_dq      db 8 dup(?) ; 0  1  2  3  6  7  8  9
    gpr_mask    dd ?        ; AX CX DX BX SI DI R8 R9
    max_reg     db ?        ; 0..14
    max_gpr     db ?        ; 0..6
    max_xmm     db ?        ; 0..8
    max_int     db ?        ; sizeof(reg::reg[::reg::reg])
    stk_size    db ?        ; word size or 16 for vectorcall
    exp_size    db ?        ; extend regs to exp_size
    flags       db ?
   .ends

.pragma warning(disable: 6004)

.data

;
; table of fastcall types.
; must match order of enum fastcall_type!
; also see table in mangle.asm!
;
; param   0      1      2      3      4      5      6       mask   max gpr xmm int stk exp flags

fast_table fc_info {
        { 0,     0,     0,     0,     0,     0,     0, 0 }, ; SYSCALL16
        { 0,     0,     0,     0,     0,     0,     0, 0 },
        { 0,     0,     0,     0,     0,     0,     0, 0 },
        { 0,     0,     0,     0,     0,     0,     0, 0 }, 0x000,  0,  0,  0,  0,  0,  0,  0
    },{
        { 0,     0,     0,     0,     0,     0,     0, 0 }, ; SYSCALL32
        { 0,     0,     0,     0,     0,     0,     0, 0 },
        { 0,     0,     0,     0,     0,     0,     0, 0 },
        { 0,     0,     0,     0,     0,     0,     0, 0 }, 0x000,  0,  0,  0,  0,  0,  0,  0
    },{
        { T_DIL, T_SIL, T_DL,  T_CL,  T_R8B, T_R9B, 0, 0 }, ; SYSCALL64
        { T_DI,  T_SI,  T_DX,  T_CX,  T_R8W, T_R9W, 0, 0 }, ;
        { T_EDI, T_ESI, T_EDX, T_ECX, T_R8D, T_R9D, 0, 0 },
        { T_RDI, T_RSI, T_RDX, T_RCX, T_R8,  T_R9,  0, 0 }, 0x3C6, 14,  6,  8, 32,  8,  4,  0
    },{
        { T_AL,  T_DL,  T_BL,  0,     0,     0,     0, 0 }, ; FASTCALL16
        { T_AX,  T_DX,  T_BX,  0,     0,     0,     0, 0 },
        { 0,     0,     0,     0,     0,     0,     0, 0 },
        { 0,     0,     0,     0,     0,     0,     0, 0 }, 0x00D,  3,  3,  0,  4,  2,  2, FC_FIXED or FC_LOCAL or FC_TMACRO
    },{
        { T_CL,  T_DL,  0,     0,     0,     0,     0, 0 }, ; FASTCALL32
        { T_CX,  T_DX,  0,     0,     0,     0,     0, 0 },
        { T_ECX, T_EDX, 0,     0,     0,     0,     0, 0 },
        { 0,     0,     0,     0,     0,     0,     0, 0 }, 0x006,  2,  2,  0,  4,  4,  4, FC_FIXED or FC_LOCAL or FC_TMACRO
    },{
        { T_CL,  T_DL,  T_R8B, T_R9B, 0,     0,     0, 0 }, ; FASTCALL64
        { T_CX,  T_DX,  T_R8W, T_R9W, 0,     0,     0, 0 },
        { T_ECX, T_EDX, T_R8D, T_R9D, 0,     0,     0, 0 },
        { T_RCX, T_RDX, T_R8,  T_R9,  0,     0,     0, 0 }, 0x306,  4,  4,  4, 16,  8,  4, FC_FIXED or FC_RESERVED
    },{
        { 0,     0,     0,     0,     0,     0,     0, 0 }, ; VECTORCALL16
        { 0,     0,     0,     0,     0,     0,     0, 0 },
        { 0,     0,     0,     0,     0,     0,     0, 0 },
        { 0,     0,     0,     0,     0,     0,     0, 0 }, 0x000,  0,  0,  0,  0,  0,  0, 0
    },{
        { T_CL,  T_DL,  0,     0,     0,     0,     0, 0 }, ; VECTORCALL32
        { T_CX,  T_DX,  0,     0,     0,     0,     0, 0 },
        { T_ECX, T_EDX, 0,     0,     0,     0,     0, 0 },
        { 0,     0,     0,     0,     0,     0,     0, 0 }, 0x006,  8,  2,  6,  4,  4,  4, FC_FIXED or FC_LOCAL or FC_TMACRO
    },{
        { T_CL,  T_DL,  T_R8B, T_R9B, 0,     0,     0, 0 }, ; VECTORCALL64
        { T_CX,  T_DX,  T_R8W, T_R9W, 0,     0,     0, 0 },
        { T_ECX, T_EDX, T_R8D, T_R9D, 0,     0,     0, 0 },
        { T_RCX, T_RDX, T_R8,  T_R9,  0,     0,     0, 0 }, 0x306,  6,  4,  6, 16, 16,  4, FC_FIXED or FC_RESERVED
    },{
        { T_AL,  T_DL,  T_BL,  T_CL,  0,     0,     0, 0 }, ; WATCALL16
        { T_AX,  T_DX,  T_BX,  T_CX,  0,     0,     0, 0 },
        { 0,     0,     0,     0,     0,     0,     0, 0 },
        { 0,     0,     0,     0,     0,     0,     0, 0 }, 0x00F,  4,  4,  0,  8,  2,  0, FC_FIXED or FC_LOCAL or FC_TMACRO
    },{
        { T_AL,  T_DL,  T_BL,  T_CL,  0,     0,     0, 0 }, ; WATCALL32
        { T_AX,  T_DX,  T_BX,  T_CX,  0,     0,     0, 0 },
        { T_EAX, T_EDX, T_EBX, T_ECX, 0,     0,     0, 0 },
        { 0,     0,     0,     0,     0,     0,     0, 0 }, 0x00F,  4,  4,  4,  16, 4,  4, FC_FIXED or FC_TMACRO
    },{
        { T_AL,  T_DL,  T_BL,  T_CL,  0,     0,     0, 0 }, ; WATCALL64
        { T_AX,  T_DX,  T_BX,  T_CX,  0,     0,     0, 0 },
        { T_EAX, T_EDX, T_EBX, T_ECX, 0,     0,     0, 0 },
        { T_RAX, T_RDX, T_RBX, T_RCX, 0,     0,     0, 0 }, 0x00F,  4,  4,  4,  32, 8,  4, FC_FIXED or FC_TMACRO
    }

simd_scratch int_t 0
wreg_scratch int_t 0

    .code

fastcall_init proc __ccall

    mov simd_scratch,0
    mov wreg_scratch,0
    ret

fastcall_init endp


get_register proc __ccall reg:int_t, size:int_t

    lea  rcx,SpecialTable
    imul eax,reg,special_item
    mov  edx,size
    .if ( [rcx+rax].special_item.value & OP_XMM )
        mov edx,16
    .endif
    movzx ecx,[rcx+rax].special_item.bytval
    mov eax,reg

    .return .if ( ecx > 15 )
    .switch rdx
    .case 1
        .if ( ecx < 4 )
            .return( &[rcx+T_AL] )
        .endif
        .return( &[rcx+T_SPL-4] )
    .case 2
        .if ( ecx < 8 )
            .return( &[rcx+T_AX] )
        .endif
        .return( &[rcx+T_R8W-8] )
    .case 4
        .if ( ecx < 8 )
            .return( &[rcx+T_EAX] )
        .endif
        .return( &[rcx+T_R8D-8] )
    .case 8
        .if ( ecx < 8 )
            .return( &[rcx+T_RAX] )
        .endif
        .return( &[rcx+T_R8-8] )
    .endsw
    ret

get_register endp


get_fasttype proc fastcall Ofssize:int_t, langtype:int_t

    sub     edx,2
    and     edx,3
    imul    edx,edx,fc_info * 3
    imul    ecx,ecx,fc_info
    lea     rax,fast_table
    add     rax,rcx
    add     rax,rdx
    ret

get_fasttype endp

; reg::reg[::reg::reg] 4, 8, 16, 32

get_nextreg proc watcall private reg:int_t, fp:ptr fc_info

    xchg    rdx,rdi
    mov     ecx,8*4-1
    repnz   scasb
    movzx   eax,byte ptr [rdi]
    mov     rdi,rdx
    ret

get_nextreg endp

;
; fast_pcheck() sets:
;
; paranode:
;   .param_reg      = register
;   .param_id       = param index
;   .param_regs     = number or registers assign to this param
;   .flags          = S_REGPARAM
;   .state          = SYM_TMACRO
;   .string_ptr     = param register name
; proc:
;   .sys_rcnt       = GP register count
;   .sys_xcnt       = SIMD register count
;   .sys_size       = max param size
;
    assume rsi:asym_t
    assume rbx:ptr fc_info

fast_pcheck proc __ccall uses rsi rdi rbx pProc:dsym_t, paranode:dsym_t, used:ptr int_t

   .new regname[32]:sbyte
   .new wordsize:int_t

    UNREFERENCED_PARAMETER(pProc)
    UNREFERENCED_PARAMETER(paranode)
    UNREFERENCED_PARAMETER(used)

    ldr rdi,used
    ldr rsi,paranode
    ldr rcx,pProc

    xor eax,eax
    mov [rsi].string_ptr,rax
    mov al,[rdi+2]
    inc byte ptr [rdi+2]
    mov [rsi].param_id,al
    mov rbx,get_fasttype([rsi].Ofssize, [rcx].asym.langtype)

    SizeFromMemtype( [rsi].mem_type, [rsi].Ofssize, [rsi].type )
    movzx ecx,[rsi].Ofssize
    mov edx,2
    shl edx,cl
    mov wordsize,edx
    .if ( eax == 0 && [rsi].asym.mem_type == MT_ABS )
        mov eax,edx
    .endif
    mov ecx,eax
    dec edx
    add eax,edx
    not edx
    and eax,edx
    .if ( al < [rbx].stk_size )
        mov al,[rbx].stk_size
    .endif
    mov rdx,pProc
    .if ( al > [rdx].asym.sys_size )
        mov [rdx].asym.sys_size,al
    .endif

    mov al,[rsi].mem_type
    .if ( al == MT_TYPE )
        mov rax,[rsi].type
        mov al,[rax].asym.mem_type
    .endif

    .if ( al & MT_FLOAT || al == MT_YWORD )

        .if ( [rbx].flags & FC_FIXED )
            movzx eax,[rsi].param_id
        .else
            movzx eax,byte ptr [rdi+1]
        .endif
        lea edx,[rax+T_XMM0]
        .if ( ecx == 64 )
            lea edx,[rax+T_ZMM0]
        .elseif ( ecx == 32 )
            lea edx,[rax+T_YMM0]
        .endif
        mov [rsi].param_reg,dl
        .if ( al >= [rbx].max_xmm )
           .return( 0 )
        .endif
        inc byte ptr [rdi+1]
        inc [rsi].param_regs

    .else

        mov eax,wordsize
        add eax,eax
        .if ( ecx > eax ) ; span 4 registers ?

            lea edx,[rax*2]
            .if ( edx == ecx && dl <= [rbx].max_int )

                mov dl,[rdi]
                add dl,4
                .if !( dl > [rbx].max_gpr || ( [rbx].flags & FC_FIXED && dl > [rbx].max_reg ) )

                    add byte ptr [rdi],2
                    mov [rsi].param_regs,2
                    mov eax,ecx
                .endif
            .endif
        .endif

        .if ( [rbx].flags & FC_FIXED )
            movzx edx,[rsi].param_id
            .if ( dl < [rdi] )
                mov dl,[rdi]
            .endif
        .else
            movzx edx,byte ptr [rdi]
        .endif
        .if ( dl >= [rbx].max_gpr || ( [rbx].flags & FC_FIXED && dl >= [rbx].max_reg ) )
            .return( 0 )
        .endif

        .if ( eax == ecx && al <= [rbx].max_int )

            mov al,dl
            inc al
            .if ( al >= [rbx].max_gpr || ( [rbx].flags & FC_FIXED && al >= [rbx].max_reg ) )
                .return( 0 )
            .endif
            .for ( eax = 1 : eax < wordsize : eax+=eax )
                add edx,8
            .endf
            mov [rsi].param_reg,[rbx+rdx]
            or  [rsi].flags,S_REGPAIR
            add byte ptr [rdi],2
            add [rsi].param_regs,2

        .elseif ( ecx > wordsize )
            .return( 0 )
        .else
            .for ( eax = 1 : eax < ecx : eax+=eax )
                add edx,8
            .endf
            mov [rsi].param_reg,[rbx+rdx]
            inc byte ptr [rdi]
            inc [rsi].param_regs
        .endif
    .endif

    xor eax,eax
    .if ( [rsi].sflags & S_ISVARARG )
       .return
    .endif

    mov ecx,[rdi]
    mov rdx,pProc
    mov [rdx].asym.sys_rcnt,cl
    mov [rdx].asym.sys_xcnt,ch
    or  [rsi].flags,S_REGPARAM

    .if ( [rbx].flags & FC_TMACRO )

        mov [rsi].state,SYM_TMACRO
        lea rdx,regname
        mov al,[rsi].param_reg
        mov [rsi].string_ptr,LclDup( GetResWName(eax, rdx) )
        mov eax,1
    .endif
    ret

fast_pcheck endp

    assume rbx:nothing

fast_fcstart proc __ccall uses rsi rdi rbx pp:dsym_t, numparams:int_t, start:int_t,
    tokenarray:token_t, value:ptr int_t

   .new opnd:expr
   .new i:int_t
   .new wordsize:int_t
   .new stkparams:int_t = 0
   .new xmmparams:int_t = 0
   .new absparams:int_t = 0
   .new stksize:int_t = 0
   .new Ofssize:int_t
   .new hasvararg:byte = 0

    UNREFERENCED_PARAMETER(pp)
    UNREFERENCED_PARAMETER(numparams)

    ldr rbx,pp
    ldr esi,numparams

    mov ecx,GetSymOfssize( rbx )
    mov Ofssize,ecx
    mov eax,2
    shl eax,cl
    mov wordsize,eax

    mov rdx,[rbx].dsym.procinfo
    .for ( rdi = [rdx].proc_info.paralist : rdi : rdi = [rdi].dsym.prev )

        .if ( [rdi].asym.flags & S_REGPARAM || [rdi].asym.mem_type == MT_ABS )

            dec esi
            .if ( [rdi].asym.mem_type == MT_ABS )
                inc absparams
            .endif

        .elseif ( [rdi].asym.sflags & S_ISVARARG )

            dec numparams
            inc hasvararg
        .else

            inc stkparams
            mov eax,[rdi].asym.total_size
            mov edx,wordsize
            dec edx
            add eax,edx
            not edx
            and eax,edx
            add stksize,eax
            mov dl,[rdi].asym.mem_type
            .if ( dl == MT_TYPE )
                mov rdx,[rdi].asym.type
                mov dl,[rdx].asym.mem_type
            .endif
            .if ( dl & MT_FLOAT || dl == MT_YWORD )
                inc xmmparams
            .endif
        .endif
    .endf

    .if ( hasvararg )

        imul edi,start,asm_tok
        add  rdi,tokenarray

        .for ( ecx = 0 : ecx <= numparams && [rdi].asm_tok.token != T_FINAL : rdi+=asm_tok )

            inc start
            .if ( [rdi].asm_tok.token == T_COMMA )
                inc ecx
            .endif
        .endf

        .while ( [rdi].asm_tok.token != T_FINAL )

            movzx eax,[rdi].asm_tok.token
            .switch eax
            .case T_ID
            .case T_OP_SQ_BRACKET
                mov i,start
                .endc .ifd ( EvalOperand( &i, tokenarray, TokenCount, &opnd, EXPF_NOERRMSG ) == ERROR )
                .if ( opnd.mem_type != MT_EMPTY && opnd.mem_type & MT_FLOAT )
                    inc simd_scratch
                .endif
                .endc
            .case T_REG
               .endc .ifd !( GetValueSp( [rdi].asm_tok.tokval ) & OP_XMM )
            .case T_FLOAT
                inc simd_scratch
               .endc
            .endsw
            .while ( [rdi].asm_tok.token != T_FINAL )

                inc start
                add rdi,asm_tok
               .break .if ( [rdi-asm_tok].asm_tok.token == T_COMMA )
            .endw
            inc wreg_scratch
        .endw
        mov eax,simd_scratch
        sub wreg_scratch,eax
    .endif

    mov rdi,get_fasttype(Ofssize, [rbx].asym.langtype)
    mov rcx,value
    mov eax,simd_scratch
    add eax,wreg_scratch
    mul wordsize
    add eax,stksize
    mov edx,eax

    assume rdi:ptr fc_info

    .if ( [rdi].flags & FC_FIXED )

        .if ( [rdi].flags & FC_RESERVED )

            xor eax,eax
            mov [rcx],eax
            movzx ecx,[rdi].stk_size
            movzx eax,[rbx].asym.sys_size
            .if ( eax > ecx )
                mov ecx,eax
            .endif
            mov [rbx].asym.sys_size,cl

            mov eax,numparams
            add eax,simd_scratch
            add eax,wreg_scratch
            sub eax,absparams
            mov dl,[rdi].max_reg ; this will fail in vectorcall with GPR's > 4..
            .if ( al < dl )
                mov al,dl
            .endif
            mov edx,eax
            .if ( ecx == 8 && eax & 1 ) ; a flag should be set for alignment..
                inc eax
            .endif

            ; v2.31.24: skip stack alloc if inline

            .if ( [rbx].asym.flags & S_ISINLINE && dl == [rdi].max_reg )
                xor eax,eax
            .endif
            mul ecx

            .if ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP )

                mov rdx,CurrProc
                .if ( eax && rdx )
                    or [rdx].asym.sflags,S_STKUSED
                .endif

                mov rdx,sym_ReservedStack
                .if ( eax > [rdx].asym.value )
                    mov [rdx].asym.value,eax
                .endif
            .elseif ( eax )

                mov rcx,value
                mov [rcx],eax
                AddLineQueueX( " sub rsp, %d", eax )
            .endif
            .return( 0 )
        .endif

    .elseif ( Ofssize == USE64 )

        movzx edi,[rbx].asym.sys_xcnt
        movzx esi,[rbx].asym.sys_rcnt
        add edi,simd_scratch
        add edi,xmmparams
        add esi,stkparams
        sub esi,xmmparams
        add esi,wreg_scratch
        xor eax,eax
        .if esi > 6
            lea eax,[rsi-6]
        .endif
        .if edi > 8
            lea eax,[rax+rdi-8]
            mov edi,8
        .endif
        mul wordsize
        mov [rcx],eax

        .if ( eax & 15 && ModuleInfo.win64_flags & W64F_AUTOSTACKSP )

            add eax,8
            mov [rcx],eax
            AddLineQueue( " sub rsp, 8" )
        .endif
        .return( edi )
    .endif

    xor eax,eax
    .if ( Ofssize == USE32 )
        inc eax
    .endif
    .if ( [rdi].flags & FC_LOCAL && !( [rbx].asym.flags & S_ISINLINE ) )
        xor edx,edx
    .endif
    mov [rcx],edx
    ret

fast_fcstart endp

    assume rdi:nothing


fast_return proc __ccall uses rdi rbx p:ptr dsym, buffer:string_t

   .new wordsize:int_t

    ldr rbx,p
    ldr rdi,buffer

    UNREFERENCED_PARAMETER(p)
    UNREFERENCED_PARAMETER(buffer)

    mov ecx,GetSymOfssize( rbx )
    mov eax,2
    shl eax,cl
    mov wordsize,eax
    movzx edx,[rbx].asym.langtype
    get_fasttype(ecx, edx)

    .if ( [rax].fc_info.flags & FC_LOCAL )

        mov rdx,[rbx].dsym.procinfo
        .for ( ecx = 0, rdx = [rdx].proc_info.paralist: rdx: rdx = [rdx].dsym.nextparam )

            .if ( [rdx].asym.state != SYM_TMACRO ) ; v2.34.35: used by ms32..

                add ecx,[rdx].asym.total_size
                mov eax,wordsize
                dec eax
                add ecx,eax
                not eax
                and ecx,eax
            .endif
        .endf
        .if ( ecx )

            .while ( byte ptr [rdi] )
                inc rdi
            .endw
            tsprintf( rdi, "%d", ecx )
        .endif
    .endif
    ret

fast_return endp

fast_fcend proc __ccall pp:dsym_t, numparams:int_t, value:int_t

    ldr rcx,pp
    ldr edx,value

    UNREFERENCED_PARAMETER(pp)
    UNREFERENCED_PARAMETER(numparams)

    .if ( edx )

        GetSymOfssize( rcx )

        lea rdx,stackreg
        mov edx,[rdx+rax*4]
        AddLineQueueX( " add %r, %d", edx, value )
    .endif
    ret

fast_fcend endp

    assume rdi:expr_t

fast_param proc __ccall uses rsi rdi rbx pp:dsym_t, index:int_t, param:dsym_t,
        address:int_t, opnd:ptr expr, paramvalue:string_t, regs_used:ptr byte

   .new src_size:int_t          ; size of param
   .new src_reg:int_t = 0       ; register param
   .new src_rsize:int_t = 0     ; size of register param
   .new src_regno:int_t         ; register param id
   .new dst_size:int_t          ; target size
   .new dst_reg:int_t           ; target register
   .new dst_flt:int_t = 0       ; target GPR float register
   .new dst_rsize:int_t         ; target register size
   .new ext_reg:int_t           ; extended register
   .new sreg:int_t              ; SP/ESP/RSP
   .new cpu:int_t               ; current CPU
   .new wordsize:int_t          ; sizeof(sreg)
   .new ssize:int_t             ; 2/4/8/16/32/64
   .new langid:ptr fc_info      ; pointer into lang_table
   .new maxint:int_t            ; sizeof(reg::reg[::reg::reg])
   .new expsize:int_t           ; expand size
   .new argoffs:int_t = 0       ; current stack offset
   .new rmask:int_t             ; mask for used registers
   .new reg[4]:int_t            ; temp registers
   .new size:int_t              ; temp size
   .new isfloat:byte = FALSE    ; target is float
   .new Ofssize:byte            ; 0/1/2
   .new resstack:byte = FALSE   ; use reserved stack
   .new memtype:byte            ; param type
   .new stack:byte = FALSE      ; stack param
   .new buffer[16]:char_t       ; created float label
   .new destroyed:byte = FALSE  ; register overwritten
   .new isvararg:byte

    UNREFERENCED_PARAMETER(pp)
    UNREFERENCED_PARAMETER(param)
    UNREFERENCED_PARAMETER(opnd)

    ldr rbx,pp
    ldr rsi,param
    ldr rdi,opnd

    mov Ofssize,GetSymOfssize( rbx )
    mov ecx,eax
    mov eax,2
    shl eax,cl
    mov wordsize,eax
    mov langid,get_fasttype(ecx, [rbx].asym.langtype)
    mov rdx,rax
    xor eax,eax
    .if ( [rdx].fc_info.flags & FC_RESERVED )
        inc al
    .endif
    mov resstack,al
    mov al,[rdx].fc_info.exp_size
    mov expsize,eax
    mov al,[rdx].fc_info.max_int
    mov maxint,eax
    mov rmask,[rdx].fc_info.gpr_mask
    mov al,[rsi].mem_type
    .if ( al == MT_TYPE )
        mov rax,[rsi].type
        mov al,[rax].asym.mem_type
    .endif
    mov memtype,al

    ; skip arg if :vararg and inline

    mov rcx,paramvalue
    .if ( byte ptr [rcx] == 0 ||
          ( [rsi].sflags & S_ISVARARG && [rbx].asym.flags & S_ISINLINE ) )
        .return( TRUE )
    .endif

    ; skip loading class pointer if :vararg and inline

    mov rdx,[rbx].dsym.procinfo
    .if ( [rdx].proc_info.flags & PROC_HAS_VARARG &&
          [rbx].asym.flags & S_ISINLINE && [rbx].asym.flags & S_METHOD && !index )
        .return( TRUE )
    .endif

    ; skip arg if :abs

    .if ( memtype == MT_ABS )
        mov [rsi].name,LclDup( paramvalue )
       .return( TRUE )
    .endif

    ; Use SIMD if 64-bit or CPU >= SSE2

    mov cl,Ofssize
    mov eax,ModuleInfo.curr_cpu
    and eax,P_CPU_MASK
    mov cpu,eax
    movzx edx,[rbx].asym.sys_size
    mov ssize,edx
    .if ( resstack )

        mov eax,wordsize
        mov ecx,index
        .if ( al < dl )
            mov al,dl
        .endif
        mul ecx
        mov argoffs,eax
        mov [rsi].param_offs,al
    .endif

    ; get param size

    mov eax,wordsize
    .if ( eax == 8 && !address && [rdi].inst != T_OFFSET && [rsi].sflags & S_ISVARARG )
        mov eax,4 ; v2.11: default size is 32-bit, not 64-bit
    .endif
    mov src_size,eax

    mov cl,[rdi].mem_type
    .if ( cl == 0xF0 ) ; reg::reg
        mov cl,MT_EMPTY
    .endif
    .if ( address || [rdi].inst == T_OFFSET )
    .elseif ( [rdi].kind == EXPR_REG )
        .if ( [rdi].flags & E_INDIRECT )
            .if ( cl != MT_EMPTY )
                .ifd SizeFromMemtype( cl, Ofssize, [rdi].type )
                    mov src_size,eax
                .endif
            .elseif ( memtype == MT_PTR || [rsi].sflags & S_ISVARARG )
                mov src_size,wordsize
            .endif
        .endif
    .elseif ( [rdi].kind == EXPR_ADDR )
        xor eax,eax
        .if ( cl != MT_EMPTY )
            .if ( [rsi].sflags & S_ISVARARG && memtype == MT_EMPTY )
                mov memtype,cl
            .endif
            SizeFromMemtype( cl, Ofssize, [rdi].type )
        .elseif ( memtype == MT_PTR || [rsi].sflags & S_ISVARARG )
            mov eax,wordsize
        .endif
        .if ( eax )
            mov src_size,eax
        .endif
    .endif

    ; check register overwrites

    .if ( [rdi].base_reg )

        mov     rax,[rdi].base_reg
        mov     ecx,[rax].asm_tok.tokval
        lea     rdx,SpecialTable
        imul    eax,ecx,special_item
        add     rdx,rax
        mov     eax,[rdx].special_item.sflags
        and     eax,SFR_SIZMSK
        mov     src_rsize,eax
        mov     eax,ecx
        movzx   ecx,[rdx].special_item.bytval
        mov     edx,[rdx].special_item.value
        mov     src_regno,ecx

        .if ( [rdi].kind == EXPR_REG && !( [rdi].flags & E_INDIRECT ) )
            mov src_reg,eax
        .endif
        .if ( edx & ( OP_XMM or OP_YMM or OP_ZMM ) )
            inc isfloat
        .endif
        .if ( edx & OP_R )

            mov reg,eax
            mov eax,1
            shl eax,cl
            and eax,rmask
            mov rcx,regs_used
            .if ( eax )
                .if ( eax & [rcx] )
                    mov destroyed,1
                .endif
            .elseif ( byte ptr [rcx] & R0_USED && ( edx & OP_A || reg == T_AH ) )
                mov destroyed,TRUE
            .endif
            .if ( [rdi].kind == EXPR_REG && !( [rdi].flags & E_INDIRECT ) )
                mov src_size,src_rsize
            .endif
        .endif
    .endif

    .if ( [rdi].kind == EXPR_ADDR && [rdi].idx_reg )

        mov     rax,[rdi].idx_reg
        mov     ecx,[rax].asm_tok.tokval
        lea     rdx,SpecialTable
        imul    eax,ecx,special_item
        mov     reg,ecx
        movzx   ecx,[rdx+rax].special_item.bytval
        mov     edx,[rdx+rax].special_item.value

        .if ( edx & OP_R )

            mov eax,1
            shl eax,cl
            and eax,rmask
            mov rcx,regs_used

            .if ( eax )
                .if ( eax & [rcx] )
                    mov destroyed,TRUE
                .endif
            .elseif ( byte ptr [rcx] & R0_USED && ( edx & OP_A || reg == T_AH ) )
                mov destroyed,TRUE
            .endif
        .endif
    .endif
    .if ( destroyed )

        asmerr( 2133 )
        inc eax
        mov rcx,regs_used
        mov [rcx],eax
    .endif

    ; get target size

    mov eax,src_size
    mov isvararg,1
    .if !( [rsi].sflags & S_ISVARARG )

        SizeFromMemtype( [rsi].mem_type, Ofssize, [rsi].type )
        mov isvararg,0
    .endif
    mov dst_size,eax

    ; check float

    .if ( [rdi].kind == EXPR_FLOAT || ( memtype != MT_EMPTY && memtype & MT_FLOAT ) )
        inc isfloat
    .endif

    ; get target register: register param or AX

    mov rcx,rbx
    xor ebx,ebx

    .if ( [rsi].flags & S_REGPARAM )

        movzx ebx,[rsi].param_reg
        mov dst_reg,ebx

    .elseif ( [rsi].sflags & S_ISVARARG )

        .if ( memtype == MT_EMPTY )
            mov memtype,[rdi].mem_type
        .endif

        mov rdx,langid
        .if ( [rdx].fc_info.flags & FC_FIXED )

            mov eax,index
            .if ( isfloat )

                .if ( al < [rdx].fc_info.max_xmm )

                    lea ebx,[rax+T_XMM0]
                    .if ( al < [rdx].fc_info.max_gpr )

                        movzx   ecx,Ofssize
                        shl     ecx,3
                        add     ecx,eax
                        movzx   eax,byte ptr [rdx+rcx+8]
                        mov     dst_flt,eax
                    .endif
                .endif

            .elseif ( al < [rdx].fc_info.max_gpr )

                movzx   ecx,Ofssize
                shl     ecx,3
                add     ecx,eax
                movzx   ebx,byte ptr [rdx+rcx+8]
            .endif

        .elseif ( isfloat )

            .if ( simd_scratch )

                movzx eax,[rcx].asym.sys_xcnt
                dec simd_scratch
                mov ecx,simd_scratch
                .if ( [rdx].fc_info.max_xmm > cl )
                    lea ebx,[rax+rcx+T_XMM0]
                .endif
            .endif

        .elseif ( wreg_scratch )

            movzx eax,[rcx].asym.sys_rcnt
            dec wreg_scratch
            mov ecx,wreg_scratch
            .if ( [rdx].fc_info.max_gpr > cl )

                add     eax,ecx
                movzx   ecx,Ofssize
                shl     ecx,3
                add     ecx,eax
                movzx   ebx,byte ptr [rdx+rcx+8]
            .endif
        .endif

        .if ( ebx )

            .ifd ( SizeFromRegister( ebx ) < 16 )

                mov edx,wordsize
                .if ( eax > dst_size )
                    shr edx,1
                    .if ( edx >= dst_size )
                        mov ebx,get_register(ebx, edx)
                    .endif
                .endif
            .endif
            mov dst_reg,ebx
        .endif
    .endif

    .if ( ebx )

        .if ( !isfloat || dst_flt )

            mov ecx,ebx
            .if ( dst_flt )
                mov ecx,dst_flt
            .endif
            lea   rdx,SpecialTable
            imul  eax,ecx,special_item
            movzx ecx,[rdx+rax].special_item.bytval

            .if ( dst_flt || !( src_reg && ecx == src_regno ) )

                ; v2.34.65 - a register is only used if written to

                ; - it may however be sign extended..

                mov eax,1
                shl eax,cl
                mov rcx,regs_used
                or  [rcx],eax
            .endif
        .endif

    .else

        .if ( !resstack )

            mov     rdx,langid
            movzx   eax,[rsi].param_id
            sub     al,[rdx].fc_info.max_gpr
            mul     wordsize
            mov     [rsi].param_offs,al
        .endif

        mov     stack,TRUE
        movzx   eax,Ofssize
        lea     rdx,stackreg
        mov     eax,[rdx+rax*4]
        mov     sreg,eax
        mov     ebx,ModuleInfo.accumulator
        mov     eax,ebx
        mov     edx,wordsize

        .if ( edx > dst_size )
            shr edx,1
            .if ( edx >= dst_size )
                get_register(ebx, edx)
            .endif
        .endif
        mov dst_reg,eax
    .endif

    mov ext_reg,dst_reg
    mov dst_rsize,SizeFromRegister( dst_reg )
    .if ( Ofssize )
        mov ext_reg,get_register(dst_reg, 4)
    .endif
    mov eax,dst_size
    mov ecx,wordsize
    mov edx,ecx
    shr edx,1

    ; handle address and size > stack size first

    .if ( address || eax > ecx )

        .if ( eax == ecx || eax == edx )

            mov esi,ebx
            .if ( eax == edx )
                mov esi,ext_reg
            .endif
            AddLineQueueX( " lea %r, %s", esi, paramvalue )
            .if ( stack )
                .if ( resstack )
                    mov ebx,esi
                .endif
                jmp stack_ebx
            .endif
            .return( TRUE )

        .elseif ( eax < ecx )

            jmp arg_error
        .endif

        ; param size > stack reg

        .if ( isfloat )

            ; 64 bit value <= USE32

            .if ( eax <= 8 )

                .if ( [rdi].kind == EXPR_REG && !( [rdi].flags & E_INDIRECT ) )

                    mov ecx,T_MOVSD
                    .if ( eax == 4 )
                        mov ecx,T_MOVSS
                    .endif
                    .if ( dst_rsize == 16 )
                        .if ( ebx != src_reg )
                            AddLineQueueX( " %r %r, %r", ecx, ebx, src_reg )
                        .endif
                    .else
                        AddLineQueueX( " sub %r, %u\n"
                                       " %r [%r], %r", sreg, src_size, ecx, sreg, src_reg )
                    .endif
                .else
                    AddLineQueueX( " push dword ptr %s[4]\n"
                                   " push dword ptr %s[0]", paramvalue, paramvalue )
                .endif
                .return( TRUE )
            .endif

            ; constant value is 128 bit

            .if ( [rdi].kind == EXPR_FLOAT )

                .if ( stack )

                    .if ( Ofssize == USE32 )

                        AddLineQueueX( " push %u\n"
                                       " push %u\n"
                                       " push %u\n"
                                       " push %u", [rdi].h64_h, [rdi].h64_l, [rdi].l64_h, [rdi].l64_l )
                        .return( TRUE )
                    .endif

                    .if ( !resstack )
                        AddLineQueueX( " sub %r, 16", sreg )
                    .endif
                    .if ( Ofssize == USE64 && [rdi].l64_h == 0 && [rdi].l64_l == 0 )
                        AddLineQueueX( " mov qword ptr [%r+%u], 0", sreg, argoffs )
                    .else
                        AddLineQueueX( " mov dword ptr [%r+%u][0], %u\n"
                                       " mov dword ptr [%r+%u][4], %u", sreg, argoffs, [rdi].l64_l, sreg, argoffs, [rdi].l64_h )
                    .endif
                    AddLineQueueX( " mov dword ptr [%r+%u][8], %u\n"
                                   " mov dword ptr [%r+%u][12], %u", sreg, argoffs, [rdi].h64_l, sreg, argoffs, [rdi].h64_h )
                    .return( TRUE )
                .endif

                .if ( [rdi].l64_l == 0 && [rdi].l64_h == 0 && [rdi].h64_l == 0 && [rdi].h64_h == 0 )

                    AddLineQueueX( " %r %r, %r", T_XORPS, ebx, ebx )
                   .return( TRUE )
                .endif
                lea rsi,buffer
                CreateFloat( eax, rdi, rsi )
                AddLineQueueX( " %r %r, xmmword ptr %s", T_MOVAPS, ebx, rsi )
               .return( TRUE )
            .endif

            ; SIMD reg 16/32/64

            .if ( src_reg )

                .if ( stack )

                    mov ecx,T_MOVAPS
                    .if ( eax > 16 )
                        mov ecx,T_VMOVAPS
                    .endif
                    .if ( !resstack )

                        AddLineQueueX( " sub %r, %u", sreg, eax )
                    .endif
                    AddLineQueueX( " %r [%r+%u], %r", ecx, sreg, argoffs, src_reg )

                .elseif ( ebx != src_reg )

                    mov ecx,T_VMOVAPS
                    .if ( src_reg < T_XMM16 && eax == 16 )
                        mov ecx,T_MOVAPS
                    .endif
                    AddLineQueueX( " %r %r, %r", ecx, ebx, src_reg )
                .endif
                .return( TRUE )
            .endif

            ; memory operand to SIMD

            .if ( stack == FALSE )

                mov ecx,GetValueSp( ebx )
                .if !( ecx & ( OP_XMM or OP_YMM or OP_ZMM ) )
                    jmp arg_error
                .endif
                mov edx,T_VMOVAPS
                mov esi,T_XMMWORD
                .if ( ecx & OP_ZMM )
                    mov esi,T_ZMMWORD
                .elseif ( ecx & OP_YMM )
                    mov esi,T_YMMWORD
                .elseif ( ebx < T_XMM16 )
                    mov edx,T_MOVAPS
                .endif
                AddLineQueueX( " %r %r, %r ptr %s", edx, ebx, esi, paramvalue )
                .if ( dst_flt )
                    AddLineQueueX( " lea %r, %s", dst_flt, paramvalue )
                .endif
               .return( TRUE )
            .endif

            ; param is memory operand

            jmp memory_operand
        .endif

        ; register pair

        .if ( src_reg )

            ; the base reg is the second - reg::[reg]::reg..

            mov rdx,[rdi].base_reg
            .if ( [rdx-asm_tok].asm_tok.token == T_DBL_COLON )

                mov ecx,[rdx-asm_tok*2].asm_tok.tokval
                mov eax,[rdx].asm_tok.tokval

            .else ; single register: upper half is 0

                .if ( stack )

                    .if ( resstack )

                        mov edx,T_WORD
                        .if ( ecx == 4 )
                            mov edx,T_DWORD
                        .elseif ( ecx == 8 )
                            mov edx,T_QWORD
                        .endif
                        AddLineQueueX( " mov [%r+%u], %r\n"
                                       " mov %r ptr [%r+%u+%u], 0", sreg, argoffs, src_reg, edx, sreg, argoffs, wordsize )
                    .else
                        AddLineQueueX( " push 0\n push %r", src_reg )
                    .endif
                .else
                    .if ( ebx != src_reg )
                        AddLineQueueX( " mov %r, %r", ebx, src_reg )
                    .endif
                    .ifd ( get_nextreg(ebx, langid) == 0 )
                        jmp arg_error
                    .endif
                    .if ( wordsize == 8 )
                        get_register( eax, 4 )
                    .endif
                    AddLineQueueX( " xor %r, %r", eax, eax )
                .endif
                .return( TRUE )
            .endif

            mov reg[0],ecx
            mov reg[4],eax
            mov esi,2
            .if ( [rdx+asm_tok].asm_tok.token == T_DBL_COLON )
                mov ecx,[rdx+asm_tok*2].asm_tok.tokval
                mov eax,[rdx+asm_tok*4].asm_tok.tokval
                mov reg[8],ecx
                mov reg[12],eax
                mov esi,4
            .endif
            .if ( stack )
                .if ( resstack )
                    .for ( ebx = argoffs : esi : esi--, ebx += wordsize )
                        AddLineQueueX( " mov [%r+%u], %r", sreg, ebx, reg[rsi*4-4] )
                    .endf
                .else
                    .for ( ebx = 0 : ebx < esi : ebx++ )
                        AddLineQueueX( " push %r", reg[rbx*4] )
                    .endf
                .endif

            .else
                .ifd ( get_nextreg(ebx, langid) == 0 )
                    jmp arg_error
                .endif
                mov edi,eax
                .if ( esi == 4 )
                    .ifd ( get_nextreg(edi, langid) == 0 )
                        jmp arg_error
                    .endif
                    mov esi,eax
                    .ifd ( get_nextreg(esi, langid) == 0 )
                        jmp arg_error
                    .endif
                    mov ecx,eax
                    .if ( eax != reg )
                        AddLineQueueX( " mov %r, %r", ecx, reg )
                    .endif
                    .if ( esi != reg[4] )
                        AddLineQueueX( " mov %r, %r", esi, reg[4] )
                    .endif
                    mov eax,reg[8]
                    mov reg,eax
                    mov eax,reg[12]
                    mov reg[4],eax
                .endif
                .if ( edi != reg )
                    AddLineQueueX( " mov %r, %r", edi, reg )
                .endif
                .if ( ebx != reg[4] )
                    AddLineQueueX( " mov %r, %r", ebx, reg[4] )
                .endif
            .endif
            .return( TRUE )
        .endif

        ; memory or const value to register pair

        .if ( [rdi].kind == EXPR_CONST )

            .if ( stack )
                .if ( resstack )
                    .if ( [rdi].l64_h == 0 && [rdi].l64_l == 0 )
                        AddLineQueueX( " mov qword ptr [%r+%u], 0", sreg, argoffs )
                    .else
                        AddLineQueueX( " mov dword ptr [%r+%u][0], %u\n"
                                       " mov dword ptr [%r+%u][4], %u", sreg, argoffs, [rdi].l64_l, sreg, argoffs, [rdi].l64_h )
                    .endif
                    AddLineQueueX( " mov dword ptr [%r+%u][8], %u\n"
                                   " mov dword ptr [%r+%u][12], %u", sreg, argoffs, [rdi].h64_l, sreg, argoffs, [rdi].h64_h )
                .elseif ( Ofssize == USE16 )
                    .switch eax
                    .case 8
                        movzx ecx,word ptr [rdi].hvalue[2]
                        movzx edx,word ptr [rdi].hvalue[0]
                        AddLineQueueX( " push %u\n push %u", ecx, edx )
                    .case 4
                        movzx ecx,word ptr [rdi].value[2]
                        movzx edx,word ptr [rdi].value[0]
                        AddLineQueueX( " push %u\n push %u", ecx, edx )
                       .endc
                    .default
                        jmp arg_error
                    .endsw
                .elseif ( Ofssize == USE32 )
                    .switch eax
                    .case 16
                        AddLineQueueX( " push %u\n push %u", [rdi].h64_h, [rdi].h64_l )
                    .case 8
                        AddLineQueueX( " push %u\n push %u", [rdi].l64_h, [rdi].l64_l )
                       .endc
                    .default
                        jmp arg_error
                    .endsw
                .elseif ( eax != 16 )
                    jmp arg_error
                .else
                    .if ( [rdi].h64_h == 0 )
                        AddLineQueueX( " push %u", [rdi].h64_l )
                    .else
                        mov rax,regs_used
                        or byte ptr [rax],R0_USED
                        AddLineQueueX( " mov %r, %lu", ebx, [rdi].hlvalue )
                        AddLineQueueX( " push %r", ebx )
                    .endif
                    .if ( [rdi].l64_h == 0 )
                        AddLineQueueX( " push %u", [rdi].l64_l )
                    .else
                        mov rax,regs_used
                        or byte ptr [rax],R0_USED
                        AddLineQueueX( " mov %r, %lu", ebx, [rdi].llvalue )
                        AddLineQueueX( " push %r", ebx )
                    .endif
                .endif
                .return( TRUE )
            .endif
        .endif


        .if ( stack == FALSE )

            .if !( [rsi].flags & S_REGPAIR )

                jmp handle_address
            .endif

            mov reg,ebx
            mov ebx,T_WORD
            .if ( ecx == 4 )
                mov ebx,T_DWORD
            .elseif ( ecx == 8 )
                mov ebx,T_QWORD
            .endif

            .for ( edx = 1 : ecx < eax : edx++, ecx += wordsize )
            .endf
            .for ( size = edx, esi = 0 : esi < size : esi++ )

                mov eax,wordsize
                mul esi

                .if ( [rdi].kind == EXPR_CONST )

                    mov ecx,eax
                    .if ( wordsize == 2 )
                        movzx eax,word ptr [rdi+rax]
                    .else
                        .if ( wordsize == 8 )
                            mov edx,[rdi+rax+4]
                        .endif
                        mov eax,[rdi+rax]
                    .endif

                    .if ( !eax && !edx )

                        ; a negative value needs extension to 128-bit
                        ; however, "-0" is also flagged as negative

                        mov eax,[rdi]
                        or  eax,[rdi+4]
                        or  eax,[rdi+8]
                        or  eax,[rdi+12]

                        .if ( eax && [rdi].flags & E_NEGATIVE && wordsize == 8 )

                            AddLineQueueX( " mov %r, -1", reg )
                        .else
                            mov ecx,reg
                            .if ( wordsize == 8 )
                                mov ecx,get_register( ecx, 4 )
                            .endif
                            AddLineQueueX( " xor %r, %r", ecx, ecx )
                        .endif

                    .elseif ( wordsize < 8 )
                        AddLineQueueX( " mov %r, %u", reg, eax )
                    .elseif ( !edx )
                        mov reg[4],eax
                        mov ecx,get_register(reg, 4)
                        AddLineQueueX( " mov %r, %u", ecx, reg[4] )
                    .else
                        AddLineQueueX( " mov %r, %lu", reg, qword ptr [rdi+rcx] )
                    .endif
                .else
                    AddLineQueueX( " mov %r, %r ptr %s[%u]", reg, ebx, paramvalue, eax )
                .endif
                mov reg,get_nextreg(reg, langid)
            .endf
            .return( TRUE )
        .endif

memory_operand:

        .for ( esi = 1 : ecx < eax : esi+=esi, ecx+=ecx )
        .endf

        .if ( ecx > ssize || ecx > maxint )

handle_address:

            AddLineQueueX( " lea %r, %s", ebx, paramvalue )
            .if ( stack )
                jmp stack_ebx
            .endif
            .return( TRUE )
        .endif

        .if ( [rdi].kind == EXPR_CONST )

            .for ( : esi : esi-- )

                .if ( wordsize == 8 )

                    mov rax,regs_used
                    or byte ptr [rax],R0_USED

                    AddLineQueueX( " mov %r, %lu", ebx, qword ptr [rdi+rsi*8-8] )
                    .if ( resstack )
                        lea ecx,[rsi*8-8]
                        add ecx,argoffs
                        AddLineQueueX( " mov [%r+%u], %r", sreg, ecx, ebx )
                    .else
                        AddLineQueueX( " push %r", ebx )
                    .endif

                .else

                    .if ( wordsize == 4 )
                        mov eax,[rdi+rsi*4-4]
                    .else
                        movzx eax,word ptr [rdi+rsi*2-2]
                    .endif
                    AddLineQueueX( " push %u", eax )
                .endif
            .endf
            .return( TRUE )
        .endif

        mov ebx,T_DWORD
        .switch pascal ecx
        .case 8  : mov ebx,T_QWORD
        .case 16 : mov ebx,T_XMMWORD
        .case 32 : mov ebx,T_YMMWORD
        .case 64 : mov ebx,T_ZMMWORD
        .endsw
        .if ( !resstack )
            AddLineQueueX( " sub %r, %u", sreg, ecx )
        .endif
        AddLineQueueX( " mov [%r+%u], %r ptr %s", sreg, argoffs, ebx, paramvalue )
        mov rax,regs_used
        or byte ptr [rax],R0_USED
       .return( TRUE )
    .endif

    ; here param size <= stack size

    ; handle float param 2..8

    .if ( isfloat )

        mov dl,memtype
        mov ecx,dst_size

        .if ( [rsi].sflags & S_ISVARARG && dl != MT_REAL4 && dl != MT_REAL8 )

            mov dl,MT_REAL4
            .if ( src_rsize == 16 || [rdi].kind == EXPR_FLOAT )
                mov dl,MT_REAL8
            .endif
        .endif
        .if ( ecx > 8 || ( Ofssize < USE64 && ecx > 4 ) )
            jmp arg_error
        .endif
        .if ( ecx < wordsize )
            mov ecx,wordsize
        .endif

        .if ( [rdi].kind == EXPR_REG && !( [rdi].flags & E_INDIRECT ) )

            .if ( stack == FALSE && ebx == src_reg )

                .if ( dst_flt )

                    AddLineQueueX( " movq %r, %r", dst_flt, ebx )
                .endif
                .return( TRUE )
            .endif
            mov esi,edx
            .if ( stack && resstack == FALSE )
                AddLineQueueX( " sub %r, %u", sreg, ecx )
            .endif
            mov edx,esi

            mov ecx,T_MOVAPS
            .if ( dl == MT_REAL4 || dl == MT_REAL2 )
                mov ecx,T_MOVSS
            .elseif ( dl == MT_REAL8 )
                mov ecx,T_MOVSD
            .endif
            .if ( src_reg >= T_XMM16 )
                mov ecx,T_VMOVAPS
                .if ( dl == MT_REAL4 || dl == MT_REAL2 )
                    mov ecx,T_VMOVSS
                .elseif ( dl == MT_REAL8 )
                    mov ecx,T_VMOVSD
                .endif
            .endif

            .if ( ecx == T_VMOVSS || ecx == T_VMOVSD )

                .if ( stack )
                    AddLineQueueX( " %r [%r+%u], %r", ecx, sreg, argoffs, src_reg )
                .else
                    AddLineQueueX( " %r %r, %r, %r", ecx, ebx, ebx, src_reg )
                .endif
            .else
                .if ( stack )
                    AddLineQueueX( " %r [%r+%u], %r", ecx, sreg, argoffs, src_reg )
                .else
                    AddLineQueueX( " %r %r, %r", ecx, ebx, src_reg )
                    .if ( dst_flt )
                        AddLineQueueX( " movq %r, %r", dst_flt, ebx )
                    .endif
                .endif
            .endif
            .return( TRUE )
        .endif

        .if ( stack && resstack && [rdi].kind == EXPR_FLOAT )

            xor eax,eax
            mov rdx,paramvalue
            .if ( [rdi].flags & E_NEGATIVE )
                inc eax
            .endif
            mov rcx,[rdi].float_tok
            .if rcx
                mov rdx,[rcx].asm_tok.string_ptr
            .endif
            atofloat( rdi, rdx, dst_size, eax, 0 )
            AddLineQueueX( " mov dword ptr [%r+%u], %u", sreg, argoffs, [rdi].l64_l )
            .if ( dst_size == 8 )
                AddLineQueueX( " mov dword ptr [%r+%u][4], %u", sreg, argoffs, [rdi].l64_h )
            .endif
            .return( TRUE )
        .endif

        .if ( dl == MT_REAL2 )

            AddLineQueueX( " mov ax, %s", paramvalue )
            .if ( stack )
                .if ( resstack )
                    mov ebx,T_AX
                .endif
                jmp stack_ebx
            .else
                mov rdx,regs_used
                or  byte ptr [rdx],R0_USED
                AddLineQueueX( " movd %r, eax", ebx )
            .endif
            .return( TRUE )
        .endif

        .if ( dl == MT_REAL4 )

            .if ( stack )

                AddLineQueueX( " mov eax, %s", paramvalue )
                .if ( resstack )
                    mov ebx,T_EAX
                .endif
                jmp stack_ebx
            .else
                mov ecx,T_MOVSS
                .if ( [rsi].sflags & S_ISVARARG && wordsize == 8 )
                    mov ecx,T_CVTSS2SD
                    .if ( [rdi].kind == EXPR_FLOAT )
                        mov ecx,T_MOVSD
                    .endif
                .endif
                AddLineQueueX( " %r %r, %s", ecx, ebx, paramvalue )
                .if ( dst_flt )
                    AddLineQueueX( " movq %r, %r", dst_flt, ebx )
                .endif
            .endif
            .return( TRUE )
        .endif

        .if ( stack )

            .if ( wordsize == 8 )

                mov ebx,T_RAX
                AddLineQueueX( " mov %r, %s", ebx, paramvalue )
                jmp stack_ebx

            .elseif ( [rdi].kind == EXPR_FLOAT )

                AddLineQueueX( " push %u\n"
                               " push %u", [rdi].l64_h, [rdi].l64_l )
            .else

                AddLineQueueX( " push dword ptr %s[4]\n"
                               " push dword ptr %s", paramvalue, paramvalue )
            .endif
        .else
            AddLineQueueX( " movsd %r, %s", ebx, paramvalue )
            .if ( dst_flt )
                AddLineQueueX( " movq %r, %r", dst_flt, ebx )
            .endif
        .endif
        .return( TRUE )
    .endif

    ; const param

    .if ( [rdi].kind == EXPR_CONST || ( [rdi].kind == EXPR_ADDR && !( [rdi].flags & E_INDIRECT ) &&
          [rdi].mem_type == MT_EMPTY && [rdi].inst != T_OFFSET ) )

        ; v2.06: support 64-bit constants for params > 4

        .if ( ecx == 8 && eax == 8 )
ifdef _WIN64
            mov rax,[rdi].value64
            .ifs ( rax > INT_MAX || rax < INT_MIN )
else
            mov eax,[rdi].value
            mov edx,[rdi].hvalue
            .ifs ( ( !edx && eax > INT_MAX ) || ( edx < 0 && eax < INT_MIN ) )
endif
                mov rdx,paramvalue
                .if ( stack && resstack )

                    AddLineQueueX( " mov dword ptr [%r+%u], low32(%s)\n"
                                   " mov dword ptr [%r+%u+4], high32(%s)", sreg, argoffs, rdx, sreg, argoffs, rdx )
                .else

                    AddLineQueueX( " mov %r, %s", ebx, rdx )

                    .if ( stack )

                        jmp stack_ebx
                    .endif
                .endif
                .return( TRUE )
            .endif
        .endif

        ; v2.11: no expansion if target type is a pointer and argument
        ; is an address part

        mov rax,[rdi].sym
        .if ( [rsi].mem_type == MT_PTR && [rdi].kind == EXPR_ADDR && [rax].asym.state != SYM_UNDEFINED )
            jmp arg_error
        .endif

        mov rdx,paramvalue
        .if ( stack == FALSE )

            .if ( word ptr [rdx] == "0" || ( [rdi].value == 0 && [rdi].hvalue == 0 ) )

                AddLineQueueX( " xor %r, %r", ext_reg, ext_reg )
               .return( TRUE )
            .endif

        .elseif ( resstack == FALSE )

            .if ( cpu < P_186 )

                AddLineQueueX( " mov %r, %s\n push %r", ebx, rdx, ebx )
                mov rax,regs_used
                or byte ptr [rax],R0_USED
            .else
                AddLineQueueX( " push %s", rdx )
            .endif
            .return( TRUE )
        .endif

        .if ( stack )

            mov eax,dst_size
            mov ecx,T_QWORD
            .if ( eax == 1 )
                mov ecx,T_BYTE
            .elseif ( eax == 2 )
                mov ecx,T_WORD
            .elseif ( eax == 4 )
                ;
                ; added v2.33.57 for vararg
                ; - this fails for NULL pointers as the upper value is not cleared
                ; - the default size is 4
                ;
                .if ( [rdi].value || !( [rsi].sflags & S_ISVARARG ) )

                    mov ecx,T_DWORD
                .endif
            .endif
            AddLineQueueX( " mov %r ptr [%r+%u], %s", ecx, sreg, argoffs, rdx )
        .else
            .if ( [rdi].hvalue == 0 )
                mov ebx,ext_reg
            .endif
            AddLineQueueX( " mov %r, %s", ebx, rdx )
        .endif
        .return( TRUE )
    .endif

    ; register param

    .if ( src_reg )

        mov edx,src_rsize
        .if ( edx < eax && memtype == MT_PTR )
            jmp arg_error
        .endif

        .if ( edx > dst_rsize )

            mov src_reg,get_register( src_reg, dst_rsize )
            .if ( eax == dst_reg && !stack )
                .return( TRUE )
            .endif
            mov src_rsize,dst_rsize
            mov src_size,eax
            mov edx,eax
        .endif

        .if ( stack )

            .if ( resstack )
                .if ( isvararg && expsize > edx )
                    .if ( cpu >= P_386 )
                        mov esi,T_MOVZX
                        .if ( IS_SIGNED([rdi].mem_type) )
                            mov esi,T_MOVSX
                        .endif
                        AddLineQueueX( " %r %r, %r", esi, dst_reg, src_reg )
                        mov src_reg,dst_reg
                        mov rax,regs_used
                        or byte ptr [rax],R0_USED
                    .endif
                .endif
                AddLineQueueX( " mov [%r+%u], %r", sreg, argoffs, src_reg )
            .else
                AddLineQueueX( " push %r", get_register( src_reg, wordsize ) )
            .endif
            .return( TRUE )
        .endif

        mov esi,T_MOV
        .if ( expsize > edx )

            mov ebx,get_register( dst_reg, expsize )
            .if ( cpu >= P_386 )
                mov esi,T_MOVZX
                .if ( IS_SIGNED([rdi].mem_type) )
                    mov esi,T_MOVSX
                .endif
            .else
                jmp @F
            .endif

        .elseif ( dst_rsize > edx )

            .if ( cpu >= P_386 )

                mov esi,T_MOVZX
                .if ( IS_SIGNED([rdi].mem_type) )
                    mov esi,T_MOVSX
                .endif
                .if ( edx == 4 )
                    .if ( esi == T_MOVZX )
                        mov esi,T_MOV
                        mov ebx,get_register( dst_reg, 4 )
                    .else
                        mov esi,T_MOVSXD
                    .endif
                .endif
            .else
             @@:
                imul  eax,ebx,special_item
                lea   rdx,SpecialTable
                movzx ecx,[rdx+rax].special_item.bytval
                lea   ebx,[rcx+T_AL]
                add   ecx,T_AH
                AddLineQueueX( " mov %r, 0", ecx )
            .endif
        .endif
        .if ( ebx != src_reg )
            AddLineQueueX( " %r %r, %r", esi, ebx, src_reg )
        .endif
        .return( TRUE )
    .endif

    ; memory operand

    mov esi,eax ; find out if size fits in a register
    bsf eax,eax
    bsr esi,esi

    .if ( eax == esi )

        .if ( src_size > dst_rsize )
            mov src_size,eax
        .endif
        mov eax,src_size
        .if ( eax == ecx && stack && !resstack )

            AddLineQueueX( " push %s", paramvalue )
           .return( TRUE )
        .endif

        mov esi,T_MOV
        mov edx,dst_rsize

        .if ( !stack && expsize > edx )

            mov dst_reg,get_register( dst_reg, expsize )
            mov dst_rsize,expsize
            mov eax,src_size
        .endif
        mov ecx,T_BYTE
        .if ( eax == 2 )
            mov ecx,T_WORD
        .elseif ( eax == 4 )
            mov ecx,T_DWORD
        .elseif ( eax == 8 )
            mov ecx,T_QWORD
        .endif
        .if ( eax < dst_rsize )

            .if ( cpu >= P_386 )

                mov esi,T_MOVZX
                .if ( IS_SIGNED([rdi].mem_type) )
                    mov esi,T_MOVSX
                .endif
                .if ( src_size == 4 )
                    .if ( esi == T_MOVZX )
                        mov dst_reg,get_register( dst_reg, 4 )
                        mov esi,T_MOV
                        mov ecx,T_DWORD
                    .else
                        mov esi,T_MOVSXD
                    .endif
                .endif
            .else

                imul    eax,ebx,special_item
                lea     rdx,SpecialTable
                movzx   ecx,[rdx+rax].special_item.bytval
                lea     eax,[rcx+T_AL]
                mov     dst_reg,eax
                add     ecx,T_AH

                AddLineQueueX( " mov %r, 0", ecx )
                mov ecx,T_BYTE
            .endif
        .endif
        AddLineQueueX( " %r %r, %r ptr %s", esi, dst_reg, ecx, paramvalue )

        .if ( stack )

            .if ( resstack )
                mov ebx,dst_reg
            .endif
            jmp stack_ebx
        .endif
        .return( TRUE )
    .endif

    ; Here USE16 is done and size left is 3, 5, 6, or 7
    ;
    ; regression from v2.29.02 - see invoke40a.asm and invoke6440.asm
    ; v2.34.65 - optimized to use one register
    ;
    ; We can't read beyond the size here (there may be dragons)
    ; so we use register-size chunks + shift

    mov ecx,src_size
    mov edi,T_DWORD     ; read 2 or 4 bytes from the end
    mov esi,1           ; bytes left
    .switch ecx
    .case 7             ; dword ptr m7[3]
        inc esi
    .case 6             ; dword ptr m6[2]
        inc esi
    .case 5             ; dword ptr m5[1]
       .endc
    .case 3             ; word ptr m3[1]
        mov edi,T_WORD
       .endc
    .default
        jmp arg_error
    .endsw

    sub ecx,esi
    mov ecx,get_register(ebx, ecx)
    mov edx,T_MOV

    .if ( edi == T_WORD )

        mov edx,T_MOVZX ; clear upper part if reg32
        mov ecx,ebx
    .endif
    AddLineQueueX( " %r %r, %r ptr %s[%u]", edx, ecx, edi, paramvalue, esi )

    .if ( esi > 1 ) ; 6 or 7

        sub esi,2
        mov ecx,get_register(ebx, 2)
        AddLineQueueX( " shl %r, 16\n mov %r, word ptr %s[%u]", ebx, ecx, paramvalue, esi )
    .endif

    .if ( esi ) ; 7 is reg32 + reg16 + reg8

        mov ecx,get_register(ebx, 1)
        AddLineQueueX( " shl %r, 8\n mov %r, byte ptr %s", ebx, ecx, paramvalue )
    .endif

    .if ( stack )

stack_ebx:

        mov rax,regs_used
        or byte ptr [rax],R0_USED
        .if ( resstack )
            AddLineQueueX( " mov [%r+%u], %r", sreg, argoffs, ebx )
        .else
            AddLineQueueX( " push %r", ebx )
        .endif
    .endif
    .return( TRUE )

arg_error:

    mov edx,index
    inc edx
    asmerr( 2114, edx )
    ret

fast_param endp

    END
