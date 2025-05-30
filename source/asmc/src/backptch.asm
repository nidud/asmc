; BACKPTCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; backpatch: short forward jump optimization.
;

include asmc.inc
include symbols.inc
include fixup.inc
include segment.inc

; LABELOPT: short jump label optimization.
; if this is 0, there is just the simple "fixup backpatch",
; which cannot adjust any label offsets between the forward reference
; and the newly defined label, resulting in more passes to be needed.

LABELOPT equ 1

    .code

    assume rsi:asym_t
    assume rbx:fixup_t

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

   .new next:fixup_t

    .return( NOT_ERROR ) .if ( Parse_Pass != PASS_1 )

    .for ( rsi = rcx, rbx = [rsi].bp_fixup : rbx : rbx = next )

        mov next,[rbx].nextbp

        ; all relative fixups should occure only at first pass and they signal forward references
        ; they must be removed after patching or skiped ( next processed as normal fixup )

        mov rax,[rsi].segm

        ; if fixup location is in another segment, backpatch is possible, but
        ; complicated and it's a pretty rare case, so nothing's done.

        .continue .if ( rax == NULL || [rbx].def_seg != rax )

        xor edi,edi         ; size
        movzx ecx,[rbx].type

        .if ( [rsi].mem_type == MT_FAR && [rbx].options == OPTJ_CALL )

            ; convert near call to push cs + near call,
            ; (only at first pass)

            mov MODULE.PhaseError,TRUE
            inc [rsi].offs ; a PUSH CS will be added

            ; todo: insert LABELOPT block here

            OutputByte(0) ; it's pass one, nothing is written
           .continue

        .else

            ; forward reference, only at first pass

            .if ( ecx == FIX_RELOFF32 || ecx == FIX_RELOFF16 )

               .continue
            .endif

            .if ( ecx == FIX_OFF8 ) ; push <forward reference>

                .if ( [rbx].options == OPTJ_PUSH )

                    mov edi,1 ; size increases from 2 to 3/5
                    jmp patch
                .endif
            .endif
        .endif

        .switch ecx
        .case FIX_RELOFF32
            mov edi,2   ; will be 4 finally
                        ; fall through
        .case FIX_RELOFF16
            inc edi     ; will be 2 finally
                        ; fall through
        .case FIX_RELOFF8
            inc edi     ; calculate the displacement
            mov rcx,[rbx].sym
            mov edx,[rbx].offs
            add edx,[rcx].asym.offs
            sub edx,[rbx].locofs
            sub edx,edi
            sub edx,1   ; displacement
            lea ecx,[rdi*8-1]
            mov eax,1
            shl eax,cl
            dec eax     ; max displacement
            mov ecx,eax
            neg ecx
            dec ecx

            .ifs ( edx > eax || edx < ecx )

              patch:

                mov MODULE.PhaseError,TRUE

                ; ok, the standard case is: there's a forward jump which
                ; was assumed to be SHORT, but it must be NEAR instead.

                .switch edi
                .case 1
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
                        mov rdx,[rsi].segm
                        mov rdx,[rdx].dsym.seginfo
                        assume rdx:segment_t
                        .if ( [rdx].Ofssize )
                            add edi,2 ; NEAR32 instead of NEAR16
                        .endif
                        inc edi
if LABELOPT
                        ; v2.04: if there's an ORG between src and dst, skip
                        ; the optimization!

                        mov eax,[rbx].locofs

                        .for ( rcx = [rdx].head: rcx: rcx = [rcx].fixup.nextrlc )

                            .continue(1) .if ( [rcx].fixup.fx_flag & FX_ORGOCCURED )

                            ; do this check after the check for ORG!

                            .break .if ( [rcx].fixup.locofs <= eax )
                        .endf

                        ; scan the segment's label list and adjust all labels
                        ; which are between the fixup loc and the current sym.
                        ; ( PROCs are NOT contained in this list because they
                        ; use the <next>-field of dsym already!)

                        .for ( rcx = [rdx].label_list: rcx: rcx = [rcx].dsym.next )

                            .break .if ( [rcx].asym.offs <= eax )

                            add [rcx].asym.offs,edi
                        .endf

                        ; v2.03: also adjust fixup locations located between the
                        ; label reference and the label. This should reduce the
                        ; number of passes to 2 for not too complex sources.

                        .for ( rcx = [rdx].head: rcx: rcx = [rcx].fixup.nextrlc )

                            .if ( [rcx].fixup.sym != rsi )

                                .break .if ( [rcx].fixup.locofs <= eax )
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
                        .endc
                    .endsw
                    .endc
                .case 2
                .case 4
                    sub edx,eax
                    asmerr( 2075, edx ) ; warning ?
                .endsw
            .endif

            ; v2.04: fixme: is it ok to remove the fixup?
            ; it might still be needed in a later backpatch.
        .endsw
    .endf
    xor eax,eax ; NOT_ERROR
    mov [rsi].bp_fixup,rax
    ret

BackPatch endp

    end
