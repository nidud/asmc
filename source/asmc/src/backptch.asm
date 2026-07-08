; BACKPTCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; backpatch: short forward jump optimization.
;

include asmc.inc
include fixup.inc
include segment.inc

; LABELOPT: short jump label optimization.
; if this is 0, there is just the simple "fixup backpatch",
; which cannot adjust any label offsets between the forward reference
; and the newly defined label, resulting in more passes to be needed.

define LABELOPT

.code

 assume rsi:asym_t, rbx:fixup_t

;
; patching for forward reference labels in Jmp/Call instructions;
; called by LabelCreate(), ProcDef() and data_dir(), that is, whenever
; a (new) label is defined. The new label is the <sym> parameter.
; During the process, the label's offset might be changed!
;
; field sym->fixup is a "descending" list of forward references
; to this symbol. These fixups are only generated during pass 1.
;

BackPatch proc fastcall uses rsi rdi rbx _sym:asym_t

    .for ( rsi = rcx, rbx = [rsi].bp_fixup : rbx : rbx = [rbx].nextbp )

        .continue .if ( [rbx].options == OPTJ_NONE )

        ; all relative fixups should occure only at first pass and they signal forward references
        ; they must be removed after patching or skiped ( next processed as normal fixup )

        mov rax,[rsi].segm

        ; if fixup location is in another segment, backpatch is possible, but
        ; complicated and it's a pretty rare case, so nothing's done.

        .continue .if ( rax == NULL || [rbx].def_seg != rax )

        xor edi,edi         ; size
        movzx ecx,[rbx].type

        ; forward reference, only at first pass

        .switch ecx
        .case FIX_RELOFF32
        .case FIX_RELOFF16
            .if ( [rsi].mem_type == MT_FAR && [rbx].options == OPTJ_CALL )

                ; convert near call to push cs + near call,
                ; (only at first pass)

                mov MODULE.PhaseError,TRUE
                inc [rsi].offs ; a PUSH CS will be added

                ; todo: insert LABELOPT block here

                OutputByte(0) ; it's pass one, nothing is written
            .endif
            .continue
        .case FIX_OFF8 ; push <forward reference>
            .if ( [rbx].options == OPTJ_PUSH )
                inc edi ; size increases from 2 to 3/5
            .endif
            .endc
        .case FIX_RELOFF8
            mov rcx,[rbx].sym ; calculate the displacement
            mov eax,[rbx].offs
            add eax,[rcx].asym.offs
            sub eax,[rbx].locofs
            sub eax,2
            .ifs ( eax > 127 || eax < -128 )
                inc edi
            .endif
        .endsw
        .continue .if ( !edi )
        ;
        ; ok, the standard case is: there's a forward jump which
        ; was assumed to be SHORT, but it must be NEAR instead.
        ;
        xor edi,edi
        .switch( [rbx].options )
        .case OPTJ_EXPLICIT
            .continue
        .case OPTJ_EXTEND   ; Jxx for 8086
            inc edi         ; will be 3/5 finally
                            ; fall through
        .case OPTJ_JXX      ; Jxx for 386
            inc edi         ; fall through
        .default            ; normal JMP (and PUSH)

            mov MODULE.PhaseError,TRUE

            mov rdx,[rsi].segm
            mov rdx,[rdx].asym.seginfo
            assume rdx:segment_t
            .if ( [rdx].Ofssize )
                add edi,2 ; NEAR32 instead of NEAR16
            .endif
            inc edi
ifdef LABELOPT
            ; v2.04: if there's an ORG between src and dst, skip
            ; the optimization!

            .for ( eax = [rbx].locofs, rcx = [rdx].head : rcx : rcx = [rcx].fixup.nextrlc )
                .if ( [rcx].fixup.orgoccured )
                    mov MODULE.OrgOccured,1 ; v2.37.93: added - see CreateLabel()
                   .endc
                .endif
                ; do this check after the check for ORG!
                .break .if ( eax >= [rcx].fixup.locofs )
            .endf

            ; scan the segment's label list and adjust all labels
            ; which are between the fixup loc and the current sym.
            ; ( PROCs are NOT contained in this list because they
            ; use the <next>-field of asym already!)

            .for ( rcx = [rdx].label_list : rcx : rcx = [rcx].asym.next )
                .break .if ( eax >= [rcx].asym.offs )
                add [rcx].asym.offs,edi
            .endf

            ; v2.03: also adjust fixup locations located between the
            ; label reference and the label. This should reduce the
            ; number of passes to 2 for not too complex sources.

            .for ( rcx = [rdx].head : rcx : rcx = [rcx].fixup.nextrlc )
                .if ( rsi != [rcx].fixup.sym )
                    .break .if ( eax >= [rcx].fixup.locofs )
                    add [rcx].fixup.locofs,edi
                .endif
            .endf
else
            add [rsi].offs,edi
endif
            ; it doesn't matter what's actually "written"

            .for ( : edi : edi-- )
                OutputByte( 0xCC )
            .endf
        .endsw
    .endf
    ret
    endp

    end
