; OMFFIXUP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description: handle OMF fixups
;

include stddef.inc
include asmc.inc
include parser.inc
include segment.inc
include fixup.inc
include omfint.inc
include omfspec.inc

ifndef ASMC64

externdef szNull:char_t
omf_GetGrpIdx proto :ptr asym

;; logical data for fixup subrecord creation

.template logref
    frame           db ? ;; see enum frame_methods in omfspec.h
    frame_datum     dw ? ;; datum for certain frame methods
    is_secondary    db ? ;; can write target in a secondary manner
    target          db ? ;; see enum target_methods in omfspec.h
    target_datum    dw ? ;; datum for certain target methods
    target_offset   dd ? ;; offset of target for target method
   .ends

endif

   .code

ifndef ASMC64

putIndex proc watcall private p:ptr byte, index:word

    .if ( dx > 0x7f )
        or  dh,0x80
        mov [eax],dh
        inc eax
    .endif
    mov [eax],dl
    inc eax
    ret

putIndex endp

put16 proc watcall private p:ptr byte, value:word

    WriteU16( eax, edx )
    add eax,2
    ret

put16 endp

put32 proc watcall private p:ptr byte, value:dword

    WriteU32( eax, edx )
    add eax,4
    ret

put32 endp

putFrameDatum proc private p:ptr byte, method:byte, datum:word

    .switch( method )
    .case FRAME_SEG
    .case FRAME_GRP
    .case FRAME_EXT
        .return( putIndex( p, datum ) )
if 0 ;; v2.12: FRAME_ABS is invalid according to TIS OMF docs.
    .case FRAME_ABS
        .return( put16( p, datum ) )
endif
    .endsw
    ;; for FRAME_LOC & FRAME_TARG ( & FRAME_NONE ) there's no datum to write.
    .return( p )

putFrameDatum endp

putTargetDatum proc private p:ptr byte, method:byte, datum:word

    .return( putIndex( p, datum ) )

putTargetDatum endp

;; translate logref to FIXUP subrecord ( without Locat field ).
;; fields written to buf:
;; - uint_8    Fix Data (type of frame and target)
;; - index     Frame Datum (optional, index of a SEGDEF, GRPDEF or EXTDEF)
;; - index     Target Datum (index of a SEGDEF, GRPDEF or EXTDEF)
;; - uint_16/32 Target Displacement (optional)
;;
;; type is FIX_GEN_INTEL or FIX_GEN_MS386
;; v2.12: new function OmfFixGetFixModend() replaced code in writeModend(),
;;       TranslateLogref() has become static.

    assume esi:ptr logref

TranslateLogref proc private uses esi edi ebx lr:ptr logref, buf:ptr byte, type:fixgen_types

    ;; According to the discussion on p102 of the Intel OMF document, we
    ;; cannot just arbitrarily write fixups without a displacment if their
    ;; displacement field is 0. So we use the is_secondary field.

    mov esi,lr
    mov bl,[esi].target
    .if ( [esi].target_offset == 0 && [esi].is_secondary )
        or bl,0x04 ;; P=1 -> no displacement field
    .endif
    mov edi,buf
    ;; write the "Fix Data" field, FfffTPtt:
    ;; F  : 0,frame method is defined in fff field ( F0-F5)
    ;;         1,frame is defined by a thread ( won't occur here )
    ;; fff: frame method
    ;; T  : 0,target is defined by tt
    ;;         1,target is defined by thread# in tt, P is used as bit 2 for method
    ;; P  : 0,target displacement field is present
    ;;         1,no displacement field
    ;; tt : target method
    mov al,[esi].frame
    shl al,4
    or  al,bl
    stosb
    mov edi,putFrameDatum( edi, [esi].frame, [esi].frame_datum )
    mov edi,putTargetDatum( edi, bl, [esi].target_datum )
    .if ( !( bl & 0x04 ) )
        mov edx,[esi].target_offset
        .if( type == FIX_GEN_MS386 )
            mov edi,put32( edi, edx )
        .else
            mov edi,put16( edi, dx )
        .endif
    .endif
    mov eax,edi
    sub eax,buf
    ret

TranslateLogref endp

endif

;; generate start address subfield for MODEND

    assume ebx:ptr fixup

OmfFixGenFixModend proc uses edi ebx fixp:ptr fixup, buf:ptr byte, displ:dword, type:fixgen_types

ifndef ASMC64

  local lr:logref

    mov ebx,fixp
    mov edi,[ebx].sym

    mov lr.is_secondary,FALSE
    mov eax,[edi].asym.offs
    add eax,displ
    mov lr.target_offset,eax
    mov lr.frame_datum,[ebx].frame_datum

    ;; symbol is always a code label (near or far), internal or external
    ;; now set Target and Frame

    .if ( [edi].asym.state == SYM_EXTERNAL )

        mov lr.target,TARGET_EXT and TARGET_WITH_DISPL
        mov lr.target_datum,[edi].asym.ext_idx1

        .if ( [ebx].frame_type == FRAME_GRP && [ebx].frame_datum == 0 )
            ;; set the frame to the frame of the corresponding segment
            mov lr.frame_datum,omf_GetGrpIdx( edi )
        .endif
    .else  ;; SYM_INTERNAL

        mov lr.target,TARGET_SEG and TARGET_WITH_DISPL
        mov lr.target_datum,GetSegIdx( [edi].asym.segm )
    .endif

    .if ( [ebx].frame_type != FRAME_NONE && [ebx].frame_type != FRAME_SEG )
        mov lr.frame,[ebx].frame_type
    .else
        mov lr.frame,FRAME_TARG
    .endif
    .return( TranslateLogref( &lr, buf, type ) )
else
    .return 0
endif

OmfFixGenFixModend endp

;; fill a logref from a fixup's info
ifndef ASMC64

omf_fill_logref proc private uses esi edi ebx fixp:ptr fixup, lr:ptr logref

    mov esi,lr
    mov ebx,fixp
    mov edi,[ebx].sym ;; may be NULL!

    ;;------------------------------------
    ;; Determine the Target and the Frame
    ;;------------------------------------

    .if ( edi == NULL )

        .if ( [ebx].frame_type == FRAME_NONE ) ;; v1.96: nothing to do without a frame
            .return( 0 )
        .endif

        mov [esi].target,[ebx].frame_type
        mov [esi].target_datum,[ebx].frame_datum
        mov [esi].frame,FRAME_TARG

    .elseif ( [edi].asym.state == SYM_UNDEFINED )  ;; shouldn't happen

        asmerr( 2006, [edi].asym.name )
        .return( 0 )

    .elseif ( [edi].asym.state == SYM_GRP )

        mov [esi].target,TARGET_GRP
        mov ecx,[edi].dsym.grpinfo
        mov [esi].target_datum,[ecx].grp_info.grp_idx
        .if ( [ebx].frame_type != FRAME_NONE )
            mov [esi].frame,[ebx].frame_type
            mov [esi].frame_datum,[ebx].frame_datum
        .else
            mov [esi].frame,FRAME_GRP
            mov [esi].frame_datum,[esi].target_datum
        .endif

    .elseif ( [edi].asym.state == SYM_SEG )

        mov [esi].target,TARGET_SEG
        mov [esi].target_datum,GetSegIdx( edi )
        .if ( [ebx].frame_type != FRAME_NONE )
            mov [esi].frame,[ebx].frame_type
            mov [esi].frame_datum,[ebx].frame_datum
        .else
            mov [esi].frame,FRAME_SEG
            mov [esi].frame_datum,[esi].target_datum
        .endif

    .else

        ;; symbol is a label

        mov [esi].frame_datum,[ebx].frame_datum
        .if ( [edi].asym.state == SYM_EXTERNAL )
            mov [esi].target,TARGET_EXT
            mov [esi].target_datum,[edi].asym.ext_idx1

            .if ( [ebx].frame_type == FRAME_GRP && [ebx].frame_datum == 0 )
                ;; set the frame to the frame of the corresponding segment
                mov [esi].frame_datum,omf_GetGrpIdx( edi )
            .endif
        .else
            .if ( [edi].asym.flags & S_VARIABLE )
                mov eax,TARGET_SEG
                .if ( [ebx].frame_type == FRAME_GRP )
                    mov eax,TARGET_GRP
                .endif
                mov [esi].target,al
                mov [esi].target_datum,[ebx].frame_datum
            .elseif ( [edi].asym.segm == NULL )  ;; shouldn't happen
                asmerr( 3005, [edi].asym.name )
                .return ( 0 )
            .else
                mov ecx,[edi].asym.segm
                mov ecx,[ecx].dsym.seginfo
                .if ( [ecx].seg_info.comdatselection )
                    mov [esi].target,TARGET_EXT
                    mov [esi].target_datum,[ecx].seg_info.seg_idx
                    mov [esi].frame,FRAME_TARG
                    .return( 1 )
                .endif
                mov [esi].target,TARGET_SEG
                mov [esi].target_datum,GetSegIdx( [edi].asym.segm )
            .endif
        .endif

        .if ( [ebx].frame_type != FRAME_NONE )
            mov [esi].frame,[ebx].frame_type
        .else
            mov [esi].frame,FRAME_TARG
        .endif
    .endif

    ;;--------------------
    ;; Optimize the fixup
    ;;--------------------
    mov al,[esi].target
    sub al,TARGET_SEG
    .if ( [esi].frame == al )
        mov [esi].frame,FRAME_TARG
    .endif
    .return( 1 )

omf_fill_logref endp

endif

;; translate a fixup into its binary representation,
;; which is a "FIXUPP subrecord" according to OMF docs.
;; structure:
;; - WORD, Locat: 1MLLLLDD DDDDDDDD, is
;;   1,indicates FIXUP, no THREAD subrecord
;;   M,mode: 1=segment relative, 0=self relative
;;   L,location, see LOC_ entries in omfspec.h
;;   D,data record offset, 10 bits for range 0-3FFh
;; - BYTE, Fix Data: FRRRTPGG, is
;;   F,0=frame defined in fixup, 1=frame defined in frame thread
;;   R,Frame
;;   T,0=target defined in fixup, 1=Target defined in target thread
;;   P,0=target displacement is present
;;   G,lower bits of target method (F=0), target thread number (F=1)
;; - void/BYTE/WORD, Frame Datum
;; - BYTE/WORD, Target Datum
;; - WORD/DWORD, Target Displacement


OmfFixGenFix proc uses esi edi ebx fixp:ptr fixup, start_loc:dword, buf:ptr byte, type:fixgen_types

ifndef ASMC64

    .new locat1:byte
    .new self_relative:byte = FALSE
    .new data_rec_offset:dword
    .new lr:logref

    mov lr.is_secondary,TRUE
    mov lr.target_offset,0
    mov ebx,fixp

    .switch( [ebx].type )
    .case FIX_RELOFF8
        mov self_relative,TRUE
        ;; no break
    .case FIX_OFF8
        mov locat1,( LOC_OFFSET_LO shl 2 )
        .endc
    .case FIX_RELOFF16
        mov self_relative,TRUE
        ;; no break
    .case FIX_OFF16
        mov al,LOC_OFFSET shl 2
        .if ( [ebx].fx_flag & FX_LOADER_RESOLVED )
            mov al,LOC_MS_LINK_OFFSET shl 2
        .endif
        mov locat1,al
        .endc
    .case FIX_RELOFF32
        mov self_relative,TRUE
        ;; no break
    .case FIX_OFF32
        mov al,LOC_MS_OFFSET_32 shl 2
        .if ( [ebx].fx_flag & FX_LOADER_RESOLVED )
            mov al,LOC_MS_LINK_OFFSET_32 shl 2
        .endif
        mov locat1,al
        .endc
    .case FIX_HIBYTE
        mov locat1,( LOC_OFFSET_HI shl 2 )
        .endc
    .case FIX_SEG
        mov locat1,( LOC_BASE shl 2 )
        .endc
    .case FIX_PTR16
        mov locat1,( LOC_BASE_OFFSET shl 2 )
        .endc
    .case FIX_PTR32
        mov locat1,( LOC_MS_BASE_OFFSET_32 shl 2 )
        .endc
    .default ;; shouldn't happen. Check for valid fixup has already happened
        mov ecx,ModuleInfo.fmtopt
        lea eax,szNull
        .if ( edi )
            mov eax,[edi].asym.name
        .endif
        asmerr( 3001, [ecx].format_options.formatname, eax )
        .return( 0 )
    .endsw
    mov al,0xc0
    .if ( self_relative )
        mov al,0x80
    .endif
    or locat1,al  ;; bit 7: 1=is a fixup subrecord

    .if ( omf_fill_logref( ebx, &lr ) == 0 )
        .return( 0 )
    .endif

    ;; calculate the fixup's position in current LEDATA
    mov eax,[ebx].locofs
    sub eax,start_loc
    mov data_rec_offset,eax
    or  locat1,ah
    mov ecx,buf
    mov [ecx+1],al
    mov al,locat1
    mov [ecx],al
    add ecx,2
    TranslateLogref( &lr, ecx, type )
    .return( &[eax+2] )
else
    .return 0
endif
OmfFixGenFix endp

    end
