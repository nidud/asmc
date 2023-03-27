; ASSUME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; handles ASSUME
;

include string.inc
include malloc.inc
include asmc.inc
include token.inc
include hll.inc
include assume.inc
include types.inc
include segment.inc
include parser.inc
include operands.inc
include lqueue.inc
include expreval.inc
include fastpass.inc

OperandSize proto fastcall :int_t, :ptr code_info

NUM_STDREGS equ 16

; todo: move static variables to ModuleInfo

.data?

; table SegAssume is for the segment registers;
; for order see enum assume_segreg.

SegAssumeTable assume_info NUM_SEGREGS dup(<>)

; table StdAssume is for the standard registers;
; order does match regno in special.h:
; (R|E)AX=0, (R|E)CX=1, (R|E)DX=2, (R|E)BX=3
; (R|E)SP=4, (R|E)BP=5, (R|E)SI=6, (R|E)DI=7
; R8 .. R15.

StdAssumeTable assume_info NUM_STDREGS dup(<>)

stdsym asym_t NUM_STDREGS dup(?)

saved_SegAssumeTable assume_info NUM_SEGREGS dup(<>)
saved_StdAssumeTable assume_info NUM_STDREGS dup(<>)

; v2.05: saved type info content

saved_StdTypeInfo stdassume_typeinfo NUM_STDREGS dup(<>)

.data

; order to use for assume searches

searchtab int_t ASSUME_DS, ASSUME_SS, ASSUME_ES, ASSUME_FS, ASSUME_GS, ASSUME_CS

szError   char_t "ERROR",0
szNothing char_t "NOTHING",0
szDgroup  char_t "DGROUP",0

.code


SetSegAssumeTable proc fastcall uses rsi rdi savedstate:ptr

    mov rsi,rcx
    lea rdi,SegAssumeTable
    mov ecx,sizeof(SegAssumeTable)
    rep movsb
    ret

SetSegAssumeTable endp


GetSegAssumeTable proc fastcall uses rsi rdi savedstate:ptr

    mov rdi,rcx
    lea rsi,SegAssumeTable
    mov ecx,sizeof(SegAssumeTable)
    rep movsb
    ret

GetSegAssumeTable endp


; unlike the segment register assumes, the
; register assumes need more work to save/restore the
; current status, because they have their own
; type symbols, which may be reused.
; this functions is also called by context.c, ContextDirective()!


    assume rdi:ptr assume_info, rsi:ptr stdassume_typeinfo, rdx:asym_t


SetStdAssumeTable proc fastcall uses rsi rdi savedstate:ptr, ti:ptr stdassume_typeinfo

    lea rdi,StdAssumeTable
    mov rsi,rcx
    mov ecx,sizeof(StdAssumeTable)
    mov rax,rdi
    rep movsb

    mov rdi,rax
    mov rsi,rdx

    .for ( ecx = 0: ecx < NUM_STDREGS: ecx++,
           rdi += assume_info, rsi += stdassume_typeinfo )

        .if ( [rdi].symbol )

            mov rdx,[rdi].symbol

            mov [rdx].type,        [rsi].type
            mov [rdx].target_type, [rsi].target_type
            mov [rdx].mem_type,    [rsi].mem_type
            mov [rdx].ptr_memtype, [rsi].ptr_memtype
            mov [rdx].is_ptr,      [rsi].is_ptr
        .endif
    .endf
    ret

SetStdAssumeTable endp


    assume rsi:ptr assume_info, rdi:ptr stdassume_typeinfo

GetStdAssumeTable proc fastcall uses rsi rdi savedstate:ptr, ti:ptr stdassume_typeinfo

    mov rdi,rcx
    lea rsi,StdAssumeTable
    mov ecx,sizeof(StdAssumeTable)
    rep movsb

    lea rsi,StdAssumeTable
    mov rdi,rdx

    .for ( : ecx < NUM_STDREGS: ecx++,
           rdi += stdassume_typeinfo, rsi += assume_info )

        .if ( [rsi].symbol )

            mov rdx,[rsi].symbol
            mov [rdi].type,        [rdx].type
            mov [rdi].target_type, [rdx].target_type
            mov [rdi].mem_type,    [rdx].mem_type
            mov [rdi].ptr_memtype, [rdx].ptr_memtype
            mov [rdi].is_ptr,      [rdx].is_ptr
        .endif
    .endf
    ret

GetStdAssumeTable endp

    assume rdx:nothing, rdi:nothing, rsi:nothing


AssumeSaveState proc

    GetSegAssumeTable( &saved_SegAssumeTable )
    GetStdAssumeTable( &saved_StdAssumeTable, &saved_StdTypeInfo )
    ret

AssumeSaveState endp


    assume rdx:ptr assume_info

AssumeInit proc fastcall uses rbx pass:int_t ;; pass may be -1 here!

    mov ebx,ecx
    xor eax,eax

    .for ( rdx = &SegAssumeTable,
           ecx = 0 : ecx < NUM_SEGREGS : ecx++, rdx += assume_info )

        mov [rdx].symbol,rax
        mov [rdx].error,al
        mov [rdx].is_flat,al
    .endf

    ; the GPR assumes are handled somewhat special by masm.
    ; they aren't reset for each pass - instead they keep their value.

    .if ( ebx <= PASS_1 ) ; v2.10: just reset assumes in pass one

        .for ( rdx = &StdAssumeTable,
               ecx = 0 : ecx < NUM_STDREGS : ecx++, rdx += assume_info )

            mov [rdx].symbol,rax
            mov [rdx].error,al
        .endf

        .if ( ebx == PASS_1 )

            lea  rdx,stdsym
            mov  ecx,sizeof(stdsym)
            xchg rdi,rdx
            rep  stosb
            mov  rdi,rdx
        .endif
    .endif

    .if ( ebx > PASS_1 && UseSavedState )

        SetSegAssumeTable( &saved_SegAssumeTable )
        SetStdAssumeTable( &saved_StdAssumeTable, &saved_StdTypeInfo )
    .endif
    ret

AssumeInit endp

    assume edx:nothing


; generate assume lines after .MODEL directive
; model is in ModuleInfo.model, it can't be MODEL_NONE.

ModelAssumeInit proc

    ; Generates codes for assume

    mov al,ModuleInfo._model
    and eax,7

    .switch jmp rax

    .case MODEL_FLAT

        lea rdx,szError
        mov rcx,rdx
        .if ( ModuleInfo.fctype == FCT_WIN64 || ModuleInfo.fctype == FCT_VEC64 )
            lea rcx,szNothing
        .endif
        AddLineQueueX( "assume cs:flat,ds:flat,ss:flat,es:flat,fs:%s,gs:%s", rdx, rcx )
       .endc

    .case MODEL_TINY
    .case MODEL_SMALL
    .case MODEL_COMPACT
    .case MODEL_MEDIUM
    .case MODEL_LARGE
    .case MODEL_HUGE

ifndef ASMC64

        ; v2.03: no DGROUP for COFF/ELF

        .endc .if ( Options.output_format == OFORMAT_COFF || Options.output_format == OFORMAT_ELF )

        lea rdx,szDgroup
        .if ( ModuleInfo._model != MODEL_TINY )
            mov rdx,SimGetSegName( SIM_CODE )
        .endif
        lea rcx,@CStr("assume cs:%s,ds:%s,ss:%s")
        .if ( ModuleInfo.distance == STACK_FAR )
            lea rcx,@CStr("assume cs:%s,ds:%s")
        .endif
        lea rax,szDgroup
        AddLineQueueX( rcx, rdx, rax, rax )
        .endc
endif
    .case MODEL_NONE
    .endsw
    ret

ModelAssumeInit endp


; used by INVOKE directive

GetStdAssume proc fastcall reg:int_t

    imul ecx,ecx,assume_info
    lea rax,StdAssumeTable
    mov rax,[rax+rcx].assume_info.symbol

    .if ( rax )

        .if ( [rax].asym.mem_type == MT_TYPE )
            mov rax,[rax].asym.type
        .else
            mov rax,[rax].asym.target_type
        .endif
    .endif
    ret

GetStdAssume endp


; v2.05: new, used by
; expression evaluator if a register is used for indirect addressing

GetStdAssumeEx proc watcall reg:int_t

    .if ( eax < NUM_STDREGS )

        push rcx
        imul ecx,eax,assume_info
        lea  rax,StdAssumeTable
        mov  rax,[rax+rcx].assume_info.symbol
        pop  rcx
    .else
        xor eax,eax
    .endif
    ret

GetStdAssumeEx endp


; Handles ASSUME
; syntax is :
; - ASSUME
; - ASSUME NOTHING
; - ASSUME segregister : seglocation [, segregister : seglocation ]
; - ASSUME dataregister : qualified type [, dataregister : qualified type ]
; - ASSUME register : ERROR | NOTHING | FLAT

    assume rbx:token_t, rdi:ptr assume_info

AssumeDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

   .new reg:int_t = 0
   .new j:int_t = 0
   .new size:int_t
   .new flags:uint_t = 0
   .new info:ptr assume_info
   .new segtable:int_t = 0
   .new ti:qualified_type
   .new opnd:expr

    inc i
    imul ebx,i,asm_tok
    add rbx,tokenarray

    .for ( : i < Token_Count : i++, rbx += asm_tok )

        .if ( [rbx].token == T_ID )
            .ifd !tstricmp( [rbx].string_ptr, &szNothing )

                AssumeInit(-1)
                inc i
               .break
            .endif
        .endif

        ; ---- get the info ptr for the register ----

        xor edi,edi

        .if ( [rbx].token == T_REG )

            mov reg,[rbx].tokval
            mov flags,GetValueSp(eax)
            movzx eax,GetRegNo(reg)
            mov j,eax
            imul eax,eax,assume_info

            .if ( flags & OP_SR )
                lea rdi,SegAssumeTable
                add rdi,rax
                mov segtable,TRUE
            .elseif ( flags & OP_R )
                lea rdi,StdAssumeTable
                add rdi,rax
                mov segtable,FALSE
            .endif
        .endif
        .if ( rdi == NULL )
            .return( asmerr(2008, [rbx].string_ptr ) )
        .endif

        mov ecx,ModuleInfo.curr_cpu
        and ecx,P_CPU_MASK
        .if ( ( cx ) < GetCpuSp(reg) )
            .return( asmerr( 2085 ) )
        .endif
        .if ( [rbx+asm_tok].token != T_COLON )
            .return( asmerr( 2065, "" ) )
        .endif
        .if ( [rbx+2*asm_tok].token == T_FINAL )
            .return( asmerr( 2009 ) )
        .endif

        add i,2 ; go past register
        add rbx,2*asm_tok

        ; check for ERROR and NOTHING */

        .ifd !tstricmp( [rbx].string_ptr, &szError )
            .if ( segtable )
                mov [rdi].is_flat,FALSE
                mov [rdi].error,TRUE
            .else
                mov eax,flags
                and eax,OP_R
                .if ( reg >= T_AH && reg <= T_BH )
                    mov eax,RH_ERROR
                .endif
                or [rdi].error,al
            .endif
            mov [rdi].symbol,NULL
            inc i
        .elseifd ( !tstricmp( [rbx].string_ptr, &szNothing ))
            .if ( segtable )
                mov [rdi].is_flat,FALSE
                mov [rdi].error,FALSE
            .else
                mov eax,flags
                and eax,OP_R
                .if ( reg >= T_AH && reg <= T_BH )
                    mov eax,RH_ERROR
                .endif
                not eax
                mov cl,[rdi].error
                and al,cl
                mov [rdi].error,al
            .endif
            mov [rdi].symbol,NULL
            inc i

        .elseif ( segtable == FALSE )

            ;; v2.05: changed to use new GetQualifiedType() function
            mov ti.size,0
            mov ti.is_ptr,0
            mov ti.is_far,FALSE
            mov ti.mem_type,MT_EMPTY
            mov ti.ptr_memtype,MT_EMPTY
            mov ti.symtype,NULL
            mov ti.Ofssize,ModuleInfo.Ofssize

            .return .ifd GetQualifiedType( &i, tokenarray, &ti ) == ERROR

            ;; v2.04: check size of argument!
            mov size,OperandSize(flags, NULL)
            .if ( ( ti.is_ptr == 0 && eax != ti.size ) || ( ti.is_ptr > 0 && al < CurrWordSize ) )
                .return( asmerr( 2024 ) )
            .endif

            mov eax,flags
            and eax,OP_R
            .if ( reg >= T_AH && reg <= T_BH )
                mov eax,RH_ERROR
            .endif
            not eax
            mov cl,[rdi].error
            and al,cl
            mov [rdi].error,al

            mov esi,j

            assume rsi:asym_t
            lea rcx,stdsym
            mov rax,[rcx+rsi*asym_t]

            .if ( rax == NULL )

                CreateTypeSymbol( NULL, "", FALSE )

                lea rcx,stdsym
                mov [rcx+rsi*asym_t],rax
                mov [rax].asym.typekind,TYPE_TYPEDEF
            .endif
            mov rsi,rax

            mov [rsi].total_size,  ti.size
            mov [rsi].mem_type,    ti.mem_type
            mov [rsi].is_ptr,      ti.is_ptr
            mov [rsi].is_far,      ti.is_far
            mov [rsi].Ofssize,     ti.Ofssize
            mov [rsi].ptr_memtype, ti.ptr_memtype ;; added v2.05 rc13
            .if ( ti.mem_type == MT_TYPE )
                mov [rsi].type,    ti.symtype
            .else
                mov [rsi].target_type,ti.symtype
            .endif
            mov [rdi].symbol,rsi

        .else ; segment register


            ; v2.08: read expression with standard evaluator
            .return .ifd EvalOperand( &i, tokenarray, Token_Count, &opnd, 0 ) == ERROR
            mov rsi,opnd.sym

            .switch ( opnd.kind )
            .case EXPR_ADDR
                .if ( rsi == NULL || opnd.flags & E_INDIRECT || opnd.value )
                    .return( asmerr( 2096 ) );
                .elseif ( [rsi].state == SYM_UNDEFINED )

                    ; ensure that directive is rerun in pass 2
                    ; so an error msg can be emitted.

                    .if ( Parse_Pass == PASS_1 )
                        StoreLine( CurrSource, 0, 0 )
                    .endif

                    mov [rdi].symbol,rsi
                .elseif ( ( [rsi].state == SYM_SEG || [rsi].state == SYM_GRP ) && opnd.inst == EMPTY )
                    mov [rdi].symbol,rsi
                .elseif ( opnd.inst == T_SEG )
                    mov [rdi].symbol,[rsi].segm
                .else
                    .return( asmerr( 2096 ) )
                .endif
                xor eax,eax
                mov rcx,ModuleInfo.flat_grp
                .if ( [rdi].symbol == rcx )
                    inc eax
                .endif
                mov [rdi].is_flat,al
                .endc
            .case EXPR_REG
                mov rdx,opnd.base_reg
                mov esi,[rdx].asm_tok.tokval

                .if ( GetValueSp(esi) & OP_SR )
                    movzx ecx,GetRegNo(esi)
                    imul ecx,ecx,assume_info
                    lea rdx,SegAssumeTable
                    mov rax,[rdx+rcx].assume_info.symbol
                    mov [rdi].symbol,rax
                    mov al,[rdx+rcx].assume_info.is_flat
                    mov [rdi].is_flat,al
                    .endc
                .endif
            .default
                .return( asmerr( 2096 ) )
            .endsw
            mov [rdi].error,FALSE
        .endif

        ;; comma expected

        imul ebx,i,asm_tok
        add rbx,tokenarray

        .break .if ( i < Token_Count && [rbx].token != T_COMMA )
    .endf

    .if ( i < Token_Count )

        imul ebx,i,asm_tok
        add rbx,tokenarray
       .return( asmerr( 2008, [rbx].tokpos ) )
    .endif
    .return( NOT_ERROR )

AssumeDirective endp

    assume rsi:nothing, rdi:nothing, rbx:nothing


; for a symbol, search segment register which holds segment
; part of symbol's address in assume table.
; - sym: segment of symbol for which to search segment register
; - def: prefered default register (or ASSUME_NOTHING )
; - search_grps: if TRUE, check groups as well
;
; for data items, Masm checks assumes in this order:
;   DS, SS, ES, FS, GS, CS

    assume rdx:ptr assume_info

search_assume proc __ccall uses rsi rdi rbx sym:asym_t, def:int_t, search_grps:int_t

    mov rdi,sym
    mov ebx,def

    .if ( rdi == NULL )
        .return( ASSUME_NOTHING )
    .endif

    mov rsi,GetGroup(rdi)
    lea rcx,SegAssumeTable

    ; first check the default segment register

    .if ( ebx != ASSUME_NOTHING )

        mov  eax,ebx
        imul edx,ebx,assume_info
        add  rdx,rcx

        .return .if ( rdi == [rdx].symbol )
        .if ( search_grps && rsi )

            .return .if ( [rdx].is_flat && rsi == ModuleInfo.flat_grp )
            .return .if ( rsi == [rdx].symbol )
        .endif
    .endif

    ; now check all segment registers

    lea rdi,SegAssumeTable
    .for ( rbx = &searchtab, ecx = 0 : ecx < NUM_SEGREGS : ecx++ )

        mov  eax,[rbx+rcx*4]
        imul edx,eax,assume_info
        mov  rdx,[rdi+rdx].symbol
       .return .if ( rdx == sym )
    .endf

    ; now check the groups

    .if ( search_grps && rsi )

        .for ( ecx = 0 : ecx < NUM_SEGREGS : ecx++ )

            mov eax,[rbx+rcx*4]
            imul edx,eax,assume_info

            .return .if ( [rdi+rdx].is_flat && rsi == ModuleInfo.flat_grp )
            .return .if ( rsi == [rdi+rdx].symbol )
        .endf
    .endif
    .return( ASSUME_NOTHING )

search_assume endp

;
; called by the parser's seg_override() function if
; a segment register override has been detected.
; - override: segment register override (0,1,2,3,4,5)
;

GetOverrideAssume proc fastcall override:int_t

    imul edx,override,assume_info
    lea rcx,SegAssumeTable
    mov rax,[rdx+rcx].symbol
    .if ( [rdx+rcx].is_flat )
        mov rax,ModuleInfo.flat_grp
    .endif
    ret

GetOverrideAssume endp

;
; GetAssume():
; called by check_assume() in parser.c
; in:
; - override: SegOverride
; - sym: symbol in current memory operand
; - def: default segment assume value
; to be fixed: check if symbols with state==SYM_STACK are handled correctly.
;

GetAssume proc __ccall override:asym_t, sym:asym_t, def:int_t, passume:ptr asym_t

    imul eax,def,assume_info
    lea rdx,SegAssumeTable
    add rdx,rax
    mov eax,def

    .if ( ( eax != ASSUME_NOTHING ) && [rdx].is_flat )

        mov rdx,ModuleInfo.flat_grp
        mov rcx,passume
        mov [rcx],rdx
       .return
    .endif

    mov rcx,sym
    .if ( override != NULL )

        search_assume( override, eax, FALSE )

        ; v2.10: added

    .elseif ( [rcx].asym.state == SYM_STACK )

        ; stack symbols don't have a segment part.
        ; In case [R|E]BP is used as base, it doesn't matter.
        ; However, if option -Zg is set, this isn't true.

        mov eax,ASSUME_SS
    .else
        search_assume( [rcx].asym.segm, eax, TRUE )
    .endif

    .if ( eax == ASSUME_NOTHING )
        mov rcx,sym
        .if ( rcx && [rcx].asym.state == SYM_EXTERNAL && [rcx].asym.segm == NULL )
            mov eax,def
        .endif
    .endif

    .if ( eax != ASSUME_NOTHING )

        imul edx,eax,assume_info
        lea rcx,SegAssumeTable
        mov rcx,[rdx+rcx].symbol
        assume rdx:nothing
        mov rdx,passume
        mov [rdx],rcx
       .return
    .endif

    mov rcx,passume
    xor eax,eax
    mov [rcx],rax

   .return ASSUME_NOTHING

GetAssume endp

    end
