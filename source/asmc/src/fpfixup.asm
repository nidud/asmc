; FPFIXUP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description:  FP fixups for 16-bit code. These fixups allow the linker
;               or program loader to replace FP instructions by calls to
;               an FP emulation library.
;

include asmc.inc
include parser.inc
include extern.inc
include fixup.inc
include mangle.inc
include segment.inc
include omf.inc
include omfspec.inc

.enum fp_patches {
    FPP_WAIT,
    FPP_NORMAL,
    FPP_ES, ; last 6 entries match order of ASSUME_ES, ...
    FPP_CS,
    FPP_SS,
    FPP_DS,
    FPP_FS,
    FPP_GS
    }

; FP 16-bit fixup names.
; Known by MS VC, Open Watcom, Borland and Digital Mars:
;  FIWRQQ, FIDRQQ, FIERQQ, FICRQQ, FISRQQ, FIARQQ, FIFRQQ, FIGRQQ,
;                          FJCRQQ, FJSRQQ, FJARQQ, FJFRQQ, FJGRQQ

define patchmask 0xF8FF

.data
 patchchr2 db 'W', 'D', 'E', 'C', 'S', 'A', 'F', 'G'

.code

AddFloatingPointEmulationFixup proc uses esi edi ebx CodeInfo:ptr code_info

  local sym[2]:ptr asym
  local data:int_t
  local name[2]:DWORD

    mov name[0],"R__F"
    mov name[4],"QQ"

    mov ecx,CodeInfo
    .if( [ecx].code_info.token == T_FWAIT )
        mov edi,FPP_WAIT
    .elseif ( [ecx].code_info.RegOverride == EMPTY )
        mov edi,FPP_NORMAL
    .else
        mov edi,[ecx].code_info.RegOverride
        add edi,2
    .endif

    ; emit 1-2 externals for the patch if not done already

    .for ( ebx = 0 : ebx < 2 : ebx++ )

        mov sym[ebx*4],NULL
        lea ecx,[edi+ebx*8]
        mov eax,1
        shl eax,cl

        .if ( eax & patchmask )

            lea eax,[ebx+'I']
            mov byte ptr name[1],al
            mov al,patchchr2[edi]
            mov byte ptr name[2],al
            mov sym[ebx*4],SymSearch( &name )

            .if ( eax == NULL || [eax].asym.state == SYM_UNDEFINED )
                mov sym[ebx*4],MakeExtern( &name, MT_FAR, NULL, eax, USE16 )
                mov [eax].asym.langtype,LANG_NONE
            .endif
        .endif
    .endf

    ; no need for fixups if no object file is written

    .return .if ( write_to_file == FALSE )

    ; make sure the next 3 bytes in code stream aren't separated.
    ; The first fixup covers bytes $+0 and $+1, the (possible) second
    ; fixup covers bytes $+1 and $+2.

    mov edi,CurrSeg
    mov edx,[edi].dsym.seginfo
    mov eax,[edx].seg_info.current_loc
    sub eax,[edx].seg_info.start_loc
    add eax,3
    .if ( Options.output_format == OFORMAT_OMF && eax > MAX_LEDATA_THRESHOLD )
        omf_FlushCurrSeg()
    .endif

    assume esi:ptr fixup
    .for ( ebx = 0 : ebx < 2 : ebx++ )
        mov eax,sym[ebx*4]
        .if ( eax )
            mov esi,CreateFixup( eax, FIX_OFF16, OPTJ_NONE )
            mov [esi].frame_type,FRAME_TARG
            add [esi].locofs,ebx
            mov data,0
            store_fixup( esi, edi, &data )
        .endif
    .endf
    ret

AddFloatingPointEmulationFixup endp

    end
