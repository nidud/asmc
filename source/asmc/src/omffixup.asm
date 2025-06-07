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
omf_GetGrpIdx proto fastcall :ptr asym

; logical data for fixup subrecord creation

.template logref
    frame_meth      db ? ; see enum frame_methods in omfspec.h
    frame_datum     dw ? ; datum for certain frame methods
    is_secondary    db ? ; can write target in a secondary manner
    target_meth     db ? ; see enum target_methods in omfspec.h
    target_datum    dw ? ; datum for certain target methods
    target_offset   dd ? ; offset of target for target method
   .ends

endif

   .code

ifndef ASMC64

putIndex proc watcall private p:ptr byte, index:word

    .if ( dx > 0x7f )
        or  dh,0x80
        mov [rax],dh
        inc rax
    .endif
    mov [rax],dl
    inc rax
    ret

putIndex endp


put16 proc watcall private p:ptr byte, value:word

    WriteU16( rax, edx )
    add rax,2
    ret

put16 endp


put32 proc watcall private p:ptr byte, value:dword

    WriteU32( rax, edx )
    add rax,4
    ret

put32 endp


putFrameDatum proc fastcall private p:ptr byte, method:byte, datum:word

    .switch( dl )
    .case FRAME_SEG
    .case FRAME_GRP
    .case FRAME_EXT
        .return( putIndex( rcx, datum ) )
if 0 ; v2.12: FRAME_ABS is invalid according to TIS OMF docs.
    .case FRAME_ABS
        .return( put16( p, datum ) )
endif
    .endsw
    ; for FRAME_LOC & FRAME_TARG ( & FRAME_NONE ) there's no datum to write.
    .return( rcx )

putFrameDatum endp


putTargetDatum proc fastcall private p:ptr byte, method:byte, datum:word

    .return( putIndex( rcx, datum ) )

putTargetDatum endp


; translate logref to FIXUP subrecord ( without Locat field ).
; fields written to buf:
; - uint_8    Fix Data (type of frame and target)
; - index     Frame Datum (optional, index of a SEGDEF, GRPDEF or EXTDEF)
; - index     Target Datum (index of a SEGDEF, GRPDEF or EXTDEF)
; - uint_16/32 Target Displacement (optional)
;
; type is FIX_GEN_INTEL or FIX_GEN_MS386
; v2.12: new function OmfFixGetFixModend() replaced code in writeModend(),
;       TranslateLogref() has become static.

    assume rsi:ptr logref

TranslateLogref proc __ccall private uses rsi rdi rbx lr:ptr logref, buf:ptr byte, type:fixgen_types

    ; According to the discussion on p102 of the Intel OMF document, we
    ; cannot just arbitrarily write fixups without a displacment if their
    ; displacement field is 0. So we use the is_secondary field.

    ldr rsi,lr
    mov bl,[rsi].target_meth

    .if ( [rsi].target_offset == 0 && [rsi].is_secondary )

        or bl,0x04 ; P=1 -> no displacement field
    .endif
    mov rdi,buf

    ; write the "Fix Data" field, FfffTPtt:
    ; F  : 0,frame method is defined in fff field ( F0-F5)
    ;         1,frame is defined by a thread ( won't occur here )
    ; fff: frame method
    ; T  : 0,target is defined by tt
    ;         1,target is defined by thread# in tt, P is used as bit 2 for method
    ; P  : 0,target displacement field is present
    ;         1,no displacement field
    ; tt : target method

    mov al,[rsi].frame_meth
    shl al,4
    or  al,bl
    stosb
    mov rdi,putFrameDatum( rdi, [rsi].frame_meth, [rsi].frame_datum )
    mov rdi,putTargetDatum( rdi, bl, [rsi].target_datum )

    .if ( !( bl & 0x04 ) )

        mov edx,[rsi].target_offset
        .if( type == FIX_GEN_MS386 )
            mov rdi,put32( rdi, edx )
        .else
            mov rdi,put16( rdi, dx )
        .endif
    .endif
    mov rax,rdi
    sub rax,buf
    ret

TranslateLogref endp

endif


; generate start address subfield for MODEND

    assume rbx:ptr fixup

OmfFixGenFixModend proc __ccall uses rdi rbx fixp:ptr fixup, buf:ptr byte, displ:dword, type:fixgen_types

ifndef ASMC64

  local lr:logref

    ldr rbx,fixp
    mov rdi,[rbx].sym

    mov lr.is_secondary,FALSE
    mov eax,[rdi].asym.offs
    add eax,displ
    mov lr.target_offset,eax
    mov lr.frame_datum,[rbx].frame_datum

    ; symbol is always a code label (near or far), internal or external
    ; now set Target and Frame

    .if ( [rdi].asym.state == SYM_EXTERNAL )

        mov lr.target_meth,TARGET_EXT and TARGET_WITH_DISPL
        mov lr.target_datum,[rdi].asym.ext_idx1

        .if ( [rbx].frame_type == FRAME_GRP && [rbx].frame_datum == 0 )

            ; set the frame to the frame of the corresponding segment

            mov lr.frame_datum,omf_GetGrpIdx( rdi )
        .endif
    .else ; SYM_INTERNAL

        mov lr.target_meth,TARGET_SEG and TARGET_WITH_DISPL
        mov lr.target_datum,GetSegIdx( [rdi].asym.segm )
    .endif

    .if ( [rbx].frame_type != FRAME_NONE && [rbx].frame_type != FRAME_SEG )
        mov lr.frame_meth,[rbx].frame_type
    .else
        mov lr.frame_meth,FRAME_TARG
    .endif
    .return( TranslateLogref( &lr, buf, type ) )
else
    .return 0
endif

OmfFixGenFixModend endp


; fill a logref from a fixup's info

ifndef ASMC64

omf_set_logref proc __ccall private uses rsi rdi rbx fixp:ptr fixup, lr:ptr logref

    ldr rsi,lr
    ldr rbx,fixp
    mov rdi,[rbx].sym ; may be NULL!

    ;------------------------------------
    ; Determine the Target and the Frame
    ;------------------------------------

    .if ( rdi == NULL )

        .if ( [rbx].frame_type == FRAME_NONE ) ; v1.96: nothing to do without a frame
            .return( 0 )
        .endif

        ; v2.15: do NOT create fixups for FLAT group frame.
        ; Perhaps never create fixups for GROUP frames? It's useless
        ; unless the linker does pack groups. And, last but not least, jwlink crashes
        ; if target datum contains FLAT group index.

        mov rcx,MODULE.flat_grp
        .if ( rcx )
            mov rcx,[rcx].dsym.grpinfo
            .if ( [rbx].frame_type == FRAME_GRP && [rbx].frame_datum == [rcx].grp_info.grp_idx )
                .return( 0 )
            .endif
        .endif

        mov [rsi].target_meth,[rbx].frame_type
        mov [rsi].target_datum,[rbx].frame_datum
        mov [rsi].frame_meth,FRAME_TARG
if 1
        ; v2.15: modify frame if segment (used in override) is in a group; see lea2.asm.
        ;        note that this mod also affects test offset12.asm!

        .if ( [rbx].frame_type == FRAME_SEG )

            .for ( rcx = SymTables[TAB_SEG*symbol_queue].head : rcx : rcx = [rcx].dsym.next )
                mov rdx,[rcx].dsym.seginfo
                .if ( [rdx].seg_info.seg_idx == [rbx].frame_datum )
                    .if ( [rdx].seg_info.sgroup )
                        mov [rsi].frame_meth,FRAME_GRP
                        mov rcx,[rdx].seg_info.sgroup
                        mov [rsi].frame_datum,[rcx].grp_info.grp_idx
                    .endif
                    .break
                .endif
            .endf
        .endif
endif

    .elseif ( [rdi].asym.state == SYM_UNDEFINED )  ; shouldn't happen

        asmerr( 2006, [rdi].asym.name )
        .return( 0 )

    .elseif ( [rdi].asym.state == SYM_GRP )

        mov [rsi].target_meth,TARGET_GRP
        mov rcx,[rdi].dsym.grpinfo
        mov [rsi].target_datum,[rcx].grp_info.grp_idx
        .if ( [rbx].frame_type != FRAME_NONE )
            mov [rsi].frame_meth,[rbx].frame_type
            mov [rsi].frame_datum,[rbx].frame_datum
        .else
            mov [rsi].frame_meth,FRAME_GRP
            mov [rsi].frame_datum,[rsi].target_datum
        .endif

    .elseif ( [rdi].asym.state == SYM_SEG )

        mov [rsi].target_meth,TARGET_SEG
        mov [rsi].target_datum,GetSegIdx( rdi )
        .if ( [rbx].frame_type != FRAME_NONE )
            mov [rsi].frame_meth,[rbx].frame_type
            mov [rsi].frame_datum,[rbx].frame_datum
        .else
            mov [rsi].frame_meth,FRAME_SEG
            mov [rsi].frame_datum,[rsi].target_datum
        .endif

    .else

        ; symbol is a label

        mov [rsi].frame_datum,[rbx].frame_datum
        .if ( [rdi].asym.state == SYM_EXTERNAL )
            mov [rsi].target_meth,TARGET_EXT
            mov [rsi].target_datum,[rdi].asym.ext_idx1

            .if ( [rbx].frame_type == FRAME_GRP && [rbx].frame_datum == 0 )
                ; set the frame to the frame of the corresponding segment
                mov [rsi].frame_datum,omf_GetGrpIdx( rdi )
            .endif
        .else

if 0 ; v2.19: "isvariable" branch disabled; see label9.asm

            .if ( [rdi].asym.isvariable )
                mov eax,TARGET_SEG
                .if ( [rbx].frame_type == FRAME_GRP )
                    mov eax,TARGET_GRP
                .endif
                mov [rsi].target,al
                mov [rsi].target_datum,[rbx].frame_datum
            .elseif ( [rdi].asym.segm == NULL )  ; shouldn't happen
else
            .if ( [rdi].asym.segm == NULL )  ; shouldn't happen
endif
                asmerr( 3005, [rdi].asym.name )
               .return( 0 )
            .else
                mov rcx,[rdi].asym.segm
                mov rcx,[rcx].dsym.seginfo
                .if ( [rcx].seg_info.comdatselection )
                    mov [rsi].target_meth,TARGET_EXT
                    mov [rsi].target_datum,[rcx].seg_info.seg_idx
                    mov [rsi].frame_meth,FRAME_TARG
                    .return( 1 )
                .endif
                mov [rsi].target_meth,TARGET_SEG
                mov [rsi].target_datum,GetSegIdx( [rdi].asym.segm )
            .endif
        .endif

        .if ( [rbx].frame_type != FRAME_NONE )
            mov [rsi].frame_meth,[rbx].frame_type
        .else
            mov [rsi].frame_meth,FRAME_TARG
        .endif
    .endif

    ; Optimize the fixup

    mov al,[rsi].target_meth
    sub al,TARGET_SEG
    .if ( [rsi].frame_meth == al )
        mov [rsi].frame_meth,FRAME_TARG
    .endif
    .return( 1 )

omf_set_logref endp

endif


; translate a fixup into its binary representation,
; which is a "FIXUPP subrecord" according to OMF docs.
; structure:
; - WORD, Locat: 1MLLLLDD DDDDDDDD, is
;   1,indicates FIXUP, no THREAD subrecord
;   M,mode: 1=segment relative, 0=self relative
;   L,location, see LOC_ entries in omfspec.h
;   D,data record offset, 10 bits for range 0-3FFh
; - BYTE, Fix Data: FRRRTPGG, is
;   F,0=frame defined in fixup, 1=frame defined in frame thread
;   R,Frame
;   T,0=target defined in fixup, 1=Target defined in target thread
;   P,0=target displacement is present
;   G,lower bits of target method (F=0), target thread number (F=1)
; - void/BYTE/WORD, Frame Datum
; - BYTE/WORD, Target Datum
; - WORD/DWORD, Target Displacement


OmfFixGenFix proc __ccall uses rsi rdi rbx fixp:ptr fixup,
    start_loc:dword, buf:ptr byte, type:fixgen_types

ifndef ASMC64

    .new locat1:byte
    .new self_relative:byte = FALSE
    .new data_rec_offset:dword
    .new lr:logref

    mov lr.is_secondary,TRUE
    mov lr.target_offset,0
    ldr rbx,fixp

    .switch( [rbx].type )
    .case FIX_RELOFF8
        mov self_relative,TRUE
        ; no break
    .case FIX_OFF8
        mov locat1,( LOC_OFFSET_LO shl 2 )
        .endc
    .case FIX_RELOFF16
        mov self_relative,TRUE
        ; no break
    .case FIX_OFF16
        mov al,LOC_OFFSET shl 2
        .if ( [rbx].fx_flag & FX_LOADER_RESOLVED )
            mov al,LOC_MS_LINK_OFFSET shl 2
        .endif
        mov locat1,al
        .endc
    .case FIX_RELOFF32
        mov self_relative,TRUE
        ; no break
    .case FIX_OFF32
        mov al,LOC_MS_OFFSET_32 shl 2
        .if ( [rbx].fx_flag & FX_LOADER_RESOLVED )
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
    .default ; shouldn't happen. Check for valid fixup has already happened
        mov rcx,MODULE.fmtopt
        lea rax,szNull
        .if ( [rbx].sym )
            mov rax,[rbx].sym
            mov rax,[rax].asym.name
        .endif
        asmerr( 3001, &[rcx].format_options.formatname, rax )
        .return( 0 )
    .endsw
    mov al,0xc0
    .if ( self_relative )
        mov al,0x80
    .endif
    or locat1,al  ; bit 7: 1=is a fixup subrecord

    .ifd ( omf_set_logref( rbx, &lr ) == 0 )
        .return( 0 )
    .endif

    ; calculate the fixup's position in current LEDATA
    mov eax,[rbx].locofs
    sub eax,start_loc
    mov data_rec_offset,eax
    or  locat1,ah
    mov rcx,buf
    mov [rcx+1],al
    mov al,locat1
    mov [rcx],al
    add rcx,2
    TranslateLogref( &lr, rcx, type )
    .return( &[rax+2] )
else
    .return 0
endif

OmfFixGenFix endp

    end
