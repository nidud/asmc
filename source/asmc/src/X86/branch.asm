; BRANCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include asmc.inc
include parser.inc
include fixup.inc
include expreval.inc
include segment.inc
include assume.inc
include codegen.inc

IS_CONDJMP macro inst
    exitm<( ( inst !>= T_JA ) && ( inst !<= T_JZ ) )>
    endm

;; opsize byte (0x66) to be generated?

OPSIZE proto fastcall s:byte, x:abs {
    cmp cl,x
    setne al
    }

segm_override proto :ptr expr, :ptr code_info
extern SegOverride:ptr asym

;;
;; "short jump extension": extend a (conditional) jump.
;; example:
;; "jz label"
;; is converted to
;; "jnz SHORT $+x"  ( x = sizeof(next ins), may be 3|5|6|7|8 )
;; "jmp label"
;;
;; there is a problem if it's a short forward jump with a distance
;; of 7D-7F (16bit), because the additional "jmp label" will increase
;; the code size.
;;
    .code

    assume esi:ptr code_info

jumpExtend proc private uses esi ebx CodeInfo:ptr code_info, far_flag:int_t

    .if( Parse_Pass == PASS_2 )
        asmerr( 6003 )
    .endif

    mov esi,CodeInfo
    mov al,[esi].Ofssize

    .if ( far_flag )

        .if ( [esi].opsiz )

            ;; it's 66 EA OOOO SSSS or 66 EA OOOOOOOO SSSS

            mov ebx,8
            .if al
                mov ebx,6
            .endif
        .else

            ;; it's EA OOOOOOOO SSSS or EA OOOO SSSS

            mov ebx,5
            .if al
                mov ebx,7
            .endif
        .endif
    .else

        ;; it's E9 OOOOOOOO or E9 OOOO

        mov ebx,3
        .if al
            mov ebx,5
        .endif
    .endif

    mov edx,[esi].pinstr
    movzx eax,[edx].instr_item.opcode
    xor eax,1
    OutputByte( eax )
    OutputByte( ebx )
    mov [esi].token,T_JMP
    movzx eax,IndexFromToken(T_JMP)
    lea eax,InstrTable[eax*8]
    mov [esi].pinstr,eax
    ret

jumpExtend endp

;; "far call optimisation": a far call is done to a near label
;; optimize (call SSSS:OOOO -> PUSH CS, CALL OOOO)

FarCallToNear proc private CodeInfo:ptr code_info

    .if ( Parse_Pass == PASS_2 )
        asmerr( 7003 )
    .endif

    OutputByte( 0x0E ) ;; 0x0E is "PUSH CS" opcode
    mov ecx,CodeInfo
    mov [ecx].code_info.mem_type,MT_NEAR
    ret

FarCallToNear endp


;;
;; called by idata_fixup(), idata_nofixup().
;; current instruction is CALL, JMP, Jxx, LOOPx, JCXZ or JECXZ
;; and operand is an immediate value.
;; determine the displacement of jmp;
;; possible return values are:
;; - NOT_ERROR,
;; - ERROR,
;;

    assume ebx:ptr expr
    assume edi:ptr asym

process_branch proc uses esi edi ebx CodeInfo:ptr code_info, CurrOpnd:dword, opndx:ptr expr

  local adr:int_32
  local fixup_type:int_32
  local fixup_option:int_32
  local state:int_32
  local mem_type:byte
  local symseg:ptr dsym
  local opidx:dword

    mov esi,CodeInfo
    mov ebx,opndx

    movzx eax,[esi].token
    movzx eax,IndexFromToken(eax)
    mov opidx,eax

    ;; v2.05: just 1 operand possible

    .return( asmerr( 2070 ) ) .if ( CurrOpnd != OPND1 )

    .if ( [ebx].flags & E_EXPLICIT && [ebx].inst != T_SHORT )
        mov [esi].mem_type,[ebx].mem_type
    .endif

    ;; Masm checks overrides for branch instructions with immediate operand!
    ;; Of course, no segment prefix byte is emitted - would be pretty useless.
    ;; It might cause the call/jmp to become FAR, though.

    .if ( [ebx].override != NULL )

        segm_override( ebx, NULL )
        mov ecx,[ebx].sym
        mov eax,SegOverride

        .if ( eax && ecx && [ecx].asym.segm )

            mov edx,[ecx].asym.segm
            mov edx,[edx].dsym.seginfo
            mov edx,[edx].seg_info.sgroup

            .if ( eax != [ecx].asym.segm &&  eax != edx )

                .return( asmerr( 2074, [ecx].asym.name ) )
            .endif

            ;; v2.05: switch to far jmp/call

            mov ecx,CurrSeg
            mov edx,[ecx].dsym.seginfo
            mov edx,[edx].seg_info.sgroup

            .if ( eax != ecx && eax != edx )
                mov [esi].mem_type,MT_FAR
            .endif
        .endif
    .endif

    mov [esi].opnd[OPND1].data32l,[ebx].value

    ;; v2.06: make sure, that next bytes are cleared (for OP_I48)!

    mov [esi].opnd[OPND1].data32h,0

    mov edi,[ebx].sym
    .if ( edi == NULL ) ;; no symbolic label specified?

        ;; Masm rejects: "jump dest must specify a label

        .return( asmerr( 2076 ) )
    .endif

    mov state,[edi].state
    mov adr,GetCurrOffset() ;; for SYM_UNDEFINED, will force distance to SHORT

    ;; v2.02: if symbol is GLOBAL and it isn't clear yet were
    ;; it's located, then assume it is a forward reference (=SYM_UNDEFINED)!
    ;; This applies to PROTOs and EXTERNDEFs in Pass 1.

    .if ( ( state == SYM_EXTERNAL ) && [edi].sflags & S_WEAK )
        mov state,SYM_UNDEFINED
    .endif

    .if ( state == SYM_INTERNAL || state == SYM_EXTERNAL )

        ;; v2.04: if the symbol is internal, but wasn't met yet
        ;; in this pass and its offset is < $, don't use current offset

        mov eax,Parse_Pass
        and eax,0xFF
        mov ecx,adr

        .ifs ( state == SYM_INTERNAL && [edi].asmpass != al && [edi].offs < ecx )
        .else
            mov adr,[edi].offs ;; v2.02: init addr, so sym->offset isn't changed
        .endif
        mov symseg,[edi].segm

        .if ( eax == NULL || ( CurrSeg != eax ) )

            ;; if label has a different segment and jump/call is near or short,
            ;; report an error

            .if eax
                mov ecx,[eax].dsym.seginfo
            .endif
            .if ( ModuleInfo.flat_grp && ( eax == NULL || [ecx].seg_info.Ofssize == ModuleInfo.Ofssize ) )

            .elseif ( eax != NULL && CurrSeg != NULL )

                ;; if the segments belong to the same group, it's ok

                mov edx,CurrSeg
                mov edx,[edx].dsym.seginfo

                .if ( [ecx].seg_info.sgroup != NULL && [ecx].seg_info.sgroup == [edx].seg_info.sgroup )
                    ;
                .elseif ( [ebx].mem_type == MT_NEAR && SegOverride == NULL )
                    .return( asmerr( 2107 ) )
                .endif
            .endif

            ;; jumps to another segment are just like to another file

            mov state,SYM_EXTERNAL
        .endif

    .elseif ( state != SYM_UNDEFINED )

        .return( asmerr( 2076 ) )

    .endif

    .if ( state != SYM_EXTERNAL )

        ;; v1.94: if a segment override is active,
        ;; check if it's matching the assumed value of CS.
        ;; If no, assume a FAR call.

        .if ( SegOverride != NULL && [esi].mem_type == MT_EMPTY )
            .if ( SegOverride != GetOverrideAssume( ASSUME_CS ) )
                mov [esi].mem_type,MT_FAR
            .endif
        .endif
        .if ( ( [esi].mem_type == MT_EMPTY || [esi].mem_type == MT_NEAR ) && \
             !( [esi].flags & CI_ISFAR ) )

            ;; if the label is FAR - or there is a segment override
            ;; which equals assumed value of CS - and there is no type cast,
            ;; then do a "far call optimization".

            .if ( [esi].token == T_CALL && [esi].mem_type == MT_EMPTY && \
                  ( [edi].mem_type == MT_FAR || SegOverride ) )

                FarCallToNear( esi ) ;; switch mem_type to NEAR
            .endif

            GetCurrOffset() ;; calculate the displacement
            mov edx,adr
            sub edx,eax
            sub edx,2
            add edx,[esi].opnd[OPND1].data32l

            ;;  JCXZ, LOOPW, LOOPEW, LOOPZW, LOOPNEW, LOOPNZW,
            ;; JECXZ, LOOPD, LOOPED, LOOPZD, LOOPNED, LOOPNZD?

            mov ecx,opidx
            .if ( ( [esi].Ofssize && InstrTable[ecx*8].byte1_info == F_16A ) || \
                  ( [esi].Ofssize != USE32 && InstrTable[ecx*8].byte1_info == F_32A ) )

                dec edx ;; 1 extra byte for ADRSIZ (0x67)
            .endif

            .ifs ( [esi].mem_type != MT_NEAR && [esi].token != T_CALL && \
                  ( edx >= SCHAR_MIN && edx <= SCHAR_MAX ) )

                mov [esi].opnd[OPND1].type,OP_I8

            .else

                .if ( [ebx].inst == T_SHORT || ( IS_XCX_BRANCH( [esi].token ) ) )

                    ;; v2.06: added

                    .if( [esi].token == T_CALL )
                        .return( asmerr( 2008, "short" ) )
                    .endif

                    .ifs ( edx < 0 )
                        sub edx,SCHAR_MIN
                        xor eax,eax
                        sub eax,edx
                        mov edx,eax
                    .else
                        sub edx,SCHAR_MAX
                    .endif
                    .if ( [esi].mem_type == MT_EMPTY )
                        .return asmerr( 2075, edx )
                    .endif
                    .return asmerr( 2080 )
                .endif

                ;; near destination
                ;; is there a type coercion?

                .if ( [ebx].Ofssize != USE_EMPTY )
                    .if ( [ebx].Ofssize == USE16 )
                        mov [esi].opnd[OPND1].type,OP_I16
                        dec edx ;; 16 bit displacement
                    .else
                        mov [esi].opnd[OPND1].type,OP_I32
                        sub edx,3 ;; 32 bit displacement
                    .endif
                    mov [esi].opsiz,OPSIZE( [ebx].Ofssize, [esi].Ofssize )
                    .if ( [esi].opsiz )
                        dec edx
                    .endif
                .elseif( [esi].Ofssize > USE16 )
                    mov [esi].opnd[OPND1].type,OP_I32
                    sub edx,3 ;; 32 bit displacement
                .else
                    mov [esi].opnd[OPND1].type,OP_I16
                    dec edx ;; 16 bit displacement
                .endif
                .if ( IS_CONDJMP( [esi].token ) )
                    ;; 1 extra byte for opcode ( 0F )
                    dec edx
                .endif

            .endif
            mov adr,edx

            ;; store the displacement
            mov [esi].opnd[OPND1].data32l,adr

            ;; automatic (conditional) jump expansion.
            ;; for 386 and above this is not needed, since there exists
            ;; an extended version of Jcc

            mov ecx,ModuleInfo.curr_cpu
            and ecx,P_CPU_MASK

            .if ( ecx < P_386 && IS_JCC( [esi].token ) )

                ;; look into jump extension

                .if ( [esi].opnd[OPND1].type != OP_I8 )

                    .if( [esi].mem_type == MT_EMPTY && ModuleInfo.ljmp == TRUE )

                        jumpExtend( esi, FALSE )
                        sub adr,1
                        mov [esi].opnd[OPND1].data32l,adr

                    .else

                        ;; v2.11: don't emit "out of range" if OP_I16 was forced
                        ;; by type coercion ( jmp near ptr xxx )

                        mov eax,2079
                        .if ( [esi].mem_type == MT_EMPTY )
                            mov eax,2075
                        .endif
                        .return( asmerr( eax, adr ) )
                    .endif
                .endif
            .endif

            ;; v2.02: in pass one, write "backpatch" fixup for forward
            ;; references.

            ;; the "if" below needs to be explaind.
            ;; Fixups will be written for forward references in pass one.
            ;; state is SYM_UNDEFINED then. The fixups will be scanned when
            ;; the label is met finally, still in pass one. See backptch.c
            ;; for details.

            .if ( state != SYM_UNDEFINED )
                .return( NOT_ERROR ) ;; exit, no fixup is written!
            .endif
        .endif
    .endif

    mov fixup_option,OPTJ_NONE
    mov fixup_type,FIX_RELOFF8

    mov mem_type,[ebx].mem_type

    ;; v2.04: far call optimization possible if destination is in
    ;; another segment of the same group. However, a fixup must be written.
    ;; Masm does NOT optimize if destination is external!

    .if ( [esi].token == T_CALL && [esi].mem_type == MT_EMPTY && \
          ( [edi].mem_type == MT_FAR || SegOverride ) )

        mov eax,[edi].segm
        mov symseg,eax
        xor ecx,ecx

        .if eax
            mov ecx,[eax].dsym.seginfo
            .if ecx
                mov ecx,[ecx].seg_info.sgroup
            .endif
        .endif
        mov edx,CurrSeg
        mov edx,[edx].dsym.seginfo

        .if ( eax == CurrSeg || \
            ( eax != NULL && ecx != NULL && ecx == [edx].seg_info.sgroup ) )

            FarCallToNear(esi) ;; switch mem_type to NEAR
        .endif
    .endif

    ;; forward ref, or external symbol

    mov al,mem_type
    .if ( [esi].mem_type == MT_EMPTY && al != MT_EMPTY && [ebx].inst != T_SHORT )

        ;; MT_PROC is most likely obsolete ( used by TYPEDEF only )

        .switch al
        .case MT_FAR
            .if( IS_JMPCALL( [esi].token ) )
                or [esi].flags,CI_ISFAR
            .endif
        .case MT_NEAR
            ;; v2.04: 'if' added
            .if ( state != SYM_UNDEFINED )
                mov [esi].mem_type,al
            .endif
            .endc
        .default
            mov [esi].mem_type,al
        .endsw
    .endif

    ;; handle far JMP + CALL?

    mov al,[esi].mem_type

    .if ( IS_JMPCALL( [esi].token ) && ( [esi].flags & CI_ISFAR || al == MT_FAR ) )

        or [esi].flags,CI_ISFAR ;; flag isn't set if explicit is true

        .switch al
        .case MT_NEAR

            .if( [ebx].flags & E_EXPLICIT || [ebx].inst == T_SHORT )
                .return( asmerr( 2077 ) )
            .endif

            ;; fall through

        .case MT_FAR
        .case MT_EMPTY

            .if ( [ebx].Ofssize != USE_EMPTY )
                mov [esi].opsiz,OPSIZE( [esi].Ofssize, [ebx].Ofssize )
            .else
                mov [esi].opsiz,OPSIZE( GetSymOfssize(edi), [esi].Ofssize )
            .endif

            ;; set fixup frame variables Frame + Frame_Datum

            set_frame( edi )
            .if( IS_OPER_32( esi ) )
                mov fixup_type,FIX_PTR32
                mov [esi].opnd[OPND1].type,OP_I48
            .else
                mov fixup_type,FIX_PTR16
                mov [esi].opnd[OPND1].type,OP_I32
            .endif
            .endc
        .endsw

        mov [esi].opnd[OPND1].InsFixup,CreateFixup( edi, fixup_type, fixup_option )
        .return( NOT_ERROR )

    .endif

    movzx eax,[esi].token
    .switch eax
    .case T_CALL
        .if ( [ebx].inst == T_SHORT )
            .return( asmerr( 2077 ) )
        .endif

        .if ( [esi].mem_type == MT_EMPTY )
            mov fixup_option,OPTJ_CALL
            .if ( [esi].Ofssize > USE16 )
                mov fixup_type,FIX_RELOFF32
                mov [esi].opnd[OPND1].type,OP_I32
            .else
                mov fixup_type,FIX_RELOFF16
                mov [esi].opnd[OPND1].type,OP_I16
            .endif
            .endc
        .endif

        ;; fall through

    .case T_JMP

        mov al,[esi].mem_type
        .switch al

        .case MT_EMPTY

            ;; forward reference
            ;; default distance is short, we will expand later if needed

            mov [esi].opnd[OPND1].type,OP_I8
            mov fixup_type,FIX_RELOFF8
            mov eax,OPTJ_NONE
            .if ( [ebx].inst == T_SHORT )
                mov eax,OPTJ_EXPLICIT
            .endif
            mov fixup_option,eax
            .endc

        .case MT_NEAR

            mov fixup_option,OPTJ_EXPLICIT
            .if( [ebx].Ofssize != USE_EMPTY )
                .if ( [ebx].Ofssize == USE16 )
                    mov fixup_type,FIX_RELOFF16
                    mov [esi].opnd[OPND1].type,OP_I16
                .else
                    mov fixup_type,FIX_RELOFF32
                    mov [esi].opnd[OPND1].type,OP_I32
                .endif
                mov [esi].opsiz,OPSIZE( [esi].Ofssize, [ebx].Ofssize )
            .else
                .if ( [esi].Ofssize > USE16 )
                    mov fixup_type,FIX_RELOFF32
                    mov [esi].opnd[OPND1].type,OP_I32
                .else
                    mov fixup_type,FIX_RELOFF16
                    mov [esi].opnd[OPND1].type,OP_I16
                .endif
            .endif
            set_frame(edi)
            .endc
         .endsw
        .endc

    .default

        ;; JxCXZ, LOOPxx, Jxx
        ;; JxCXZ and LOOPxx always require SHORT label

        .if ( IS_XCX_BRANCH( eax ) )

            .if ( [esi].mem_type != MT_EMPTY && [ebx].inst != T_SHORT )
                .return( asmerr( 2080 ) )
            .endif

            mov [esi].opnd[OPND1].type,OP_I8
            mov fixup_option,OPTJ_EXPLICIT
            mov fixup_type,FIX_RELOFF8

            .endc

        .endif

        ;; just Jxx remaining

        mov eax,ModuleInfo.curr_cpu
        and eax,P_CPU_MASK

        .if( eax >= P_386 )

            mov al,[esi].mem_type

            .switch ( al )

            .case MT_EMPTY

                ;; forward reference

                mov eax,OPTJ_JXX
                .if ( [ebx].inst == T_SHORT )
                    mov eax,OPTJ_EXPLICIT
                .endif

                mov fixup_option,eax
                mov fixup_type,FIX_RELOFF8
                mov [esi].opnd[OPND1].type,OP_I8

                .endc

            .case MT_NEAR

                mov fixup_option,OPTJ_EXPLICIT

                ;; v1.95: explicit flag to be removed!

                .if ( [ebx].Ofssize != USE_EMPTY )

                    mov [esi].opsiz,OPSIZE( [esi].Ofssize, [ebx].Ofssize )

                    mov eax,OP_I16
                    .if ( [ebx].Ofssize >= USE32 )
                        mov eax,OP_I32
                    .endif
                    mov [esi].opnd[OPND1].type,eax

                .elseif ( [esi].Ofssize > USE16 )

                    mov fixup_type,FIX_RELOFF32
                    mov [esi].opnd[OPND1].type,OP_I32
                .else

                    mov fixup_type,FIX_RELOFF16
                    mov [esi].opnd[OPND1].type,OP_I16
                .endif
                .endc

            .case MT_FAR

                .if ( ModuleInfo.ljmp ) ;; OPTION LJMP set?

                    .if ( [ebx].Ofssize != USE_EMPTY )
                        mov [esi].opsiz,OPSIZE( [esi].Ofssize, [ebx].Ofssize )
                    .else
                        mov [esi].opsiz,OPSIZE( GetSymOfssize(edi), [esi].Ofssize )
                    .endif

                    ;; destination is FAR (externdef <dest>:far

                    jumpExtend( esi, TRUE )
                    or [esi].flags,CI_ISFAR

                    .if( IS_OPER_32( esi ) )
                        mov fixup_type,FIX_PTR32
                        mov [esi].opnd[OPND1].type,OP_I48
                    .else
                        mov fixup_type,FIX_PTR16
                        mov [esi].opnd[OPND1].type,OP_I32
                    .endif
                    .endc

                .endif

                ;; fall through

            .default

                ;; is another memtype possible at all?

                .return( asmerr( 2080 ) )
            .endsw
        .else

            ;; the only mode in 8086, 80186, 80286 is
            ;; Jxx SHORT
            ;; Masm allows "Jxx near" if LJMP is on (default)

            mov al,[esi].mem_type
            .switch al
            .case MT_EMPTY

                .if ( [ebx].inst == T_SHORT )
                    mov fixup_option,OPTJ_EXPLICIT
                .else
                    mov fixup_option,OPTJ_EXTEND
                .endif

                mov fixup_type,FIX_RELOFF8
                mov [esi].opnd[OPND1].type,OP_I8
                .endc

            .case MT_NEAR ;; allow Jxx NEAR if LJMP on
            .case MT_FAR

                .if ( ModuleInfo.ljmp )

                    .if ( al == MT_FAR )

                        jumpExtend( esi, TRUE )
                        mov fixup_type,FIX_PTR16
                        or  [esi].flags,CI_ISFAR
                        mov [esi].opnd[OPND1].type,OP_I32

                    .else

                        jumpExtend( esi, FALSE )
                        mov fixup_type,FIX_RELOFF16
                        mov [esi].opnd[OPND1].type,OP_I16
                    .endif
                    .endc
                .endif

                ;; fall through

            .default

                .return( asmerr( 2080 ) )
            .endsw

        .endif

    .endsw

    mov [esi].opnd[OPND1].InsFixup,CreateFixup( edi, fixup_type, fixup_option )
    mov eax,NOT_ERROR
    ret

process_branch endp

    end
