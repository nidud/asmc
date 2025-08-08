; END.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description: directives END, .STARTUP and .EXIT
;

include asmc.inc
include parser.inc
include segment.inc
include extern.inc
include expreval.inc
include types.inc
include listing.inc
include proc.inc
include lqueue.inc

; prototypes

idata_fixup proto __ccall :ptr code_info, :dword, :ptr expr

    .data

    T equ <@CStr>

; startup code for 8086

ifndef ASMC64

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

; .STARTUP and .EXIT directives

    assume rbx:token_t

ifndef ASMC64

StartupExitDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

   .new rc:int_t = NOT_ERROR
   .new opndx:expr

    imul ebx,i,asm_tok
    add rbx,tokenarray

    LstWriteSrcLine()

    .if ( MODULE._model == MODEL_NONE )
        .return( asmerr( 2013 ) )
    .endif

    .if ( MODULE.Ofssize > USE16 )
        .return( asmerr( 2199 ) )
    .endif

    .switch ( [rbx].tokval )
    .case T_DOT_STARTUP
        xor edi,edi
        ;; for tiny model, set current PC to 100h.
        .if ( MODULE._model == MODEL_TINY )
            AddLineQueue( "org 100h" )
        .endif
        AddLineQueueX( "%s::", szStartAddr )
        .if ( MODULE.ostype == OPSYS_DOS )
            .if ( MODULE._model == MODEL_TINY )

            .else
                .if ( MODULE.distance == STACK_NEAR )
                    mov eax,MODULE.cpu
                    and eax,M_CPUMSK
                    .if ( eax  <= M_8086 )
                        lea rsi,StartupDosNear0
                        mov edi,lengthof( StartupDosNear0 )
                    .else
                        lea rsi,StartupDosNear1
                        mov edi,lengthof( StartupDosNear1 )
                    .endif
                .else
                    lea rsi,StartupDosFar
                    mov edi,lengthof( StartupDosFar )
                .endif
                .for ( : edi : edi--, rsi+=string_t )
                    AddLineQueue( [rsi] )
                .endf
            .endif
        .endif
        mov MODULE.StartupDirectiveFound,TRUE
        add rbx,asm_tok ; skip directive token
        .endc
    .case T_DOT_EXIT
        .if ( MODULE.ostype == OPSYS_DOS )
            lea rsi,ExitDos
            mov edi,lengthof( ExitDos )
        .else
            lea rsi,ExitOS2
            mov edi,lengthof( ExitOS2 )
        .endif
        add rbx,asm_tok ; skip directive token
        .if ( [rbx].token != T_FINAL )

            .if ( MODULE.ostype == OPSYS_OS2 )
                AddLineQueueX( "mov ax,%s", [rbx].tokpos )
                imul ebx,TokenCount,asm_tok
            .else
                inc i
                .ifd ( EvalOperand( &i, tokenarray, TokenCount, &opndx, 0 ) == ERROR )
                    .return( ERROR )
                .endif
                .if ( opndx.kind == EXPR_CONST && opndx.value < 0x100 )

                    AddLineQueueX( "mov ax,4C00h + %u", opndx.value )
                .else
                    AddLineQueueX(
                        "mov al,%s\n"
                        "mov ah,4Ch", [rbx].tokpos )
                .endif
                imul ebx,i,asm_tok
            .endif
            add rbx,tokenarray
            add rsi,string_t
            dec edi
        .endif

        .for ( : edi : edi--, rsi+=string_t )
            AddLineQueue([rsi])
        .endf
        .endc
    .endsw
    .if ( [rbx].token != T_FINAL )
        asmerr( 2008, [rbx].tokpos )
        mov rc,ERROR
    .endif

    RunLineQueue()
   .return(rc)

StartupExitDirective endp

endif

; END directive

EndDirective proc __ccall uses rsi rbx i:int_t, tokenarray:token_t

  local opndx:expr

    inc i ; skip directive

    ; v2.08: END may generate code, so write listing first

    LstWriteSrcLine()

    ; v2.05: first parse the arguments. this allows
    ; SegmentModuleExit() later to run generated code.

ifndef ASMC64
    .if ( MODULE.StartupDirectiveFound )
        ; start label behind END ignored if .STARTUP has been found
        mov esi,TokenCount
        .if ( i < esi && Parse_Pass == PASS_1 )
            asmerr( 4003 )
        .endif
        inc esi
        mov i,esi
        imul ebx,esi,asm_tok
        add rbx,tokenarray
        mov [rbx].token,T_ID
        mov [rbx].string_ptr,&T(szStartAddr)
        mov [rbx+asm_tok].token,T_FINAL
        mov [rbx+asm_tok].string_ptr,&T("")
        inc esi
        mov TokenCount,esi
    .endif
endif
    ; v2.11: flag EXPF_NOUNDEF added - will return ERROR if start label isn't defined
    .ifd ( EvalOperand( &i, tokenarray, TokenCount, &opndx, EXPF_NOUNDEF ) == ERROR )
        .return( ERROR )
    .endif
    imul ebx,i,asm_tok
    add rbx,tokenarray
    .if ( [rbx].token != T_FINAL )
        .return( asmerr(2008, [rbx].tokpos ) )
    .endif
    mov rcx,CurrStruct
    .if ( rcx )
        .while ( [rcx].asym.next )
            mov rcx,[rcx].asym.next
        .endw
        asmerr( 1010, [rcx].asym.name )
    .endif

    ; v2.10: check for open PROCedures

    ProcCheckOpen()

    ; v2.19 close open segments before calling idata_fixup(). This sets
    ; CurrSeg = NULL if simplified segment directives are ON.

    SegmentModuleExit()

    ; check type of start label. Must be a symbolic code label, internal or external

    mov rsi,opndx.sym
    .if ( opndx.kind == EXPR_ADDR && !( opndx.indirect ) &&
         ( opndx.mem_type == MT_NEAR || opndx.mem_type == MT_FAR ||
         ( opndx.mem_type == MT_EMPTY && opndx.inst == T_OFFSET ) ) &&
         rsi && ( [rsi].asym.state == SYM_INTERNAL || [rsi].asym.state == SYM_EXTERNAL ) )

        .if ( Options.output_format == OFORMAT_OMF )

           .new CodeInfo:code_info
            mov CodeInfo.opnd[0].InsFixup,NULL
            mov CodeInfo.token,T_NOP
            movzx eax,IndexFromToken(T_NOP)
            lea rcx,InstrTable
            lea rax,[rcx+rax*instr_item]
            mov CodeInfo.pinstr,rax
            mov CodeInfo.flags,0
            mov CodeInfo.mem_type,MT_EMPTY
            idata_fixup( &CodeInfo, 0, &opndx )
            mov MODULE.start_fixup,CodeInfo.opnd[0].InsFixup
            mov MODULE.start_displ,opndx.value
        .else
            .if ( [rsi].asym.state != SYM_EXTERNAL && !( [rsi].asym.ispublic ) )
                mov [rsi].asym.ispublic,1
                AddPublicData(rsi)
            .endif
            mov MODULE.start_label,rsi
        .endif
    .elseif ( opndx.kind != EXPR_EMPTY )
        .return( asmerr( 2094 ) )
    .endif

    ; close open segments

    ;SegmentModuleExit() - v2.19 moved

    .if ( MODULE.EndDirHook )

        MODULE.EndDirHook()

ifdef _EXEC_LINK
    .elseif ( Parse_Pass == PASS_1 )
        mov rcx,MODULE.curr_fname[OBJ*string_t]
        .if ( rcx )
            CollectLinkObject(rcx)
        .endif
endif
    .endif

    mov MODULE.EndDirFound,TRUE
   .return( NOT_ERROR )

EndDirective endp

    end
