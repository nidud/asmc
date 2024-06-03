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

SimGetSegName proc fastcall segno:sim_seg

    lea rax,SegmNames
    .return( [rax+rcx*string_t] )

SimGetSegName endp


GetCodeClass proc __ccall

    ; option -nc set?
    .if ( Options.names[OPTN_CODE_CLASS*string_t] )
        .return( Options.names[OPTN_CODE_CLASS*string_t] )
    .endif
    lea rax,SegmClass
   .return( [rax+SIM_CODE*string_t] )

GetCodeClass endp


; emit DGROUP GROUP instruction

AddToDgroup proc fastcall private segm:sim_seg, name:string_t

    ; no DGROUP for FLAT or COFF/ELF
    .if ( ModuleInfo._model == MODEL_FLAT || Options.output_format == OFORMAT_COFF ||
          Options.output_format == OFORMAT_ELF )

        .return
    .endif

    .if ( rdx == NULL )

        lea rdx,SegmNames
        mov rdx,[rdx+rcx*string_t]
    .endif
    AddLineQueueX( "%s %r %s", &szDgroup, T_GROUP, rdx )
    ret

AddToDgroup endp


; generate code to close the current segment

close_currseg proc __ccall private

    mov rcx,CurrSeg
    .if ( rcx )
        AddLineQueueX( "%s %r", [rcx].asym.name, T_ENDS )
    .endif
    ret

close_currseg endp


; translate a simplified segment directive to
; a standard segment directive line

SetSimSeg proc __ccall private uses rsi rdi rbx segm:sim_seg, name:string_t

    .new pAlign:string_t = "WORD"
    .new pAlignSt:string_t = "PARA"
    .new pUse:string_t = ""
    .new calign[16]:char_t
    .new sym:ptr asym
    .new pFmt:string_t
    .new pClass:string_t

    ; v2.24 /Sp[n] Set segment alignment

    .if ( Options.segmentalign != 4 )

        mov edx,1
        mov cl,Options.segmentalign
        shl edx,cl
        tsprintf( &calign, "ALIGN(%d)", edx )
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
        lea rcx,SegmClass
        mov pClass,[rcx+rsi*size_t]
    .endif

    .if ( esi == SIM_STACK || esi == SIM_FARDATA || esi == SIM_FARDATA_UN )
        mov pAlign,pAlignSt
    .endif

    mov pFmt,&T("%s %r %s %s %s '%s'")
    mov rdi,name

    .if ( rdi == NULL )

        lea rcx,SegmNames
        mov rdi,[rcx+rsi*size_t]

        mov ebx,1
        mov ecx,esi
        shl ebx,cl

        .if ( ModuleInfo.simseg_init & bl )
            mov pFmt,&T("%s %r")
        .else

            or ModuleInfo.simseg_init,bl

            ; v2.05: if segment exists already, use the current attribs.
            ; This allows a better mix of full and simplified segment
            ; directives. Masm behaves differently: the attributes
            ; of the simplified segment directives have highest priority.

            .if ( Parse_Pass == PASS_1 )

                SymSearch( rdi )

                ; v2.12: check 'isdefined' member instead of 'lname_idx'

                .if ( rax && [rax].asym.state == SYM_SEG && [rax].asym.flags & S_ISDEFINED )
                    or ModuleInfo.simseg_defd,bl
                .endif
            .endif
            .if ( ModuleInfo.simseg_defd & bl )
                mov pFmt,&T("%s %r")
            .endif
        .endif
    .else

        SymSearch( rdi )

        ; v2.04: testing for state SYM_SEG isn't enough. The segment
        ; might have been "defined" by a GROUP directive. Additional
        ; check for segment's lname index is needed.
        ; v2.12: check 'isdefined' member instead of 'lname_idx'

        .if ( rax && [rax].asym.state == SYM_SEG && [rax].asym.flags & S_ISDEFINED )
            mov pFmt,&T("%s %r")
        .endif
    .endif
    lea rax,SegmCombine
    mov rcx,[rax+rsi*size_t]
    AddLineQueueX( pFmt, rdi, T_SEGMENT, pAlign, pUse, rcx, pClass )
    ret

SetSimSeg endp


EndSimSeg proc fastcall private segm:sim_seg

    lea rax,SegmNames
    mov rdx,[rax+rcx*size_t]
    AddLineQueueX( "%s %r", rdx, T_ENDS )
    ret

EndSimSeg endp


GetCodeGroupName proc fastcall private name:string_t

    ldr rax,name

    .if ( ModuleInfo._model == MODEL_FLAT ||
          Options.output_format == OFORMAT_COFF ||
          Options.output_format == OFORMAT_ELF )

        .if ( rax == NULL )
            mov rax,SegmNames[SIM_CODE*size_t]
        .endif
    .else
        lea rax,szDgroup
    .endif
    ret

GetCodeGroupName endp


    assume rbx:ptr asm_tok

SimplifiedSegDir proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

 ; Handles simplified segment directives:
 ; .CODE, .STACK, .DATA, .DATA?, .FARDATA, .FARDATA?, .CONST

    .new init:char_t
    .new opndx:expr

    .return( ERROR ) .if ( ModuleInfo._model == MODEL_NONE )

    LstWrite( LSTTYPE_DIRECTIVE, 0, NULL )

    xor  edi,edi
    inc  i ; get past the directive token
    imul ebx,i,asm_tok
    add  rbx,tokenarray
    mov  esi,GetSflagsSp( [rbx-asm_tok].tokval )

    .if ( esi == SIM_STACK )
        .ifd ( EvalOperand( &i, tokenarray, TokenCount, &opndx, 0 ) == ERROR )
            .return( ERROR )
        .endif
        .if( opndx.kind == EXPR_EMPTY )
            mov opndx.value,DEFAULT_STACK_SIZE
        .elseif( opndx.kind != EXPR_CONST )
            asmerr( 2026 )
            .return( ERROR )
        .endif
    .else
        ; Masm accepts a name argument for .CODE and .FARDATA[?] only.
        ; JWasm also accepts this for .DATA[?] and .CONST unless
        ; option -Zne is set.

        .if ( [rbx].token == T_ID &&
            ( esi == SIM_CODE || esi == SIM_FARDATA || esi == SIM_FARDATA_UN
            || ( Options.strict_masm_compat == FALSE &&
               ( esi == SIM_DATA || esi == SIM_DATA_UN || esi == SIM_CONST ) ) ) )
            mov rdi,[rbx].string_ptr
            inc i
        .endif
    .endif

    imul ebx,i,asm_tok
    add  rbx,tokenarray

    .if ( [rbx].token != T_FINAL )
        .return( asmerr( 2008, [rbx].string_ptr ) )
    .endif

    .if ( esi != SIM_STACK )
        close_currseg() ; emit a "xxx ENDS" line to close current seg
    .endif

    .if ( rdi == NULL )

        mov ecx,esi
        mov edx,1
        shl edx,cl
        and dl,ModuleInfo.simseg_init
        mov init,dl
    .endif

    .switch( esi )
    .case SIM_CODE ; .code

        SetSimSeg( SIM_CODE, rdi )

        .if ( ModuleInfo._model == MODEL_TINY )

            ; v2.34.61 - v2.05: add the named code segment to DGROUP

            .if ( rdi )

                ; v2.17: don't add to DGROUP if code segment's wordsize isn't the default wordsize;
                ;        todo: check why this "auto adding" has been implemented.

                .if ( SymSearch( rdi ) && [rax].asym.state == SYM_SEG )

                    mov rax,[rax].dsym.seginfo
                    mov al,[rax].seg_info.Ofssize

                    .if ( al == ModuleInfo.defOfssize )

                        AddToDgroup( SIM_CODE, rdi )
                        mov rdi,GetCodeGroupName( rdi )
                    .endif
                .endif
            .else
                mov rdi,GetCodeGroupName( rdi )
            .endif

        .elseif ( ModuleInfo._model == MODEL_FLAT )

            lea rdi,T("FLAT")

        .else
            .if ( rdi == NULL )
                mov rdi,SegmNames[SIM_CODE*size_t]
            .endif

            ; v2.34.61 - v2.13: added

            .if ( SymSearch( rdi ) && [rax].asym.state == SYM_SEG )

                mov rax,[rax].dsym.seginfo
                mov rax,[rax].seg_info.sgroup
                .if ( rax )
                    mov rdi,[rax].asym.name
                .endif
            .endif
        .endif
        AddLineQueueX( "assume cs:%s", rdi )
       .endc
    .case SIM_STACK ; .stack
        ; if code is generated which does "emit" bytes,
        ; the original source line has to be saved.
        ; v2.05: must not be done after LstWrite() has been called!
        ; Also, there are no longer bytes "emitted".

        SetSimSeg( SIM_STACK, NULL )
        AddLineQueueX( "ORG 0%xh", opndx.value )
        EndSimSeg( SIM_STACK )
        ; add stack to dgroup for some segmented models
        .if ( !init )
            .if ( ModuleInfo.distance != STACK_FAR )
                AddToDgroup( SIM_STACK, NULL )
            .endif
        .endif
        .endc
    .case SIM_DATA    ; .data
    .case SIM_DATA_UN ; .data?
    .case SIM_CONST   ; .const
        SetSimSeg( esi, rdi )
        AddLineQueue( "assume cs:ERROR" )
        .if ( rdi || (!init) )
            AddToDgroup( esi, rdi )
        .endif
        .endc
    .case SIM_FARDATA     ; .fardata
    .case SIM_FARDATA_UN  ; .fardata?
        SetSimSeg( esi, rdi )
        AddLineQueue( "assume cs:ERROR" )
        .endc
    .default ; shouldn't happen
        .endc
    .endsw

    RunLineQueue()
   .return( NOT_ERROR )

SimplifiedSegDir endp


; Set default values for .CODE and .DATA segment names.
; Called by ModelDirective(), at Pass 1 only.


SetModelDefaultSegNames proc __ccall uses rsi

    ; init segment names with default values
    tmemcpy( &SegmNames, &SegmNamesDef, sizeof(SegmNames) )

    ; option -nt set?

    .if ( Options.names[OPTN_TEXT_SEG*size_t] )

        mov SegmNames[SIM_CODE*size_t],LclDup( Options.names[OPTN_TEXT_SEG*size_t] )

    .else

        mov eax,1
        mov cl,ModuleInfo._model
        shl eax,cl

        .if ( eax & SIZE_CODEPTR )

            ; for some models, the code segment contains the module name

            mov esi,tstrlen( SegmNamesDef[SIM_CODE*size_t] )
            add esi,tstrlen( &ModuleInfo.name )
            inc esi
            mov SegmNames[SIM_CODE*size_t],LclAlloc( esi )
            tstrcpy( SegmNames[SIM_CODE*size_t], &ModuleInfo.name )
            tstrcat( SegmNames[SIM_CODE*size_t], SegmNamesDef[SIM_CODE*size_t] )
        .endif
    .endif

    ; option -nd set?
    .if ( Options.names[OPTN_DATA_SEG*size_t] )
        mov SegmNames[SIM_DATA*size_t],LclDup( Options.names[OPTN_DATA_SEG*size_t] )
    .endif
    ret

SetModelDefaultSegNames endp


; Called by SetModel() [.MODEL directive].
; Initializes simplified segment directives.
; and the caller will run RunLineQueue() later.
; Called for each pass.

ModelSimSegmInit proc __ccall model:int_t

  local buffer[20]:char_t

    mov ModuleInfo.simseg_init,0; ; v2.09: reset init flags

    ; create default code segment (_TEXT)
    SetSimSeg( SIM_CODE, NULL )
    EndSimSeg( SIM_CODE )

    ; create default data segment (_DATA)
    SetSimSeg( SIM_DATA, NULL )
    EndSimSeg( SIM_DATA )

    ; create DGROUP for BIN/OMF if model isn't FLAT
    .if ( model != MODEL_FLAT &&
         ( Options.output_format == OFORMAT_OMF || Options.output_format == OFORMAT_BIN ) )

        tstrcpy( &buffer, "%s %r %s" )
        .if ( model == MODEL_TINY )
            tstrcat( &buffer, ", %s" )
            AddLineQueueX( &buffer, &szDgroup, T_GROUP, SegmNames[SIM_CODE*size_t], SegmNames[SIM_DATA*size_t] )
        .else
            AddLineQueueX( &buffer, &szDgroup, T_GROUP, SegmNames[SIM_DATA*size_t] )
        .endif
    .endif
    .return( NOT_ERROR )

ModelSimSegmInit endp


; called when END has been found

ModelSimSegmExit proc __ccall

    ; a model is set. Close current segment if one is open.
    .if ( CurrSeg )
        close_currseg()
        RunLineQueue()
    .endif
    ret

ModelSimSegmExit endp

    end
