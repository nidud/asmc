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

OperandSize proto :int_t, :ptr code_info

NUM_STDREGS equ 16

;; todo: move static variables to ModuleInfo

.data?

;; table SegAssume is for the segment registers;
;; for order see enum assume_segreg.
;;
SegAssumeTable assume_info NUM_SEGREGS dup(<>)

;; table StdAssume is for the standard registers;
;; order does match regno in special.h:
;; (R|E)AX=0, (R|E)CX=1, (R|E)DX=2, (R|E)BX=3
;; (R|E)SP=4, (R|E)BP=5, (R|E)SI=6, (R|E)DI=7
;; R8 .. R15.
;;
StdAssumeTable assume_info NUM_STDREGS dup(<>)

stdsym asym_t NUM_STDREGS dup(?)

saved_SegAssumeTable assume_info NUM_SEGREGS dup(<>)
saved_StdAssumeTable assume_info NUM_STDREGS dup(<>)

;; v2.05: saved type info content
saved_StdTypeInfo stdassume_typeinfo NUM_STDREGS dup(<>)

.data

;; order to use for assume searches
searchtab int_t ASSUME_DS, ASSUME_SS, ASSUME_ES, ASSUME_FS, ASSUME_GS, ASSUME_CS


szError   char_t "ERROR",0
szNothing char_t "NOTHING",0
szDgroup  char_t "DGROUP",0

.code

SetSegAssumeTable proc uses esi edi savedstate:ptr

    lea edi,SegAssumeTable
    mov esi,savedstate
    mov ecx,sizeof(SegAssumeTable)
    rep movsb
    ret

SetSegAssumeTable endp

GetSegAssumeTable proc uses esi edi savedstate:ptr

    mov edi,savedstate
    lea esi,SegAssumeTable
    mov ecx,sizeof(SegAssumeTable)
    rep movsb
    ret

GetSegAssumeTable endp

;; unlike the segment register assumes, the
;; register assumes need more work to save/restore the
;; current status, because they have their own
;; type symbols, which may be reused.
;; this functions is also called by context.c, ContextDirective()!
;;

SetStdAssumeTable proc uses esi edi savedstate:ptr, ti:ptr stdassume_typeinfo

    lea edi,StdAssumeTable
    mov esi,savedstate
    mov ecx,sizeof(StdAssumeTable)
    mov edx,edi
    rep movsb

    mov edi,edx
    mov esi,ti

    assume edi:ptr assume_info
    assume esi:ptr stdassume_typeinfo

    .for ( ecx = 0: ecx < NUM_STDREGS: ecx++,
           edi += assume_info, esi += stdassume_typeinfo )

        .if [edi].symbol

            mov edx,[edi].symbol
            assume edx:asym_t

            mov [edx].type,        [esi].type
            mov [edx].target_type, [esi].target_type
            mov [edx].mem_type,    [esi].mem_type
            mov [edx].ptr_memtype, [esi].ptr_memtype
            mov [edx].is_ptr,      [esi].is_ptr

            assume edx:nothing

        .endif
    .endf
    assume edi:nothing
    assume esi:nothing
    ret

SetStdAssumeTable endp

    assume esi:ptr assume_info
    assume edi:ptr stdassume_typeinfo

GetStdAssumeTable proc uses esi edi savedstate:ptr, ti:ptr stdassume_typeinfo

    mov edi,savedstate
    lea esi,StdAssumeTable
    mov ecx,sizeof(StdAssumeTable)
    rep movsb

    lea esi,StdAssumeTable
    mov edi,ti

    .for ( : ecx < NUM_STDREGS: ecx++,
           edi += stdassume_typeinfo, esi += assume_info )

        .if ( [esi].symbol )

            mov edx,[esi].symbol
            assume edx:asym_t

            mov [edi].type,        [edx].type
            mov [edi].target_type, [edx].target_type
            mov [edi].mem_type,    [edx].mem_type
            mov [edi].ptr_memtype, [edx].ptr_memtype
            mov [edi].is_ptr,      [edx].is_ptr

            assume edx:nothing

        .endif
    .endf
    ret

GetStdAssumeTable endp

    assume edi:nothing
    assume esi:nothing

AssumeSaveState proc

    GetSegAssumeTable( &saved_SegAssumeTable )
    GetStdAssumeTable( &saved_StdAssumeTable, &saved_StdTypeInfo )
    ret

AssumeSaveState endp


AssumeInit proc pass:int_t ;; pass may be -1 here!

    assume edx:ptr assume_info

    .for ( edx = &SegAssumeTable,
           eax = 0,
           ecx = 0 : ecx < NUM_SEGREGS : ecx++, edx += assume_info )
        mov [edx].symbol,eax
        mov [edx].error,al
        mov [edx].is_flat,al
    .endf

    ;; the GPR assumes are handled somewhat special by masm.
    ;; they aren't reset for each pass - instead they keep their value.
    ;;

    .if ( pass <= PASS_1 ) ;; v2.10: just reset assumes in pass one

        .for ( edx = &StdAssumeTable,
               ecx = 0 : ecx < NUM_STDREGS : ecx++, edx += assume_info )

            mov [edx].symbol,eax
            mov [edx].error,al
        .endf

        .if ( pass == PASS_1 )

            lea  edx,stdsym
            mov  ecx,sizeof(stdsym)
            xchg edi,edx
            rep  stosb
            mov  edi,edx
        .endif
    .endif

    assume edx:nothing

    .if ( pass > PASS_1 && UseSavedState )

        SetSegAssumeTable( &saved_SegAssumeTable )
        SetStdAssumeTable( &saved_StdAssumeTable, &saved_StdTypeInfo )
    .endif
    ret

AssumeInit endp

;; generate assume lines after .MODEL directive
;; model is in ModuleInfo.model, it can't be MODEL_NONE.

ModelAssumeInit proc

    ;; Generates codes for assume

    mov al,ModuleInfo._model
    and eax,7
    .switch jmp eax
    .case MODEL_FLAT
        lea edx,szError
        .if ( ModuleInfo.fctype == FCT_WIN64 || ModuleInfo.fctype == FCT_VEC64 )
            lea edx,szNothing
        .endif
        AddLineQueueX( "assume cs:flat,ds:flat,ss:flat,es:flat,fs:%s,gs:%s",
                  &szError, edx )
        .endc
    .case MODEL_TINY
    .case MODEL_SMALL
    .case MODEL_COMPACT
    .case MODEL_MEDIUM
    .case MODEL_LARGE
    .case MODEL_HUGE
ifndef __ASMC64__

        ;; v2.03: no DGROUP for COFF/ELF

        .endc .if ( Options.output_format == OFORMAT_COFF || Options.output_format == OFORMAT_ELF )

        .if ( ModuleInfo._model == MODEL_TINY )
            lea edx,szDgroup
        .else
            mov edx,SimGetSegName( SIM_CODE )
        .endif

        .if ( ModuleInfo.distance != STACK_FAR )
            lea ecx,@CStr("assume cs:%s,ds:%s,ss:%s")
        .else
            lea ecx,@CStr("assume cs:%s,ds:%s")
        .endif
        lea eax,szDgroup
        AddLineQueueX( ecx, edx, eax, eax )
        .endc
endif
    .case MODEL_NONE
    .endsw
    ret
ModelAssumeInit endp

;; used by INVOKE directive

    assume edx:ptr assume_info

GetStdAssume proc reg:int_t

    mov ecx,reg
    mov eax,StdAssumeTable[ecx*8].symbol

    .if ( eax )

        .if ( [eax].asym.mem_type == MT_TYPE )
            mov eax,[eax].asym.type
        .else
            mov eax,[eax].asym.target_type
        .endif
    .endif
    ret

GetStdAssume endp

    assume edx:nothing

;; v2.05: new, used by
;; expression evaluator if a register is used for indirect addressing

GetStdAssumeEx proc reg:int_t

    xor eax,eax
    .if ( reg < NUM_STDREGS )
        mov eax,reg
        mov eax,StdAssumeTable[eax*8].symbol
    .endif
    ret

GetStdAssumeEx endp


;; Handles ASSUME
;; syntax is :
;; - ASSUME
;; - ASSUME NOTHING
;; - ASSUME segregister : seglocation [, segregister : seglocation ]
;; - ASSUME dataregister : qualified type [, dataregister : qualified type ]
;; - ASSUME register : ERROR | NOTHING | FLAT

AssumeDirective proc uses esi edi ebx i:int_t, tokenarray:tok_t

  local reg:int_t
  local j:int_t
  local size:int_t
  local flags:uint_t
  local info:ptr assume_info
  local segtable:int_t
  local ti:qualified_type
  local opnd:expr

    xor eax,eax
    mov reg,eax
    mov j,eax
    mov flags,eax
    mov segtable,eax

    inc i
    mov ebx,i
    shl ebx,4
    add ebx,tokenarray

    .for( : i < Token_Count : i++, ebx += 16 )

        assume ebx:tok_t
        assume edi:ptr assume_info

        .if ( [ebx].token == T_ID )
            .if !_stricmp( [ebx].string_ptr, &szNothing )

                AssumeInit(-1)
                inc i
                .break
            .endif
        .endif

        ;;---- get the info ptr for the register ----

        xor edi,edi

        .if ( [ebx].token == T_REG )
            mov reg,[ebx].tokval
            mov flags,GetValueSp(eax)
            movzx eax,GetRegNo(reg)
            mov j,eax

            .if ( flags & OP_SR )
                lea edi,SegAssumeTable[eax*8]
                mov segtable,TRUE
            .elseif ( flags & OP_R )
                lea edi,StdAssumeTable[eax*8]
                mov segtable,FALSE
            .endif
        .endif
        .if ( edi == NULL )
            .return( asmerr(2008, [ebx].string_ptr ) )
        .endif

        mov ecx,ModuleInfo.curr_cpu
        and ecx,P_CPU_MASK
        .if( ( cx ) < GetCpuSp(reg) )
            .return( asmerr( 2085 ) )
        .endif
        .if( [ebx+16].token != T_COLON )
            .return( asmerr( 2065, "" ) )
        .endif
        .if( [ebx+32].token == T_FINAL )
            .return( asmerr( 2009 ) )
        .endif

        add i,2 ;; go past register
        add ebx,32

        ;; check for ERROR and NOTHING */

        .if !_stricmp( [ebx].string_ptr, &szError )
            .if ( segtable )
                mov [edi].is_flat,FALSE
                mov [edi].error,TRUE
            .else
                mov eax,flags
                and eax,OP_R
                .if ( reg >= T_AH && reg <= T_BH )
                    mov eax,RH_ERROR
                .endif
                or [edi].error,al
            .endif
            mov [edi].symbol,NULL
            inc i
        .elseif( !_stricmp( [ebx].string_ptr, &szNothing ))
            .if ( segtable )
                mov [edi].is_flat,FALSE
                mov [edi].error,FALSE
            .else
                mov eax,flags
                and eax,OP_R
                .if ( reg >= T_AH && reg <= T_BH )
                    mov eax,RH_ERROR
                .endif
                not eax
                mov cl,[edi].error
                and al,cl
                mov [edi].error,al
            .endif
            mov [edi].symbol,NULL
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

            .return .if GetQualifiedType( &i, tokenarray, &ti ) == ERROR

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
            mov cl,[edi].error
            and al,cl
            mov [edi].error,al

            mov esi,j

            assume esi:asym_t

            .if ( stdsym[esi*4] == NULL )

                mov stdsym[esi*4],CreateTypeSymbol(NULL, "", FALSE)
                mov [eax].asym.typekind,TYPE_TYPEDEF
            .endif

            mov esi,stdsym[esi*4]

            mov [esi].total_size,  ti.size
            mov [esi].mem_type,    ti.mem_type
            mov [esi].is_ptr,      ti.is_ptr
            mov al,[esi].sflags
            and al,not S_ISFAR
            .if ti.is_far
                or al,S_ISFAR
            .endif
            mov [esi].sflags,al
            mov [esi].Ofssize,     ti.Ofssize
            mov [esi].ptr_memtype, ti.ptr_memtype ;; added v2.05 rc13
            .if ( ti.mem_type == MT_TYPE )
                mov [esi].type,    ti.symtype
            .else
                mov [esi].target_type,ti.symtype
            .endif
            mov [edi].symbol,esi

        .else ;; segment register


            ;; v2.08: read expression with standard evaluator
            .return .if EvalOperand( &i, tokenarray, Token_Count, &opnd, 0 ) == ERROR
            mov esi,opnd.sym

            .switch ( opnd.kind )
            .case EXPR_ADDR
                .if ( esi == NULL || opnd.flags & E_INDIRECT || opnd.value )
                    .return( asmerr( 2096 ) );
                .elseif ( [esi].state == SYM_UNDEFINED )
                    ;; ensure that directive is rerun in pass 2
                    ;; so an error msg can be emitted.

                    .if ( Parse_Pass == PASS_1 )
                        StoreLine( CurrSource, 0, 0 )
                    .endif

                    mov [edi].symbol,esi
                .elseif ( ( [esi].state == SYM_SEG || [esi].state == SYM_GRP ) && opnd.inst == EMPTY )
                    mov [edi].symbol,esi
                .elseif ( opnd.inst == T_SEG )
                    mov [edi].symbol,[esi].segm
                .else
                    .return( asmerr( 2096 ) )
                .endif
                xor eax,eax
                mov ecx,ModuleInfo.flat_grp
                .if ( [edi].symbol == ecx )
                    inc eax
                .endif
                mov [edi].is_flat,al
                .endc
            .case EXPR_REG
                mov edx,opnd.base_reg
                mov esi,[edx].asm_tok.tokval

                .if ( GetValueSp(esi) & OP_SR )
                    movzx ecx,GetRegNo(esi)
                    mov eax,SegAssumeTable[ecx*8].symbol
                    mov [edi].symbol,eax
                    mov al,SegAssumeTable[ecx*8].is_flat
                    mov [edi].is_flat,al
                    .endc
                .endif
            .default
                .return( asmerr( 2096 ) )
            .endsw
            mov [edi].error,FALSE
        .endif

        ;; comma expected

        mov ebx,i
        shl ebx,4
        add ebx,tokenarray

        .break .if( i < Token_Count && [ebx].token != T_COMMA )
    .endf

    .if ( i < Token_Count )
        mov ebx,i
        shl ebx,4
        add ebx,tokenarray
        .return( asmerr(2008, [ebx].tokpos ) )
    .endif
    mov eax,NOT_ERROR
    ret

AssumeDirective endp

;; for a symbol, search segment register which holds segment
;; part of symbol's address in assume table.
;; - sym: segment of symbol for which to search segment register
;; - def: prefered default register (or ASSUME_NOTHING )
;; - search_grps: if TRUE, check groups as well
;;
;; for data items, Masm checks assumes in this order:
;;   DS, SS, ES, FS, GS, CS


search_assume proc uses esi sym:asym_t, def:int_t, search_grps:int_t


    .return( ASSUME_NOTHING ) .if ( sym == NULL )

    mov esi,GetGroup(sym)
    mov edx,def

    ;; first check the default segment register

    .if ( edx != ASSUME_NOTHING )

        mov eax,edx
        mov ecx,sym
        .return .if ( SegAssumeTable[edx*8].symbol == ecx )

        .if ( search_grps && esi )

            .return .if ( SegAssumeTable[edx*8].is_flat && esi == ModuleInfo.flat_grp )
            .return .if ( SegAssumeTable[edx*8].symbol == esi )
        .endif
    .endif

    ;; now check all segment registers

    .for ( ecx = 0: ecx < NUM_SEGREGS: ecx++ )

        mov eax,searchtab[ecx*4]
        mov edx,SegAssumeTable[eax*8].symbol
        .return .if ( edx == sym )
    .endf

    ;; now check the groups

    .if( search_grps && esi )

        .for( ecx = 0: ecx < NUM_SEGREGS: ecx++ )

            mov eax,searchtab[ecx*4]

            .return .if ( SegAssumeTable[eax*8].is_flat && esi == ModuleInfo.flat_grp )
            .return .if ( SegAssumeTable[eax*8].symbol == esi )
        .endf
    .endif
    mov eax,ASSUME_NOTHING
    ret

search_assume endp

;;
;; called by the parser's seg_override() function if
;; a segment register override has been detected.
;; - override: segment register override (0,1,2,3,4,5)
;;

GetOverrideAssume proc override:int_t

    imul edx,override,assume_info
    mov  eax,SegAssumeTable[edx].symbol
    .if( SegAssumeTable[edx].is_flat )
        mov eax,ModuleInfo.flat_grp
    .endif
    ret

GetOverrideAssume endp

;;
;; GetAssume():
;; called by check_assume() in parser.c
;; in:
;; - override: SegOverride
;; - sym: symbol in current memory operand
;; - def: default segment assume value
;; to be fixed: check if symbols with state==SYM_STACK are handled correctly.
;;

GetAssume proc override:asym_t, sym:asym_t, def:int_t, passume:ptr asym_t

    mov eax,def

    .if( ( eax != ASSUME_NOTHING ) && SegAssumeTable[eax*8].is_flat )

        mov ecx,passume
        mov edx,ModuleInfo.flat_grp
        mov [ecx],edx
        .return
    .endif

    mov edx,sym
    .if( override != NULL )
        search_assume( override, eax, FALSE )
    ;; v2.10: added
    .elseif ( [edx].asym.state == SYM_STACK )
        ;; stack symbols don't have a segment part.
        ;; In case [R|E]BP is used as base, it doesn't matter.
        ;; However, if option -Zg is set, this isn't true.
        ;;
        mov eax,ASSUME_SS
    .else
        search_assume( [edx].asym.segm, def, TRUE )
    .endif

    .if( eax == ASSUME_NOTHING )
        mov edx,sym
        .if( edx && [edx].asym.state == SYM_EXTERNAL && [edx].asym.segm == NULL )
            mov eax,def
        .endif
    .endif
    mov edx,passume
    .if( eax != ASSUME_NOTHING )

        mov  ecx,SegAssumeTable[eax*8].symbol
        mov [edx],ecx
        .return
    .endif
    mov dword ptr [edx],NULL
    mov eax,ASSUME_NOTHING
    ret

GetAssume endp

    end
