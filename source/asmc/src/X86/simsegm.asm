; SIMSEGM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description: Processing simplified segment directives:
;  - .CODE, .DATA, .DATA?, .CONST, .STACK, .FARDATA, .FARDATA?
;

include asmc.inc
include memalloc.inc
include parser.inc
include segment.inc
include lqueue.inc
include expreval.inc
include fastpass.inc
include listing.inc
include tokenize.inc

define DEFAULT_STACK_SIZE 1024
define T <@CStr>

.data

externdef szDgroup:sbyte

SegmNames string_t SIM_LAST dup(0)

SegmNamesDef string_t \
    T("_TEXT"),
    T("STACK"),
    T("_DATA"),
    T("_BSS"),
    T("FAR_DATA"),
    T("FAR_BSS"),
    T("CONST")

SegmClass string_t \
    T("CODE"),
    T("STACK"),
    T("DATA"),
    T("BSS"),
    T("FAR_DATA"),
    T("FAR_BSS"),
    T("CONST")

SegmCombine string_t \
    T("PUBLIC"),
    T("STACK"),
    T("PUBLIC"),
    T("PUBLIC"),
    T("PRIVATE"),
    T("PRIVATE"),
    T("PUBLIC")

.code

SimGetSegName proc segno:sim_seg
    mov ecx,segno
    .return( SegmNames[ecx*4] )
SimGetSegName endp

GetCodeClass proc
    ;; option -nc set?
    .if ( Options.names[OPTN_CODE_CLASS*4] )
        .return( Options.names[OPTN_CODE_CLASS*4] )
    .endif
    .return( SegmClass[SIM_CODE*4] )
GetCodeClass endp

;; emit DGROUP GROUP instruction

AddToDgroup proc fastcall private segm:sim_seg, name:string_t

    ;; no DGROUP for FLAT or COFF/ELF
    .if ( ModuleInfo._model == MODEL_FLAT || \
          Options.output_format == OFORMAT_COFF || \
          Options.output_format == OFORMAT_ELF )
        .return
    .endif
    .if ( name == NULL )
        mov name,SegmNames[segm*4]
    .endif
    AddLineQueueX( "%s %r %s", &szDgroup, T_GROUP, name )
    ret

AddToDgroup endp

;; generate code to close the current segment

close_currseg proc private

    .if ( CurrSeg )
        mov ecx,CurrSeg
        AddLineQueueX( "%s %r", [ecx].asym.name, T_ENDS )
    .endif
    ret

close_currseg endp

;; translate a simplified segment directive to
;; a standard segment directive line

SetSimSeg proc private uses esi edi ebx segm:sim_seg, name:string_t

    .new pAlign:string_t = "WORD"
    .new pAlignSt:string_t = "PARA"
    .new pUse:string_t = ""
    .new calign[16]:char_t
    .new sym:ptr asym
    .new pFmt:string_t
    .new pClass:string_t

    ;; v2.24 /Sp[n] Set segment alignment

    .if ( Options.segmentalign != 4 )

        mov edx,1
        mov cl,Options.segmentalign
        shl edx,cl
        sprintf( &calign, "ALIGN(%d)", edx )
        mov pAlignSt,&calign
    .endif

    .if ( ModuleInfo.defOfssize > USE16 )
        .if ( ModuleInfo._model == MODEL_FLAT )
            mov pUse,&T("FLAT")
        .else
            mov pUse,&T("USE32")
        .endif

        mov eax,ModuleInfo.curr_cpu
        and eax,P_CPU_MASK

        .if ( Options.segmentalign != 4 )
            mov pAlign,&calign
        .elseif ( eax <= P_386 )
            mov pAlign,&T("DWORD")
        .else
            mov pAlign,&T("PARA")
        .endif
        mov pAlignSt,pAlign
    .endif
    mov esi,segm
    .if ( esi == SIM_CODE )
        mov pClass,GetCodeClass()
    .else
        mov pClass,SegmClass[esi*4]
    .endif

    .if ( esi == SIM_STACK || esi == SIM_FARDATA || esi == SIM_FARDATA_UN )
        mov pAlign,pAlignSt
    .endif

    mov pFmt,&T("%s %r %s %s %s '%s'")
    mov edi,name
    .if ( edi == NULL )
        mov edi,SegmNames[esi*4]

        mov ebx,1
        mov ecx,esi
        shl ebx,cl

        .if ( ModuleInfo.simseg_init & bl )
            mov pFmt,&T("%s %r")
        .else
            or ModuleInfo.simseg_init,bl
            ;; v2.05: if segment exists already, use the current attribs.
            ;; This allows a better mix of full and simplified segment
            ;; directives. Masm behaves differently: the attributes
            ;; of the simplified segment directives have highest priority.

            .if ( Parse_Pass == PASS_1 )
                SymSearch( edi )
                ;; v2.12: check 'isdefined' member instead of 'lname_idx'
                .if ( eax && [eax].asym.state == SYM_SEG && [eax].asym.flags & S_ISDEFINED )
                    or ModuleInfo.simseg_defd,bl
                .endif
            .endif
            .if ( ModuleInfo.simseg_defd & bl )
                mov pFmt,&T("%s %r")
            .endif
        .endif
    .else
        SymSearch( edi )
        ;; v2.04: testing for state SYM_SEG isn't enough. The segment
        ;; might have been "defined" by a GROUP directive. Additional
        ;; check for segment's lname index is needed.
        ;; v2.12: check 'isdefined' member instead of 'lname_idx'

        .if ( eax && [eax].asym.state == SYM_SEG && [eax].asym.flags & S_ISDEFINED )
            mov pFmt,&T("%s %r")
        .endif
    .endif
    AddLineQueueX( pFmt, edi, T_SEGMENT, pAlign, pUse, SegmCombine[esi*4], pClass )
    ret
SetSimSeg endp

EndSimSeg proc fastcall private segm:sim_seg

    AddLineQueueX( "%s %r", SegmNames[segm*4], T_ENDS )
    ret

EndSimSeg endp

    assume ebx:ptr asm_tok

SimplifiedSegDir proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

 ;; Handles simplified segment directives:
 ;; .CODE, .STACK, .DATA, .DATA?, .FARDATA, .FARDATA?, .CONST

    .new init:char_t
    .new opndx:expr

    .return( ERROR ) .if ( ModuleInfo._model == MODEL_NONE )

    LstWrite( LSTTYPE_DIRECTIVE, 0, NULL )

    xor  edi,edi
    inc  i ;; get past the directive token
    imul ebx,i,16
    add  ebx,tokenarray
    mov  esi,GetSflagsSp( [ebx-16].tokval )

    .if ( esi == SIM_STACK )
        .if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR )
            .return( ERROR )
        .endif
        .if( opndx.kind == EXPR_EMPTY )
            mov opndx.value,DEFAULT_STACK_SIZE
        .elseif( opndx.kind != EXPR_CONST )
            asmerr( 2026 )
            .return( ERROR )
        .endif
    .else
        ;; Masm accepts a name argument for .CODE and .FARDATA[?] only.
        ;; JWasm also accepts this for .DATA[?] and .CONST unless
        ;; option -Zne is set.

        .if ( [ebx].token == T_ID && \
            ( esi == SIM_CODE || esi == SIM_FARDATA || esi == SIM_FARDATA_UN \
            || ( ModuleInfo.strict_masm_compat == FALSE && \
               ( esi == SIM_DATA || esi == SIM_DATA_UN || esi == SIM_CONST ) ) ) )
            mov edi,[ebx].string_ptr
            inc i
        .endif
    .endif

    imul ebx,i,16
    add  ebx,tokenarray

    .if ( [ebx].token != T_FINAL )
        .return( asmerr( 2008, [ebx].string_ptr ) )
    .endif

    .if ( esi != SIM_STACK )
        close_currseg() ;; emit a "xxx ENDS" line to close current seg
    .endif

    .if ( edi == NULL )

        mov ecx,esi
        mov edx,1
        shl edx,cl
        and dl,ModuleInfo.simseg_init
        mov init,dl
    .endif

    .switch( esi )
    .case SIM_CODE ;; .code
        SetSimSeg( SIM_CODE, edi )

        .if ( ModuleInfo._model == MODEL_TINY )
            ;; v2.05: add the named code segment to DGROUP
            .if ( edi )
                AddToDgroup( SIM_CODE, edi )
            .endif
            lea edi,szDgroup
        .elseif ( ModuleInfo._model == MODEL_FLAT )
            lea edi,T("FLAT")
        .else
            .if ( edi == NULL )
                mov edi,SegmNames[SIM_CODE*4]
            .endif
        .endif
        AddLineQueueX( "assume cs:%s", edi )
        .endc
    .case SIM_STACK ;; .stack
        ;; if code is generated which does "emit" bytes,
        ;; the original source line has to be saved.
        ;; v2.05: must not be done after LstWrite() has been called!
        ;; Also, there are no longer bytes "emitted".

        SetSimSeg( SIM_STACK, NULL )
        AddLineQueueX( "ORG 0%xh", opndx.value )
        EndSimSeg( SIM_STACK )
        ;; add stack to dgroup for some segmented models
        .if ( !init )
            .if ( ModuleInfo.distance != STACK_FAR )
                AddToDgroup( SIM_STACK, NULL )
            .endif
        .endif
        .endc
    .case SIM_DATA    ;; .data
    .case SIM_DATA_UN ;; .data?
    .case SIM_CONST   ;; .const
        SetSimSeg( esi, edi )
        AddLineQueue( "assume cs:ERROR" )
        .if ( edi || (!init) )
            AddToDgroup( esi, edi )
        .endif
        .endc
    .case SIM_FARDATA     ;; .fardata
    .case SIM_FARDATA_UN  ;; .fardata?
        SetSimSeg( esi, edi )
        AddLineQueue( "assume cs:ERROR" )
        .endc
    .default ;; shouldn't happen
        .endc
    .endsw

    RunLineQueue()
    .return( NOT_ERROR )

SimplifiedSegDir endp

;;
 ;; Set default values for .CODE and .DATA segment names.
 ;; Called by ModelDirective(), at Pass 1 only.


SetModelDefaultSegNames proc uses esi

    ;; init segment names with default values
    memcpy( &SegmNames, &SegmNamesDef, sizeof(SegmNames) )

    ;; option -nt set?
    .if ( Options.names[OPTN_TEXT_SEG*4] )
        mov SegmNames[SIM_CODE*4],LclAlloc( &[strlen( Options.names[OPTN_TEXT_SEG*4] ) + 1] )
        strcpy( SegmNames[SIM_CODE*4], Options.names[OPTN_TEXT_SEG*4] )
    .else
        mov eax,1
        mov cl,ModuleInfo._model
        shl eax,cl
        .if ( eax & SIZE_CODEPTR )
            ;; for some models, the code segment contains the module name
            mov esi,strlen( SegmNamesDef[SIM_CODE*4] )
            add esi,strlen( &ModuleInfo.name )
            inc esi
            mov SegmNames[SIM_CODE*4],LclAlloc( esi )
            strcpy( SegmNames[SIM_CODE*4], &ModuleInfo.name )
            strcat( SegmNames[SIM_CODE*4], SegmNamesDef[SIM_CODE*4] )
        .endif
    .endif

    ;; option -nd set?
    .if ( Options.names[OPTN_DATA_SEG*4] )
        mov SegmNames[SIM_DATA*4],LclAlloc( &[strlen( Options.names[OPTN_DATA_SEG*4] ) + 1] )
        strcpy( SegmNames[SIM_DATA*4], Options.names[OPTN_DATA_SEG*4] )
    .endif
    ret
SetModelDefaultSegNames endp

;; Called by SetModel() [.MODEL directive].
;; Initializes simplified segment directives.
;; and the caller will run RunLineQueue() later.
;; Called for each pass.

ModelSimSegmInit proc model:int_t

  local buffer[20]:char_t

    mov ModuleInfo.simseg_init,0; ;; v2.09: reset init flags

    ;; create default code segment (_TEXT)
    SetSimSeg( SIM_CODE, NULL )
    EndSimSeg( SIM_CODE )

    ;; create default data segment (_DATA)
    SetSimSeg( SIM_DATA, NULL )
    EndSimSeg( SIM_DATA )

    ;; create DGROUP for BIN/OMF if model isn't FLAT
    .if ( model != MODEL_FLAT && \
        ( Options.output_format == OFORMAT_OMF || Options.output_format == OFORMAT_BIN ))
        strcpy( &buffer, "%s %r %s" )
        .if ( model == MODEL_TINY )
            strcat( &buffer, ", %s" )
            AddLineQueueX( &buffer, &szDgroup, T_GROUP, SegmNames[SIM_CODE*4], SegmNames[SIM_DATA*4] )
        .else
            AddLineQueueX( &buffer, &szDgroup, T_GROUP, SegmNames[SIM_DATA*4] )
        .endif
    .endif
    .return( NOT_ERROR )

ModelSimSegmInit endp

;; called when END has been found

ModelSimSegmExit proc

    ;; a model is set. Close current segment if one is open.
    .if ( CurrSeg )
        close_currseg()
        RunLineQueue()
    .endif
    ret

ModelSimSegmExit endp

    end
