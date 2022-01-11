; CONTEXT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description: Processing of PUSHCONTEXT and POPCONTEXT directives.
;

include asmc.inc
include memalloc.inc
include parser.inc
include assume.inc
include expreval.inc
include fastpass.inc
include listing.inc

; v2.10: static variables moved to ModuleInfo

define contextStack     <ModuleInfo.ContextStack>
define contextFree      <ModuleInfo.ContextFree>
define cntsavedContexts <ModuleInfo.cntSavedContexts>
define savedContexts    <ModuleInfo.SavedContexts>

.enum context_type {
    CONT_ASSUMES   = 0x01,
    CONT_RADIX     = 0x02,
    CONT_LISTING   = 0x04,
    CONT_CPU       = 0x08,
    CONT_ALIGNMENT = 0x10, ; new for v2.0, specific for JWasm
    CONT_ALL       = CONT_ASSUMES or CONT_RADIX or CONT_LISTING or CONT_CPU,
    }

.data

typetab context_type \
    CONT_ASSUMES,
    CONT_RADIX,
    CONT_LISTING,
    CONT_CPU,
    CONT_ALIGNMENT,
    CONT_ALL

contextnames string_t \
    @CStr("ASSUMES"),
    @CStr("RADIX"),
    @CStr("LISTING"),
    @CStr("CPU"),
    @CStr("ALIGNMENT"),
    @CStr("ALL")


define NUM_STDREGS 16

; Masm has a max context nesting level of 10.
; JWasm has no restriction currently.

.template assumes_context
    SegAssumeTable assume_info NUM_SEGREGS dup(<>)
    StdAssumeTable assume_info NUM_STDREGS dup(<>)
    type_content stdassume_typeinfo NUM_STDREGS dup(<>)
   .ends

.template listing_context
    list_macro listmacro ?
    list db ?
    cref db ?
    listif db ?
    list_generated_code db ?
   .ends

.template cpu_context
    cpu int_t ?             ; saved ModuleInfo.cpu
    curr_cpu cpu_info ?     ; saved ModuleInfo.curr_cpu
   .ends

.template radix_context
    radix db ?              ; saved ModuleInfo.radix
   .ends

.template alignment_context
    fieldalign db ?         ; saved ModuleInfo.fieldalign
    procalign db ?          ; saved ModuleInfo.procalign
   .ends


; v2.10: the type-specific data is now declared as a union;
; and PUSH|POPCONTEXT ALL will push/pop 4 single items.
; all items are equal in size, this made it possible to implement
; a "free items" heap.

.template context
    next ptr context ?
    type context_type ?
    union
        rc  radix_context <>
        alc alignment_context <>
        lc  listing_context <>
        cc  cpu_context <>
        ac  assumes_context <>
    ends
   .ends

ifndef ASMC64
extern sym_Cpu:ptr asym
endif

.code

; v2.10: major rewrite of this function

    assume rbx:ptr asm_tok
    assume r14:ptr context

ContextDirective proc __ccall uses rsi rdi rbx r12 r13 r14 i:int_t, tokenarray:ptr asm_tok

    imul ebx,ecx,asm_tok
    add rbx,rdx

   .new start:ptr asm_tok = rbx
   .new directive:int_t = [rbx].tokval

    inc i ; skip CONTEXT keyword
    add rbx,asm_tok

    .while ( [rbx].token == T_ID )

        lea r12,contextnames
        .for ( esi = 0, edi = -1: esi < lengthof(typetab): esi++ )

            .if ( tstricmp( [r12+rsi*8], [rbx].string_ptr ) == 0 )

                lea rcx,typetab
                mov edi,[rcx+rsi*4]
                .break
            .endif
        .endf
        .break .if ( edi == -1 )

        ; reject ALIGNMENT if strict masm compat is on

        .if ( ModuleInfo.strict_masm_compat )
            .if ( edi == CONT_ALIGNMENT )
                .break
            .else
                and edi,not CONT_ALIGNMENT ; in case ALIGNMENT is again included in ALL
            .endif
        .endif

        .if ( directive == T_POPCONTEXT )

            ; for POPCONTEXT, check if appropriate items are on the stack

            .for ( r12d = NULL, r14 = contextStack : r14 && edi : r14 = r13 )

                mov r13,[r14].next
                mov ecx,[r14].type
                .if ( !( ecx & edi ) ) ; matching item on the stack?
                    mov r12,r14
                    .continue
                .endif
                not ecx
                and edi,ecx
                .if ( r12 )
                    mov [r12].context.next,r13
                .else
                    mov contextStack,r13
                .endif

                mov [r14].next,contextFree
                mov contextFree,r14

                ; restore the values

                mov eax,[r14].type
                .switch pascal eax
                .case CONT_ASSUMES
                    SetSegAssumeTable( &[r14].ac.SegAssumeTable )
                    SetStdAssumeTable( &[r14].ac.StdAssumeTable, &[r14].ac.type_content )
                .case CONT_RADIX
                    mov ModuleInfo.radix,       [r14].rc.radix
                .case CONT_ALIGNMENT
                    mov ModuleInfo.fieldalign,  [r14].alc.fieldalign
                    mov ModuleInfo.procalign,   [r14].alc.procalign
                .case CONT_LISTING
                    mov ModuleInfo.list_macro,  [r14].lc.list_macro
                    mov ModuleInfo.list,        [r14].lc.list
                    mov ModuleInfo.cref,        [r14].lc.cref
                    mov ModuleInfo.listif,      [r14].lc.listif
                    mov ModuleInfo.list_generated_code, [r14].lc.list_generated_code
                .case CONT_CPU
                    mov ModuleInfo.cpu,         [r14].cc.cpu
ifndef ASMC64
                    mov rcx,sym_Cpu
                    .if ( rcx )
                        mov [rcx].asym.value,   [r14].cc.cpu
                    .endif
endif
                    mov ModuleInfo.curr_cpu,    [r14].cc.curr_cpu
                .endsw
            .endf
            .if ( edi )
                mov rcx,start
                .return( asmerr( 1010, [rcx].asm_tok.tokpos ) )
            .endif

        .else

            .for ( esi = 0: esi < lengthof(typetab) && edi: esi++ )

                lea r12,typetab
                mov eax,[r12+rsi*4]

                .if ( edi & eax )

                    not eax
                    and edi,eax

                    .if ( contextFree )
                        mov r14,contextFree
                        mov contextFree,[r14].next
                    .else
                        mov r14,LclAlloc( sizeof( context ) )
                    .endif

                    mov [r14].next,contextStack
                    mov [r14].type,[r12+rsi*4]
                    mov contextStack,r14
                    ;mov eax,[r12+rsi*4]
                    .switch pascal eax
                    .case CONT_ASSUMES
                        GetSegAssumeTable( &[r14].ac.SegAssumeTable )
                        GetStdAssumeTable( &[r14].ac.StdAssumeTable, &[r14].ac.type_content )
                    .case CONT_RADIX
                        mov [r14].rc.radix,         ModuleInfo.radix
                    .case CONT_ALIGNMENT
                        mov [r14].alc.fieldalign,   ModuleInfo.fieldalign
                        mov [r14].alc.procalign,    ModuleInfo.procalign
                    .case CONT_LISTING
                        mov [r14].lc.list_macro,    ModuleInfo.list_macro
                        mov [r14].lc.list,          ModuleInfo.list
                        mov [r14].lc.cref,          ModuleInfo.cref
                        mov [r14].lc.listif,        ModuleInfo.listif
                        mov [r14].lc.list_generated_code, ModuleInfo.list_generated_code
                    .case CONT_CPU
                        mov [r14].cc.cpu,           ModuleInfo.cpu
                        mov [r14].cc.curr_cpu,      ModuleInfo.curr_cpu
                    .endsw
                .endif
            .endf
        .endif
        add rbx,asm_tok
        .if ( [rbx].token == T_COMMA && [rbx+asm_tok].token != T_FINAL )
            add rbx,asm_tok
        .endif
    .endw
    .if ( [rbx].token != T_FINAL || edi == -1 )
        .return( asmerr(2008, [rbx].tokpos ) )
    .endif
    .return( NOT_ERROR )
ContextDirective endp

; save current context status

    assume rdi:ptr context

ContextSaveState proc __ccall uses rsi rdi rbx

    .for ( ecx = 0, rdx = contextStack : rdx : ecx++, rdx = [rdx].context.next )
    .endf
    .if ( ecx )
        mov cntsavedContexts,ecx
        imul ecx,ecx,sizeof( context )
        mov savedContexts,LclAlloc( ecx )
        .for ( rsi = contextStack, rdi = rax : rsi : rsi = [rsi].context.next )

            mov rdx,rsi
            mov ecx,sizeof( context )
            rep movsb
            mov rsi,rdx
        .endf
    .endif
    ret
ContextSaveState endp

; restore context status

ContextRestoreState proc __ccall private uses rsi rdi rbx

    .for ( ebx = cntsavedContexts : ebx : ebx-- )
        .if ( contextFree )
            mov rdi,contextFree
            mov contextFree,[rdi].next
        .else
            mov rdi,LclAlloc( sizeof( context ) )
        .endif
        lea rax,[rbx-1]
        imul esi,eax,sizeof( context )
        add rsi,savedContexts
        mov ecx,sizeof( context )
        mov rdx,rdi
        rep movsb
        mov rdi,rdx
        mov [rdi].next,contextStack
        mov contextStack,rdi
    .endf
    ret

ContextRestoreState endp

; init context, called once per pass

ContextInit proc __ccall pass:int_t

    ; if ContextStack isn't NULL, then at least one PUSHCONTEXT
    ; didn't have a matching POPCONTEXT. No need to reset it to NULL -
    ; but might be ok to move the items to the ContextFree heap.

    .if ( ecx > PASS_1 )
        ContextRestoreState()
    .endif
    ret
ContextInit endp

    end
