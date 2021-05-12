; FIXUP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description: handles fixups
;

include asmc.inc
include memalloc.inc
include parser.inc
include fixup.inc
include segment.inc
include omfspec.inc

define GNURELOCS 1
public Frame_Type
public Frame_Datum
extern SegOverride:ptr asym

.data
Frame_Type  db 0 ; curr fixup frame type: SEG|GRP|EXT|ABS|NONE; see omfspec.inc
Frame_Datum dw 0 ; curr fixup frame value
.code

CreateFixup proc uses esi edi ebx sym:ptr asym, type:fixup_types, options:fixup_options

;;
;; called when an instruction operand or a data item is relocatable:
;; - Parser.idata_fixup()
;; - Parser.memory_operand()
;; - branch.process_branch()
;; - data.data_item()
;; - dbgcv()
;; - fpfixup()
;; creates a new fixup item and initializes it using symbol <sym>.
;; put the correct target offset into the link list when forward reference of
;; relocatable is resolved;
;; Global vars Frame_Type and Frame_Datum "should" be set.
;;

    assume ebx:ptr fixup

    mov ebx,LclAlloc( sizeof( fixup ) )
    mov esi,sym

    ;; add the fixup to the symbol's linked list (used for backpatch)
    ;; this is done for pass 1 only.

    .if ( Parse_Pass == PASS_1 )

        .if ( ebx ) ;; changed v1.96

            mov [ebx].nextbp,[esi].asym.bp_fixup
            mov [esi].asym.bp_fixup,ebx
        .endif

        ;; v2.03: in pass one, create a linked list of
        ;; fixup locations for a segment. This is to improve
        ;; backpatching, because it allows to adjust fixup locations
        ;; after a distance has changed from short to near

        mov ecx,CurrSeg
        .if ( ecx )
            mov edx,[ecx].dsym.seginfo
            mov [ebx].nextrlc,[edx].seg_info.head
            mov [edx].seg_info.head,ebx
        .endif
    .endif
    ;; initialize locofs member with current offset.
    ;; It's unlikely to be the final location, but sufficiently exact for backpatching.
    ;;
    mov [ebx].locofs,GetCurrOffset()
    mov [ebx].offs,0
    mov [ebx].type,type
    mov [ebx].options,options
    mov [ebx].flags,0
    mov [ebx].frame_type,Frame_Type     ;; this is just a guess
    mov [ebx].frame_datum,Frame_Datum
    mov [ebx].def_seg,CurrSeg           ;; may be NULL (END directive)
    mov [ebx].sym,esi

    .return( ebx )
CreateFixup endp

;; remove a fixup from the segment's fixup queue

FreeFixup proc uses ebx fixp:ptr fixup

    mov ebx,fixp
    .if ( Parse_Pass == PASS_1 )
        mov ecx,[ebx].def_seg
        .if ( ecx )
            mov edx,[ecx].dsym.seginfo
            .if ( ebx == [edx].seg_info.head )
                mov [edx].seg_info.head,[ebx].nextrlc
            .else
                .for ( ecx = [edx].seg_info.head : ecx : ecx = [ecx].fixup.nextrlc )
                    .if ( [ecx].fixup.nextrlc == ebx )
                        mov [ecx].fixup.nextrlc,[ebx].nextrlc
                        .break
                    .endif
                .endf
            .endif
        .endif
    .endif
    ret

FreeFixup endp

;;
;; Set global variables Frame_Type and Frame_Datum.
;; segment override with a symbol (i.e. DGROUP )
;; it has been checked in the expression evaluator that the
;; symbol has type SYM_SEG/SYM_GRP.
;;

SetFixupFrame proc uses esi edi sym:ptr asym, ign_grp:char_t

    mov esi,sym
    .if ( esi )
        .switch ( [esi].asym.state )
        .case SYM_INTERNAL
        .case SYM_EXTERNAL
            .if( [esi].asym.segm != NULL )
                .if( ign_grp == FALSE && GetGroup( esi ) )
                    mov ecx,[eax].dsym.grpinfo
                    mov Frame_Type,FRAME_GRP
                    mov Frame_Datum,[ecx].grp_info.grp_idx
                .else
                    mov Frame_Type,FRAME_SEG
                    mov Frame_Datum,GetSegIdx( [esi].asym.segm )
                .endif
            .endif
            .endc
        .case SYM_SEG
            mov Frame_Type,FRAME_SEG
            mov Frame_Datum,GetSegIdx( [esi].asym.segm )
            .endc
        .case SYM_GRP
            mov Frame_Type,FRAME_GRP
            mov ecx,[esi].dsym.grpinfo
            mov Frame_Datum,[ecx].grp_info.grp_idx
            .endc
        .endsw
    .endif
    ret

SetFixupFrame endp

;;
;; Store fixup information in segment's fixup linked list.
;; please note: forward references for backpatching are written in PASS 1 -
;; they no longer exist when store_fixup() is called.
;;

store_fixup proc uses esi ebx fixp:ptr fixup, s:ptr dsym, pdata:ptr int_t

    mov ebx,fixp
    mov esi,pdata
    mov [ebx].offs,[esi]

    mov [ebx].nextrlc,NULL
    .if ( Options.output_format == OFORMAT_OMF )

        ;; for OMF, the target's offset is stored at the fixup's location.
        .if ( [ebx].type != FIX_SEG && [ebx].sym )
            mov ecx,[ebx].sym
            add [esi],[ecx].asym.offs
        .endif

    .else

        .if ( Options.output_format == OFORMAT_ELF )
            ;; v2.07: inline addend for ELF32 only.
            ;; Also, in 64-bit, pdata may be a int_64 pointer (FIX_OFF64)!
            ;;
            mov eax,[esi]
            .if ( ModuleInfo.defOfssize == USE64 )
            .elseif ( [ebx].type == FIX_RELOFF32 )
                mov eax,-4
if GNURELOCS ;; v2.04: added
            .elseif ( [ebx].type == FIX_RELOFF16 )
                mov eax,-2
            .elseif ( [ebx].type == FIX_RELOFF8 )
                mov eax,-1
            .endif
endif
            mov [esi],eax
        .endif
        ;; special handling for assembly time variables needed
        mov ecx,[ebx].sym
        .if ( ecx && [ecx].asym.flags & S_VARIABLE )
            ;; add symbol's offset to the fixup location and fixup's offset
            add [esi],[ecx].asym.offs
            add [ebx].offs,[ecx].asym.offs
            ;; and save symbol's segment in fixup
            mov [ebx].segment_var,[ecx].asym.segm
        .endif
    .endif
    mov esi,s
    mov esi,[esi].dsym.seginfo
    .if ( [esi].seg_info.head == NULL )
        mov [esi].seg_info.tail,ebx
        mov [esi].seg_info.head,ebx
    .else
        mov ecx,[esi].seg_info.tail
        mov [ecx].fixup.nextrlc,ebx
        mov [esi].seg_info.tail,ebx
    .endif
    ret
store_fixup endp

    end
