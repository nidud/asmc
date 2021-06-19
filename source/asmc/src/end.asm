; END.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description: directives END, .STARTUP and .EXIT
;

include asmc.inc
include memalloc.inc
include parser.inc
include segment.inc
include extern.inc
include fixup.inc
include lqueue.inc
include tokenize.inc
include expreval.inc
include types.inc
include listing.inc
include proc.inc
include omf.inc
include mangle.inc
include bin.inc

;; prototypes
idata_fixup proto :ptr code_info, :dword, :ptr expr

    .data

    T equ <@CStr>

;; startup code for 8086

ifndef __ASMC64__

StartupDosNear0 string_t \
    T("mov dx,DGROUP"),
    T("mov ds,dx"),
    T("mov bx,ss"),
    T("sub bx,dx"),
    T("shl bx,1"),
    T("shl bx,1"),
    T("shl bx,1"),
    T("shl bx,1"),
    T("cli"),
    T("mov ss,dx"),
    T("add sp,bx"),
    T("sti")

;; startup code for 80186+

StartupDosNear1 string_t \
    T("mov ax,DGROUP"),
    T("mov ds,ax"),
    T("mov bx,ss"),
    T("sub bx,ax"),
    T("shl bx,4"),
    T("mov ss,ax"),
    T("add sp,bx")

StartupDosFar string_t \
    T("mov dx,DGROUP"),
    T("mov ds,dx")

;; mov al, retval  followed by:

ExitOS2 string_t \
    T("mov ah,0"),
    T("push 1"),
    T("push ax"),
    T("call DOSEXIT")


ExitDos string_t \
    T("mov ah,4ch"),
    T("int 21h")


szStartAddr equ <"@Startup">

endif

.code

;; .STARTUP and .EXIT directives

    assume ebx:ptr asm_tok

ifndef __ASMC64__

StartupExitDirective proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

   .new rc:int_t = NOT_ERROR
   .new opndx:expr

    imul ebx,i,asm_tok
    add ebx,tokenarray

    LstWriteSrcLine()

    .if ( ModuleInfo._model == MODEL_NONE )
        .return( asmerr( 2013 ) )
    .endif

    .if ( ModuleInfo.Ofssize > USE16 )
        .return( asmerr( 2199 ) )
    .endif

    .switch ( [ebx].tokval )
    .case T_DOT_STARTUP
        xor edi,edi
        ;; for tiny model, set current PC to 100h.
        .if ( ModuleInfo._model == MODEL_TINY )
            AddLineQueue( "org 100h" )
        .endif
        AddLineQueueX( "%s::", szStartAddr )
        .if ( ModuleInfo.ostype == OPSYS_DOS )
            .if ( ModuleInfo._model == MODEL_TINY )

            .else
                .if ( ModuleInfo.distance == STACK_NEAR )
                    mov eax,ModuleInfo.cpu
                    and eax,M_CPUMSK
                    .if ( eax  <= M_8086 )
                        lea esi,StartupDosNear0
                        mov edi,lengthof( StartupDosNear0 )
                    .else
                        lea esi,StartupDosNear1
                        mov edi,lengthof( StartupDosNear1 )
                    .endif
                .else
                    lea esi,StartupDosFar
                    mov edi,lengthof( StartupDosFar )
                .endif
                .for ( : edi : edi-- )
                    lodsd
                    AddLineQueue( eax )
                .endf
            .endif
        .endif
        mov ModuleInfo.StartupDirectiveFound,TRUE
        add ebx,16 ; skip directive token
        .endc
    .case T_DOT_EXIT
        .if ( ModuleInfo.ostype == OPSYS_DOS )
            lea esi,ExitDos
            mov edi,lengthof( ExitDos )
        .else
            lea esi,ExitOS2;
            mov edi,lengthof( ExitOS2 )
        .endif
        add ebx,16 ; skip directive token
        .if ( [ebx].token != T_FINAL )

            .if ( ModuleInfo.ostype == OPSYS_OS2 )
                AddLineQueueX( "mov ax,%s", [ebx].tokpos )
                imul ebx,Token_Count,asm_tok
            .else
                inc i
                .if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR )
                    .return( ERROR )
                .endif
                .if ( opndx.kind == EXPR_CONST && opndx.value < 0x100 )
                    AddLineQueueX( "mov ax,4C00h + %u", opndx.value )
                .else
                    AddLineQueueX( "mov al,%s", [ebx].tokpos )
                    AddLineQueue ( "mov ah,4Ch" )
                .endif
                imul ebx,i,asm_tok
            .endif
            add ebx,tokenarray
            lodsd
            dec edi
        .endif
        .for ( : edi : edi-- )
            lodsd
            AddLineQueue( eax )
        .endf
        .endc
    .endsw
    .if ( [ebx].token != T_FINAL )
        asmerr(2008, [ebx].tokpos )
        mov rc,ERROR
    .endif

    RunLineQueue()

    .return( rc )
StartupExitDirective endp

endif

;; END directive

EndDirective proc uses esi ebx i:int_t, tokenarray:ptr asm_tok

  local opndx:expr

    inc i ;; skip directive

    ;; v2.08: END may generate code, so write listing first
    LstWriteSrcLine()

    ;; v2.05: first parse the arguments. this allows
    ;; SegmentModuleExit() later to run generated code.

ifndef __ASMC64__
    .if ( ModuleInfo.StartupDirectiveFound )
        ;; start label behind END ignored if .STARTUP has been found
        mov esi,Token_Count
        .if ( i < esi && Parse_Pass == PASS_1 )
            asmerr( 4003 )
        .endif
        inc esi
        mov i,esi
        imul ebx,esi,asm_tok
        add ebx,tokenarray
        mov [ebx].token,T_ID
        mov [ebx].string_ptr,&T(szStartAddr)
        mov [ebx+16].token,T_FINAL
        mov [ebx+16].string_ptr,&T("")
        inc esi
        mov Token_Count,esi
    .endif
endif
    ;; v2.11: flag EXPF_NOUNDEF added - will return ERROR if start label isn't defined
    .if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) == ERROR )
        .return( ERROR )
    .endif
    imul ebx,i,asm_tok
    add ebx,tokenarray
    .if ( [ebx].token != T_FINAL )
        .return( asmerr(2008, [ebx].tokpos ) )
    .endif
    mov ecx,CurrStruct
    .if ( ecx )
        .while ( [ecx].dsym.next )
            mov ecx,[ecx].dsym.next
        .endw
        asmerr( 1010, [ecx].asym.name )
    .endif
    ;; v2.10: check for open PROCedures
    ProcCheckOpen()

    ;; check type of start label. Must be a symbolic code label, internal or external
    mov esi,opndx.sym
    .if ( opndx.kind == EXPR_ADDR && !( opndx.flags & E_INDIRECT ) && \
        ( opndx.mem_type == MT_NEAR || opndx.mem_type == MT_FAR || ( opndx.mem_type == MT_EMPTY && opndx.inst == T_OFFSET ) ) && \
        esi && ( [esi].asym.state == SYM_INTERNAL || [esi].asym.state == SYM_EXTERNAL ) )

        .if ( Options.output_format == OFORMAT_OMF )

            .new CodeInfo:code_info
            mov CodeInfo.opnd[0].InsFixup,NULL
            mov CodeInfo.token,T_NOP
            movzx eax,IndexFromToken(T_NOP)
            mov CodeInfo.pinstr,&InstrTable[eax*8]
            mov CodeInfo.flags,0
            mov CodeInfo.mem_type,MT_EMPTY
            idata_fixup( &CodeInfo, 0, &opndx )
            mov ModuleInfo.start_fixup,CodeInfo.opnd[0].InsFixup
            mov ModuleInfo.start_displ,opndx.value
        .else
            .if ( [esi].asym.state != SYM_EXTERNAL && !( [esi].asym.flags & S_ISPUBLIC ) )
                or [esi].asym.flags,S_ISPUBLIC
                AddPublicData( esi )
            .endif
            mov ModuleInfo.start_label,esi
        .endif
    .elseif ( opndx.kind != EXPR_EMPTY )
        .return( asmerr( 2094 ) )
    .endif

    ;; close open segments
    SegmentModuleExit()

    .if ( ModuleInfo.EndDirHook )
        ModuleInfo.EndDirHook( &ModuleInfo )
    .endif

    mov ModuleInfo.EndDirFound,TRUE

    .return( NOT_ERROR )
EndDirective endp

    end
