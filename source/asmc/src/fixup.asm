; FIXUP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description: handles fixups
;

include asmc.inc
include memalloc.inc
include fixup.inc
include segment.inc
include omfspec.inc

define GNURELOCS 1

public Frame_Type
public Frame_Datum

extern SegOverride:asym_t

.data
 Frame_Type  db 0 ; curr fixup frame type: SEG|GRP|EXT|ABS|NONE; see omfspec.inc
 Frame_Datum dw 0 ; curr fixup frame value

.code

; called when an instruction operand or a data item is relocatable:
; - Parser.idata_fixup()
; - Parser.memory_operand()
; - branch.process_branch()
; - data.data_item()
; - dbgcv()
; - fpfixup()
; creates a new fixup item and initializes it using symbol <sym>.
; put the correct target offset into the link list when forward reference of
; relocatable is resolved;
; Global vars Frame_Type and Frame_Datum "should" be set.

    assume rbx:ptr fixup

CreateFixup proc __ccall uses rsi rdi rbx sym:asym_t, type:fixup_types, options:fixup_options

    ldr rsi,sym

    mov rbx,LclAlloc( sizeof( fixup ) )

    ; add the fixup to the symbol's linked list (used for backpatch)
    ; this is done for pass 1 only.

    .if ( Parse_Pass == PASS_1 )

        .if ( rsi && !( [rsi].asym.isdefined ) ) ; changed v1.96

            mov [rbx].nextbp,[rsi].asym.bp_fixup
            mov [rsi].asym.bp_fixup,rbx
        .endif

        ; v2.03: in pass one, create a linked list of
        ; fixup locations for a segment. This is to improve
        ; backpatching, because it allows to adjust fixup locations
        ; after a distance has changed from short to near

        mov rcx,CurrSeg
        .if ( rcx )
            mov rdx,[rcx].asym.seginfo
            mov [rbx].nextrlc,[rdx].seg_info.head
            mov [rdx].seg_info.head,rbx
        .endif
    .endif

    ; initialize locofs member with current offset.
    ; It's unlikely to be the final location, but sufficiently exact for backpatching.

    mov [rbx].locofs,GetCurrOffset()
    mov [rbx].offs,0
    mov [rbx].type,type
    mov [rbx].options,options
    mov [rbx].flags,0
    mov [rbx].frame_type,Frame_Type     ; this is just a guess
    mov [rbx].frame_datum,Frame_Datum
    mov [rbx].def_seg,CurrSeg           ; may be NULL (END directive)
    mov [rbx].sym,rsi
   .return( rbx )

CreateFixup endp


;
; Set global variables Frame_Type and Frame_Datum.
; segment override with a symbol (i.e. DGROUP )
; it has been checked in the expression evaluator that the
; symbol has type SYM_SEG/SYM_GRP.
;

SetFixupFrame proc __ccall uses rsi rdi sym:asym_t, ign_grp:char_t

    ldr rsi,sym
    .if ( rsi )

        movzx eax,[rsi].asym.state
        .switch eax
        .case SYM_INTERNAL
        .case SYM_EXTERNAL
            .if( [rsi].asym.segm != NULL )
                .if( ign_grp == FALSE && GetGroup( rsi ) )
                    mov rcx,[rax].asym.grpinfo
                    mov Frame_Type,FRAME_GRP
                    mov Frame_Datum,[rcx].grp_info.grp_idx
                .else
                    mov Frame_Type,FRAME_SEG
                    mov Frame_Datum,GetSegIdx( [rsi].asym.segm )
                .endif
            .endif
            .endc
        .case SYM_SEG
            mov Frame_Type,FRAME_SEG
            mov Frame_Datum,GetSegIdx( [rsi].asym.segm )
            .endc
        .case SYM_GRP
            mov Frame_Type,FRAME_GRP
            mov rcx,[rsi].asym.grpinfo
            mov Frame_Datum,[rcx].grp_info.grp_idx
            .endc
        .endsw
    .endif
    ret

SetFixupFrame endp


;
; Store fixup information in segment's fixup linked list.
; please note: forward references for backpatching are written in PASS 1 -
; they no longer exist when store_fixup() is called.
;

store_fixup proc __ccall uses rsi rbx fixp:ptr fixup, s:asym_t, pdata:ptr int_t

    ldr rbx,fixp
    ldr rsi,pdata

    mov [rbx].offs,[rsi]
    mov [rbx].nextrlc,NULL

    .if ( Options.output_format == OFORMAT_OMF )

        ; for OMF, the target's offset is stored at the fixup's location.

        .if ( [rbx].type != FIX_SEG && [rbx].sym )
            mov rcx,[rbx].sym
            add [rsi],[rcx].asym.offs
        .endif

    .else

        .if ( Options.output_format == OFORMAT_ELF )

            ; v2.07: inline addend for ELF32 only.
            ; Also, in 64-bit, pdata may be a int_64 pointer (FIX_OFF64)!

            mov eax,[rsi]
            .if ( MODULE.defOfssize == USE64 )

                xor eax,eax ; added v2.33.46 - @Hello71

                ; offset added in write_relocs64()

                ; mov [rsi+4],eax ; --> opnd_item.data64

            .elseif ( [rbx].type == FIX_RELOFF32 )
                mov eax,-4

if GNURELOCS ; v2.04: added

            .elseif ( [rbx].type == FIX_RELOFF16 )
                mov eax,-2
            .elseif ( [rbx].type == FIX_RELOFF8 )
                mov eax,-1
            .endif
endif
            mov [rsi],eax
        .endif

        ; special handling for assembly time variables needed

        mov rcx,[rbx].sym
        .if ( rcx && [rcx].asym.isvariable )

            ; add symbol's offset to the fixup location and fixup's offset

            mov eax,[rcx].asym.offs ; added v2.33.48
            .if ( !( Options.output_format == OFORMAT_ELF &&
                     MODULE.defOfssize == USE64 ) )
                add [rsi],eax
            .endif
            add [rbx].offs,eax

            ; and save symbol's segment in fixup

            mov [rbx].segment_var,[rcx].asym.segm
        .endif
    .endif

    mov rsi,s
    mov rsi,[rsi].asym.seginfo
    .if ( [rsi].seg_info.head == NULL )
        mov [rsi].seg_info.tail,rbx
        mov [rsi].seg_info.head,rbx
    .else
        mov rcx,[rsi].seg_info.tail
        mov [rcx].fixup.nextrlc,rbx
        mov [rsi].seg_info.tail,rbx
    .endif
    ret

store_fixup endp

    end
