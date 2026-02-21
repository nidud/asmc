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

; opsize byte (0x66) to be generated?

OPSIZE proto fastcall s:byte, x:abs {
    cmp cl,x
    setne al
    }

segm_override proto __ccall :ptr expr, :ptr code_info
externdef SegOverride:asym_t

;
; "short jump extension": extend a (conditional) jump.
; example:
; "jz label"
; is converted to
; "jnz SHORT $+x"  ( x = sizeof(next ins), may be 3|5|6|7|8 )
; "jmp label"
;
; there is a problem if it's a short forward jump with a distance
; of 7D-7F (16bit), because the additional "jmp label" will increase
; the code size.
;
    .code

    assume rsi:ptr code_info

jumpExtend proc fastcall private uses rsi rbx CodeInfo:ptr code_info, far_flag:int_t
    mov rsi,rcx
    mov ebx,edx
    .if( Parse_Pass == PASS_2 )
        asmerr( 6003 )
    .endif
    mov al,[rsi].Ofssize
    .if ( ebx )
        .if ( [rsi].opsiz )
            ; it's 66 EA OOOO SSSS or 66 EA OOOOOOOO SSSS
            mov ebx,8
            .if al
                mov ebx,6
            .endif
        .else
            ; it's EA OOOOOOOO SSSS or EA OOOO SSSS
            mov ebx,5
            .if al
                mov ebx,7
            .endif
        .endif
    .else
        ; it's E9 OOOOOOOO or E9 OOOO
        mov ebx,3
        .if al
            mov ebx,5
        .endif
    .endif
    mov rdx,[rsi].pinstr
    movzx eax,[rdx].instr_item.opcode
    xor eax,1
    OutputByte( eax )
    OutputByte( ebx )
    mov [rsi].token,T_JMP
    movzx eax,IndexFromToken(T_JMP)
    lea rdx,InstrTable
    lea rax,[rdx+rax*instr_item]
    mov [rsi].pinstr,rax
    ret
    endp

; "far call optimisation": a far call is done to a near label
; optimize (call SSSS:OOOO -> PUSH CS, CALL OOOO)

FarCallToNear proc __ccall private CodeInfo:ptr code_info
    .if ( Parse_Pass == PASS_2 )
        asmerr( 7003 )
    .endif
    OutputByte( 0x0E ) ; 0x0E is "PUSH CS" opcode
    mov rcx,CodeInfo
    mov [rcx].code_info.mem_type,MT_NEAR
    ret
    endp


;
; called by idata_fixup(), idata_nofixup().
; current instruction is CALL, JMP, Jxx, LOOPx, JCXZ or JECXZ
; and operand is an immediate value.
; determine the displacement of jmp;
; possible return values are:
; - NOT_ERROR,
; - ERROR,
;

    assume rbx:expr_t, rdi:asym_t

process_branch proc __ccall uses rsi rdi rbx CodeInfo:ptr code_info, CurrOpnd:dword, opndx:expr_t

  local adr:int_32
  local fixup_type:int_32
  local fixup_option:int_32
  local state:int_32
  local mem_type:byte
  local symseg:asym_t
  local opidx:dword

    ldr rsi,CodeInfo
    ldr rbx,opndx
    movzx eax,[rsi].token
    movzx eax,IndexFromToken(eax)
    mov opidx,eax

    ; v2.05: just 1 operand possible

    .return( asmerr( 2070 ) ) .if ( CurrOpnd != OPND1 )
    .if ( [rbx].explicit && [rbx].inst != T_SHORT )
        mov [rsi].mem_type,[rbx].mem_type
    .endif

    ; Masm checks overrides for branch instructions with immediate operand!
    ; Of course, no segment prefix byte is emitted - would be pretty useless.
    ; It might cause the call/jmp to become FAR, though.

    .if ( [rbx].override != NULL )
        segm_override( rbx, NULL )
        mov rcx,[rbx].sym
        mov rax,SegOverride
        .if ( rax && rcx && [rcx].asym.segm )
            mov rdx,[rcx].asym.segm
            mov rdx,[rdx].asym.seginfo
            mov rdx,[rdx].seg_info.sgroup
            .if ( rax != [rcx].asym.segm &&  rax != rdx )
                .return( asmerr( 2074, [rcx].asym.name ) )
            .endif
            ; v2.05: switch to far jmp/call
            mov rcx,CurrSeg
            mov rdx,[rcx].asym.seginfo
            mov rdx,[rdx].seg_info.sgroup
            .if ( rax != rcx && rax != rdx )
                mov [rsi].mem_type,MT_FAR
            .endif
        .endif
    .endif

    mov [rsi].opnd[OPND1].data32l,[rbx].value
    ; v2.06: make sure, that next bytes are cleared (for OP_I48)!
    mov [rsi].opnd[OPND1].data32h,0
    mov rdi,[rbx].sym
    .if ( rdi == NULL ) ; no symbolic label specified?
        ; Masm rejects: "jump dest must specify a label
        .return( asmerr( 2076 ) )
    .endif
    mov state,[rdi].state
    mov adr,GetCurrOffset() ; for SYM_UNDEFINED, will force distance to SHORT
    ; v2.02: if symbol is GLOBAL and it isn't clear yet were
    ; it's located, then assume it is a forward reference (=SYM_UNDEFINED)!
    ; This applies to PROTOs and EXTERNDEFs in Pass 1.

    .if ( ( state == SYM_EXTERNAL ) && [rdi].weak )
        mov state,SYM_UNDEFINED
    .endif

    .if ( state == SYM_INTERNAL || state == SYM_EXTERNAL )

        ; v2.04: if the symbol is internal, but wasn't met yet
        ; in this pass and its offset is < $, don't use current offset

        mov eax,Parse_Pass
        and eax,0xFF
        mov ecx,adr

        .ifs ( state == SYM_INTERNAL && [rdi].asmpass != al && [rdi].offs < ecx )
        .else
            mov adr,[rdi].offs ; v2.02: init addr, so sym->offset isn't changed
        .endif
        mov symseg,[rdi].segm

        .if ( rax == NULL || rax != CurrSeg )

            ; if label has a different segment and jump/call is near or short,
            ; report an error

            .if rax
                mov rcx,[rax].asym.seginfo
            .endif
            mov dl,MODULE.Ofssize
            .if ( MODULE.flat_grp && ( rax == NULL || [rcx].seg_info.Ofssize == dl ) )

            .elseif ( rax && CurrSeg )

                ; if the segments belong to the same group, it's ok

                mov rax,CurrSeg
                mov rdx,[rax].asym.seginfo
                mov rax,[rcx].seg_info.sgroup

                ; v2.19: no error in pass one ( a GROUP directive might follow that "fixes" the error )

                .if ( rax && rax == [rdx].seg_info.sgroup && [rcx].seg_info.Ofssize == MODULE.Ofssize )
                    ;
                .elseif ( Parse_Pass > PASS_1 && [rbx].mem_type == MT_NEAR && SegOverride == NULL )
                    .return( asmerr( 2107 ) )
                .endif
            .endif
            ; jumps to another segment are just like to another file
            mov state,SYM_EXTERNAL
        .endif
    .elseif ( state != SYM_UNDEFINED )
        .return( asmerr( 2076 ) )
    .endif

    .if ( state != SYM_EXTERNAL )

        ; v1.94: if a segment override is active,
        ; check if it's matching the assumed value of CS.
        ; If no, assume a FAR call.

        .if ( SegOverride != NULL && [rsi].mem_type == MT_EMPTY )
            .if ( SegOverride != GetOverrideAssume( ASSUME_CS ) )
                mov [rsi].mem_type,MT_FAR
            .endif
        .endif
        .if ( ( [rsi].mem_type == MT_EMPTY || [rsi].mem_type == MT_NEAR ) && !( [rsi].isfar ) )

            ; if the label is FAR - or there is a segment override
            ; which equals assumed value of CS - and there is no type cast,
            ; then do a "far call optimization".

            .if ( [rsi].token == T_CALL && [rsi].mem_type == MT_EMPTY &&
                  ( [rdi].mem_type == MT_FAR || SegOverride ) )

                FarCallToNear( rsi ) ; switch mem_type to NEAR
            .endif

            GetCurrOffset() ; calculate the displacement
            mov edx,adr
            sub edx,eax
            sub edx,2
            add edx,[rsi].opnd[OPND1].data32l

            ;  JCXZ, LOOPW, LOOPEW, LOOPZW, LOOPNEW, LOOPNZW,
            ; JECXZ, LOOPD, LOOPED, LOOPZD, LOOPNED, LOOPNZD?

            mov eax,opidx
            lea rcx,InstrTable
            lea rcx,[rcx+rax*instr_item]

            .if ( ( [rsi].Ofssize && [rcx].instr_item.byte1_info == F_16A ) ||
                  ( [rsi].Ofssize != USE32 && [rcx].instr_item.byte1_info == F_32A ) )

                dec edx ; 1 extra byte for ADRSIZ (0x67)
            .endif
            mov ecx,OP_I8
            .ifs ( edx < SCHAR_MIN || edx > SCHAR_MAX || [rsi].mem_type == MT_NEAR || [rsi].token == T_CALL )
                .if ( [rbx].inst == T_SHORT || ( IS_XCX_BRANCH( [rsi].token ) ) )
                    ; v2.06: added
                    .if( [rsi].token == T_CALL )
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
                    .if ( [rsi].mem_type == MT_EMPTY )
                        .return asmerr( 2075, edx )
                    .endif
                    .return asmerr( 2080 )
                .endif

                ; near destination
                ; is there a type coercion?

                mov ecx,OP_I32
                mov ah,[rbx].Ofssize
                mov al,[rsi].Ofssize

                .if ( ah != USE_EMPTY )

                    cmp     al,ah
                    movzx   eax,al
                    setne   al
                    mov     [rsi].opsiz,al
                    sub     edx,eax
                    mov     al,[rbx].Ofssize
                .endif
                .if( al > USE16 )
                    sub edx,3   ; 32 bit displacement
                .else
                    mov ecx,OP_I16
                    dec edx     ; 16 bit displacement
                .endif
                movzx eax,[rsi].token
                .if ( IS_CONDJMP( eax ) )
                    dec edx     ; 1 extra byte for opcode ( 0F )
                .endif
if 0
                ; displacement now in range?
                .ifs ( ecx == OP_I32 && edx >= SCHAR_MIN && edx <= SCHAR_MAX &&
                       eax != T_CALL && [rsi].mem_type != MT_NEAR )
                    mov ecx,OP_I8
                .endif
endif
            .endif

            ; store the displacement

            mov adr,edx
            mov [rsi].opnd[OPND1].type,ecx
            mov [rsi].opnd[OPND1].data32l,edx


            ; automatic (conditional) jump expansion.
            ; for 386 and above this is not needed, since there exists
            ; an extended version of Jcc

            mov ecx,MODULE.curr_cpu
            and ecx,P_CPU_MASK
            .if ( ecx < P_386 && IS_JCC( [rsi].token ) )
                ; look into jump extension
                .if ( [rsi].opnd[OPND1].type != OP_I8 )
                    .if( [rsi].mem_type == MT_EMPTY && MODULE.ljmp == TRUE )
                        jumpExtend( rsi, FALSE )
                        sub adr,1
                        mov [rsi].opnd[OPND1].data32l,adr
                    .else
                        ; v2.11: don't emit "out of range" if OP_I16 was forced
                        ; by type coercion ( jmp near ptr xxx )
                        mov eax,2079
                        .if ( [rsi].mem_type == MT_EMPTY )
                            mov eax,2075
                        .endif
                        .return( asmerr( eax, adr ) )
                    .endif
                .endif
            .endif

            ; v2.02: in pass one, write "backpatch" fixup for forward
            ; references.

            ; the "if" below needs to be explaind.
            ; Fixups will be written for forward references in pass one.
            ; state is SYM_UNDEFINED then. The fixups will be scanned when
            ; the label is met finally, still in pass one. See backptch.c
            ; for details.

            .if ( state != SYM_UNDEFINED )
                .return( NOT_ERROR ) ; exit, no fixup is written!
            .endif
        .endif
    .endif

    mov fixup_option,OPTJ_NONE
    mov fixup_type,FIX_RELOFF8
    mov mem_type,[rbx].mem_type

    ; v2.04: far call optimization possible if destination is in
    ; another segment of the same group. However, a fixup must be written.
    ; Masm does NOT optimize if destination is external!

    .if ( [rsi].token == T_CALL && [rsi].mem_type == MT_EMPTY &&
          ( [rdi].mem_type == MT_FAR || SegOverride ) )

        mov rax,[rdi].segm
        mov symseg,rax
        xor ecx,ecx
        .if rax
            mov rcx,[rax].asym.seginfo
            .if rcx
                mov rcx,[rcx].seg_info.sgroup
            .endif
        .endif
        mov rdx,CurrSeg
        mov rdx,[rdx].asym.seginfo
        .if ( rax == CurrSeg ||
             ( rax != NULL && rcx != NULL && rcx == [rdx].seg_info.sgroup ) )
            FarCallToNear(rsi) ; switch mem_type to NEAR
        .endif
    .endif

    ; forward ref, or external symbol

    mov al,mem_type
    .if ( [rsi].mem_type == MT_EMPTY && al != MT_EMPTY && [rbx].inst != T_SHORT )

        ; MT_PROC is most likely obsolete ( used by TYPEDEF only )

        .switch al
        .case MT_FAR
            .if( IS_JMPCALL( [rsi].token ) )
                mov [rsi].isfar,1
            .endif
        .case MT_NEAR
            ; v2.04: 'if' added
            .if ( state != SYM_UNDEFINED )
                mov [rsi].mem_type,al
            .endif
            .endc
        .default
            mov [rsi].mem_type,al
        .endsw
    .endif

    ; handle far JMP + CALL?

    mov al,[rsi].mem_type
    .if ( IS_JMPCALL( [rsi].token ) && ( [rsi].isfar || al == MT_FAR ) )
        mov [rsi].isfar,1 ; flag isn't set if explicit is true
        .switch al
        .case MT_NEAR
            .if( [rbx].explicit || [rbx].inst == T_SHORT )
                .return( asmerr( 2077 ) )
            .endif
            ; fall through
        .case MT_FAR
        .case MT_EMPTY
            .if ( [rbx].Ofssize != USE_EMPTY )
                mov [rsi].opsiz,OPSIZE( [rsi].Ofssize, [rbx].Ofssize )
            .else
                mov [rsi].opsiz,OPSIZE( GetSymOfssize(rdi), [rsi].Ofssize )
            .endif
            ; set fixup frame variables Frame + Frame_Datum
            set_frame( rdi )
            .if( IS_OPER_32( rsi ) )
                mov fixup_type,FIX_PTR32
                mov [rsi].opnd[OPND1].type,OP_I48
            .else
                mov fixup_type,FIX_PTR16
                mov [rsi].opnd[OPND1].type,OP_I32
            .endif
            .endc
        .endsw
        mov [rsi].opnd[OPND1].InsFixup,CreateFixup( rdi, fixup_type, fixup_option )
        .return( NOT_ERROR )
    .endif

    movzx eax,[rsi].token
    .switch eax
    .case T_CALL
        .if ( [rbx].inst == T_SHORT )
            .return( asmerr( 2077 ) )
        .endif
        .if ( [rsi].mem_type == MT_EMPTY )
            mov fixup_option,OPTJ_CALL
            .if ( [rsi].Ofssize > USE16 )
                mov fixup_type,FIX_RELOFF32
                mov [rsi].opnd[OPND1].type,OP_I32
            .else
                mov fixup_type,FIX_RELOFF16
                mov [rsi].opnd[OPND1].type,OP_I16
            .endif
            .endc
        .endif
        ; fall through
    .case T_JMP
        mov al,[rsi].mem_type
        .switch al
        .case MT_EMPTY
            ; forward reference
            ; default distance is short, we will expand later if needed
            mov [rsi].opnd[OPND1].type,OP_I8
            mov fixup_type,FIX_RELOFF8
            mov eax,OPTJ_NONE
            .if ( [rbx].inst == T_SHORT )
                mov eax,OPTJ_EXPLICIT
            .endif
            mov fixup_option,eax
            .endc
        .case MT_NEAR
            mov fixup_option,OPTJ_EXPLICIT
            .if( [rbx].Ofssize != USE_EMPTY )
                .if ( [rbx].Ofssize == USE16 )
                    mov fixup_type,FIX_RELOFF16
                    mov [rsi].opnd[OPND1].type,OP_I16
                .else
                    mov fixup_type,FIX_RELOFF32
                    mov [rsi].opnd[OPND1].type,OP_I32
                .endif
                mov [rsi].opsiz,OPSIZE( [rsi].Ofssize, [rbx].Ofssize )
            .else
                .if ( [rsi].Ofssize > USE16 )
                    mov fixup_type,FIX_RELOFF32
                    mov [rsi].opnd[OPND1].type,OP_I32
                .else
                    mov fixup_type,FIX_RELOFF16
                    mov [rsi].opnd[OPND1].type,OP_I16
                .endif
            .endif
            set_frame(rdi)
            .endc
         .endsw
        .endc
    .default
        ; JxCXZ, LOOPxx, Jxx
        ; JxCXZ and LOOPxx always require SHORT label
        .if ( IS_XCX_BRANCH( eax ) )
            .if ( [rsi].mem_type != MT_EMPTY && [rbx].inst != T_SHORT )
                .return( asmerr( 2080 ) )
            .endif
            mov [rsi].opnd[OPND1].type,OP_I8
            mov fixup_option,OPTJ_EXPLICIT
            mov fixup_type,FIX_RELOFF8
           .endc
        .endif
        ; just Jxx remaining
        mov eax,MODULE.curr_cpu
        and eax,P_CPU_MASK
        .if ( eax >= P_386 )
            mov al,[rsi].mem_type
            .switch ( al )
            .case MT_EMPTY
                ; forward reference
                mov eax,OPTJ_JXX
                .if ( [rbx].inst == T_SHORT )
                    mov eax,OPTJ_EXPLICIT
                .endif
                mov fixup_option,eax
                mov fixup_type,FIX_RELOFF8
                mov [rsi].opnd[OPND1].type,OP_I8
               .endc
            .case MT_NEAR
                mov fixup_option,OPTJ_EXPLICIT
                ; v1.95: explicit flag to be removed!
                .if ( [rbx].Ofssize != USE_EMPTY )
                    mov [rsi].opsiz,OPSIZE( [rsi].Ofssize, [rbx].Ofssize )
                    mov eax,OP_I16
                    .if ( [rbx].Ofssize >= USE32 )
                        mov eax,OP_I32
                    .endif
                    mov [rsi].opnd[OPND1].type,eax
                .elseif ( [rsi].Ofssize > USE16 )
                    mov fixup_type,FIX_RELOFF32
                    mov [rsi].opnd[OPND1].type,OP_I32
                .else
                    mov fixup_type,FIX_RELOFF16
                    mov [rsi].opnd[OPND1].type,OP_I16
                .endif
                .endc
            .case MT_FAR
                .if ( MODULE.ljmp ) ; OPTION LJMP set?
                    .if ( [rbx].Ofssize != USE_EMPTY )
                        mov [rsi].opsiz,OPSIZE( [rsi].Ofssize, [rbx].Ofssize )
                    .else
                        mov [rsi].opsiz,OPSIZE( GetSymOfssize(rdi), [rsi].Ofssize )
                    .endif
                    ; destination is FAR (externdef <dest>:far
                    jumpExtend( rsi, TRUE )
                    mov [rsi].isfar,1
                    .if( IS_OPER_32( rsi ) )
                        mov fixup_type,FIX_PTR32
                        mov [rsi].opnd[OPND1].type,OP_I48
                    .else
                        mov fixup_type,FIX_PTR16
                        mov [rsi].opnd[OPND1].type,OP_I32
                    .endif
                    .endc
                .endif
                ; fall through
            .default
                ; is another memtype possible at all?
                .return( asmerr( 2080 ) )
            .endsw
        .else
            ; the only mode in 8086, 80186, 80286 is
            ; Jxx SHORT
            ; Masm allows "Jxx near" if LJMP is on (default)
            mov al,[rsi].mem_type
            .switch al
            .case MT_EMPTY
                .if ( [rbx].inst == T_SHORT )
                    mov fixup_option,OPTJ_EXPLICIT
                .else
                    mov fixup_option,OPTJ_EXTEND
                .endif
                mov fixup_type,FIX_RELOFF8
                mov [rsi].opnd[OPND1].type,OP_I8
               .endc
            .case MT_NEAR ; allow Jxx NEAR if LJMP on
            .case MT_FAR
                .if ( MODULE.ljmp )
                    .if ( al == MT_FAR )
                        jumpExtend( rsi, TRUE )
                        mov fixup_type,FIX_PTR16
                        mov [rsi].isfar,1
                        mov [rsi].opnd[OPND1].type,OP_I32
                    .else
                        jumpExtend( rsi, FALSE )
                        mov fixup_type,FIX_RELOFF16
                        mov [rsi].opnd[OPND1].type,OP_I16
                    .endif
                    .endc
                .endif
                ; fall through
            .default
                .return( asmerr( 2080 ) )
            .endsw
        .endif
    .endsw
    mov [rsi].opnd[OPND1].InsFixup,CreateFixup( rdi, fixup_type, fixup_option )
    mov eax,NOT_ERROR
    ret
    endp

    end
